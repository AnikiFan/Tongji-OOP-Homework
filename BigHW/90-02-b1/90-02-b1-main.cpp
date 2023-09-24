/* 2254298 ´óÊý¾Ý ·¶äì */
#include <iostream>
#include<Windows.h>
#include "../include/cmd_console_tools.h"
#include "../include/menu.h"
#include"90-02-b1.h"
using namespace std;

int main()
{
	cct_setconsoleborder(CONSOLE_WIDTH, CONSOLE_HEIGHT, CONSOLE_BUFFER_WIDTH, CONSOLE_BUFFER_HEIGHT);
	cct_setfontsize(CONSOLE_FONT_FAMILY, CONSOLE_FONT_SIZE);
	while (1) {
		const char* menu_list[] = MENU_LIST,*scoreboard_info_list[] = SCOREBOARD_INFO_LIST;
		int option = menu(menu_list, MENU_LIST_LENGTH, QUIT_KEY, true);
		if (!option)
			break;
		cct_cls();
		make_board(GAMEBOARD_X, GAMEBOARD_Y, GAMEBOARD_WIDTH, GAMEBOARD_HEIGHT, 1, 1, false,
			GAMEBOARD_COLOR, GAMEBOARD_SIDE_COLOR, nullptr, GAMEBOARD_SIDE_WIDTH, true, GAMEBOARD_SHADOW_WIDTH, GAMEBOARD_SHADOW_COLOR);
		make_board(SCOREBOARD_X, SCOREBOARD_Y, SCOREBOARD_WIDTH, SCOREBOARD_HEIGHT, 1, 1, false,
			SCOREBOARD_COLOR, SCOREBOARD_SIDE_COLOR, nullptr, SCOREBOARD_SIDE_WIDTH, true, SCOREBOARD_SHADOW_WIDTH, SCOREBOARD_SIDE_COLOR);
		make_list(SCOREBOARD_INFO_X, SCOREBOARD_INFO_Y, scoreboard_info_list, SCOREBOARD_INFO_LENGTH,SCOREBOARD_INFO_INTERVAL,SCOREBOARD_COLOR,SCOREBOARD_INFO_COLOR);
		if (option == 1) {
			enter_to_continue(PROMPT_X, PROMPT_Y);
			continue;
		}

	}
	return 0;
}
