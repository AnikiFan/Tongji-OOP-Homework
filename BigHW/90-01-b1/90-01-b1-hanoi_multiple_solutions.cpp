/* 2254298 大数据 范潇 */


/* ----------------------------------------------------------------------------------

	 本文件功能：
	1、存放被 hanoi_main.cpp 中根据菜单返回值调用的各菜单项对应的执行函数

	 本文件要求：
	1、不允许定义外部全局变量（const及#define不在限制范围内）
	2、允许定义静态全局变量（具体需要的数量不要超过文档显示，全局变量的使用准则是：少用、慎用、能不用尽量不用）
	3、静态局部变量的数量不限制，但使用准则也是：少用、慎用、能不用尽量不用
	4、按需加入系统头文件、自定义头文件、命名空间等

   ----------------------------------------------------------------------------------- */
#include"90-01-b1-hanoi.h"
static int Top[3], Stack[3][10], speed, totalstep = 0;//Top存储的是待插入的位置


/***************************************************************************
  函数名称：reload
  功    能：
  输入参数：
  返 回 值：
  说    明：按回车键继续,清屏集成为一个函数
***************************************************************************/
extern void reload(void)
{
	char input;
	cout << endl;
	cout << "按回车键继续";
	while (1) {
		input = _getch();
		if (input == 13)
			break;
	}
	cct_cls();
	speed = 0;
	totalstep = 0;
	return;
}

/***************************************************************************
  函数名称：initializevariable
  功    能：
  输入参数：
  返 回 值：dst
  说    明：依据inputnumber来决定给哪些变量赋值并且初始化Top和Stack,输入应该遵循只有在输入类型错误时才清空缓存区的原则
***************************************************************************/
void initializevariable(char input, char* src, char* dst, char* tmp, int* level)
{
	int  i, j;
	//TODO:测试用
	//for (i = 0; i < 3; i++)
	//	cout << "测试用&" << Top[i];
	//测试用
	for (i = 0; i < 3; i++)
		Top[i] = 0;//重置Top数组
	for (i = 0; i < 3; i++)
		for (j = 0; j < 10; j++)
			Stack[i][j] = 0;//重置Stack数组
	cout << "请输入汉诺塔的层数(1-10)" << endl;
	while (1) {
		cin >> *level;
		if (*level > 0 && *level <= 10 && !cin.rdstate()) {
			cin.clear();
			cin.ignore(10000000, '\n');//删了这个以后会死循环
			break;
		}
		else if (cin.rdstate()) {
			cin.clear();
			cin.ignore(10000000, '\n');//删了这个以后会死循环
		}
		cout << "请输入汉诺塔的层数(1-10)" << endl;
	}
	//TODO:测试用
	//for (i = 0; i < 3; i++)
	//	cout << "测试用#" << Top[i];
	//测试用
	cout << "请输入起始柱(A-C)" << endl;
	while (1) {
		cin >> *src;
		if ((*src == 'A' || *src == 'B' || *src == 'C' || *src == 'a' || *src == 'b' || *src == 'c') && !cin.rdstate()) {
			switch (*src) {
				case 'a':
					*src = 'A';
					break;
				case 'b':
					*src = 'B';
					break;
				case 'c':
					*src = 'C';
					break;
				default:
					break;
			}
			cin.clear();
			cin.ignore(10000000, '\n');//删了这个以后会死循环
			break;
		}
		else if (cin.rdstate()) {
			cin.clear();
			cin.ignore(10000000, '\n');//删了这个以后会死循环
		}
		cout << "请输入起始柱(A-C)" << endl;
	}
	cout << "请输入目标柱(A-C)" << endl;
	while (1) {
		cin >> *dst;
		if ((*dst == 'A' || *dst == 'B' || *dst == 'C' || *dst == 'a' || *dst == 'b' || *dst == 'c') && !cin.rdstate()
			&& dst != src && dst != (src + 32)) {
			cin.clear();
			cin.ignore(10000000, '\n');//删了这个以后会死循环
			break;
		}
		else if (cin.rdstate()) {
			cin.clear();
			cin.ignore(10000000, '\n');//删了这个以后会死循环
		}
		if (*dst == *src || *dst == (*src + 32))
			cout << "目标柱(" << src << ")不能与起始柱(" << src << ")相同" << endl;
		cout << "请输入目标柱(A-C)" << endl;
	}
	switch (*dst) {
		case 'a':
			*dst = 'A';
			break;
		case 'b':
			*dst = 'B';
			break;
		case 'c':
			*dst = 'C';
			break;
	}
	*tmp = 'A' + 'B' + 'C' - *src - *dst;
	//TODO:测试用
	//for (i = 0; i < 3; i++)
	//	cout << "测试用*" << Top[i];
	//测试用
	Top[*src - 'A'] = *level;
	for (i = 0; i < *level; i++)
		Stack[*src - 'A'][i] = *level - i;
	//TODO:测试用
	//for (i = 0; i < 3; i++)
	//	cout << "测试用" << Top[i];
	//测试用
	if (input == '4' || input == '8') {
		cout << "请输入移动速度(0-5: 0-按回车单步演示 1-延时最长 5-延时最短)" << endl;
		while (1) {
			cin >> speed;
			if (speed >= 0 && speed <= 5 && !cin.rdstate()) {
				cin.clear();
				cin.ignore(10000000, '\n');//删了这个以后会死循环
				break;
			}
			else if (cin.rdstate()) {
				cin.clear();
				cin.ignore(10000000, '\n');//删了这个以后会死循环
			}
			cout << "请输入移动速度(0-5: 0-按回车单步演示 1-延时最长 5-延时最短)";
		}
	}
	return;
}


