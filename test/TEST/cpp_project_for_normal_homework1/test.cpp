#include<iostream>
#include<fstream>
using namespace std;
int main()
{
	ofstream a("a.txt", ios::out | ios::binary);
	a.put('\v');
	a.put('\r');
	a.put(EOF);
	a.close();
	return 0;
}