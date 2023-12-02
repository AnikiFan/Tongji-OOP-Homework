/* 2254298 ´óÊý¾Ý ·¶äì */
#include<iostream>
using namespace std;
template<typename T, size_t R, size_t C>
class matrix {
private:
	T value[R][C];
public:
	matrix() {
		for (int i = 0; i < R; i++)
			for (int j = 0; j < C; j++)
				value[i][j] = T();
	}
	matrix<T, R, C> operator+(const matrix <T, R, C>& M)const {
		matrix<T, R, C> temp;
		for (int i = 0; i < R; i++)
			for (int j = 0; j < C; j++)
				temp.value[i][j] = value[i][j] + M.value[i][j];
		return temp;
	}
	friend istream& operator >> (istream&in, matrix<T, R, C>&M) {
		for (int i = 0; i < R; i++)
			for (int j = 0; j < C; j++)
				in >> M.value[i][j];
		return in;
	}
	friend ostream& operator << (ostream&out, const matrix<T, R, C>&M) {
		for (int i = 0; i < R; i++) {
			for (int j = 0; j < C; j++)
				out << M.value[i][j]<<" ";
			out << endl;
		}
		return out;
	}
};