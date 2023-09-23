/* 2254298 信11 范潇 */
#pragma once
using namespace std;
#include<iostream>
#include<conio.h>
#include<iomanip>
#include"cmd_console_tools.h"
#include<Windows.h>

//颜色
#define defaultColor 0,7
#define black 0,0
#define background black
#define backgroundhighlight 14,0
#define texthighlight 0,14
#define colorBoard  { { 15,0},{ 13,0} ,{11,0} ,{8,0} ,{14,0} ,{6,0} ,{2,0} ,{4,0} ,{1,0} ,{5,0} }
#define inverseColor 15,0
#define blockheight 3
#define blockwidth 6
#define delay Sleep(1)
#define coverLength 60
#define boardwidth 85
#define boardheight 47
#define covering "                              "
#define beat 100
#define do Beep(523,beat);
#define re Beep(578,beat);
#define mi Beep(659,beat);
#define fa Beep(698,beat);
#define so Beep(784,beat);
#define la Beep(880,beat);
#define si Beep(988,beat);

void reload(void);
void module1(int rowMax, int colMax, int matrix[][10]);
void module2(int rowMax, int colMax, int matrix[][10]);
void module3(int rowMax, int colMax, int matrix[][10]);
void module4(int rowMax, int colMax, int matrix[][10]);
void module5(int rowMax, int colMax, int matrix[][10]);
void module6(int rowMax, int colMax, int matrix[][10]);
void module7(int rowMax, int colMax, int matrix[][10]);
void matrixGenerator(int matrix[][10], int rowInterval, int colInterval, int rowMax, int colMax, int srcxcoo, int srcycoo, bool zeroHighlight);
int search(int srcRow, int srcCol, int matrix[][10], int rowMax, int colMax, int option, int x, int y, int rowInterval, int colInterval, int pivotMatrix[][10], int& sum);//xy为第一个元素的坐标
void getCoordinate(int& row, int& col, int rowMax, int colMax);
void matrixInitialize(int rowMax, int colMax, int matrix[][10], bool zeroHighlight);
void zeroMoving(int matrix[][10], int rowMax, int colMax);
int victory(int matrix[][10], int rowMax, int colMax, int& total);
void matrixInitialize(int maxRow, int maxCol, bool frame, int matrix[][10]);
void inverseBlock(int x, int y, int colorCode);
void reverseBlock(int x, int y, int colorCode);
void selectBlock(int x, int y, int colorCode);
void cancelBlock(int x, int y);