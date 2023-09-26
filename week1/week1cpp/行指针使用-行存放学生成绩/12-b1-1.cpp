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
  ˵    ���������������ں����м���
***************************************************************************/
void average(int(*score)[SCORE_NUM])
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
	for (int(*row)[SCORE_NUM] = score; row < score + STUDENT_NUM; row++)
		sum += **row;
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
  ˵    ���������������ں����м���
***************************************************************************/
void fail(int(*score)[SCORE_NUM])
{
	/* ����������䲿�֣�
	   1���������н������� 2���򵥱��� + 1����ָ����� + 1����ָ����� */

	   /* ����ִ����䲿�֣�Ҫ��ͬaverage��*/
	cout << "2�����ϲ������ѧ����" << endl;
	int(*row)[SCORE_NUM] = score, * p, failn;
	double sum = 0;
	for (; row < score + STUDENT_NUM; row++) {
		failn = 0;
		sum = 0;
		for (p = *row; p < *row + SCORE_NUM; p++) {
			if (*p < 60)
				failn++;
			if (failn >= 2) {
				cout << "No��" << row - score + 1 << " ";
				for (p = *row; p < *row + SCORE_NUM; p++) {
					cout << *p << " ";
					sum += *p;
				}
				if (sum / SCORE_NUM >= 10)
					cout << "ƽ����" << setprecision(4) << sum / SCORE_NUM << endl;
				else
					cout << "ƽ����" << setprecision(3) << sum / SCORE_NUM << endl;
				break;
			}
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
void good(int(*score)[SCORE_NUM])
{
	/* ����������䲿�֣�
	   1���������н������� 2���򵥱��� + 1����ָ����� + 1����ָ����� */

	   /* ����ִ����䲿�֣�Ҫ��ͬaverage��*/
	cout << "ƽ��90���ϻ�ȫ��85���ϵ�ѧ����" << endl;
	int(*row)[SCORE_NUM] = score, * p, good = 1;
	double sum = 0;
	for (; row < score + STUDENT_NUM; row++) {
		sum = 0;
		good = 1;
		for (p = *row; p < *row + SCORE_NUM; p++) {
			if (*p < 85)
				good = 0;
			sum += *p;
		}
		if (good) {
			cout << "No��" << row - score + 1 << " ";
			for (p = *row; p < *row + SCORE_NUM; p++) {
				cout << *p << " ";
			}
			if (sum/SCORE_NUM>=10)
			cout << "ƽ����" << setprecision(4) << sum / SCORE_NUM << endl;
			else
				cout << "ƽ����" << setprecision(3) << sum / SCORE_NUM << endl;
		}
		else if (sum / SCORE_NUM >= 90) {
			cout << "No��" << row - score + 1 << " ";
			for (p = *row; p < *row + SCORE_NUM; p++) {
				cout << *p << " ";
			}
			if(sum/SCORE_NUM>=10)
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
	int a[STUDENT_NUM][SCORE_NUM] = {
		{91, 81, 71, 61, 51},	//��1��ѧ����1-5�ſεĳɼ�
		{92, 82, 72, 32, 52},   //��2��ѧ����1-5�ſεĳɼ�
		{93, 83, 99, 80, 95},   //��3��ѧ����1-5�ſεĳɼ�
		{97, 85, 87, 91, 88} }; //��4��ѧ����1-5�ſεĳɼ�

	/* �������Ԥ�������⣬�������н������� 1����ָ����� + 1����ָ����� */

	/* ����ִ����䲿�֣�Ҫ��ͬaverage��*/
// ��ӡ��ʼ��Ϣ
	int(*row)[SCORE_NUM] = a, * elem = *a;
	cout << "��ʼ��Ϣ��" << endl;
	for (; row < a + STUDENT_NUM; row++) {
		cout << "No." << row - a + 1 << "��1-" << SCORE_NUM << "�ſγɼ���";
		for (; elem < *row + SCORE_NUM; elem++)
			cout << *elem << " ";
		cout << endl;
	}
	cout << endl;

	//��ӡ��һ�ſε�ƽ���ɼ�
	average(a);

	//��ӡ�������ϲ������ѧ��
	fail(a);

	//��ӡƽ����90���ϻ�ȫ��85���ϵ�ѧ��
	good(a);

	return 0;
}