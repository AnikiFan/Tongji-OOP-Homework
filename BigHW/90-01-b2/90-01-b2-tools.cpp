/* 2254298 ��11 ���� */
#include"popstar.h"
/***************************************************************************
  �������ƣ�reload
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    �������س�������,��������Ϊһ������
***************************************************************************/
void reload(void)
{
	char input[100];
	int xcoo, ycoo;
	cct_getxy(xcoo, ycoo);
	cout << " ";
	cct_gotoxy(xcoo, ycoo);
	cct_showch(xcoo, ycoo, ' ', background, coverLength);
	cct_setcolor(defaultColor);
	cct_gotoxy(xcoo, ycoo);
	cout << "��С�������������End����...";
	//
	//cout << "*";
	//
	//cin.ignore(10000, '\n');

	while (1) {
		cin.getline(input, 99, '\n');
		if ((input[0] == 'E' || input[0] == 'e') &&
			(input[1] == 'N' || input[1] == 'n') &&
			(input[2] == 'D' || input[2] == 'd'))
			break;
		input[0] = 0;
		input[1] = 0;
		input[2] = 0;
		cout << "�����������������";
		//
//cout << "*";
//
		cct_getxy(xcoo, ycoo);
		cct_showch(28, ycoo - 1, ' ', background, 20);
		cct_setcolor(defaultColor);
		cct_gotoxy(28, ycoo - 1);
	}
	cct_cls();
	cct_setconsoleborder(boardwidth, boardheight, boardwidth, boardheight);
	//cct_setconsoleborder(80, 40, 80, 400);
	return;
}
void searchPlus(int srcRow, int srcCol, int matrix[][10], int rowMax, int colMax, int option, int x, int y, int rowInterval, int colInterval, int pivot)
{
	switch (option) {
		case 0://���κβ���
			break;
		case 1://������ʾ
			cct_showch(x + srcCol + srcCol * colInterval, y + srcRow + srcRow * rowInterval, pivot + '0', backgroundhighlight, 1);
			cct_setcolor(defaultColor);
			break;
		case 2://����������
			cct_showch(x + srcCol + srcCol * colInterval, y + srcRow + srcRow * rowInterval, '*', defaultColor, 1);
			break;
		case 3://�����ڶ�ӦԪ�����㲢������ʾ
			matrix[srcRow][srcCol] = 0;
			cct_showch(x + srcCol + srcCol * colInterval, y + srcRow + srcRow * rowInterval, '0', backgroundhighlight, 1);
			cct_setcolor(defaultColor);
			break;
		case 4://ͼ�λ�ѡ��
			delay;
			selectBlock(x + srcCol + srcCol * colInterval, y + srcRow + srcRow * rowInterval, matrix[srcRow][srcCol]);
			break;
		case 5://�ж��Ƿ�ʤ��
			break;
		case 6://ͼ�λ�ȡ��ѡ��;
			delay;
			reverseBlock(x + srcCol + srcCol * colInterval, y + srcRow + srcRow * rowInterval, matrix[srcRow][srcCol]);
			break;
		case 7://�������鲢�������ڲ���ӦԪ������
			delay;
			matrix[srcRow][srcCol] = 0;
			cancelBlock(x + srcCol + srcCol * colInterval, y + srcRow + srcRow * rowInterval);
			break;
	}
	return;
}
int search(int srcRow, int srcCol, int matrix[][10], int rowMax, int colMax, int option, int x, int y, int rowInterval, int colInterval, int pivotMatrix[][10], int& sum)//xyΪ��һ��Ԫ�ص�����
{//option==5ʱ���ж��Ƿ�Ϊ0
	int pivot = matrix[srcRow][srcCol];

	pivotMatrix[srcRow][srcCol] = 1;
	searchPlus(srcRow, srcCol, matrix, rowMax, colMax, option, x, y, rowInterval, colInterval, pivot);//�Ե�ǰԪ�ؽ��ж������
	if (option != 5 || (option == 5 && pivot != 0))
		sum++;
	else
		return(sum = -1);
	if (srcRow != 0 && matrix[srcRow - 1][srcCol] == pivot && pivotMatrix[srcRow - 1][srcCol] == 0)
		search(srcRow - 1, srcCol, matrix, rowMax, colMax, option, x, y, rowInterval, colInterval, pivotMatrix, sum);
	if (srcCol != 0 && matrix[srcRow][srcCol - 1] == pivot && pivotMatrix[srcRow][srcCol - 1] == 0)
		search(srcRow, srcCol - 1, matrix, rowMax, colMax, option, x, y, rowInterval, colInterval, pivotMatrix, sum);
	if (srcRow != rowMax - 1 && matrix[srcRow + 1][srcCol] == pivot && pivotMatrix[srcRow + 1][srcCol] == 0)
		search(srcRow + 1, srcCol, matrix, rowMax, colMax, option, x, y, rowInterval, colInterval, pivotMatrix, sum);
	if (srcCol != colMax - 1 && matrix[srcRow][srcCol + 1] == pivot && pivotMatrix[srcRow][srcCol + 1] == 0)
		search(srcRow, srcCol + 1, matrix, rowMax, colMax, option, x, y, rowInterval, colInterval, pivotMatrix, sum);
	return sum;
}

int victory(int matrix[][10], int rowMax, int colMax, int& total)
{
	int i, j, u, v, pivotMatrix[10][10] = { 0 }, sum = 0;
	total = 0;
	for (i = 0; i < rowMax; i++) {
		for (j = 0; j < colMax; j++) {
			sum = 0;
			search(i, j, matrix, rowMax, colMax, 5, 0, 0, 0, 0, pivotMatrix, sum);
			if (sum != 1 && sum != -1)
				return 0;
			for (u = 0; u < 10; u++)
				for (v = 0; v < 10; v++)
					pivotMatrix[u][v] = 0;
			if (sum != -1)
				total++;
		}
	}
	return 1;
}