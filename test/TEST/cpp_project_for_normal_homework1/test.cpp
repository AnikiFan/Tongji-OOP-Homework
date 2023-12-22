#include<iostream>

using namespace std;
typedef int ElemType;
typedef struct BST {
	ElemType key;
	int n;
	BST* lchild, * rchild;
}BST;
void insert(BST*& T, ElemType x)
{
	if (!T) {
		T = new BST;
		if (!T) {
			cout << "OVERFLOW" << endl;
			getchar();
			return;
		}
		T->rchild = NULL;
		T->lchild = NULL;
		T->key = x;
		T->n = 1;
		return;
	}
	if (x == T->key)
		T->n++;
	else {
		BST* p = T;
		BST* pre = NULL;
		while (p && p->key != x) {
			pre = p;
			if (p->key < x)
				p = p->rchild;
			else
				p = p->lchild;
		}
		if (p)
			p->n++;
		else {
			p = new BST;
			if (pre->key < x)
				pre->rchild = p;
			else
				pre->lchild = p;
			if (!T) {
				cout << "OVERFLOW" << endl;
				getchar();
				return;
			}
			p->rchild = NULL;
			p->lchild = NULL;
			p->key = x;
			p->n = 1;
		}
	}
	return;
}
void sum(BST* T, ElemType x)
{
	if (!T) {
		cout << "0" << endl;
		return;
	}
	BST* p = T;
	while (p && p->key != x)
		if (p->key < x)
			p = p->rchild;
		else
			p = p->lchild;
	if (p)
		cout << p->n << endl;
	else
		cout << "0" << endl;
	return;
}
int min(BST* T)
{
	BST* p = T;
	if (!T) {
		cout << "-1" << endl;
		return -1;
	}
	while (p->lchild)
		p = p->lchild;
	cout << p->key << endl;
	return p->key;
}

void get_rear(BST* T, BST*& target, ElemType x)
{
	if (!T)
		return;
	get_rear(T->lchild, target, x);
	if (T->key < x)
		target = T;
	get_rear(T->rchild, target, x);
	return;
}
void rear(BST* T, ElemType x)
{
	BST* target = NULL;
	get_rear(T, target, x);
	if (!target)
		cout << "None" << endl;
	else
		cout << target->key << endl;
	return;
}
void del(BST*& T, ElemType x, BST*& pre,int remove)
{
	if (!T) {
		cout << "None" << endl;
		return;
	}
	BST* p = T;
	//寻找删除元素
	while (p && p->key != x) {
		pre = p;
		if (p->key < x)
			p = p->rchild;
		else
			p = p->lchild;
	}
	//未找到
	if (!p) {
		cout << "None" << endl;
		return;
	}
	//找到，但是有多个
	if (p->n > 1&&!remove) {
		//cout << p->key << endl;
		p->n--;
		return;
	}
	//叶子结点
	if (!p->rchild && !p->lchild) {
		if (pre&&pre->rchild == p)
			pre->rchild = NULL;
		else if(pre)
			pre->lchild = NULL;
		//cout << p->key << endl;
		free(p);
		if (p == T)
			T = NULL;
		return;
	}
	//	没有左孩子
	if (!p->lchild) {
		if (pre && pre->rchild == p)
			pre->rchild = p->rchild;
		else if (pre && pre->lchild == p)
			pre->lchild = p->rchild;
		else 
			T = T->rchild;
		//cout << p->key << endl;
		free(p);
		return;
	}
	//没有右孩子
	if (!p->rchild) {
		if (pre && pre->lchild == p)
			pre->lchild = p->lchild;
		else if (pre && pre->rchild == p)
			pre->rchild = p->lchild;
		else 
			T = T->lchild;
		//cout << p->key << endl;
		free(p);
		return;
	}
	BST* q = p->lchild;
	pre = p;
	while (q->rchild) {
		pre = q;
		q = q->rchild;
	}
	p->key = q->key;
	p->n = q->n;
	del(q, q->key, pre,1);
	return;
}
int main()
{
	int n;
	int opt;
	int x;
	BST* T = NULL;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> opt;
		if (opt != 4)
			cin >> x;
		BST* pre = NULL;
		switch (opt) {
			case 1:
				insert(T, x);
				break;
			case 2:
				del(T, x, pre,0);
				break;
			case 3:
				sum(T, x);
				break;
			case 4:
				min(T);
				break;
			case 5:
				rear(T, x);
				break;
		}
	}
	return 0;
}