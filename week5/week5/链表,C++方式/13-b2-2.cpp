/* 2254298 大数据 范潇 */
#include<iostream>
#include<fstream>
using namespace std;
#define STOP 9999999
struct student {
	int no;
	char name[9];
	int score;
	struct student* next;
};
int main()
{
	int no;
	ifstream fin;
	fin.open("list.txt", ios::in);
	if (!fin.is_open()) {
		cout<<"打开文件失败"<<endl;
		return -1;
	}
	student* head = new (nothrow)student,*p;
	if (!head) {
		cout<<"分配内存失败"<<endl;
		return -1;
	}
	head->next = NULL;
	fin >> no;
	p = head;
	while (no != STOP) {
		p->no = no;
		fin >> p->name >> p->score;
		p->next = new (nothrow)student;
		if (!p->next) {
			cout<<"分配内存失败"<<endl;
			return -1;
		}
		p = p->next;
		p->next = NULL;
		fin >> no;
	}
	p = head;
	while (p->next) {
		cout << p->no << " " << p->name << " " << p->score << endl;
		p = p->next;
	}
	p = head;
	while (p->next) {
		head = p;
		p = p->next;
		delete head;
	}
	fin.close();
	delete p;
	return 0;
}