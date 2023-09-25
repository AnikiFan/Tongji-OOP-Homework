#pragma once

#define TEXTLENGTH 50 
#define horizontal_line  "--------------------------------------------" 
//交互类函数
//int menu(const char* menu_list[], int menu_length, const char* quit_key, bool alpha = false, bool case_sensitive = false,
	//int delay = 50, const char* prompt = "请重新输入", const char* header = horizontal_line, const char* bottom = horizontal_line);
int menu(const char* menu_list[], int menu_length, const char* quit_key, bool alpha = false,int stop = 500,bool case_sensitive = false, 
	const char* prompt = "请重新输入", const char* header=horizontal_line, const char* bottom=horizontal_line);
void to_be_continued(int x, int y, const char* prompt = "按回车键继续", const char* key = "\10", int bg_color = COLOR_BLACK, int fg_color = COLOR_WHITE);
void enter_to_continue(int x, int y, const int bg_color=COLOR_BLACK, int fg_color=COLOR_WHITE, const char* prompt="按回车键继续", char key='\r');
//数值运算类函数
int between(double num, double x, double y);
int case_insensitive_char_compare(char x, char y);
int get_next_num(int n, const bool new_seed = false, const unsigned int seed = 0);
//打印类函数
void clear_and_prompt(int x, int y, int dx, int dy, const char* prompt, int whitespace_length = TEXTLENGTH);
void erase_prompt(int dx, int dy, int bg_color = COLOR_BLACK, int fg_color = COLOR_WHITE, int erase_length = TEXTLENGTH);
void make_colorblock(int x, int y, int width, int height, int color = COLOR_WHITE);
void make_frame(int x, int y, int width, int height, const char* side_list[] = nullptr,
	int side_width = 2, int bg_color = COLOR_BLACK, int fg_color = COLOR_WHITE);
void make_board(int x, int y, int block_width, int block_height, int vertical_block_num = 1, int horizontal_block_num = 1,
	bool inner_side = false,  int board_color = COLOR_WHITE,int side_color = COLOR_BLACK, const char* side_list[] = nullptr,
	int side_width = 2, bool shadow = false, int shadow_width = 2, int shadow_color = COLOR_CYAN);
void make_line(int x, int y, const char* fill, int n, bool horizontal = true, int bg_color = COLOR_BLACK, int fg_color = COLOR_WHITE);
void make_dotted_line(int x, int y, int coordinate_difference, int n, const char* dot,
	bool horizontal = true, int bg_color = COLOR_BLACK, int fg_color = COLOR_WHITE);
void make_lattice(int x, int y, int dx, int dy, int x_num, int y_num, const char* dot, int bg_color = COLOR_BLACK, int fg_color = COLOR_WHITE);
void make_list(int x, int y, const char* list[], int list_length, int dy=1, int bg_color=COLOR_BLACK, int fg_color=COLOR_WHITE);
//字符串类函数
int begin_with(const char* x, const char* y, int case_sensitive = 0);
