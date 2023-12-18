/* 2254298 大数据 范潇 */
#pragma once

#include "17-b2-date.h"
#include "17-b2-time.h"

/* 如果有其它全局函数需要声明，写于此处 */
/* 可以在此定义其它需要的函数 */
#define secondPerMinute 60
#define minutePerHour 60
#define secondPerHour (secondPerMinute*minutePerHour)
#define hourPerDay 24
#define secondPerDay (secondPerHour*hourPerDay)
#define dayPerLeapYear 366
#define secondPerLeapYear (dayPerLeapYear*secondPerDay)
#define dayPerNonLeapYear 365
#define secondPerNonLeapYear (dayPerNonLeapYear*secondPerDay)
#define srcHour 0
#define srcMinute 0
#define srcSecond 0
#define maxday {31,28,31,30,31,30,31,31,30,31,30,31}
#define febMaxDayInLeapYear 29
#define febMaxDayInNonLeapYear 28
#define timeZone 8
/* DateTime类的基本要求：
	1、不允许定义任何数据成员
	2、尽量少定义成员函数 
*/

class DateTime:public Date, public Time {
protected:
	/* 除这三个以外，不允许再定义任何数据成员 */ 

public:
	/* 允许需要的成员函数及友元函数的声明 */
	DateTime();
	void set(int y=DEFYEAR, int m=DEFMON,int d=DEFDAY, int h=srcHour, int min=srcMinute, int s=srcSecond);
	/* 允许加入友元声明（如果有必要） */
	DateTime(int y, int m,int d, int h, int min, int s);
	void get (int &y, int &m,int &d, int &h, int &min, int &s);
	operator long long()const ;
	DateTime(const long long);
	void show();
	friend DateTime operator+ (const DateTime& now, const int delta);
	friend DateTime operator+ (const int delta, const DateTime& now);
	friend DateTime operator- (const DateTime& now, const int delta);
	friend DateTime operator+ (const DateTime& now, const long int delta);
	friend DateTime operator+ (const long int delta, const DateTime& now);
	friend DateTime operator- (const DateTime& now, const long int delta);
	friend DateTime operator+ (const DateTime& now, const long long delta);
	friend DateTime operator+ (const long  long delta, const DateTime& now);
	friend DateTime operator- (const DateTime& now, const long long delta);
	
	friend long long operator- (const DateTime& d1, const DateTime& d2);
	//要求8
	friend DateTime& operator ++ (DateTime& now);
	friend DateTime& operator -- (DateTime& now);
	friend DateTime operator ++ (DateTime& now, int);
	friend DateTime operator -- (DateTime& now, int);
	//要求9
	friend ostream& operator << (ostream& out, const DateTime& now);
	friend istream& operator >> (istream& in, DateTime& now);
	//要求10
	friend bool operator > (const DateTime& d1, const DateTime& d2);
	friend bool operator >= (const DateTime& d1, const DateTime& d2);
	friend bool operator < (const DateTime& d1, const DateTime& d2);
	friend bool operator <= (const DateTime& d1, const DateTime& d2);
	friend bool operator == (const DateTime& d1, const DateTime& d2);
	friend bool operator != (const DateTime& d1, const DateTime& d2);
};
