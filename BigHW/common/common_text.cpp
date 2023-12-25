/* 2254298 大数据 范潇 */
#define _CRT_SECURE_NO_WARNINGS
#include<vector>
#include"../include/common_text.h"
#include"../include/cmd_console_tools.h"
#include"../include/common_calc.h"
//====================================================
//函 数 名:int_len
//功能描述:返回整数的长度
//输入参数: 
//返 回 值:
//说    明:包括符号
//=====================================================	
int int_len(int num)
{
	if (!num)
		return 1;
	int len = (num < 0 ? 1 : 0);
	num = (num < 0 ? -num : num);
	while (num) {
		len++;
		num /= 10;
	}
	return len;
}
//====================================================
//函 数 名:ch_in_str
//功能描述:判断指定字符是否在给定字符串中
//输入参数:
//返 回 值:1为真，0为假
//说    明:
//=====================================================
int ch_in_str(char ch, const char* const str, int strlen)
{
	for (int i = 0; i < strlen; i++)
		if (str[i] == ch)
			return 1;
	return 0;
}
//====================================================
//函 数 名:get_line
//功能描述:从给定文件指针，读取至指定字符为止
//输入参数:文件指针，存储输入的数组，以及接收读入字符数的int，结束字符（串），trim方式，trim字符及其个数，
//返 回 值:,当返回1时表示读到文件结尾（人为添加的EOF不算），若读入字符数超过maxn则放回-1，其余情况返回0
//说    明:读入字符数（不包括结束字符和被trim字符）
//=====================================================
int get_line(ifstream& infile, char* buffer, int& inputn, int trim, char* trim_ch, int ch_num,
	char* end, int end_len, enum system& sys, int maxn, int CR_CRLF_not_equal)
{
	inputn = 0;
	int cur_pos = (int)infile.tellg();
	infile.seekg(0, ios::end);
	int end_pos = (int)infile.tellg();
	infile.seekg(cur_pos, ios::beg);
	if (cur_pos == end_pos)
		return 1;
	char input;
	int trim_left = 0;
	int comp_p = 0;
	int D = 0;
	if (trim == TRIM_LEFT || trim == TRIM_ALL)
		trim_left = 1;
	while (infile.tellg() != end_pos) {
		input = infile.get();
		if (input == 0x0D)
			D = 1;
		else if (input == 0x0A && D) {
			sys = WINDOWS;
			D = 0;
		}
		else
			D = 0;
		if (trim_left && ch_in_str(input, trim_ch, ch_num))
			continue;
		else {
			trim_left = 0;
			buffer[inputn++] = input;
			if (input == end[comp_p])
				comp_p++;
			else
				comp_p = 0;
			if (comp_p == end_len)
				break;
			else if (inputn == maxn)
				return -1;
		}
	}
	int eof = 0;
	if (comp_p == end_len) {
		inputn -= end_len;
		if (!CR_CRLF_not_equal && !strcmp("\n", end) && (buffer[inputn - 1] == '\r'))
			//用于处理demo当最后最后一行为单独一个\r时并不会打印的情况，若解决，则应该放到(comp_p==end_len)的条件分支中
			inputn--;
	}
	else
		eof = 1;
	if (CR_CRLF_not_equal && ((trim == TRIM_RIGHT) || (trim == TRIM_ALL)) && (buffer[inputn - 1] == '\r'))
		inputn--;
	if (CR_CRLF_not_equal && trim == TRIM_LEFT && inputn == 1 && buffer[0] == '\r')
		inputn--;
	if (trim == TRIM_RIGHT || trim == TRIM_ALL)
		while (inputn && ch_in_str(buffer[inputn - 1], trim_ch, ch_num))
			inputn--;
	buffer[inputn] = '\0';
	if (eof)
		return 1;
	//正常情况应该在while循环体内因为读入end而return
	return 0;
}
//====================================================
//函 数 名:print_row
//功能描述:打印一行中的内容
//输入参数:
//返 回 值:
//说    明:含高亮
//=====================================================
void print_row(char* row1, char* row2, int len1, int len2, int eof1, int eof2)
{
	char highlight_char[5] = "\r\v\b\a";
	cout << "文件1 : ";
	if (!len1) {
		if (eof1)
			cout << "<EOF>" << endl;
		else {
			cct_setcolor(HIGHLIGHT);
			cout << "<EMPTY>";
			cct_setcolor();
			cout << "<CR>" << endl;
		}
	}
	else {
		int i = 0;
		while (i < len2 && i < len1) {
			if (row1[i] != row2[i])
				cct_setcolor(HIGHLIGHT);
			char output = row1[i];
			if (ch_in_str(row1[i], highlight_char, 4))
				output = 'X';
			else if (row1[i] == EOF)
				output = ' ';
			cout << output;
			cct_setcolor();
			i++;
		}
		while (i < len1) {
			cct_setcolor(HIGHLIGHT);
			char output = row1[i];
			if (ch_in_str(row1[i], highlight_char, 4))
				output = 'X';
			else if (row1[i] == EOF)
				output = ' ';
			cout << output;
			cct_setcolor();
			i++;
		}
		if (eof1)
			cout << "<EOF>" << endl;
		else
			cout << "<CR>" << endl;
	}
	cout << "文件2 : ";
	if (!len2) {
		if (eof2)
			cout << "<EOF>" << endl;
		else {
			cct_setcolor(HIGHLIGHT);
			cout << "<EMPTY>";
			cct_setcolor();
			cout << "<CR>" << endl;
		}
	}
	else {
		int i = 0;
		while (i < len2 && i < len1) {
			if (row1[i] != row2[i])
				cct_setcolor(HIGHLIGHT);
			char output = row2[i];
			if (ch_in_str(row2[i], highlight_char, 4))
				output = 'X';
			else if (row2[i] == EOF)
				output = ' ';
			cout << output;
			cct_setcolor();
			i++;
		}
		while (i < len2) {
			cct_setcolor(HIGHLIGHT);
			char output = row2[i];
			if (ch_in_str(row2[i], highlight_char, 4))
				output = 'X';
			else if (row2[i] == EOF)
				output = ' ';
			cout << output;
			cct_setcolor();
			i++;
		}
		if (eof2)
			cout << "<EOF>" << endl;
		else
			cout << "<CR>" << endl;
	}

	return;
}
//====================================================
//函 数 名:print_rule
//功能描述:打印尺子
//输入参数:
//返 回 值:
//说    明:
//=====================================================
void print_rule(int length)
{
	cout << dec;
	int n = length / 10 + 1;
	cout << setw(8) << " ";
	for (int i = 0; i < n; i++)
		cout << setw(10) << setfill('-') << "-";
	cout << setfill(' ') << endl;;
	cout << setw(8) << " ";
	for (int i = 0; i < n; i++)
		cout << setw(10) << resetiosflags(ios::right) << setiosflags(ios::left) << i % 10;
	cout << endl;
	cout << setw(8) << " ";
	for (int i = 0; i < n; i++)
		for (int j = 0; j < 10; j++)
			cout << j;
	cout << endl;
	cout << setw(8) << " ";
	for (int i = 0; i < n; i++)
		cout << setw(10) << setfill('-') << "-";
	cout << setfill('-') << endl;
	return;
}
//====================================================
//函 数 名:print_hex
//功能描述:打印hex格式
//输入参数:
//返 回 值:
//说    明:
//=====================================================
void print_hex(char* buffer, int len, int eof)
{
	if (!len && eof) {
		cout << "<EOF>" << endl;
		return;
	}
	else if (!len) {
		cout << "<EMPTY>" << endl;
		return;
	}
	int i = 0;
	while (i + 16 <= len) {
		cout << setw(8) << setfill('0') << setiosflags(ios::right) << hex << i << " :";
		for (int j = 0; j < 8; j++)
			cout << " " << setw(2) << setfill('0') << setiosflags(ios::right) << hex << ((int)(unsigned char)buffer[i + j]);
		cout << " -";
		for (int j = 8; j < 16; j++)
			cout << " " << setw(2) << setfill('0') << setiosflags(ios::right) << hex << ((int)(unsigned char)buffer[i + j]);
		cout << "  ";
		for (int j = 0; j < 16; j++)
			if (buffer[i + j] < 33 || buffer[i + j]>136) {
				if (buffer[i + j] != ' ')
					cout << ".";
				else
					cout << ' ';
			}
			else
				putchar(buffer[i + j]);
		cout << endl;
		i += 16;
	}
	int temp = i;
	if (len % 16) {
		cout << setw(8) << setfill('0') << setiosflags(ios::right) << hex << i << " :";
		while (i < len) {
			if (i % 16 == 8)
				cout << " -";
			cout << " " << setw(2) << setfill('0') << setiosflags(ios::right) << hex << ((int)(unsigned char)buffer[i]);
			i++;
		}
		for (int j = 0; j < (16 - i % 16); j++)
			cout << "   ";
		if (i % 16 <= 8)
			cout << "  ";
		cout << "  ";
		while (temp < len) {
			if (buffer[temp] < 33 || buffer[temp]>136) {
				if (buffer[temp] != ' ')
					cout << ".";
				else
					cout << ' ';
			}
			else
				putchar(buffer[temp]);
			temp++;
		}
		if (len % 16)
			cout << endl;
	}
	return;
}
//====================================================
//函 数 名:display
//功能描述:向流中输入错误信息
//输入参数:
//返 回 值:
//说    明:
//=====================================================
void display(int error_type, char* buffer1, char* buffer2, int len1, int len2, int rown1, int rown2, int eof1, int eof2, int display_mode, int debug)
{
	int i = 0;
	int llen = int_len(rown1) + 1, rlen = int_len(rown2) + 1;
	switch (error_type) {
		case CHAR_DIFF:
			while (buffer1[i] == buffer2[i])
				i++;
			cout << dec << setfill(' ') << resetiosflags(ios::right) << "第[" << setiosflags(ios::left) << setw(llen) << rown1 << "/" << setw(rlen) << setiosflags(ios::right)
				<< rown2 << "]行 - 第[" << i << "]个字符开始有差异：" << endl;
			break;
		case MORE_CHAR:
			cout << dec << setfill(' ') << resetiosflags(ios::right) << "第[" << setiosflags(ios::left) << setw(llen) << rown1 << "/" << setw(rlen) << setiosflags(ios::right)
				<< rown2 << "]行 - 文件" << (len1 > len2 ? 1 : 2) << "的尾部有多余字符：" << endl;
			break;
		case NOT_END:
			cout << dec << setfill(' ') << resetiosflags(ios::right) << "第[" << setiosflags(ios::left) << setw(llen) << rown1 << "/" << setw(rlen) << setiosflags(ios::right)
				<< rown2 << "]行 - 文件" << (eof1 > eof2 ? "1已结束/文件2仍有内容：" : "1仍有内容/文件2已结束：") << endl;
			break;
	}
	if (display_mode == NORMAL_MODE || (debug && display_mode == NONE_MODE)) {
		print_row(buffer1, buffer2, len1, len2, eof1, eof2);
		cout << endl;
	}
	else if (display_mode == DETAIL_MODE) {
		print_rule((len1 > len2) ? len1 : len2);
		print_row(buffer1, buffer2, len1, len2, eof1, eof2);
		cout << "文件1(HEX) : " << endl;
		print_hex(buffer1, len1, eof1);
		cout << "文件2(HEX) : " << endl;
		print_hex(buffer2, len2, eof2);
		cout << endl;
	}
	return;
}

