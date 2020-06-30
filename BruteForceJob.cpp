#include "BruteForceJob.h"

BruteForceJob::BruteForceJob(string ctext, vector<string> alphabet, int ksize)
{
    this->ctext = ctext;
    this->alphabet = alphabet;
    this->key_size = ksize;
    this->result = "";
}

BruteForceJob::~BruteForceJob()
{
    //dtor
}

void BruteForceJob::ExecJob() {

	
	string res;
	
	auto tsize = this->ctext.size();
	int hsize = tsize / this->key_size + ((tsize % this->key_size != 0) ? 1 : 0);


	string** Arr = new string * [this->key_size];
	for (int i = 0; i < static_cast<int>(this->key_size); i++)
		Arr[i] = new string[hsize];

	
	//std::cout << alphabet.size();
	auto it = 0;
	for (auto i = 0; i < static_cast<int>(this->key_size); i++)
	{
		for (auto j = 0; j < hsize; j++)
		{
			if (it < static_cast<int>(this->ctext.size())) {
				Arr[i][j] = this->ctext[it];
				it++;
			}
			else Arr[i][j] = "-";
		}
	}

	//for (int i = 0; i < hsize; i++)
	//{
	//	for (int j = 0; j < static_cast<int>(this->key_size); j++)
	//	{
	//		cout << Arr[j][i];
	//	}
	//	std::cout << std::endl;
	//}
	vector<int> vec;
	for (int i = 0; i < this->key_size; i++)
		vec.push_back(i);
	
	int num_entry = 0;
	vector<int> skey;
	string detext = "";
	while (next_permutation(vec.begin(), vec.end())) { //перебираем все варианты сочитаний
		string tmp_text = "";
		int count = 0;
		vector <int>new_key;
		
		for (const auto& i : vec)
			new_key.push_back(i); //берем ключ

		for (auto i = 0; i < hsize; i++) //дешифруем по ключу
			for (auto j = 0; j < static_cast<int>(this->key_size); j++)
			{
				auto tt = static_cast<int>(new_key[j]);
				tmp_text += Arr[tt][i];
			}

		for (int i = 0; i < alphabet.size(); i++) {//сравниваем результат со словарем, подсчитываем сочетания
			string word = alphabet[i];
			int n = tmp_text.find(word);
			if (n >= 0) {
				count++;
				//std::cout << count << std::endl;
			}
		}
		//std::cout << tmp_text << count << std::endl;
		if ((count > 0))
			if (num_entry < count) {
				num_entry = count;
				skey = new_key;
				detext = tmp_text;
			}
	}

	if (num_entry > 0) {
		int countd = 0;
		for (auto rit = detext.crbegin(); rit != detext.crbegin() + this->key_size; ++rit) {
			if (*rit == '-') countd++;
			else break;
		}
		detext.erase(detext.size() - countd);


		res += to_string(num_entry) + "\n";
		string tmp = "";
		for (int j = 0; j < this->key_size; j++) 
			tmp += to_string(skey[j]);
		res += tmp + "\n";
		res += detext;
	}
	this->result = res;
}

string BruteForceJob::GetResult() {
    return this->result;
}