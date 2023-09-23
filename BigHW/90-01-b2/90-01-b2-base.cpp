/* 2254298 ��11 ���� */
#include"popstar.h"
void matrixGenerator(int matrix[][10], int rowInterval, int colInterval, int rowMax, int colMax, int srcxcoo, int srcycoo, bool zeroHighlight)//��ʼ����Ϊ(1,1)Ԫλ��,Ԫ������пո�
{
	int i, j, x, y;
	cct_gotoxy(srcxcoo, srcycoo);
	cout << setfill(' ');
	for (i = 0; i < rowMax; i++) {
		for (j = 0; j < colMax; j++)
			if (!zeroHighlight || (zeroHighlight && matrix[i][j] != 0))
				cout << setw(colInterval + 1) << setiosflags(ios::left) << matrix[i][j];
			else {
				cct_getxy(x, y);
				cct_showch(x, y, '0', backgroundhighlight, 1);
				cct_setcolor(defaultColor);
				cout << setw(colInterval) << " ";
			}
		if (i != rowMax - 1)
			cct_gotoxy(srcxcoo, srcycoo + i * rowInterval + i + 1);
	}
	cout << endl;
	return;
}
void zeroMoving(int matrix[][10], int rowMax, int colMax)
{
	int i, j;
	bool horizontalMoveFinish, verticalMoveFinish;
	while (1) {
		verticalMoveFinish = true;
		for (j = 0; j < colMax; j++) {
			for (i = rowMax - 1; i > 0; i--) {
				if (matrix[i - 1][j] != 0 && matrix[i][j] == 0) {
					matrix[i][j] = matrix[i - 1][j];
					matrix[i - 1][j] = 0;
					verticalMoveFinish = false;
				}
			}
		}
		if (verticalMoveFinish)
			break;
	}
	while (1) {
		horizontalMoveFinish = true;
		for (j = 0; j < colMax - 1; j++)
			if (matrix[rowMax - 1][j] == 0 && matrix[rowMax - 1][j + 1] != 0) {
				horizontalMoveFinish = false;
				for (i = 0; i < rowMax; i++) {
					matrix[i][j] = matrix[i][j + 1];
					matrix[i][j + 1] = 0;
				}
			}
		if (horizontalMoveFinish)
			break;
	}
	return;
}
void matrixInitialize(int rowMax, int colMax, int matrix[][10], bool zeroHighlight)
{
	int i, x, y, X, Y;
	cout << "  |";
	for (i = 0; i < colMax; i++)
		cout << setiosflags(ios::right) << setw(3) << i << resetiosflags(ios::right);
	cout << endl;
	cout << setw(4 + 3 * colMax) << setfill('-') << "-" << endl;
	//
	//Sleep(1000);
	cct_getxy(x, y);
	for (i = 0; i < rowMax; i++) {
		cout << (char)('A' + i) << " | ";
		if (i != rowMax - 1)
			cout << endl;
	}
	cct_getxy(X, Y);
	//matrixGenerator(matrix, 0, 2, rowMax, colMax, x + 5, y,zeroHighlight);
	matrixGenerator(matrix, 0, 2, rowMax, colMax, X + 1, Y - rowMax + 1, zeroHighlight);
}
void getCoordinate(int& row, int& col, int rowMax, int colMax)
{
	int x, y;
	char input[100];
	cout << "������ĸ+������ʽ[����c2]����������꣺";
	cout << endl;
	cct_getxy(x, y);
	cct_gotoxy(39, y - 1);
	cct_getxy(x, y);
	while (1) {
		cin.getline(input, 99);
		if ((input[0] >= 'a' && input[0] <= ('a' + rowMax - 1) || input[0] >= 'A' && input[0] <= ('A' + rowMax - 1)) && (input[1] >= '0' && input[1] <= '0' + colMax - 1)) {
			if (input[0] >= 'A' && input[0] <= ('A' + rowMax - 1))
				row = input[0] - 'A';
			else
				row = input[0] - 'a';
			col = input[1] - '0';
			break;
		}
		cct_gotoxy(0, y + 1);
		cout << "�����������������.";
		cct_showch(x, y, ' ', background, 30);
		cct_setcolor(defaultColor);
		cct_gotoxy(x, y);
		input[0] = '\0';
		input[1] = '\0';
	}
	return;
}

