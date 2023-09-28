#include<iostream>
#include<Windows.h>
#include<conio.h>
#include"../include/cmd_console_tools.h"
#include"../include/menu.h"
#include"90-02-b1.h"
//=====================================================
//函 数 名:make_board
//功能描述:制作用于模拟游戏的矩阵
//输入参数:
//返 回 值:
//说    明:
//=====================================================
void make_board(int matrix[MAX_BOARD_HEIGHT][MAX_BOARD_WIDTH], const int VERTICAL_BLOCK_NUM, const int HORIZONTAL_BLOCK_NUM)
{
	for (int i = 0; i < MAX_BOARD_HEIGHT; i++)
		for (int j = 0; j < MAX_BOARD_WIDTH; j++)
			matrix[i][j] = -1;
	for (int i = 0; i < BOARD_TOP_WIDTH + VERTICAL_BLOCK_NUM; i++)
		for (int j = BOARD_SIDE_WIDTH; j < BOARD_SIDE_WIDTH + HORIZONTAL_BLOCK_NUM; j++)
			matrix[i][j] = 0;
	return;
}
//=====================================================
//函 数 名:from_index_to_coordinate
//功能描述:将模拟数组的绝对指标转化为屏幕上的绝对坐标
//输入参数:模拟数组的绝对指标
//返 回 值:
//说    明:
//=====================================================
struct point from_index_to_coordinate(int x, int y)
{
	return  linear_transformation(x - BOARD_SIDE_WIDTH, y - BOARD_TOP_WIDTH, BLOCK_WIDTH, 0, 0, BLOCK_HEIGHT, GAMEBOARD_X + GAMEBOARD_SIDE_WIDTH, GAMEBOARD_Y + 1);
}
//=====================================================
//函 数 名:print_block
//功能描述:打印方块
//输入参数:方块对象
//返 回 值:
//说    明:超出顶部部分不打印
//=====================================================
void print_block(struct Block block)
{
	const char* block_list[] = BLOCK;
	for (int i = 0; i < block.index_num; i++) {
		int abs_x = block.abs_index.x, abs_y = block.abs_index.y;
		int rel_x = block.rel_index[i].x, rel_y = block.rel_index[i].y;
		int x = abs_x + rel_x, y = abs_y + rel_y;
		if (y < BOARD_TOP_WIDTH)
			continue;
		struct point point = from_index_to_coordinate(x, y);
		make_block(point.x, point.y, block_list, 3, block.color, BLOCK_FRAME_COLOR);
	}
}
//=====================================================
//函 数 名:valid_move
//功能描述:检查方块能否进行某一操作
//输入参数:方块形状编号,游戏矩阵,操作代码,1为旋转,2为下落3为左移,4为右移
//返 回 值:1为可以,0为不可以
//说    明:不检查游戏是否结束,结束下落的原因一定是执行下落的操作,而非平移等操作
//=====================================================
int valid_move(struct Block block, int(*board)[MAX_BOARD_WIDTH], int opt = 2)
{
	int abs_x = block.abs_index.x, abs_y = block.abs_index.y;
	if (opt == 2) {
		abs_y++;
		for (int i = 0; i < block.index_num; i++) {
			if (board[block.rel_index[i].y + abs_y][block.rel_index[i].x + abs_x])
				return 0;
		}
	}
	else if (opt == 1) {
		for (int i = 0; i < block.index_num; i++) {
			struct point point = counterclockwise_rotate(block.rel_index[i].x, block.rel_index[i].y);
			if (board[abs_y + point.y][abs_x + point.x])
				return 0;
		}
	}
	else if (opt == 4 || opt == 3) {
		int direction = 1;
		if (opt == 3)
			direction = -1;
		abs_x += direction;
		for (int i = 0; i < block.index_num; i++) {
			if (board[block.rel_index[i].y + abs_y][block.rel_index[i].x + abs_x])
				return 0;
		}
	}
	return 1;
}
//=====================================================
//函 数 名:erase_remain_block
//功能描述:消除方块变化后,如下落一格,或旋转,之前方块的残留部分
//输入参数:方块形状编号,游戏矩阵,方块的变化代码,1为旋转,2为下落3为左移,4为右移
//返 回 值:若erase_list_block中坐标为-1,则说明无需消除
//说    明:该游戏中方块只能逆时针旋转,返回的是绝对指标
//=====================================================
void get_erase_list(struct Block block, int(*abs_erase_list)[2], int opt = 2)
{
	if (opt == 2) {
		for (int i = 0; i < block.index_num; i++) {
			abs_erase_list[i][0] = block.rel_index[i].x + block.abs_index.x;
			abs_erase_list[i][1] = block.rel_index[i].y + block.abs_index.y - 1;
		}
	}
	else if (opt == 3) {
		for (int i = 0; i < block.index_num; i++) {
			abs_erase_list[i][0] = block.rel_index[i].x + block.abs_index.x + 1;
			abs_erase_list[i][1] = block.rel_index[i].y + block.abs_index.y;
		}
	}
	else if (opt == 4) {
		for (int i = 0; i < block.index_num; i++) {
			abs_erase_list[i][0] = block.rel_index[i].x + block.abs_index.x - 1;
			abs_erase_list[i][1] = block.rel_index[i].y + block.abs_index.y;
		}
	}
	else if (opt == 1) {
		for (int i = 0; i < block.index_num; i++) {
			abs_erase_list[i][0] = clockwise_rotate(block.rel_index[i].x, block.rel_index[i].y).x + block.abs_index.x;
			abs_erase_list[i][1] = clockwise_rotate(block.rel_index[i].x, block.rel_index[i].y).y + block.abs_index.y;
		}
	}
	for (int i = 0; i < block.index_num; i++) {
		for (int j = 0; j < block.index_num; j++) {
			if (abs_erase_list[j][0] == (block.rel_index[i].x + block.abs_index.x) && abs_erase_list[j][1] == (block.rel_index[i].y + block.abs_index.y))
				abs_erase_list[j][0] = abs_erase_list[j][1] = -1;
		}
	}
	return;
}
//=====================================================
//函 数 名:erase_remain
//功能描述:消除方块移动后的残留部分
//输入参数:残留部分的指标集
//返 回 值:
//说    明:指标集为中的元素为-1,-1则说明跳过,同时如果y的范围在顶部,那么也跳过
//=====================================================
void erase_remain(int(*abs_erase_list)[2])
{
	for (int i = 0; i < MAX_REL_INDEX_NUM; i++) {
		if (abs_erase_list[i][1] < BOARD_TOP_WIDTH || (abs_erase_list[i][1] == -1 && abs_erase_list[i][0] == -1))
			continue;
		struct point point = from_index_to_coordinate(abs_erase_list[i][0], abs_erase_list[i][1]);
		make_colorblock(point.x, point.y, BLOCK_WIDTH, BLOCK_HEIGHT, GAMEBOARD_COLOR);
	}
	return;
}
//=====================================================
//函 数 名:rotate_and_print
//功能描述:打印旋转后的方块
//输入参数:方块
//返 回 值:
//说    明:不检查是否合法
//=====================================================
void rotate_and_print(struct Block* block)
{
	for (int i = 0; i < block->index_num; i++) {
		int temp_x = block->rel_index[i].x;
		int temp_y = block->rel_index[i].y;
		struct point point = counterclockwise_rotate(temp_x, temp_y);
		block->rel_index[i].x = point.x;
		block->rel_index[i].y = point.y;
	}
	print_block(*block);
	int abs_erase_list[MAX_REL_INDEX_NUM][2];
	for (int i = 0; i < MAX_REL_INDEX_NUM; i++)
		abs_erase_list[i][0] = abs_erase_list[i][1] = -1;
	get_erase_list(*block, abs_erase_list, 1);
	erase_remain(abs_erase_list);
	return;
}
//=====================================================
//函 数 名:horizontal_move
//功能描述:左右平移并打印
//输入参数:方块,方向
//返 回 值:
//说    明:不检查是否合法,右为1,左为-1
//=====================================================
void horizontal_move(struct Block* block, int direction = 1)
{
	block->abs_index.x += direction;
	print_block(*block);
	int abs_erase_list[MAX_REL_INDEX_NUM][2];
	for (int i = 0; i < MAX_REL_INDEX_NUM; i++)
		abs_erase_list[i][0] = abs_erase_list[i][1] = -1;
	if (direction == 1)
		get_erase_list(*block, abs_erase_list, 4);
	else
		get_erase_list(*block, abs_erase_list, 3);
	erase_remain(abs_erase_list);
	return;
}
//=====================================================
//函 数 名:other_opt
//功能描述:检查平移和旋转操作是否合法,若合法则执行
//输入参数:方块,游戏矩阵,操作代码
//返 回 值:改变后的方块
//说    明:不检查游戏是否结束,结束下落的原因一定是执行下落的操作,而非平移等操作,1为旋转,2为下落3为左移,4为右移
//=====================================================
struct Block other_opt(struct Block block, int(*board)[MAX_BOARD_WIDTH], const int opt)
{
	if (valid_move(block, board, opt)) {
		switch (opt) {
			case 1:
				rotate_and_print(&block);
				break;
			case 3:
				horizontal_move(&block, -1);
				break;
			case 4:
				horizontal_move(&block, 1);
				break;
		}
	}
	return block;
}
//=====================================================
//函 数 名:fall
//功能描述:执行一个方块的下落,直到落到底部或者落到其他方块上
//输入参数:方块形状编号,游戏矩阵
//返 回 值:操作过后的方块
//说    明:不检查游戏是否结束,结束下落的原因一定是执行下落的操作,而非平移等操作
//=====================================================
void fall(struct Block* block, int(*board)[MAX_BOARD_WIDTH], const int speed, const int OPTION)
{
	long long previous = GetTickCount64(), now;
	int  arrow_key;
	while (1) {
		while (!_kbhit() || OPTION <= 3) {
			now = GetTickCount64();
			if (previous + speed - TIME_EPSILON <= now) {
				previous = now;
				//if(1){
					//Sleep(1000);
				if (valid_move(*block, board)) {
					block->abs_index.y++;
					print_block(*block);
					int abs_erase_list[MAX_REL_INDEX_NUM][2];
					for (int i = 0; i < MAX_REL_INDEX_NUM; i++)
						abs_erase_list[i][0] = abs_erase_list[i][1] = -1;
					get_erase_list(*block, abs_erase_list);
					erase_remain(abs_erase_list);
				}
				else
					return;
			}
		}
		if (arrow_key = get_arrow_key()) {
			if (arrow_key == 2) {
				previous = GetTickCount64();
				if (valid_move(*block, board)) {
					block->abs_index.y++;
					print_block(*block);
					int abs_erase_list[MAX_REL_INDEX_NUM][2];
					for (int i = 0; i < MAX_REL_INDEX_NUM; i++)
						abs_erase_list[i][0] = abs_erase_list[i][1] = -1;
					get_erase_list(*block, abs_erase_list);
					erase_remain(abs_erase_list);
				}
				else
					return;
			}
			else if (OPTION >= 5)
				*block = other_opt(*block, board, arrow_key);
		}
	}
	return;
}
//=====================================================
//函 数 名:game_continue
//功能描述:检查游戏是否结束
//输入参数:游戏矩阵
//返 回 值:1为游戏继续,0为游戏结束
//说    明:
//=====================================================
int game_continue(int(*board)[MAX_BOARD_WIDTH], struct Block block)
{
	for (int i = 0; i < BOARD_TOP_WIDTH; i++) {
		for (int j = BOARD_SIDE_WIDTH; j < MAX_HORIZONTAL_BLOCK_NUM; j++)
			if (board[i][j] == 1)
				return 0;
	}
	return 1;
}
//=====================================================
//函 数 名:merge
//功能描述:将结束下落的方块合并至游戏板中
//输入参数:方块和游戏板
//返 回 值:
//说    明:
//=====================================================
void merge(struct Block block, int(*board)[MAX_BOARD_WIDTH])
{
	for (int i = 0; i < block.index_num; i++) {
		board[block.abs_index.y + block.rel_index[i].y][block.abs_index.x + block.rel_index[i].x] = block.color;
	}
	return;
}
//=====================================================
//函 数 名:pop_and_fall
//功能描述:进行消除操作,并在图形中显示
//输入参数:游戏矩阵
//返 回 值:消除行数
//说    明:没有连锁反应,只需每一行检查一边即可
//=====================================================
int pop_and_fall(int(*board)[MAX_BOARD_WIDTH])
{
	int sum = 0;
	for (int i = 0; i < MAX_BOARD_HEIGHT; i++) {
		int pop = 1,pos =0;
		for (int j = 0; j < MAX_BOARD_WIDTH; j++) {
			if (!board[i][j])
				pop = 0;
			if (board[i][j] > 0)
				pos = 1;
		}
		if (pop&&pos) {
			for (int j = 0; j < MAX_BOARD_HEIGHT; j++)
				if (board[i][j] >0) {
					board[i][j] = 0;
					struct point point = from_index_to_coordinate(j,i);
					make_colorblock(point.x, point.y, BLOCK_WIDTH, BLOCK_HEIGHT, GAMEBOARD_COLOR);
				}
			sum++;
		}
	}
	if (!sum)
		return 0;
	for (int i = MAX_BOARD_HEIGHT - 1; i >= 0; i--) {
		for (int j = i; j <= MAX_BOARD_HEIGHT- 1; j++) {
			int this_empty = 1, under_empty = 1;
			for (int k = 0; k < MAX_BOARD_WIDTH; k++) {
				if ( board[j][k]>0)
					this_empty = 0;
				if ( board[j + 1][k]>0)
					under_empty = 0;
				if (!this_empty && under_empty) {
					for (int l = 0; l < MAX_BOARD_WIDTH; l++)
						if (board[j][l] != -1 && board[j][l]) {
							board[j + 1][l] = board[j][l];
							board[j][l] = 0;
							struct point point = from_index_to_coordinate( l,j+1);
							const char* block[] = BLOCK;
							make_block(point.x, point.y, block, 3, board[j+1][l], BLOCK_FRAME_COLOR);
							make_colorblock(point.x, point.y - BLOCK_HEIGHT, BLOCK_WIDTH, BLOCK_HEIGHT, GAMEBOARD_COLOR);
						}
					break;
				}
			}
		}
	}
	return sum;
}
//=====================================================
//函 数 名:update_info
//功能描述:更新得分板上的信息
//输入参数:
//返 回 值:
//说    明:
//=====================================================
void update_info(int erase_sum, int next_num)
{
	return;
}


