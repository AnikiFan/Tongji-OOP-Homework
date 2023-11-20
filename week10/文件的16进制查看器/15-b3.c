/* 2254298 大数据 范潇 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<string.h>
#define INPUTSIZE 10
#define MAXNAMESIZE 200
#define TEST_ENVIRONMENT 0
void usage(char * name)
{
	printf("Usage : %s --infile 原始文件 [ --outfile hex格式文件 ]\n",name);
	printf("        %s --infile a.docx\n",name);
	printf("        %s --infile a.docx --outfile a.hex\n",name);
	return;
}
int main(int argc,char**argv)
{
	int in=0, out=0;
	if (argc != 3 && argc != 5) {
		usage(argv[0]);
		return 0;
	}
	if (argc == 3) {
		if (strcmp("--infile", argv[1])) {
			usage(argv[0]);
			return 0;
		}
		in = 2;
	}
	if (argc == 5) {
		if (!strcmp("--infile", argv[1]) && !strcmp("--outfile", argv[3])) {
			in = 2;
			out = 4;
		}
		else if (!strcmp("--infile", argv[3]) && !strcmp("--outfile", argv[1])) {
			in = 4;
			out = 2;
		}
		else {
			 usage(argv[0]);
			return 0;
		}
	}
	FILE* infile;
	if (argc == 3) {
		infile = fopen(argv[in], "rb");
		if (!infile) {
			printf("输入文件%s打开失败!\n", argv[in]);
			return -1;
		}
	}
	else {
		infile =fopen(argv[in], "rb");
		if (!infile) {
			printf("输入文件%s打开失败!\n", argv[in]);
			return -1;
		}
		FILE* temp = fopen(argv[out], "w");
		if (!temp) {
			printf("输出文件%s打开失败!\n", argv[out]);
			fclose(infile);
			return -1;
		}
		freopen(argv[out], "w", stdout);
		fclose(temp);
	}
	char input[INPUTSIZE], buff[20] = { 0 };
	int top = 0;
	fseek(infile, 0, SEEK_END);
	int end = ftell(infile), count = 0;
	fseek(infile, 0, SEEK_SET);
	while (count < end) {
		if (!((count - 8) % 16))
			printf(" -");
		if (!(count % 16))
			printf("%08x ", count);
		fread(input,1,1,infile);
		printf(" %02x", ((int)(unsigned char)input[0]));
		buff[top++] = input[0];
		if (top == 16) {
			printf("     ");
			top = 0;
			for (int i = 0; i < 16; i++)
				if (buff[i] >= 33 && buff[i] <= 126)
					putchar(buff[i]);
				else
					putchar('.');
			printf("\n");
		}
		count++;
	}
	if (!top)
		return 0;
	printf("  ");
	for (int i = 0; i < 16 - top; i++)
		printf("   ");
	if (top <= 8)
		printf("  ");
	printf("   ");
	for (int i = 0; i < top; i++)
		if (buff[i] >= 33 && buff[i] <= 126)
			putchar(buff[i]);
		else
			putchar('.');
	printf("\n");
	fclose(infile);
	return 0;
}