/***************************************************************************
  函数名称：speedcontrol
  功    能：
  输入参数：
  返 回 值：
  说    明：负责延时的函数
***************************************************************************/
void speedcontrol()
{
	switch (speed) {
		case 0:
			while (_getch() != 13)
				;
			break;
		case 1:
			Sleep(speed1);
			break;
		case 2:
			Sleep(speed2);
			break;
		case 3:
			Sleep(speed3);
			break;
		case 4:
			Sleep(speed4);
			break;
		case 5:
			Sleep(speed5);
			break;
		case 6:
			Sleep(speed6);
			break;
	}
	return;
}

/***************************************************************************
函数名称：horizontal
功    能：
输入参数：输出起始位置,如果需要输出"初始"则bool initialize==True
返 回 值：
说    明：横向输出
***************************************************************************/
void horizontal(int xcoordinate, int ycoordinate, int level, char src, char dst, bool initialized)
{
	int i, tenflag = 0;

	cct_gotoxy(xcoordinate, ycoordinate);
	if (initialized)
		cout << "初始:  ";
	else
		cout << "第" << setw(4) << totalstep << " 步( " << setw(2) << level << "#: " << src << "-->" << dst << ") ";
	cout << "A:";
	for (i = 0; i < Top[0]; i++) {
		if (Stack[0][i] == 10)
			tenflag = 1;
		cout << setw(2) << Stack[0][i];
	}
	cout << setw(2 * (10 - Top[0]) + 3);
	tenflag = 0;

	cout << "B:";
	for (i = 0; i < Top[1]; i++) {
		if (Stack[1][i] == 10)
			tenflag = 1;
		cout << setw(2) << Stack[1][i];
	}
	cout << setw(2 * (10 - Top[1]) + 3);

	cout << "C:";
	for (i = 0; i < Top[2]; i++) {
		if (Stack[2][i] == 10)
			tenflag = 1;
		cout << setw(2) << Stack[2][i];
	}
	cout << setw(2 * (10 - Top[2]) + 3) << " ";
	cout << endl;
}

