/* 2254298 ������ ���� */
#include<iostream>
using namespace std;
int main()
{
	const char* p = "int";
	cout <<strcmp(typeid('a').name(),"char") << endl;
	return 0;
}