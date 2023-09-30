/* 2254298 大数据 范潇 */
#include<iostream>
using namespace std;
#include"../include/cmd_console_tools.h"
#include"../include/common_make.h"
//====================================================
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
//函 数 名:make_list
//功能描述:打印若干行文字
//输入参数:起始位置,文字数组,数组长度,间隔行数,颜色
//返 回 值:
//说    明:
//=====================================================
void make_list(int x, int y, const char* list[], int list_length, int dy, int bg_color, int fg_color)
{
	int X, Y;
	cct_getxy(X, Y);
	cct_setcolor(bg_color, fg_color);
	for (int i = 0; i < list_length; i++) {
		cct_gotoxy(x, y + i * dy);
		cout << list[i];
	}
	cct_setcolor();
	cct_gotoxy(X, Y);
	return;
}

//=====================================================
//函 数 名:make_block
//功能描述:打印一个方块
//输入参数:构成方块的各行字符串
//返 回 值:
//说    明:
//=====================================================
void make_block(int x, int y, const char* row[], int row_num, int bg_color, int fg_color)
{
	make_list(x, y, row, row_num, 1, bg_color, fg_color);
	return;
}