/***************************************************************************
函数名称：vertical
功    能：
输入参数：输出B的位置,需要显示初始状态时bool initialize=tru
返 回 值：
说    明：竖直输出
***************************************************************************/
void vertical(char src, char dst, int level, int xcoordinate, int ycoordinate, bool initialize)
{
	int i;
	if (initialize) {
		cct_gotoxy(xcoordinate - xcoodif - 2, ycoordinate - 1);
		cout << setfill('=') << setw(6 + 2 * xcoodif) << " ";
		cout << setfill(' ');
		cct_gotoxy(xcoordinate, ycoordinate);
		cout << "B";
		cct_gotoxy(xcoordinate - xcoodif, ycoordinate);
		cout << "A";
		cct_gotoxy(xcoordinate + xcoodif, ycoordinate);
		cout << "C";
		for (i = 1; i < level + 1; i++) {
			cct_gotoxy(xcoordinate - ('B' - src) * xcoodif - 1, ycoordinate - 1 - i);
			cout << setw(2) << level + 1 - i;

		}
		return;
	}
	cct_gotoxy(xcoordinate - ('B' - src) * xcoodif - 1, ycoordinate - Top[src - 'A'] - 2);
	cout << setw(2) << " ";
	cct_gotoxy(xcoordinate - ('B' - dst) * xcoodif - 1, ycoordinate - 1 - Top[dst - 'A']);
	//测试用
	//cout << "$";
	//测试用
	cout << setw(2) << Stack[src - 'A'][Top[src - 'A']];
	return;

}
/***************************************************************************
函数名称：plateMoving
功    能：
输入参数：srclevel和sdtlevel分别是起始层数和结束层数,size是盘子的大小
返 回 值：
说    明：移动盘子
***************************************************************************/
void plateMoving(char src, char dst, int srclevel, int dstlevel, int size)
{
	int i, color[10][2] = colorBoard, direction = dst - src;

	cct_gotoxy(mdclxcoo + (src - 'B') * clxcoodif, bmclycoo - srclevel + 1);
	//测试用
	//Sleep(10000);
	//测试用
	//测试用
	//cout << "测试用" <<"*"<<size-1;
	//测试用
	for (i = bmclycoo - srclevel; i >= bmclycoo - clht; i--) {

		cct_showch(mdclxcoo + (src - 'B') * clxcoodif - size, i, ' ', background, 2 * size + 1);
		//消除潘
		if (i != bmclycoo - clht)
			cct_showch(mdclxcoo + (src - 'B') * clxcoodif, i, ' ', columnColor, 1);
		//补柱
		speedcontrol();
		cct_showch(mdclxcoo + (src - 'B') * clxcoodif - size, i - 1, ' ', color[size - 1][0], color[size - 1][1], 2 * size + 1);
		//生成
		speedcontrol();
	}
	if (direction > 0) {
		for (i = mdclxcoo + (src - 'B') * clxcoodif - size; i < mdclxcoo + (dst - 'B') * clxcoodif - size; i++) {
			cct_showch(i, bmclycoo - clht - 1, ' ', background, 2 * size + 1);
			//消除潘
			speedcontrol();
			cct_showch(i + 1, bmclycoo - clht - 1, ' ', color[size - 1][0], color[size - 1][1], 2 * size + 1);
			//生成
			speedcontrol();
		}
	}
	else {
		for (i = mdclxcoo + (src - 'B') * clxcoodif - size; i > mdclxcoo + (dst - 'B') * clxcoodif - size; i--) {
			cct_showch(i, bmclycoo - clht - 1, ' ', background, 2 * size + 1);
			//消除潘
			speedcontrol();
			cct_showch(i - 1, bmclycoo - clht - 1, ' ', color[size - 1][0], color[size - 1][1], 2 * size + 1);
			//生成
			speedcontrol();
		}
	}


	for (i = bmclycoo - clht - 1; i < bmclycoo - dstlevel - 1; i++) {
		cct_showch(mdclxcoo + (dst - 'B') * clxcoodif - size, i, ' ', background, 2 * size + 1);
		//消除潘
		if (i > bmclycoo - clht)
			cct_showch(mdclxcoo + (dst - 'B') * clxcoodif, i, ' ', columnColor, 1);
		//补柱
		speedcontrol();
		cct_showch(mdclxcoo + (dst - 'B') * clxcoodif - size, i + 1, ' ', color[size - 1][0], color[size - 1][1], 2 * size + 1);
		//生成
		speedcontrol();
	}
	cct_setcolor(defaultColor);
	cct_gotoxy endcoo;
	return;
}


