#pragma once

#define horizontal_line  "--------------------------------------------" 
#define MENU_SCREEN_WIDTH 45
#define TEXTLENGTH (2*MENU_SCREEN_WIDTH)
#define MENU_SCREEN_HEIGHT 12
#define MENU_FONT_FAMILY "宋体"
#define MENU_FONT_SIZE 20
//交互类函数
int menu(const char* menu_list[], int menu_length, const char* quit_key, bool alpha = false,int stop = 500,bool case_sensitive = false,const char * prompt ="[请选择:]",
	const char* caution = "请重新输入", const char* header=horizontal_line, const char* bottom=horizontal_line,	int menu_screen_width = MENU_SCREEN_WIDTH,
	int menu_screen_height=MENU_SCREEN_HEIGHT,const char*menu_font_family= MENU_FONT_FAMILY,int menu_font_size=MENU_FONT_SIZE);
void to_be_continued(int x, int y, const char* prompt = "按回车键继续", const char* key = "\10", int bg_color = COLOR_BLACK, int fg_color = COLOR_WHITE);
void enter_to_continue(int x, int y, const int bg_color=COLOR_BLACK, int fg_color=COLOR_WHITE, const char* prompt="按回车键继续", char key='\r');
//数值运算类函数
struct point {
	int x;
	int y;
};
int between(double num, double x, double y);
int case_insensitive_char_compare(char x, char y);
int get_next_num(int n, const bool new_seed = false, const unsigned int seed = 0);
struct point coordinate_transformation(int x, int y, int (*x_transformation)(int, int), int (*y_transformation)(int, int));
struct point coordinate_transpose(int x, int y);
struct point linear_transformation(int x, int y, int a11 = 1, int a12 = 0, int a21 = 0, int a22 = 1, int d1 = 0, int d2 = 0);
struct point clockwise_rotate(int x, int y, int axis_x=0, int axis_y=0);
struct point counterclockwise_rotate(int x, int y, int axis_x = 0, int axis_y = 0);
struct point central_symmetry(int x, int y, int axis_x = 0, int axis_y = 0);
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
void make_block(int x, int y ,const char* row[], int row_num, int bg_color = COLOR_BLACK, int fg_color = COLOR_WHITE);
//字符串类函数
int begin_with(const char* x, const char* y, int case_sensitive = 0);
//数组类函数
void matrix_iteration(int* p, int row_num, int col_num, void(*manipulation)(int, int, int));
void list_iteration(int* p, int list_size, void(*manipulation)(int, int));
//调试类函数
void check_element(int* p, int row_num, int col_num);

