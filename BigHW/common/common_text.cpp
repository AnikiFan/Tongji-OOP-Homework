/* 2254298 ´óÊı¾İ ·¶äì */
#define _CRT_SECURE_NO_WARNINGS
#include<vector>
#include"../include/common_text.h"
#include"../include/cmd_console_tools.h"
#include"../include/common_calc.h"
//====================================================
//º¯ Êı Ãû:int_len
//¹¦ÄÜÃèÊö:·µ»ØÕûÊıµÄ³¤¶È
//ÊäÈë²ÎÊı: 
//·µ »Ø Öµ:
//Ëµ    Ã÷:°üÀ¨·ûºÅ
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
//º¯ Êı Ãû:ch_in_str
//¹¦ÄÜÃèÊö:ÅĞ¶ÏÖ¸¶¨×Ö·ûÊÇ·ñÔÚ¸ø¶¨×Ö·û´®ÖĞ
//ÊäÈë²ÎÊı:
//·µ »Ø Öµ:1ÎªÕæ£¬0Îª¼Ù
//Ëµ    Ã÷:
//=====================================================
int ch_in_str(char ch, const char* const str, int strlen)
{
	for (int i = 0; i < strlen; i++)
		if (str[i] == ch)
			return 1;
	return 0;
}
//====================================================
//º¯ Êı Ãû:get_line
//¹¦ÄÜÃèÊö:´Ó¸ø¶¨ÎÄ¼şÖ¸Õë£¬¶ÁÈ¡ÖÁÖ¸¶¨×Ö·ûÎªÖ¹
//ÊäÈë²ÎÊı:ÎÄ¼şÖ¸Õë£¬´æ´¢ÊäÈëµÄÊı×é£¬ÒÔ¼°½ÓÊÕ¶ÁÈë×Ö·ûÊıµÄint£¬½áÊø×Ö·û£¨´®£©£¬trim·½Ê½£¬trim×Ö·û¼°Æä¸öÊı£¬
//·µ »Ø Öµ:,µ±·µ»Ø1Ê±±íÊ¾¶Áµ½ÎÄ¼ş½áÎ²£¨ÈËÎªÌí¼ÓµÄEOF²»Ëã£©£¬Èô¶ÁÈë×Ö·ûÊı³¬¹ımaxnÔò·Å»Ø-1£¬ÆäÓàÇé¿ö·µ»Ø0
//Ëµ    Ã÷:¶ÁÈë×Ö·ûÊı£¨²»°üÀ¨½áÊø×Ö·ûºÍ±»trim×Ö·û£©
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
			//ÓÃÓÚ´¦Àídemoµ±×îºó×îºóÒ»ĞĞÎªµ¥¶ÀÒ»¸ö\rÊ±²¢²»»á´òÓ¡µÄÇé¿ö£¬Èô½â¾ö£¬ÔòÓ¦¸Ã·Åµ½(comp_p==end_len)µÄÌõ¼ş·ÖÖ§ÖĞ
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
	//Õı³£Çé¿öÓ¦¸ÃÔÚwhileÑ­»·ÌåÄÚÒòÎª¶ÁÈëend¶øreturn
	return 0;
}
//====================================================
//º¯ Êı Ãû:print_row
//¹¦ÄÜÃèÊö:´òÓ¡Ò»ĞĞÖĞµÄÄÚÈİ
//ÊäÈë²ÎÊı:
//·µ »Ø Öµ:
//Ëµ    Ã÷:º¬¸ßÁÁ
//=====================================================
void print_row(char* row1, char* row2, int len1, int len2, int eof1, int eof2)
{
	char highlight_char[5] = "\r\v\b\a";
	cout << "ÎÄ¼ş1 : ";
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
				output = 'ÿ';
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
				output = 'ÿ';
			cout << output;
			cct_setcolor();
			i++;
		}
		if (eof1)
			cout << "<EOF>" << endl;
		else
			cout << "<CR>" << endl;
	}
	cout << "ÎÄ¼ş2 : ";
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
				output = 'ÿ';
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
				output = 'ÿ';
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
//º¯ Êı Ãû:print_rule
//¹¦ÄÜÃèÊö:´òÓ¡³ß×Ó
//ÊäÈë²ÎÊı:
//·µ »Ø Öµ:
//Ëµ    Ã÷:
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
//º¯ Êı Ãû:print_hex
//¹¦ÄÜÃèÊö:´òÓ¡hex¸ñÊ½
//ÊäÈë²ÎÊı:
//·µ »Ø Öµ:
//Ëµ    Ã÷:
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
//º¯ Êı Ãû:display
//¹¦ÄÜÃèÊö:ÏòÁ÷ÖĞÊäÈë´íÎóĞÅÏ¢
//ÊäÈë²ÎÊı:
//·µ »Ø Öµ:
//Ëµ    Ã÷:
//=====================================================
void display(int error_type, char* buffer1, char* buffer2, int len1, int len2, int rown1, int rown2, int eof1, int eof2, int display_mode, int debug)
{
	int i = 0;
	int llen = int_len(rown1) + 1, rlen = int_len(rown2) + 1;
	switch (error_type) {
		case CHAR_DIFF:
			while (buffer1[i] == buffer2[i])
				i++;
			cout << dec << setfill(' ') << resetiosflags(ios::right) << "µÚ[" << setiosflags(ios::left) << setw(llen) << rown1 << "/" << setw(rlen) << setiosflags(ios::right)
				<< rown2 << "]ĞĞ - µÚ[" << i << "]¸ö×Ö·û¿ªÊ¼ÓĞ²îÒì£º" << endl;
			break;
		case MORE_CHAR:
			cout << dec << setfill(' ') << resetiosflags(ios::right) << "µÚ[" << setiosflags(ios::left) << setw(llen) << rown1 << "/" << setw(rlen) << setiosflags(ios::right)
				<< rown2 << "]ĞĞ - ÎÄ¼ş" << (len1 > len2 ? 1 : 2) << "µÄÎ²²¿ÓĞ¶àÓà×Ö·û£º" << endl;
			break;
		case NOT_END:
			cout << dec << setfill(' ') << resetiosflags(ios::right) << "µÚ[" << setiosflags(ios::left) << setw(llen) << rown1 << "/" << setw(rlen) << setiosflags(ios::right)
				<< rown2 << "]ĞĞ - ÎÄ¼ş" << (eof1 > eof2 ? "1ÒÑ½áÊø/ÎÄ¼ş2ÈÔÓĞÄÚÈİ£º" : "1ÈÔÓĞÄÚÈİ/ÎÄ¼ş2ÒÑ½áÊø£º") << endl;
			break;
	}
	if (display_mode == NORMAL_MODE || (debug && display_mode == NONE_MODE)) {
		print_row(buffer1, buffer2, len1, len2, eof1, eof2);
		cout << endl;
	}
	else if (display_mode == DETAIL_MODE) {
		print_rule((len1 > len2) ? len1 : len2);
		print_row(buffer1, buffer2, len1, len2, eof1, eof2);
		cout << "ÎÄ¼ş1(HEX) : " << endl;
		print_hex(buffer1, len1, eof1);
		cout << "ÎÄ¼ş2(HEX) : " << endl;
		print_hex(buffer2, len2, eof2);
		cout << endl;
	}
	return;
}

