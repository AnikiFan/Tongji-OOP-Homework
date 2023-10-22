/* 2254298 大数据 范潇 */
#include<iostream>
#include<fstream>
using namespace std;
#define STOP 9999999
#define MAXINFOLENGTH 10
struct student {
	int *no;
	char *name;
	int *score;
	struct student* next;
};
int main()
{
	int no,i;
	char temp[MAXINFOLENGTH];
	ifstream fin;
	fin.open("list.txt", ios::in);
	if (!fin.is_open()) {
		cout << "打开文件失败" << endl;
		return -1;
	}
	student* head = new (nothrow)student, * p;
	if (!head) {
		cout << "分配内存失败" << endl;
		return -1;
	}
	head->next = NULL;
	fin >> no;
	p = head;
	while (no != STOP) {
		p->no = new (nothrow)int;
		if (!p->no) {
			cout << "分配内存失败" << endl;
			return -1;
		}
		fin >> temp;
		i = 0;
		while(temp [i]!= '\0')
			i++;	
		p->name = new (nothrow)char[i+1];
		if (!p->name) {
			cout << "分配内存失败" << endl;
			return -1;
		}
		for(int j = 0;j<i;j++)
			p->name[j] = temp[j];
		p->name[i] = '\0';
		p->score = new (nothrow)int;
		if (!p->score) {
			cout << "分配内存失败" << endl;
			return -1;
		}
		fin  >> *(p->score);
		*(p->no) = no;
		p->next = new (nothrow)student;
		if (!p->next) {
			cout << "分配内存失败" << endl;
			return -1;
		}
		p = p->next;
		p->next = NULL;
		fin >> no;
	}
	p = head;
	while (p->next) {
		cout <<*( p->no) << " " << p->name << " " <<*( p->score )<< endl;
		p = p->next;
	}
	p = head;
	while (p->next) {
		head = p;
		p = p->next;
		delete head->no;
		delete[]head->name;
		delete head->score;
		delete head;
	}
	fin.close();
	delete p;
	return 0;
}