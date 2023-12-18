/* 2254298 ������ ���� */
#pragma once

#include <iostream>
using namespace std;

/* ���������ȫ�ֺ�����Ҫ������д�ڴ˴� */
int invaliddaytest(int y, int m, int d);
#define DEFYEAR 1900
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
/* Date������� */ 
class Date {
protected:
	/* �����������⣬�������ٶ����κ����ݳ�Ա */ 
	int year;
	int month;
	int day;
public:
	/* ������Ҫ�ĳ�Ա��������Ԫ���������� */
	
	/* ���������Ԫ����������б�Ҫ�� */
	Date();//�޲ι���
	Date(int y, int m, int d);//���ι���
	//Ҫ��3
	void set(int y, int m = 1, int d = 1);
	//Ҫ��4
	void get(int& y, int& m, int& d);
	//Ҫ��5
	void show();
	//Ҫ��6
	Date(int offset);//ת�����캯��
	operator int()const;//����ת������
	//Ҫ��7
	friend Date operator+ (const Date& now, const int delta);
	friend Date operator+ (const int delta, const Date& now);
	friend Date operator- (const Date& now, const int delta);
	friend int operator- (const Date& d1, const Date& d2);
	//Ҫ��8
	friend Date& operator ++ (Date& now);
	friend Date& operator -- (Date& now);
	friend Date operator ++ (Date& now, int);
	friend Date operator -- (Date& now, int);
	//Ҫ��9
	friend ostream& operator << (ostream& out, const Date& now);
	friend istream& operator >> (istream& in, Date& now);
	//Ҫ��10
	friend bool operator > (const Date& d1, const Date& d2);
	friend bool operator >= (const Date& d1, const Date& d2);
	friend bool operator < (const Date& d1, const Date& d2);
	friend bool operator <= (const Date& d1, const Date& d2);
	friend bool operator == (const Date& d1, const Date& d2);
	friend bool operator != (const Date& d1, const Date& d2);
};
