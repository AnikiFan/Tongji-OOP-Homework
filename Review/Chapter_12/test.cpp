/* 2254298 ������ ���� */
#include<iostream>
using namespace std;
int main()
{
	int a[12] = { 0 };
	cout << sizeof(a) << endl;
	cout << sizeof(&a[0]) << endl;
	//��Ԫ�صĵ�ַ������һ�������ĵ�ַ�����Բ����ٶ���ȡ��ַ
	cout << sizeof(char*) << endl;
	//&(& a[0]);
	//����
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