//====================================================
//º¯ Êı Ãû:diff_and_display
//¹¦ÄÜÃèÊö:½«Á½¸ö×Ö·ûÊı×é½øĞĞ¶Ô±È
//ÊäÈë²ÎÊı:´æ´¢´íÎóĞÅÏ¢µÄÁ÷¶ÔÏó£¬´ı¶Ô±ÈµÄ×Ö·ûÊı×é¼´Æä³¤¶È,µ±Ç°ĞĞÊı£¬Õ¹Ê¾·½Ê½£¬ÊÇ·ñµ½´ïÎÄ¼ş½áÎ²
//·µ »Ø Öµ:
//Ëµ    Ã÷:ÓĞ²îÒìÔò·µ»Ø1£¬ÎŞ²îÒì·µ»Ø0
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
				//TODO:ÕâÀï´¦ÀíµÄÊÇÌØÅĞµÄÇé¿ö£¬ºóÃæ»¹ĞèÒª½øÒ»²½È·ÈÏ
				cout << dec << resetiosflags(ios::right) << "µÚ[" << setiosflags(ios::left) << setw(int_len(rown1) + 1) << rown1 << "/" << setw(int_len(rown2) + 1)
					<< setiosflags(ios::right) << rown2 << "]ĞĞ - " << "Ò»ÖÂ: " << buffer1;
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
		if (error_type == NOT_END && (trim == TRIM_RIGHT || trim == TRIM_ALL) && (eof1 ^ eof2) && (!len1 || !len2)) {//ÌØÅĞ
			if (!debug)
				cout << dec << resetiosflags(ios::right) << "µÚ[" << setiosflags(ios::left) << setw(int_len(rown1) + 1) << rown1 << "/" << setw(int_len(rown2) + 1)
				<< setiosflags(ios::right) << rown2 << "]ĞĞ - ÎÄ¼ş" << (eof1 > eof2 ? "1ÒÑ½áÊø/ÎÄ¼ş2ÈÔÓĞÄÚÈİ." : "1ÈÔÓĞÄÚÈİ/ÎÄ¼ş2ÒÑ½áÊø.") << endl;
			else
				cout << dec << resetiosflags(ios::right) << "µÚ[" << setiosflags(ios::left) << setw(int_len(rown1) + 1) << rown1 << "/" << setw(int_len(rown2) + 1)
				<< setiosflags(ios::right) << rown2 << "]ĞĞ - ÎÄ¼ş" << (eof1 > eof2 ? "1ÒÑ½áÊø/ÎÄ¼ş2ÈÔÓĞÄÚÈİ." : "1ÈÔÓĞÄÚÈİ/ÎÄ¼ş2ÒÑ½áÊø.") << endl;
		}
		else
			display(error_type, buffer1, buffer2, len1, len2, rown1, rown2, eof1, eof2, display_mode, debug);
		return 1;
	}
}
//====================================================
//º¯ Êı Ãû:split
//¹¦ÄÜÃèÊö:Óöµ½µÚÒ»¸ökeyÊ±½Ø¶Ï
//ÊäÈë²ÎÊı:
//·µ »Ø Öµ:
//Ëµ    Ã÷:
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
//º¯ Êı Ãû:trim
//¹¦ÄÜÃèÊö:
//ÊäÈë²ÎÊı:
//·µ »Ø Öµ:
//Ëµ    Ã÷:optionÎª1£¬2£¬3·Ö±ğ¶ÔÓ¦r£¬l£¬all
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
//º¯ Êı Ãû:to_upper
//¹¦ÄÜÃèÊö:
//ÊäÈë²ÎÊı:
//·µ »Ø Öµ:
//Ëµ    Ã÷:×ª´óĞ´
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
//º¯ Êı Ãû:check
//¹¦ÄÜÃèÊö:
//ÊäÈë²ÎÊı:
//·µ »Ø Öµ:
//Ëµ    Ã÷:¸ºÔğbase,ÒÔ¼°firstline
//=====================================================
int check(const file wh, const student stu, const string src_folder, const string cno)
{
	string addr;
	addr = src_folder + cno + "-" + stu.code + "\\" + wh.file_name;
	ifstream file(addr, ios::in | ios::binary);
	//Ã»·¨´ò¿ªÊÓÎªÕÒ²»µ½ÎÄ¼ş
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
	else
		if (buffer[0] == '/' && buffer[1] == '*' && buffer[strlen(buffer) - 1] == '/' && buffer[strlen(buffer) - 2] == '*')
			trim(buffer, "/*", 3);
		else
			return  NO_ANNO;
	stringstream temp;
	string info[3];
	string check;
	int name = 1, code = 1, major = 1;
	temp << buffer;
	temp >> info[0] >> info[1] >> info[2] >> check;
	if (info[0].length() && info[1].length() && info[2].length() && !check.length()) {
		for (int i = 0; i < 3; i++)
			if (info[i] == stu.code)
				code = 0;
		for (int i = 0; i < 3; i++)
			if (info[i] == stu.major)
				major = 0;
		for (int i = 0; i < 3; i++)
			if (info[i] == stu.stu_name)
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
//º¯ Êı Ãû:check_second
//¹¦ÄÜÃèÊö:´òÓ¡¡°ÕıÈ·¡±»ò´íÎóĞÅÏ¢
//ÊäÈë²ÎÊı:
//·µ »Ø Öµ:·µ»Ø1ËµÃ÷Ã»ÎÊÌâ
//Ëµ    Ã÷:¸ºÔğsecondline
//=====================================================
int check_second(student stu, file wh, const string src_folder, const string cno, int correct)
{
	string addr;
	addr = src_folder + cno + "-" + stu.code + "\\" + wh.file_name;
	ifstream file(addr, ios::in | ios::binary);
	if (!file) {
		cout << "´ò¿ªÎÄ¼ş" << addr << "Ê§°Ü£¡" << endl;
		return -1;
	}
	const int BUFFER_SIZE = 200;
	char buffer[BUFFER_SIZE];
	//Ã»·¨´ò¿ªÊÓÎªÕÒ²»µ½ÎÄ¼ş
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
	temp << buffer;
	vector<string> info_list;
	while (!temp.eof()) {
		temp >> info;
		info_list.push_back(info);
	}
	for (int i = 0; i < (int)info_list.size(); i++) {
		if (i == (int)info_list.size() - 1 && !(i % 2)) {
			if (correct)
				cout << "µÚ[" << i / 2 << "]¸öÑ§ÉúºóÃæµÄĞÅÏ¢²»È«(Ö»¶Áµ½Ò»Ïî)£¬ºóĞøÄÚÈİºöÂÔ" << endl;
			return 1;
		}
		if (!(i % 2)) {
			if ((int)info_list[i].length() != 7) {
				if (correct) {
					info_list[i] += "]";
					if (info_list[i].length() >= 64) {
						info_list[i].resize(64);
						info_list[i][63] = ']';
					}
					cout << "µÚ" << i / 2 + 1 << "Î»Í¬Ñ§µÄÑ§ºÅ" << "[" << info_list[i] << "²»ÊÇ7Î»£¬ºóĞøÄÚÈİºöÂÔ" << endl;
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
						cout << "µÚ" << i / 2 + 1 << "Î»Í¬Ñ§µÄÑ§ºÅ" << "[" << info_list[i] << "ÖĞÓĞ·ÇÊı×Ö´æÔÚ£¬ºóĞøÄÚÈİºöÂÔ" << endl;
					}
					return 1;
					break;
				}
		}
	}
	if (correct)
		cout << "ÕıÈ·" << endl;
	return 1;
}
//====================================================
//º¯ Êı Ãû:get_name_list
//¹¦ÄÜÃèÊö:
//ÊäÈë²ÎÊı:
//·µ »Ø Öµ:
//Ëµ    Ã÷:ÌáÈ¡»¥ÑéÃûµ¥
//=====================================================
vector<student> get_name_list(const file wh, const student stu, const string src_folder, const string cno)
{
	string addr;
	vector<student> name_list;
	addr = src_folder + cno + "-" + stu.code + "\\" + wh.file_name;
	ifstream file(addr, ios::in | ios::binary);
	if (!file) 
		return name_list;
	const int BUFFER_SIZE = 200;
	char buffer[BUFFER_SIZE];
	//Ã»·¨´ò¿ªÊÓÎªÕÒ²»µ½ÎÄ¼ş
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
//º¯ Êı Ãû:check_out
//¹¦ÄÜÃèÊö:
//ÊäÈë²ÎÊı:
//·µ »Ø Öµ:1ÎªÃ»ÓĞ±»Å×Æú£¬0Îª±»Å×Æú
//Ëµ    Ã÷:ÅĞ¶ÏÊÇ·ñ±»Å×Æú
//=====================================================
int check_out(const file wh, const student stu, const student bro, const string src_folder, const string cno)
{
	vector<student> bro_list;
	bro_list = get_name_list(wh, bro, src_folder, cno);
	for (int i = 0; i < (int)bro_list.size(); i++)
		if (bro_list[i].code == stu.code)
			return 1;
	return 0;
}
//====================================================
//º¯ Êı Ãû:utf8_check
//¹¦ÄÜÃèÊö:
//ÊäÈë²ÎÊı:
//·µ »Ø Öµ:1Îªutf_8¸ñÊ½
//Ëµ    Ã÷:
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
