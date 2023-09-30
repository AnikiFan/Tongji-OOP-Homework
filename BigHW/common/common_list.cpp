/* 2254298 ������ ���� */
#include"../include/common_list.h"
#include"../include/common_calc.h"
#include<iostream>
using namespace std;
//=====================================================
//�� �� ��:begin_with
//��������:�ж�һ���ַ����Ƿ�������һ���ַ�����ʼ.
//�������:�����ַ���,�����Ⱥ�.
//�� �� ֵ:1Ϊ��,0Ϊ��
//˵    ��:
//=====================================================
int begin_with(const char* x, const char* y, int case_sensitive)
{
	if (*x && !*y || !*x && *y)
		return 0;
	while (*x && *y) {
		if ((*x != *y) && case_sensitive || !case_insensitive_char_compare(*x, *y) && !case_sensitive)
			return 0;
		x++;
		y++;
	}
	return 1;
}
//=====================================================
//�� �� ��:matrix_iteration
//��������:����һ��int�Ͷ�ά����,������ÿ��Ԫ�ص�ֵ������Ӧ�Ĳ���
//�������:���鿪ʼ����ָ��,��������,�����������
//�� �� ֵ:
//˵    ��:
//=====================================================
void matrix_iteration(int* p, int row_num, int col_num, void(*manipulation)(int, int, int))
{
	for (int i = 0; i < row_num; i++)
		for (int j = 0; j < col_num; j++)
			manipulation(i, j, *(p + i * col_num + j));
	return;
}
//=====================================================
//�� �� ��:list_iteration
//��������:����һ��int������,������ÿ��Ԫ�ص�ֵ������Ӧ�Ĳ���
//�������:���鿪ʼ����ָ��,��������,����Ĵ�С
//�� �� ֵ:
//˵    ��:
//=====================================================
void list_iteration(int* p, int list_size, void(*manipulation)(int, int))
{
	for (int i = 0; i < list_size; i++)
		manipulation(i, *(p + i));
	return;
}
//=====================================================
//�� �� ��:check_element
//��������:����һ��int�Ͷ�ά����,����ӡ�������꼰��ֵ
//�������:���鿪ʼ����ָ��,�����������
//�� �� ֵ:
//˵    ��:
//=====================================================
void check_element(int* p, int row_num, int col_num)
{
	for (int i = 0; i < row_num; i++) {
		for (int j = 0; j < col_num; j++)
			cout << "[" << row_num << "]" << "[" << col_num << "]" << *(p + i * col_num + j) << "  ";
		cout << endl;
	}
	return;
}
//=====================================================
//�� �� ��:list_any
//��������:�ж������б����Ƿ�����һԪ��������������
//�������:�����б�,�б��С,��������,��һ������ΪԪ��,�ڶ�������Ϊָ��
//�� �� ֵ:1Ϊ��,0Ϊ��
//˵    ��:
//=====================================================
int list_any(int* list, int list_size, int(*condition)(int, int))
{
	for (int i = 0; i < list_size; i++) {
		if (condition(list[i], i))
			return 1;
	}
	return 0;
}
//=====================================================
//�� �� ��:list_all
//��������:�ж������б����Ƿ�������Ԫ��������������
//�������:�����б�,�б��С,��������,��һ������ΪԪ��,�ڶ�������Ϊָ��
//�� �� ֵ:1Ϊ��,0Ϊ��
//˵    ��:
//=====================================================
int list_all(int* list, int list_size, int(*condition)(int, int))
{
	for (int i = 0; i < list_size; i++) {
		if (!condition(list[i], i))
			return 0;
	}
	return 1;
}
//=====================================================
//�� �� ��:list_valid_num
//��������:�ж������б�����������������Ԫ�ظ���
//�������:�����б�,�б��С,��������,��һ������ΪԪ��,�ڶ�������Ϊָ��
//�� �� ֵ:
//˵    ��:
//=====================================================
int list_valid_num(int* list, int list_size, int(*condition)(int, int))
{
	int sum = 0;
	for (int i = 0; i < list_size; i++) {
		if (condition(list[i], i))
			sum++;
	}
	return sum;
}
//=====================================================
//�� �� ��:list_copy
//��������:��һ�������б��е�Ԫ�ظ�������һ�б�,Ҳ����ѡ��Ϊ������
//�������:src,dst,ѡ��,0Ϊ����,0Ϊ����,����
//�� �� ֵ:
//˵    ��:
//=====================================================
void  list_copy(int* dst, int* src, int list_size, const int OPTION)
{
	for (int i = 0; i < list_size; i++) {
		dst[i] = src[i];
	}
	if (OPTION)
		for (int i = 0; i < list_size; i++)
			src[i] = 0;
	return;
}