/* 2254298 ��11 ���� */
#include"popstar.h"
/***************************************************************************
  �������ƣ�menu
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����������ѡ��������Լ�������������
***************************************************************************/
int menu(int* row, int* column)
{
	char input;
	srand((unsigned int)(time(0)));
	cout << "--------------------------------------------" << endl;
	cout << "A.�������ҳ����������ʶ" << endl;
	cout << "B.���������һ���������ֲ�����ʾ��" << endl;
	cout << "C.���������һ�أ��ֲ�����ʾ��" << endl;
	cout << "D.αͼ�ν����������ѡ��һ��ɫ�飨�޷ָ��ߣ�" << endl;
	cout << "E.αͼ�ν����������ѡ��һ��ɫ�飨�зָ��ߣ�" << endl;
	cout << "F.αͼ�ν������һ���������ֲ��裩" << endl;
	cout << "G.αͼ�ν���������" << endl;
	cout << "Q.�˳�" << endl;
	cout << "--------------------------------------------" << endl;
	cout << "[��ѡ��:] ";
	while (1) {
		input = _getch();
		if (input == 'a' || input == 'A' || input == 'b' || input == 'B' ||
			input == 'c' || input == 'C' || input == 'd' || input == 'D' ||
			input == 'e' || input == 'E' || input == 'f' || input == 'F' ||
			input == 'g' || input == 'G' || input == 'q' || input == 'Q') {
			cout << input;
			Sleep(200);
			break;
		}
	}
	switch (input) {
		case'A':
			input = 'a';
			break;
		case'B':
			input = 'b';
			break;
		case'C':
			input = 'c';
			break;
		case'D':
			input = 'd';
			break;
		case'E':
			input = 'e';
			break;
		case'F':
			input = 'f';
			break;
		case'G':
			input = 'g';
			break;
		case'Q':
			input = 'q';
			break;
		default:
			break;
	}
	if (input == 'q')
		return 'q';
	cct_cls();
	cout << "����������(8-10)��" << endl;
	while (1) {
		cin >> *row;
		if (*row >= 8 && *row <= 10 && !cin.rdstate())
			break;
		else if (cin.rdstate()) {
			cin.clear();
			cin.ignore(10000000, '\n');//ɾ������Ժ����ѭ��
		}
		cout << "����������(8-10)��" << endl;
	}
	cout << "����������(8-10)��" << endl;
	while (1) {
		cin >> *column;
		if (*column >= 8 && *column <= 10 && !cin.rdstate())
			break;
		else if (cin.rdstate()) {
			cin.clear();
			cin.ignore(10000000, '\n');//ɾ������Ժ����ѭ��
		}
		cout << "����������(8-10)��" << endl;
	}
	return input;
}
int main()
{
	char option;
	int rowMax, colMax, matrix[10][10], i, j;
	cct_setconsoleborder(boardwidth, boardheight, boardwidth, boardheight);
	cct_setfontsize("��������", 15);




	while (1) {
		option = menu(&rowMax, &colMax);
		for (i = 0; i < 10; i++)
			for (j = 0; j < 10; j++)
				matrix[i][j] = (rand() % 5) + 1;
		//matrix[i][j] =  1;
		//������
		//for (i = 0; i < 10; i++)
		//	for (j = 0; j < 10; j++)
		//		matrix[i][j] = j;
		//
		if (option == 'q')
			break;

		switch (option) {
			case 'a':
				module1(rowMax, colMax, matrix);
				break;
			case 'b':
				module2(rowMax, colMax, matrix);
				break;
			case 'c':
				module3(rowMax, colMax, matrix);
				break;
			case 'd':
				module4(rowMax, colMax, matrix);
				break;
			case 'e':
				module5(rowMax, colMax, matrix);
				break;
			case 'f':
				module6(rowMax, colMax, matrix);
				break;
			case 'g':
				module7(rowMax, colMax, matrix);
				break;
		}
		reload();
	}
	return 0;
}