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
//�� �� ��:query_with_test
//��������:�����û�������,���ж��Ƿ����Ҫ��
//�������:��������ı���,�ж��Ƿ����Ҫ��ĺ���
//�� �� ֵ:1Ϊ��ȷ,0Ϊ����.
//˵    ��:��ָ�뽫�����ֵ��������
// TODO:���������غ�����д������ܲ�ͬ���͵ı����ĺ���,���������ع�menu����
//=====================================================
//=====================================================
//�� �� ��:menu
//��������:չʾ�˵�,�������û���ѡ��
//�������:�����˵����ַ�ָ�����鼰�䳤��,�˳������䳤��,�˵������ʽ,��Сд�Ƿ�����,������ȷ�����ʱ�Լ���ʾ���
//�� �� ֵ:����������������ѡ�Ĳ˵���,����0�����˳�
//˵    ��:���д�����,�˳����������ֿ�ͷ,����ֻ��һλ��
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
	cout << quit_key << "." << "�˳�" << endl;
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
//�� �� ��:to_be_continued
//��������:��ͣ����,����ʾ�û���ĳ��������
//�������:��ʾ��ʾλ��,��ʾ���,�����,��ɫ
//�� �� ֵ:
//˵    ��:��֧�ֻس���
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
//�� �� ��:enter_to_continue
//��������:��ͣ����,����ʾ�û�������������
//�������:��ʾ��ʾλ��,��ʾ���,�����,��ɫ
//�� �� ֵ:
//˵    ��:
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
//�� �� ��:wait_arrow_key
//��������:�ȴ��û�����һ����ͷ��,������,1,2,3,4�ֱ������������
//�������:
//�� �� ֵ:
//˵    ��:
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
//�� �� ��:get_arrow_key
//��������:��ȡ�û�������,���Ǽ�ͷ��,������,1,2,3,4�ֱ������������,���򷵻�0
//�������:
//�� �� ֵ:
//˵    ��:
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


