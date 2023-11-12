#define _CRT_SECURE_NO_WARNINGS
#define MAXN 11000
#define OK 1
#define ERROR 0
#define MAXINFOLENGTH 30
#include<stdio.h>
#include<cstdlib>
typedef int Status;
typedef struct {
	char data;
	int lchild;
	int rchild;
}ElemType;
typedef struct {
	ElemType elem[MAXN];
	int root;
} Tree;
Status CreateTree(Tree& T)
{
	int n;
	char temp[MAXINFOLENGTH];
	scanf("%d", &n);
	getchar();
	for (int i = 0; i < n; i++) {
		scanf("%s", temp);
		T.elem[i].data = temp[0];
		scanf("%s", temp);
		if (temp[0] == '-')
			T.elem[i].lchild = -1;
		else
			T.elem[i].lchild = atoi(temp);
		scanf("%s", temp);
		if (temp[0] == '-')
			T.elem[i].rchild = -1;
		else
			T.elem[i].rchild = atoi(temp);
	}
	int valid;
	for (int i = 0; i < n; i++) {
		valid = 1;
		for (int j = 0; j < n; j++)
			if (i != j && (T.elem[j].rchild == i || T.elem[j].lchild == i)) {
				valid = 0;
				break;
			}
		if (valid) {
			T.root = i;
			return OK;
		}
	}
	return ERROR;
}
int Depth(Tree T, int root)
{
	if (root == -1)
		return 0;
	else
		return Depth(T, T.elem[root].lchild) > Depth(T, T.elem[root].rchild) ? Depth(T, T.elem[root].lchild) + 1 : Depth(T, T.elem[root].rchild) + 1;
}
Status valid(Tree T1, int root1, Tree T2, int root2)
{
	if (T1.elem[root1].lchild == -1
		|| T2.elem[root2].lchild == -1
		|| T1.elem[root1].rchild == -1
		|| T2.elem[root2].rchild == -1) {
		if (T1.elem[root1].lchild == -1
			&& T2.elem[root2].lchild == -1
			&& T1.elem[root1].rchild == -1
			&& T2.elem[root2].rchild == -1
			&& T1.elem[root1].data == T2.elem[root2].data)
			return OK;
		else if (T1.elem[root1].lchild == -1 && T2.elem[root2].lchild == -1 &&
			T1.elem[root1].rchild != -1 && T2.elem[root2].rchild != -1
			&& T1.elem[root1].data == T2.elem[root2].data)
			return valid(T1, T1.elem[root1].rchild, T2, T2.elem[root2].rchild);
		else if (T1.elem[root1].lchild != -1 && T2.elem[root2].lchild != -1 &&
			T1.elem[root1].rchild == -1 && T2.elem[root2].rchild == -1
			&& T1.elem[root1].data == T2.elem[root2].data)
			return valid(T1, T1.elem[root1].lchild, T2, T2.elem[root2].lchild);
		else if (T1.elem[root1].lchild != -1 && T2.elem[root2].lchild == -1 &&
			T1.elem[root1].rchild == -1 && T2.elem[root2].rchild != -1
			&& T1.elem[root1].data == T2.elem[root2].data)
			return valid(T1, T1.elem[root1].lchild, T2, T2.elem[root2].rchild);
		else if (T1.elem[root1].lchild == -1 && T2.elem[root2].lchild != -1 &&//都为叶子结点
			T1.elem[root1].rchild != -1 && T2.elem[root2].rchild == -1
			&& T1.elem[root1].data == T2.elem[root2].data)
			return valid(T1, T1.elem[root1].rchild, T2, T2.elem[root2].lchild);
		else
			return ERROR;
	}
	else if (T1.elem[root1].lchild == T2.elem[root2].lchild && T1.elem[root1].rchild == T2.elem[root2].rchild
		&& T1.elem[root1].lchild != T1.elem[root1].rchild)//左右子树对应相等，且左右子树互不相等
		return (valid(T1, T1.elem[root1].lchild, T2, T2.elem[root2].lchild)
			&& valid(T1, T1.elem[root1].rchild, T2, T2.elem[root2].rchild));
	else if (T1.elem[root1].lchild == T2.elem[root2].rchild && T1.elem[root1].rchild == T2.elem[root2].lchild
		&& T1.elem[root1].lchild != T1.elem[root1].rchild)//左右子树交错相等，且左右子树互不相等
		return (valid(T1, T1.elem[root1].lchild, T2, T2.elem[root2].rchild)
			&& valid(T1, T1.elem[root1].rchild, T2, T2.elem[root2].lchild));
	else if (T1.elem[root1].lchild == T2.elem[root2].rchild && T1.elem[root1].rchild == T2.elem[root2].lchild
		&& T1.elem[root1].lchild == T1.elem[root1].rchild)//四个子树都相等
		return((valid(T1, T1.elem[root1].lchild, T2, T2.elem[root2].rchild)
			&& valid(T1, T1.elem[root1].rchild, T2, T2.elem[root2].lchild))
			|| (valid(T1, T1.elem[root1].lchild, T2, T2.elem[root2].lchild)
				&& valid(T1, T1.elem[root1].rchild, T2, T2.elem[root2].rchild)));
	else
		return 0;
}

int main()
{
	Tree T1, T2;
	CreateTree(T1);
	printf("find root: %d\n", T1.root);
	CreateTree(T2);
	printf("find root: %d\n", T2.root);
	printf("valid: %d\n", valid(T1, T1.root, T2, T2.root));
	printf("%d\n", Depth(T1, T1.root));
	printf("%d\n", Depth(T2, T2.root));
	return 0;
}

