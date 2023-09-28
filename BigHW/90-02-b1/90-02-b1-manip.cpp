#include<iostream>
#include<Windows.h>
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
//�� �� ��:from_index_to_coordinate
//��������:��ģ������ľ���ָ��ת��Ϊ��Ļ�ϵľ�������
//�������:ģ������ľ���ָ��
//�� �� ֵ:
//˵    ��:
//=====================================================
struct point from_index_to_coordinate(int x, int y)
{
	return  linear_transformation(x-BOARD_SIDE_WIDTH, y-BOARD_TOP_WIDTH, BLOCK_WIDTH, 0,0, BLOCK_HEIGHT, GAMEBOARD_X + GAMEBOARD_SIDE_WIDTH, GAMEBOARD_Y + 1);
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
//�� �� ��:valid_fall
//��������:��鷽���ܷ�����һ��
//�������:������״���,��Ϸ����
//�� �� ֵ:1Ϊ����,0Ϊ������
//˵    ��:�������Ϸ�Ƿ����,���������ԭ��һ����ִ������Ĳ���,����ƽ�ƵȲ���
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
//�� �� ��:erase_remain_block
//��������:��������仯��,������һ��,����ת,֮ǰ����Ĳ�������
//�������:������״���,��Ϸ����,����ı仯
//�� �� ֵ:��erase_list_block������Ϊ-1,��˵����������
//˵    ��:����Ϸ�з���ֻ����ʱ����ת,���ص��Ǿ���ָ��
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
//�� �� ��:erase_remain
//��������:���������ƶ���Ĳ�������
//�������:�������ֵ�ָ�꼯
//�� �� ֵ:
//˵    ��:ָ�꼯Ϊ�е�Ԫ��Ϊ-1,-1��˵������,ͬʱ���y�ķ�Χ�ڶ���,��ôҲ����
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
//�� �� ��:fall
//��������:ִ��һ�����������,ֱ���䵽�ײ������䵽����������
//�������:������״���,��Ϸ����
//�� �� ֵ:
//˵    ��:�������Ϸ�Ƿ����,���������ԭ��һ����ִ������Ĳ���,����ƽ�ƵȲ���
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
//�� �� ��:game_continue
//��������:�����Ϸ�Ƿ����
//�������:��Ϸ����
//�� �� ֵ:1Ϊ��Ϸ����,0Ϊ��Ϸ����
//˵    ��:
//=====================================================
int game_continue(int(*board)[MAX_BOARD_WIDTH])
{
	return 0;
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
	return;
}
//=====================================================
//�� �� ��:pop
//��������:������������,����ͼ������ʾ
//�������:��Ϸ����
//�� �� ֵ:��������
//˵    ��:û��������Ӧ,ֻ��ÿһ�м��һ�߼���
//=====================================================
int pop(int(*board)[MAX_BOARD_WIDTH])
{
	return 0;
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


