/* 2254298 大数据 范潇 */
/* 2050215 吴樾强 2151188 陆李天 2153538 刘博洋 2251320 涂中浩 2253716 欧佳音 2252313 陈兴悦 2253733 廖耀文 2251882 聂师扬 2151753 彭坤宇 2253204 邵琳博 2252086 孙靖贻 2251924 晏景豪 */
#include<iostream>
#include<fstream>
#define MAXFILESIZE 200
using namespace std;
int main(int argc,char**argv)
{
	clog << "文件名以下形式均可以:" << endl;
	clog << "    a.hex                     : 不带路径形式 " << endl;
	clog << "    ..\\data\\b.txt             : 相对路径形式" << endl;
	clog << "    C:\\Windows\\System32\\c.hex : 绝对相对路径形式" << endl;
	clog << "请输入要转换的hex格式文件名 : " ;
	char filename[MAXFILESIZE],input[10],output[MAXFILESIZE];
	cin >> filename;
	clog << "请输入转换后的文件名        : ";
	cin >> output;
	ifstream infile(filename, ios::in|ios::binary);
	if (!infile) {
		cout << "输入文件" << filename << "打开失败!" << endl;
		infile.close();
		return -1;
	}
	ofstream outfile(output, ios::out|ios::binary);
	if (!outfile) {
		cout << "输出文件" << output << "打开失败!" << endl;
		outfile.close();
		infile.close();
		return -1;
	}
	infile.seekg(0, ios::end);
	long long end = infile.tellg(), count = 11;
	infile.seekg(11, ios::beg);
	while (count+80 < end) {
		for (int i = 0; i < 8; i++) {
			infile.read(input, 3);
			if (input[0] > '9')
				input[0] = input[0]-'A'+'0' + 10;
			if (input[1] > '9')
				input[1] = input[1]-'A' +'0' + 10;
			outfile<<(char)((input[0] - '0') * 16 + input[1] - '0');
		}
		infile.read(input, 2);
		for (int i = 0; i < 8; i++) {
			infile.read(input, 3);
			if (input[0] > '9')
				input[0] =input[0]-'A'+10 +'0' ;
			if (input[1] > '9')
				input[1] =input[1] - 'A' + 10 +'0' ;
			outfile<<(char)((input[0] - '0') * 16 + input[1] - '0');
		}
		count += 80;
		infile.seekg(30, ios::cur);
	}
	int quit = 0;
	char temp;
	while (1) {
		infile.read(input, 1);
		temp = input[0];
		if (temp == '-') {
			infile.read(input, 1);
			continue;
		}
		if (temp == ' ' && quit)
			break;
		else if (temp == ' ')
			quit = 1;
		else {
			quit = 0;
			infile.read(input, 1);
			if (input[0] > '9')
				input[0] =input[0]- 'A' +10 +'0' ;
			if (temp > '9')
				temp =temp- 'A'+10 +'0' ;
			outfile<<(char)((temp - '0') * 16 + input[0] - '0');
		}
	}
	infile.close();
	outfile.close();
	return 0;
}