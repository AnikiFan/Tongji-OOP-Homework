/* 2254298 大数据 范潇 */

#pragma once

#include <iostream>
using namespace std;

/* 如果有其它全局函数需要声明，写于此处 */
int invaliddaytest(int y, int m, int d);
/* 如果有需要的宏定义、只读全局变量等，写于此处 */
#define DEFYEAR 2000
#define DEFMON 1
#define DEFDAY 1

#define secondPerMinute 60
#define minutePerHour 60
#define secondPerHour (secondPerMinute*minutePerHour)
#define hourPerDay 24
#define secondPerDay (secondPerHour*hourPerDay)
#define dayPerLeapYear 366
#define secondPerLeapYear (dayPerLeapYear*secondPerDay)
#define dayPerNonLeapYear 365
#define secondPerNonLeapYear (dayPerNonLeapYear*secondPerDay)
#define srcYear 1900
#define srcMonth 1
#define srcDay 1
#define maxday {31,28,31,30,31,30,31,31,30,31,30,31}
#define febMaxDayInLeapYear 29
#define febMaxDayInNonLeapYear 28
#define timeZone 8
/* 补全Date类的定义，所有成员函数均体外实现，不要在此处体内实现 */
class Date {
private:
	int year;
	int month;
	int day;
	/* 不允许添加数据成员 */
public:
	/* 根据需要定义所需的成员函数、友元函数等(不允许添加数据成员) */
	//构造函数以及自增自减有错误处理要求
	//要求2
	Date();//无参构造
	Date(int y, int m, int d);//三参构造
	//要求3
	void set(int y, int m=1, int d=1);
	//要求4
	void get(int& y, int& m, int& d);
	//要求5
	void show();
	//要求6
	Date(int offset);//转换构造函数
	operator int()const;//类型转换函数
	//要求7
	friend Date operator+ (const Date& now, const int delta);
	friend Date operator+ (const int delta,const Date& now );
	friend Date operator- (const Date& now, const int delta);
	friend int operator- (const Date&d1,const Date& d2 );
	//要求8
	friend Date& operator ++ (Date& now);
	friend Date& operator -- (Date& now);
	friend Date operator ++ (Date& now,int);
	friend Date operator -- (Date& now,int);
	//要求9
	friend ostream& operator << (ostream& out, const Date& now);
	friend istream& operator >> (istream& in,  Date& now);
	//要求10
	friend bool operator > (const Date& d1, const Date& d2);
	friend bool operator >= (const Date& d1, const Date& d2);
	friend bool operator < (const Date& d1, const Date& d2);
	friend bool operator <= (const Date& d1, const Date& d2);
	friend bool operator == (const Date& d1, const Date& d2);
	friend bool operator != (const Date& d1, const Date& d2);
};

