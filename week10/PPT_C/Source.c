#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
int main(int argc, char* argv[])
{
    int status;
    status = freopen("test.txt", "w", stdin);
    printf("%d", status);
    return 0;
}


