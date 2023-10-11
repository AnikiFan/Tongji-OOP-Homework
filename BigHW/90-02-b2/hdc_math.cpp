/* 2254298 范潇 大数据 */
#include "../include/cmd_hdc_tools.h"
#include <iostream>
#include <Windows.h>
using namespace std;
//黎曼函数中分母的最大值
const int N = 500;
//点的起始大小
const int  POINT_THICKNESS= 1;
//变化率点大小随y值的变化率
const double CHANGE_RATE = 0.1;
//坐标轴的宽度
const int AXIS_WIDTH = 1;
//点颜色第一分量的起始大小(y=0时),y以像素点为单位
const int R = 0;
//点颜色第二分量的起始大小
const int G = 0;
//点颜色第三分量的起始大小
const int B = 0;
//点颜色第一分量的变化率
const double R_CHANGE_RATE = 100;
//点颜色第二分量的变化率
const double G_CHANGE_RATE = 30;
//点颜色第三分量的变化率
const double B_CHANGE_RATE = 80;

#define PI 3.1415926
#define BOARD_SIZE 800
#define INTERVAL 100
#define OX INTERVAL
#define OY (BOARD_SIZE-INTERVAL)
#define AXIS_LENGTH (BOARD_SIZE-2*INTERVAL)
#define NEG_LENGTH (INTERVAL/2)
#define AXIS_COLOR RGB(0,0,0)
#define ARROW_LENGTH 10
#define ARROW_WIDTH AXIS_WIDTH
#define O_X (OX-NEG_LENGTH/2)
#define O_Y (OY+NEG_LENGTH/2)
#define O_RADIUS (NEG_LENGTH/4)
#define O_RADIUS_DIFF (O_RADIUS/3)
#define O_THICKNESS (AXIS_WIDTH*2)
#define O_ANGLE 15
#define X_X (OX+AXIS_LENGTH+NEG_LENGTH/2)
#define X_Y (OY+NEG_LENGTH/2)
#define X_HEIGHT (NEG_LENGTH/2)
#define X_THICKNESS AXIS_WIDTH
#define X_ANGLE 30
#define Y_X (OX-NEG_LENGTH/2)
#define Y_Y (OY-AXIS_LENGTH-NEG_LENGTH/2)
#define Y_HEIGHT (NEG_LENGTH/2)
#define Y_THICKNESS AXIS_WIDTH
#define Y_ANGLE 30
#define ONE_X (OX+AXIS_LENGTH-100)
#define ONE_Y (OY+NEG_LENGTH/2)
#define ONE_HEIGHT (NEG_LENGTH/2)
#define ONE_THICKNESS AXIS_WIDTH
#define ONE_METER (ONE_X-OX)
static void make_axis()
{
	hdc_line(OX-NEG_LENGTH, OY, OX + AXIS_LENGTH, OY, AXIS_WIDTH, AXIS_COLOR);
	hdc_line(OX, OY+NEG_LENGTH, OX, OY - AXIS_LENGTH, AXIS_WIDTH, AXIS_COLOR);
	hdc_line(OX + AXIS_LENGTH, OY, OX + AXIS_LENGTH - ARROW_LENGTH, OY - ARROW_WIDTH, AXIS_WIDTH, AXIS_COLOR);
	hdc_line(OX + AXIS_LENGTH, OY, OX + AXIS_LENGTH - ARROW_LENGTH, OY + ARROW_WIDTH, AXIS_WIDTH, AXIS_COLOR);
	hdc_line(OX, OY - AXIS_LENGTH, OX - ARROW_WIDTH, OY - AXIS_LENGTH + ARROW_LENGTH, AXIS_WIDTH, AXIS_COLOR);
	hdc_line(OX, OY - AXIS_LENGTH, OX + ARROW_WIDTH, OY - AXIS_LENGTH + ARROW_LENGTH, AXIS_WIDTH, AXIS_COLOR);
	hdc_ellipse(O_X, O_Y, O_RADIUS-O_RADIUS_DIFF, O_RADIUS+O_RADIUS_DIFF, O_ANGLE, 0, O_THICKNESS, AXIS_COLOR);
	hdc_line((int)(X_X-tan((45-X_ANGLE)*PI/180)*X_HEIGHT/2),X_Y-X_HEIGHT/2,(int) (X_X + tan((45 - X_ANGLE) * PI / 180) * X_HEIGHT / 2), X_Y + X_HEIGHT / 2, X_THICKNESS, AXIS_COLOR);
	hdc_line((int)(X_X-tan((45-X_ANGLE/2)*PI/180)*X_HEIGHT/2),X_Y+X_HEIGHT/2,(int)(X_X+tan((45-X_ANGLE/2)*PI/180)*X_HEIGHT/2),X_Y-X_HEIGHT/2,X_THICKNESS,AXIS_COLOR);
	hdc_line(Y_X,Y_Y,Y_X-(int)(Y_HEIGHT*(tan((Y_ANGLE*PI/2/180)/2))),Y_Y+Y_HEIGHT/2,Y_THICKNESS,AXIS_COLOR);
	hdc_line(Y_X,Y_Y,Y_X+(int)(Y_HEIGHT*(tan((45+Y_ANGLE/2)*PI/2/180))),Y_Y-Y_HEIGHT/2,Y_THICKNESS,AXIS_COLOR);
	hdc_line(Y_X,Y_Y,Y_X-(int)(Y_HEIGHT*(tan((45-Y_ANGLE)*PI/2/180))),Y_Y-Y_HEIGHT/2,Y_THICKNESS,AXIS_COLOR);
	hdc_line(ONE_X,ONE_Y+ONE_HEIGHT/2,ONE_X,ONE_Y-ONE_HEIGHT/2,ONE_THICKNESS,AXIS_COLOR);
	return;
}

static void make_point()
{
	hdc_point(OX, OY, POINT_THICKNESS, RGB(R,G,B));
	hdc_point(OX+ONE_METER, OY, POINT_THICKNESS, RGB(R,G,B));
	for (int i = 2; i <= N; i++) 
		for(int j = 1;j<i;j++)
			hdc_point(OX + (int)(ONE_METER * j / i), OY - (int)(ONE_METER   / i),(int) (POINT_THICKNESS+(ONE_METER*CHANGE_RATE/ i)), 
				RGB((int)(R+(ONE_METER*R_CHANGE_RATE/ i))%256,(int)(G+(ONE_METER*G_CHANGE_RATE/ i))%256,(int)(B+(ONE_METER*B_CHANGE_RATE/ i))%256  ));
	return;
}
void hdc_draw_Mathematical_curve_2254298()
{//画一个黎曼函数
	hdc_cls();
	hdc_init(COLOR_WHITE,COLOR_BLACK, 800, 800);
	make_axis();
	make_point();
	return;
}