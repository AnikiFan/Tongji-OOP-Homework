/* 2254298 ´óÊı¾İ ·¶äì */
#include<iostream>
#include<fstream>
using namespace std;
int main()
{
	ofstream outfile("out.txt", ios::out | ios::binary);
	outfile.put(0x0A);
	 
	return 0;
}