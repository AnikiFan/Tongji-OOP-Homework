/* 2254298 ������ ���� */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
struct test {
	int a;
	int b;
};
int main()//TODO:���Ϊ����������δָ����ʽ�ģ���Ҫ�� double �ͣ�C++Ϊ cout ȱʡ�����C Ϊ%lf ��ȱʡ���
{
	struct	test temp = { 1,2 },receive;
	receive = temp;
	printf("%d %d\n", receive.a, receive.b);
	return 0;
}