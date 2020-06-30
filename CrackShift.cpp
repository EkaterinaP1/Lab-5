#include "CrackShift.h"


CrackShift::CrackShift()
{
    PTObj = new PoolThread(4);
    PTObj->SetMaxQueueSize(1000);
    PTObj->Start();
}

CrackShift::~CrackShift()
{
    delete PTObj;
}
//////////////////////////////////////////////////////////////////
bool CrackShift::GetEncryptText(string name) {
		std::ifstream in(name);
		if (in.fail()) {
			std::cout << "file is not present\n";
			return false;
		}
		string file_contents{ std::istreambuf_iterator<char>(in), istreambuf_iterator<char>() };
		this->ctext = file_contents;
		in.close();
		return true;
}
//////////////////////////////////////////////////////////////////
bool CrackShift::GetAlphabet(string name) {
        std::ifstream in(name);
        if (in.fail()) {
			std::cout << "file is not present\n";
			return false;
		}
        std::string buf;
        while (std::getline(in, buf))
            if (buf.size() > 0)
                this->alphabet.push_back(buf);
		in.close();
		return true;
}
//////////////////////////////////////////////////////////////////
void CrackShift::Crack() {
	vector<int> job_id;
	vector<int> length_key = find_length_key();

	for (int i = 0; i < length_key.size(); i++) {	
		BruteForceJob* bfj = new BruteForceJob(this->ctext, this->alphabet, length_key[i]);
		AJob* njob = bfj;
		int nid = this->PTObj->ASyncSubmitJob(njob);
		job_id.push_back(nid);
	}

	while (true) {
		//this->PTObj->PrintQueue();
		int count_compl = 0;
		for (int i = 0; i < job_id.size(); i++)
			if (this->PTObj->GetJobStatusId(job_id[i]) == 3) count_compl++;
		if (job_id.size() == count_compl)
			break;
		Sleep(1000);
		
	}
	int num_entry = 0;
	string s_result = "";
	for (int i = 0; i < job_id.size(); i++) {
		AJob* tjob = this->PTObj->GetResJob(job_id[i]);
		string tmp_result = tjob->GetResult();
		if (tmp_result.size() > 0) {
			std::size_t pos = tmp_result.find("\n");
			std::string num_entry_s = tmp_result.substr(0, pos);
			std::string::size_type sz;
			int num_entry_i = std::stoi(num_entry_s, &sz);
			if (num_entry_i > num_entry) {
				num_entry = num_entry_i;
				s_result = tmp_result.substr(pos+1);
			}
		}
	}
	this->text = s_result;
	
}

void CrackShift::WriteText(string name) {
	ofstream fout;
	fout.open(name);
	fout << this->text;
	fout.close();

}

vector<int> CrackShift::find_length_key() {
	vector<int> length_key;
	if (this->ctext.size() != 0) {
		
		for (int i = 2; i <= this->ctext.size(); i++) {
			int del = this->ctext.size() % i;
			//Ограничили размер ключа, т.к. длина ключа более 12 дает
			//очень много перестановок
			if ((del == 0) and (i <= 12)) 
				length_key.push_back(i);
		}
	}
	return length_key;
}
