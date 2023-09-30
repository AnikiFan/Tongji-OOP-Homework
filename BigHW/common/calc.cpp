#include"../include/calc.h"
#include<Windows.h>
//=====================================================
//函 数 名:between
//功能描述:判断第一个参数是否在第二三个参数中间(包括)
//输入参数:
//返 回 值:1表示包括,0表示不包括
//说    明:
//=====================================================
int between(double num, double x, double y)
{
	return (x <= num && num <= y || y <= num && num <= x);
}
//=====================================================
//函 数 名:case_insensitive_char_compare
//功能描述:比较两个字符是否相等,大小写不敏感
//输入参数:两个字符,不分先后.
//返 回 值:1为真,0为假
//说    明:
//=====================================================
int case_insensitive_char_compare(char x, char y)
{
	if (x == y)
		return 1;
	else if (between(x, 'a', 'z') && between(y, 'A', 'Z') && y + 32 == x)
		return 1;
	else if (between(y, 'a', 'z') && between(x, 'A', 'Z') && x + 32 == y)
		return 1;
	else
		return 0;
}
//=====================================================
//函 数 名:coordinate_transformation
//功能描述:坐标之间的变换
//输入参数:原坐标,变换函数
//返 回 值:point结构体
//说    明:坐标均为整数
//=====================================================
struct point coordinate_transformation(int x, int y, int (*x_transformation)(int, int), int (*y_transformation)(int, int))
{
	struct point point { x_transformation(x, y), y_transformation(x, y) };
	return point;
}
//=====================================================
//函 数 名:coordinate_transpose
//功能描述:坐标之间的转置
//输入参数:原坐标
//返 回 值:point结构体
//说    明:
//=====================================================
struct point coordinate_transpose(int x, int y)
{
	struct point point { y, x };
	return point;
}
//=====================================================
//函 数 名:clockwise_rotate
//功能描述:坐标绕给定轴顺时针旋转90度
//输入参数:旋转坐标,轴坐标
//返 回 值:point结构体
//说    明:
//=====================================================
struct point clockwise_rotate(int x, int y, int axis_x, int axis_y)
{
	struct point point { axis_x + y - axis_y, axis_y - x + axis_x };
	return point;
}
//=====================================================
//函 数 名:counterclockwise_rotate
//功能描述:坐标绕给定轴逆时针旋转90度
//输入参数:旋转坐标,轴坐标
//返 回 值:point结构体
//说    明:
//=====================================================
struct point counterclockwise_rotate(int x, int y, int axis_x, int axis_y)
{
	struct point point { axis_x - y + axis_y, axis_y + x - axis_x };
	return point;
}
//=====================================================
//函 数 名:central_symmetry
//功能描述:坐标绕给定轴中心对称
//输入参数:坐标,轴坐标
//返 回 值:point结构体
//说    明:
//=====================================================
struct point central_symmetry(int x, int y, int axis_x, int axis_y)
{
	struct point point { 2 * axis_x - x, 2 * axis_y - y };
	return point;
};
//=====================================================
//函 数 名:linear_transformation
//功能描述:坐标之间的线性变化
//输入参数:原坐标,作用矩阵的元素
//返 回 值:point结构体
//说    明:
//=====================================================
struct point linear_transformation(int x, int y, int a11, int a12, int a21, int a22, int d1, int d2)
{
	struct point point { a11* x + a12 * y + d1, a21* x + a22 * y + d2 };
	return point;
}
//=====================================================
//函 数 名:make_random_num
//功能描述:
//输入参数:范围,是否使用新的种子,种子
//返 回 值:默认输出0到n-1的随机数
//说    明:
//=====================================================
int get_next_num(int n, const bool new_seed, const unsigned int seed)
{
	if (new_seed)
		srand(seed);
	return rand() % n;
}