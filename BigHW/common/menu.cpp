#include<iostream>
#include "../include/cmd_console_tools.h"
#define TEXTLENGTH 50 
#define horizontal_line  "--------------------------------------------" 
using namespace std;
//=====================================================
//�� �� ��:between
//��������:�жϵ�һ�������Ƿ��ڵڶ����������м�(����)
//�������:
//�� �� ֵ:1��ʾ����,0��ʾ������
//˵    ��:����Ӧ�ðѸú�������������صĹ��߼���
//=====================================================
int between(double num, double x, double y)
{
	return (x <= num && num <= y || y <= num && num <= x);
}
//=====================================================
//�� �� ��:clear_and_prompt
//��������:���һ���ո�,�������ʾ
//�������:�ո�ʼ�����λ��,�Լ���ʾ��ӡ����������λ��
//�� �� ֵ:
//˵    ��:����Ӧ�ðѸú���������ʾ��صĹ��߼���
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
//�� �� ��:case_insensitive_char_compare
//��������:�Ƚ������ַ��Ƿ����,��Сд������
//�������:�����ַ�,�����Ⱥ�.
//�� �� ֵ:1Ϊ��,0Ϊ��
//˵    ��:����Ӧ�ðѸú��������ַ�����صĹ��߼���
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
//�� �� ��:begin_with
//��������:�ж�һ���ַ����Ƿ�������һ���ַ�����ʼ.
//�������:�����ַ���,�����Ⱥ�.
//�� �� ֵ:1Ϊ��,0Ϊ��
//˵    ��:����Ӧ�ðѸú��������ַ�����صĹ��߼���
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
//�� �� ��:erase_prompt
//��������:�����ʾ���
//�������:��ʾ�������ڵ�ǰ��λ��
//�� �� ֵ:
//˵    ��:����Ӧ�ðѸú��������ַ�����صĹ��߼���
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
//�� �� ��:menu
//��������:չʾ�˵�,�������û���ѡ��
//�������:�����˵����ַ�ָ�����鼰�䳤��,�˳������䳤��,�˵������ʽ,��Сд�Ƿ������Լ���ʾ���
//�� �� ֵ:����������������ѡ�Ĳ˵���,����0�����˳�
//˵    ��:���д�����,�˳����������ֿ�ͷ,����ֻ��һλ��
//=====================================================
int menu(const char* menu_list[], int menu_length, const char* quit_key, bool alpha = false,
	bool case_sensitive = false, const char* prompt = "����������",
	const char * header=horizontal_line,const char * bottom = horizontal_line)
{
	cout << header << endl;
	for (int i = 0; i < menu_length; i++)
		cout << (alpha ? (char)(1 + 'A') : i + 1) << "." << menu_list[i] << endl;
	cout << quit_key << "." << "�˳�" << endl;
	cout << bottom << endl;
	cout << "[��ѡ��:]" << endl;
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
