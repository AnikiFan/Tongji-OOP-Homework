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
		int rel_x = block.rel_index[i].x,rel_y =block.rel_index[i].y;
		int x = abs_x + rel_x, y = abs_y + rel_y;
		if (y < 0)
			continue;
		struct point point= linear_transformation(x, y, BLOCK_WIDTH, 0, BLOCK_HEIGHT, 0, GAMEBOARD_X + GAMEBOARD_WIDTH, GAMEBOARD_Y + 1);
		make_block(point.x, point.y, block_list, 3, block.color, BLOCK_FRAME_COLOR);
	}
}
//=====================================================
//�� �� ��:valid_fall
//��������:��鷽���ܷ�����һ��
//�������:������״���,��Ϸ����
//�� �� ֵ:
//˵    ��:�������Ϸ�Ƿ����,���������ԭ��һ����ִ������Ĳ���,����ƽ�ƵȲ���
//=====================================================
//=====================================================
//�� �� ��:fall
//��������:ִ��һ�����������,ֱ���䵽�ײ������䵽����������
//�������:������״���,��Ϸ����
//�� �� ֵ:
//˵    ��:�������Ϸ�Ƿ����,���������ԭ��һ����ִ������Ĳ���,����ƽ�ƵȲ���
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
			//TODO:Ҫ��дһ����������ȥ֮ǰ�Ĳ���
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
int game_continue(int(*board)[BOARD_WIDTH])
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
void merge(struct Block block,int(*board)[BOARD_WIDTH])
{
	return ;
}
//=====================================================
//�� �� ��:pop
//��������:������������,����ͼ������ʾ
//�������:��Ϸ����
//�� �� ֵ:��������
//˵    ��:û��������Ӧ,ֻ��ÿһ�м��һ�߼���
//=====================================================
int pop(int(*board)[BOARD_WIDTH])
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