//====================================================
//函 数 名:diff_and_display
//功能描述:将两个字符数组进行对比
//输入参数:存储错误信息的流对象，待对比的字符数组即其长度,当前行数，展示方式，是否到达文件结尾
//返 回 值:
//说    明:有差异则返回1，无差异返回0
//=====================================================
int diff(char* buffer1, char* buffer2, int len1, int len2, int rown1, int rown2, int eof1, int eof2, int display_mode, int trim, int debug, int first)
{
	int i = 0;
	int error_type = NO_DIFF;
	while (i < len1 && i < len2) {
		if (buffer1[i] != buffer2[i]) {
			error_type = CHAR_DIFF;
			break;
		}
		i++;
	}
	if (len1 == len2 && !error_type)
		if (eof1 ^ eof2)
			error_type = NOT_END;
		else {
			if (debug) {
				//TODO:这里处理的是特判的情况，后面还需要进一步确认
				cout << dec << resetiosflags(ios::right) << "第[" << setiosflags(ios::left) << setw(int_len(rown1) + 1) << rown1 << "/" << setw(int_len(rown2) + 1)
					<< setiosflags(ios::right) << rown2 << "]行 - " << "一致: " << buffer1;
				if (eof1)
					cout << "<EOF>" << endl;
				else {
					if (!len1)
						cout << "<EMPTY>";
					cout << "<CR>" << endl;
					cout << endl;
				}
			}
			return 0;
		}
	else if (!error_type)
		error_type = MORE_CHAR;
	if (!debug && display_mode == NONE_MODE && error_type)
		return 1;
	else {
		if (error_type == NOT_END && (trim == TRIM_RIGHT || trim == TRIM_ALL) && (eof1 ^ eof2) && (!len1 || !len2)) {//特判
			if (!debug)
				cout << dec << resetiosflags(ios::right) << "第[" << setiosflags(ios::left) << setw(int_len(rown1) + 1) << rown1 << "/" << setw(int_len(rown2) + 1)
				<< setiosflags(ios::right) << rown2 << "]行 - 文件" << (eof1 > eof2 ? "1已结束/文件2仍有内容." : "1仍有内容/文件2已结束.") << endl;
			else
				cout << dec << resetiosflags(ios::right) << "第[" << setiosflags(ios::left) << setw(int_len(rown1) + 1) << rown1 << "/" << setw(int_len(rown2) + 1)
				<< setiosflags(ios::right) << rown2 << "]行 - 文件" << (eof1 > eof2 ? "1已结束/文件2仍有内容." : "1仍有内容/文件2已结束.") << endl;
		}
		else
			display(error_type, buffer1, buffer2, len1, len2, rown1, rown2, eof1, eof2, display_mode, debug);
		return 1;
	}
}
//====================================================
//函 数 名:split
//功能描述:遇到第一个key时截断
//输入参数:
//返 回 值:
//说    明:
//=====================================================
void split(char* const buffer, const char* const key)
{
	if (!buffer || !key)
		return;
	for (int i = 0; i < (int)strlen(buffer); i++)
		if (ch_in_str(buffer[i], key, strlen(key))) {
			buffer[i] = '\0';
			break;
		}
	return;
}
//====================================================
//函 数 名:trim
//功能描述:
//输入参数:
//返 回 值:
//说    明:option为1，2，3分别对应r，l，all
//=====================================================
void trim(char* const buffer, const char* const key, int option)
{
	if (option != 1 && option != 2 && option != 3)
		return;
	if (!buffer || !strlen(buffer) || !strlen(key))
		return;
	int l = 0, r = strlen(buffer) - 1;
	if (option == 1 || option == 3)
		while (ch_in_str(buffer[l], key, strlen(key))) {
			l++;
			if (l > r) {
				buffer[0] = '\0';
				return;
			}
		}
	if (option == 2 || option == 3)
		while (ch_in_str(buffer[r], key, strlen(key)) && r != l)
			r--;
	if (r == l) {
		buffer[0] = buffer[r];
		buffer[1] = '\0';
		return;
	}
	if (r != strlen(buffer) - 1)
		buffer[r + 1] = '\0';
	strcpy(buffer, buffer + l);
	return;
}
//====================================================
//函 数 名:to_upper
//功能描述:
//输入参数:
//返 回 值:
//说    明:转大写
//=====================================================
void to_upper(string& str)
{
	if (str.empty())
		return;
	for (int i = 0; i < (int)str.size(); i++)
		if (between(str[i], 'a', 'z'))
			str[i] = str[i] + 'A' - 'a';
	return;
}
//====================================================
//函 数 名:check
//功能描述:
//输入参数:
//返 回 值:
//说    明:负责base,以及firstline
//=====================================================
int check(const file wh, const student stu, const string src_folder, const string cno)
{
	string addr;
	addr = src_folder + cno + "-" + stu.code + "\\" + wh.file_name;
	ifstream file(addr, ios::in | ios::binary);
	//没法打开视为找不到文件
	if (!file)
		return NO;
	const int BUFFER_SIZE = 200;
	char buffer[BUFFER_SIZE];
	if (wh.type == RAR)
		return CORRECT;
	else if (wh.type == PDF) {
		file.read(buffer, 8);
		buffer[8] = '\0';
		file.close();
		if (!between(buffer[7], '0', '9'))
			return INVALID_PDF;
		buffer[7] = 0;
		if (!strcmp(buffer, "%PDF-1."))
			return CORRECT;
		else
			return INVALID_PDF;
	}
	int utf8 = 0;
	utf8 = utf8_check(file);
	if (utf8) {
		file.close();
		return INVALID_ENCODING;
	}
	file.clear();
	file.seekg(0, ios::beg);
	while (!file.eof()) {
		file.getline(buffer, BUFFER_SIZE);
		trim(buffer, " \t\r", 3);
		if (strlen(buffer))
			break;
	}
	file.close();
	trim(buffer, " \t\r", 3);
	if (strlen(buffer) == 1 || strlen(buffer) == 0)
		return NO_ANNO;
	if ((strlen(buffer) == 2 || strlen(buffer) == 3) && buffer[0] == '/' && buffer[1] == '/')
		return NO_THREE;
	if (buffer[0] == '/' && buffer[1] == '/')
		strcpy(buffer, buffer + 2);
	else {
		if (buffer[0] == '/' && buffer[1] == '*' && buffer[strlen(buffer) - 1] == '/' && buffer[strlen(buffer) - 2] == '*')
			trim(buffer, "/*", 3);
		/*	else if (buffer[0] == '/' && buffer[1] == '*')
				return INVALID_MULTI_ANNO;*/
		else
			return  NO_ANNO;

	}
	stringstream temp;
	string info[3];
	string check;
	int name = 1, code = 1, major = 1;
	temp << buffer;
	temp >> info[0] >> info[1] >> info[2] >> check;
	if (info[0].length() && info[1].length() && info[2].length() && !check.length()) {
		for (int i = 0; i < 3; i++)
			if (!strncmp((const char*)info[i].c_str(), (const char*)stu.code.c_str(), 7))
				code = 0;
		for (int i = 0; i < 3; i++)
			if (info[i] == stu.major || info[i] == stu.f_major)
				major = 0;
		for (int i = 0; i < 3; i++)
			if (!strncmp((const char*)info[i].c_str(), (const char*)stu.stu_name.c_str(), stu.stu_name.length()))
				name = 0;
	}
	else
		return NO_THREE;
	int result = 0;
	result += code * WRONG_NO + major * WRONG_CLASS + name * WRONG_NAME;
	return result;
	file.close();
}
//====================================================
//函 数 名:check_second
//功能描述:打印“正确”或错误信息
//输入参数:
//返 回 值:返回1说明没问题
//说    明:负责secondline
//=====================================================
int check_second(student stu, file wh, const string src_folder, const string cno, int correct)
{
	string addr;
	addr = src_folder + cno + "-" + stu.code + "\\" + wh.file_name;
	ifstream file(addr, ios::in | ios::binary);
	if (!file) {
		cout << "打开文件" << addr << "失败！" << endl;
		return -1;
	}
	const int BUFFER_SIZE = 200;
	char buffer[BUFFER_SIZE];
	//没法打开视为找不到文件
	if (wh.type != TXT)
		return -1;
	while (!file.eof()) {
		file.getline(buffer, BUFFER_SIZE);
		trim(buffer, " \t\r", 3);
		if (strlen(buffer))
			break;
	}
	while (!file.eof()) {
		file.getline(buffer, BUFFER_SIZE);
		trim(buffer, " \t\r", 3);
		if (strlen(buffer))
			break;
	}
	file.close();
	trim(buffer, " \t\r", 3);
	if (strlen(buffer) == 1 || strlen(buffer) == 0)
		return 0;
	if (buffer[0] == '/' && buffer[1] == '/')
		strcpy(buffer, buffer + 2);
	else
		if (buffer[0] == '/' && buffer[1] == '*' && buffer[strlen(buffer) - 1] == '/' && buffer[strlen(buffer) - 2] == '*')
			trim(buffer, "/*", 3);
		else 
			return 0;
	int i = 0;
	stringstream temp;
	string info;
	trim(buffer, " \t\r", 3);
	if (!strlen(buffer)) {
		if (correct)
			cout << "正确" << endl;
		return 1;
	}
	temp << buffer;
	vector<string> info_list;
	while (!temp.eof()) {
		temp >> info;
		info_list.push_back(info);
	}
	for (int i = 0; i < (int)info_list.size(); i++) {
		if (info_list[i] == stu.code) {
			if (correct)
				cout << "第[" << i + 1 << "]项写了自己" << endl << endl;
			return 1;
			break;
		}
		if (i == (int)info_list.size() - 1 && !(i % 2)) {
			if (correct)
				cout << "第[" << i / 2 << "]个学生后面的信息不全(只读到一项)，后续内容忽略" << endl;
			return 1;
		}
		if (!(i % 2)) {
			if ((int)info_list[i].length() != 7) {
				if (correct) {
					info_list[i] += "]";
					cout << "第" << i / 2 + 1 << "位同学的学号" << "[" << info_list[i] << "不是7位，后续内容忽略" << endl;
				}
				return 1;
				break;
			}
			for (int j = 0; j < (int)info_list[i].length(); j++)
				if (!between(info_list[i][j], '0', '9')) {
					if (correct) {
						info_list[i] += "]";
						if (info_list[i].length() >= 64) {
							info_list[i].resize(64);
							info_list[i][63] = ']';
						}
						cout << "第" << i / 2 + 1 << "位同学的学号" << "[" << info_list[i] << "中有非数字存在，后续内容忽略" << endl;
					}
					return 1;
					break;
				}


		}
	}
	if (correct)
		cout << "正确" << endl;
	return 1;
}
//====================================================
//函 数 名:get_name_list
//功能描述:
//输入参数:
//返 回 值:
//说    明:提取互验名单
//=====================================================
vector<student> get_name_list(const file wh, const student stu, const string src_folder, const string cno)
{
	string addr;
	vector<student> name_list;
	addr = src_folder + cno + "-" + stu.code + "\\" + wh.file_name;
	ifstream file(addr, ios::in | ios::binary);
	if (!file)
		return name_list;
	if (utf8_check(file)) {
		file.close();
		return name_list;
	}
	file.clear();
	file.seekg(ios::beg);
	const int BUFFER_SIZE = 200;
	char buffer[BUFFER_SIZE];
	//没法打开视为找不到文件
	if (wh.type != TXT)
		return name_list;
	file.getline(buffer, BUFFER_SIZE);
	file.getline(buffer, BUFFER_SIZE);
	file.close();
	trim(buffer, " \t\r", 3);
	if (strlen(buffer) == 1 || strlen(buffer) == 0)
		return name_list;
	if (buffer[0] == '/' && buffer[1] == '/')
		strcpy(buffer, buffer + 2);
	else
		if (buffer[0] == '/' && buffer[1] == '*' && buffer[strlen(buffer) - 1] == '/' && buffer[strlen(buffer) - 2] == '*')
			trim(buffer, "/*", 3);
		else
			return name_list;
	int i = 0;
	stringstream temp;
	string info;
	student bro;
	trim(buffer, " \t\r", 3);
	temp << buffer;
	while (!temp.eof()) {
		temp >> info;
		if (!(i % 2)) {
			if (info.length() != 7)
				break;
			for (int j = 0; j < (int)info.length(); j++)
				if (!between(info[j], '0', '9'))
					break;
			bro.code = info;
		}
		else {
			bro.stu_name = info;
			name_list.push_back(bro);
		}
		i++;
	}
	return name_list;

}
//====================================================
//函 数 名:check_out
//功能描述:
//输入参数:
//返 回 值:1为没有被抛弃，0为被抛弃,-1即对方没写对名字
//说    明:判断是否被抛弃
//=====================================================
int check_out(const file wh, const student stu, const student bro, const string src_folder, const string cno)
{
	vector<student> bro_list;
	bro_list = get_name_list(wh, bro, src_folder, cno);
	for (int i = 0; i < (int)bro_list.size(); i++) {
		if (bro_list[i].code == bro.code)
			return 0;
		if (bro_list[i].code.length() != 7)
			return 0;
		int flag = 0;
		for (int j = 0; j < 7; j++)
			if (!between(bro_list[i].code[j], '0', '9'))
				flag = 1;
		if (flag)
			return 0;
		if (bro_list[i].code == stu.code) {
			if (bro_list[i].stu_name == stu.stu_name)
				return 1;
			else
				return -1;
		}
	}
	return 0;
}
//====================================================
//函 数 名:utf8_check
//功能描述:
//输入参数:
//返 回 值:1为utf_8格式
//说    明:
//=====================================================
int utf8_check(ifstream& file)
{
	char buffer[10];
	file.seekg(0, ios::beg);
	file.read(buffer, 3);
	buffer[3] = 0;
	if (!strcmp(buffer, "\xef\xbb\xbf"))
		return 1;
	file.seekg(0, ios::beg);
	unsigned char one = 0b10000000;
	unsigned char two = 0b11000000;
	unsigned char three = 0b11100000;
	unsigned char four = 0b11110000;
	unsigned char five = 0b11111000;
	unsigned char six = 0b11111100;
	unsigned char seven = 0b11111110;
	unsigned char now;
	now = file.get();
	int n = 0;
	int flag = 0;
	while (!file.eof()) {
		if (now < one)
			n = 0;
		else if (now >= two && now < three)
			n = 1;
		else if (now >= three && now < four)
			n = 2;
		else if (now >= four && now < five)
			n = 3;
		else if (now >= five && now < six)
			n = 4;
		else if (now >= six && now < seven)
			n = 5;
		while (n--) {
			flag = 1;
			now = file.get();
			if (now >= one && now < two)
				continue;
			else
				return 0;
		}
		now = file.get();
	}
	if (flag)
		return 1;
	else
		return 0;
}
