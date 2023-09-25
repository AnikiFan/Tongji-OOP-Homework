#include<iostream>
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
int(*make_board(void))[BOARD_WIDTH]
{
	int matrix[BOARD_HEIGHT][BOARD_WIDTH];
	for (int i = 0; i < BOARD_HEIGHT; i++)
		for (int j = 0; j < BOARD_WIDTH; j++)
			matrix[i][j] = -1;
	for (int i = BOARD_TOP_WIDTH; i < BOARD_HEIGHT; i++)
		for (int j = BOARD_SIDE_WIDTH; j < BOARD_SIDE_WIDTH + HORIZONTAL_BLOCK_NUM; j++)
			matrix[i][j] = 0;
	return matrix;
}
//=====================================================
//函 数 名:fall
//功能描述:执行一个方块的下落,直到落到底部或者落到其他方块上
//输入参数:方块形状编号,游戏矩阵
//返 回 值:
//说    明:不检查游戏是否结束
//=====================================================
struct Block fall(int num, int(*board)[BOARD_WIDTH]);
//=====================================================
//函 数 名:game_continue
//功能描述:检查游戏是否结束
//输入参数:游戏矩阵
//返 回 值:1为游戏继续,0为游戏结束
//说    明:
//=====================================================
int game_continue(int(*board)[BOARD_WIDTH]);
//=====================================================
//函 数 名:pop
//功能描述:进行消除操作,并在图形中显示
//输入参数:游戏矩阵
//返 回 值:消除行数
//说    明:没有连锁反应,只需每一行检查一边即可
//=====================================================
int pop(int(*board)[BOARD_WIDTH]);
//=====================================================
//函 数 名:update_info
//功能描述:更新得分板上的信息
//输入参数:
//返 回 值:
//说    明:
//=====================================================
void update_info(int erase_sum, int next_num);


