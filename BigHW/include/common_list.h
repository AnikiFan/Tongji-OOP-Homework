/* 2254298 大数据 范潇 */
#pragma once
//字符串类函数
int begin_with(const char* x, const char* y, int case_sensitive = 0);
//数组类函数
void matrix_iteration(int* p, int row_num, int col_num, void(*manipulation)(int, int, int));
void list_iteration(int* p, int list_size, void(*manipulation)(int, int));
int list_any(int* list, int list_size, int(*condition)(int, int));
int list_all(int* list, int list_size, int(*condition)(int, int));
int list_valid_num(int* list, int list_size, int(*condition)(int, int));
void  list_copy(int* dst, int* src, int list_size, const int OPTION);
//调试类函数 
void check_element(int* p, int row_num, int col_num);