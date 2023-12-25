#pragma once
#include<fstream>
#include<iostream>
#include<sstream>
#include<iomanip>
#include<vector>
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

#define ERROR_TYPE_MAX_NUM 20
#define CORRECT 0
#define	NO 9
#define INVALID_ENCODING 1
#define INVALID_PDF 2
#define NO_ANNO 3
#define WRONG_NO 4
#define WRONG_NAME 40
#define WRONG_CLASS 400
#define NO_THREE 5
#define NAME_POS 6
#define CLASS_POS 7
#define NO_SEC_ANNO 8
#define INVALID_MULTI_ANNO 10

#define TXT  0
#define RAR  1
#define PDF 2
struct file {
	string file_name;
	int type;
};
struct student {
	string stu_name;
	string code;
	string major;
	string f_major;
};

enum system { WINDOWS = 0,LINUX };
int get_line(ifstream& infile, char* buffer, int& inputn, int trim, char* trim_ch, int ch_num, char* end, int end_len, enum system &sys,int maxn = 0x10000 ,int CR_CRLF_not_equal=0);
int diff( char* buffer1, char* buffer2, int len1, int len2, int rown1, int rown2, int eof1, int eof2, int display_mode,int trim,int debug=0,int first = 0);
void display( int error_type,char* buffer1, char* buffer2, int len1, int len2, int rown1, int rown2, int eof1, int eof2, int display_mode,int debug = 0);
int int_len(int num);
void split(char* const buffer, const char* const key);
void trim(char* const buffer, const char* const key, int option);
int ch_in_str(char ch, const char* const str, int strlen);
void to_upper(string& str);
int check(const file wh, const student stu, const string src_folder, const string cno);
int check_second(student stu, file wh,const string src_folder,const string cno,int correct);
vector<student> get_name_list(const file wh, const student stu, const string src_folder, const string cno);
int check_out(const file wh, const student stu, const student bro, const string src_folder, const string cno);
int utf8_check(ifstream& file);
