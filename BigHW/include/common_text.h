#pragma once
#include<fstream>
#include<iostream>
#include<sstream>
#include<iomanip>
using namespace std;
#define TRIM_RIGHT 1
#define TRIM_LEFT 2
#define TRIM_ALL 3
#define TRIM_NONE 0
#define NONE_MODE 0
#define NORMAL_MODE 1
#define DETAIL_MODE 2
#define NO_DIFF 0
#define CHAR_DIFF 1
#define MORE_CHAR 2
#define NOT_END 3
#define HIGHLIGHT_BG 14
#define HIGHLIGHT_FG 12
#define HIGHLIGHT HIGHLIGHT_BG,HIGHLIGHT_FG
#define RULE_OFFSET 8
int get_line(ifstream& infile, char* buffer, int& inputn, int trim, char* trim_ch, char ch_num, char* end, int end_len, int maxn = 0xFFFF ,int CR_CRLF_not_equal=0);
int diff( char* buffer1, char* buffer2, int len1, int len2, int rown1, int rown2, int eof1, int eof2, int display_mode,int trim);
void display( int error_type,char* buffer1, char* buffer2, int len1, int len2, int rown1, int rown2, int eof1, int eof2, int display_mode);
