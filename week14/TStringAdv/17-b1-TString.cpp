/* 2254298 大数据 范潇 */

/* 允许添加需要的头文件、宏定义等 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include "17-b1-TString.h"
using namespace std;

/* 给出 TString 类的所有成员函数的体外实现 */
TString:: ~TString()
{
	if (content)
		delete[]content;
}
TString::TString()
{
	len = 0;
	content = NULL;
}
TString::TString(const char* const input)
{
	if (!input) {
		len = 0;
		content = NULL;
		return;
	}
	len = (int)strlen(input);
	content = new char[len + 1] {0};
	if (!content) {
		cout << "OVERFLOW" << endl;
		getchar();
	}
	strcpy(content, input);
}
TString::TString(const TString& input)
{
	len = input.len;
	if (!len) {
		len = 0;
		content = NULL;
		return;
	}
	content = new char[len + 1] {0};
	if (!content) {
		cout << "OVERFLOW" << endl;
		getchar();
	}
	strcpy(content, input.content);
}
istream& operator >>(istream& in, TString& s)
{
	s.len = 0;
	if (s.content) {
		delete[]s.content;
		s.content = NULL;
	}
	char input;
	char* temp = NULL;
	input = in.get();
	while (input != ' ' && input != '\r' && input != '\n') {
		s.len++;
		if (s.content)
			temp = s.content;
		s.content = new char[s.len + 1] {0};
		if (!s.content) {
			cout << "OVERFLOW" << endl;
			getchar();
		}
		if (temp) {
			strcpy(s.content, temp);
			delete[]temp;
		}
		s.content[s.len - 1] = input;
		input = in.get();
	}
	if (!s.len)
		s.content = NULL;
	return in;
}
ostream& operator << (ostream& out, const TString& s)
{
	if (!s.len)
		out << "<NULL>" << endl;
	else
		cout << s.content << endl;
	return out;
}
const char* TString::c_str()const
{
	return content;
}
TString& TString::operator=(const TString& s)
{
	if ((!s.len && !len) || (s.len && len && !strcmp(s.content, content)))
		return *this;
	len = s.len;
	if (!len) {
		content = NULL;
		return *this;
	}
	if (content)
		delete[]content;
	content = new char[len + 1] {0};
	if (!content) {
		cout << "OVERFLOW" << endl;
		getchar();
	}
	memcpy(content, s.content,len); 
	content[len] = 0;
	return *this;
}
TString& TString::operator=(const char* const s)
{
	if (!s) {
		len = 0;
		content = NULL;
		return *this;
	}
	len = (int)strlen(s);
	if (content)
		delete[]content;
	content = new char[len + 1] {0};
	if (!content) {
		cout << "OVERFLOW" << endl;
		getchar();
	}
	memcpy(content, s,len);
	content[len] = 0;
	return *this;
}
const TString operator +(const char* const s1, const TString& s2)
{
	TString out;
	if (s1)
		out.len = (int)strlen(s1) + s2.len;
	else
		out.len = s2.len;
	if (!out.len)
		out.content = NULL;
	else {
		if (out.content)
			delete[]out.content;

		out.content = new char[out.len + 1] {0};
		if (!out.content) {
			cout << "OVERFLOW" << endl;
			getchar();
			return out;
		}
		if (s1) {
			memcpy(out.content, s1,strlen(s1));
			if (s2.content) {
				memcpy(out.content+strlen(s1), s2.content,s2.len);
				out.content[out.len] = 0;
			}
		}
		else {
			memcpy(out.content, s2.content,s2.len);
			out.content[out.len ] = 0;
		}
	}
	return out;
}
const TString operator +(const TString& s1, const char* const s2)
{
	TString out;
	if (s2)
		out.len = s1.len + (int)strlen(s2);
	else
		out.len = s1.len;
	if (!out.len)
		out.content = NULL;
	else {
		if (out.content)
			delete[]out.content;
		out.content = new char[out.len + 1] {0};
		if (!out.content) {
			cout << "OVERFLOW" << endl;
			getchar();
			return out;
		}
		if (s1.content) {
			memcpy(out.content, s1.content,s1.len);
			if (s2) {
				memcpy(out.content+s1.len, s2,strlen(s2));
				out.content[out.len ] = 0;
			}
		}
		else {
			memcpy(out.content, s2,strlen(s2));
			out.content[out.len ] = 0;
		}
	}
	return out;
}
const TString operator +(const TString& s1, const TString& s2)
{
	TString out;
	out.len = s1.len + s2.len;
	if (!out.len)
		out.content = NULL;
	else {
		out.content = new char[out.len + 1] {0};
		if (!out.content) {
			cout << "OVERFLOW" << endl;
			getchar();
			return out;
		}
		if (s1.content) {
			strcpy(out.content, s1.content);
			if (s2.content)
				strcat(out.content, s2.content);
		}
		else
			strcpy(out.content, s2.content);
	}
	return out;
}
const TString operator +(const char ch, const TString& s)
{
	TString out ;
	out.len = 1;
	out.content = new char[2] {0};
	if (!out.content) {
		cout << "OVERFLOW" << endl;
		getchar();
		return s;
	}
	out.content[0] = ch;
	return out+s;
}
const TString operator +(const TString& s, const char ch)
{
	TString out ;
	out.len = 1;
	out.content = new char[2] {0};
	if (!out.content) {
		cout << "OVERFLOW" << endl;
		getchar();
		return s;
	}
	out.content[0] = ch;
	return s+out;
}
TString& TString::operator += (const char ch)
{
	TString out;
	out.len = 1;
	out.content = new char[2] {0};
	if (!out.content) {
		cout << "OVERFLOW" << endl;
		getchar();
		return *this;
	}
	out.content[0] = ch;
	return *this = *this+out;
}
TString& TString::operator += (const TString& s)
{
	(*this) = *this + s;
	return *this;
}
//void TString::append(const TString& s)
//{
//	if (!s.len)
//		return;
//	if (len) {
//		len += s.len;
//		char* temp = content;
//		content = new char[len + 1] {0};
//		if (!content) {
//			cout << "OVERFLOW" << endl;
//			getchar();
//			return;
//		}
//		strcpy(content, temp);
//		strcpy(content+strlen(temp), s.content);
//		delete[]temp;
//	}
//	else {
//		len += s.len;
//		content = new char[len + 1];
//		if (!content) {
//			cout << "OVERFLOW" << endl;
//			getchar();
//			return;
//		}
//		strcpy(content, s.content);
//	}
//}
//void TString::append(const char ch)
//{
//	*this += ch;
//}
const TString operator - (const TString& s1, const TString& s2)
{
	int n = (int)(strstr(s1.content, s2.content) - s1.content);
	if (n < 0)
		return s1;
	TString s = s1;
	if (!s2.len)
		return s;
	s.len -= s2.len;
	if (!s.len)
		s.content = NULL;
	else {
		char* temp = new char[s.len + 1] {0};
		if (!temp) {
			cout << "OVERFLOW" << endl;
			getchar();
			return s;
		}
		int j = -1;
		for (int i = 0; i < s.len; i++) {
			j++;
			if (j >= n && j < n + s2.len) {
				i--;
				continue;
			}
			temp[i] = s.content[j];
		}
		s.content = temp;
	}
	return s;
}
const TString operator-(const TString& s, const char ch)
{
	TString temp;
	temp.len = 1;
	temp.content = new char[2] {0};
	if (!temp.content) {
		cout << "OVERFLOW" << endl;
		getchar();
		return s;
	}
	temp.content[0] = ch;
	return s-temp;
}
TString& TString:: operator-=(const TString& s)
{
	*this = *this - s;
	return *this;
}
TString& TString:: operator-=(const char ch)
{
	return *this = *this - ch;
}
const TString TString:: operator*(const int n)
{
	TString result;
	for (int i = 0; i < n; i++)
		result += *this;
	return result;
}
TString& TString::operator*=(const int n)
{
	*this = *this * n;
	return *this;
}
const TString operator!(const TString& s)
{
	if (!s.len)
		return s;
	TString result = s;
	for (int i = 0; i < s.len; i++)
		result.content[i] = s.content[result.len - 1 - i];
	return result;
}
int operator > (const TString& s1, const TString& s2) {
	if (!s1.len || !s2.len)
		return s1.len > s2.len;
	return  strcmp(s1.content, s2.content) >0;
}
int operator >= (const TString& s1, const TString& s2) {
	if (!s1.len || !s2.len)
		return s1.len >= s2.len;
	return  strcmp(s1.content, s2.content) >= 0;
}
int operator <= (const TString& s1, const TString& s2) {
	if (!s1.len || !s2.len)
		return s1.len <= s2.len;
	return  strcmp(s1.content, s2.content) <= 0;
}
int operator < (const TString& s1, const TString& s2) {
	if (!s1.len || !s2.len)
		return s1.len < s2.len;
	return  strcmp(s1.content, s2.content) < 0;
}
int operator== (const TString& s1, const TString& s2) {
	if (!s1.len || !s2.len)
		return s1.len == s2.len;
	return  strcmp(s1.content, s2.content) == 0;
}
int operator != (const TString& s1, const TString& s2) {
	if (!s1.len || !s2.len)
		return s1.len != s2.len;
	return  strcmp(s1.content, s2.content) != 0;
}
int TString::length()const
{
	return len;
}
char& TString::operator[](int n)
{
	return content[n];
}
int TStringLen(const TString& s)
{
	return s.length();
}
/* 如果有需要的其它全局函数的实现，可以写于此处 */

