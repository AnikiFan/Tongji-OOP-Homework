/* 2254298 ���� ������ */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <stdio.h>  
#include <stdlib.h>  
#include <conio.h>  
#include <math.h>
#include <time.h>
using namespace std;
#include"../../BigHW/include/cmd_console_tools.h"
void hdc_init(const int bgcolor, const int fgcolor, const int width, const int high);
void thdc_init(const int bgcolor = COLOR_BLACK, const int fgcolor = COLOR_WHITE, const int width = 8 * 120, const int high = 16 * 30);
void hdc_arc(const int point_x, const int point_y, const int radius, const int angle_begin, const int angle_end, const int thickness, const int RGB_value);
void thdc_arc(const int point_x, const int point_y, const int radius, const int angle_begin, const int angle_end, const int thickness, const int RGB_value);
int main()
{
	const int   win_width = 800, win_high = 800;	//�趨��Ļ���
	const int   win_bgcolor = COLOR_WHITE, win_fgcolor = COLOR_HRED;
	const int   color[] = { 0x00FF0000, 0x0000FF00, 0x000000FF }; //R G B
	const int   STL_X = 0, STL_Y = win_high / 16 - 5;	//״̬�е���ʼ����
	const char* fill_str[] = { "����", "ʵ��" };

	char test_choise[1024] = "111111111111";
	char tmp[80];
	int i, round;
	int delay_ms = 0; //��ʼΪ����ʱ
	long t_end, t_start = GetTickCount(); //ȡ��ǰϵͳʱ�䣬��λ���룬����55ms

	srand((unsigned int)time(0));

	hdc_init(win_bgcolor, win_fgcolor, win_width, win_high);		//��(����ɫ��ǰ��ɫ����ȣ��߶ȣ���ʼ������

	//hdc_arc(400, 400, 200, -45, 45, 100, 0x000000FF);
	thdc_arc(400, 400, 200, 145, 225, 2, 0x000000FF);
	/* ������ʱʱ����ʱ��0��ʾ����ʱ����λms */
	return 0;

}
