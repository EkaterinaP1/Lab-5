#include "CrackShift.h"
using namespace std;

int main() {
	setlocale(LC_ALL, "ru");

	//Пытаемся расшифровать
	CrackShift* CSObj = new CrackShift();
	if (!CSObj->GetEncryptText("sencr.txt")) {
		delete CSObj;
		exit(0);
	}
	if (!CSObj->GetAlphabet("alph.txt")) {
		delete CSObj;
		exit(0);
	}
	CSObj->Crack();
	CSObj->WriteText("text.txt");
	delete CSObj;

	return 0;
}
