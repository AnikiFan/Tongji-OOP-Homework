/* 2254298 大数据 范潇 */
#include <iostream>
using namespace std;
template <typename T>
/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void test(T(&array))	//将...替换为相应内容
{
	cout << sizeof(array) << endl;	//array为形参名
}
template<typename T>
/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
char* tj_strcpy_s(T(&dst),const char*src)	//将...替换为相应内容
{
	char* d = dst;		//dst为要复制的目标串
	const char* s = src;	//src为要复制的源串

	while (*s != '\0' && d - dst < int(sizeof(dst)) - 1)
		*d++ = *s++;
	*d = '\0';

	return dst;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int main()
{
	int t1[10];
	double t2[20];
	test(t1);	//期望输入40
	test(t2);	//期望输出160

	char s1[10], s2[20];
	const char* s = "Welcome to Tongji University!";
	cout << tj_strcpy_s(s1, s) << '*' << endl; //期望输出：Welcome t*
	cout << tj_strcpy_s(s2, s) << '*' << endl; //期望输出：Welcome to Tongji U*

	return 0;
}