/* 2254298 大数据 范潇 */
#include"../include/common_list.h"
#include"../include/common_calc.h"
#include<iostream>
using namespace std;
//=====================================================
//函 数 名:begin_with
//功能描述:判断一个字符串是否由另外一个字符串开始.
//输入参数:两个字符串,不分先后.
//返 回 值:1为真,0为假
//说    明:
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
//函 数 名:matrix_iteration
//功能描述:遍历一个int型二维数组,并根据每个元素的值来做相应的操作
//输入参数:数组开始处的指针,操作函数,数组的行列数
//返 回 值:
//说    明:
//=====================================================
void matrix_iteration(int* p, int row_num, int col_num, void(*manipulation)(int, int, int))
{
	for (int i = 0; i < row_num; i++)
		for (int j = 0; j < col_num; j++)
			manipulation(i, j, *(p + i * col_num + j));
	return;
}
//=====================================================
//函 数 名:list_iteration
//功能描述:遍历一个int型数组,并根据每个元素的值来做相应的操作
//输入参数:数组开始处的指针,操作函数,数组的大小
//返 回 值:
//说    明:
//=====================================================
void list_iteration(int* p, int list_size, void(*manipulation)(int, int))
{
	for (int i = 0; i < list_size; i++)
		manipulation(i, *(p + i));
	return;
}
//=====================================================
//函 数 名:check_element
//功能描述:遍历一个int型二维数组,并打印行列坐标及其值
//输入参数:数组开始处的指针,数组的行列数
//返 回 值:
//说    明:
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
//函 数 名:list_any
//功能描述:判断整型列表中是否有任一元素满足所给函数
//输入参数:整型列表,列表大小,条件函数,第一个参量为元素,第二个参量为指标
//返 回 值:1为真,0为假
//说    明:
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
//函 数 名:list_all
//功能描述:判断整型列表中是否有所有元素满足所给函数
//输入参数:整型列表,列表大小,条件函数,第一个参量为元素,第二个参量为指标
//返 回 值:1为真,0为假
//说    明:
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
//函 数 名:list_valid_num
//功能描述:判断整型列表中满足所给函数的元素个数
//输入参数:整型列表,列表大小,条件函数,第一个参量为元素,第二个参量为指标
//返 回 值:
//说    明:
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
//函 数 名:list_copy
//功能描述:将一个整型列表中的元素复制至另一列表,也可以选择为剪切至
//输入参数:src,dst,选项,0为复制,0为剪切,长度
//返 回 值:
//说    明:
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