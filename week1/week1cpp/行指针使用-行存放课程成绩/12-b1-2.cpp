/* 2254298 ������ ���� */
#include <iostream>
#include <iomanip>
using namespace std;

#define STUDENT_NUM	4
#define SCORE_NUM	5

/* --- ���������κ���ʽ��ȫ�ֱ��� --- */

/***************************************************************************
  �������ƣ�
  ��    �ܣ����һ�ſε�ƽ����
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void average(int(*score)[STUDENT_NUM])
{
	/* ����������䲿�֣�
	   1���������н������� 1���򵥱��� + 1��ָ����� */

	   /* ����ִ����䲿�֣�
		  1���������ٶ����κ����͵ı��������� for (int i=0;...������ʽ�������
		  2��ѭ������������ָ���������������в��������[]��ʽ��������
			 ������int a[10], i;
					 for(i=0; i<10; i++)
						 cout << a[i];
			 ����  ��int a[10], p;
					 for(p=a; p<a+10; p++)
						 cout << *p;          */
	double sum = 0;
	int* p = *score;
	for (; p - *score < STUDENT_NUM; p++)
		sum += *p;
	if (sum / STUDENT_NUM >= 10)
		cout << "��1�ſ�ƽ���֣�" << setprecision(4) << sum / STUDENT_NUM << endl << endl;
	else
		cout << "��1�ſ�ƽ���֣�" << setprecision(3) << sum / STUDENT_NUM << endl << endl;

	return;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ��ҳ����������Ͽγ̲������ѧ��
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void fail(int(*score)[STUDENT_NUM])
{
	/* ����������䲿�֣�
	   1���������н������� 3���򵥱��� + 1����ָ����� + 1����ָ����� */

	   /* ����ִ����䲿�֣�Ҫ��ͬaverage��*/
	double sum = 0;
	int failn, (*row)[STUDENT_NUM] = score, * p = *score, fail = 0;
	cout << "2�����ϲ������ѧ����" << endl;
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
			cout << "No��" << p - *score+1<<" ";
			for (row = score; row < score + SCORE_NUM; row++) {
				sum += *(*row + (p - *score));
				cout << *(*row + (p - *score)) << " ";
			}
			if (sum / SCORE_NUM >= 10)
				cout << "ƽ����" << setprecision(4) << sum / SCORE_NUM << endl;
			else
				cout << "ƽ����" << setprecision(3) << sum / SCORE_NUM << endl;
		}
	}
	cout << endl;
	return;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ��ҳ�ƽ���ɼ���90�����ϻ�ȫ���ɼ���85�����ϵ�ѧ��
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void good(int(*score)[STUDENT_NUM])
{
	/* ����������䲿�֣�
	   1���������н������� 3���򵥱��� + 1����ָ����� + 1����ָ����� */

	   /* ����ִ����䲿�֣�Ҫ��ͬaverage��*/
	double sum = 0;
	int(*row)[STUDENT_NUM] = score, * p = *score, good = 1;
	cout << "ƽ��90���ϻ�ȫ��85���ϵ�ѧ����"<<endl;
	for (; p < *score + STUDENT_NUM; p++) {
		sum = 0;
		good = 1;
		for (row = score; row < score + SCORE_NUM; row++) {
			if (*(*row + (p - *score)) < 85)
				good = 0;
			sum += *(*row + (p - *score));
		}
		if (good) {
			cout << "No��" << p - *score+1<<" ";
			for (row = score; row < score + SCORE_NUM; row++)
				cout << *(*row + (p - *score)) << " ";
			if (sum / SCORE_NUM >= 10)
				cout << "ƽ����" << setprecision(4) << sum / SCORE_NUM << endl;
			else
				cout << "ƽ����" << setprecision(3) << sum / SCORE_NUM << endl;
		}
		else if (sum / SCORE_NUM >= 90) {
			cout << "No��" << p - *score+1<<" ";
			for (row = score; row < score + SCORE_NUM; row++)
				cout << *(*row + (p - *score)) << " ";
			if (sum / SCORE_NUM >= 10)
				cout << "ƽ����" << setprecision(4) << sum / SCORE_NUM << endl;
			else
				cout << "ƽ����" << setprecision(3) << sum / SCORE_NUM << endl;
		}
	}
	return;
}



/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int main()
{
	int a[SCORE_NUM][STUDENT_NUM] = {
		{91,92,93,97},  //��1-4��ѧ���ĵ�1�ſγɼ�
		{81,82,83,85},  //��1-4��ѧ���ĵ�2�ſγɼ�
		{71,72,99,87},  //��1-4��ѧ���ĵ�3�ſγɼ�
		{61,32,80,91},  //��1-4��ѧ���ĵ�4�ſγɼ�
		{51,52,95,88} };//��1-4��ѧ���ĵ�5�ſγɼ�
	/* �������Ԥ�������⣬�������н������� 1����ָ����� + 1����ָ����� */

	/* ����ִ����䲿�֣�Ҫ��ͬaverage��*/
	cout << "��ʼ��Ϣ��" << endl;
	int(*row)[STUDENT_NUM] = a, * p;
	for (; row < a + SCORE_NUM; row++) {
		cout << "No.1-" << STUDENT_NUM << "ѧ���ĵ�" << row - a + 1 << "�ſεĳɼ���";
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
