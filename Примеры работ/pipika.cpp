//В этой программке расшифровываем плохо зашифрованный шифротекст.
#include<iostream>
#include <sstream>
#include <bitset>
#include<string>
using namespace std;

int f(char a);

int main() {
	string text[11] = {
		"a23a31787c08a00309998594280cc9f2701a6e6dfa10eb45dd46017e36d82beb7671e815996ad5dbd353b51e",
		"83722b777e4cef1146d890977d0ad2f23c052b2bc144a7599c511d3b3b8c69e63975e9479c6dcb949c53ad1f",
		"927230796008bb0d4cd88e976c0b81ff31156e2ce904aa5cd215137536d828f53771e8158970ddd6cf16a851",
		"8f3d2d36674dbd0c469c9ad8671e81f022026869a80cad15cb5d1b783ad830fd2338ee5498679cd6d407ec10",
		"8033317a724cef1c468d9b8b6d14c7b9702a7f2ce110eb41d558173b269769e03379ea5c94679cccd312b851",
		"8f3d2d36765aaa4548d8849d651ac4e5700c6d2cfc0bae15e95b1b6d378a3af77a38f25d8f769cc1d406ec10",
		"84377874785aa145469ec9b6690cd4e535436278fb06a7539015137536d83dfd7673e85a9922c8d0da07ec10",
		"d63e317b7e5cef0d488bc99a6d1dcfb723067f2cfc0ceb4cd340003b269124f77838d3468b22d9cede01b551",
		"9b3d3573795cef12408b8c94715481e33f437b69fa00ae5cca5052623d8d3bb23f76e8509c22cedddd06a016",
		"933c3b733b08a01709df9d8f6114cdb732062b6be70dae15dd5b163b3c9d3ff72475e9478b22cbd1cf1ba51f",
		"9e34787e635cbf1613d7c681670dd5e23206256fe70ee442dd4111736d8e74d36548c26d835bd3fe8e26ec" };

	string open[11];//Открытый текст
	char kk[44];//Ключ
	string str;//Что это?
	char probel;

	bitset<8> b;
	bitset<8> be, bz;//8-битные битсеты. Страх и ненависть.
	int proof = 0, maxproof = 0;//Переменные, проверяющие похожесть символа на пробел
	int t = 1;

	for (int i = 0; i < text[0].length()-2; i += 2) {//Проходимся по длине всего текста
		maxproof = 0;
		for (int h = 0; h < 11; ++h) {
			b = f(text[h][i]);
			b = b << 4;
			b ^= f(text[h][i + 1]);//Получаем 8 бит символа, который хотим проверить. Как в аски.
			proof = 0;
			for (int j = 0; j < 11; ++j) {//в этом цикле сравниваем прошлый символ со всеми в том же столбце
				if (j != h) {
					be = f(text[j][i]);
					be = be << 4;
					be ^= f(text[j][i + 1]);
					be ^= b;

					probel = be.to_ulong();
					if (('A' <= probel && probel <= 'Z') || ('a' <= probel && probel <= 'z')) { proof++; }
					//Если при сложении получается буква, то, считаем, что это пробел
					//Чем больше получилось букв в столбце, тем выше вероятность, что наш символ - пробел
				}
			}
			if (maxproof < proof) {
				maxproof = proof;
				bz = ' ';
				kk[i / 2] = (bz ^ b).to_ulong();
			}
		}
	}
	kk[13] ^= 12;//Тут костыльки пошли. 
	kk[21] ^= 7;
	kk[28] ^= 31;
	kk[34] ^= 74;
	kk[36] ^= 34;
	kk[4] ^= 12;
	kk[40] ^= 29;
	kk[39] ^= 12;
	kk[40] ^= 26;
	cout << "\n";
	char k;
	for (int i = 0; i < 11; i++) {
		for (int h = 0; h < text[0].length() - 2; h += 2) {
			b = f(text[i][h]);
			b = b << 4;
			b ^= f(text[i][h + 1]);
			k = b.to_ulong();
			open[i] += k ^ kk[h / 2];	//Складываем шифротекст с ключом и получаем открытый текст!		
		}
		cout << open[i];
		cout << "\n";
	}
	system("pause");
	return 0; //Конец
}

int f(char a) {//Переводит шестнадцатеричное число в 4 бита
	if (a == 'a')return 10;
	if (a == 'b')return 11;
	if (a == 'c')return 12;
	if (a == 'd')return 13;
	if (a == 'e')return 14;
	if (a == 'f')return 15;
	if (a == '0')return 0;
	if (a == '1')return 1;
	if (a == '2')return 2;
	if (a == '3')return 3;
	if (a == '4')return 4;
	if (a == '5')return 5;
	if (a == '6')return 6;
	if (a == '7')return 7;
	if (a == '8')return 8;
	if (a == '9')return 9;
}