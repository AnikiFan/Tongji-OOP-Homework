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
void make_board(int matrix[MAX_BOARD_HEIGHT][MAX_BOARD_WIDTH],const int VERTICAL_BLOCK_NUM,const int HORIZONTAL_BLOCK_NUM)
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
	return  linear_transformation(x-BOARD_SIDE_WIDTH, y-BOARD_TOP_WIDTH, BLOCK_WIDTH, 0,0, BLOCK_HEIGHT, GAMEBOARD_X + GAMEBOARD_SIDE_WIDTH, GAMEBOARD_Y + 1);
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
//函 数 名:valid_fall
//功能描述:检查方块能否下移一格
//输入参数:方块形状编号,游戏矩阵
//返 回 值:1为可以,0为不可以
//说    明:不检查游戏是否结束,结束下落的原因一定是执行下落的操作,而非平移等操作
//=====================================================
int valid_fall(struct Block block, int(*board)[MAX_BOARD_WIDTH])
{
	int abs_x = block.abs_index.x, abs_y = block.abs_index.y + 1;
	for (int i = 0; i < block.index_num; i++) {
		if (board[block.rel_index[i].y + abs_y][block.rel_index[i].x + abs_x])
			return 0;
	}
	return 1;
}
//=====================================================
//函 数 名:erase_remain_block
//功能描述:消除方块变化后,如下落一格,或旋转,之前方块的残留部分
//输入参数:方块形状编号,游戏矩阵,方块的变化
//返 回 值:若erase_list_block中坐标为-1,则说明无需消除
//说    明:该游戏中方块只能逆时针旋转,返回的是绝对指标
//=====================================================
void get_erase_list(struct Block block, int(*abs_erase_list)[2], int down = true, int left = false, int right = false, int rotate = false)
{
	if (down) {
		for (int i = 0; i < block.index_num; i++) {
			abs_erase_list[i][0] = block.rel_index[i].x + block.abs_index.x;
			abs_erase_list[i][1] = block.rel_index[i].y + block.abs_index.y-1;
		}
	}
	else if (left) {
		for (int i = 0; i < block.index_num; i++) {
			abs_erase_list[i][0] = block.rel_index[i].x + block.abs_index.x+1;
			abs_erase_list[i][1] = block.rel_index[i].y + block.abs_index.y;
		}
	}
	else if (right) {
		for (int i = 0; i < block.index_num; i++) {
			abs_erase_list[i][0] = block.rel_index[i].x + block.abs_index.x-1;
			abs_erase_list[i][1] = block.rel_index[i].y + block.abs_index.y;
		}
	}
	else if (rotate) {
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
		if (abs_erase_list[i][1] < BOARD_TOP_WIDTH||(abs_erase_list[i][1]==-1&&abs_erase_list[i][0]==-1))
			continue;
		struct point point = from_index_to_coordinate(abs_erase_list[i][0], abs_erase_list[i][1]);
		make_colorblock(point.x, point.y,BLOCK_WIDTH,BLOCK_HEIGHT,GAMEBOARD_COLOR);
	}
	return;
}
//=====================================================
//函 数 名:fall
//功能描述:执行一个方块的下落,直到落到底部或者落到其他方块上
//输入参数:方块形状编号,游戏矩阵
//返 回 值:
//说    明:不检查游戏是否结束,结束下落的原因一定是执行下落的操作,而非平移等操作
//=====================================================
void fall(struct Block* block, int(*board)[MAX_BOARD_WIDTH], int speed)
{
	long long previous = GetTickCount64(), now;
	while (1) {
		now = GetTickCount64();
		if (previous +speed - TIME_EPSILON <= now && now <= previous+speed + TIME_EPSILON) {
			previous = now;
		//if(1){
			//Sleep(1000);
			if (valid_fall(*block, board)) {
				block->abs_index.y++;
				print_block(*block);
				int abs_erase_list[MAX_REL_INDEX_NUM][2];
				for (int i = 0; i < MAX_REL_INDEX_NUM; i++)
					abs_erase_list[i][0] = abs_erase_list[i][1] = -1;
				get_erase_list(*block,abs_erase_list);
				erase_remain(abs_erase_list);
			}
			else
				return;
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
int game_continue(int(*board)[MAX_BOARD_WIDTH])
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
void merge(struct Block block, int(*board)[MAX_BOARD_WIDTH])
{
	return;
}
//=====================================================
//函 数 名:pop
//功能描述:进行消除操作,并在图形中显示
//输入参数:游戏矩阵
//返 回 值:消除行数
//说    明:没有连锁反应,只需每一行检查一边即可
//=====================================================
int pop(int(*board)[MAX_BOARD_WIDTH])
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


