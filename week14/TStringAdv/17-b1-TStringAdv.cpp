/* 2254298 ´óÊý¾Ý ·¶äì */
#define _CRT_SECURE_NO_WARNINGS
#include"17-b1-TStringAdv.h"
#include<cstring>
TStringAdv::TStringAdv()
{
}
TStringAdv::TStringAdv(const char* const s) :TString(s)
{
}
TStringAdv::TStringAdv(const TStringAdv& old) :TString(old)
{
}
TStringAdv::TStringAdv(const TString&old):TString(old)
{
}
int TStringAdvLen(const TStringAdv& ts)
{
	return ts.len;
}
int TStringAdvLen(const TString& ts)
{
	return ts.length();
}
TStringAdv& TStringAdv::assign(const TStringAdv& ts2)
{
	len = ts2.length();
	if (len) {
		if (content)
			delete[]content;
		content = new (nothrow) char[len + 1];
		if (!content) {
			cout << "OVERFLOW" << endl;
			getchar();
			return *this;
		}
		memcpy(content, ts2.c_str(), len + 1);
	}
	else {
		content = nullptr;
		len = 0;
	}
	return *this;
}
TStringAdv& TStringAdv::assign(const char* s)
{
	if (!s) {
		content = nullptr;
		len = 0;
	}
	else {
		len = strlen(s);
		if (content)
			delete[]content;
		content = new (nothrow)char[len + 1];
		if (!content) {
			cout << "OVERFLOW" << endl;
			getchar();
			return *this;
		}
		memcpy(content, s, len + 1);
	}
	return *this;
}
TStringAdv& TStringAdv::append(const TStringAdv& ts2)
{
	if (!ts2.content)
		return *this;
	const char* temp = content;
	content = new char[len + ts2.len + 1];
	if (!content) {
		cout << "OVERFLOW" << endl;
		getchar();
		return *this;
	}

	memcpy(content, temp, len);
	memcpy(content + len, ts2.content, ts2.len + 1);
	len += ts2.len;
	delete[]temp;
	return *this;
}
TStringAdv& TStringAdv::append(const char* s)
{
	if (!s)
		return *this;
	const char* temp = content;
	content = new char[len + strlen(s) + 1];
	if (!content) {
		cout << "OVERFLOW" << endl;
		getchar();
		return *this;
	}

	memcpy(content, temp, len);
	memcpy(content + len, s, strlen(s) + 1);
	len += strlen(s);
	delete[]temp;
	return *this;
}
TStringAdv& TStringAdv::append(const char& c)
{
	const char* temp = content;
	content = new char[len + 1 + 1];
	if (!content) {
		cout << "OVERFLOW" << endl;
		getchar();
		return *this;
	}

	memcpy(content, temp, len);
	content[len] = c;
	content[len + 1] = 0;
	len++;
	delete[]temp;
	return *this;
}
TStringAdv& TStringAdv::insert(const TStringAdv& ts2, int pos)
{
	if (pos <= 0 || pos > len + 1)
		return *this;
	if (pos == len + 1) {
		append(ts2);
		return *this;
	}
	pos--;
	const char* temp = content;
	content = new char[len + ts2.len + 1];
	if (!content) {
		cout << "OVERFLOW" << endl;
		getchar();
		return *this;
	}
	memcpy(content, temp, pos);
	memcpy(content + pos, ts2.content, ts2.len);
	memcpy(content + pos + ts2.len, temp + pos, len - pos + 1);
	delete[]temp;
	return *this;
}
TStringAdv& TStringAdv::insert(const char* s, int pos)
{
	if (pos <= 0 || pos > len + 1)
		return *this;
	if (pos == len + 1) {
		append(s);
		return *this;
	}
	pos--;
	const char* temp = content;
	content = new char[len + strlen(s) + 1];
	if (!content) {
		cout << "OVERFLOW" << endl;
		getchar();
		return *this;
	}
	memcpy(content, temp, pos);
	memcpy(content + pos, s, strlen(s));
	memcpy(content + pos + strlen(s), temp + pos, len - pos + 1);
	delete[]temp;
	return *this;
}
TStringAdv& TStringAdv::insert(const char& c, int pos)
{
	if (pos <= 0 || pos > len + 1)
		return *this;
	if (pos== len + 1) {
		append(c);
		return *this;
	}
	pos--;
	const char* temp = content;
	content = new char[len + 1 + 1] { 0 };
	if (!content) {
		cout << "OVERFLOW" << endl;
		getchar();
		return *this;
	}
	memcpy(content, temp, pos);
	*(content + pos) = c;
	memcpy(content + pos + 1, temp + pos, len - pos + 1);
	len++;
	delete[]temp;
	return *this;
}
TStringAdv& TStringAdv::erase(const TStringAdv& ts2)
{
	if (!ts2.content||!content)
		return *this;
	int n = (strstr(content, ts2.content) - content);
	if (n < 0)
		return *this;
	len -= ts2.len;
	if (!len)
		content = nullptr;
	else {
		const char* temp= content;
		content = new char[len + 1] ;
		if (!content) {
			cout << "OVERFLOW" << endl;
			getchar();
			return *this;
		}
		memcpy(content,temp,n);
		memcpy(content + n, temp + n + ts2.len, len - n + 1);
		delete[]temp;
	}
	return *this;
}
TStringAdv& TStringAdv::erase(const char* s)
{
	TStringAdv temp =s;
	this->erase( temp);
	return *this;
}
TStringAdv& TStringAdv::erase(const char& c)
{
	TStringAdv temp ;
	temp.len = 1;
	temp.content = new (nothrow)char[2];
	temp.content[0] = c;
	temp.content[1] = 0;
	this->erase(temp);
	return *this;
}
TStringAdv TStringAdv::substr(const int pos, const int len)
{
	TStringAdv t;
	int Len=len;
	int Pos = pos - 1;
	if ((len < 0) && (len != FOO))
		return t;
	if (Pos<0 || Pos>this->len)
		return t;
	if (len == FOO||Pos + len > this->len)
		Len = this->len - Pos;
	char* temp = new (nothrow) char[Len + 1];
	if (!temp) {
		cout << "OVERFLOW" << endl;
		getchar();
		return t;
	}
	memcpy(temp, content + Pos, Len);
	temp[Len] = 0;
	TStringAdv temp_string(temp);
	return temp_string;
}
char& TStringAdv::at(const int n)
{
	if (!content || n<0 || n>len)
		return content[0];
	return content[n];
}