/***************************************************************************
  函数名称：column
  功    能：
  输入参数：
  返 回 值：
  说    明：输出三个柱子
***************************************************************************/
void column()
{
	int i, j;
	for (i = -1; i < 2; i++) {
		cct_showch(mdclxcoo + i * clxcoodif - clsgwid, bmclycoo, ' ', columnColor, 2 * clsgwid + 1);
		prolong
			for (j = 0; j < clht; j++) {
				cct_showch(mdclxcoo + i * clxcoodif, bmclycoo - j, ' ', columnColor, 1);
				prolong
			}
	}
	cct_setcolor(defaultColor);
	cct_gotoxy endcoo;
	return;
}

/***************************************************************************
  函数名称：plategenerator
  功    能：
  输入参数：最低层盘子的坐标以及层数
  返 回 值：
  说    明：负责生成盘子
***************************************************************************/
void plategenerator(int xcoordinate, int ycoordinate, int level)
{
	int i, color[10][2] = colorBoard;
	for (i = 0; i < level; i++) {
		cct_showch(xcoordinate - (level - i), ycoordinate - i, ' ', color[level - i - 1][0], color[level - i - 1][1], 2 * (level - i) + 1);
		//测试用
		//cout << "测试用$" << color[level - i-1][0]<< color[level - i-1][1]<<level-i-1;
		//测试用
		prolong
	}
	cct_setcolor(defaultColor);
	cct_gotoxy endcoo;
	return;
}

/***************************************************************************
  函数名称：hanoiplus
  功    能：
  输入参数：
  返 回 值：
  说    明：辅助汉诺塔输出以及统计步数的函数
***************************************************************************/
void hanoiplus(int level, char src, char tmp, char dst, char inputnumber)
{
	int x, y;
	switch (inputnumber) {
		case'1':
			cout << level << "# " << src << arrow << dst << endl;
			break;
		case'2':
			totalstep++;
			cout << "第" << setw(4) << totalstep << " 步( " << setw(2) << level << "#: " << src << "-->" << dst << ")" << endl;
			break;
		case'3':
			cct_getxy(x, y);
			totalstep++;
			horizontal(x, y, level, src, dst, false);
			break;
		case '4':
			totalstep++;
			horizontal(htxcoo, htycoo, level, src, dst, false);
			vertical(src, dst, level, vtBx, vtBy, false);
			speedcontrol();
			break;
		case '7':
			totalstep++;
			if (totalstep == 1)
				plateMoving(src, dst, Top[src - 'A'] + 1, Top[dst - 'A'] - 1, Stack[dst - 'A'][Top[dst - 'A'] - 1]);
			break;
		case '8':
			if (speed == 6)
				while (_getch() != 13)
					;
			totalstep++;
			horizontal(htxcoo, htycoo + offset, level, src, dst, false);
			vertical(src, dst, level, vtBx, vtBy + offset, false);
			plateMoving(src, dst, Top[src - 'A'] + 1, Top[dst - 'A'] - 1, Stack[dst - 'A'][Top[dst - 'A'] - 1]);
			break;
	}
	return;
}


