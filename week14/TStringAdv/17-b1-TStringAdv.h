/* 2254298 大数据 范潇 */
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include"17-b1-TString.h"
#define FOO -123456
class TStringAdv: public TString {
public:
	TStringAdv();
	TStringAdv(const char* const);
	TStringAdv(const TStringAdv&);
	TStringAdv(const TString&);
	TStringAdv& assign(const TStringAdv& ts2);
	TStringAdv& assign(const char* s);
	TStringAdv& append(const TStringAdv& ts2);
	TStringAdv& append(const char* s);
	TStringAdv& append(const char&c);
	TStringAdv& insert(const TStringAdv& ts2, int pos);
	TStringAdv& insert(const char* s, int pos);
	TStringAdv& insert(const char& c, int pos);
	TStringAdv& erase(const TStringAdv& ts2);
	TStringAdv& erase(const char *s);
	TStringAdv& erase(const char&c);
	TStringAdv substr(const int pos, const int len =FOO)const;
	char& at(const int n);
//	friend int TStringAdvLen(const TStringAdv&);
};
int TStringAdvLen(const TString&);//为什么不会自动调用转换构造函数，从而不用写这个函数？
