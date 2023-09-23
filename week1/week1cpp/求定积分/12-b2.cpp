/* 2254298 大数据 范潇 */
#include<iostream>
#include<cmath>
using namespace std;
double definite_integration(double(*f)(double),double low,double high ,int n)
{
	double dx = (high - low) / n,x=low,rect,sum=0;
	for (int i = 1; i <= n; i++) {
		x += dx;
		rect = dx * f(x);
		sum += rect;
	}
	return sum;
}
int main()
{
	int n;
	double low, high;
	cout << "请输入sinxdx的下限、上限及区间划分数量" << endl;
	cin >> low >> high >> n;
	cout << "sinxdx[" << low << "~" << high << "/n=" << n << "] : " << definite_integration(sin, low, high, n)<<endl;
	cout << "请输入cosxdx的下限、上限及区间划分数量" << endl;
	cin >> low >> high >> n;
	cout << "cosxdx[" << low << "~" << high << "/n=" << n << "] : " << definite_integration(cos, low, high, n)<<endl;
	cout << "请输入sinxdx的下限、上限及区间划分数量" << endl;
	cin >> low >> high >> n;
	cout << "e^xdx[" << low << "~" << high << "/n=" << n << "] : " << definite_integration(exp, low, high, n)<<endl;
	return 0;
}