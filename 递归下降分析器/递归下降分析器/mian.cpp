
#define _CRT_SECURE_NO_WARNINGS
#if 0
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define LEN 100

char str[LEN];
int i;
bool flag = true;

void E();
void E1();
void T();
void T1();
void F();
void F1();
void P();

int main() {
	int m;
	printf("��������ԵĴ���:");
	scanf("%d", &m);
	while (m--) {
		printf("�������ַ���(��#����):");
		scanf("%s", &str);
		i = 0;
		E();
		if (flag == true) {
			printf("%sΪ�Ϸ��ַ���!\n", str);
		}
		else {
			printf("%sΪ�Ƿ��ַ���!\n", str);
		}
		strcpy(str, "");
	}
	return 0;
}

void E() {
	if (flag) {
		if (str[i] == '(' || str[i] == 'a' || str[i] == 'b' || str[i] == 'v') {
			T();
			E1();
		}
		else {
			flag = false;
		}
	}
}

void E1() {
	if (flag) {
		if (str[i] == '+') {
			i++;
			E();
		}
		else if (str[i] != '#'&&str[i] != ')') {
			flag = false;
		}
	}
}

void T() {
	if (flag) {
		if (str[i] == '(' || str[i] == 'a' || str[i] == 'b' || str[i] == 'v') {
			F();
			T1();
		}
		else {
			flag = false;
		}
	}
}

void T1() {
	if (flag) {
		if (str[i] == '(' || str[i] == 'a' || str[i] == 'b' || str[i] == 'v') {
			T();
		}
		else if (str[i] != '+'&&str[i] != ')'&& str[i] != '#') {
			flag = false;
		}
	}
}

void F() {
	if (flag) {
		if (str[i] == '(' || str[i] == 'a' || str[i] == 'b' || str[i] == 'v') {
			P();
			F1();
		}
		else {
			flag = false;
		}
	}
}

void F1() {
	if (flag) {
		if (str[i] == '*') {
			i++;
			F1();
		}
		else if (str[i] != '('&&str[i] != 'a'&&str[i] != 'b'&&str[i] != 'v'&&str[i] != '+'&&str[i] != ')'&&str[i] != '#') {
			flag = false;
		}
	}
}

void P() {
	if (flag) {
		if (str[i] == '(') {
			i++;
			E();
			if (str[i] == ')') {
				i++;
			}
		}
		else if (str[i] == 'a') {
			i++;
		}
		else if (str[i] == 'b') {
			i++;
		}
		else if (str[i] == 'v') {
			i++;
		}
		else {
			flag = false;
		}
	}
}
#endif
#include<stdio.h>    
#include<string> 
char str[50];
int index = 0;
void E();                //E->TX; 
void X();                //X->+TX | e 
void T();                //T->FY 
void Y();                //Y->*FY | e 
void F();                //F->(E) | i 

int main()                /*�ݹ����*/
{
	int len;
	int m;
	printf("������Ҫ���ԵĴ�����");
	scanf("%d", &m);
	while (m--)
	{
		printf("�������ַ���(����<50>��:\n");
		scanf("%s", str);
		len = strlen(str);
		//str[len]='#';
		str[len + 1] = '\0';
		E();
		printf("%sΪ�Ϸ����Ŵ�!\n", str);
		strcpy(str, "");
		index = 0;
	} 
	return 0;
}

void E()
{
	T();    X();
}
void X()
{
	if (str[index] == '+')
	{
		index++;
		T();
		X();
	}
}
void T()
{
	F();     Y();
}
void Y()
{
	if (str[index] == '*') {
		index++;
		F();
		Y();
	}
}
void F()
{
	if (str[index] == 'i')
	{
		index++;
	}
	else if (str[index] == '(')
	{
		index++;
		E();
		if (str[index] == ')')
		{
			index++;
		}
		else
		{
			printf("\n�Ƿ��ķ��Ŵ�!\n");
			exit(0);
		}
	}
	else
	{
		printf("�Ƿ��ķ��Ŵ�!\n");
		exit(0);
	}
}
