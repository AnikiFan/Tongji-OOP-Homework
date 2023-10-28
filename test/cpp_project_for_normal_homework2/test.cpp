#include<iostream>
using namespace std;
class Time {
private:
	int hour;
	int minute;
	int second;
public:
	Time(int h = 0, int m = 0, int s = 0);
	Time(const Time& t);
	~Time();
	void display()
	{
		cout << hour << ":" << minute << ":" << second << endl;
	};
};
Time :: Time(int h, int m, int s)
{
	hour = h;
	minute = m;
	second = s;
	cout << "普通构造" <<hour<< endl;
}
Time ::~Time()
{
	cout << "析构" <<hour<< endl;
}
Time :: Time(const Time& t)
{
	hour = t.hour-1;
	minute = t.minute-1;
	second = t.second-1;
	cout << "复制构造" << endl;
}

Time fun()
{
	 Time t1(14, 15, 23);
	return t1;
}
int main()
{
	Time t2 = fun();
	t2.display();
	return 0;
}
