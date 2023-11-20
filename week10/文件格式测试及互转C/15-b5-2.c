/* 2254298 大数据 范潇 */
#define _CRT_SECURE_NO_WARNINGS
#define MAXFILESIZE 200
#include<string.h>
#include<stdio.h>
void Usage(char* name)
{
	printf("Usage : %s --check 文件名 | --convert { wtol|ltow } 源文件名 目标文件名\n", name);
	printf("        %s --check a.txt\n",name);
	printf("        %s --convert wtol a.win.txt a.linux.txt\n", name);
	printf("        %s --convert ltow a.linux.txt a.win.txt\n", name);
	return;
}
int main(int argc, char** argv)
{
	char  input[10];
	if (argc != 3 && argc != 5) {
		Usage(argv[0]);
		return 0;
	}
	int wtol = 0;
	int ltow = 0;
	int in = 0, out = 0;
	if (argc == 3 && strcmp(argv[1], "--check")) {
		Usage(argv[0]);
		return 0;
	}
	if ((argc == 5) && (strcmp(argv[1], "--convert") ||( strcmp(argv[2], "wtol") && strcmp(argv[2], "ltow")))) {
		Usage(argv[0]);
		return 0;
	}
	if (argc == 3)
		in = 2;
	else {
		in = 3;
		out = 4;
		if (!strcmp(argv[2], "ltow"))
			ltow = 1;
		else if (!strcmp(argv[2], "wtol"))
			wtol = 1;
		else {
			Usage(argv[0]);
			return 0;
		}
	}
	FILE* infile=fopen(argv[in],"rb");
	if(!infile){
		printf("文件打开失败\n");
		return -1;
	}
	fseek(infile, 0,SEEK_END);
	long long end = ftell(infile), count = 0;
	fseek(infile, 0,SEEK_SET);
	int windows = 0, Linux = 0;
	int D = 0;
	while (count < end) {
		fread(input, 1, 1, infile);
		if (input[0] == 0x0D)
			D = 1;
		else if (input[0] == 0x0A && D) {
			windows = 1;
			D = 0;
		}
		else if (input[0] == 0x0A) {
			Linux = 1;
		}
		else
			D = 0;
		if (windows && Linux)
			break;
		count++;
	}
	int invalid = !(windows ^ Linux);
	if (invalid) {
		printf("文件无法识别\n");
		return 0;
	}
	if (argc == 3) {
		if (windows)
			printf("Windows格式\n");
		else
			printf("Linux格式\n");
		fclose(infile);
		return 0;
	}
	if ((wtol && Linux) || (ltow && windows)) {
		printf("文件无法识别\n");
		return 0;
	}
	FILE* outfile = fopen(argv[out], "wb");
	if (!outfile) {
		printf("文件打开失败\n");
		fclose(outfile);
		return -1;
	}
	count = 0;
	int num = 0;
	fseek(infile, 0, SEEK_SET);
	int flag = 0;
	while (count < end) {//wtol时，读到0D0A只写0A。ltow时，读到0A写0A0D
		if(!flag)
			fread(input, 1, 1, infile);
		flag = 0;
		if (input[0] == 0x0A && ltow) {
			fputc(0x0D, outfile);
			fputc(0x0A, outfile);
			num++;
		}
		else if (input[0] == 0x0D && wtol) {
			if (count + 1 == end) {
				fputc(input[0], outfile);
				break;
			}
			fread(input, 1, 1, infile);
			if (input[0] == 0x0A) {
				fputc(0x0A, outfile);
				num++;
				count++;
			}
			else {
				fputc(0x0D, outfile);
				flag = 1;
			}
		}
		else
			putc(input[0], outfile);
		count++;
	}
	printf("转换成功，");
	if (wtol)
		printf("去除");
	else
		printf("加入");
	printf("%d个0x0D\n", num);
	fclose(infile);
	fclose(outfile);
	return 0;
}