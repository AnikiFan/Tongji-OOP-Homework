/* 2254298 信11 范潇 */
#include"popstar.h"
void matrixGenerator(int matrix[][10], int rowInterval, int colInterval, int rowMax, int colMax, int srcxcoo, int srcycoo, bool zeroHighlight)//起始坐标为(1,1)元位置,元素左侧有空格
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
	cout << "请以字母+数字形式[例：c2]输入矩阵坐标：";
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
		cout << "输入错误，请重新输入.";
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
	cout << "当前数组:" << endl;
	cct_getxy(x, y);
	matrixInitialize(rowMax, colMax, matrix, false);
	while (1) {
		for (i = 0; i < 10; i++)
			for (j = 0; j < 10; j++)
				pivotMatrix[i][j] = 0;
		cout << endl;
		getCoordinate(row, col, rowMax, colMax);
		cout << "输入为" << (char)(row + 'A') << "行" << col << "列" << endl;
		sum = search(row, col, matrix, rowMax, colMax, 0, x + 5, y + 2, 0, 2, pivotMatrix, sum);
		if (sum == 1) {
			sum = 0;
			cout << "输入的矩阵坐标位置处无连续相同值，请重新输入" << endl;
		}
		else {
			cout << endl << "查找结果数组:" << endl;
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
			cout << endl << endl << "当前数组(不同色标识)" << endl;
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
	cout << "当前数组:" << endl;
	cct_getxy(x, y);
	matrixInitialize(rowMax, colMax, matrix, false);
	while (1) {
		for (i = 0; i < 10; i++)
			for (j = 0; j < 10; j++)
				pivotMatrix[i][j] = 0;
		cout << endl;
		getCoordinate(row, col, rowMax, colMax);
		cout << "输入为" << (char)(row + 'A') << "行" << col << "列" << endl;
		sum = search(row, col, matrix, rowMax, colMax, 0, x + 5, y + 2, 0, 2, pivotMatrix, sum);
		if (sum == 1) {
			sum = 0;
			cout << "输入的矩阵坐标位置处无连续相同值，请重新输入" << endl;
		}
		else {
			cout << endl << "查找结果数组:" << endl;
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
			cout << endl << endl << endl << "当前数组(不同色标识)" << endl;
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
			//之前部分与module1相同
			cout << "请确认是否把" << (char)(row + 'A') << col << "及周围的相同值消除(Y/N/Q)：";
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
				cout << endl << "相同值归并后的数组(不同色标识):" << endl;
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
				cout << "本次得分: " << sum * sum * 5 << " 总得分: " << sum * sum * 5 << endl;
				cout << endl << "按回车键进行数组下落操作...";
				while (_getch() != 13)
					;
				cout << endl;
				cout << "下落后的数组:" << endl;
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
		cout << "当前数组:" << endl;
		cct_getxy(x, y);
		matrixInitialize(rowMax, colMax, matrix, true);
		while (1) {
			cout << endl;
			getCoordinate(row, col, rowMax, colMax);
			cout << "输入为" << (char)(row + 'A') << "行" << col << "列" << endl;
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
				cout << "输入的矩阵坐标位置处无连续相同值，请重新输入" << endl;
			}
			else if (sum == -1) {
				sum = 0;
				cout << "输入的矩阵坐标位置为0（非法位置），请重新输入";
			}
			else {
				for (i = 0; i < 10; i++)
					for (j = 0; j < 10; j++)
						pivotMatrix[i][j] = 0;
				cout << endl << "查找结果数组:" << endl;
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
				cout << endl << endl << "当前数组(不同色标识)" << endl;
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
				cout << "请确认是否把" << (char)(row + 'A') << col << "及周围的相同值消除(Y/N/Q)：";
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
					cout << endl << "相同值归并后的数组(不同色标识)：" << endl;
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
					cout << "本次得分: " << sum * sum * 5 << " 总得分: " << score << endl;
					cout << endl << "按回车键进行数组下落操作...";
					while (_getch() != 13)
						;
					cout << endl;
					cout << "下落后的数组:" << endl;
					zeroMoving(matrix, rowMax, colMax);
					//cct_getxy(x, y);
					matrixInitialize(rowMax, colMax, matrix, true);
					//cout << "*";
					cout << endl << "本次消除结束，按回车键继续新一次的消除..." << endl;
					while (_getch() != 13)
						;
					cout << endl;
					break;
				}
				else if (input == 'N') {
					cout << endl;
					cout << endl << "当前数组" << endl;
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
			cout << "剩余" << remainder << "个不可消除项,本关结束!";
			cct_setcolor(defaultColor);
			cout << endl;
			break;
		}

	}
	return;
}