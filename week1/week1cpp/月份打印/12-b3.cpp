/* 2254298 大数据 范潇 */
#include<iostream>
using namespace std;
int main()
{
	const char* monthname[] = { "","January","February","March","April","May","June","July","August","September","October","November","December" };
	cout << "请输入月份(1-12)" << endl;
	int month;
	cin >> month;
	if (month <= 0 || month >= 13 || cin.rdstate())
		cout << "Invalid" << endl;
	else
		cout << monthname[month] << endl;
	return 0;
}