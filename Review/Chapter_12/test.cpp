/* 2254298 大数据 范潇 */
#include<iostream>
using namespace std;
int main()
{
	int a[12] = { 0 };
	cout << sizeof(a) << endl;
	cout << sizeof(&a[0]) << endl;
	//首元素的地址，仍是一个变量的地址，所以不能再对其取地址
	cout << sizeof(char*) << endl;
	//&(& a[0]);
	//报错
	int b[12][12] = { 0 };
	cout << sizeof(&(b[0])) << endl;
	cout<< &(b[0]) << endl;
	cout<< &(b[0])+1 << endl;
	cout << sizeof(&(b[0])) << endl;
	cout << typeid(*(&b[2])).name() << endl;
	cout << typeid(*b).name() << endl;
	cout << typeid(b[0]).name() << endl;
	cout << typeid(*(b+0)).name() << endl;
	cout << typeid(&*b).name() << endl;
	cout << typeid(&b[0]).name() << endl;
	cout << typeid(&*(b+0)).name() << endl;
	return 0;
}