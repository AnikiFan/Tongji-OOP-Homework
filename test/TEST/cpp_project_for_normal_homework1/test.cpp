/* 2254298 ������ ���� */
#include<iostream>
using namespace std;
int main(int argc,char ** argv,char** env)
{
	while (env)
		cout << *(env++)<<endl;
	return 0;
}