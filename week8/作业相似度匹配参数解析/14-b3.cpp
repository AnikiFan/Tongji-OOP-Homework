/* 2254298 大数据 范潇 */
#include<iostream>
#include<string.h>
using namespace std;
/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int usage(const char* const procname)
{
	cout << "Usage: " << procname << " 要检查的学号/all 匹配学号/all 源程序名/all 相似度阀值(60-100) 输出(filename/screen)" << endl << endl;
	cout << "e.g. : " << procname << " 2159999 2159998 all       80 screen" << endl;
	cout << "       " << procname << " 2159999 all     14-b1.cpp 75 result.txt" << endl;
	cout << "       " << procname << " all     all     14-b2.cpp 80 check.dat" << endl;
	cout << "       " << procname << " all     all     all       85 screen" << endl;

	return 0;
}
int check_name(const char* name, int obj) {//先判断位数，再判断是否为数字
	if (strlen(name) != 7)
		if (!obj) {
			cout << "要检查的学号不是7位" << endl;
			return 0;
		}
		else {
			cout << "要匹配的学号不是7位" << endl;
			return 0;
		}
	else
		for (int i = 0; i < 7; i++)
			if (name[i] < '0' || name[i]>'9') {
				if (!obj) {
					cout << "要检查的学号不是7位数字" << endl;
					return 0;
				}
				else {
					cout << "要匹配的学号不是7位数字" << endl;
					return 0;
				}
			}
	return 1;
}
int main(int argc, char** argv)
{
	int para = 80;
	if (argc != 6) {
		usage(argv[0]);
		return 0;
	}
	if (!strcmp((const char*)argv[1], "all")) {//第一个参数是all 
		if (strcmp("all",(const char *)argv[2])&&!check_name((const char*)argv[2], 1)) //检查第二个参数对不对
			return 0;
		else if (strcmp((const char*)argv[2], "all")) {//是对的
			cout << "检查学号是all，匹配学号必须是all" << endl;//学号对了，报all错
			return 0;
		}
	}
else if (!check_name((const char*)argv[1], 0))//检查第一个参数对不对
		return 0;
	else if (strcmp((const char*)argv[2], "all") && !check_name((const char*)argv[2], 1))//检查第二个参数对不对
		return 0;
	else if (!strcmp((const char*)argv[1], (const char*)argv[2]) && strcmp((const char*)argv[1], "all")) {
		cout << "匹配学号与要检查学号相同" << endl;
		return 0;
	}
	//名字参数检查完毕
	if (strlen(argv[3]) > 32) {
		cout << "源程序文件名超过了32字节" << endl;
		return 0;
	}
	if (strlen(argv[4]) == 2&&argv[4][0]>='0'&&argv[4][0]<='9'&&argv[4][1]>='0'&&argv[4][1]<='9') {
		para = 10 * (argv[4][0] - '0') + argv[4][1] - '0';
		if (para < 60 || para>100)
			para = 80;
	}
	if (strlen(argv[5]) > 32) {
		cout << "输出结果文件名超过了32字节" << endl;
		return 0;
	}
	cout << "参数检查通过" << endl;
	cout << "检查学号：" << argv[1] << endl;
	cout << "匹配学号：" << argv[2] << endl;
	cout << "源文件名：" << argv[3] << endl;
	cout << "匹配阈值：" << para << endl;
	cout << "输出目标：" << argv[5] << endl;
	return 0;
}