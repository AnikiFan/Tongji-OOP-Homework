/* 2254298 大数据 范潇 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
struct test {
	int a;
	int b;
};
int main()//TODO:输出为浮点数的且未指定格式的，均要求 double 型，C++为 cout 缺省输出，C 为%lf 的缺省输出
{
	struct	test temp = { 1,2 },receive;
	receive = temp;
	printf("%d %d\n", receive.a, receive.b);
	return 0;
}