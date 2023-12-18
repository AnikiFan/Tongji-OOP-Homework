/* 2254298 大数据 范潇 */
#pragma once

#include <iostream>
using namespace std;

/* 如果有其它全局函数需要声明，写于此处 */
#define DEFHOUR 0
#define DEFMIN 0
#define DEFSEC 0
#define SEC_PER_MIN 60
#define MIN_PER_HOUR 60
#define SEC_PER_HOUR (SEC_PER_MIN*MIN_PER_HOUR)
#define HOUR_PER_DAY 24
#define SEC_PER_DAY (HOUR_PER_DAY*SEC_PER_HOUR)

/* Time类的声明 */ 
class Time {
protected:
	/* 除这三个以外，不允许再定义任何数据成员 */ 
	int hour;
	int minute;
	int second;
public:
	/* 允许需要的成员函数及友元函数的声明 */
	Time();//无参构造
	Time(int h, int m, int s);//三参构造
	//要求3
	void set(int h, int m = 0, int s = 0);
	//要求4
	void get(int& h, int& m, int& s);
	//要求5
	void show();
	//要求6
	Time(int offset);//转换构造函数
	operator int()const;//类型转换函数
	//要求7
	friend Time operator+ (const Time& now, const int delta);
	friend Time operator+ (const int delta, const Time& now);
	friend Time operator- (const Time& now, const int delta);
	friend int operator- (const Time& t1, const Time& t2);
	//要求8
	friend Time& operator ++ (Time& now);
	friend Time& operator -- (Time& now);
	friend Time operator ++ (Time& now, int);
	friend Time operator -- (Time& now, int);
	//要求9
	friend ostream& operator << (ostream& out, const Time& now);
	friend istream& operator >> (istream& in, Time& now);
	//要求10
	friend bool operator > (const Time& t1, const Time& t2);
	friend bool operator >= (const Time& t1, const Time& t2);
	friend bool operator < (const Time& t1, const Time& t2);
	friend bool operator <= (const Time& t1, const Time& t2);
	friend bool operator == (const Time& t1, const Time& t2);
	friend bool operator != (const Time& t1, const Time& t2);
	/* 允许加入友元声明（如果有必要） */

};
