/* 2254298 ������ ���� */
#pragma once
#define horizontal_line  "--------------------------------------------" 
#define MENU_SCREEN_WIDTH 45
#define MENU_SCREEN_HEIGHT 12
#define MENU_FONT_FAMILY "������"
#define MENU_FONT_SIZE 50
//�����ຯ��
int menu(const char* menu_list[], int menu_length, const char* quit_key, bool alpha = false,int stop = 500,bool case_sensitive = false,const char * prompt ="[��ѡ��:]",
	const char* caution = "����������", const char* header=horizontal_line, const char* bottom=horizontal_line,	int menu_screen_width = MENU_SCREEN_WIDTH,
	int menu_screen_height=MENU_SCREEN_HEIGHT,const char*menu_font_family= MENU_FONT_FAMILY,int menu_font_size=MENU_FONT_SIZE);
void to_be_continued(int x, int y, const char* prompt = "���س�������", const char* key = "\10", int bg_color = COLOR_BLACK, int fg_color = COLOR_WHITE);
void enter_to_continue(int x, int y, const int bg_color=COLOR_BLACK, int fg_color=COLOR_WHITE, const char* prompt="���س�������", char key='\r');
int wait_arrow_key();
int get_arrow_key();


