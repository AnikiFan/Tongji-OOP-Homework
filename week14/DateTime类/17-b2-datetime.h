/* 2254298 ������ ���� */
#pragma once

#include "17-b2-date.h"
#include "17-b2-time.h"

/* ���������ȫ�ֺ�����Ҫ������д�ڴ˴� */
/* �����ڴ˶���������Ҫ�ĺ��� */
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
/* DateTime��Ļ���Ҫ��
	1�����������κ����ݳ�Ա
	2�������ٶ����Ա���� 
*/

class DateTime:public Date, public Time {
protected:
	/* �����������⣬�������ٶ����κ����ݳ�Ա */ 

public:
	/* ������Ҫ�ĳ�Ա��������Ԫ���������� */
	DateTime();
	void set(int y=DEFYEAR, int m=DEFMON,int d=DEFDAY, int h=srcHour, int min=srcMinute, int s=srcSecond);
	/* ���������Ԫ����������б�Ҫ�� */
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
	//Ҫ��8
	friend DateTime& operator ++ (DateTime& now);
	friend DateTime& operator -- (DateTime& now);
	friend DateTime operator ++ (DateTime& now, int);
	friend DateTime operator -- (DateTime& now, int);
	//Ҫ��9
	friend ostream& operator << (ostream& out, const DateTime& now);
	friend istream& operator >> (istream& in, DateTime& now);
	//Ҫ��10
	friend bool operator > (const DateTime& d1, const DateTime& d2);
	friend bool operator >= (const DateTime& d1, const DateTime& d2);
	friend bool operator < (const DateTime& d1, const DateTime& d2);
	friend bool operator <= (const DateTime& d1, const DateTime& d2);
	friend bool operator == (const DateTime& d1, const DateTime& d2);
	friend bool operator != (const DateTime& d1, const DateTime& d2);
};
