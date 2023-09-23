/* 2254298 信11 范潇 */
#include"popstar.h"
void blockGenrator(int x, int y, int colorCode)
{//xy是星星的坐标
	int color[10][2] = colorBoard, i, j;
	cct_gotoxy(x - 2, y - 1);

	cct_setcolor(color[colorCode][0], color[colorCode][1]);
	for (i = 0; i < blockheight; i++) {
		for (j = 0; j < blockwidth; j++)
			cout << " ";
		cct_gotoxy(x - 2, y + i);
	}

	cct_gotoxy(x - 2, y - 1);
	cct_setcolor(color[colorCode][0], 0);
	cct_getxy(x, y);
	cout << "╔═╗" << endl;
	cct_gotoxy(x, y + 1);
	cout << "║  ║" << endl;
	cct_gotoxy(x, y + 2);
	cout << "╚═╝" << endl;
	cct_gotoxy(x + 2, y + 1);
	cct_setcolor(color[colorCode][0], 0);
	//cout << colorCode;
	cout << "★";
}
void inverseBlock(int x, int y, int colorCode)
{
	int color[10][2] = colorBoard;
	if (colorCode) {
		cct_setcolor(color[colorCode][0], 15);
		cct_gotoxy(x - 2, y - 1);
		cct_getxy(x, y);
		cout << "╔═╗" << endl;
		cct_gotoxy(x, y + 1);
		cout << "║  ║" << endl;
		cct_gotoxy(x, y + 2);
		cout << "╚═╝" << endl;
		cct_gotoxy(x + 2, y + 1);
		cout << "★";
		cct_setcolor(defaultColor);
	}
	return;
}
void reverseBlock(int x, int y, int colorCode)
{
	int color[10][2] = colorBoard;
	if (colorCode) {
		cct_setcolor(color[colorCode][0], 0);
		cct_gotoxy(x - 2, y - 1);
		cct_getxy(x, y);
		cout << "╔═╗" << endl;
		cct_gotoxy(x, y + 1);
		cout << "║  ║" << endl;
		cct_gotoxy(x, y + 2);
		cout << "╚═╝" << endl;
		cct_gotoxy(x + 2, y + 1);
		cout << "★";
		cct_setcolor(defaultColor);
	}
	return;
}
void selectBlock(int x, int y, int colorCode)
{
	int color[10][2] = colorBoard;
	if (colorCode) {
		cct_setcolor(color[colorCode][0], 7);
		cct_gotoxy(x - 2, y - 1);
		cct_getxy(x, y);
		cout << "╔═╗" << endl;
		cct_gotoxy(x, y + 1);
		cout << "║  ║" << endl;
		cct_gotoxy(x, y + 2);
		cout << "╚═╝" << endl;
		cct_gotoxy(x + 2, y + 1);
		cout << "★";
		cct_setcolor(defaultColor);
	}
	return;
}
void cancelBlock(int x, int y)
{
	int color[10][2] = colorBoard;
	cct_setcolor(15, 15);
	cct_gotoxy(x - 2, y - 1);
	cct_getxy(x, y);
	cout << "      " << endl;
	cct_gotoxy(x, y + 1);
	cout << "      " << endl;
	cct_gotoxy(x, y + 2);
	cout << "      " << endl;
	cct_setcolor(defaultColor);
	return;
}
void zeroMoving(int matrix[][10], int rowMax, int colMax, bool frame)
{
	int i, j, k, t;
	bool horizontalMoveFinish, verticalMoveFinish;
	//测试用
//cct_setconsoleborder(80, 80, 800, 100);
//
//for (i = 0; i < rowMax; i++) {
//	for (j = 0; j < colMax; j++)
//		cout << matrix[i][j] << " ";
//	cout << endl;
//}
//system("pause");
////
// 
	while (1) {
		verticalMoveFinish = true;
		for (j = 0; j < colMax; j++) {
			for (i = rowMax - 1; i > 0; i--) {
				if (matrix[i - 1][j] != 0 && matrix[i][j] == 0) {
					for (k = 4 + (i - 1) * (blockheight + frame); k < 4 + i * (blockheight + frame); k++) {
						//cancelBlock(6 + j * (blockwidth + 2 * frame), k);
						////system("pause");
						//delay;
						blockGenrator(6 + j * (blockwidth + 2 * frame), k + 1, matrix[i - 1][j]);
						//system("pause");
						delay;
						cct_showch(6 + j * (blockwidth + 2 * frame) - 2, k - 1, ' ', 15, 15, blockwidth);
						delay;
					}
					if (frame) {
						cct_setcolor(inverseColor);
						for (t = 6 + j * (blockwidth + 2 * frame) - 2; t <= 6 + j * (blockwidth + 2 * frame) + 3; t++) {
							cct_gotoxy(t, 4 + i * (blockheight + frame) - 2);
							cout << "═";
							t++;
						}
						cct_setcolor(defaultColor);
					}
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

					for (k = 6 + (j + 1) * (blockwidth + 2 * frame) - 1; k > 6 + j * (blockwidth + 2 * frame) - 1; k--) {
						if (matrix[i][j + 1] == 0)
							break;
						int r;

						//cancelBlock(k + 1, 4 + i * (blockheight + frame));
						////system("pause");
						//delay;

						blockGenrator(k, 4 + i * (blockheight + frame), matrix[i][j + 1]);
						//system("pause");
						delay;
						for (r = 4 + i * (blockheight + frame); r < 4 + i * (blockheight + frame) + blockheight; r++)

							cct_showch(k + 4, r - 1, ' ', 15, 15, 1);
						delay;
					}
					matrix[i][j] = matrix[i][j + 1];
					matrix[i][j + 1] = 0;
					if (frame) {
						cct_setcolor(inverseColor);
						for (t = 4 + i * (blockheight + frame) - 1; t <= 4 + i * (blockheight + frame) + 1; t++) {
							cct_gotoxy(6 + (j + 1) * (blockwidth + 2 * frame) - 4, t);
							cout << "║";
						}
						cct_setcolor(defaultColor);
					}
				}

			}
		if (horizontalMoveFinish)
			break;
	}
	return;
}
int whetherMove(int matrix[][10], int rowMax, int colMax)
{
	int i, j;
	for (j = 0; j < colMax; j++)
		for (i = rowMax - 1; i > 0; i--)
			if (matrix[i - 1][j] != 0 && matrix[i][j] == 0)
				return 1;
	int temp = 0;
	for (j = 0; j < colMax - 1; j++)
		if (matrix[rowMax - 1][j] == 0 && matrix[rowMax - 1][j + 1] != 0) {
			temp = 0;
			for (i = 0; i < rowMax; i++)
				if (matrix[i][j] != 0)
					temp = 1;
			if (!temp)
				return 1;
		}
	return 0;
}
void matrixInitialize(int maxRow, int maxCol, bool frame, int matrix[][10])
{
	int i, j;
	//测试用
	//cct_setconsoleborder(80, 80, 800, 100);
	////
	//for (i = 0; i < maxRow; i++) {
	//	for (j = 0; j < maxCol; j++)
	//		cout << matrix[i][j] << " ";
	//	cout << endl;
	//}
	//system("pause");
	//
	// 
	cct_setconsoleborder(55 + (maxCol - 8) * 6 + frame * 14 + frame * 2 * (maxCol - 8), 32 + (maxRow - 8) * 3 + frame * 7 + frame * (maxRow - 8), 55 + (maxCol - 8) * 6 + frame * 14 + frame * 2 * (maxCol - 8), 32 + (maxRow - 8) * 3 + frame * 7 + frame * (maxRow - 8));
	cout << "屏幕当前设置为: " << 32 + (maxRow - 8) * 3 + frame * 7 + frame * (maxRow - 8) << "行" << 55 + (maxCol - 8) * 6 + frame * 14 + frame * 2 * (maxCol - 8) << "列" << endl;
	for (i = 0; i < maxCol; i++) {
		delay;
		cct_showint(6 + i * (6 + 2 * frame), 1, i, defaultColor, 1);
	}
	for (i = 0; i < maxRow; i++) {
		delay;
		cct_showch(0, 4 + i * (3 + frame), 'A' + i, defaultColor, 1);
	}
	for (i = 0; i < maxRow; i++)
		for (j = 0; j < maxCol; j++) {
			delay;
			blockGenrator(6 + j * (6 + 2 * frame), 4 + i * (3 + frame), matrix[i][j]);
			//测试用
			//cout << matrix[i][j];
			//
		}
	cct_setcolor(inverseColor);
	cct_gotoxy(2, 2);
	delay;
	cout << "╔";
	cct_gotoxy(6 + (maxCol - 1) * (6 + 2 * frame) + 4, 2);
	delay;
	cout << "╗";
	cct_gotoxy(2, 4 + (maxRow - 1) * (3 + frame) + 2);
	delay;
	cout << "╚";
	cct_gotoxy(6 + (maxCol - 1) * (6 + 2 * frame) + 4, 4 + (maxRow - 1) * (3 + frame) + 2);
	delay;
	cout << "╝";
	cct_setcolor(inverseColor);
	i = 4;
	while (i < 6 + (maxCol - 1) * (6 + 2 * frame) + 4) {
		cct_gotoxy(i, 2);
		delay;
		cout << "═";
		cct_gotoxy(i, 4 + (maxRow - 1) * (3 + frame) + 2);
		delay;
		cout << "═";
		i++;
		i++;
	}
	i = 3;
	while (i < 4 + (maxRow - 1) * (3 + frame) + 2) {
		cct_gotoxy(2, i);
		delay;
		cout << "║";
		cct_gotoxy(6 + (maxCol - 1) * (6 + 2 * frame) + 4, i);
		delay;
		cout << "║";
		i++;
	}
	cct_setcolor(inverseColor);
	if (frame) {
		for (i = 0; i < maxCol - 1; i++) {
			cct_gotoxy(6 + i * (6 + 2 * frame) + 4, 2);
			delay;
			cout << "╦";
			cct_gotoxy(6 + i * (6 + 2 * frame) + 4, 4 + (maxRow - 1) * (3 + frame) + 2);
			delay;
			cout << "╩";
		}
		for (i = 0; i < maxRow - 1; i++) {
			cct_gotoxy(2, 4 + i * (3 + frame) + 2);
			delay;
			cout << "╠";
			cct_gotoxy(6 + (maxCol - 1) * (6 + 2 * frame) + 4, 4 + i * (3 + frame) + 2);
			delay;
			cout << "╣";
		}
		for (i = 0; i < maxCol - 1; i++) {
			j = 3;
			while (j < 4 + (maxRow - 1) * (3 + frame) + 2) {
				cct_gotoxy(6 + i * (6 + 2 * frame) + 4, j);
				delay;
				cout << "║";
				j++;
			}
			j = 4;
			while (j < 6 + (maxCol - 1) * (6 + 2 * frame) + 4) {
				cct_gotoxy(j, 4 + i * (3 + frame) + 2);
				delay;
				cout << "═";
				j++;
				j++;
			}
		}
		for (i = 0; i < maxCol - 1; i++)
			for (j = 0; j < maxRow - 1; j++) {
				cct_gotoxy(6 + i * (6 + 2 * frame) + 4, 4 + j * (3 + frame) + 2);
				delay;
				cout << "╬";
			}
	}
	do
		re
		mi
		fa
		so
		la
		si
		do
			si
			la
			so
			fa
			mi
			re
			do
				cct_setcolor(defaultColor);
	return;
}
void module4(int rowMax, int colMax, int matrix[][10])
{
	bool frame = false, first = true, prompt = true;
	int x = 6, y = 4;
	cct_cls();
	cct_setcursor(CURSOR_INVISIBLE);
	matrixInitialize(rowMax, colMax, frame, matrix);
	if (prompt) {
		cct_gotoxy(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4);
		cout << "箭头键/鼠标移动, 回车键/单击左键选择并结束";
	}
	inverseBlock(6, 4, matrix[0][0]);
	first = false;
	if (1) {
		int X = 0, Y = 0;
		int ret, maction;
		int keycode1, keycode2;
		int loop = 1;

		cct_enable_mouse();

		/* 打印初始光标位置[0,0] */
		//		cout << "[当前鼠标位置] X:0  Y:0"; //打印初始鼠标位置

		while (loop) {
			/* 读鼠标/键盘，返回值为下述操作中的某一种, 当前鼠标位置在<X,Y>处 */
			ret = cct_read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);
			cct_setcursor(CURSOR_INVISIBLE);
			if (ret == CCT_MOUSE_EVENT) {
				/* 转到第7行进行打印 */
				if (prompt) {
					prompt = false;
					//cct_showch(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4, ' ', background, coverLength);
					//cct_setcolor(defaultColor);
				}
				if (Y > 2 && Y < 4 + (rowMax - 1) * (3 + frame) + 2 && X>2 && X < 6 + (colMax - 1) * (6 + 2 * frame) + 4) {
					reverseBlock(x, y, matrix[((y - 3) / (blockheight + frame))][(x - 4) / (blockwidth + 2 * frame)]);
					inverseBlock(6 + ((X - 4) / blockwidth) * (6 + 2 * frame), 4 + ((Y - 3) / blockheight) * (3 + frame), matrix[((Y - 3) / blockheight)][(X - 4) / blockwidth]);
					if ((x != 6 + ((X - 4) / blockwidth) * (6 + 2 * frame) || y != 4 + ((Y - 3) / blockheight) * (3 + frame)) && !first)
						reverseBlock(x, y, matrix[((y - 3) / blockheight)][(x - 4) / blockwidth]);
					if (first)
						first = false;
					x = 6 + ((X - 4) / blockwidth) * (6 + 2 * frame);
					y = 4 + ((Y - 3) / blockheight) * (3 + frame);
					//cct_showch(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4, ' ', background, coverLength);
					//cct_setcolor(defaultColor);
					cct_gotoxy(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4);
					cout << "[当前鼠标] " << (char)('A' + (Y - 3) / blockheight) << "行" << (X - 4) / blockwidth << "列" << covering;
					if (maction == MOUSE_LEFT_BUTTON_CLICK || maction == MOUSE_LEFT_BUTTON_DOUBLE_CLICK) {
						//cct_showch(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4, ' ', background, coverLength);
						//cct_setcolor(defaultColor);
						cct_gotoxy(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4);
						cout << "选中了" << (char)('A' + (y - 3) / blockheight) << "行" << (x - 4) / blockwidth << "列" << covering;
						loop = 0;
					}
					if (maction == MOUSE_RIGHT_BUTTON_CLICK || maction == MOUSE_RIGHT_BUTTON_DOUBLE_CLICK || maction == MOUSE_LEFTRIGHT_BUTTON_CLICK) {
						//cct_showch(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4, ' ', background, coverLength);
						//cct_setcolor(defaultColor);
						cct_gotoxy(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4);
						loop = 0;
						break;
					}
				}
				else {
					reverseBlock(x, y, matrix[((y - 3) / (blockheight + frame))][(x - 4) / (blockwidth + 2 * frame)]);
					if (!first) {
						reverseBlock(x, y, matrix[((y - 3) / blockheight)][(x - 4) / blockwidth]);
						first = true;
					}
					//cct_showch(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4, ' ', background, coverLength);
					//cct_setcolor(defaultColor);
					cct_gotoxy(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4);
					cout << "[当前鼠标] 位置非法" << covering;
				}


			} //end of if (CCT_MOUSE_EVENT)
			else if (ret == CCT_KEYBOARD_EVENT) {
				if (prompt && ((keycode1 == 224 && (keycode2 == KB_ARROW_UP || keycode2 == KB_ARROW_DOWN || keycode2 == KB_ARROW_LEFT || keycode2 == KB_ARROW_RIGHT)) || keycode1 == 13 || keycode1 == 'q' || keycode1 == 'Q')) {
					prompt = false;
					cct_showch(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4, ' ', background, coverLength);
					cct_setcolor(defaultColor);
				}
				if ((keycode1 == 224 && (keycode2 == KB_ARROW_UP || keycode2 == KB_ARROW_DOWN || keycode2 == KB_ARROW_LEFT || keycode2 == KB_ARROW_RIGHT)) || keycode1 == 13 || keycode1 == 'q' || keycode1 == 'Q') {
					cct_showch(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4, ' ', background, coverLength);
					cct_setcolor(defaultColor);
				}
				cct_gotoxy(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4);
				switch (keycode1) {
					case 224:
						reverseBlock(x, y, matrix[((y - 3) / blockheight)][(x - 4) / blockwidth]);
						switch (keycode2) {
							case KB_ARROW_UP:

								if (y == 4)
									y = 4 + (rowMax - 1) * (3 + frame);
								else
									y -= blockheight;

								break;
							case KB_ARROW_DOWN:
								if (y == 4 + (rowMax - 1) * (3 + frame))
									y = 4;
								else
									y += blockheight;
								break;
							case KB_ARROW_LEFT:
								if (x == 6)
									x = 6 + (colMax - 1) * (6 + 2 * frame);
								else
									x -= blockwidth;

								break;
							case KB_ARROW_RIGHT:
								if (x == 6 + (colMax - 1) * (6 + 2 * frame))
									x = 6;
								else
									x += blockwidth;

								break;
						}
						inverseBlock(x, y, matrix[((y - 3) / blockheight)][(x - 4) / blockwidth]);
						cct_gotoxy(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4);
						cout << "[当前键盘] " << (char)('A' + (y - 3) / blockheight) << "行" << (x - 4) / blockwidth << "列";
						break;
					case 13:	//ENTER键
						cct_showch(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4, ' ', background, coverLength);
						cct_setcolor(defaultColor);
						cct_gotoxy(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4);
						cout << "选中了" << (char)('A' + (y - 3) / blockheight) << "行" << (x - 4) / blockwidth << "列";
						loop = 0;
						break;
					case 'q':
						cct_showch(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4, ' ', background, coverLength);
						cct_setcolor(defaultColor);
						cct_gotoxy(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4);
						loop = 0;
						break;
					case'Q':
						cct_showch(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4, ' ', background, coverLength);
						cct_setcolor(defaultColor);
						cct_gotoxy(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4);
						loop = 0;
						break;
				}//end of swicth(keycode1)
			}//end of else if(ret == CCT_KEYBOARD_EVENT）
		} //end of while(1)

		cct_disable_mouse();	//禁用鼠标
		cct_setcursor(CURSOR_VISIBLE_NORMAL);	//打开光标
	}
	cct_gotoxy(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 3);
	cin.ignore(10000, '\n');
	return;
}
void module5(int rowMax, int colMax, int matrix[][10])
{
	bool frame = true, first = true, prompt = true, valid;
	int x = 6, y = 4, i;
	cct_cls();
	matrixInitialize(rowMax, colMax, frame, matrix);

	if (prompt) {
		cct_gotoxy(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4);
		cout << "箭头键/鼠标移动, 回车键/单击左键选择并结束";
	}
	inverseBlock(6, 4, matrix[0][0]);
	first = false;
	if (1) {
		int X = 0, Y = 0;
		int ret, maction;
		int keycode1, keycode2;
		int loop = 1;

		cct_enable_mouse();

		/* 打印初始光标位置[0,0] */
		//		cout << "[当前鼠标位置] X:0  Y:0"; //打印初始鼠标位置

		while (loop) {
			cct_setcursor(CURSOR_INVISIBLE);
			/* 读鼠标/键盘，返回值为下述操作中的某一种, 当前鼠标位置在<X,Y>处 */
			ret = cct_read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);

			if (ret == CCT_MOUSE_EVENT) {
				/* 转到第7行进行打印 */
				if (prompt && ((keycode1 == 224 && (keycode2 == KB_ARROW_UP || keycode2 == KB_ARROW_DOWN || keycode2 == KB_ARROW_LEFT || keycode2 == KB_ARROW_RIGHT)) || keycode1 == 13 || keycode1 == 'q' || keycode1 == 'Q')) {
					prompt = false;
					//cct_showch(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4, ' ', background, coverLength);
					//cct_setcolor(defaultColor);
				}
				valid = true;
				if (Y > 2 && Y < 4 + (rowMax - 1) * (3 + frame) + 2 && X>2 && X < 6 + (colMax - 1) * (6 + 2 * frame) + 4) {
					for (i = 0; i < colMax - 1; i++)
						if (X == 6 + i * (6 + 2 * frame) + 4 || X == 6 + i * (6 + 2 * frame) + 5)
							valid = false;
					for (i = 0; i < rowMax - 1; i++)
						if (Y == 4 + i * (3 + frame) + 2)
							valid = false;
				}
				else
					valid = false;
				if (valid) {
					reverseBlock(x, y, matrix[((y - 3) / (blockheight + frame))][(x - 4) / (blockwidth + 2 * frame)]);
					inverseBlock(6 + ((X - 4) / (blockwidth + 2 * frame)) * (6 + 2 * frame), 4 + ((Y - 3) / (blockheight + frame)) * (3 + frame), matrix[((Y - 3) / (blockheight + frame))][(X - 4) / (blockwidth + 2 * frame)]);
					if ((x != 6 + ((X - 4) / (blockwidth + 2 * frame)) * (6 + 2 * frame) || y != 4 + ((Y - 3) / (blockheight + frame)) * (3 + frame)) && !first)

						reverseBlock(x, y, matrix[((y - 3) / (blockheight + frame))][(x - 4) / (blockwidth + 2 * frame)]);
					if (first)
						first = false;
					x = 6 + ((X - 4) / (blockwidth + 2 * frame)) * (6 + 2 * frame);
					y = 4 + ((Y - 3) / (blockheight + frame)) * (3 + frame);
					//cct_showch(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4, ' ', background, coverLength);
					//cct_setcolor(defaultColor);
					cct_gotoxy(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4);
					cout << "[当前鼠标] " << (char)('A' + (Y - 3) / (blockheight + frame)) << "行" << (X - 4) / (blockwidth + 2 * frame) << "列" << covering;
					if (maction == MOUSE_LEFT_BUTTON_CLICK || maction == MOUSE_LEFT_BUTTON_DOUBLE_CLICK) {

						//cct_showch(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4, ' ', background, coverLength);
						//cct_setcolor(defaultColor);
						cct_gotoxy(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4);
						cout << "选中了" << (char)('A' + (y - 3) / (blockheight + frame)) << "行" << (x - 4) / (blockwidth + 2 * frame) << "列" << covering;
						loop = 0;
					}
					if (maction == MOUSE_RIGHT_BUTTON_CLICK || maction == MOUSE_RIGHT_BUTTON_DOUBLE_CLICK || maction == MOUSE_LEFTRIGHT_BUTTON_CLICK) {
						//cct_showch(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4, ' ', background, coverLength);
						//cct_setcolor(defaultColor);
						cct_gotoxy(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4);
						loop = 0;
						break;
					}
				}
				else {
					reverseBlock(x, y, matrix[((y - 3) / (blockheight + frame))][(x - 4) / (blockwidth + 2 * frame)]);
					if (!first) {
						reverseBlock(x, y, matrix[((y - 3) / (blockheight + frame))][(x - 4) / (blockwidth + 2 * frame)]);
						first = true;
					}
					//cct_showch(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4, ' ', background, coverLength);
					//cct_setcolor(defaultColor);
					cct_gotoxy(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4);
					cout << "[当前鼠标] 位置非法" << covering;

				}


			} //end of if (CCT_MOUSE_EVENT)
			else if (ret == CCT_KEYBOARD_EVENT) {
				if (prompt && ((keycode1 == 224 && (keycode2 == KB_ARROW_UP || keycode2 == KB_ARROW_DOWN || keycode2 == KB_ARROW_LEFT || keycode2 == KB_ARROW_RIGHT)) || keycode1 == 13 || keycode1 == 'q' || keycode1 == 'Q')) {
					prompt = false;
					cct_showch(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4, ' ', background, coverLength);
					cct_setcolor(defaultColor);
				}
				if ((keycode1 == 224 && (keycode2 == KB_ARROW_UP || keycode2 == KB_ARROW_DOWN || keycode2 == KB_ARROW_LEFT || keycode2 == KB_ARROW_RIGHT)) || keycode1 == 13 || keycode1 == 'q' || keycode1 == 'Q') {
					cct_showch(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4, ' ', background, coverLength);
					cct_setcolor(defaultColor);
				}
				cct_gotoxy(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4);
				switch (keycode1) {
					case 224:
						reverseBlock(x, y, matrix[((y - 3) / (blockheight + frame))][(x - 4) / (blockwidth + 2 * frame)]);
						switch (keycode2) {
							case KB_ARROW_UP:

								if (y == 4)
									y = 4 + (rowMax - 1) * (3 + frame);
								else
									y -= (blockheight + 1);

								break;
							case KB_ARROW_DOWN:
								if (y == 4 + (rowMax - 1) * (3 + frame))
									y = 4;
								else
									y += (blockheight + 1);
								break;
							case KB_ARROW_LEFT:
								if (x == 6)
									x = 6 + (colMax - 1) * (6 + 2 * frame);
								else
									x -= (blockwidth + 2);

								break;
							case KB_ARROW_RIGHT:
								if (x == 6 + (colMax - 1) * (6 + 2 * frame))
									x = 6;
								else
									x += (blockwidth + 2);

								break;
						}
						inverseBlock(x, y, matrix[((y - 3) / (blockheight + frame))][(x - 4) / (blockwidth + 2 * frame)]);
						cct_gotoxy(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4);
						cout << "[当前键盘] " << (char)('A' + (y - 3) / (blockheight + frame)) << "行" << (x - 4) / (blockwidth + 2 * frame) << "列";
						break;
					case 13:	//ENTER键
						cct_showch(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4, ' ', background, coverLength);
						cct_setcolor(defaultColor);
						cct_gotoxy(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4);
						cout << "选中了" << (char)('A' + (y - 3) / (blockheight + frame)) << "行" << (x - 4) / (blockwidth + 2 * frame) << "列";
						loop = 0;
						break;
					case 'q':
						cct_showch(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4, ' ', background, coverLength);
						cct_setcolor(defaultColor);
						cct_gotoxy(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4);
						loop = 0;
						break;
					case'Q':
						cct_showch(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4, ' ', background, coverLength);
						cct_setcolor(defaultColor);
						cct_gotoxy(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4);
						loop = 0;
						break;
				}//end of swicth(keycode1)
			}//end of else if(ret == CCT_KEYBOARD_EVENT）
		} //end of while(1)

		cct_disable_mouse();	//禁用鼠标
		cct_setcursor(CURSOR_VISIBLE_NORMAL);	//打开光标
	}

	cct_gotoxy(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 3);
	cin.ignore(10000, '\n');
	return;
}
void module6(int rowMax, int colMax, int matrix[][10])
{
	bool frame = false, first = true, prompt = true, warning = false, selected = false;
	int x = 6, y = 4, pivotMatrix[10][10] = { 0 }, i, j, sum = 0, score = 0;
	cct_cls();
	cct_setcursor(CURSOR_INVISIBLE);
	matrixInitialize(rowMax, colMax, frame, matrix);
	if (prompt) {
		cct_gotoxy(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4);
		cout << "箭头键/鼠标移动, 回车键/单击左键选择并结束";
	}
	inverseBlock(6, 4, matrix[0][0]);
	first = false;
	if (1) {
		int X = 0, Y = 0;
		int ret, maction;
		int keycode1, keycode2;
		int loop = 1;

		cct_enable_mouse();

		/* 打印初始光标位置[0,0] */
		//		cout << "[当前鼠标位置] X:0  Y:0"; //打印初始鼠标位置

		while (loop) {
			/* 读鼠标/键盘，返回值为下述操作中的某一种, 当前鼠标位置在<X,Y>处 */
			ret = cct_read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);
			cct_setcursor(CURSOR_INVISIBLE);
			if (ret == CCT_MOUSE_EVENT) {
				/* 转到第7行进行打印 */
				if (prompt) {
					prompt = false;
					//cct_showch(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4, ' ', background, coverLength);
					//cct_setcolor(defaultColor);
				}
				if (Y > 2 && Y < 4 + (rowMax - 1) * (3 + frame) + 2 && X>2 && X < 6 + (colMax - 1) * (6 + 2 * frame) + 4) {
					reverseBlock(x, y, matrix[((y - 3) / blockheight)][(x - 4) / blockwidth]);
					inverseBlock(6 + ((X - 4) / blockwidth) * (6 + 2 * frame), 4 + ((Y - 3) / blockheight) * (3 + frame), matrix[((Y - 3) / blockheight)][(X - 4) / blockwidth]);
					if ((x != 6 + ((X - 4) / blockwidth) * (6 + 2 * frame) || y != 4 + ((Y - 3) / blockheight) * (3 + frame)) && !first) {
						for (i = 0; i < 10; i++)
							for (j = 0; j < 10; j++)
								pivotMatrix[i][j] = 0;
						search((y - 3) / (blockheight + frame), (x - 4) / (blockwidth + 2 * frame), matrix, rowMax, colMax, 6, 6, 4, blockheight - 1, blockwidth - 1, pivotMatrix, sum);
					}
					//reverseBlock(x, y, matrix[((y - 3) / blockheight)][(x - 4) / blockwidth]);
					if (first)
						first = false;
					if (warning && (x != 6 + ((X - 4) / blockwidth) * (6 + 2 * frame) || y != 4 + ((Y - 3) / blockheight) * (3 + frame))) {


						//	cct_showch(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4, ' ', background, coverLength);
						cct_showch(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 3, ' ', background, coverLength);
						cct_setcolor(defaultColor);
						warning = false;
					}
					if (selected && (x != 6 + ((X - 4) / blockwidth) * (6 + 2 * frame) || y != 4 + ((Y - 3) / blockheight) * (3 + frame))) {
						//		cct_showch(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4, ' ', background, coverLength);
						cct_setcolor(defaultColor);
						search((y - 3) / blockheight, (x - 4) / blockwidth, matrix, rowMax, colMax, 6, 6, 4, blockheight - 1, blockwidth - 1, pivotMatrix, sum);
						selected = false;
					}
					x = 6 + ((X - 4) / blockwidth) * (6 + 2 * frame);
					y = 4 + ((Y - 3) / blockheight) * (3 + frame);

					if (!warning && !selected) {
						//	cct_showch(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4, ' ', background, coverLength);
						//	cct_setcolor(defaultColor);
						cct_gotoxy(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4);
						cout << "[当前鼠标] " << (char)('A' + (Y - 3) / blockheight) << "行" << (X - 4) / blockwidth << "列" << covering;
					}
					for (i = 0; i < 10; i++)
						for (j = 0; j < 10; j++)
							pivotMatrix[i][j] = 0;
					sum = 0;
					if (maction == MOUSE_LEFT_BUTTON_CLICK || maction == MOUSE_LEFT_BUTTON_DOUBLE_CLICK) {
						cct_showch(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4, ' ', background, coverLength);
						cct_setcolor(defaultColor);
						cct_gotoxy(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4);
						sum = search((y - 3) / blockheight, (x - 4) / blockwidth, matrix, rowMax, colMax, 0, 0, 0, 0, 0, pivotMatrix, sum);
						//
						//cout << (y - 3) / blockheight << (x - 4) / blockwidth << matrix[(y - 3) / blockheight][(x - 4) / blockwidth] << sum;
						//
						if (sum == 1) {
							cct_setcolor(texthighlight);
							cout << "周围无相同值,";
							cct_setcolor(defaultColor);
							cout << endl << "箭头键/鼠标移动,回车键/单击左键选择,Q/单击右键结束";
							warning = true;
						}
						else if (!selected && !warning) {

							cout << "箭头键/鼠标移动取消当前选择,回车键/单击左键合成";
							//
							//for (i = 0; i < rowMax; i++) {
							//	for (j = 0; j < colMax; j++)
							//		cout << matrix[i][j] << " ";
							//	cout << endl;
							//}
							//system("pause");
							//
							for (i = 0; i < 10; i++)
								for (j = 0; j < 10; j++)
									pivotMatrix[i][j] = 0;
							search((y - 3) / blockheight, (x - 4) / blockwidth, matrix, rowMax, colMax, 4, 6, 4, blockheight - 1, blockwidth - 1, pivotMatrix, sum);
							selected = true;
							inverseBlock(x, y, matrix[((y - 3) / blockheight)][(x - 4) / blockwidth]);

						}
						else if (selected && !warning) {
							cct_showch(0, 0, ' ', background, coverLength);
							cct_setcolor(defaultColor);
							cct_gotoxy(0, 0);
							score += sum * sum * 5;
							cout << "本次得分" << sum * sum * 5 << " 总分:" << score;
							cct_gotoxy(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4);
							cout << "合成完成,回车键/单击左键下落";
							for (i = 0; i < 10; i++)
								for (j = 0; j < 10; j++)
									pivotMatrix[i][j] = 0;
							search((y - 3) / blockheight, (x - 4) / blockwidth, matrix, rowMax, colMax, 7, 6, 4, blockheight - 1, blockwidth - 1, pivotMatrix, sum);
							while (1) {
								ret = cct_read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);

								if (ret == CCT_MOUSE_EVENT && (maction == MOUSE_LEFT_BUTTON_CLICK || maction == MOUSE_LEFT_BUTTON_DOUBLE_CLICK || maction == MOUSE_LEFTRIGHT_BUTTON_CLICK || maction == FROM_LEFT_2ND_BUTTON_PRESSED))
									break;
								else if (ret == CCT_KEYBOARD_EVENT && keycode1 == 13)
									break;
							}
							zeroMoving(matrix, rowMax, colMax, false);
							cct_showch(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4, ' ', background, coverLength);

							cct_gotoxy(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4);
							cct_setcolor(texthighlight);
							cout << "本次合成结束,按C/单击左键继续新一次的合成";
							cct_setcolor(defaultColor);
							while (1) {
								ret = cct_read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);

								if (ret == CCT_MOUSE_EVENT && (maction == MOUSE_LEFT_BUTTON_CLICK || maction == MOUSE_LEFT_BUTTON_DOUBLE_CLICK))
									break;
								else if (ret == CCT_KEYBOARD_EVENT && keycode1 == 'c' || keycode1 == 'C')
									break;
							}
							loop = 0;
						}
					}
					else if (maction == MOUSE_RIGHT_BUTTON_CLICK || maction == MOUSE_RIGHT_BUTTON_DOUBLE_CLICK || maction == MOUSE_LEFTRIGHT_BUTTON_CLICK) {
						//cct_showch(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4, ' ', background, coverLength);
						//cct_setcolor(defaultColor);
						cct_gotoxy(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 3);
						loop = 0;
					}
				}
				else {
					//reverseBlock(x, y, matrix[((y - 3) / blockheight)][(x - 4) / blockwidth]);
					for (i = 0; i < 10; i++)
						for (j = 0; j < 10; j++)
							pivotMatrix[i][j] = 0;
					search((y - 3) / (blockheight + frame), (x - 4) / (blockwidth + 2 * frame), matrix, rowMax, colMax, 6, 6, 4, blockheight - 1, blockwidth - 1, pivotMatrix, sum);
					if (!first) {
						reverseBlock(x, y, matrix[((y - 3) / blockheight)][(x - 4) / blockwidth]);
						first = true;
					}
					//	cct_showch(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4, ' ', background, coverLength);
					//	cct_setcolor(defaultColor);

					if (warning) {
						//		cct_showch(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4, ' ', background, coverLength);
						cct_showch(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 3, ' ', background, coverLength);
						cct_setcolor(defaultColor);
						warning = false;
						first = true;
					}
					if (selected) {
						//		cct_showch(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4, ' ', background, coverLength);
						cct_setcolor(defaultColor);
						search((y - 3) / (blockheight + frame), (x - 4) / (blockwidth + 2 * frame), matrix, rowMax, colMax, 6, 6, 4, blockheight - 1, blockwidth - 1, pivotMatrix, sum);
						selected = false;
						first = true;
					}
					cct_gotoxy(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4);
					cout << "[当前鼠标] 位置非法" << covering;

				}


			} //end of if (CCT_MOUSE_EVENT)
			else if (ret == CCT_KEYBOARD_EVENT) {
				if (prompt && ((keycode1 == 224 && (keycode2 == KB_ARROW_UP || keycode2 == KB_ARROW_DOWN || keycode2 == KB_ARROW_LEFT || keycode2 == KB_ARROW_RIGHT)) || keycode1 == 13 || keycode1 == 'q' || keycode1 == 'Q')) {
					prompt = false;
					cct_showch(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4, ' ', background, coverLength);
					cct_setcolor(defaultColor);
				}
				if ((keycode1 == 224 && (keycode2 == KB_ARROW_UP || keycode2 == KB_ARROW_DOWN || keycode2 == KB_ARROW_LEFT || keycode2 == KB_ARROW_RIGHT)) || keycode1 == 13 || keycode1 == 'q' || keycode1 == 'Q') {
					cct_showch(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4, ' ', background, coverLength);
					cct_setcolor(defaultColor);
				}
				cct_gotoxy(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4);
				for (i = 0; i < 10; i++)
					for (j = 0; j < 10; j++)
						pivotMatrix[i][j] = 0;
				sum = 0;
				switch (keycode1) {
					case 224:
						reverseBlock(x, y, matrix[((y - 3) / blockheight)][(x - 4) / blockwidth]);
						if (keycode2 == KB_ARROW_UP || keycode2 == KB_ARROW_DOWN || keycode2 == KB_ARROW_LEFT || keycode2 == KB_ARROW_RIGHT) {
							if (warning) {
								cct_showch(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4, ' ', background, coverLength);
								cct_showch(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 3, ' ', background, coverLength);
								cct_setcolor(defaultColor);
								warning = false;
							}
							if (selected) {
								cct_showch(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4, ' ', background, coverLength);
								cct_setcolor(defaultColor);
								search((y - 3) / blockheight, (x - 4) / blockwidth, matrix, rowMax, colMax, 6, 6, 4, blockheight - 1, blockwidth - 1, pivotMatrix, sum);
								selected = false;
							}
						}
						switch (keycode2) {
							case KB_ARROW_UP:


								if (y == 4)
									y = 4 + (rowMax - 1) * (3 + frame);
								else
									y -= blockheight;

								break;
							case KB_ARROW_DOWN:


								if (y == 4 + (rowMax - 1) * (3 + frame))
									y = 4;
								else
									y += blockheight;
								break;
							case KB_ARROW_LEFT:


								if (x == 6)
									x = 6 + (colMax - 1) * (6 + 2 * frame);
								else
									x -= blockwidth;

								break;
							case KB_ARROW_RIGHT:


								if (x == 6 + (colMax - 1) * (6 + 2 * frame))
									x = 6;
								else
									x += blockwidth;

								break;
						}
						inverseBlock(x, y, matrix[((y - 3) / blockheight)][(x - 4) / blockwidth]);
						cct_showch(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4, ' ', background, coverLength);
						cct_setcolor(defaultColor);
						cct_gotoxy(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4);
						cout << "[当前键盘] " << (char)('A' + (y - 3) / blockheight) << "行" << (x - 4) / blockwidth << "列";
						break;
					case 13:	//ENTER键
						cct_showch(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4, ' ', background, coverLength);
						cct_setcolor(defaultColor);
						cct_gotoxy(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4);
						sum = search((y - 3) / blockheight, (x - 4) / blockwidth, matrix, rowMax, colMax, 0, 0, 0, 0, 0, pivotMatrix, sum);
						//
						//cout << (y - 3) / blockheight<< (x - 4) / blockwidth<<matrix[(y - 3) / blockheight][(x - 4) / blockwidth] <<sum;
						//
						if (sum == 1) {
							cct_setcolor(texthighlight);
							cout << "周围无相同值,";
							cct_setcolor(defaultColor);
							cout << endl << "箭头键/鼠标移动,回车键/单击左键选择,Q/单击右键结束";
							warning = true;
						}
						else if (!selected && !warning) {
							cout << "箭头键/鼠标移动取消当前选择,回车键/单击左键合成";
							//
							//for (i = 0; i < rowMax; i++) {
							//	for (j = 0; j < colMax; j++)
							//		cout << matrix[i][j] << " ";
							//	cout << endl;
							//}
							//system("pause");
							//
							for (i = 0; i < 10; i++)
								for (j = 0; j < 10; j++)
									pivotMatrix[i][j] = 0;
							search((y - 3) / blockheight, (x - 4) / blockwidth, matrix, rowMax, colMax, 4, 6, 4, blockheight - 1, blockwidth - 1, pivotMatrix, sum);
							selected = true;
							inverseBlock(x, y, matrix[((y - 3) / blockheight)][(x - 4) / blockwidth]);

						}
						else if (selected && !warning) {
							cct_showch(0, 0, ' ', background, coverLength);
							cct_setcolor(defaultColor);
							cct_gotoxy(0, 0);
							score += sum * sum * 5;
							cout << "本次得分" << sum * sum * 5 << " 总分:" << score;
							cct_gotoxy(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4);
							cout << "合成完成,回车键/单击左键下落";
							for (i = 0; i < 10; i++)
								for (j = 0; j < 10; j++)
									pivotMatrix[i][j] = 0;
							search((y - 3) / blockheight, (x - 4) / blockwidth, matrix, rowMax, colMax, 7, 6, 4, blockheight - 1, blockwidth - 1, pivotMatrix, sum);
							while (1) {
								ret = cct_read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);

								if (ret == CCT_MOUSE_EVENT && (maction == MOUSE_LEFT_BUTTON_CLICK || maction == MOUSE_LEFT_BUTTON_DOUBLE_CLICK || maction == MOUSE_LEFTRIGHT_BUTTON_CLICK || maction == FROM_LEFT_2ND_BUTTON_PRESSED))
									break;
								else if (ret == CCT_KEYBOARD_EVENT && keycode1 == 13)
									break;
							}
							zeroMoving(matrix, rowMax, colMax, false);
							cct_showch(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4, ' ', background, coverLength);
							cct_gotoxy(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4);
							cct_setcolor(texthighlight);

							cout << "本次合成结束,按C/单击左键继续新一次的合成";
							cct_setcolor(defaultColor);
							while (1) {
								ret = cct_read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);

								if (ret == CCT_MOUSE_EVENT && (maction == MOUSE_LEFT_BUTTON_CLICK || maction == MOUSE_LEFT_BUTTON_DOUBLE_CLICK))
									break;
								else if (ret == CCT_KEYBOARD_EVENT && keycode1 == 'c' || keycode1 == 'C')
									break;
							}
							loop = 0;
						}
						break;
					case 'q':
						cct_showch(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4, ' ', background, coverLength);
						cct_setcolor(defaultColor);
						cct_gotoxy(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4);
						loop = 0;
						break;
					case'Q':
						cct_showch(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4, ' ', background, coverLength);
						cct_setcolor(defaultColor);
						cct_gotoxy(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4);
						loop = 0;
						break;
				}//end of swicth(keycode1)
			}//end of else if(ret == CCT_KEYBOARD_EVENT）
		} //end of while(1)

		cct_disable_mouse();	//禁用鼠标
		cct_setcursor(CURSOR_VISIBLE_NORMAL);	//打开光标
	}
	cct_gotoxy(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 3);
	cin.ignore(10000, '\n');
	return;
}
void module7(int rowMax, int colMax, int matrix[][10])
{
	bool frame = true, first = true, prompt = true, warning = false, selected = false, valid, end = false;
	int x = 6, y = 4, pivotMatrix[10][10] = { 0 }, i, j, sum = 0, score = 0, remainder;
	while (!end) {

		cct_cls();
		matrixInitialize(rowMax, colMax, frame, matrix);
		if (prompt) {
			cct_gotoxy(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4);
			cout << "箭头键/鼠标移动, 回车键/单击左键选择并结束" << covering;
		}
		inverseBlock(6, 4, matrix[0][0]);
		first = false;
		if (1) {
			int X = 0, Y = 0;
			int ret, maction;
			int keycode1, keycode2;
			int loop = 1;

			cct_enable_mouse();

			/* 打印初始光标位置[0,0] */
			//		cout << "[当前鼠标位置] X:0  Y:0"; //打印初始鼠标位置

			while (loop) {
				cct_setcursor(CURSOR_INVISIBLE);
				cct_enable_mouse();
				/* 读鼠标/键盘，返回值为下述操作中的某一种, 当前鼠标位置在<X,Y>处 */
				//maction == 0;
				ret = cct_read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);

				if (ret == CCT_MOUSE_EVENT) {
					/* 转到第7行进行打印 */
					if (prompt) {
						prompt = false;
						cct_showch(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4, ' ', background, coverLength);
						cct_setcolor(defaultColor);
					}
					valid = true;
					if (matrix[((Y - 3) / (blockheight + frame))][(X - 4) / (blockwidth + 2 * frame)] == 0)
						valid = false;
					if (Y > 2 && Y < 4 + (rowMax - 1) * (3 + frame) + 2 && X>2 && X < 6 + (colMax - 1) * (6 + 2 * frame) + 4) {
						for (i = 0; i < colMax - 1; i++)
							if (X == 6 + i * (6 + 2 * frame) + 4 || X == 6 + i * (6 + 2 * frame) + 5)
								valid = false;
						for (i = 0; i < rowMax - 1; i++)
							if (Y == 4 + i * (3 + frame) + 2)
								valid = false;
					}
					else
						valid = false;
					if (valid) {
						inverseBlock(6 + ((X - 4) / (blockwidth + 2 * frame)) * (6 + 2 * frame), 4 + ((Y - 3) / (blockheight + frame)) * (3 + frame), matrix[((Y - 3) / (blockheight + frame))][(X - 4) / (blockwidth + 2 * frame)]);
						if ((x != 6 + ((X - 4) / (blockwidth + 2 * frame)) * (6 + 2 * frame) || y != 4 + ((Y - 3) / (blockheight + frame)) * (3 + frame)) && !first) {
							//reverseBlock(x, y, matrix[((y - 3) / (blockheight + frame))][(x - 4) / (blockwidth + 2 * frame)]);
							for (i = 0; i < 10; i++)
								for (j = 0; j < 10; j++)
									pivotMatrix[i][j] = 0;
							search((y - 3) / (blockheight + frame), (x - 4) / (blockwidth + 2 * frame), matrix, rowMax, colMax, 6, 6, 4, blockheight, blockwidth + 1, pivotMatrix, sum);
						}
						if (first)
							first = false;
						if (warning && ((x != 6 + ((X - 4) / (blockwidth + frame * 2)) * (6 + 2 * frame) || y != 4 + ((Y - 3) / (blockheight + frame)) * (3 + frame)))) {
							reverseBlock(x, y, matrix[((y - 3) / (blockheight + frame))][(x - 4) / (blockwidth + 2 * frame)]);

							//system("pause");
							//cct_showch(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4, ' ', background, coverLength);
							cct_showch(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 3, ' ', background, coverLength);
							cct_setcolor(defaultColor);
							warning = false;
						}
						if (selected && ((x != 6 + ((X - 4) / (blockwidth + frame * 2)) * (6 + 2 * frame) || y != 4 + ((Y - 3) / (blockheight + frame)) * (3 + frame)))) {
							//system("pause");
							//cct_showch(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4, ' ', background, coverLength);
							cct_setcolor(defaultColor);
							search((y - 3) / (blockheight + frame), (x - 4) / (blockwidth + 2 * frame), matrix, rowMax, colMax, 6, 6, 4, blockheight, blockwidth + 1, pivotMatrix, sum);
							selected = false;
						}
						for (i = 0; i < 10; i++)
							for (j = 0; j < 10; j++)
								pivotMatrix[i][j] = 0;
						sum = 0;
						x = 6 + ((X - 4) / (blockwidth + 2 * frame)) * (6 + 2 * frame);
						y = 4 + ((Y - 3) / (blockheight + frame)) * (3 + frame);
						if (!warning && !selected) {
							//cct_showch(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4, ' ', background, coverLength);
							//cct_setcolor(defaultColor);
							cct_gotoxy(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4);
							cout << "[当前鼠标] " << (char)('A' + (Y - 3) / (blockheight + frame)) << "行" << (X - 4) / (blockwidth + 2 * frame) << "列" << covering;
						}
						if (maction == MOUSE_LEFT_BUTTON_CLICK || maction == MOUSE_LEFT_BUTTON_DOUBLE_CLICK) {
							cct_showch(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4, ' ', background, coverLength);
							cct_setcolor(defaultColor);
							cct_gotoxy(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4);
							sum = search((y - 3) / (blockheight + frame), (x - 4) / (blockwidth + 2 * frame), matrix, rowMax, colMax, 0, 0, 0, 0, 0, pivotMatrix, sum);
							//
							//cout << (y - 3) / blockheight << (x - 4) / blockwidth << matrix[(y - 3) / blockheight][(x - 4) / blockwidth] << sum;
							//
							if (sum == 1) {
								cct_setcolor(texthighlight);
								cout << "周围无相同值,";
								cct_setcolor(defaultColor);
								cout << endl << "箭头键/鼠标移动,回车键/单击左键选择,Q/单击右键结束";
								warning = true;
							}
							else if (!selected && !warning) {
								cout << "箭头键/鼠标移动取消当前选择,回车键/单击左键合成";
								//
								//for (i = 0; i < rowMax; i++) {
								//	for (j = 0; j < colMax; j++)
								//		cout << matrix[i][j] << " ";
								//	cout << endl;
								//}
								//system("pause");
								//
								for (i = 0; i < 10; i++)
									for (j = 0; j < 10; j++)
										pivotMatrix[i][j] = 0;
								search((y - 3) / (blockheight + frame), (x - 4) / (blockwidth + 2 * frame), matrix, rowMax, colMax, 4, 6, 4, blockheight, blockwidth + 1, pivotMatrix, sum);
								selected = true;
								inverseBlock(x, y, matrix[((y - 3) / (blockheight + 1))][(x - 4) / (blockwidth + 2 * frame)]);

							}
							else if (selected && !warning) {
								//								system("pause");

								cct_enable_mouse();
								if (matrix[((y - 3) / (blockheight + 1))][(x - 4) / (blockwidth + 2 * frame)] != 0) {
									cct_showch(0, 0, ' ', background, coverLength);
									cct_setcolor(defaultColor);
									cct_gotoxy(0, 0);
									score += sum * sum * 5;
									cout << "本次得分" << sum * sum * 5 << " 总分:" << score;
								}
								//								cct_showch(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4, ' ', background, coverLength);
								//								cct_setcolor(defaultColor);
								for (i = 0; i < 10; i++)
									for (j = 0; j < 10; j++)
										pivotMatrix[i][j] = 0;
								search((y - 3) / (blockheight + frame), (x - 4) / (blockwidth + 2 * frame), matrix, rowMax, colMax, 7, 6, 4, blockheight, blockwidth + 1, pivotMatrix, sum);
								if (whetherMove(matrix, rowMax, colMax)) {
									cct_gotoxy(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4);
									cout << "合成完成,回车键/单击左键下落" << covering;

									while (1) {
										ret = cct_read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);

										if (ret == CCT_MOUSE_EVENT && (maction == MOUSE_LEFT_BUTTON_CLICK || maction == MOUSE_LEFT_BUTTON_DOUBLE_CLICK || maction == MOUSE_LEFTRIGHT_BUTTON_CLICK || maction == FROM_LEFT_2ND_BUTTON_PRESSED))
											break;
										else if (ret == CCT_KEYBOARD_EVENT && keycode1 == 13)
											break;
									}
									zeroMoving(matrix, rowMax, colMax, true);
								}
								else {
									cct_gotoxy(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4);
									cout << "[当前鼠标] 位置非法" << covering;
									warning = true;
								}
								if (victory(matrix, rowMax, colMax, remainder)) {
									cct_gotoxy(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4);
									cct_setcolor(texthighlight);
									cout << "剩余" << remainder << "个星星, 无可消除项,本关结束!";
									cct_setcolor(defaultColor);
									cout << "回车继续下一关";
									cct_showch(0, 0, ' ', background, coverLength);
									cct_setcolor(defaultColor);
									cct_gotoxy(0, 0);
									cout << "奖励得分";
									if (remainder >= 10)
										cout << "0 ";
									else {
										cout << (10 - remainder) * 180 << " ";
										score += (10 - remainder) * 180;
									}
									cout << "总分:" << score;
									while (_getch() != 13)
										;
									loop = 0;
									cct_gotoxy(0, 0);
									for (i = 0; i < 10; i++)
										for (j = 0; j < 10; j++)
											matrix[i][j] = (rand() % 5) + 1;
									x = 6;
									y = 4;
								}
								else {
									if (matrix[((y - 3) / (blockheight + 1))][(x - 4) / (blockwidth + 2 * frame)] != 0) {
										//cct_showch(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4, ' ', background, coverLength);
										//cct_setcolor(defaultColor);
										cct_gotoxy(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4);
										cout << "[当前鼠标] " << (char)('A' + (y - 3) / (blockheight + frame)) << "行" << (x - 4) / (blockwidth + 2 * frame) << "列" << covering;
									}
									else {
										x = 6;
										y = 4;
										while (matrix[(y - 3) / (blockheight + frame)][(j - 4) / (blockwidth + 2 * frame)] == 0) {
											if (y == 4 + (rowMax - 1) * (3 + frame))
												y = 4;
											else
												y += (blockheight + 1);
										}

									}
									selected = false;
								}
							}
						}
						else if (maction == MOUSE_RIGHT_BUTTON_CLICK || maction == MOUSE_RIGHT_BUTTON_DOUBLE_CLICK || maction == MOUSE_LEFTRIGHT_BUTTON_CLICK) {
							cct_showch(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4, ' ', background, coverLength);
							cct_setcolor(defaultColor);
							cct_gotoxy(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 3);
							loop = 0;
							end = true;
						}
					}
					else {
						for (i = 0; i < 10; i++)
							for (j = 0; j < 10; j++)
								pivotMatrix[i][j] = 0;
						search((y - 3) / (blockheight + frame), (x - 4) / (blockwidth + 2 * frame), matrix, rowMax, colMax, 6, 6, 4, blockheight, blockwidth + 1, pivotMatrix, sum);
						//reverseBlock(x, y, matrix[((y - 3) / (blockheight + frame))][(x - 4) / (blockwidth + 2 * frame)]);
						if (!first) {
							reverseBlock(x, y, matrix[((y - 3) / (blockheight + frame))][(x - 4) / (blockwidth + 2 * frame)]);
							first = true;
						}
						//cct_showch(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4, ' ', background, coverLength);
						//cct_setcolor(defaultColor);

						if (warning) {
							//cct_showch(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4, ' ', background, coverLength);
							cct_showch(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 3, ' ', background, coverLength);
							cct_setcolor(defaultColor);
							warning = false;
						}
						if (selected) {
							//cct_showch(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4, ' ', background, coverLength);
							//cct_setcolor(defaultColor);
							search((y - 3) / (blockheight + frame), (x - 4) / (blockwidth + 2 * frame), matrix, rowMax, colMax, 6, 6, 4, blockheight, blockwidth + 1, pivotMatrix, sum);
							selected = false;
						}
						cct_gotoxy(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4);
						cout << "[当前鼠标] 位置非法" << covering;

					}


				} //end of if (CCT_MOUSE_EVENT)
				else if (ret == CCT_KEYBOARD_EVENT) {
					if (prompt && ((keycode1 == 224 && (keycode2 == KB_ARROW_UP || keycode2 == KB_ARROW_DOWN || keycode2 == KB_ARROW_LEFT || keycode2 == KB_ARROW_RIGHT)) || keycode1 == 13 || keycode1 == 'q' || keycode1 == 'Q')) {
						prompt = false;
						cct_showch(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4, ' ', background, coverLength);
						cct_setcolor(defaultColor);
					}
					if ((keycode1 == 224 && (keycode2 == KB_ARROW_UP || keycode2 == KB_ARROW_DOWN || keycode2 == KB_ARROW_LEFT || keycode2 == KB_ARROW_RIGHT)) || keycode1 == 13 || keycode1 == 'q' || keycode1 == 'Q') {
						cct_showch(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4, ' ', background, coverLength);
						cct_setcolor(defaultColor);
					}
					cct_gotoxy(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4);
					for (i = 0; i < 10; i++)
						for (j = 0; j < 10; j++)
							pivotMatrix[i][j] = 0;
					sum = 0;
					switch (keycode1) {
						case 224:
							reverseBlock(x, y, matrix[((y - 3) / (blockheight + frame))][(x - 4) / (blockwidth + 2 * frame)]);
							if (keycode2 == KB_ARROW_UP || keycode2 == KB_ARROW_DOWN || keycode2 == KB_ARROW_LEFT || keycode2 == KB_ARROW_RIGHT) {
								if (warning) {
									cct_showch(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4, ' ', background, coverLength);
									cct_showch(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 3, ' ', background, coverLength);
									cct_setcolor(defaultColor);
									warning = false;
								}
								if (selected) {
									cct_showch(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4, ' ', background, coverLength);
									cct_setcolor(defaultColor);
									search((y - 3) / (blockheight + frame), (x - 4) / (blockwidth + 2 * frame), matrix, rowMax, colMax, 6, 6, 4, blockheight, blockwidth + 1, pivotMatrix, sum);
									selected = false;
								}
							}
							if (x == 6)
								i = 6 + (colMax - 1) * (6 + 2 * frame);
							else
								i = x - (blockwidth + 2);
							while (matrix[(y - 3) / (blockheight + frame)][(i - 4) / (blockwidth + 2 * frame)] == 0 && i != x) {
								if (i == 6)
									i = 6 + (colMax - 1) * (6 + 2 * frame);
								else
									i -= (blockwidth + 2);
							}
							if (x == 6 + (colMax - 1) * (6 + 2 * frame))
								j = 6;
							else
								j = x + (blockwidth + 2);
							while (matrix[(y - 3) / (blockheight + frame)][(j - 4) / (blockwidth + 2 * frame)] == 0 && j != x) {
								if (j == 6 + (colMax - 1) * (6 + 2 * frame))
									j = 6;
								else
									j += (blockwidth + 2);

							}
							switch (keycode2) {
								case KB_ARROW_UP:

									if (y == 4 || matrix[(y - 3) / (blockheight + frame) - 1][(x - 4) / (blockwidth + 2 * frame)] == 0)
										y = 4 + (rowMax - 1) * (3 + frame);
									else
										y -= (blockheight + 1);

									break;
								case KB_ARROW_DOWN:


									if (y == 4 + (rowMax - 1) * (3 + frame)) {
										y = 4;
										while (1)
											if (matrix[(y - 3) / (blockheight + frame)][(x - 4) / (blockwidth + 2 * frame)] == 0)
												y += (blockheight + 1);
											else
												break;

									}
									else
										y += (blockheight + 1);
									break;
								case KB_ARROW_LEFT:
									x = i;
									break;
								case KB_ARROW_RIGHT:
									x = j;
									break;
							}
							inverseBlock(x, y, matrix[((y - 3) / (blockheight + frame))][(x - 4) / (blockwidth + 2 * frame)]);
							cct_gotoxy(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4);
							cout << "[当前键盘] " << (char)('A' + (y - 3) / (blockheight + frame)) << "行" << (x - 4) / (blockwidth + 2 * frame) << "列";
							break;
						case 13:	//ENTER键
							cct_showch(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4, ' ', background, 60);
							cct_setcolor(defaultColor);
							cct_gotoxy(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4);
							sum = search((y - 3) / (blockheight + frame), (x - 4) / (blockwidth + 2 * frame), matrix, rowMax, colMax, 0, 0, 0, 0, 0, pivotMatrix, sum);
							if (sum == 1) {
								cct_setcolor(texthighlight);
								cout << "周围无相同值,";
								cct_setcolor(defaultColor);
								cout << endl << "箭头键/鼠标移动,回车键/单击左键选择,Q/单击右键结束";
								warning = true;
							}
							else if (!selected && !warning) {
								cout << "箭头键/鼠标移动取消当前选择,回车键/单击左键合成";
								//
								//for (i = 0; i < rowMax; i++) {
								//	for (j = 0; j < colMax; j++)
								//		cout << matrix[i][j] << " ";
								//	cout << endl;
								//}
								//system("pause");
								//
								for (i = 0; i < 10; i++)
									for (j = 0; j < 10; j++)
										pivotMatrix[i][j] = 0;
								search((y - 3) / (blockheight + frame), (x - 4) / (blockwidth + 2 * frame), matrix, rowMax, colMax, 4, 6, 4, blockheight, blockwidth + 1, pivotMatrix, sum);
								selected = true;
								inverseBlock(x, y, matrix[((y - 3) / (blockheight + frame))][(x - 4) / (blockwidth + 2 * frame)]);

							}
							else if (selected && !warning) {

								if (matrix[((y - 3) / (blockheight + 1))][(x - 4) / (blockwidth + 2 * frame)] != 0) {
									cct_showch(0, 0, ' ', background, 40);
									cct_setcolor(defaultColor);
									cct_gotoxy(0, 0);
									score += sum * sum * 5;
									cout << "本次得分" << sum * sum * 5 << " 总分:" << score;
								}
								cct_showch(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4, ' ', background, coverLength);
								cct_setcolor(defaultColor);
								for (i = 0; i < 10; i++)
									for (j = 0; j < 10; j++)
										pivotMatrix[i][j] = 0;
								search((y - 3) / (blockheight + frame), (x - 4) / (blockwidth + 2 * frame), matrix, rowMax, colMax, 7, 6, 4, blockheight, blockwidth + 1, pivotMatrix, sum);
								if (whetherMove(matrix, rowMax, colMax)) {
									cct_gotoxy(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4);
									cout << "合成完成,回车键/单击左键下落";

									while (1) {
										ret = cct_read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);

										if (ret == CCT_MOUSE_EVENT && (maction == MOUSE_LEFT_BUTTON_CLICK || maction == MOUSE_LEFT_BUTTON_DOUBLE_CLICK || maction == MOUSE_LEFTRIGHT_BUTTON_CLICK || maction == FROM_LEFT_2ND_BUTTON_PRESSED))
											break;
										else if (ret == CCT_KEYBOARD_EVENT && keycode1 == 13)
											break;
									}
									zeroMoving(matrix, rowMax, colMax, true);
								}
								if (victory(matrix, rowMax, colMax, remainder)) {
									cct_gotoxy(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4);
									cct_setcolor(texthighlight);
									cout << "剩余" << remainder << "个星星, 无可消除项,本关结束!";
									cct_setcolor(defaultColor);
									cout << "回车继续下一关";
									cct_gotoxy(0, 0);
									cout << "奖励得分:";
									if (remainder >= 10)
										cout << "0 ";
									else {
										cout << (10 - remainder) * 180 << " ";
										score += (10 - remainder) * 180;
									}
									cout << "总分:" << score;
									while (_getch() != 13)
										;
									loop = 0;
									cct_gotoxy(0, 0);
									for (i = 0; i < 10; i++)
										for (j = 0; j < 10; j++)
											matrix[i][j] = (rand() % 5) + 1;
									x = 6;
									y = 4;
								}
								else {
									if ((keycode1 == 224 && (keycode2 == KB_ARROW_UP || keycode2 == KB_ARROW_DOWN || keycode2 == KB_ARROW_LEFT || keycode2 == KB_ARROW_RIGHT)) || keycode1 == 13 || keycode1 == 'q' || keycode1 == 'Q') {
										cct_showch(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4, ' ', background, coverLength);
										cct_setcolor(defaultColor);
									}
									cct_gotoxy(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4);
									cout << "箭头键/鼠标移动,回车键/单击左键选择,Q/单击右键结束";
									x = 6;
									y = 4;
									while (matrix[(y - 3) / (blockheight + frame)][(j - 4) / (blockwidth + 2 * frame)] == 0) {
										if (y == 4 + (rowMax - 1) * (3 + frame))
											y = 4;
										else
											y += (blockheight + 1);
									}
									inverseBlock(x, y, matrix[(y - 3) / (blockheight + frame)][(j - 4) / (blockwidth + 2 * frame)]);
								}
								break;
						case 'q':
							cct_showch(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4, ' ', background, coverLength);
							cct_setcolor(defaultColor);
							cct_gotoxy(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4);
							loop = 0;
							end = true;
							cin.ignore(10000, '\n');
							break;
						case'Q':
							cct_showch(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4, ' ', background, coverLength);
							cct_setcolor(defaultColor);
							cct_gotoxy(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 4);
							loop = 0;
							end = true;
							cin.ignore(10000, '\n');
							break;
							}//end of swicth(keycode1)
					}//end of else if(ret == CCT_KEYBOARD_EVENT）
				} //end of while(1)

				cct_disable_mouse();	//禁用鼠标
				cct_setcursor(CURSOR_VISIBLE_NORMAL);	//打开光标
			}

			cct_gotoxy(0, 32 + (rowMax - 8) * 3 + frame * 7 + frame * (rowMax - 8) - 3);
			//cin.ignore(10000, '\n');
		}
	}
	return;
}