#include<iostream>
#include "../include/cmd_console_tools.h"
#define TEXTLENGTH 50 
#define horizontal_line  "--------------------------------------------" 
using namespace std;
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
//说    明:将来应该把该函数移至显示相关的工具集中
//=====================================================
void clear_and_prompt(int x, int y, int dx, int dy, const char* prompt, int whitespace_length = TEXTLENGTH)
{
	cct_showch(x, y, ' ', COLOR_BLACK, COLOR_WHITE, whitespace_length);
	cct_gotoxy(x + dx, y + dy);
	cout << prompt;
	cct_gotoxy(x, y);
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
int begin_with(const char* x, const char* y, int case_sensitive = 0)
{
	while (*x && *y) {
		if ((*x != *y) && case_sensitive || case_insensitive_char_compare(*x, *y) && !case_sensitive)
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
void erase_prompt(int dx, int dy, int bg_color = COLOR_BLACK, int fg_color = COLOR_WHITE, int erase_length = TEXTLENGTH)
{
	int x, y;
	cct_getxy(x, y);
	cct_showch(x + dx, y + dy, ' ', bg_color, fg_color, erase_length);
	cct_gotoxy(x, y);
	return;
}
//=====================================================
//函 数 名:menu
//功能描述:展示菜单,并返回用户的选择
//输入参数:包含菜单的字符指针数组及其长度,退出键及其长度,菜单编号样式,大小写是否敏感以及提示语句
//返 回 值:返回正整数代表所选的菜单项,返回0代表退出
//说    明:含有错误处理,退出键若以数字开头,至多只有一位数
//=====================================================
int menu(const char* menu_list[], int menu_length, const char* quit_key, bool alpha = false,
	bool case_sensitive = false, const char* prompt = "请重新输入",
	const char * header=horizontal_line,const char * bottom = horizontal_line)
{
	cout << header << endl;
	for (int i = 0; i < menu_length; i++)
		cout << (alpha ? (char)(1 + 'A') : i + 1) << "." << menu_list[i] << endl;
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
				return 0;
			}
			else if (case_sensitive && between(*input_text, 'A', 'A' + menu_length) ||
				!case_sensitive && (between(*input_text, 'A', 'A' + menu_length) || between(*input_text, 'a', 'a' + menu_length))) {
				erase_prompt(0, 0);
				return between(*input_text, 'A', 'A' + menu_length) ? *input_text - 'A' + 1 : *input_text - 'a' + 1;
			}
		}
	}
}