/***************************************************************************
  函数名称：hanoi
  功    能：
  输入参数：
  返 回 值：
  说    明：汉诺塔递归函数
***************************************************************************/
void hanoi(int level, char src, char tmp, char dst, char inputnumber)
{
	if (level == 1) {
		Stack[dst - 'A'][Top[dst - 'A']++] = Stack[src - 'A'][--Top[src - 'A']];
		hanoiplus(level, src, tmp, dst, inputnumber);
		//	num++;
		//	cout << "第" << setw(4) << num << " 步" << "(1#: " << src << arrow << dst << ")  ";
		return;
	}
	hanoi(level - 1, src, dst, tmp, inputnumber);
	Stack[dst - 'A'][Top[dst - 'A']++] = Stack[src - 'A'][--Top[src - 'A']];
	hanoiplus(level, src, tmp, dst, inputnumber);
	//num++;
	//cout << "第" << setw(4) << num << " 步" << "(" << temp << "#: " << src << arrow << dst << ")  ";
	hanoi(level - 1, tmp, src, dst, inputnumber);
	return;
}






/***************************************************************************
  函数名称：module4
  功    能：
  输入参数：
  返 回 值：
  说    明：内部数组显示(纵向+横向)
***************************************************************************/
void module4(char src, char dst, char tmp, int level)
{
	cct_cls();
	cout << "从 " << src << " 移动到 " << dst << "，共 " << level << " 层，延时设置为 " << speed << endl;
	horizontal(htxcoo, htycoo, level, src, dst, true);
	vertical(src, dst, level, vtBx, vtBy, true);
	speedcontrol();
	hanoi(level, src, tmp, dst, '4');
	cct_gotoxy(endxcoo, endycoo);
	return;
}



/***************************************************************************
  函数名称：module6
  功    能：
  输入参数：
  返 回 值：
  说    明：图形解-预备-在起始柱上画n个盘子
***************************************************************************/
void module6(char src, char dst, char tmp, int level)
{
	cct_cls();
	cout << "从 " << src << " 移动到 " << dst << "，共 " << level << " 层" << endl;
	column();
	plategenerator(mdclxcoo + (src - 'B') * clxcoodif, bmclycoo - 1, level);
	return;
} 

/***************************************************************************
  函数名称：module7
  功    能：
  输入参数：
  返 回 值：
  说    明：图形解-预备-第一次移动
***************************************************************************/
void module7(char src, char dst, char tmp, int level)
{
	speed = 4;
	cct_cls();
	cout << "从 " << src << " 移动到 " << dst << "，共 " << level << " 层" << endl;
	column();
	plategenerator(mdclxcoo + (src - 'B') * clxcoodif, bmclycoo - 1, level);
	hanoi(level, src, tmp, dst, '7');
	return;
}

/***************************************************************************
  函数名称：module8
  功    能：
  输入参数：
  返 回 值：
  说    明：图形解-自动移动版本
***************************************************************************/
void module8(char src, char dst, char tmp, int level)
{
	if (speed == 0)
		speed = 6;
	cct_cls();
	cout << "从 " << src << " 移动到 " << dst << "，共 " << level << " 层" << endl;
	horizontal(htxcoo, htycoo + offset, level, src, dst, true);
	vertical(src, dst, level, vtBx, vtBy + offset, true);
	column();
	plategenerator(mdclxcoo + (src - 'B') * clxcoodif, bmclycoo - 1, level);
	hanoi(level, src, tmp, dst, '8');
	return;
}

