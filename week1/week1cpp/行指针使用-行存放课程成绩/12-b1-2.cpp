/* 2254298 大数据 范潇 */
#include <iostream>
#include <iomanip>
using namespace std;

#define STUDENT_NUM	4
#define SCORE_NUM	5

/* --- 不允许定义任何形式的全局变量 --- */

/***************************************************************************
  函数名称：
  功    能：求第一门课的平均分
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void average(int(*score)[STUDENT_NUM])
{
	/* 函数定义语句部分：
	   1、本函数中仅允许定义 1个简单变量 + 1个指针变量 */

	   /* 函数执行语句部分：
		  1、不允许再定义任何类型的变量，包括 for (int i=0;...）等形式定义变量
		  2、循环变量必须是指针变量，后续语句中不允许出现[]形式访问数组
			 不允许：int a[10], i;
					 for(i=0; i<10; i++)
						 cout << a[i];
			 允许  ：int a[10], p;
					 for(p=a; p<a+10; p++)
						 cout << *p;          */
	double sum = 0;
	int* p = *score;
	for (; p - *score < STUDENT_NUM; p++)
		sum += *p;
	if (sum / STUDENT_NUM >= 10)
		cout << "第1门课平均分：" << setprecision(4) << sum / STUDENT_NUM << endl << endl;
	else
		cout << "第1门课平均分：" << setprecision(3) << sum / STUDENT_NUM << endl << endl;

	return;
}

/***************************************************************************
  函数名称：
  功    能：找出有两门以上课程不及格的学生
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void fail(int(*score)[STUDENT_NUM])
{
	/* 函数定义语句部分：
	   1、本函数中仅允许定义 3个简单变量 + 1个行指针变量 + 1个简单指针变量 */

	   /* 函数执行语句部分（要求同average）*/
	double sum = 0;
	int failn, (*row)[STUDENT_NUM] = score, * p = *score, fail = 0;
	cout << "2门以上不及格的学生：" << endl;
	for (; p < *score + STUDENT_NUM; p++) {
		failn = 0;
		fail = 0;
		for (row = score; row < score + SCORE_NUM; row++) {
			if (*(*row + (p - *score)) < 60)
				failn++;
			if (failn >= 2) {
				fail = 1;
				break;
			}
		}
		if (fail) {
			cout << "No：" << p - *score+1<<" ";
			for (row = score; row < score + SCORE_NUM; row++) {
				sum += *(*row + (p - *score));
				cout << *(*row + (p - *score)) << " ";
			}
			if (sum / SCORE_NUM >= 10)
				cout << "平均：" << setprecision(4) << sum / SCORE_NUM << endl;
			else
				cout << "平均：" << setprecision(3) << sum / SCORE_NUM << endl;
		}
	}
	cout << endl;
	return;
}

/***************************************************************************
  函数名称：
  功    能：找出平均成绩在90分以上或全部成绩在85分以上的学生
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void good(int(*score)[STUDENT_NUM])
{
	/* 函数定义语句部分：
	   1、本函数中仅允许定义 3个简单变量 + 1个行指针变量 + 1个简单指针变量 */

	   /* 函数执行语句部分（要求同average）*/
	double sum = 0;
	int(*row)[STUDENT_NUM] = score, * p = *score, good = 1;
	cout << "平均90以上或全部85以上的学生："<<endl;
	for (; p < *score + STUDENT_NUM; p++) {
		sum = 0;
		good = 1;
		for (row = score; row < score + SCORE_NUM; row++) {
			if (*(*row + (p - *score)) < 85)
				good = 0;
			sum += *(*row + (p - *score));
		}
		if (good) {
			cout << "No：" << p - *score+1<<" ";
			for (row = score; row < score + SCORE_NUM; row++)
				cout << *(*row + (p - *score)) << " ";
			if (sum / SCORE_NUM >= 10)
				cout << "平均：" << setprecision(4) << sum / SCORE_NUM << endl;
			else
				cout << "平均：" << setprecision(3) << sum / SCORE_NUM << endl;
		}
		else if (sum / SCORE_NUM >= 90) {
			cout << "No：" << p - *score+1<<" ";
			for (row = score; row < score + SCORE_NUM; row++)
				cout << *(*row + (p - *score)) << " ";
			if (sum / SCORE_NUM >= 10)
				cout << "平均：" << setprecision(4) << sum / SCORE_NUM << endl;
			else
				cout << "平均：" << setprecision(3) << sum / SCORE_NUM << endl;
		}
	}
	return;
}



/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int main()
{
	int a[SCORE_NUM][STUDENT_NUM] = {
		{91,92,93,97},  //第1-4个学生的第1门课成绩
		{81,82,83,85},  //第1-4个学生的第2门课成绩
		{71,72,99,87},  //第1-4个学生的第3门课成绩
		{61,32,80,91},  //第1-4个学生的第4门课成绩
		{51,52,95,88} };//第1-4个学生的第5门课成绩
	/* 除上面的预置数组外，本函数中仅允许定义 1个行指针变量 + 1个简单指针变量 */

	/* 函数执行语句部分（要求同average）*/
	cout << "初始信息：" << endl;
	int(*row)[STUDENT_NUM] = a, * p;
	for (; row < a + SCORE_NUM; row++) {
		cout << "No.1-" << STUDENT_NUM << "学生的第" << row - a + 1 << "门课的成绩：";
		for (p = *row; p < *row + STUDENT_NUM; p++)
			cout << *p << " ";
		cout << endl;
	}
	cout << endl;

	average(a);

	fail(a);

	good(a);

	return 0;
}
