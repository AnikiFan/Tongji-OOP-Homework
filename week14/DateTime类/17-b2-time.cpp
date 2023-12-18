/* 2254298 大数据 范潇 */
#include <iostream>
#include <iomanip>
#include "17-b2-time.h"
using namespace std;

/* --- 给出Time类的成员函数的体外实现(含友元及其它必要的公共函数)  --- */

Time::Time()
{
	hour = DEFHOUR;
	minute = DEFMIN;
	second = DEFSEC;
}
Time::Time(int h, int m, int s)
{
	if (h < 0 || h>23 || m < 0 || m>59 || s < 0 || s>59)
		hour = minute = second = 0;
	else {
		 hour=h;
		 minute=m;
		 second=s;
	}
}
void Time::set(int h, int m, int s)
{
	if (h < 0 || h>23 || m < 0 || m>59 || s < 0 || s>59)
		hour = minute = second = 0;
	else {
		hour = h;
		minute = m;
		second = s;
	}
}
void Time::get(int& h, int& m, int& s)
{
	h = hour;
	m = minute;
	s = second;
}
void Time::show()
{
	cout << setw(2) << setfill('0') << hour << ":" << setw(2) << setfill('0') << minute << ":" << setw(2) << setfill('0') << second << endl;
}
Time::Time(int offset)
{
	while (offset >= SEC_PER_DAY)
		offset -= SEC_PER_DAY;
	while (offset < 0)
		offset += SEC_PER_DAY;
	second = offset % SEC_PER_MIN;
	offset -= second;
	offset /= SEC_PER_MIN;
	minute = offset % MIN_PER_HOUR;
	offset /= MIN_PER_HOUR;
	hour = offset;
}
Time::operator int()const
{
	return second + minute * SEC_PER_MIN + hour * SEC_PER_HOUR;
}
Time operator+ (const Time& now, const int delta)
{
	return (now.operator int() + delta) % SEC_PER_DAY;
}
Time operator+ (const int delta, const Time& now)
{
	return (now.operator int() + delta) % SEC_PER_DAY;
}
Time operator- (const Time& now, const int delta)
{
	return (now.operator int() - delta) % SEC_PER_DAY;
}
int operator- (const Time& t1, const Time& t2)
{
	return (t1.operator int() - t2.operator int()) % SEC_PER_DAY;
}
//要求8
Time& operator ++ (Time& now)
{
	now = now + 1;
	return now;

}
Time& operator -- (Time& now)
{
	now = now - 1;
	return now;
}
Time operator ++ (Time& now, int)
{
	Time temp = now;
	now = now + 1;
	return temp;
}
Time operator -- (Time& now, int)
{
	Time temp = now;
	now = now - 1;
	return temp;
}
//要求9
ostream& operator << (ostream& out, const Time& now)
{
	out << setw(2) << setfill('0') << now.hour << ":" << setw(2) << setfill('0') << now.minute << ":" << setw(2) << setfill('0') << now.second << endl;
	return out;
}
istream& operator >> (istream& in, Time& now)
{
	int h, m, s;
	in >> h >> m >> s;
	now.set(h, m, s);
	return in;
}
//要求10
bool operator > (const Time& d1, const Time& d2)
{
	return d1.operator int() > d2.operator int();
}
bool operator >= (const Time& d1, const Time& d2)
{
	return d1.operator int() >= d2.operator int();
}
bool operator < (const Time& d1, const Time& d2)
{
	return d1.operator int() < d2.operator int();
}
bool operator <= (const Time& d1, const Time& d2)
{
	return d1.operator int() <= d2.operator int();
}
bool operator == (const Time& d1, const Time& d2)
{
	return d1.operator int() == d2.operator int();
}
bool operator != (const Time& d1, const Time& d2)
{
	return d1.operator int() != d2.operator int();
}
