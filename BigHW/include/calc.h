#pragma once
//数值运算类函数
struct point {
	int x;
	int y;
};
int between(double num, double x, double y);
int case_insensitive_char_compare(char x, char y);
int get_next_num(int n, const bool new_seed = false, const unsigned int seed = 0);
struct point coordinate_transformation(int x, int y, int (*x_transformation)(int, int), int (*y_transformation)(int, int));
struct point coordinate_transpose(int x, int y);
struct point linear_transformation(int x, int y, int a11 = 1, int a12 = 0, int a21 = 0, int a22 = 1, int d1 = 0, int d2 = 0);
struct point clockwise_rotate(int x, int y, int axis_x = 0, int axis_y = 0);
struct point counterclockwise_rotate(int x, int y, int axis_x = 0, int axis_y = 0);
struct point central_symmetry(int x, int y, int axis_x = 0, int axis_y = 0);