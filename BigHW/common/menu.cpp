#include<iostream>
#include<Windows.h>
#include<conio.h>
#include "../include/cmd_console_tools.h"
#include"../include/menu.h"
using namespace std;
//TODO:有些变量可以设为const,如X,Y
//=====================================================
//函 数 名:between
//功能描述:判断第一个参数是否在第二三个参数中间(包括)
//输入参数:
//返 回 值:1表示包括,0表示不包括
//说    明:将来应该把该函数移至运算相关的工具集中
//=====================================================
int between(double num, double x, double y)
{
	return (x <= num && num <= y || y <= num && num <= x);
}
//=====================================================
//函 数 名:clear_and_prompt
//功能描述:输出一串空格,并输出提示
//输入参数:空格开始输出的位置,以及提示打印处与其的相对位置
//返 回 值:
//说    明:将来应该把该函数移至显示相关的工具集中,没有清除提示位置的内容,若长短不一会导致显示问题.
//=====================================================
void clear_and_prompt(int x, int y, int dx, int dy, const char* prompt, int whitespace_length)
{
	cct_showch(x, y, ' ', COLOR_BLACK, COLOR_WHITE, whitespace_length);
	cct_gotoxy(x + dx, y + dy);
	cout << prompt;
	cct_gotoxy(x, y);
	cct_setcolor();
	return;
}
//=====================================================
//函 数 名:case_insensitive_char_compare
//功能描述:比较两个字符是否相等,大小写不敏感
//输入参数:两个字符,不分先后.
//返 回 值:1为真,0为假
//说    明:将来应该把该函数移至字符串相关的工具集中
//=====================================================
int case_insensitive_char_compare(char x, char y)
{
	if (x == y)
		return 1;
	else if (between(x, 'a', 'z') && between(y, 'A', 'Z') && y + 32 == x)
		return 1;
	else if (between(y, 'a', 'z') && between(x, 'A', 'Z') && x + 32 == y)
		return 1;
	else
		return 0;
}
//=====================================================
//函 数 名:begin_with
//功能描述:判断一个字符串是否由另外一个字符串开始.
//输入参数:两个字符串,不分先后.
//返 回 值:1为真,0为假
//说    明:将来应该把该函数移至字符串相关的工具集中
//=====================================================
int begin_with(const char* x, const char* y, int case_sensitive)
{
	if (*x && !*y || !*x && *y)
		return 0;
	while (*x && *y) {
		if ((*x != *y) && case_sensitive || !case_insensitive_char_compare(*x, *y) && !case_sensitive)
			return 0;
		x++;
		y++;
	}
	return 1;
}
//=====================================================
//函 数 名:erase_prompt
//功能描述:清除提示语句
//输入参数:提示语句相对于当前的位置
//返 回 值:
//说    明:将来应该把该函数移至字符串相关的工具集中
//=====================================================
void erase_prompt(int dx, int dy, int bg_color, int fg_color, int erase_length)
{
	int x, y;
	cct_getxy(x, y);
	cct_showch(x + dx, y + dy, ' ', bg_color, fg_color, erase_length);
	cct_gotoxy(x, y);
	cct_setcolor();
	return;
}
//=====================================================
//函 数 名:query_with_test
//功能描述:接受用户的输入,并判断是否符合要求
//输入参数:接受输入的变量,判断是否符合要求的函数
//返 回 值:1为正确,0为错误.
//说    明:用指针将输入的值传出函数
// TODO:用利用重载函数编写多个接受不同类型的变量的函数,并用其来重构menu函数
//=====================================================
//=====================================================
//函 数 名:menu
//功能描述:展示菜单,并返回用户的选择
//输入参数:包含菜单的字符指针数组及其长度,退出键及其长度,菜单编号样式,大小写是否敏感,输入正确后的延时以及提示语句
//返 回 值:返回正整数代表所选的菜单项,返回0代表退出
//说    明:含有错误处理,退出键若以数字开头,至多只有一位数
//=====================================================
int menu(const char* menu_list[], int menu_length, const char* quit_key, bool alpha, int stop,
	bool case_sensitive, const char* prompt, const char* header, const char* bottom)
{
	cct_cls();
	cout << header << endl;
	for (int i = 0; i < menu_length; i++)
		if (alpha)
			cout << (char)(i + 'A') << "." << menu_list[i] << endl;
		else
			cout << i + 1 << "." << menu_list[i] << endl;
	cout << quit_key << "." << "退出" << endl;
	cout << bottom << endl;
	cout << "[请选择:]" << endl;
	int x, y, input_num;
	char input_text[TEXTLENGTH];
	cct_getxy(x, y);
	while (true) {
		cct_showch(x, y, ' ', COLOR_BLACK, COLOR_WHITE, TEXTLENGTH);
		cct_gotoxy(x, y);
		cin >> input_num;
		if (!cin.rdstate() && (input_num + '0' == *quit_key)) {
			erase_prompt(0, 0);
			Sleep(stop);
			return 0;
		}
		if (cin.rdstate() && !alpha) {
			cin.clear();
			cin.ignore(2 * TEXTLENGTH, '\n');
			clear_and_prompt(x, y, 0, 1, prompt);
			continue;
		}
		else if (!cin.rdstate() && alpha) {
			cin.ignore(2 * TEXTLENGTH, '\n');
			clear_and_prompt(x, y, 0, 1, prompt);
			continue;
		}
		else if (!cin.rdstate() && !alpha)
			if (between(input_num, 1, menu_length)) {
				erase_prompt(0, 0);
				Sleep(stop);
				return input_num;
			}
			else {
				cin.ignore(2 * TEXTLENGTH, '\n');
				clear_and_prompt(x, y, 0, 1, prompt);
				continue;
			}
		else {
			cin.clear();
			cin >> input_text;
			if (begin_with(input_text, quit_key)) {
				erase_prompt(0, 0);
				Sleep(stop);
				return 0;
			}
			else if (case_sensitive && between(*input_text, 'A', 'A' + menu_length - 1) ||
				!case_sensitive && (between(*input_text, 'A', 'A' + menu_length - 1) || between(*input_text, 'a', 'a' + menu_length - 1))) {
				erase_prompt(0, 0);
				Sleep(stop);
				return between(*input_text, 'A', 'A' + menu_length - 1) ? *input_text - 'A' + 1 : *input_text - 'a' + 1;
			}
			clear_and_prompt(x, y, 0, 1, prompt);
		}
	}
}
//=====================================================
//函 数 名:make_colorblock
//功能描述:打印一个色块
//输入参数:色块的左上角坐标,色块的长宽,颜色
//返 回 值:
//说    明:
//=====================================================
void make_colorblock(int x, int y, int width, int height, int color)
{
	int X, Y;
	cct_getxy(X, Y);
	for (int i = 0; i < height; i++)
		cct_showch(x, y + i, ' ', color, color, width);
	cct_gotoxy(X, Y);
	cct_setcolor();
	return;
}
//=====================================================
//函 数 名:make_frame
//功能描述:打印一个边框
//输入参数:边框左上角坐标,长宽,边框的字符以及边框的颜色以及底色
//返 回 值:
//说    明:side_list中的字符应该依次为四个角,从左上角顺时针,横竖线
// 使用const char*[]而不是char[]是因为有些边框无法用char来存储
//=====================================================
void make_frame(int x, int y, int width, int height, const char* side_list[], int side_width, int bg_color, int fg_color)
{
	const	char* default_side_list[] = { "╔","╗","╝","╚","═","║" };
	if (!side_list)
		side_list = default_side_list;
	int X, Y;
	cct_getxy(X, Y);
	cct_gotoxy(x, y);
	cct_setcolor(bg_color, fg_color);
	cout << side_list[0];
	for (int i = side_width; i < width - side_width; i += side_width)
		cout << side_list[4];
	cout << side_list[1];
	cct_gotoxy(x, y + height - 1);
	cout << side_list[3];
	for (int i = side_width; i < width - side_width; i += side_width)
		cout << side_list[4];
	cout << side_list[2];
	for (int i = y + 1; i <= y + height - 2; i++) {
		cct_gotoxy(x, i);
		cout << side_list[5];
		cct_gotoxy(x + width - side_width, i);
		cout << side_list[5];
	}
	cct_setcolor();
	cct_gotoxy(X, Y);
	return;
}
//=====================================================
//函 数 名:make_line
//功能描述:打印一条线
//输入参数:起始坐标,填充字符,填充字符个数,是否为横,颜色
//返 回 值:
//说    明:因为打印一些特殊字符无法使用cct_showch
//=====================================================
void make_line(int x, int y, const char* fill, int n, bool horizontal, int bg_color, int fg_color)
{
	int X, Y;
	cct_getxy(X, Y);
	cct_setcolor(bg_color, fg_color);
	if (horizontal) {
		cct_gotoxy(x, y);
		for (int i = 0; i < n; i++)
			cout << fill;
	}
	else
		for (int i = 0; i < n; i++) {
			cct_gotoxy(x, y + i);
			cout << fill;
		}
	cct_setcolor();
	cct_gotoxy(X, Y);
	return;
}
//=====================================================
//函 数 名:make_dotted_line
//功能描述:打印一条点线
//输入参数:第一个点的坐标,点的个数,两个点坐标之间的差,横竖,颜色
//返 回 值:
//说    明:
//=====================================================
void make_dotted_line(int x, int y, int coordinate_difference, int n, const char* dot, bool horizontal, int bg_color, int fg_color)
{
	int X, Y;
	cct_getxy(X, Y);
	cct_setcolor(bg_color, fg_color);
	if (horizontal)
		for (int i = 0; i < n; i++) {
			cct_gotoxy(x + i * coordinate_difference, y);
			cout << dot;
		}
	else
		for (int i = 0; i < n; i++) {
			cct_gotoxy(x, y + i * coordinate_difference);
			cout << dot;
		}
	cct_setcolor();
	cct_gotoxy(X, Y);
	return;
}
//=====================================================
//函 数 名:make_lattice
//功能描述:打印一个点阵
//输入参数:最左上角点的坐标,xy方向点的坐标的差,xy方向点的个数,点的样式,颜色
//返 回 值:
//说    明:
//=====================================================
void make_lattice(int x, int y, int dx, int dy, int x_num, int y_num, const char* dot, int bg_color, int fg_color)
{
	int X, Y;
	cct_getxy(X, Y);
	cct_setcolor(bg_color, fg_color);
	for (int i = 0; i < y_num; i++)
		make_dotted_line(x, y + i * dy, dx, x_num, dot, true, bg_color, fg_color);
	cct_gotoxy(X, Y);
	cct_setcolor();
	return;
}
//=====================================================
//函 数 名:make_board
//功能描述:打印一个展示板
//输入参数:展示板左上角的坐标,边框的组成字符,竖直边框的宽度,内部各块的长宽,是否要内部的边框,内部分块的个数,边框的颜色,底部的颜色
//返 回 值:
//说    明:side_list中的字符应该依次为四个角,从左上角顺时针,横竖线,T字联结符,顺序为上下左右,最后一个是十字形联结符
// 使用const char* []而不是 char[]是因为有些边框字符无法用char来存储
//使用时要让blockwidth为sidewidth的整数倍.
//=====================================================
void make_board(int x, int y, int block_width, int block_height, int vertical_block_num, int horizontal_block_num,
	bool inner_side, int board_color, int side_color, const char* side_list[], int side_width, bool shadow, int shadow_width, int shadow_color)
{
	const	char* default_side_list[] = { "╔","╗","╝","╚","═","║","╦","╩","╠","╣","╬" };
	if (!side_list)
		side_list = default_side_list;
	int X, Y;
	int totle_width = horizontal_block_num * block_width + (horizontal_block_num - 1) * inner_side * side_width + 2 * side_width;
	int totle_height = vertical_block_num * block_height + (vertical_block_num - 1) * inner_side + 2;
	cct_getxy(X, Y);
	cct_gotoxy(x, y);
	if (shadow)
		make_colorblock(x + shadow_width, y + shadow_width, totle_width, totle_height, shadow_color);
	make_colorblock(x, y, totle_width, totle_height, board_color);
	make_frame(x, y, totle_width, totle_height, side_list, side_width, board_color, side_color);
	if (inner_side) {
		for (int i = 1; i < horizontal_block_num; i++)
			make_line(x + i * (side_width + block_width), y + 1, side_list[5], totle_height - 2, false, board_color, side_color);
		for (int i = 1; i < vertical_block_num; i++)
			make_line(x + side_width, y + i * (1 + block_height), side_list[4], (totle_width - 2 * side_width) / 2, true, board_color, side_color);
		make_dotted_line(x + side_width + block_width, y, side_width + block_width, horizontal_block_num - 1, side_list[6], true, board_color, side_color);
		make_dotted_line(x + side_width + block_width, y + totle_height - 1, side_width + block_width, horizontal_block_num - 1, side_list[7], true, board_color, side_color);
		make_dotted_line(x, y + 1 + block_height, 1 + block_height, vertical_block_num - 1, side_list[8], false, board_color, side_color);
		make_dotted_line(x + totle_width - side_width, y + 1 + block_height, 1 + block_height, vertical_block_num - 1, side_list[9], false, board_color, side_color);
		make_lattice(x + block_width + side_width, y + block_height + 1, side_width + block_width, 1 + block_height, horizontal_block_num - 1, vertical_block_num - 1,
			side_list[10], board_color, side_color);
	}
	cct_gotoxy(X, Y);
	cct_setcolor();
	return;
}
//=====================================================
//函 数 名:to_be_continued
//功能描述:暂停程序,并提示用户按某个键继续
//输入参数:显示提示位置,提示语句,输入键,颜色
//返 回 值:
//说    明:不支持回车键
//=====================================================
void to_be_continued(int x, int y, const char* prompt, const char* key, int bg_color, int fg_color)
{
	int X, Y;
	char input[TEXTLENGTH];
	cct_getxy(X, Y);
	cct_gotoxy(x, y);
	cct_setcolor(bg_color, fg_color);
	cout << prompt << endl;
	cct_getxy(x, y);
	while (1) {
		cin.get(input, TEXTLENGTH, '\n');
		if (begin_with(input, key))
			break;
		cct_showch(x, y, ' ', bg_color, fg_color, TEXTLENGTH);
		cct_gotoxy(x, y);
	}
	cct_setcolor();
	cct_gotoxy(X, Y);
	return;
}
//=====================================================
//函 数 名:enter_to_continue
//功能描述:暂停程序,并提示用户按单个键继续
//输入参数:显示提示位置,提示语句,输入键,颜色
//返 回 值:
//说    明:
//=====================================================
void enter_to_continue(int x, int y, const int bg_color, int fg_color, const char* prompt, char key)
{
	int X, Y;
	cct_getxy(X, Y);
	cct_gotoxy(x, y);
	cct_setcolor(bg_color, fg_color);
	cout << prompt << endl;
	cct_getxy(x, y);
	while (_getch() != key)
		;
	cct_setcolor();
	cct_gotoxy(X, Y);
	return ;
}
//=====================================================
//函 数 名:make_list
//功能描述:打印若干行文字
//输入参数:起始位置,文字数组,数组长度,间隔行数,颜色
//返 回 值:
//说    明:
//=====================================================
void make_list(int x,int y,const char* list[],int list_length,int dy,int bg_color,int fg_color)
{
	int X, Y;
	cct_getxy(X, Y);
	cct_setcolor(bg_color, fg_color);
	for (int i = 0; i < list_length; i++) {
		cct_gotoxy(x, y + i*dy);
		cout << list[i];
	}
	cct_setcolor();
	cct_gotoxy(X, Y);
	return;
}
//=====================================================
//函 数 名:make_random_num
//功能描述:
//输入参数:范围,是否使用新的种子,种子
//返 回 值:默认输出0到n-1的随机数
//说    明:
//=====================================================
int get_next_num(int n,const bool new_seed , const unsigned int seed)
{
	if (new_seed)
		srand(seed);
	return rand() % n;
}

