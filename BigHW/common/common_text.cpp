/* 2254298 ´óÊı¾İ ·¶äì */
#define _CRT_SECURE_NO_WARNINGS
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
int ch_in_str(char ch,const char*  const str, int strlen)
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
	if (CR_CRLF_not_equal && ((trim == TRIM_RIGHT) ||( trim == TRIM_ALL)) && (buffer[inputn - 1] == '\r'))
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
		cout << setw(10) << resetiosflags(ios::right) << setiosflags(ios::left) << i%10;
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
	for (int i = 0; i <(int) strlen(buffer); i++) 
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
void trim(char*const buffer, const char* const key,int option)
{
	if (option != 1 && option != 2 && option != 3)
		return;
	if (!buffer||!strlen(buffer)||!strlen(key))
		return;
	int l = 0, r = strlen(buffer) - 1;
	if (option == 1 || option == 3)
		while (ch_in_str(buffer[l++], key, strlen(key)))
			if (l > r) {
				buffer[0] = '\0';
				return;
			}
	if (option == 2 || option == 3)
		while (ch_in_str(buffer[r--], key, strlen(key)) && r != l)
			;
	if (r == l) {
		buffer[0] = buffer[r];
		buffer[1] = '\0';
		return;
	}
	if (r != strlen(buffer) - 1)
		buffer[r + 1] = '0';
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
	for (int i = 0; i < str.size(); i++) 
		if (between(str[i], 'a', 'z'))
			str[i] = str[i] + 'A' - 'a';
	return;
}
