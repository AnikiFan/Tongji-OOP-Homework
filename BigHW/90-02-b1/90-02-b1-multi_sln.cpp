#include<iostream>
#include"../include/cmd_console_tools.h"
#include"../include/menu.h"
#include"90-02-b1.h"
void game(void)
{
	int erase_num = 0, erase_sum = 0;
	int board[BOARD_HEIGHT][BOARD_WIDTH];
	make_board(board);
	int num, next_num;
	int speed = INITIAL_SPEED;
	next_num = get_next_num(NUM_BOUND);
	while (1) {
		num = next_num;
		next_num = get_next_num(NUM_BOUND);
		int index_num_list[NUM_BOUND] = INDEX_NUM_LIST,block_color_list[NUM_BOUND]=BLOCK_COLOR_LIST;
		struct Index initiate_index { INITIATE_INDEX }, rel_index_list[NUM_BOUND][MAX_REL_INDEX_NUM] = REL_INDEX_LIST;
		struct Block block { initiate_index, index_num_list[num], rel_index_list[num],block_color_list[num] };
		fall(&block, board,speed);
		//system("pause");
		//if (!game_continue(board))
			//break;
		//merge(block, board);
		//erase_num = pop(board);
		//erase_sum += erase_num;
		//update_info(erase_sum, next_num);
	}
	return;
}
