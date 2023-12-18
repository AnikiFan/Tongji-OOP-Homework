/* 2254298 ������ ���� */
#include <iostream>
#include <iomanip>
#include "17-b2-datetime.h"
using namespace std;

/* --- ����DateTime��ĳ�Ա����������ʵ��(����Ԫ��������Ҫ�Ĺ�������)  ---

	������Ҫ��ʾ��
	1��6�ι��캯���ܷ�պ����壬ֱ�Ӽ���Date��Time�Ĺ��캯����
	2��1�ι��캯�����ܷ���ѭ����ֱ�ӽ���Date��Time��һ�ι���������ʵ�֣� 
	3��DateTimeתlong long������ת���������ܷ���ѭ����������ֵ���ݹ������ʵ�֣�(��̿�������ֻ��һ��return)�� 
	4��DateTime��n�Ĳ�������Ҫ���弸�����͵���������أ� 
*/ 
/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
DateTime::DateTime()
{
	((Date)(*this))=Date();
	((Time)(*this))=Time();
}
DateTime::DateTime(int y, int m, int d, int h, int min, int s)
{
	if ( m>=1&&m<=12&&y>=1900&&y<=2099&&h >= 0 && h <= 23 && min >= 0 && min <= 59 && s >= 0 && s <= 59&&invaliddaytest(y, m, d) ) {
		year = y;
		month = m;
		day = d;
		hour = h;
		minute = min;
		second = s;
	}
	else {
		(*this).Date::set(-1, m, d);
		(*this).Time::set(-1, min, s);
	}
}
void DateTime::set(int y, int m, int d, int h, int min, int s)
{
	(*this).Date::set(y, m, d);
	(*this).Time::set(h,min,s);
}
void DateTime::get(int &y, int &m, int &d, int &h, int &min, int &s)
{
	(*this).Date::get(y, m, d);
	(*this).Time::get(h,min,s);
}
DateTime::operator long long ()const
{
	return (*this).Time::operator int() + (long long)(*this).Date::operator int() * secondPerDay;
}
DateTime::DateTime(const long long offset):Date((offset<0?(int)(offset / secondPerDay)-1:(int)(offset / secondPerDay))),Time((int)(offset % secondPerDay))
{
}
void DateTime::show()
{
	cout << setw(4) << setfill('0') << year << "-" << setw(2) << setfill('0') << month << "-" << setw(2) << setfill('0') << day << " ";
	cout << setw(2) << setfill('0') << hour << ":" << setw(2) << setfill('0') << minute <<":" << setw(2) << setfill('0') << second << endl;
}
DateTime operator+ (const DateTime& now, const long long  delta)
{
	DateTime temp = now;
	temp=((((long long)temp.Date::operator int()*secondPerDay)+delta+(long long)temp.Time::operator int()));
	return temp;
}
DateTime operator+ (const long long delta, const DateTime& now)
{
	DateTime temp = now;
	temp=((((long long)temp.Date::operator int()*secondPerDay)+delta+(long long)temp.Time::operator int()));
	return temp;
}
DateTime operator- (const DateTime& now, const long long delta)
{
	DateTime temp = now;
	temp=((((long long)temp.Date::operator int()*secondPerDay)-delta+(long long)temp.Time::operator int()) );
	return temp;
}
DateTime operator+ (const DateTime& now, const int  delta)
{
	DateTime temp = now;
	temp=((((long long)temp.Date::operator int()*secondPerDay)+delta+(long long)temp.Time::operator int()));
	return temp;
}
DateTime operator+ (const int delta, const DateTime& now)
{
	DateTime temp = now;
	temp=((((long long)temp.Date::operator int()*secondPerDay)+delta+(long long)temp.Time::operator int()) );
	return temp;
}
DateTime operator- (const DateTime& now, const int delta)
{
	DateTime temp = now;
	temp=((((long long)temp.Date::operator int()*secondPerDay)-delta+(long long)temp.Time::operator int()));
	return temp;
}
DateTime operator+ (const DateTime& now, const long int  delta)
{
	DateTime temp = now;
	temp = ((((long long)temp.Date::operator int() * secondPerDay) + delta + (long long)temp.Time::operator int()));
	return temp;
}
DateTime operator+ (const long int delta, const DateTime& now)
{
	DateTime temp = now;
	temp = ((((long long)temp.Date::operator int() * secondPerDay) + delta + (long long)temp.Time::operator int()));
	return temp;
}
DateTime operator- (const DateTime& now, const long int delta)
{
	DateTime temp = now;
	temp = ((((long long)temp.Date::operator int() * secondPerDay) - delta + (long long)temp.Time::operator int()));
	return temp;
}
long long operator- (const DateTime& d1, const DateTime& d2)
{
	return ((long long)(d1.Date::operator int())) * secondPerDay - ((long long)(d2.Date:: operator int())) * secondPerDay + d1.Time::operator int()-d2.Time::operator int();
}
//Ҫ��8
DateTime& operator ++ (DateTime& now)
{
	now = now + 1;
	return now;
}
DateTime& operator -- (DateTime& now)
{
	now = now - 1;
	return now;
}
DateTime operator ++ (DateTime& now, int)
{
	DateTime temp = now;
	now = now + 1;
	return temp;
}
DateTime operator -- (DateTime& now, int)
{
	DateTime temp = now;
	now = now - 1;
	return temp;
}
//Ҫ��9
ostream& operator << (ostream& out, const DateTime& now)
{
	out << setw(4) << setfill('0') << now.year << "-" << setw(2) << setfill('0') << now.month << "-" << setw(2) << setfill('0') << now.day  << " ";
	out << setw(2) << setfill('0') << now.hour << ":" << setw(2) << setfill('0') << now.minute <<":" << setw(2) << setfill('0') << now.second << endl;
	return out;
}
istream& operator >> (istream& in, DateTime& now)
{
	int y,m,d,h,min,s;
	in >> y >> m >> d >> h >> min >> s;
	if (m >= 1 && m <= 12 && y >= 1900 && y <= 2099 && h >= 0 && h <= 23 && min >= 0 && min <= 59 && s >= 0 && s <= 59 && invaliddaytest(y, m, d)) {
		now.year = y;
		now.month = m;
		now.day = d;
		now.hour = h;
		now.minute = min;
		now.second = s;
	}
	else {
		now.Date::set(-1, m, d);
		now.Time::set(-1, min, s);
	}
	return in;
}
//Ҫ��10
bool operator > (const DateTime& d1, const DateTime& d2)
{
	return d1.operator long long() > d2.operator long long();
}
bool operator >= (const DateTime& d1, const DateTime& d2)
{
	return d1.operator long long() >= d2.operator long long();
}
bool operator < (const DateTime& d1, const DateTime& d2)
{
	return d1.operator long long() < d2.operator long long();
}
bool operator <= (const DateTime& d1, const DateTime& d2)
{
	return d1.operator long long() <= d2.operator long long();
}
bool operator == (const DateTime& d1, const DateTime& d2)
{
	return d1.operator long long() == d2.operator long long();
}
bool operator != (const DateTime& d1, const DateTime& d2)
{
	return d1.operator long long() != d2.operator long long();
}
