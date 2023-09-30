#include<iostream>
#include<Windows.h>
#include<conio.h>
#include "../include/cmd_console_tools.h"
#include"../include/menu.h"
#include"../include/calc.h"
#include"../include/make.h"
#include"../include/list.h"
using namespace std;
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
	bool case_sensitive, const char* prompt, const char* caution, const char* header, const char* bottom,
	int menu_screen_width, int menu_screen_height, const char* menu_font_family, int menu_font_size)
{
	cct_cls();
	if (menu_length + 11 > menu_screen_height)
		menu_screen_height = menu_length + 11;
	cct_setconsoleborder(menu_screen_width, menu_screen_height, menu_screen_width, menu_screen_height);
	cct_setfontsize(menu_font_family, menu_font_size);
	cout << header << endl;
	for (int i = 0; i < menu_length; i++)
		if (alpha)
			cout << (char)(i + 'A') << "." << menu_list[i] << endl;
		else
			cout << i + 1 << "." << menu_list[i] << endl;
	cout << quit_key << "." << "退出" << endl;
	cout << bottom << endl;
	cout << prompt << endl;
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
	return;
}
//=====================================================
//函 数 名:wait_arrow_key
//功能描述:等待用户输入一个箭头键,并返回,1,2,3,4分别代表上下左右
//输入参数:
//返 回 值:
//说    明:
//=====================================================
int wait_arrow_key()
{
	while (1) {
		if (_getch() == 224) {
			int temp = _getch();
			if (temp == 72)
				return 1;
			else if (temp == 80)
				return 2;
			else if (temp == 75)
				return 3;
			else if (temp == 77)
				return 4;
		}
	}
}
//=====================================================
//函 数 名:get_arrow_key
//功能描述:读取用户的输入,若是箭头键,并返回,1,2,3,4分别代表上下左右,否则返回0
//输入参数:
//返 回 值:
//说    明:
//=====================================================
int get_arrow_key()
{
	if (_getch() == 224) {
		int temp = _getch();
		if (temp == 72)
			return 1;
		else if (temp == 80)
			return 2;
		else if (temp == 75)
			return 3;
		else if (temp == 77)
			return 4;
	}
	return 0;
}


