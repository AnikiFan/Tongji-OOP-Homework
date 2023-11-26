#include<iostream>
#include<fstream>
using namespace std;
int main()
{
	ofstream a("a.txt", ios::out | ios::binary);
	for (int i = 0; i < 1000; i++)
	a.put('a');
	a.close();
	return 0;
}