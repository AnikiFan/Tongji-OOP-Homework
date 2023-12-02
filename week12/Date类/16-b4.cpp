/* 2254298 大数据 范潇 */
#include "16-b4.h"
using namespace std;

/* 给出 Date 类的所有成员函数的体外实现 */
Date::Date()
{
	year = DEFYEAR;
	month = DEFMON;
	day = DEFDAY;
}
Date::Date(int y, int m, int d)
{
	year = (1900<=y&&2099>=y?y:2000);
	month = (1<=m&&12>=m?m:1);
	day = (invaliddaytest(year,month,d)?d:1);
}
void Date::set(int y, int m, int d)
{
	if (!y)
		y = year;
	if (!m)
		m = month;
	if (!d)
		d = day;
	year = (1900<=y&&2099>=y?y:2000);
	month = (1<=m&&12>=m?m:1);
	day = (invaliddaytest(year,month,d)?d:1);
	return;
}
void Date::get(int& y, int& m, int& d)
{
	y = year;
	m = month;
	d = day;
	return;
}
void Date::show()
{
	cout << year << "年" << month << "月" << day << "日" << endl;
	return;
}
Date::Date(int offset)
{
	if (offset <= 1) {
		year = 1900;
		month = 1;
		day = 1;
		return;
	}
	if (offset >= 73049) {
		year = 2099;
		month = 12;
		day = 31;
		return;
	}
	offset--;
	int  maxDay[12] = maxday;
	day = srcDay;
	month = srcMonth;
	year = srcYear;
	while (1) {
		if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0) {//是闰年
			maxDay[1] = febMaxDayInLeapYear;
			if (offset >= dayPerLeapYear) {
				year++;
				offset -= dayPerLeapYear;
			}
			else {
				while (1) {
					if (offset >= maxDay[month - 1]) {
						offset -= maxDay[month - 1];
						month++;
					}
					else {
						day += offset;
						break;
					}
				}
				break;
			}
		}
		else {
			maxDay[1] = febMaxDayInNonLeapYear;
			if (offset >= dayPerNonLeapYear) {
				year++;
				offset -= dayPerNonLeapYear;
			}
			else {
				while (1) {
					if (offset >= maxDay[month - 1]) {
						offset -= maxDay[month - 1];
						month++;
					}
					else {
						day += offset;
						break;
					}
				}
				break;
			}
		}
	}
	return;
}
Date::operator int()const
{
	int result = day;
	int  maxDay[12] = maxday;
	if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0) 
		maxDay[1] = febMaxDayInLeapYear;
	for (int i = 0; i < month - 1; i++)
		result += maxDay[i];
	for (int i = srcYear; i < year; i++)
		result += (i % 4 == 0 && i % 100 != 0 || i % 400 == 0 ? 366 : 365);
	return result;
}
/* 如果有需要的其它全局函数的实现，可以写于此处 */
int invaliddaytest(int y, int m, int d)
{
	int max;
	switch (m) {
		case 1:
			max = 31;
			break;
		case 3:
			max = 31;
			break;
		case 5:
			max = 31;
			break;
		case 7:
			max = 31;
			break;
		case 8:
			max = 31;
			break;
		case 10:
			max = 31;
			break;
		case 12:
			max = 31;
			break;
		case 4:
			max = 30;
			break;
		case 6:
			max = 30;
			break;
		case 9:
			max = 30;
			break;
		case 11:
			max = 30;
			break;
		case 2:
			if (y % 4 == 0 && y % 100 != 0 || y % 400 == 0)
				max = 29;
			else
				max = 28;
			break;
	}
	return(1 <= d && d <= max);
}
Date operator+ (const Date& now, const int delta)
{
	Date temp = now.operator int() + delta;
	return temp;
}
Date operator+ (const int delta, const Date& now)
{
	Date temp = now.operator int() + delta;
	return temp;
}
Date operator- (const Date& now, const int delta)
{
	Date temp = now.operator int() - delta;
	return temp;

}
int operator- (const Date&d1, const Date& d2)
{
	return d1.operator int() - d2.operator int();
}
//要求8
Date& operator ++ (Date& now)
{
	now = now.operator int() + 1;
	return now;
}
Date& operator -- (Date& now)
{
	now = now.operator int() - 1;
	return now;
}
Date operator ++ (Date& now, int) 
{
	Date temp = now;
	now = now.operator int() + 1;
	return temp;
}
Date operator -- (Date& now, int)
{
	Date temp = now;
	now = now.operator int() - 1;
	return temp;
}
//要求9
ostream& operator << (ostream& out, const Date& now)
{
	out << now.year << "年"<<now.month << "月" << now.day <<"日" << endl;
	return out;
}
istream& operator >> (istream& in, Date& now)
{
	int y, m, d;
	cin >> y >> m >> d;
	now.set(y, m, d);
	return in;
}
//要求10
bool operator > (const Date& d1, const Date& d2)
{
	return d1.operator int() > d2.operator int();
}
bool operator >= (const Date& d1, const Date& d2)
{
	return d1.operator int() >= d2.operator int();
}
bool operator < (const Date& d1, const Date& d2)
{
	return d1.operator int() < d2.operator int();
}
bool operator <= (const Date& d1, const Date& d2)
{
	return d1.operator int() <= d2.operator int();
}
bool operator == (const Date& d1, const Date& d2)
{
	return d1.operator int() == d2.operator int();
}
bool operator != (const Date& d1, const Date& d2)
{
	return d1.operator int()!= d2.operator int();
}
