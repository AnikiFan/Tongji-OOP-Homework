/* 2254298 大数据 范潇 */
#include <iostream>
#include <iomanip>
#include<climits>
#include "17-b2-datetime.h"
using namespace std;

#if defined(__linux) || defined(__linux__) //Linux
/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
static void wait_for_enter()
{
	cout << endl << "按回车键继续";
	while (getchar() != '\n')
		;
	cout << endl << endl;
}

#else //VS+Dev
#include <Windows.h>
#include <conio.h>
/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
static void wait_for_enter()
{
	cout << endl << "按回车键继续";
	while (_getch() != '\r')
		;
	cout << endl << endl;
}
#endif


/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
static int test_for_date()
{
	cout << setfill('=') << setw(20) << "=" << endl;
	cout << "     Date类测试" << endl;
	cout << setw(20) << "=" << endl;
	cout << setfill(' ');

	if (1) {
		cout << "测试初始化，完全正确的赋值" << endl;

		Date d1;
		Date d2(2023, 12, 1);
		Date d3(1900, 1, 1);
		Date d4(2099, 12, 31);
		cout << "d1应该是1900-01-01，实际为：";
		d1.show();
		cout << "d2应该是2023-12-01，实际为：";
		d2.show();
		cout << "d3应该是1900-01-01，实际为：";
		d3.show();
		cout << "d4应该是2099-12-31，实际为：";
		d4.show();

		wait_for_enter();
	}

	if (1) {
		cout << "测试初始化，年、月、日非法" << endl;

		/* 单个错，都是1900.1.1 */
		Date d1(1870, 3, 15);
		Date d2(2112, 3, 4);
		Date d3(2005, 13, 15);
		Date d4(2023, 11, 31);
		cout << "d1应该是1900-01-01，实际为：";
		d1.show();
		cout << "d2应该是1900-01-01，实际为：";
		d2.show();
		cout << "d3应该是1900-01-01，实际为：";
		d3.show();
		cout << "d4应该是1900-01-01，实际为：";
		d4.show();

		/* 多个错，都是1900.1.1 */
		Date d5(1899, 2, 29);
		Date d6(1899, 2, 30);
		Date d7(1899, 13, 31);
		Date d8(1899, 13, 32);
		cout << "d5应该是1900-01-01，实际为：";
		d5.show();
		cout << "d6应该是1900-01-01，实际为：";
		d6.show();
		cout << "d7应该是1900-01-01，实际为：";
		d7.show();
		cout << "d8应该是1900-01-01，实际为：";
		d8.show();

		wait_for_enter();
	}

	if (1) {
		cout << "测试初始化，闰年" << endl;

		Date d1(2023, 2, 29); //1900.1.1
		Date d2(2020, 2, 29); //2020.2.29
		cout << "d1应该是1900-01-01，实际为：";
		d1.show();
		cout << "d2应该是2020-02-29，实际为：";
		d2.show();

		wait_for_enter();
	}

	if (1) {
		cout << "测试set，带缺省值" << endl;

		Date d1, d2, d3; //都是1900.1.1
		d1.set(2023, 12, 10);	//2023.12.10
		d2.set(2023, 12);		//2023.12.1
		d3.set(2023);		//2023.1.1
		cout << "d1应该是2023-12-10，实际为：";
		d1.show();
		cout << "d2应该是2023-12-01，实际为：";
		d2.show();
		cout << "d3应该是2023-01-01，实际为：";
		d3.show();

		wait_for_enter();
	}

	if (1) {
		cout << "测试set，含0，都是1900-01-01" << endl;

		Date d1(2023, 12, 1), d2(d1), d3(d1);
		d1.set(2007, 0, 0); //1900.1.1
		d2.set(0, 10, 18);  //1900.1.1
		d3.set(0, 0, 28);   //1900.1.1

		cout << "d1应该是1900-01-01，实际为：";
		d1.show();
		cout << "d2应该是1900-01-01，实际为：";
		d2.show();
		cout << "d3应该是1900-01-01，实际为：";
		d3.show();

		wait_for_enter();
	}

	if (1) {
		cout << "测试set，年、月、日非法，都是1900-01-01" << endl;

		Date d1, d2, d3, d4;
		d1.set(2112, 2, 29);
		d2.set(2019, 2, 29);
		d3.set(2023, 11, 32);
		d4.set(2023, 13, 12);
		cout << "d1应该是1900-01-01，实际为：";
		d1.show();
		cout << "d2应该是1900-01-01，实际为：";
		d2.show();
		cout << "d3应该是1900-01-01，实际为：";
		d3.show();
		cout << "d4应该是1900-01-01，实际为：";
		d4.show();

		wait_for_enter();
	}

	if (1) {
		Date d1(2023, 12, 1);
		int y, m, d;

		cout << "测试get" << endl;
		d1.get(y, m, d);

		cout << "应该y=2023,m=12,d=1，实际为：";
		cout << "y=" << y << ",m=" << m << ",d=" << d << endl;

		wait_for_enter();
	}

	if (1) {
		Date d1(2023, 12, 1);
		Date d2;

		cout << "测试cout" << endl;
		cout << "d1应该是2023-12-01，实际为：" << d1 << endl;
		cout << "d2应该是1900-01-01，实际为：" << d2 << endl;

		wait_for_enter();
	}

	if (1) {
		Date d1;

		cout << "测试cin/cout" << endl;

		cout << "请输入2023 12 1" << endl;
		cin >> d1;
		cout << "d1应该是2023-12-01，实际为：" << d1 << endl;

		cout << "请输入2020 2 29" << endl;
		cin >> d1;
		cout << "d1应该是2020-02-29，实际为：" << d1 << endl;

		cout << "请输入2023 2 29" << endl;
		cin >> d1;
		cout << "d1应该是1900-01-01，实际为：" << d1 << endl;

		cout << "请输入1899 4 10" << endl;
		cin >> d1;
		cout << "d1应该是1900-01-01，实际为：" << d1 << endl;

		cout << "请输入2023 13 10" << endl;
		cin >> d1;
		cout << "d1应该是1900-01-01，实际为：" << d1 << endl;

		cout << "请输入2023 11 31" << endl;
		cin >> d1;
		cout << "d1应该是1900-01-01，实际为：" << d1 << endl;

		cout << "请输入2112 15 34" << endl;
		cin >> d1;
		cout << "d1应该是1900-01-01，实际为：" << d1 << endl;

		wait_for_enter();
	}

	if (1) {
		cout << "转换构造函数测试，包括合法及非法值" << endl;

		Date d1(0);
		Date d2(73048);
		Date d3(-100);
		Date d4(80000);
		Date d5(35000);
		Date d6(45259);
		Date d7(INT_MIN);
		Date d8(INT_MAX);

		cout << "d1应该是1900-01-01，实际为：";
		d1.show();
		cout << "d2应该是2099-12-31，实际为：";
		d2.show();
		cout << "d3应该是2099-09-23，实际为：";
		d3.show();
		cout << "d4应该是1919-01-13，实际为：";
		d4.show();
		cout << "d5应该是1995-10-30，实际为：";
		d5.show();
		cout << "d6应该是2023-12-01，实际为：";
		d6.show();
		cout << "d7应该是1929-09-20，实际为：";
		d7.show();
		cout << "d8应该是2070-04-13，实际为：";
		d8.show();

		wait_for_enter();
	}

	if (1) {
		cout << "类型转换函数测试，包括合法及非法值" << endl;

		Date d1(1900, 1, 1);
		Date d2(2099, 12, 31);
		Date d3(1995, 10, 30);
		Date d4(2023, 12, 1);
		cout << "d1应该是0，    实际为：" << int(d1) << endl;
		cout << "d2应该是73048，实际为：" << int(d2) << endl;
		cout << "d3应该是35000，实际为：" << int(d3) << endl;
		cout << "d4应该是45259，实际为：" << int(d4) << endl;

		wait_for_enter();
	}

	if (1) {
		cout << "测试+/- n" << endl;

		Date d1(2023, 12, 1);
		Date d2;

		d2 = d1 + 27;
		cout << "d2应该是2023-12-28，   实际为：" << d2 << endl;

		d2 = 27 + d1;
		cout << "d2应该是2023-12-28，   实际为：" << d2 << endl;

		d2 = d1 - 25;
		cout << "d2应该是2023-11-06，   实际为：" << d2 << endl;

		d1.set(2020, 2, 28);
		d2 = d1 + 3;
		cout << "d2应该是2020-03-02，   实际为：" << d2 << endl;

		d1.set(2023, 2, 28);
		d2 = d1 + 3;
		cout << "d2应该是2023-03-03，   实际为：" << d2 << endl;

		d1.set(2023, 12, 28);
		d2 = d1 + 5;
		cout << "d2应该是2024-01-02，   实际为：" << d2 << endl;

		d1.set(2023, 1, 1);
		d2 = d1 - 5;
		cout << "d2应该是2022-12-27，   实际为：" << d2 << endl;

		d1.set(2019, 12, 31);
		d2 = d1 + 367;
		cout << "d2应该是2021-01-01，   实际为：" << d2 << endl;

		d1.set(2022, 12, 31);
		d2 = d1 + 366;
		cout << "d2应该是2024-01-01，   实际为：" << d2 << endl;

		d1.set(2024, 1, 1);
		d2 = d1 - 366;
		cout << "d2应该是2022-12-31，   实际为：" << d2 << endl;

		d1.set(2021, 1, 1);
		d2 = d1 - 367;
		cout << "d2应该是2019-12-31，   实际为：" << d2 << endl;

		d1.set(1900, 1, 1);
		d2 = d1 - 1;
		cout << "d2应该是2099-12-31，   实际为：" << d2 << endl;
		d2 = d1 - 10;
		cout << "d2应该是2099-12-22，   实际为：" << d2 << endl;

		d1.set(2099, 12, 31);
		d2 = d1 + 1;
		cout << "d2应该是1900-01-01，   实际为：" << d2 << endl;
		d2 = d1 + 5;
		cout << "d2应该是1900-01-05，   实际为：" << d2 << endl;

		d1.set(2023, 12, 1);
		cout << "d1+27应该是2023-12-28，实际为：" << d1 + 27 << endl;
		cout << "27+d1应该是2023-12-28，实际为：" << 27 + d1 << endl;
		cout << "d1-25应该是2023-11-06，实际为：" << d1 - 25 << endl;

		d1.set(2023, 12, 1);
		d2 = d1 + 73049;
		cout << "d2应该是2023-12-01，   实际为：" << d2 << endl;
		d2 = d1 - 73049;
		cout << "d2应该是2023-12-01，   实际为：" << d2 << endl;
		d2 = d1 + 10000000;
		cout << "d2应该是2002-10-19，   实际为：" << d2 << endl;
		d2 = d1 - 20000000;
		cout << "d2应该是2066-02-24，   实际为：" << d2 << endl;

		wait_for_enter();
	}

	if (1) {
		cout << "测试date-date" << endl;

		Date d1(2023, 12, 1);
		Date d2(2023, 10, 13);

		cout << "日期差值应为49，   实际为：" << d1 - d2 << endl;

		d2.set(2023, 12, 17);
		cout << "日期差值应为-16，  实际为：" << d1 - d2 << endl;

		d1.set(2020, 3, 2);
		d2.set(2020, 2, 27);
		cout << "日期差值应为4，    实际为：" << d1 - d2 << endl;

		d1.set(2023, 3, 2);
		d2.set(2023, 2, 27);
		cout << "日期差值应为3，    实际为：" << d1 - d2 << endl;

		d1.set(2023, 1, 2);
		d2.set(2022, 12, 27);
		cout << "日期差值应为6，    实际为：" << d1 - d2 << endl;

		d1.set(2023, 1, 1);
		d2.set(2021, 12, 31);
		cout << "日期差值应为366，  实际为：" << d1 - d2 << endl;

		d1.set(2021, 1, 1);
		d2.set(2019, 12, 31);
		cout << "日期差值应为367，  实际为：" << d1 - d2 << endl;

		d1.set(1900, 1, 1);
		d2.set(2099, 12, 31);
		cout << "d1-d2应该是-73048，实际为：" << d1 - d2 << endl;
		cout << "d2-d1应该是73048， 实际为：" << d2 - d1 << endl;

		wait_for_enter();
	}

	if (1) {
		cout << "测试++/--" << endl;

		Date d1, d2;

		d1.set(2023, 12, 1);
		d2 = d1++;
		cout << "d1应该是2023-12-02，实际为：" << d1 << endl;
		cout << "d2应该是2023-12-01，实际为：" << d2 << endl;

		d1.set(2023, 12, 1);
		d2 = ++d1;
		cout << "d1应该是2023-12-02，实际为：" << d1 << endl;
		cout << "d2应该是2023-12-02，实际为：" << d2 << endl;

		d1.set(2023, 12, 1);
		d2 = d1--;
		cout << "d1应该是2023-11-30，实际为：" << d1 << endl;
		cout << "d2应该是2023-12-01，实际为：" << d2 << endl;

		d1.set(2023, 12, 1);
		d2 = --d1;
		cout << "d1应该是2023-11-30，实际为：" << d1 << endl;
		cout << "d2应该是2023-11-30，实际为：" << d2 << endl;

		d1.set(2022, 12, 31);
		d2 = d1++;
		cout << "d1应该是2023-01-01，实际为：" << d1 << endl;
		cout << "d2应该是2022-12-31，实际为：" << d2 << endl;

		d1.set(2023, 1, 1);
		d2 = d1--;
		cout << "d1应该是2022-12-31，实际为：" << d1 << endl;
		cout << "d2应该是2023-01-01，实际为：" << d2 << endl;

		d1.set(2020, 2, 28);
		d2 = d1++;
		cout << "d1应该是2020-02-29，实际为：" << d1 << endl;
		cout << "d2应该是2020-02-28，实际为：" << d2 << endl;

		d1.set(2023, 2, 28);
		d2 = d1++;
		cout << "d1应该是2023-03-01，实际为：" << d1 << endl;
		cout << "d2应该是2023-02-28，实际为：" << d2 << endl;

		d1.set(2020, 3, 1);
		d2 = d1--;
		cout << "d1应该是2020-02-29，实际为：" << d1 << endl;
		cout << "d2应该是2020-03-01，实际为：" << d2 << endl;

		d1.set(2023, 3, 1);
		d2 = d1--;
		cout << "d1应该是2023-02-28，实际为：" << d1 << endl;
		cout << "d2应该是2023-03-01，实际为：" << d2 << endl;

		d1.set(2099, 12, 31);
		d2 = ++d1;
		cout << "d1应该是1900-01-01，实际为：" << d1 << endl;
		cout << "d2应该是1900-01-01，实际为：" << d2 << endl;

		d1.set(2099, 12, 31);
		d2 = d1++;
		cout << "d1应该是1900-01-01，实际为：" << d1 << endl;
		cout << "d2应该是2099-12-31，实际为：" << d2 << endl;

		d1.set(1900, 1, 1);
		d2 = --d1;
		cout << "d1应该是2099-12-31，实际为：" << d1 << endl;
		cout << "d2应该是2099-12-31，实际为：" << d2 << endl;

		d1.set(1900, 1, 1);
		d2 = d1--;
		cout << "d1应该是2099-12-31，实际为：" << d1 << endl;
		cout << "d2应该是1900-01-01，实际为：" << d2 << endl;

		wait_for_enter();
	}

	if (1) {
		cout << "测试比较运算符" << endl;

		Date d1(2023, 12, 1);
		Date d2(2023, 12, 1);
		Date d3(2023, 11, 29);

		cout << "比较结果应为0，实际为：" << (d1 > d2) << endl;
		cout << "比较结果应为1，实际为：" << (d1 >= d2) << endl;
		cout << "比较结果应为0，实际为：" << (d1 < d2) << endl;
		cout << "比较结果应为1，实际为：" << (d1 <= d2) << endl;
		cout << "比较结果应为1，实际为：" << (d1 == d2) << endl;
		cout << "比较结果应为0，实际为：" << (d1 != d2) << endl;

		cout << "比较结果应为1，实际为：" << (d1 > d3) << endl;
		cout << "比较结果应为1，实际为：" << (d1 >= d3) << endl;
		cout << "比较结果应为0，实际为：" << (d1 < d3) << endl;
		cout << "比较结果应为0，实际为：" << (d1 <= d3) << endl;
		cout << "比较结果应为0，实际为：" << (d1 == d3) << endl;
		cout << "比较结果应为1，实际为：" << (d1 != d3) << endl;

		wait_for_enter();
	}

	return 0;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
static int test_for_time()
{
	cout << setfill('=') << setw(20) << "=" << endl;
	cout << "     Time类测试" << endl;
	cout << setw(20) << "=" << endl;
	cout << setfill(' ');

	if (1) {
		cout << "测试初始化，完全正确的赋值" << endl;

		Time t1;
		Time t2(10, 11, 12);
		Time t3(0, 0, 0);
		Time t4(23, 59, 59);
		cout << "t1应该是00:00:00，实际为：";
		t1.show();
		cout << "t2应该是10:11:12，实际为：";
		t2.show();
		cout << "t3应该是00:00:00，实际为：";
		t3.show();
		cout << "t4应该是23:59:59，实际为：";
		t4.show();

		wait_for_enter();
	}

	if (1) {
		cout << "测试初始化，时、分、秒非法" << endl;

		/* 都是00:00:00 */
		Time t1(-1, 2, 3);
		Time t2(1, -2, 3);
		Time t3(1, 2, -3);
		Time t4(-1, -2, -3);
		cout << "t1应该是00:00:00，实际为：";
		t1.show();
		cout << "t2应该是00:00:00，实际为：";
		t2.show();
		cout << "t3应该是00:00:00，实际为：";
		t3.show();
		cout << "t4应该是00:00:00，实际为：";
		t4.show();

		wait_for_enter();
	}

	if (1) {
		cout << "测试set，带缺省值" << endl;

		Time t1, t2, t3;
		t1.set(10, 11, 12);
		t2.set(10, 11);
		t3.set(10);
		cout << "t1应该是10:11:12，实际为：";
		t1.show();
		cout << "t2应该是10:11:00，实际为：";
		t2.show();
		cout << "t3应该是10:00:00，实际为：";
		t3.show();

		t1.set(10, -1, -2);
		t2.set(10, -1);
		t3.set(-1, 10);
		cout << "t1应该是00:00:00，实际为：";
		t1.show();
		cout << "t2应该是00:00:00，实际为：";
		t2.show();
		cout << "t3应该是00:00:00，实际为：";
		t3.show();

		t1.set(-1, -2, -3);
		t2.set(-1, -2);
		t3.set(-1);
		cout << "t1应该是00:00:00，实际为：";
		t1.show();
		cout << "t2应该是00:00:00，实际为：";
		t2.show();
		cout << "t3应该是00:00:00，实际为：";
		t3.show();

		wait_for_enter();
	}

	if (1) {
		Time t1(10, 11, 12);
		int h, m, s;

		cout << "测试get" << endl;
		t1.get(h, m, s);

		cout << "应该h=10,m=11,s=12，实际为：";
		cout << "h=" << h << ",m=" << m << ",s=" << s << endl;

		wait_for_enter();
	}

	if (1) {
		Time t1(10, 11, 12);
		Time t2;

		cout << "测试cout" << endl;
		cout << "t1应该是10:11:12，实际为：" << t1 << endl;
		cout << "t2应该是00:00:00，实际为：" << t2 << endl;

		wait_for_enter();
	}

	if (1) {
		Time t1;

		cout << "测试cin/cout" << endl;

		cout << "请输入0 0 0" << endl;
		cin >> t1;
		cout << "t1应该是00:00:00，实际为：" << t1 << endl;

		cout << "请输入23 59 59" << endl;
		cin >> t1;
		cout << "t1应该是23:59:59，实际为：" << t1 << endl;

		cout << "请输入10 11 12" << endl;
		cin >> t1;
		cout << "t1应该是10:11:12，实际为：" << t1 << endl;

		cout << "请输入0 0 60" << endl;
		cin >> t1;
		cout << "t1应该是00:00:00，实际为：" << t1 << endl;

		cout << "请输入0 60 0" << endl;
		cin >> t1;
		cout << "t1应该是00:00:00，实际为：" << t1 << endl;

		cout << "请输入24 0 0" << endl;
		cin >> t1;
		cout << "t1应该是00:00:00，实际为：" << t1 << endl;

		cout << "请输入-1 -2 -3" << endl;
		cin >> t1;
		cout << "t1应该是00:00:00，实际为：" << t1 << endl;

		wait_for_enter();
	}

	if (1) {
		cout << "转换构造函数测试，包括合法及非法值" << endl;

		Time t1(0);
		Time t2(86399);
		Time t3(-1000);
		Time t4(90000);
		Time t5(35000);
		Time t6(45000);
		Time t7(INT_MIN);
		Time t8(INT_MAX);

		cout << "t1应该是00:00:00，实际为：";
		t1.show();
		cout << "t2应该是23:59:59，实际为：";
		t2.show();
		cout << "t3应该是23:43:20，实际为：";
		t3.show();
		cout << "t4应该是01:00:00，实际为：";
		t4.show();
		cout << "t5应该是09:43:20，实际为：";
		t5.show();
		cout << "t6应该是12:30:00，实际为：";
		t6.show();
		cout << "t7应该是20:45:52，实际为：";
		t7.show();
		cout << "t8应该是03:14:07，实际为：";
		t8.show();

		wait_for_enter();
	}

	if (1) {
		cout << "类型转换函数测试，包括合法及非法值" << endl;

		Time t1;
		Time t2(23, 59, 59);
		Time t3(9, 43, 20);
		cout << "t1应该是0，    实际为：" << int(t1) << endl;
		cout << "t2应该是86399，实际为：" << int(t2) << endl;
		cout << "t3应该是35000，实际为：" << int(t3) << endl;

		wait_for_enter();
	}

	if (1) {
		cout << "测试+/- n" << endl;

		Time t1(10, 11, 12);
		Time t2;

		t2 = t1 + 3661;
		cout << "t2应该是11:12:13，实际为：" << t2 << endl;

		t2 = 3661 + t1;
		cout << "t2应该是11:12:13，实际为：" << t2 << endl;

		t2 = t1 - 13;
		cout << "t2应该是10:10:59，实际为：" << t2 << endl;

		t2 = t1 + 49;
		cout << "t2应该是10:12:01，实际为：" << t2 << endl;

		t2 = t1 + 86400;
		cout << "t2应该是10:11:12，实际为：" << t2 << endl;

		t2 = t1 - 86400;
		cout << "t2应该是10:11:12，实际为：" << t2 << endl;

		t2 = t1 - 10000000;
		cout << "t2应该是16:24:32，实际为：" << t2 << endl;

		t2 = t1 + 20000000;
		cout << "t2应该是21:44:32，实际为：" << t2 << endl;

		wait_for_enter();
	}

	if (1) {
		cout << "测试time-time" << endl;

		Time t1(10, 11, 12);
		Time t2(15, 16, 17);

		cout << "时间差值应为-18305，实际为：" << t1 - t2 << endl;
		cout << "日期差值应为18305， 实际为：" << t2 - t1 << endl;

		t1.set(0, 0, 0);
		t2.set(23, 59, 59);
		cout << "日期差值应为-86399，实际为：" << t1 - t2 << endl;
		cout << "日期差值应为86399， 实际为：" << t2 - t1 << endl;

		t1.set(10, 11, 12);
		t2.set(11, 12, 13);
		cout << "日期差值应为-3661， 实际为：" << t1 - t2 << endl;
		cout << "日期差值应为+3661， 实际为：" << t2 - t1 << endl;

		wait_for_enter();
	}

	if (1) {
		Time t1, t2;

		cout << "测试++/--" << endl;

		t1.set(10, 11, 12);
		t2 = ++t1;
		cout << "t1应该是10:11:13， 实际为：" << t1 << endl;
		cout << "t2应该是10:11:13， 实际为：" << t2 << endl;

		t1.set(10, 11, 12);
		t2 = t1++;
		cout << "t1应该是10:11:13， 实际为：" << t1 << endl;
		cout << "t2应该是10:11:12， 实际为：" << t2 << endl;

		t1.set(10, 11, 12);
		t2 = --t1;
		cout << "t1应该是10:11:11， 实际为：" << t1 << endl;
		cout << "t2应该是10:11:11， 实际为：" << t2 << endl;

		t1.set(10, 11, 12);
		t2 = t1--;
		cout << "t1应该是10:11:11， 实际为：" << t1 << endl;
		cout << "t2应该是10:11:12， 实际为：" << t2 << endl;

		t1.set(0, 0, 0);
		t2 = --t1;
		cout << "t1应该是23:59:59， 实际为：" << t1 << endl;
		cout << "t2应该是23:59:59， 实际为：" << t2 << endl;

		t1.set(0, 0, 0);
		t2 = t1--;
		cout << "t1应该是23:59:59， 实际为：" << t1 << endl;
		cout << "t2应该是00:00:00， 实际为：" << t2 << endl;

		t1.set(23, 59, 59);
		t2 = ++t1;
		cout << "t1应该是00:00:00， 实际为：" << t1 << endl;
		cout << "t2应该是00:00:00， 实际为：" << t2 << endl;

		t1.set(23, 59, 59);
		t2 = t1++;
		cout << "t1应该是00:00:00， 实际为：" << t1 << endl;
		cout << "t2应该是23:59:59， 实际为：" << t2 << endl;

		wait_for_enter();
	}

	if (1) {
		cout << "测试比较运算符" << endl;

		Time t1(10, 11, 12);
		Time t2(10, 11, 12);
		Time t3(15, 16, 17);
		cout << "比较结果应为0，实际为：" << (t1 > t2) << endl;
		cout << "比较结果应为1，实际为：" << (t1 >= t2) << endl;
		cout << "比较结果应为0，实际为：" << (t1 < t2) << endl;
		cout << "比较结果应为1，实际为：" << (t1 <= t2) << endl;
		cout << "比较结果应为1，实际为：" << (t1 == t2) << endl;
		cout << "比较结果应为0，实际为：" << (t1 != t2) << endl;

		cout << "比较结果应为0，实际为：" << (t1 > t3) << endl;
		cout << "比较结果应为0，实际为：" << (t1 >= t3) << endl;
		cout << "比较结果应为1，实际为：" << (t1 < t3) << endl;
		cout << "比较结果应为1，实际为：" << (t1 <= t3) << endl;
		cout << "比较结果应为0，实际为：" << (t1 == t3) << endl;
		cout << "比较结果应为1，实际为：" << (t1 != t3) << endl;

		wait_for_enter();
	}

	return 0;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
static int test_for_datetime()
{
	cout << setfill('=') << setw(20) << "=" << endl;
	cout << "   DateTime类测试" << endl;
	cout << setw(20) << "=" << endl;
	cout << setfill(' ');

	if (1) {
		cout << "测试初始化，完全正确的赋值" << endl;

		DateTime t1;
		DateTime t2(2023, 12, 15, 10, 11, 12);
		DateTime t3(1900, 1, 1, 0, 0, 0);
		DateTime t4(2099, 12, 31, 23, 59, 59);
		cout << "t1应该是1900-01-01 00:00:00，实际为：";
		t1.show();
		cout << "t2应该是2023-12-15 10:11:12，实际为：";
		t2.show();
		cout << "t3应该是1900-01-01 00:00:00，实际为：";
		t3.show();
		cout << "t4应该是2099-12-31 23:59:59，实际为：";
		t4.show();

		wait_for_enter();
	}

	if (1) {
		cout << "测试初始化，年、月、日有一个/多个非法" << endl;

		/* 单个错 */
		DateTime t1(1870, 3, 15, 10, 11, 12);
		DateTime t2(2112, 3, 4, 10, 11, 12);
		DateTime t3(2005, 13, 15, 10, 11, 12);
		DateTime t4(2023, 11, 31, 10, 11, 12);
		cout << "t1应该是1900-01-01 00:00:00，实际为：";
		t1.show();
		cout << "t2应该是1900-01-01 00:00:00，实际为：";
		t2.show();
		cout << "t3应该是1900-01-01 00:00:00，实际为：";
		t3.show();
		cout << "t4应该是1900-01-01 00:00:00，实际为：";
		t4.show();

		/* 多个错 */
		DateTime t5(1899, 2, 29, 10, 11, 12);
		DateTime t6(1899, 2, 30, 10, 11, 12);
		DateTime t7(1899, 13, 31, 10, 11, 12);
		DateTime t8(1899, 13, 32, 10, 11, 12);
		cout << "t5应该是1900-01-01 00:00:00，实际为：";
		t5.show();
		cout << "t6应该是1900-01-01 00:00:00，实际为：";
		t6.show();
		cout << "t7应该是1900-01-01 00:00:00，实际为：";
		t7.show();
		cout << "t8应该是1900-01-01 00:00:00，实际为：";
		t8.show();

		wait_for_enter();
	}

	if (1) {
		cout << "测试初始化，闰年" << endl;

		DateTime t1(2023, 2, 29, 10, 11, 12);
		DateTime t2(2020, 2, 29, 10, 11, 12);
		cout << "t1应该是1900-01-01 00:00:00，实际为：";
		t1.show();
		cout << "t2应该是2020-02-29 10:11:12，实际为：";
		t2.show();

		wait_for_enter();
	}

	if (1) {
		cout << "测试初始化，时、分、秒一个/多个非法" << endl;

		/* 都是00:00:00 */
		DateTime t1(2023, 12, 15, 24, 11, 12);
		DateTime t2(2023, 12, 15, 10, 60, 12);
		DateTime t3(2023, 12, 15, 10, 11, 60);
		DateTime t4(2023, 12, 15, 24, 60, 60);
		DateTime t5(2023, 12, 15, 10, 60, 60);
		DateTime t6(2023, 12, 15, 24, 11, 60);
		DateTime t7(2023, 12, 15, 24, 60, 12);
		cout << "t1应该是1900-01-01 00:00:00，实际为：";
		t1.show();
		cout << "t2应该是1900-01-01 00:00:00，实际为：";
		t2.show();
		cout << "t3应该是1900-01-01 00:00:00，实际为：";
		t3.show();
		cout << "t4应该是1900-01-01 00:00:00，实际为：";
		t4.show();
		cout << "t5应该是1900-01-01 00:00:00，实际为：";
		t5.show();
		cout << "t6应该是1900-01-01 00:00:00，实际为：";
		t6.show();
		cout << "t7应该是1900-01-01 00:00:00，实际为：";
		t6.show();

		wait_for_enter();
	}

	if (1) {
		cout << "测试set，带缺省值" << endl;

		DateTime t1, t2, t3, t4, t5, t6, t7;
		t1.set(2023, 12, 15, 10, 11, 12);
		t2.set(2023, 12, 15, 10, 11);
		t3.set(2023, 12, 15, 10);
		t4.set(2023, 12, 15);
		t5.set(2023, 12);
		t6.set(2023);
		t7.set();
		cout << "t1应该是2023-12-15 10:11:12，实际为：";
		t1.show();
		cout << "t2应该是2023-12-15 10:11:00，实际为：";
		t2.show();
		cout << "t3应该是2023-12-15 10:00:00，实际为：";
		t3.show();
		cout << "t4应该是2023-12-15 00:00:00，实际为：";
		t4.show();
		cout << "t5应该是2023-12-01 00:00:00，实际为：";
		t5.show();
		cout << "t6应该是2023-01-01 00:00:00，实际为：";
		t6.show();
		cout << "t7应该是1900-01-01 00:00:00，实际为：";
		t7.show();

		t1.set(2023, 12, 15, 24, 11, 12);
		t2.set(2023, 12, 15, 10, 60, 12);
		t3.set(2023, 12, 15, 10, 11, 60);
		t4.set(2023, 12, 15, 24, 60, 60);
		t5.set(2023, 12, 15, 10, 60, 60);
		t6.set(2023, 12, 15, 24, 11, 60);
		t7.set(2023, 12, 15, 24, 60, 12);
		cout << "t1应该是1900-01-01 00:00:00，实际为：";
		t1.show();
		cout << "t2应该是1900-01-01 00:00:00，实际为：";
		t2.show();
		cout << "t3应该是1900-01-01 00:00:00，实际为：";
		t3.show();
		cout << "t4应该是1900-01-01 00:00:00，实际为：";
		t4.show();
		cout << "t5应该是1900-01-01 00:00:00，实际为：";
		t5.show();
		cout << "t6应该是1900-01-01 00:00:00，实际为：";
		t6.show();
		cout << "t7应该是1900-01-01 00:00:00，实际为：";
		t7.show();

		wait_for_enter();
	}

	if (1) {
		DateTime t1(2023, 12, 15, 10, 11, 12);
		int y, mo, d, h, m, s;

		cout << "测试get" << endl;
		t1.get(y, mo, d, h, m, s);

		cout << "应该y=2023, mo=12, d=15, h=10,m=11,s=12，实际为：";
		cout << "y=" << y << ",mo=" << mo << ",d=" << d << ",h=" << h << ",m=" << m << ",s=" << s << endl;

		wait_for_enter();
	}

	if (1) {
		DateTime t1(2023, 12, 15, 10, 11, 12);
		DateTime t2;

		cout << "测试cout" << endl;
		cout << "t1应该是2023-12-15 10:11:12，实际为：" << t1 << endl;
		cout << "t2应该是1900-01-01 00:00:00，实际为：" << t2 << endl;

		wait_for_enter();
	}

	if (1) {
		DateTime t1;

		cout << "测试cin/cout" << endl;

		cout << "请输入1900 1 1 0 0 0" << endl;
		cin >> t1;
		cout << "t1应该是1900-01-01 00:00:00，实际为：" << t1 << endl;

		cout << "请输入2099 12 31 23 59 59" << endl;
		cin >> t1;
		cout << "t1应该是2099-12-31 23:59:59，实际为：" << t1 << endl;

		cout << "请输入2023 12 15 10 11 12" << endl;
		cin >> t1;
		cout << "t1应该是2023-12-15 10:11:12，实际为：" << t1 << endl;

		cout << "请输入2023 2 29 10 11 12" << endl;
		cin >> t1;
		cout << "t1应该是1900-01-01 00:00:00，实际为：" << t1 << endl;

		cout << "请输入2020 2 29 10 11 12" << endl;
		cin >> t1;
		cout << "t1应该是2020-02-29 10:11:12，实际为：" << t1 << endl;

		cout << "请输入1899 12 15 10 11 12" << endl;
		cin >> t1;
		cout << "t1应该是1900-01-01 00:00:00，实际为：" << t1 << endl;

		cout << "请输入2023 13 15 10 11 12" << endl;
		cin >> t1;
		cout << "t1应该是1900-01-01 00:00:00，实际为：" << t1 << endl;

		cout << "请输入2023 12 32 10 11 12" << endl;
		cin >> t1;
		cout << "t1应该是1900-01-01 00:00:00，实际为：" << t1 << endl;

		cout << "请输入2023 12 15 10 11 60" << endl;
		cin >> t1;
		cout << "t1应该是1900-01-01 00:00:00，实际为：" << t1 << endl;

		cout << "请输入2023 13 15 24 60 60" << endl;
		cin >> t1;
		cout << "t1应该是1900-01-01 00:00:00，实际为：" << t1 << endl;

		cout << "请输入2100 12 15 24 11 60" << endl;
		cin >> t1;
		cout << "t1应该是1900-01-01 00:00:00，实际为：" << t1 << endl;

		cout << "请输入2023 11 31 10 11 60" << endl;
		cin >> t1;
		cout << "t1应该是1900-01-01 00:00:00，实际为：" << t1 << endl;

		cout << "请输入2023 12 15 24 60 12" << endl;
		cin >> t1;
		cout << "t1应该是1900-01-01 00:00:00，实际为：" << t1 << endl;

		wait_for_enter();
	}

	if (1) {
		cout << "转换构造函数测试，包括合法及非法值" << endl;

		DateTime t1(0);
		DateTime t2(86399);
		DateTime t3(-1000);
		DateTime t4(90000);
		DateTime t5(350000000);
		DateTime t6(123456789);
		DateTime t7(LLONG_MIN);
		DateTime t8(LLONG_MAX);

		cout << "t1应该是1900-01-01 00:00:00，实际为：";
		t1.show();
		cout << "t2应该是1900-01-01 23:59:59，实际为：";
		t2.show();
		cout << "t3应该是2099-12-31 23:43:20，实际为：";
		t3.show();
		cout << "t4应该是1900-01-02 01:00:00，实际为：";
		t4.show();
		cout << "t5应该是1911-02-03 22:13:20，实际为：";
		t5.show();
		cout << "t6应该是1903-11-30 21:33:09，实际为：";
		t6.show();
		cout << "t7应该是2027-08-31 08:29:52，实际为：";
		t7.show();
		cout << "t8应该是1972-05-03 15:30:07，实际为：";
		t8.show();

		wait_for_enter();
	}

	if (1) {
		cout << "类型转换函数测试，包括合法及非法值" << endl;

		DateTime t1;
		DateTime t2(2099, 12, 31, 23, 59, 59);
		DateTime t3(2023, 12, 15, 10, 11, 12);
		DateTime t4(2023, 13, 15, 24, 11, 65);
		cout << "t1应该是0，         实际为：" << (long long)(t1) << endl;
		cout << "t2应该是6311433599，实际为：" << (long long)(t2) << endl;
		cout << "t3应该是3911623872，实际为：" << (long long)(t3) << endl;
		cout << "t4应该是0，         实际为：" << (long long)(t4) << endl;

		wait_for_enter();
	}

	if (1) {
		cout << "测试+/- n" << endl;

		DateTime t1(2023, 12, 15, 10, 11, 12);
		DateTime t2;
		t2 = t1 + 3661;
		cout << "t2应该是2023-12-15 11:12:13，实际为：" << t2 << endl;//有错，原先是2015

		t2 = 3661 + t1;
		cout << "t2应该是2023-12-15 11:12:13，实际为：" << t2 << endl;

		t2 = t1 - 13;
		cout << "t2应该是2023-12-15 10:10:59，实际为：" << t2 << endl;

		t2 = t1 + 49;
		cout << "t2应该是2023-12-15 10:12:01，实际为：" << t2 << endl;

		t2 = t1 + 86400;
		cout << "t2应该是2023-12-16 10:11:12，实际为：" << t2 << endl;

		t2 = t1 - 86400;
		cout << "t2应该是2023-12-14 10:11:12，实际为：" << t2 << endl;

		t2 = t1 - 987654321;
		cout << "t2应该是1992-08-28 05:45:51，实际为：" << t2 << endl;

		t2 = t1 + 123456789;
		cout << "t2应该是2027-11-13 07:44:21，实际为：" << t2 << endl;

		t2 = t1 + 6311433600 * 12;
		cout << "t2应该是2023-12-15 10:11:12，实际为：" << t2 << endl;

		t2 = t1 - 6311433600 * 8;
		cout << "t2应该是2023-12-15 10:11:12，实际为：" << t2 << endl;

		wait_for_enter();
	}

	if (1) {
		cout << "测试time-time" << endl;

		DateTime t1(2023, 10, 15, 10, 11, 12);
		DateTime t2(2023, 10, 15, 15, 16, 17);

		cout << "时间差值应为-18305，     实际为：" << t1 - t2 << endl;
		cout << "日期差值应为18305，      实际为：" << t2 - t1 << endl;

		t1.set(2023, 10, 15, 10, 11, 12);
		t2.set(2023, 10, 15, 11, 12, 13);
		cout << "日期差值应为-3661，      实际为：" << t1 - t2 << endl;
		cout << "日期差值应为+3661，      实际为：" << t2 - t1 << endl;

		t1.set(2023, 2, 28, 10, 11, 12);
		t2.set(2023, 3, 1, 10, 11, 12);
		cout << "日期差值应为-86400，     实际为：" << t1 - t2 << endl;
		cout << "日期差值应为+86400，     实际为：" << t2 - t1 << endl;

		t1.set(2020, 2, 28, 10, 11, 12);
		t2.set(2020, 3, 1, 10, 11, 12);
		cout << "日期差值应为-172800，    实际为：" << t1 - t2 << endl;
		cout << "日期差值应为+172800，    实际为：" << t2 - t1 << endl;

		t1.set();
		t2.set(2099, 12, 31, 23, 59, 59);
		cout << "日期差值应为-6311433599，实际为：" << t1 - t2 << endl;
		cout << "日期差值应为6311433599， 实际为：" << t2 - t1 << endl;

		t1.set(2023, 12, 15, 10, 11, 12); //31536000 = 365*86400
		t2.set(2022, 12, 15, 10, 11, 12);
		cout << "日期差值应为31536000，  实际为：" << t1 - t2 << endl;
		cout << "日期差值应为-31536000，   实际为：" << t2 - t1 << endl;

		t1.set(2020, 12, 15, 10, 11, 12); //31536000 = 366*86400
		t2.set(2019, 12, 15, 10, 11, 12);
		cout << "日期差值应为31622400，  实际为：" << t1 - t2 << endl;
		cout << "日期差值应为-31622400，   实际为：" << t2 - t1 << endl;

		wait_for_enter();
	}

	if (1) {
		DateTime t1, t2;

		cout << "测试++/--" << endl;

		t1.set(2023, 12, 15, 10, 11, 12);
		t2 = ++t1;
		cout << "t1应该是2023-12-15 10:11:13，实际为：" << t1 << endl;
		cout << "t2应该是2023-12-15 10:11:13，实际为：" << t2 << endl;

		t1.set(2023, 12, 15, 10, 11, 12);
		t2 = t1++;
		cout << "t1应该是2023-12-15 10:11:13，实际为：" << t1 << endl;
		cout << "t2应该是2023-12-15 10:11:12，实际为：" << t2 << endl;

		t1.set(2023, 12, 15, 10, 11, 12);
		t2 = --t1;
		cout << "t1应该是2023-12-15 10:11:11，实际为：" << t1 << endl;
		cout << "t2应该是2023-12-15 10:11:11，实际为：" << t2 << endl;

		t1.set(2023, 12, 15, 10, 11, 12);
		t2 = t1--;
		cout << "t1应该是2023-12-15 10:11:11，实际为：" << t1 << endl;
		cout << "t2应该是2023-12-15 10:11:12，实际为：" << t2 << endl;

		t1.set(2023, 12, 15, 23, 59, 59);
		t2 = ++t1;
		cout << "t1应该是2023-12-16 00:00:00，实际为：" << t1 << endl;
		cout << "t2应该是2023-12-16 00:00:00，实际为：" << t2 << endl;

		t1.set(2023, 12, 15, 23, 59, 59);
		t2 = t1++;
		cout << "t1应该是2023-12-16 00:00:00，实际为：" << t1 << endl;
		cout << "t2应该是2023-12-15 23:59:59，实际为：" << t2 << endl;

		t1.set(2023, 12, 15, 0, 0, 0);
		t2 = --t1;
		cout << "t1应该是2023-12-14 23:59:59，实际为：" << t1 << endl;
		cout << "t2应该是2023-12-14 23:59:59，实际为：" << t2 << endl;

		t1.set(2023, 12, 15, 0, 0, 0);
		t2 = t1--;
		cout << "t1应该是2023-12-14 23:59:59，实际为：" << t1 << endl;
		cout << "t2应该是2023-12-15 00:00:00，实际为：" << t2 << endl;

		t1.set(2023, 2, 28, 23, 59, 59);
		t2 = ++t1;
		cout << "t1应该是2023-03-01 00:00:00，实际为：" << t1 << endl;
		cout << "t2应该是2023-03-01 00:00:00，实际为：" << t2 << endl;

		t1.set(2023, 2, 28, 23, 59, 59);
		t2 = t1++;
		cout << "t1应该是2023-03-01 00:00:00，实际为：" << t1 << endl;
		cout << "t2应该是2023-02-28 23:59:59，实际为：" << t2 << endl;

		t1.set(2023, 3, 1, 0, 0, 0);
		t2 = --t1;
		cout << "t1应该是2023-02-28 23:59:59，实际为：" << t1 << endl;
		cout << "t2应该是2023-02-28 23:59:59，实际为：" << t2 << endl;

		t1.set(2023, 3, 1, 0, 0, 0);
		t2 = t1--;
		cout << "t1应该是2023-02-28 23:59:59，实际为：" << t1 << endl;
		cout << "t2应该是2023-03-01 00:00:00，实际为：" << t2 << endl;

		t1.set(2020, 2, 28, 23, 59, 59);
		t2 = ++t1;
		cout << "t1应该是2020-02-29 00:00:00，实际为：" << t1 << endl;
		cout << "t2应该是2020-02-29 00:00:00，实际为：" << t2 << endl;

		t1.set(2020, 2, 28, 23, 59, 59);
		t2 = t1++;
		cout << "t1应该是2020-02-29 00:00:00，实际为：" << t1 << endl;
		cout << "t2应该是2020-02-28 23:59:59，实际为：" << t2 << endl;

		t1.set(2020, 3, 1, 0, 0, 0);
		t2 = --t1;
		cout << "t1应该是2020-02-29 23:59:59，实际为：" << t1 << endl;
		cout << "t2应该是2020-02-29 23:59:59，实际为：" << t2 << endl;

		t1.set(2020, 3, 1, 0, 0, 0);
		t2 = t1--;
		cout << "t1应该是2020-02-29 23:59:59，实际为：" << t1 << endl;
		cout << "t2应该是2020-03-01 00:00:00，实际为：" << t2 << endl;


		t1.set(2099, 12, 31, 23, 59, 59);
		t2 = ++t1;
		cout << "t1应该是1900-01-01 00:00:00，实际为：" << t1 << endl;
		cout << "t2应该是1900-01-01 00:00:00，实际为：" << t2 << endl;

		t1.set(2099, 12, 31, 23, 59, 59);
		t2 = t1++;
		cout << "t1应该是1900-01-01 00:00:00，实际为：" << t1 << endl;
		cout << "t2应该是2099-12-31 23:59:59，实际为：" << t2 << endl;

		t1.set(1900, 1, 1, 0, 0, 0);
		t2 = --t1;
		cout << "t1应该是2099-12-31 23:59:59，实际为：" << t1 << endl;
		cout << "t2应该是2099-12-31 23:59:59，实际为：" << t2 << endl;

		t1.set(1900, 1, 1, 0, 0, 0);
		t2 = t1--;
		cout << "t1应该是2099-12-31 23:59:59，实际为：" << t1 << endl;
		cout << "t2应该是1900-01-01 00:00:00，实际为：" << t2 << endl;

		wait_for_enter();
	}

	if (1) {
		cout << "测试比较运算符" << endl;

		DateTime t1(2023, 12, 15, 10, 11, 12);
		DateTime t2(2023, 12, 15, 10, 11, 12);
		DateTime t3(2023, 12, 15, 15, 16, 17);
		cout << "比较结果应为0，实际为：" << (t1 > t2) << endl;
		cout << "比较结果应为1，实际为：" << (t1 >= t2) << endl;
		cout << "比较结果应为0，实际为：" << (t1 < t2) << endl;
		cout << "比较结果应为1，实际为：" << (t1 <= t2) << endl;
		cout << "比较结果应为1，实际为：" << (t1 == t2) << endl;
		cout << "比较结果应为0，实际为：" << (t1 != t2) << endl;

		cout << "比较结果应为0，实际为：" << (t1 > t3) << endl;
		cout << "比较结果应为0，实际为：" << (t1 >= t3) << endl;
		cout << "比较结果应为1，实际为：" << (t1 < t3) << endl;
		cout << "比较结果应为1，实际为：" << (t1 <= t3) << endl;
		cout << "比较结果应为0，实际为：" << (t1 == t3) << endl;
		cout << "比较结果应为1，实际为：" << (t1 != t3) << endl;

		wait_for_enter();
	}

	return 0;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int main()
{
	/* 按需 注释/打开 要测试的类 */ 
	test_for_date();
	test_for_time();
	test_for_datetime();

	return 0;
}
