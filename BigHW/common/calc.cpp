#include"../include/calc.h"
#include<Windows.h>
//=====================================================
//�� �� ��:between
//��������:�жϵ�һ�������Ƿ��ڵڶ����������м�(����)
//�������:
//�� �� ֵ:1��ʾ����,0��ʾ������
//˵    ��:
//=====================================================
int between(double num, double x, double y)
{
	return (x <= num && num <= y || y <= num && num <= x);
}
//=====================================================
//�� �� ��:case_insensitive_char_compare
//��������:�Ƚ������ַ��Ƿ����,��Сд������
//�������:�����ַ�,�����Ⱥ�.
//�� �� ֵ:1Ϊ��,0Ϊ��
//˵    ��:
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
//�� �� ��:coordinate_transformation
//��������:����֮��ı任
//�������:ԭ����,�任����
//�� �� ֵ:point�ṹ��
//˵    ��:�����Ϊ����
//=====================================================
struct point coordinate_transformation(int x, int y, int (*x_transformation)(int, int), int (*y_transformation)(int, int))
{
	struct point point { x_transformation(x, y), y_transformation(x, y) };
	return point;
}
//=====================================================
//�� �� ��:coordinate_transpose
//��������:����֮���ת��
//�������:ԭ����
//�� �� ֵ:point�ṹ��
//˵    ��:
//=====================================================
struct point coordinate_transpose(int x, int y)
{
	struct point point { y, x };
	return point;
}
//=====================================================
//�� �� ��:clockwise_rotate
//��������:�����Ƹ�����˳ʱ����ת90��
//�������:��ת����,������
//�� �� ֵ:point�ṹ��
//˵    ��:
//=====================================================
struct point clockwise_rotate(int x, int y, int axis_x, int axis_y)
{
	struct point point { axis_x + y - axis_y, axis_y - x + axis_x };
	return point;
}
//=====================================================
//�� �� ��:counterclockwise_rotate
//��������:�����Ƹ�������ʱ����ת90��
//�������:��ת����,������
//�� �� ֵ:point�ṹ��
//˵    ��:
//=====================================================
struct point counterclockwise_rotate(int x, int y, int axis_x, int axis_y)
{
	struct point point { axis_x - y + axis_y, axis_y + x - axis_x };
	return point;
}
//=====================================================
//�� �� ��:central_symmetry
//��������:�����Ƹ��������ĶԳ�
//�������:����,������
//�� �� ֵ:point�ṹ��
//˵    ��:
//=====================================================
struct point central_symmetry(int x, int y, int axis_x, int axis_y)
{
	struct point point { 2 * axis_x - x, 2 * axis_y - y };
	return point;
};
//=====================================================
//�� �� ��:linear_transformation
//��������:����֮������Ա仯
//�������:ԭ����,���þ����Ԫ��
//�� �� ֵ:point�ṹ��
//˵    ��:
//=====================================================
struct point linear_transformation(int x, int y, int a11, int a12, int a21, int a22, int d1, int d2)
{
	struct point point { a11* x + a12 * y + d1, a21* x + a22 * y + d2 };
	return point;
}
//=====================================================
//�� �� ��:make_random_num
//��������:
//�������:��Χ,�Ƿ�ʹ���µ�����,����
//�� �� ֵ:Ĭ�����0��n-1�������
//˵    ��:
//=====================================================
int get_next_num(int n, const bool new_seed, const unsigned int seed)
{
	if (new_seed)
		srand(seed);
	return rand() % n;
}