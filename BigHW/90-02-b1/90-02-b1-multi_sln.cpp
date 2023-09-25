#include<iostream>
#include"../include/cmd_console_tools.h"
#include"../include/menu.h"
#include"90-02-b1.h"
void game(void)
{
	int erase_num = 0,erase_sum = 0;
	int(* board)[BOARD_WIDTH] = make_board();
	int num, next_num;
	next_num = get_next_num(NUM_BOUND);
	while (1) {
		num = next_num;
		next_num = get_next_num(NUM_BOUND);
		Block block = fall(num, board);
		if (!game_continue(board))
			break;
		merge(block, board);
		erase_num = pop(board);
		erase_sum += erase_num;
		update_info(erase_sum, next_num);
	}
	return;
}
