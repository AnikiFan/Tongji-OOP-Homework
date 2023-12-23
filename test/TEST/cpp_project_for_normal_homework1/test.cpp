#include<sstream>
#include<iostream>
using namespace std;
int main()
{
	stringstream test;
	test << "\t\t     first \t second  \t third \t   " << endl;
	string info1, info2, info3, temp;
	test >> info1 >> info2 >> info3;
	cout << info1 << endl << info2 << endl << info3 << endl;
	cout << test.eof() << endl;
	test >> temp;
	cout << temp << endl;
	cout << temp.length() << endl;
	cout << test.eof() << endl;
	
	return 0;
}