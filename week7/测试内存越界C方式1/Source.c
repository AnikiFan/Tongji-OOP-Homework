/* 2254298 大数据 范潇 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int main()//TODO:输出为浮点数的且未指定格式的，均要求 double 型，C++为 cout 缺省输出，C 为%lf 的缺省输出
{
	
	if (1) {
		int integer[10] = { 1,2,3,4,5,6,7,8,9,10 };
		integer[10] = 11;    //此句越界
		integer[14] = 12;    //此句越界
		integer[15] = 13;    //此句越界
		integer[10] = 0xcccccccc; //此句越界
		printf("addr:%p\n", integer);
		for (int i = -4; i < 16; i++) //注意，只有0-9是合理范围，其余都是越界读
			printf("integer[%2d]:  %p:%08x\n", i, (integer + i), integer[i]);
	}
if (0) {
		char ch[10] = "123456789";
		ch[10] = 'a';    //此句越界
		ch[14] = 'A';    //此句越界
		ch[15] = 'B';    //此句越界
		ch[10] = '\xdd'; //此句越界
		printf("addr:%p\n", ch);
		for (int i = -6; i < 16; i++) //注意，只有0-9是合理范围，其余都是越界读
			printf("ch[%2d]:  %p:%02x\n", i, (ch + i), ch[i]);
	}
	return 0;
}
