/* 2254298 ������ ���� */
#include<iostream>
using namespace std;
inline void fun()
{
	cout << 1 << endl;
}
void test(void(*fun)(void)) {
	fun();
	return;
}
int main()
{
	test(fun);
	return 0;
}