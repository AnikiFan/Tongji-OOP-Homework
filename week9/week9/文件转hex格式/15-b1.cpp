/* 2254298 大数据 范潇 */
/* 2050215 吴樾强 2151188 陆李天 2153538 刘博洋 2251320 涂中浩 2253716 欧佳音 2252313 陈兴悦 2253733 廖耀文 2251882 聂师扬 2151753 彭坤宇 2253204 邵琳博 2252086 孙靖贻 2251924 晏景豪 */
#include<iostream>
#include<iomanip>
#include<fstream>
#define INPUTSIZE 10
#define MAXNAMESIZE 200
using namespace std;
int main()
{
	clog << "文件名以下形式均可以:" << endl;
	clog << "    a.txt                     : 不带路径形式" << endl;
	clog << "    ..\\data\\b.dat             : 相对路径形式" << endl;
	clog << "    C:\\Windows\\System32\\c.dat : 绝对相对路径形式" << endl;
	clog << "请输入文件名 : ";
	char input[INPUTSIZE], buff[20] = { 0 },filename[MAXNAMESIZE];
	int top = 0;
	cin >> filename;
	ifstream infile (filename, ios::in|ios::binary);
	if (!infile) {
		cout << "输入文件"<<filename<<" 打开失败!" << endl;
		infile.close();
		return -1;
	}
	infile.seekg(0, ios::end);
	long long end = infile.tellg(),count = 0;
	infile.seekg(0, ios::beg);
	while (count < end) {
		if (!((count - 8) % 16))
			cout << " -";
		if (!(count % 16)) 
			cout << setw(8) << setfill('0') << setiosflags(ios::right)<<setiosflags(ios::uppercase) << hex << count  << ": ";
		infile.read(input,1);
		cout << " " << setw(2) << setfill('0') << setiosflags(ios::right) <<setiosflags(ios::uppercase)<< hex << ((int)(unsigned char)input[0]);
		buff[top++] = input[0];
		if (top == 16) {
			cout << "  ";
			top = 0;
			for (int i = 0; i < 16; i++)
				if (buff[i] >= 33 && buff[i] <= 126)
					putchar(buff[i]);
				else
					putchar('.');
			cout << endl;
		}
		count++;
	}
	if (!top)
		return 0;
	cout << "  ";
	for (int i = 0; i < 16 - top; i++)
		cout << "   ";
	if (top <= 8)
		cout << "  ";
	for (int i = 0; i < top; i++)
				if (buff[i] >= 33 && buff[i] <= 126)
					putchar(buff[i]);
				else
					putchar('.');
	cout << endl;
	infile.close();
	return 0;
}