/* 2254298 ������ ���� */
#include<iostream>
using namespace std;
#include"../include/cmd_console_tools.h"
#include"../include/common_make.h"
//====================================================
//�� �� ��:clear_and_prompt
//��������:���һ���ո�,�������ʾ
//�������:�ո�ʼ�����λ��,�Լ���ʾ��ӡ����������λ��
//�� �� ֵ:
//˵    ��:����Ӧ�ðѸú���������ʾ��صĹ��߼���,û�������ʾλ�õ�����,�����̲�һ�ᵼ����ʾ����.
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
//�� �� ��:erase_prompt
//��������:�����ʾ���
//�������:��ʾ�������ڵ�ǰ��λ��
//�� �� ֵ:
//˵    ��:����Ӧ�ðѸú��������ַ�����صĹ��߼���
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
//�� �� ��:make_colorblock
//��������:��ӡһ��ɫ��
//�������:ɫ������Ͻ�����,ɫ��ĳ���,��ɫ
//�� �� ֵ:
//˵    ��:
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
//�� �� ��:make_frame
//��������:��ӡһ���߿�
//�������:�߿����Ͻ�����,����,�߿���ַ��Լ��߿����ɫ�Լ���ɫ
//�� �� ֵ:
//˵    ��:side_list�е��ַ�Ӧ������Ϊ�ĸ���,�����Ͻ�˳ʱ��,������
// ʹ��const char*[]������char[]����Ϊ��Щ�߿��޷���char���洢
//=====================================================
void make_frame(int x, int y, int width, int height, const char* side_list[], int side_width, int bg_color, int fg_color)
{
	const	char* default_side_list[] = { "�X","�[","�a","�^","�T","�U" };
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
//�� �� ��:make_line
//��������:��ӡһ����
//�������:��ʼ����,����ַ�,����ַ�����,�Ƿ�Ϊ��,��ɫ
//�� �� ֵ:
//˵    ��:��Ϊ��ӡһЩ�����ַ��޷�ʹ��cct_showch
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
//�� �� ��:make_dotted_line
//��������:��ӡһ������
//�������:��һ���������,��ĸ���,����������֮��Ĳ�,����,��ɫ
//�� �� ֵ:
//˵    ��:
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
//�� �� ��:make_lattice
//��������:��ӡһ������
//�������:�����Ͻǵ������,xy����������Ĳ�,xy�����ĸ���,�����ʽ,��ɫ
//�� �� ֵ:
//˵    ��:
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
//�� �� ��:make_board
//��������:��ӡһ��չʾ��
//�������:չʾ�����Ͻǵ�����,�߿������ַ�,��ֱ�߿�Ŀ��,�ڲ�����ĳ���,�Ƿ�Ҫ�ڲ��ı߿�,�ڲ��ֿ�ĸ���,�߿����ɫ,�ײ�����ɫ
//�� �� ֵ:
//˵    ��:side_list�е��ַ�Ӧ������Ϊ�ĸ���,�����Ͻ�˳ʱ��,������,T�������,˳��Ϊ��������,���һ����ʮ���������
// ʹ��const char* []������ char[]����Ϊ��Щ�߿��ַ��޷���char���洢
//ʹ��ʱҪ��blockwidthΪsidewidth��������.
//=====================================================
void make_board(int x, int y, int block_width, int block_height, int vertical_block_num, int horizontal_block_num,
	bool inner_side, int board_color, int side_color, const char* side_list[], int side_width, bool shadow, int shadow_width, int shadow_color)
{
	const	char* default_side_list[] = { "�X","�[","�a","�^","�T","�U","�j","�m","�d","�g","�p" };
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
//�� �� ��:make_list
//��������:��ӡ����������
//�������:��ʼλ��,��������,���鳤��,�������,��ɫ
//�� �� ֵ:
//˵    ��:
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
//�� �� ��:make_block
//��������:��ӡһ������
//�������:���ɷ���ĸ����ַ���
//�� �� ֵ:
//˵    ��:
//=====================================================
void make_block(int x, int y, const char* row[], int row_num, int bg_color, int fg_color)
{
	make_list(x, y, row, row_num, 1, bg_color, fg_color);
	return;
}