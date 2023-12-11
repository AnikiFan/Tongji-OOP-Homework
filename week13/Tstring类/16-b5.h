/* 2254298 ������ ���� */

#pragma once

#include <iostream>
using namespace std;

/* ��ȫTString��Ķ��壬���г�Ա����������ʵ�֣���Ҫ�ڴ˴�����ʵ�� */
class TString {
private:
	char* content;
	int   len;
	/* ������Ҫ������������ݳ�Ա����Ա��������Ԫ������ */
public:
	/* ������Ҫ������������ݳ�Ա����Ա��������Ԫ������ */
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

/* ���������ȫ�ֺ�����Ҫ������д�ڴ˴� */

/* �������Ҫ�ĺ궨�塢ֻ��ȫ�ֱ����ȣ�д�ڴ˴� */
int TStringLen(const TString&);