void module1(int rowMax, int colMax, int matrix[][10])
{
	int row, col, x, y, sum = 0, pivotMatrix[10][10] = { 0 }, i, j, X, Y;
	cin.ignore(1000, '\n');
	cout << endl;
	cout << "��ǰ����:" << endl;
	cct_getxy(x, y);
	matrixInitialize(rowMax, colMax, matrix, false);
	while (1) {
		for (i = 0; i < 10; i++)
			for (j = 0; j < 10; j++)
				pivotMatrix[i][j] = 0;
		cout << endl;
		getCoordinate(row, col, rowMax, colMax);
		cout << "����Ϊ" << (char)(row + 'A') << "��" << col << "��" << endl;
		sum = search(row, col, matrix, rowMax, colMax, 0, x + 5, y + 2, 0, 2, pivotMatrix, sum);
		if (sum == 1) {
			sum = 0;
			cout << "����ľ�������λ�ô���������ֵͬ������������" << endl;
		}
		else {
			cout << endl << "���ҽ������:" << endl;
			//cct_getxy(x, y);
			//
			//Sleep(1000);
			//cct_gotoxy(x, y + rowMax + 1);
			//Sleep(1000);
			//cct_gotoxy(x, y);
			////
			matrixInitialize(rowMax, colMax, pivotMatrix, false);
			for (i = 0; i < 10; i++)
				for (j = 0; j < 10; j++)
					pivotMatrix[i][j] = 0;
			//search(row, col, matrix, rowMax, colMax, 2, x + 5, y + 2, 0, 2, pivotMatrix, sum);
			//cct_gotoxy(x, y + rowMax + 1);
			cct_getxy(X, Y);
			search(row, col, matrix, rowMax, colMax, 2, 5, Y - rowMax, 0, 2, pivotMatrix, sum);
			cct_gotoxy(X, Y);
			cout << endl << endl << "��ǰ����(��ͬɫ��ʶ)" << endl;
			for (i = 0; i < 10; i++)
				for (j = 0; j < 10; j++)
					pivotMatrix[i][j] = 0;
			cct_getxy(x, y);
			////
			//for (int k = 0; k < rowMax + 3; k++)
			//	cout << endl;
			//cct_gotoxy(x, y - rowMax - 3);
			////
			matrixInitialize(rowMax, colMax, matrix, false);
			cct_getxy(X, Y);
			//search(row, col, matrix, rowMax, colMax, 1, x + 5, y + 2, 0, 2, pivotMatrix, sum);
			search(row, col, matrix, rowMax, colMax, 1, 5, Y - rowMax, 0, 2, pivotMatrix, sum);
			cct_gotoxy(X, Y);
			//cct_gotoxy(0, boardheight - 2);
			cout << endl;
			//cct_gotoxy(x, y + rowMax + 3);
			break;
		}
	}
	//	cout << sum;
	return;
}
void module2(int rowMax, int colMax, int matrix[][10])
{
	int row, col, x, y, sum = 0, pivotMatrix[10][10] = { 0 }, i, j, X, Y;
	char input;
	cin.ignore(1000, '\n');
	cout << endl;
	cout << "��ǰ����:" << endl;
	cct_getxy(x, y);
	matrixInitialize(rowMax, colMax, matrix, false);
	while (1) {
		for (i = 0; i < 10; i++)
			for (j = 0; j < 10; j++)
				pivotMatrix[i][j] = 0;
		cout << endl;
		getCoordinate(row, col, rowMax, colMax);
		cout << "����Ϊ" << (char)(row + 'A') << "��" << col << "��" << endl;
		sum = search(row, col, matrix, rowMax, colMax, 0, x + 5, y + 2, 0, 2, pivotMatrix, sum);
		if (sum == 1) {
			sum = 0;
			cout << "����ľ�������λ�ô���������ֵͬ������������" << endl;
		}
		else {
			cout << endl << "���ҽ������:" << endl;
			//cct_getxy(x, y);
			matrixInitialize(rowMax, colMax, pivotMatrix, false);
			for (i = 0; i < 10; i++)
				for (j = 0; j < 10; j++)
					pivotMatrix[i][j] = 0;
			//search(row, col, matrix, rowMax, colMax, 2, x + 5, y + 2, 0, 2, pivotMatrix, sum);
			//cct_gotoxy(x, y + rowMax + 1);
			cct_getxy(X, Y);
			search(row, col, matrix, rowMax, colMax, 2, 5, Y - rowMax, 0, 2, pivotMatrix, sum);
			cct_gotoxy(X, Y);
			cout << endl << endl << endl << "��ǰ����(��ͬɫ��ʶ)" << endl;
			for (i = 0; i < 10; i++)
				for (j = 0; j < 10; j++)
					pivotMatrix[i][j] = 0;
			cct_getxy(x, y);
			matrixInitialize(rowMax, colMax, matrix, false);
			cct_getxy(X, Y);
			//
			//cout << "*";
			search(row, col, matrix, rowMax, colMax, 1, 5, Y - rowMax, 0, 2, pivotMatrix, sum);
			//cct_gotoxy(x, y + rowMax + 3);
			//cct_gotoxy(0, boardheight - 2);
			cct_gotoxy(X, Y);
			cout << endl;
			//֮ǰ������module1��ͬ
			cout << "��ȷ���Ƿ��" << (char)(row + 'A') << col << "����Χ����ֵͬ����(Y/N/Q)��";
			cct_getxy(x, y);
			while (1) {
				input = _getch();
				cout << input;
				if (input == 'y' || input == 'n' || input == 'q' || input == 'Y' || input == 'N' || input == 'Q')
					break;
				cct_gotoxy(x, y);
			}
			switch (input) {
				default:
					break;
				case'y':
					input = 'Y';
					break;
				case'n':
					input = 'N';
					break;
				case'q':
					input = 'Q';
					break;
			}
			if (input == 'Y') {
				cout << endl;
				cout << endl << "��ֵͬ�鲢�������(��ͬɫ��ʶ):" << endl;
				cct_getxy(x, y);
				for (i = 0; i < 10; i++)
					for (j = 0; j < 10; j++)
						pivotMatrix[i][j] = 0;
				matrixInitialize(rowMax, colMax, matrix, false);
				//
				//cout << "*";
				sum = 0;
				cct_getxy(X, Y);
				//search(row, col, matrix, rowMax, colMax, 3, x + 5, y + 2, 0, 2, pivotMatrix, sum);
				search(row, col, matrix, rowMax, colMax, 3, 5, Y - rowMax, 0, 2, pivotMatrix, sum);
				//cct_gotoxy(x, y + rowMax + 3);
				//cct_gotoxy(0, boardheight - 2);
				cct_gotoxy(X, Y);
				cout << endl;
				cout << "���ε÷�: " << sum * sum * 5 << " �ܵ÷�: " << sum * sum * 5 << endl;
				cout << endl << "���س������������������...";
				while (_getch() != 13)
					;
				cout << endl;
				cout << "����������:" << endl;
				zeroMoving(matrix, rowMax, colMax);
				//cct_getxy(x, y);
				matrixInitialize(rowMax, colMax, matrix, true);
				//cct_gotoxy(x, y + rowMax + 4);
				cct_gotoxy(0, boardheight - 1);
				cout << endl;
			}
			else
				cout << endl;
			break;
		}
	}
	return;
}
void module3(int rowMax, int colMax, int matrix[][10])
{
	int row, col, x, y, sum = 0, pivotMatrix[10][10] = { 0 }, i, j, score = 0, remainder = 0, X, Y;
	char input;
	cout << endl;
	cin.ignore(1000, '\n');
	while (1) {
		cout << "��ǰ����:" << endl;
		cct_getxy(x, y);
		matrixInitialize(rowMax, colMax, matrix, true);
		while (1) {
			cout << endl;
			getCoordinate(row, col, rowMax, colMax);
			cout << "����Ϊ" << (char)(row + 'A') << "��" << col << "��" << endl;
			for (i = 0; i < 10; i++)
				for (j = 0; j < 10; j++)
					pivotMatrix[i][j] = 0;
			sum = 0;
			//
			//cout << "*";
			sum = search(row, col, matrix, rowMax, colMax, 5, x + 5, y + 2, 0, 2, pivotMatrix, sum);
			//sum = search(row, col, matrix, rowMax, colMax, 5, 0, 0, 0, 2, pivotMatrix, sum);
			if (sum == 1) {
				sum = 0;
				cout << "����ľ�������λ�ô���������ֵͬ������������" << endl;
			}
			else if (sum == -1) {
				sum = 0;
				cout << "����ľ�������λ��Ϊ0���Ƿ�λ�ã�������������";
			}
			else {
				for (i = 0; i < 10; i++)
					for (j = 0; j < 10; j++)
						pivotMatrix[i][j] = 0;
				cout << endl << "���ҽ������:" << endl;
				//cct_getxy(x, y);
				matrixInitialize(rowMax, colMax, pivotMatrix, false);
				for (i = 0; i < 10; i++)
					for (j = 0; j < 10; j++)
						pivotMatrix[i][j] = 0;
				//
				//cout << "*";
				//search(row, col, matrix, rowMax, colMax, 2, x + 5, y + 2, 0, 2, pivotMatrix, sum);
				cct_getxy(X, Y);
				search(row, col, matrix, rowMax, colMax, 2, 5, Y - rowMax, 0, 2, pivotMatrix, sum);
				cct_gotoxy(X, Y);
				cout << endl << endl << "��ǰ����(��ͬɫ��ʶ)" << endl;
				for (i = 0; i < 10; i++)
					for (j = 0; j < 10; j++)
						pivotMatrix[i][j] = 0;
				cct_getxy(x, y);
				matrixInitialize(rowMax, colMax, matrix, false);
				//
				cct_getxy(X, Y);
				//cout << "*";
				search(row, col, matrix, rowMax, colMax, 1, 5, Y - rowMax, 0, 2, pivotMatrix, sum);
				cct_gotoxy(X, Y);
				cout << endl;
				cout << "��ȷ���Ƿ��" << (char)(row + 'A') << col << "����Χ����ֵͬ����(Y/N/Q)��";
				cct_getxy(x, y);
				while (1) {
					input = _getch();
					cout << input;
					if (input == 'y' || input == 'n' || input == 'q' || input == 'Y' || input == 'N' || input == 'Q')
						break;
					cct_gotoxy(x, y);
				}
				switch (input) {
					default:
						break;
					case'y':
						input = 'Y';
						break;
					case'n':
						input = 'N';
						break;
					case'q':
						input = 'Q';
						break;
				}
				if (input == 'Y') {
					cout << endl;
					cout << endl << "��ֵͬ�鲢�������(��ͬɫ��ʶ)��" << endl;
					cct_getxy(x, y);
					for (i = 0; i < 10; i++)
						for (j = 0; j < 10; j++)
							pivotMatrix[i][j] = 0;
					matrixInitialize(rowMax, colMax, matrix, false);
					sum = 0;
					//
					//cout << "*";
					cct_getxy(X, Y);
					search(row, col, matrix, rowMax, colMax, 3, 5, Y - rowMax, 0, 2, pivotMatrix, sum);
					cct_gotoxy(X, Y);
					score += sum * sum * 5;
					cout << endl;
					cout << "���ε÷�: " << sum * sum * 5 << " �ܵ÷�: " << score << endl;
					cout << endl << "���س������������������...";
					while (_getch() != 13)
						;
					cout << endl;
					cout << "����������:" << endl;
					zeroMoving(matrix, rowMax, colMax);
					//cct_getxy(x, y);
					matrixInitialize(rowMax, colMax, matrix, true);
					//cout << "*";
					cout << endl << "�����������������س���������һ�ε�����..." << endl;
					while (_getch() != 13)
						;
					cout << endl;
					break;
				}
				else if (input == 'N') {
					cout << endl;
					cout << endl << "��ǰ����" << endl;
					for (i = 0; i < 10; i++)
						for (j = 0; j < 10; j++)
							pivotMatrix[i][j] = 0;
					//cct_getxy(x, y);
					matrixInitialize(rowMax, colMax, matrix, true);
					//cout << "*";
					//cct_gotoxy(x, y + rowMax + 2);
				}
				else
					break;
			}
		}
		if (input == 'Q') {
			cout << endl;
			break;
		}
		else if (victory(matrix, rowMax, colMax, remainder)) {
			cct_setcolor(14, 4);
			cout << "ʣ��" << remainder << "������������,���ؽ���!";
			cct_setcolor(defaultColor);
			cout << endl;
			break;
		}

	}
	return;
}