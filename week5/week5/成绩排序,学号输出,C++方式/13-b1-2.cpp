/* 2254298 大数据 范潇 */
#include<iostream>
#include<fstream>
using namespace std;
struct student {
	int no;
	char name[9];
	int score;
	int rank;
};
void infocopy(student& dst, student src)
{
	dst.no = src.no;
	for(int i = 0;i<9;i++)
		dst.name[i] = src.name[i];
	dst.score = src.score;
	dst.rank = src.rank;
	return;
}
void infoswitch(student& a, student& b)
{
	student temp;
	infocopy(temp, a);
	infocopy(a, b);
	infocopy(b, temp);
	return;
}
//满足某一优先级的下标小，compare中，如果第一个参数优先级高，返回1，否则返回0
void sort(student* student_list, int list_length, int (*compare)(student, student))
{
	for (int i = 0; i < list_length-1; i++) {
		int k = i;
		for (int j = i + 1; j < list_length; j++) 
			if (compare(student_list[j], student_list[k]))
				k = j;
		infoswitch(student_list[i], student_list[k]);
	}
	return;
}
int  compare_by_score(student a, student b)
{
	return a.score > b.score;
}
int  compare_by_no(student a, student b)
{
	return a.no < b.no;
}
void assign_rank(student* student_list,int list_length)
{
	int rank = 0;
	for (int i = 0; i < list_length; i++)
	{
		if(i == 0)
			rank = 1;
		else if(student_list[i].score == student_list[i-1].score)
			rank = student_list[i-1].rank;
		else
			rank = i+1;
		student_list[i].rank = rank;
	}
	return;
}
int main()
{
	ifstream fin;
	fin.open("student.txt", ios::in);
	if (!fin.is_open()) {
		cout << "打开文件失败" << endl;
		return -1;
	}
	int n;
	fin >>n ;
	student* student_list = new (nothrow)student[n];
	if (!student_list)
	{
		cout << "内存分配失败" << endl;
		return -1;
	}
	for(int i = 0;i<n;i++)
		fin >> student_list[i].no >> student_list[i].name >> student_list[i].score;
	sort(student_list, n, compare_by_score);
	assign_rank(student_list, n);
	sort(student_list, n, compare_by_no);
	for(int i = 0;i<n;i++)
		cout << student_list[i].no << " " << student_list[i].name << " " << student_list[i].score<<" " << student_list[i].rank << endl;
	delete []student_list;
	fin.close();
	return 0;
}