#include<iostream>
#include"../include/cmd_console_tools.h"
#include"../include/menu.h"
#include"90-02-b1.h"
void game(const int VERTICAL_BLOCK_NUM, const int HORIZONTAL_BLOCK_NUM, const int OPTION)
{
	int erase_num = 0, erase_sum = 0;
	int score = 0;
	int board[MAX_BOARD_HEIGHT][MAX_BOARD_WIDTH];
	make_board(board, VERTICAL_BLOCK_NUM, HORIZONTAL_BLOCK_NUM);
	int num, next_num;
	int speed = INITIAL_SPEED;
	//speed = 200;
	num = get_next_num(NUM_BOUND);
	//≤‚ ‘”√
	num = 1;
	//≤‚ ‘”√
	while (1) {
		if (score / 15 >= 8)
			speed = 300;
		else
			speed = INITIAL_SPEED - 100 * (score / 15);
		next_num = get_next_num(NUM_BOUND);
		if (OPTION == 6)
			update_info(erase_sum, next_num, score,speed,HORIZONTAL_BLOCK_NUM);
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
		//≤‚ ‘”√
		num = 1;
		//≤‚ ‘”√
	}
	return;
}
