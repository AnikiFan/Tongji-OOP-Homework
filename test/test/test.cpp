/* 2254298 ´óÊı¾İ ·¶äì */
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