/* 2254298 ������ ���� */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int main()//TODO:���Ϊ����������δָ����ʽ�ģ���Ҫ�� double �ͣ�C++Ϊ cout ȱʡ�����C Ϊ%lf ��ȱʡ���
{
	
	if (1) {
		int integer[10] = { 1,2,3,4,5,6,7,8,9,10 };
		integer[10] = 11;    //�˾�Խ��
		integer[14] = 12;    //�˾�Խ��
		integer[15] = 13;    //�˾�Խ��
		integer[10] = 0xcccccccc; //�˾�Խ��
		printf("addr:%p\n", integer);
		for (int i = -4; i < 16; i++) //ע�⣬ֻ��0-9�Ǻ���Χ�����඼��Խ���
			printf("integer[%2d]:  %p:%08x\n", i, (integer + i), integer[i]);
	}
if (0) {
		char ch[10] = "123456789";
		ch[10] = 'a';    //�˾�Խ��
		ch[14] = 'A';    //�˾�Խ��
		ch[15] = 'B';    //�˾�Խ��
		ch[10] = '\xdd'; //�˾�Խ��
		printf("addr:%p\n", ch);
		for (int i = -6; i < 16; i++) //ע�⣬ֻ��0-9�Ǻ���Χ�����඼��Խ���
			printf("ch[%2d]:  %p:%02x\n", i, (ch + i), ch[i]);
	}
	return 0;
}
