#define _CRT_SECURE_NO_WARNINGS
#define MAXN 11000
#define OK 1
#define ERROR 0
#define MAXINFOLENGTH 20
#define OVERFLOW {printf("\n\nOVERFLOW\n\n");return -2;}
#include<stack>
#include<stdio.h>
#include<cstdlib>
typedef int Status;
typedef struct {
	char data;
	int lchild;
	int rchild;
}ElemType;
typedef struct {
	ElemType* elem;
	int root;
} Tree;
Status CreateTree(Tree& T)
{
	int n;
	char temp[MAXINFOLENGTH];
	int mark[MAXN] = { 0 };
	scanf("%d", &n);
	getchar();
	for (int i = 0; i < n; i++) {
		scanf("%s", temp);
		T.elem[i].data = temp[0];
		scanf("%s", temp);
		if (temp[0] == '-')
			T.elem[i].lchild = -1;
		else {
			T.elem[i].lchild = atoi(temp);
			mark[T.elem[i].lchild] = 1;
		}
		scanf("%s", temp);
		if (temp[0] == '-')
			T.elem[i].rchild = -1;
		else {
			T.elem[i].rchild = atoi(temp);
			mark[T.elem[i].rchild] = 1;
		}
	}
	for (int i = 0; i < n; i++)
		if (!mark[i]) {
			T.root = i;
			return OK;
		}
	return ERROR;
}
int Depth(Tree T)
{
	std::stack<int>s1, s2;
	int p = T.root;
	int depth = 1;
	int maxdepth = 1;
	while (!s1.empty() || p != -1) {
		while (p != -1) {
			s1.push(p);
			p = T.elem[p].lchild;

			s2.push(depth);
			depth++;
		}
		p = s1.top();
		s1.pop();
		p = T.elem[p].rchild;

		if (p != -1)
			depth = s2.top() + 1;
		else
			depth = s2.top();
		s2.pop();
		if (depth > maxdepth)
			maxdepth = depth;

	}
	return maxdepth;
}
Status valid(Tree T1, int root1, Tree T2, int root2)
{
	if (root1 == -1 && root2 == -1)
		return OK;
	else if (root1 == -1 && root2 != -1 || root1 != -1 && root2 == -1)
		return ERROR;
	else if (T1.elem[root1].data != T2.elem[root2].data)
		return ERROR;
	else
		return (valid(T1, T1.elem[root1].lchild, T2, T2.elem[root2].lchild) && valid(T1, T1.elem[root1].rchild, T2, T2.elem[root2].rchild)
			|| valid(T1, T1.elem[root1].lchild, T2, T2.elem[root2].rchild) && valid(T1, T1.elem[root1].rchild, T2, T2.elem[root2].lchild));
}
Status InitTree(Tree& T)
{
	T.elem = (ElemType*)malloc(sizeof(ElemType) * MAXN);
	if (!T.elem)
		OVERFLOW;
	for (int i = 0; i < MAXN; i++)
		T.elem[i].data = -1;
	return OK;
}

int main()
{
	Tree T1, T2;
	InitTree(T1);
	InitTree(T2);
	CreateTree(T1);
	CreateTree(T2);
	//for(int i = 0;i<6;i++)
	  //printf("%d %d %d\n",T1.elem[i].data,T1.elem[i].lchild,T1.elem[i].rchild);
	if (valid(T1, T1.root, T2, T2.root))
		printf("Yes\n");
	else
		printf("No\n");
	printf("%d\n", Depth(T1));
	printf("%d\n", Depth(T2));
	return 0;
}

