#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
struct test {
	char ch[10];
	char* p;
};
int main()
{
	test t1,t2;
	t1.ch[0] = 'a';
	t1.ch[1] = 'b';
	t1.ch[2] = 'c';
	t1.ch[3] = '\0';
	t2.ch[0] = 'd';
	t2.ch[1] = 'e';
	t2.ch[2] = 'f';
	t2.ch[3] = '\0';
	cout<<&t1.ch<<endl;
	cout<<&(t1.ch[0])<<endl;
	cout<<t2.ch<<endl;
	int p[10] ;
	t1 = t2;
	cout<<&t1.ch<<endl;
	cout << p << endl;
	cout << (void*)p << endl;
	cout << &p << endl;
	return 0;
}