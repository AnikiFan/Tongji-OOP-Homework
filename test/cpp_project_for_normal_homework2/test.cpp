#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int main()
{
	int i;
	double d;
	FILE* infile;
	infile = fopen("d.txt", "r");
	if (infile == NULL) {
		printf("打开文件失败\n");
		return -1;
	}
	fscanf(infile, "%d %lf", &i, &d);
	printf("i=%d\n", i);
	printf("d=%lf\n", d);
	fclose(infile);
	return 0;
}