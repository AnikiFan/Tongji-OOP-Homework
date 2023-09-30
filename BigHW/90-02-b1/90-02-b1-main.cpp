/* 2254298 大数据 范潇 */
#include <iostream>
#include<windows.h>
#include "../include/cmd_console_tools.h"
#include "../include/common_interact.h"
#include"../include/common_calc.h"
#include"../include/common_make.h"
#include"90-02-b1.h"
using namespace std;
void game(const int VERTICAL_BLOCK_NUM, const int HORIZONTAL_BLOCK_NUM, const int OPTION)
{
	int erase_num = 0, erase_sum = 0;
	int score = 0;
	int board[MAX_BOARD_HEIGHT][MAX_BOARD_WIDTH];
	make_gameboard(board, VERTICAL_BLOCK_NUM, HORIZONTAL_BLOCK_NUM);
	int num, next_num;
	int speed = INITIAL_SPEED;
	//speed = 200;
	num = get_next_num(NUM_BOUND,true,(unsigned int)time(0));
	//测试用
	//num = 1;
	//测试用
	while (1) {
		if (score / 15 >= 8)
			speed = 300;
		else
			speed = INITIAL_SPEED - 100 * (score / 15);
		next_num = get_next_num(NUM_BOUND);
		if (OPTION == 6) {
			update_info(erase_sum, next_num, score, speed, HORIZONTAL_BLOCK_NUM);
			showcase(next_num,HORIZONTAL_BLOCK_NUM);
		}
		int index_num_list[NUM_BOUND] = INDEX_NUM_LIST, block_color_list[NUM_BOUND] = BLOCK_COLOR_LIST;
		struct Index initiate_index { INITIATE_INDEX }, rel_index_list[NUM_BOUND][MAX_REL_INDEX_NUM] = REL_INDEX_LIST;
		struct Block block { initiate_index, index_num_list[num], rel_index_list[num], block_color_list[num] };
		fall(&block, board, speed, OPTION);
		if (OPTION == 2) {
			enter_to_continue(PROMPT_X, PROMPT_Y);
			return;
		}
		//system("pause");
		merge(block, board);
		if (!game_continue(board, block))
			break;
		erase_num = pop_and_fall(board);
		if (erase_num) {
			erase_sum += erase_num;
			switch (erase_num) {
			case 1:
				score += 1;
				break;
			case 2:
				score += 3;
				break;
			case 3:
				score += 6;
				break;
			case 4:
				score += 10;
				break;
			case 5:
				score += 15;
				break;
			}
		}
		num = next_num;
		//测试用
		//num = 1;
		//测试用
	}
	return;
}
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
		cct_setfontsize(CONSOLE_FONT_FAMILY, CONSOLE_FONT_SIZE);
		cct_setconsoleborder(CONSOLE_WIDTH, CONSOLE_HEIGHT, CONSOLE_WIDTH, CONSOLE_HEIGHT);
		make_board(GAMEBOARD_X, GAMEBOARD_Y, HORIZONTAL_BLOCK_NUM*BLOCK_WIDTH, VERTICAL_BLOCK_NUM*BLOCK_HEIGHT, 1, 1, false, GAMEBOARD_COLOR,
			GAMEBOARD_SIDE_COLOR, nullptr, GAMEBOARD_SIDE_WIDTH, true, GAMEBOARD_SHADOW_WIDTH, GAMEBOARD_SHADOW_COLOR);
		make_board(SCOREBOARD_X, SCOREBOARD_Y, SCOREBOARD_WIDTH, SCOREBOARD_HEIGHT, 1, 1, false, SCOREBOARD_COLOR,
			SCOREBOARD_SIDE_COLOR, nullptr, SCOREBOARD_SIDE_WIDTH, true, SCOREBOARD_SHADOW_WIDTH, SCOREBOARD_SHADOW_COLOR);
		make_list(SCOREBOARD_INFO_X, SCOREBOARD_INFO_Y, scoreboard_info_list, SCOREBOARD_INFO_LENGTH,
			SCOREBOARD_INFO_INTERVAL, SCOREBOARD_COLOR, SCOREBOARD_INFO_COLOR);
		make_board(SHOWCASE_X, SHOWCASE_Y, BLOCK_WIDTH * 3, BLOCK_HEIGHT * 5, 1, 1, false, SHOWCASE_COLOR, SHOWCASE_SIDE_COLOR, nullptr,
			2, true, 1, SHOWCASE_SHADOW_COLOR);
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
