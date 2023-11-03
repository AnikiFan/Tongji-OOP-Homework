/* 2254298 ������ ���� */
#include<iostream>
#include<string.h>
using namespace std;
/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int usage(const char* const procname)
{
	cout << "Usage: " << procname << " Ҫ����ѧ��/all ƥ��ѧ��/all Դ������/all ���ƶȷ�ֵ(60-100) ���(filename/screen)" << endl << endl;
	cout << "e.g. : " << procname << " 2159999 2159998 all       80 screen" << endl;
	cout << "       " << procname << " 2159999 all     14-b1.cpp 75 result.txt" << endl;
	cout << "       " << procname << " all     all     14-b2.cpp 80 check.dat" << endl;
	cout << "       " << procname << " all     all     all       85 screen" << endl;

	return 0;
}
int check_name(const char* name, int obj) {//���ж�λ�������ж��Ƿ�Ϊ����
	if (strlen(name) != 7)
		if (!obj) {
			cout << "Ҫ����ѧ�Ų���7λ" << endl;
			return 0;
		}
		else {
			cout << "Ҫƥ���ѧ�Ų���7λ" << endl;
			return 0;
		}
	else
		for (int i = 0; i < 7; i++)
			if (name[i] < '0' || name[i]>'9') {
				if (!obj) {
					cout << "Ҫ����ѧ�Ų���7λ����" << endl;
					return 0;
				}
				else {
					cout << "Ҫƥ���ѧ�Ų���7λ����" << endl;
					return 0;
				}
			}
	return 1;
}
int main(int argc, char** argv)
{
	int para = 80;
	if (argc != 6) {
		usage(argv[0]);
		return 0;
	}
	if (!strcmp((const char*)argv[1], "all")) {//��һ��������all 
		if (strcmp("all",(const char *)argv[2])&&!check_name((const char*)argv[2], 1)) //���ڶ��������Բ���
			return 0;
		else if (strcmp((const char*)argv[2], "all")) {//�ǶԵ�
			cout << "���ѧ����all��ƥ��ѧ�ű�����all" << endl;//ѧ�Ŷ��ˣ���all��
			return 0;
		}
	}
else if (!check_name((const char*)argv[1], 0))//����һ�������Բ���
		return 0;
	else if (strcmp((const char*)argv[2], "all") && !check_name((const char*)argv[2], 1))//���ڶ��������Բ���
		return 0;
	else if (!strcmp((const char*)argv[1], (const char*)argv[2]) && strcmp((const char*)argv[1], "all")) {
		cout << "ƥ��ѧ����Ҫ���ѧ����ͬ" << endl;
		return 0;
	}
	//���ֲ���������
	if (strlen(argv[3]) > 32) {
		cout << "Դ�����ļ���������32�ֽ�" << endl;
		return 0;
	}
	if (strlen(argv[4]) == 2&&argv[4][0]>='0'&&argv[4][0]<='9'&&argv[4][1]>='0'&&argv[4][1]<='9') {
		para = 10 * (argv[4][0] - '0') + argv[4][1] - '0';
		if (para < 60 || para>100)
			para = 80;
	}
	if (strlen(argv[5]) > 32) {
		cout << "�������ļ���������32�ֽ�" << endl;
		return 0;
	}
	cout << "�������ͨ��" << endl;
	cout << "���ѧ�ţ�" << argv[1] << endl;
	cout << "ƥ��ѧ�ţ�" << argv[2] << endl;
	cout << "Դ�ļ�����" << argv[3] << endl;
	cout << "ƥ����ֵ��" << para << endl;
	cout << "���Ŀ�꣺" << argv[5] << endl;
	return 0;
}