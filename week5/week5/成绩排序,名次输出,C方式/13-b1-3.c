/* 2254298 大数据 范潇 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<malloc.h>
struct student {
	int no;
	char name[9];
	int score;
	int rank;
};
void infocopy(struct student* dst, struct student* src)
{
	dst->no = src->no;
	for (int i = 0; i < 9; i++)
		dst->name[i] = src->name[i];
	dst->score = src->score;
	dst->rank = src->rank;
	return;
}
void infoswitch(struct student* a, struct student* b)
{
	struct student temp;
	infocopy(&temp, a);
	infocopy(a, b);
	infocopy(b, &temp);
	return;
}
//满足某一优先级的下标小，compare中，如果第一个参数优先级高，返回1，否则返回0
void sort(struct student* student_list, int list_length, int (*compare)(struct student*, struct  student*))
{
	for (int i = 0; i < list_length - 1; i++) {
		int k = i;
		for (int j = i + 1; j < list_length; j++)
			if (compare(&student_list[j], &student_list[k]))
				k = j;
		infoswitch(&student_list[i], &student_list[k]);
	}
	return;
}
int  compare_by_score(struct student* a, struct student* b)
{
	return a->score > b->score;
}
int  compare_by_no(struct student* a, struct student* b)
{
	return a->no < b->no;
}
void assign_rank(struct student* student_list, int list_length)
{
	int rank = 0;
	for (int i = 0; i < list_length; i++)
	{
		if (i == 0)
			rank = 1;
		else if (student_list[i].score == student_list[i - 1].score)
			rank = student_list[i - 1].rank;
		else
			rank = i + 1;
		student_list[i].rank = rank;
	}
	return;
}
int main()
{
	FILE* infile;
	infile = fopen("student.txt", "r");
	if (!infile) {
		printf("打开文件失败\n");
		return -1;
	}
	int n;
	fscanf(infile, "%d", &n);
	struct student* student_list = (struct student*)malloc(sizeof(struct student) * n);
	if (!student_list)
	{
		printf("内存分配失败\n");
		return -1;
	}
	for (int i = 0; i < n; i++)
		fscanf(infile, "%d%s%d", &student_list[i].no, student_list[i].name, &student_list[i].score);
	sort(student_list, n, compare_by_no);
	sort(student_list, n, compare_by_score);
	assign_rank(student_list, n);
	for (int i = 0; i < n; i++)
		printf("%d %s %d %d\n", student_list[i].no, student_list[i].name, student_list[i].score, student_list[i].rank);
	free(student_list);
	fclose(infile);
	return 0;
}