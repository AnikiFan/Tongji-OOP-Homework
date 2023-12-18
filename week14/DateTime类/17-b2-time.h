/* 2254298 ������ ���� */
#pragma once

#include <iostream>
using namespace std;

/* ���������ȫ�ֺ�����Ҫ������д�ڴ˴� */
#define DEFHOUR 0
#define DEFMIN 0
#define DEFSEC 0
#define SEC_PER_MIN 60
#define MIN_PER_HOUR 60
#define SEC_PER_HOUR (SEC_PER_MIN*MIN_PER_HOUR)
#define HOUR_PER_DAY 24
#define SEC_PER_DAY (HOUR_PER_DAY*SEC_PER_HOUR)

/* Time������� */ 
class Time {
protected:
	/* �����������⣬�������ٶ����κ����ݳ�Ա */ 
	int hour;
	int minute;
	int second;
public:
	/* ������Ҫ�ĳ�Ա��������Ԫ���������� */
	Time();//�޲ι���
	Time(int h, int m, int s);//���ι���
	//Ҫ��3
	void set(int h, int m = 0, int s = 0);
	//Ҫ��4
	void get(int& h, int& m, int& s);
	//Ҫ��5
	void show();
	//Ҫ��6
	Time(int offset);//ת�����캯��
	operator int()const;//����ת������
	//Ҫ��7
	friend Time operator+ (const Time& now, const int delta);
	friend Time operator+ (const int delta, const Time& now);
	friend Time operator- (const Time& now, const int delta);
	friend int operator- (const Time& t1, const Time& t2);
	//Ҫ��8
	friend Time& operator ++ (Time& now);
	friend Time& operator -- (Time& now);
	friend Time operator ++ (Time& now, int);
	friend Time operator -- (Time& now, int);
	//Ҫ��9
	friend ostream& operator << (ostream& out, const Time& now);
	friend istream& operator >> (istream& in, Time& now);
	//Ҫ��10
	friend bool operator > (const Time& t1, const Time& t2);
	friend bool operator >= (const Time& t1, const Time& t2);
	friend bool operator < (const Time& t1, const Time& t2);
	friend bool operator <= (const Time& t1, const Time& t2);
	friend bool operator == (const Time& t1, const Time& t2);
	friend bool operator != (const Time& t1, const Time& t2);
	/* ���������Ԫ����������б�Ҫ�� */

};
