/* 2254298 ������ ���� */
#include<iostream>
#include<fstream>
using namespace std;
#define MAXINFOLENGTH 20
struct student {
	int no;
	char* info;
	char* school;
};
//����n��С��MAX������������ظ�
void make_random_list(int* list, const int n,const int MAX)
{
	int i = 0,temp,same;
	while (i <= n) {
		same = 0;
		temp = rand() % MAX;
		for(int j=0;j<i;j++)
			if (temp == list[j]) {
				same = 1;
				break;
			}
		if(same)
			continue;
		list[i] = temp;
		i++;
	}
}
int main()
{
	int* random_list;
	int n, MAX, i;
	char temp[MAXINFOLENGTH];
	ifstream fin;
	ofstream fout;
	fin.open("stulist.txt", ios::in);
	if (!fin.is_open()) {
		cout << "���ļ�ʧ��" << endl;
		return -1;
	}
	fout.open("result.txt", ios::out);
	if (!fout.is_open()) {
		cout<<"���ļ�ʧ��"<<endl;
		fin.close();
		return -1;
	}
	cout << "��ʼ��ȡ����������result.txt" << endl;
	fin >> n>> MAX;
	random_list = new (nothrow)int[n];
	if (!random_list) {
		cout<<"�����ڴ�ʧ��"<<endl;
		return -1;
	}
    make_random_list(random_list, n, MAX);
	student* student_list = new (nothrow)student[MAX];
	if (!student_list) {
		cout<<"�����ڴ�ʧ��"<<endl;
		return -1;
	}
	for (int j = 0; j < MAX; j++) {
		fin >> student_list[j].no;
		fin >> temp;
		i = 0;
		while (temp[i] != '\0')
			i++;
		student_list[j].info = new (nothrow)char[i + 1];
		if (!student_list[j].info) {
			cout << "�����ڴ�ʧ��" << endl;
			return -1;
		}
		for (int k = 0; k < i; k++)
			student_list[j].info[k] = temp[k];
		student_list[j].info[i] = '\0';
		fin >> temp;
		i = 0;
		while (temp[i] != '\0')
			i++;
		student_list[j].school = new (nothrow)char[i + 1];
		if (!student_list[j].school) {
			cout << "�����ڴ�ʧ��" << endl;
			return -1;
		}
		for (int k = 0; k < i; k++)
			student_list[j].school[k] = temp[k];
		student_list[j].school[i] = '\0';
	}
	for(int i = 0;i<n;i++)
		fout <<student_list[random_list[i]].no<<" " << student_list[random_list[i]].info
		<< " " << student_list[random_list[i]].school << endl;
	for (int i = 0; i < MAX; i++) {
		delete student_list[i].info;
		delete student_list[i].school;
	}
	delete student_list;
	fin.close();
	return 0;
}//ʹ�������ռ���д洢����Ϊ��ȡ�Ĺ����д���ʹ��������� 