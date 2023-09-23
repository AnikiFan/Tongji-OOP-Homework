/* 2254298 ������ ���� */
#pragma once

/* ------------------------------------------------------------------------------------------------------

	 ���ļ����ܣ�
	1��Ϊ�˱�֤ hanoi_main.cpp/hanoi_menu.cpp/hanoi_multiple_solutions.cpp ���໥���ʺ����ĺ�������
	2��һ�����ϵ�cpp���õ��ĺ궨�壨#define����ȫ��ֻ����const����������������
	3�����Բο� cmd_console_tools.h ��д���������Ķ�����ᣩ
   ------------------------------------------------------------------------------------------------------ */

using namespace std;

#include"../include/cmd_console_tools.h"
#include<iostream>
#include<conio.h>
#include<iomanip>
#include<Windows.h>

#define horizontalline "---------------------------------"
#define arrow "---->"

//�ٶ�
#define speed1 20
#define speed2 15
#define speed3 10
#define speed4 5
#define speed5 0
#define speed6 25//��Ҫ��ʱ����������speed
#define delay 500
//��Ϸģʽ�����ѵĳ���ʱ��

#define xcoodif 10
//��ֱ���ʱA,B,C��x����֮��Ĳ�

//�������ʱ����ʼλ��
#define htxcoo 0
#define htycoo 17
#define vtBx 21
#define vtBy 13

//4������Ĺ��λ��
#define endxcoo 0
#define endycoo 37
#define endcoo (endxcoo,endycoo)

#define offset 15
//��Ϸʱ����ƫ��

//���ӳߴ�
#define mdclxcoo 43
#define bmclycoo 15
#define clxcoodif 32
#define clsgwid 11
#define clht 13

//��ɫ
#define defaultColor 0,7
#define black 0,0
#define milkWhite 7,0
#define colorBoard  { {1,0},{ 13,0} ,{11,0} ,{8,0} ,{14,0} ,{6,0} ,{2,0} ,{4,0} ,{ 10,0} ,{15,0} }
#define columnColor milkWhite
#define background black

#define prolong Sleep(75);
//��ӡ���Ӻ��ƶ����ӵ���ʱ
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
