/* 2254298 大数据 范潇 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<string.h>
#define MAXFILESIZE 200
void usage(char*name)
{
	printf("Usage : %s --infile hex格式文件 --outfile bin格式文件\n",name);
	printf("        %s --infile a.hex --outfile a.bin\n",name);
	return;
}
int main(int argc, char** argv)
{
	int in, out;
	char  input[10];
	if (argc != 5) {
		usage(argv[0]);
		return 0;
	}
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
	FILE* infile;
	infile = fopen(argv[in], "rb");
	if (!infile) {
		printf("输入文件%s打开失败!\n", argv[in]);
		return -1;
	}
	FILE* tempf = fopen(argv[out], "wb");
	if (!tempf) {
		printf("输出文件%s打开失败!\n", argv[out]);
		fclose(infile);
		return -1;
	}
	freopen(argv[out], "wb", stdout);
	fclose(tempf);
	fseek(infile, 0, SEEK_END);
	int end = ftell(infile), count = 10;
	fseek(infile, 10, SEEK_SET);
	while (count + 82 < end) {
		for (int i = 0; i < 8; i++) {
			fread(input, 1, 3, infile);
			if (input[0] > '9')
				input[0] = input[0] - 'a' + '0' + 10;
			if (input[1] > '9')
				input[1] = input[1] - 'a' + '0' + 10;
			printf("%c", (char)((input[0] - '0') * 16 + input[1] - '0')) ;
		}
		fread(input, 1, 2, infile);
		for (int i = 0; i < 8; i++) {
			fread(input, 1, 3, infile);
			if (input[0] > '9')
				input[0] = input[0] - 'a' + 10 + '0';
			if (input[1] > '9')
				input[1] = input[1] - 'a' + 10 + '0';
			printf("%c", (char)((input[0] - '0') * 16 + input[1] - '0')) ;
		}
		count += 82;
		fseek(infile, 32, SEEK_CUR);
	}
	int quit = 0;
	char temp;
	while (1) {
		fread(input, 1, 1, infile);
		temp = input[0];
		if (temp == '-') {
			fread(input, 1, 1, infile);
			continue;
		}
		if (temp == ' ' && quit)
			break;
		else if (temp == ' ')
			quit = 1;
		else {
			quit = 0;
			fread(input, 1, 1, infile);
			if (input[0] > '9')
				input[0] = input[0] - 'a' + 10 + '0';
			if (temp > '9')
				temp = temp - 'a' + 10 + '0';
			printf("%c", (char)((temp - '0') * 16 + input[0] - '0')) ;
		}
	}
	fclose(infile);
	return 0;
}