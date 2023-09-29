/* 2254298 大数据 范潇 */
#include <iostream>
#include<windows.h>
#include "../include/cmd_console_tools.h"
#include "../include/menu.h"
#include"90-02-b1.h"
using namespace std;

int main()
{
	cct_setconsoletitle(CONSOLE_TITLE);
	while (1) {
		const char* menu_list[] = MENU_LIST, * scoreboard_info_list[] = SCOREBOARD_INFO_LIST;
		const char* vertical_block_num_list[] = VERTICAL_BLOCK_NUM_LIST;
		const char* horizontal_block_num_list[] = HORIZONTAL_BLOCK_NUM_LIST;

		cct_setcursor(CURSOR_VISIBLE_NORMAL);

		const int OPTION = menu(menu_list, MENU_LIST_LENGTH, QUIT_KEY, true);
		if (!OPTION)
			break;
		const int VERTICAL_BLOCK_NUM = menu(vertical_block_num_list, 9, "Q", true, 500, false, "[请选择行数:]")+18;
		if (VERTICAL_BLOCK_NUM == 18)
			break;
		const int HORIZONTAL_BLOCK_NUM =9+3* menu(horizontal_block_num_list, 4, "Q", true, 500, false, "[请选择列数:]");
		if (HORIZONTAL_BLOCK_NUM == 9)
			break;

		cct_cls();
		cct_setconsoleborder(CONSOLE_WIDTH, CONSOLE_HEIGHT, CONSOLE_WIDTH, CONSOLE_HEIGHT);
		cct_setfontsize(CONSOLE_FONT_FAMILY, CONSOLE_FONT_SIZE);
		//cct_setfontsize(CONSOLE_FONT_FAMILY, 8);
		//Sleep(1000);
		make_board(GAMEBOARD_X, GAMEBOARD_Y, HORIZONTAL_BLOCK_NUM*BLOCK_WIDTH, VERTICAL_BLOCK_NUM*BLOCK_HEIGHT, 1, 1, false, GAMEBOARD_COLOR,
			GAMEBOARD_SIDE_COLOR, nullptr, GAMEBOARD_SIDE_WIDTH, true, GAMEBOARD_SHADOW_WIDTH, GAMEBOARD_SHADOW_COLOR);
		make_board(SCOREBOARD_X, SCOREBOARD_Y, SCOREBOARD_WIDTH, SCOREBOARD_HEIGHT, 1, 1, false, SCOREBOARD_COLOR,
			SCOREBOARD_SIDE_COLOR, nullptr, SCOREBOARD_SIDE_WIDTH, true, SCOREBOARD_SHADOW_WIDTH, SCOREBOARD_SIDE_COLOR);
		make_list(SCOREBOARD_INFO_X, SCOREBOARD_INFO_Y, scoreboard_info_list, SCOREBOARD_INFO_LENGTH,
			SCOREBOARD_INFO_INTERVAL, SCOREBOARD_COLOR, SCOREBOARD_INFO_COLOR);
		cct_setcursor(CURSOR_INVISIBLE);
		if (OPTION == 1) {
			enter_to_continue(PROMPT_X, PROMPT_Y);
			continue;
		}
		else {
			game(VERTICAL_BLOCK_NUM,HORIZONTAL_BLOCK_NUM,OPTION);
			enter_to_continue(PROMPT_X, PROMPT_Y);
			continue;
		}
	}
	return 0;
}
