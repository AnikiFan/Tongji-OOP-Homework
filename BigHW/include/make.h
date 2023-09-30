#pragma once
#include"cmd_console_tools.h"
#define MENU_SCREEN_WIDTH 45
#define TEXTLENGTH (2*MENU_SCREEN_WIDTH)
//´òÓ¡Ààº¯Êý
void clear_and_prompt(int x, int y, int dx, int dy, const char* prompt, int whitespace_length = TEXTLENGTH);
void erase_prompt(int dx, int dy, int bg_color = COLOR_BLACK, int fg_color = COLOR_WHITE, int erase_length = TEXTLENGTH);
void make_colorblock(int x, int y, int width, int height, int color = COLOR_WHITE);
void make_frame(int x, int y, int width, int height, const char* side_list[] = nullptr,
	int side_width = 2, int bg_color = COLOR_BLACK, int fg_color = COLOR_WHITE);
void make_board(int x, int y, int block_width, int block_height, int vertical_block_num = 1, int horizontal_block_num = 1,
	bool inner_side = false, int board_color = COLOR_WHITE, int side_color = COLOR_BLACK, const char* side_list[] = nullptr,
	int side_width = 2, bool shadow = false, int shadow_width = 1, int shadow_color = COLOR_CYAN);
void make_line(int x, int y, const char* fill, int n, bool horizontal = true, int bg_color = COLOR_BLACK, int fg_color = COLOR_WHITE);
void make_dotted_line(int x, int y, int coordinate_difference, int n, const char* dot,
	bool horizontal = true, int bg_color = COLOR_BLACK, int fg_color = COLOR_WHITE);
void make_lattice(int x, int y, int dx, int dy, int x_num, int y_num, const char* dot, int bg_color = COLOR_BLACK, int fg_color = COLOR_WHITE);
void make_list(int x, int y, const char* list[], int list_length, int dy = 1, int bg_color = COLOR_BLACK, int fg_color = COLOR_WHITE);
void make_block(int x, int y, const char* row[], int row_num, int bg_color = COLOR_BLACK, int fg_color = COLOR_WHITE);