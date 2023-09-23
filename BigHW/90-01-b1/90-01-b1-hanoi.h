/* 2254298 大数据 范潇 */
#pragma once

/* ------------------------------------------------------------------------------------------------------

	 本文件功能：
	1、为了保证 hanoi_main.cpp/hanoi_menu.cpp/hanoi_multiple_solutions.cpp 能相互访问函数的函数声明
	2、一个以上的cpp中用到的宏定义（#define）或全局只读（const）变量，个数不限
	3、可以参考 cmd_console_tools.h 的写法（认真阅读并体会）
   ------------------------------------------------------------------------------------------------------ */

using namespace std;

#include"../include/cmd_console_tools.h"
#include<iostream>
#include<conio.h>
#include<iomanip>
#include<Windows.h>

#define horizontalline "---------------------------------"
#define arrow "---->"

//速度
#define speed1 20
#define speed2 15
#define speed3 10
#define speed4 5
#define speed5 0
#define speed6 25//需要延时但无需输入speed
#define delay 500
//游戏模式下提醒的持续时间

#define xcoodif 10
//竖直输出时A,B,C的x坐标之间的差

//横竖输出时的起始位置
#define htxcoo 0
#define htycoo 17
#define vtBx 21
#define vtBy 13

//4结束后的光标位置
#define endxcoo 0
#define endycoo 37
#define endcoo (endxcoo,endycoo)

#define offset 15
//游戏时向下偏移

//柱子尺寸
#define mdclxcoo 43
#define bmclycoo 15
#define clxcoodif 32
#define clsgwid 11
#define clht 13

//颜色
#define defaultColor 0,7
#define black 0,0
#define milkWhite 7,0
#define colorBoard  { {1,0},{ 13,0} ,{11,0} ,{8,0} ,{14,0} ,{6,0} ,{2,0} ,{4,0} ,{ 10,0} ,{15,0} }
#define columnColor milkWhite
#define background black

#define prolong Sleep(75);
//打印柱子和移动盘子的延时
void reload(void);
int Menu(void);
void reload(void);
void initializevariable(char input, char* src, char* dst, char* tmp, int* level);
void column();
void hanoi(int level, char src, char tmp, char dst, char inputnumber);
void module4(char src, char dst, char tmp, int level);
void module6(char src, char dst, char tmp, int level);
void module7(char src, char dst, char tmp, int level);
void module8(char src, char dst, char tmp, int level);
void module9(char src, char dst, char tmp, int level);
void hanoiplus(int level, char src, char tmp, char dst, char inputnumber);
