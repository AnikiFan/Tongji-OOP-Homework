#include<iostream>
#include<Windows.h>
#include<conio.h>
#include"../include/cmd_console_tools.h"
#include"../include/menu.h"
#include"90-02-b1.h"
//=====================================================
//�� �� ��:make_board
//��������:��������ģ����Ϸ�ľ���
//�������:
//�� �� ֵ:
//˵    ��:
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
//�� �� ��:from_index_to_coordinate
//��������:��ģ������ľ���ָ��ת��Ϊ��Ļ�ϵľ�������
//�������:ģ������ľ���ָ��
//�� �� ֵ:
//˵    ��:
//=====================================================
struct point from_index_to_coordinate(int x, int y)
{
	return  linear_transformation(x - BOARD_SIDE_WIDTH, y - BOARD_TOP_WIDTH, BLOCK_WIDTH, 0, 0, BLOCK_HEIGHT, GAMEBOARD_X + GAMEBOARD_SIDE_WIDTH, GAMEBOARD_Y + 1);
}
//=====================================================
//�� �� ��:print_block
//��������:��ӡ����
//�������:�������
//�� �� ֵ:
//˵    ��:�����������ֲ���ӡ
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
//�� �� ��:valid_move
//��������:��鷽���ܷ����ĳһ����
//�������:������״���,��Ϸ����,��������,1Ϊ��ת,2Ϊ����3Ϊ����,4Ϊ����
//�� �� ֵ:1Ϊ����,0Ϊ������
//˵    ��:�������Ϸ�Ƿ����,���������ԭ��һ����ִ������Ĳ���,����ƽ�ƵȲ���
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
//�� �� ��:erase_remain_block
//��������:��������仯��,������һ��,����ת,֮ǰ����Ĳ�������
//�������:������״���,��Ϸ����,����ı仯����,1Ϊ��ת,2Ϊ����3Ϊ����,4Ϊ����
//�� �� ֵ:��erase_list_block������Ϊ-1,��˵����������
//˵    ��:����Ϸ�з���ֻ����ʱ����ת,���ص��Ǿ���ָ��
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
//�� �� ��:erase_remain
//��������:���������ƶ���Ĳ�������
//�������:�������ֵ�ָ�꼯
//�� �� ֵ:
//˵    ��:ָ�꼯Ϊ�е�Ԫ��Ϊ-1,-1��˵������,ͬʱ���y�ķ�Χ�ڶ���,��ôҲ����
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
//�� �� ��:rotate_and_print
//��������:��ӡ��ת��ķ���
//�������:����
//�� �� ֵ:
//˵    ��:������Ƿ�Ϸ�
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
//�� �� ��:horizontal_move
//��������:����ƽ�Ʋ���ӡ
//�������:����,����
//�� �� ֵ:
//˵    ��:������Ƿ�Ϸ�,��Ϊ1,��Ϊ-1
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
//�� �� ��:other_opt
//��������:���ƽ�ƺ���ת�����Ƿ�Ϸ�,���Ϸ���ִ��
//�������:����,��Ϸ����,��������
//�� �� ֵ:�ı��ķ���
//˵    ��:�������Ϸ�Ƿ����,���������ԭ��һ����ִ������Ĳ���,����ƽ�ƵȲ���,1Ϊ��ת,2Ϊ����3Ϊ����,4Ϊ����
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
//�� �� ��:fall
//��������:ִ��һ�����������,ֱ���䵽�ײ������䵽����������
//�������:������״���,��Ϸ����
//�� �� ֵ:��������ķ���
//˵    ��:�������Ϸ�Ƿ����,���������ԭ��һ����ִ������Ĳ���,����ƽ�ƵȲ���
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
//�� �� ��:game_continue
//��������:�����Ϸ�Ƿ����
//�������:��Ϸ����
//�� �� ֵ:1Ϊ��Ϸ����,0Ϊ��Ϸ����
//˵    ��:
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
//�� �� ��:merge
//��������:����������ķ���ϲ�����Ϸ����
//�������:�������Ϸ��
//�� �� ֵ:
//˵    ��:
//=====================================================
void merge(struct Block block, int(*board)[MAX_BOARD_WIDTH])
{
	for (int i = 0; i < block.index_num; i++) {
		board[block.abs_index.y + block.rel_index[i].y][block.abs_index.x + block.rel_index[i].x] = block.color;
	}
	return;
}
//=====================================================
//�� �� ��:pop_and_fall
//��������:������������,����ͼ������ʾ
//�������:��Ϸ����
//�� �� ֵ:��������
//˵    ��:û��������Ӧ,ֻ��ÿһ�м��һ�߼���
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
//�� �� ��:update_info
//��������:���µ÷ְ��ϵ���Ϣ
//�������:
//�� �� ֵ:
//˵    ��:
//=====================================================
void update_info(int erase_sum, int next_num)
{
	return;
}


