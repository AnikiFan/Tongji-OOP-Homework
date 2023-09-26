#include<iostream>
#include<Windows.h>
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
void make_board(int matrix[BOARD_HEIGHT][BOARD_WIDTH])
{
	for (int i = 0; i < BOARD_HEIGHT; i++)
		for (int j = 0; j < BOARD_WIDTH; j++)
			matrix[i][j] = -1;
	for (int i =0; i < BOARD_TOP_WIDTH+VERTICAL_BLOCK_NUM; i++)
		for (int j = BOARD_SIDE_WIDTH; j < BOARD_SIDE_WIDTH + HORIZONTAL_BLOCK_NUM; j++)
			matrix[i][j] = 0;
	return ;
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
		int rel_x = block.rel_index[i].x,rel_y =block.rel_index[i].y;
		int x = abs_x + rel_x, y = abs_y + rel_y;
		if (y < 0)
			continue;
		struct point point= linear_transformation(x, y, BLOCK_WIDTH, 0, BLOCK_HEIGHT, 0, GAMEBOARD_X + GAMEBOARD_WIDTH, GAMEBOARD_Y + 1);
		make_block(point.x, point.y, block_list, 3, block.color, BLOCK_FRAME_COLOR);
	}
}
//=====================================================
//函 数 名:valid_fall
//功能描述:检查方块能否下移一格
//输入参数:方块形状编号,游戏矩阵
//返 回 值:
//说    明:不检查游戏是否结束,结束下落的原因一定是执行下落的操作,而非平移等操作
//=====================================================
//=====================================================
//函 数 名:fall
//功能描述:执行一个方块的下落,直到落到底部或者落到其他方块上
//输入参数:方块形状编号,游戏矩阵
//返 回 值:
//说    明:不检查游戏是否结束,结束下落的原因一定是执行下落的操作,而非平移等操作
//=====================================================
void fall(struct Block * block, int(*board)[BOARD_WIDTH],int speed)
{
	long long previous = GetTickCount64(),now;
	while (1) {
		now = GetTickCount64();
		if (previous - TIME_EPSILON <= now && now <= previous + TIME_EPSILON) {
			previous = now;
			block->abs_index.y++;
			if (valid_fall()) {
				print_block(*block);
				erase_remain_block();
			}
			else
				return;
			//TODO:要编写一个函数来消去之前的部分
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
int game_continue(int(*board)[BOARD_WIDTH])
{
	return 0;
}
//=====================================================
//函 数 名:merge
//功能描述:将结束下落的方块合并至游戏板中
//输入参数:方块和游戏板
//返 回 值:
//说    明:
//=====================================================
void merge(struct Block block,int(*board)[BOARD_WIDTH])
{
	return ;
}
//=====================================================
//函 数 名:pop
//功能描述:进行消除操作,并在图形中显示
//输入参数:游戏矩阵
//返 回 值:消除行数
//说    明:没有连锁反应,只需每一行检查一边即可
//=====================================================
int pop(int(*board)[BOARD_WIDTH])
{
	return 0;
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


