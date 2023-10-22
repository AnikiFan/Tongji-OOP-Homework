/* 2254298 大数据 范潇 */
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#define STOP 9999999
#define MAXINFOLENGTH 10
struct student {
	int* no;
	char* name;
	int* score;
	struct student* next;
};
int main()
{
	int no,i;
	char temp[MAXINFOLENGTH];
	FILE* infile;
	infile = fopen("list.txt", "r");
	if (!infile) {
		printf("打开文件失败\n");
		return -1;
	}
	struct student* head = (struct student*)malloc(sizeof(struct student)), * p;
	if (!head) {
		printf("分配内存失败\n");
		return -1;
	}
	head->next = NULL;
	fscanf(infile, "%d", &no);
	p = head;
	while (no != STOP) {
		p->no = (int*)malloc(sizeof(int));
		if (!p->no) {
			printf("分配内存失败\n");
			return -1;
		}
		*(p->no) = no;
		fscanf(infile, "%s", temp);
		i = 0;
		while (temp[i] != '\0')
			i++;
		p->name = (char*)malloc(sizeof(char) * (i+1));
		if (!p->name) {
				printf("分配内存失败\n");
			return -1;
		}
		for (int j = 0; j < i; j++)
			p->name[j] = temp[j];
		p->name[i] = '\0';
		p->score = (int*)malloc(sizeof(int));
		if (!p->score) {
			printf("分配内存失败\n");
			return -1;
		}
		fscanf(infile, "%d", p->score);
		p->next = (struct student*)malloc(sizeof(struct student));
		if (!p->next) {
			printf("分配内存失败\n");
			return -1;
		}
		p = p->next;
		p->next = NULL;
		fscanf(infile, "%d", &no);
	}
	p = head;
	while (p->next) {
		printf("%d %s %d\n", *(p->no), p->name, *(p->score));
		p = p->next;
	}
	p = head;
	while (p->next) {
		head = p;
		p = p->next;
		free(head->name);
		free(head->no);
		free(head->score);
		free(head);
	}
	free(p);
	fclose(infile);
	return 0;
}