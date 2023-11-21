/* 2254298 ´óÊı¾İ ·¶äì */
#include<iostream>
#include<fstream>
using namespace std;
int main()
{
	fstream outfile("test.out", ios::out|ios::in);
	char a = 'a';
	char temp = 0;
	outfile.write(&a, 1);
	outfile.read(&temp, 1);

	return 0;
}