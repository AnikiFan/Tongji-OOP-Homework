/* 2254298 ������ ���� */
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <time.h>
/* �������Ҫ���˴��������ͷ�ļ� */

using namespace std;

/* �����峣����/�궨�壬����������ȫ�ֱ��� */

/* ��������Լ���Ҫ�ĺ��� */
//deck��Ϊ1˵���Ѿ����ߣ�player��Ϊ1˵����
void addnew(unsigned long long& deck, unsigned long long& player)
{
	while (1) {
		int pos = rand() % 54;
		if ((deck >> pos) % 2)
			continue;
		deck |= (1ULL << pos);
		player |= (1ULL << pos);
		break;
	}
	return;
}
void showcard(int i) {
			if (i == 53)
				cout << "RJ ";
			else if (i == 52)
				cout << "BJ ";
			else {
				int suit = i % 4;
				int pt = i / 4;
#if (__Linux__)
				switch (suit) {
					case 0: 
						cout << "C";
						break;
					case 1:
						cout << "D";
						break;
					case 2:
						cout << "H";
						break;
					case 3:
						cout << "S";
						break;
				}
#else
				switch (suit) {
					case 0:
						cout << '\5';
						break;
					case 1:
						cout << '\4';
						break;
					case 2:
						cout << '\3';
						break;
					case 3:
						cout << '\6';
						break;
				}
#endif
				switch (pt) {
					case 11:
						cout << "A";
						break;
					case 7:
						cout << "T";
						break;
					default:
						cout << pt+3;
						break;
					case 8:
						cout << "J";
						break;
					case 9:
						cout << "Q";
						break;
					case 10:
						cout << "K";
						break;
					case 12:
						cout << 2;
						break;
				}
				cout << ' ';
			}
	return;
}
void display(unsigned long long player)
{
	for(int i = 0;i<54;i++)
		if ((player >> i) % 2) 
			showcard(i);
	return;
}
/***************************************************************************
  �������ƣ�
  ��    �ܣ���ӡĳ����ҵ�������Ϣ������ǵ���������ӱ��
  ���������
  �� �� ֵ��
  ˵    ����
 ***************************************************************************/
int print(const char* prompt, const bool landlord, const unsigned long long player)
{
	/* ֻ�����岻���������������͵ļ򵥱��������ܶ�������������ṹ�塢string�� */
	cout << prompt;
	display(player);
	if (landlord)
		cout << "(����)";
	cout << endl;
	return 0;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ����ƣ����������������
  ���������
  �� �� ֵ��
  ˵    ����
 ***************************************************************************/
int deal(unsigned long long* player)
{
	/* ֻ�����岻����ʮ���������͵ļ򵥱��������ܶ�������������ṹ�塢string�� */
	int landlord;
	srand((unsigned)time(0));
	unsigned long long deck = 0;
	for (int i = 1; i <= 17; i++) {
		cout << "��" << i << "�ֽ�����" << endl;
		cout << "�׵��ƣ�";
		addnew(deck, player[0]);
		display(player[0]);
		cout << endl<<"�ҵ��ƣ�";
		addnew(deck, player[1]);
		display(player[1]);
		cout <<endl<< "�����ƣ�";
		addnew(deck, player[2]);
		display(player[2]);
		cout << endl;
		cout << endl;
	}
		cout << "��ѡ��һ������[0-2]��"<<endl;
		cin >> landlord;
		for (int pos = 0; pos < 54; pos++) {
			if ((deck >> pos) % 2)
				continue;
			deck |= (1ULL << pos);
			player[landlord] |= (1ULL << pos);
		}
	return landlord; //�˴��޸�Ϊѡ���ĵ���(0-2)
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����main��������׼�޸�
 ***************************************************************************/
int main()
{
	unsigned long long player[3] = { 0 }; //���������ҵķ�����Ϣ
	int landlord; //����0-2��ʾ�ĸ�����ǵ���

	cout << "���س�����ʼ����";
	while (getchar() != '\n')
		;

	landlord = deal(player);
	print("�׵��ƣ�", (landlord == 0), player[0]);
	print("�ҵ��ƣ�", (landlord == 1), player[1]);
	print("�����ƣ�", (landlord == 2), player[2]);

	return 0;
}