/***************************************************************************
  函数名称：module9
  功    能：
  输入参数：
  返 回 值：
  说    明：图形解-游戏版
***************************************************************************/
void module9(char src, char dst, char tmp, int level)
{
	char temp;
	int i = 0, x, y;
	speed = 4;
	char  input[19] = { 0 };
	cct_cls();
	cout << "从 " << src << " 移动到 " << dst << "，共 " << level << " 层" << endl;
	horizontal(htxcoo, htycoo + offset, level, src, dst, true);
	vertical(src, dst, level, vtBx, vtBy + offset, true);
	column();
	plategenerator(mdclxcoo + (src - 'B') * clxcoodif, bmclycoo - 1, level);
	cct_gotoxy(htxcoo, htycoo + offset + 2);
	cout << "请输入移动的柱号(命令形式：AC=A顶端的盘子移动到C，Q=退出) ：";

	while (1) {
		temp = _getche();
		if (temp == 8) {
			cct_getxy(x, y);
			cct_gotoxy(x + 1, y);
		}
		if ((temp <= 32 || temp >= 127) && temp != 13)
			continue;
		input[i] = temp;
		i++;
		if ((input[0] == 'q' || input[0] == 'Q') && input[1] == 13) {
			cout << endl << endl << "游戏中止!!!!!" << endl;//根据peek是否返回回车来判断是否为最后一个输入字符
			break;
		}
		//if (i == 2) {
		//	for (i = 0; i < 3; i++)
		//		input[i] = 0;
		//	i = 0;
		//	}
			//测试用
			//for (int j = 0; j < 3; j++)
			//	cout << input[j]<<j;
			//cout << "测试用" << endl;
			//测试用

		else if (temp == 13 || i == 19) {
			if (input[0] == 'a' || input[0] == 'b' || input[0] == 'c' || input[0] == 'A' || input[0] == 'B' || input[0] == 'C') {
				switch (input[0]) {
					case'a':
						input[0] = 'A';
						break;
					case'b':
						input[0] = 'B';
						break;
					case'c':
						input[0] = 'C';
						break;
				}
				if ((input[1] == 'a' || input[1] == 'b' || input[1] == 'c' || input[1] == 'A' || input[1] == 'B' || input[1] == 'C') && input[1] != input[0] && input[1] != (input[0] - 'A' + 'a') && input[2] == 13) {
					//cout << "测试用" << cin.peek() << endl;
					switch (input[1]) {
						case'a':
							input[1] = 'A';
							break;
						case'b':
							input[1] = 'B';
							break;
						case'c':
							input[1] = 'C';
							break;
					}
					if (Top[input[0] - 'A'] == 0) {
						cout << endl << endl << "源柱为空";
						Sleep(delay);
						cct_showch(0, htycoo + offset + 4, ' ', background, 20);
						cct_setcolor(defaultColor);
					}
					else if (Top[input[1] - 'A'] != 0 && Stack[input[1] - 'A'][Top[input[1] - 'A'] - 1] < Stack[input[0] - 'A'][Top[input[0] - 'A'] - 1]) {//短路逻辑确保不会超出数组范围
						cout << endl << endl << "大盘压小盘,非法移动!";
						Sleep(delay);
						cct_showch(0, htycoo + offset + 4, ' ', background, 20);
						cct_setcolor(defaultColor);
					}
					else {
						//测试用
						//cout << Top[input[1] - 'A'] - 1 << "@" << Top[input[0] - 'A'] - 1;
						//测试用
						totalstep++;
						Stack[input[1] - 'A'][Top[input[1] - 'A']++] = Stack[input[0] - 'A'][--Top[input[0] - 'A']];

						horizontal(htxcoo, htycoo + offset, Stack[input[1] - 'A'][Top[input[1] - 'A'] - 1], input[0], input[1], false);
						vertical(input[0], input[1], Stack[input[1] - 'A'][Top[input[1] - 'A'] - 1], vtBx, vtBy + offset, false);
						plateMoving(input[0], input[1], Top[input[0] - 'A'] + 1, Top[input[1] - 'A'] - 1, Stack[input[1] - 'A'][Top[input[1] - 'A'] - 1]);
						if (level == Top[input[1] - 'A']) {
							cout << "游戏结束!!!";
							break;
						}
					}
				}
			}
			input[0] = 0;
			input[1] = 0;
			input[2] = 0;
			i = 0;
			cct_showch(htxcoo + 60, htycoo + offset + 2, ' ', background, 20);
			cct_gotoxy(htxcoo + 60, htycoo + offset + 2);
			cct_setcolor(defaultColor);

		}
	}
	//测试指令有
	//正确指令:ab,aC,Bc,q,Q
	//无效指令:abc,ABC,QQ,qq,直接回车
	return;
}