#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
using namespace std;

//�ؼ��� 
string key[6] = { "main","int","if","else","while","do" };
//�ؼ��ֵ��ֱ���
int keyNum[6] = { 1,2,3,4,5,6 };
//������ͽ�� 
string symbol[17] = { "<",">","!=",">=","<=","==",",",";","(",")","{","}","+","-","*","/","=" };
//char symbol[12]={'<','>','!=','>=','<=','==',',',';','(',')','{','}'};
//������ͽ�����ֱ��� 
int symbolNum[17] = { 7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23 };
//����ļ�ȡ�����ַ� 
string letter[1000];
//���ַ�ת��Ϊ����
string  words[1000];
int length;  //����������ַ�����Ŀ 
int num;

int isSymbol(string s) { //�ж�������ͽ�� 
	int i;
	for (i = 0; i < 17; i++) {
		if (s == symbol[i])
			return symbolNum[i];
	}
	return 0;
}

//�ж��Ƿ�Ϊ���� 
bool isNum(string s) {
	if (s >= "0" && s <= "9")
		return true;
	return false;
}

//�ж��Ƿ�Ϊ��ĸ 
bool isLetter(string s)
{
	if (s >= "a" && s <= "z")
		return true;
	return false;
}

//�ж��Ƿ�Ϊ�ؼ���,�Ƿ����ֱ��� 
int isKeyWord(string s) {
	int i;
	for (i = 0; i < 6; i++) {
		if (s == key[i])
			return keyNum[i];
	}
	return 0;
}

//���ص����ַ������� 
int typeword(string str) {
	if (str >= "a" && str <= "z")   //   ��ĸ 
		return 1;

	if (str >= "0" && str <= "9")   //���� 
		return 2;

	if (str == ">" || str == "=" || str == "<" || str == "!" || str == "," || str == ";" || str == "(" || str == ")" || str == "{" || str == "}"
		|| str == "+" || str == "-" || str == "*" || str == "/")   //�ж�������ͽ�� 
		return 3;

}

string identifier(string s, int n) {
	int j = n + 1;
	int flag = 1;

	while (flag) {
		if (isNum(letter[j]) || isLetter(letter[j])) {
			s = (s + letter[j]).c_str();
			if (isKeyWord(s)) {
				j++;
				num = j;
				return s;
			}
			j++;
		}
		else {
			flag = 0;
		}
	}

	num = j;
	return s;
}

string symbolStr(string s, int n) {
	int j = n + 1;
	string str = letter[j];
	if (str == ">" || str == "=" || str == "<" || str == "!") {
		s = (s + letter[j]).c_str();
		j++;
	}
	num = j;
	return s;
}

string Number(string s, int n) {
	int j = n + 1;
	int flag = 1;

	while (flag) {
		if (isNum(letter[j])) {
			s = (s + letter[j]).c_str();
			j++;
		}
		else {
			flag = 0;
		}
	}

	num = j;
	return s;
}

void print(string s, int n) {
	cout << "(" << s << "," << n << ")" << endl;
}

void TakeWord() {  //ȡ���� 
	int k;

	for (num = 0; num < length;) {
		string str1, str;
		str = letter[num];
		k = typeword(str);
		switch (k) {
		case 1:
		{
			str1 = identifier(str, num);
			if (isKeyWord(str1))
				print(str1, isKeyWord(str1));
			else
				print(str1, 0);
			break;
		}

		case 2:
		{
			str1 = Number(str, num);
			print(str1, 24);
			break;
		}

		case 3:
		{
			str1 = symbolStr(str, num);
			print(str1, isSymbol(str1));
			break;
		}

		}

	}
}

int main() {
	char w;
	int i, j;

	freopen("s.txt", "r", stdin);
	freopen("result.txt", "w", stdout); //�ӿ���̨������������ı����

	length = 0;
	while (cin >> w) {
		if (w != ' ') {
			letter[length] = w;
			length++;
		}   //ȥ�������еĿո�
	}

	TakeWord();
	//  for(j=0;j<length;j++){
	//      cout<<letter[j]<<endl;
	//  } 

	fclose(stdin);//�ر��ļ� 
	fclose(stdout);//�ر��ļ� 
	return 0;
}