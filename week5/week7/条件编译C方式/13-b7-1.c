/* 2254298 ������ ���� */
#include <stdio.h>

int main()
{
    /* ��������������໥λ�ÿɻ���������Ŀǰ#if���������VS2022�������Ȼ�ΪLinux��*/
#if (***)
    printf("VS2022\n");
#elif (***)
    printf("Dev\n");
#elif (***)
    printf("Linux\n");
#endif

    return 0;
}