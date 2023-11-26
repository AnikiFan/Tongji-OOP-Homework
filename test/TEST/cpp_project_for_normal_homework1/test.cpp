#include<iostream>
#include<fstream>
using namespace std;
int main()
{
	ofstream a("a.txt", ios::out | ios::binary);
	a.put('a');
	a.close();
	return 0;
}