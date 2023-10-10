/* 2254298 大数据 范潇 */
#include <iostream>
#include <iomanip>
using namespace std;

const char* sp = "=====================================";
template <typename T, size_t Rows, size_t Cols>
/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：每个数字宽度为8，右对齐
***************************************************************************/
void matrix_print(const char *info,T (&mat)[Rows][Cols])	//将...替换为相应内容
{
	/* 按需增加内容 */
	cout << info << endl;
	cout << setiosflags(ios::right);
	for (long unsigned int i = 0; i < Rows; i++) {
		for (long unsigned int j = 0; j < Cols; j++)
			cout << setw(8)<<*(*mat+i*Cols+j);
		cout << endl;
	}
	cout << resetiosflags(ios::right);
	return;
}
template <typename T_ans, typename T1, typename T2, size_t Rows, size_t Cols>
/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void matrix_addition(T_ans (&ans)[Rows][Cols],T1 (&mat1)[Rows][Cols],T2 (&mat2)[Rows][Cols])	//将...替换为相应内容
{
	/* 按需增加内容 */
	cout << "源矩阵1 : 行=" <<Rows<<" 列=" << Cols<<" 占用空间="<<sizeof(T1)*Rows*Cols<<"字节"<<endl;
	cout << "源矩阵2 : 行=" << Rows << " 列=" << Cols << " 占用空间=" << sizeof(T2) * Rows * Cols << "字节" << endl;
	cout << "和矩阵  : 行=" << Rows << " 列=" << Cols << " 占用空间=" 	<< (sizeof(T_ans)) * Rows * Cols << "字节" << endl;
	for (long unsigned int i = 0; i < Rows * Cols; i++)
		*(*ans + i) =(T_ans)( *(*mat1 + i)) +(  *(*mat2 + i));
	return;
}
template <typename T_ans,typename T1,typename T2, size_t Row1, size_t mid,size_t Col2>
/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void matrix_multiplication(T_ans(&ans)[Row1][Col2],T1(&mat1)[Row1][mid],T2(&mat2)[mid][Col2])	//将...替换为相应内容
{
	/* 按需增加内容 */
	size_t Row2 = mid, Col1 = mid;
	cout << "源矩阵1 : 行=" <<Row1<<" 列="<<Col1<<" 占用空间="<<sizeof(T1)*Row1*Col1<<"字节"<<endl;
	cout << "源矩阵2 : 行=" <<Row2<<" 列="<<Col2<<" 占用空间="<<sizeof(T2)*Row2*Col2<<"字节"<<endl;
	cout << "积矩阵  : 行=" <<Row1<<" 列="<<Col2<<" 占用空间="	<<sizeof(T_ans)*Row1*Col2<<"字节"<<endl;
	T_ans sum;
	for(long unsigned int i = 0;i<Row1;i++)
		for (long unsigned int j = 0; j < Col2; j++) {
			sum = 0;
			for (long unsigned int k = 0; k < mid; k++)
				sum += (T_ans)((*(*(mat1 + i) + k)) * (*(*(mat2 + k) + j)));
			*(*(ans + i) + j) = sum;
		}
	return;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：main函数不准更改
***************************************************************************/
int main()
{
	int t1[3][4] = {
		{1,2,3,4},
		{5,6,7,8},
		{9,10,11,12}
	};
	int t2[3][4] = {
		{12,11,10,9},
		{8,7,6,5},
		{4,3,2,1}
	};
	int t3[4][2] = {
		{1, 2},
		{3, 4},
		{5, 6},
		{7, 8}
	};
	int t_add[3][4], t_mul[3][2];

	cout << sp << endl;
	matrix_print("加法运算，源矩阵1：", t1);
	matrix_print("加法运算，源矩阵2：", t2);
	matrix_addition(t_add, t1, t2);	//将t1和t2的和放入t_add中，人工保证三个矩阵行列一致
	matrix_print("加法运算，和矩阵 ：", t_add);
	cout << sp << endl;
	matrix_print("乘法运算，源矩阵1：", t1);
	matrix_print("乘法运算，源矩阵2：", t3);
	matrix_multiplication(t_mul, t1, t3);	//将t1和t2的和放入t_add中，人工保证三个矩阵行列一致
	matrix_print("乘法运算，积矩阵 ：", t_mul);
	cout << sp << endl;

	double d1[2][4] = {
		{1.1, 2.2, 3.3, 4.4},
		{5.5 ,6.6, 7.7, 8.8}
	};
	double d2[2][4] = {
		{8.8, 7.7, 6.6, 5.5},
		{4.4, 3.3, 2.2, 1.1}
	};
	double d_add[2][4];
	/* 不要问为什么矩阵乘法数据类型不同，故意的 */
	float f3[4][3] = {
		{12.12f, 11.11f, 10.10f},
		{9.9f, 8.8f, 7.7f},
		{6.6f, 5.5f, 4.4f},
		{3.3f, 2.2f, 1.1f}
	};
	int i_mul[2][3];

	matrix_print("加法运算，源矩阵1：", d1);
	matrix_print("加法运算，源矩阵2：", d2);
	matrix_addition(d_add, d1, d2);	//将d1和d2的和放入d_add中，人工保证三个矩阵行列一致
	matrix_print("加法运算，和矩阵 ：", d_add);
	cout << sp << endl;
	matrix_print("乘法运算，源矩阵1：", d1);
	matrix_print("乘法运算，源矩阵2：", f3);
	matrix_multiplication(i_mul, d1, f3);	//将t1和t2的和放入t_add中，人工保证三个矩阵行列一致
	matrix_print("乘法运算，积矩阵 ：", i_mul);
	cout << sp << endl;

	return 0;
}