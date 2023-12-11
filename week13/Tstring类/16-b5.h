/* 2254298 大数据 范潇 */

#pragma once

#include <iostream>
using namespace std;

/* 补全TString类的定义，所有成员函数均体外实现，不要在此处体内实现 */
class TString {
private:
	char* content;
	int   len;
	/* 根据需要定义所需的数据成员、成员函数、友元函数等 */
public:
	/* 根据需要定义所需的数据成员、成员函数、友元函数等 */
	~TString();
	//5.3.1
	TString();
	TString(const char * const);
	TString(const TString&);
	//5.3.2
	friend istream& operator >> (istream&, TString&);
	//5.3.3
	friend ostream& operator<<(ostream&, const TString&);
	//5.3.4
	const char* c_str()const;
	//5.3.5
	TString& operator = (const TString&);
	TString& operator = (const char * const);
	//5.3.6
	friend const TString operator + (const char * const, const TString&);
	friend const TString operator + (const TString&, const char * const);
	friend const TString operator + (const TString&, const TString&);
	friend const TString operator + (const char, const TString&);
	friend const TString operator + (const TString&, const char);
	//5.3.7
	TString& operator += (const TString&);
	TString& operator += (const char );
	//5.3.8
	void append(const TString&);
	void append(const char);
	//5.3.9
	friend const TString operator - (const TString&, const TString&);
	//		friend const TString& operator - ( const TString &,const char * const*);
			friend const TString operator - ( const TString &,const char );
			//5.3.10
	TString& operator -= (const TString&);
	TString& operator -= (const char );
	//5.3.11
	const TString operator * (const int);
	//5.3.12
	TString& operator *=(const int);
	//5.3.13
	friend const TString operator ! (const TString&);
	//5.3.14
	friend int operator > (const TString&, const TString&);
	friend int operator >= (const TString&, const TString&);
	friend int operator <= (const TString&, const TString&);
	friend int operator < (const TString&, const TString&);
	friend int operator == (const TString&, const TString&);
	friend int operator != (const TString&, const TString&);
	//5.3.15
	int length()const;
	//5.3.16
	char& operator [](int);
};

/* 如果有其它全局函数需要声明，写于此处 */

/* 如果有需要的宏定义、只读全局变量等，写于此处 */
int TStringLen(const TString&);
