/* 2254298 ������ ���� */
#include <iostream>
#include <iomanip>
using namespace std;

const char* sp = "=====================================";
template <typename T, size_t Rows, size_t Cols>
/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����ÿ�����ֿ��Ϊ8���Ҷ���
***************************************************************************/
void matrix_print(const char *info,T (&mat)[Rows][Cols])	//��...�滻Ϊ��Ӧ����
{
	/* ������������ */
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
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void matrix_addition(T_ans (&ans)[Rows][Cols],T1 (&mat1)[Rows][Cols],T2 (&mat2)[Rows][Cols])	//��...�滻Ϊ��Ӧ����
{
	/* ������������ */
	cout << "Դ����1 : ��=" <<Rows<<" ��=" << Cols<<" ռ�ÿռ�="<<sizeof(T1)*Rows*Cols<<"�ֽ�"<<endl;
	cout << "Դ����2 : ��=" << Rows << " ��=" << Cols << " ռ�ÿռ�=" << sizeof(T2) * Rows * Cols << "�ֽ�" << endl;
	cout << "�;���  : ��=" << Rows << " ��=" << Cols << " ռ�ÿռ�=" 	<< (sizeof(T_ans)) * Rows * Cols << "�ֽ�" << endl;
	for (long unsigned int i = 0; i < Rows * Cols; i++)
		*(*ans + i) =(T_ans)( *(*mat1 + i)) +(  *(*mat2 + i));
	return;
}
template <typename T_ans,typename T1,typename T2, size_t Row1, size_t mid,size_t Col2>
/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void matrix_multiplication(T_ans(&ans)[Row1][Col2],T1(&mat1)[Row1][mid],T2(&mat2)[mid][Col2])	//��...�滻Ϊ��Ӧ����
{
	/* ������������ */
	size_t Row2 = mid, Col1 = mid;
	cout << "Դ����1 : ��=" <<Row1<<" ��="<<Col1<<" ռ�ÿռ�="<<sizeof(T1)*Row1*Col1<<"�ֽ�"<<endl;
	cout << "Դ����2 : ��=" <<Row2<<" ��="<<Col2<<" ռ�ÿռ�="<<sizeof(T2)*Row2*Col2<<"�ֽ�"<<endl;
	cout << "������  : ��=" <<Row1<<" ��="<<Col2<<" ռ�ÿռ�="	<<sizeof(T_ans)*Row1*Col2<<"�ֽ�"<<endl;
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
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����main������׼����
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
	matrix_print("�ӷ����㣬Դ����1��", t1);
	matrix_print("�ӷ����㣬Դ����2��", t2);
	matrix_addition(t_add, t1, t2);	//��t1��t2�ĺͷ���t_add�У��˹���֤������������һ��
	matrix_print("�ӷ����㣬�;��� ��", t_add);
	cout << sp << endl;
	matrix_print("�˷����㣬Դ����1��", t1);
	matrix_print("�˷����㣬Դ����2��", t3);
	matrix_multiplication(t_mul, t1, t3);	//��t1��t2�ĺͷ���t_add�У��˹���֤������������һ��
	matrix_print("�˷����㣬������ ��", t_mul);
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
	/* ��Ҫ��Ϊʲô����˷��������Ͳ�ͬ������� */
	float f3[4][3] = {
		{12.12f, 11.11f, 10.10f},
		{9.9f, 8.8f, 7.7f},
		{6.6f, 5.5f, 4.4f},
		{3.3f, 2.2f, 1.1f}
	};
	int i_mul[2][3];

	matrix_print("�ӷ����㣬Դ����1��", d1);
	matrix_print("�ӷ����㣬Դ����2��", d2);
	matrix_addition(d_add, d1, d2);	//��d1��d2�ĺͷ���d_add�У��˹���֤������������һ��
	matrix_print("�ӷ����㣬�;��� ��", d_add);
	cout << sp << endl;
	matrix_print("�˷����㣬Դ����1��", d1);
	matrix_print("�˷����㣬Դ����2��", f3);
	matrix_multiplication(i_mul, d1, f3);	//��t1��t2�ĺͷ���t_add�У��˹���֤������������һ��
	matrix_print("�˷����㣬������ ��", i_mul);
	cout << sp << endl;

	return 0;
}