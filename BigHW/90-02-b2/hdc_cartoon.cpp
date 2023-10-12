/* 2254298 范潇 大数据 */
#include "../include/cmd_hdc_tools.h"
#include <iostream>
#include <Windows.h>
using namespace std;
#define WIN_WIDTH 800
#define WIN_HIGH 800
#define PI 3.1415926

#define CAT_COLOR RGB(1,205,238)
#define STRIP_COLOR RGB(0,168,195)
#define EYE_COLOR RGB(0,0,0)
#define MOUTH_COLOR RGB(254,103,110)
#define BELLY_COLOR RGB(255,255,255)
#define EYE_WHITE_COLOR RGB(255,255,255)
#define SIDE_COLOR RGB(0,0,0)
#define SIDE_WIDTH 10
//绘制彩色圆圈，集中在上方
static void make_bubble(const int center_x,const int center_y)
{
	int radius, color;
	const int color_list[9] = {
		RGB(50,75,105),
		RGB(88,74,108),
		RGB(76,70,106),
		RGB(51,102,105),
		RGB(116,89,120),
		RGB(138,125,142),
		RGB(106,83,112),
		RGB(81,129,117),
		(112,116,94)
	};
	for(int i=0;i<20;i++){
		 color = color_list[rand() % 9];
			hdc_set_pencolor(color);
		 radius = rand() % 100;
			hdc_circle((1-2*(i%2))*rand() %( WIN_WIDTH/2)+center_x,- rand() % center_y+center_y, radius, true, 1, color);
	}
	return;
}
//绘制白色线条，从中心辐射
static void make_line(const int center_x, const int center_y)
{
	int length, angle,width,light;
	for (int i = 0; i < 10; i++) {
		angle = rand() % 135*(1-2*(i%2)) + 180;
		length = rand() % 400+300;
		width = rand() % 5 + 1;
		light = rand() % 125 + 125;
		hdc_line(center_x,center_y,center_x-(int)(sin(angle*PI/180)*length),center_y+(int)(cos(angle*PI/180)*length),width,RGB(light,light,light));
	}
	return ;
}
//绘制白色圆点
static void make_dot(const int center_x, const int center_y)
{
		int radius,light;
	for (int i = 0; i < 20; i++) {
		light = rand() % 100 + 150;
		radius = rand() % 10 + 5;
		hdc_point((1 - 2 * (i % 2)) * rand() % (WIN_WIDTH / 2) + center_x, -rand() % center_y + center_y, radius, RGB(light, light, light));
	}
	return;
}
//绘制猫头轮廓
static void body(int center_x,int center_y)
{
	//画左耳朵
	hdc_ellipse(center_x - 170, center_y+20, 200, 100, -103, true, 0, CAT_COLOR);
	hdc_ellipse(center_x - 170, center_y+20, 200, 100, -103, false, SIDE_WIDTH, SIDE_COLOR);
	//画右耳朵
	hdc_ellipse(center_x +80, center_y-25, 200, 125, -70, true, 0, CAT_COLOR);
	hdc_ellipse(center_x +80, center_y-25, 200, 125, -70, false, SIDE_WIDTH, SIDE_COLOR);

	//画身体
	hdc_rectangle(center_x -272, center_y +25, 525, WIN_HIGH-center_y+40, -1, true, 0, CAT_COLOR);
	hdc_rectangle(center_x -272, center_y +25, 525, WIN_HIGH-center_y+40, -1, false, SIDE_WIDTH-1, SIDE_COLOR);
	//画脸
	hdc_ellipse(center_x, center_y, 275, 150, -10, true, 0, CAT_COLOR);
	hdc_ellipse(center_x, center_y, 275, 150, -10, false, SIDE_WIDTH, SIDE_COLOR);
	//去除下巴
	hdc_rectangle(center_x -272+SIDE_WIDTH/2, center_y +25, 525-SIDE_WIDTH,140, -1, true, 0, CAT_COLOR);
	//画斑点
	hdc_sector(center_x - 272+SIDE_WIDTH/2, center_y + 100, 25, -1, 179,true, 0, STRIP_COLOR);
	hdc_sector(center_x - 272+SIDE_WIDTH-1, center_y + 200, 25, -1, 179,true, 0, STRIP_COLOR);
	//画肚子
	hdc_ellipse(center_x,center_y+250,125,80,-10,true,0,BELLY_COLOR);
	//画左手
	hdc_ellipse(center_x-110,center_y+110,50,120,-20,true,0,CAT_COLOR);
	hdc_ellipse(center_x-110,center_y+110,50,120,-20,false,SIDE_WIDTH,SIDE_COLOR);
	//去掉多余部分
	hdc_rectangle(center_x-200,center_y-50,50*2+2*SIDE_WIDTH+50,200,-1,true,0,CAT_COLOR);
//画右手
	hdc_ellipse(center_x+110,center_y+90,45,120,5,true,0,CAT_COLOR);
	hdc_ellipse(center_x+110,center_y+90,45,120,5,false,SIDE_WIDTH,SIDE_COLOR);
	//去掉多余部分
	hdc_rectangle(center_x,center_y-50,50*2+2*SIDE_WIDTH+50,200,-5,true,0,CAT_COLOR);
	//画嘴
	hdc_ellipse(center_x, center_y, 60, 50, -10, true, 0, MOUTH_COLOR);
	hdc_ellipse(center_x, center_y, 60, 50, -10, false, SIDE_WIDTH, SIDE_COLOR);
	//画左嘴唇
	hdc_sector(center_x-75,center_y-100 , 100,  125,183, true, 0, CAT_COLOR);
	hdc_arc(center_x - 75, center_y-100 , 100, 125, 183, SIDE_WIDTH, SIDE_COLOR);
	//画右嘴唇
	hdc_sector(center_x +50, center_y - 100, 80, 160, 220, true, 0, CAT_COLOR);
	hdc_arc(center_x +50, center_y - 100,80,  160,220, SIDE_WIDTH, SIDE_COLOR);
	//去掉多余部分
	hdc_square(center_x - 25, center_y - 100, 55, 0, true, 0, CAT_COLOR);
	//画左眼
	hdc_ellipse(center_x-150, center_y-20, 55, 50, -50, true, 0, EYE_WHITE_COLOR);
	hdc_ellipse(center_x - 150, center_y - 20, 55, 50, -50, false, SIDE_WIDTH, SIDE_COLOR);
	//画左眼珠
	hdc_ellipse(center_x - 160, center_y - 25, 36, 30, -70, true, 0,SIDE_COLOR);
	//画右眼
	hdc_ellipse(center_x +150, center_y -55, 55, 50, -60, true, 0, EYE_WHITE_COLOR);
	hdc_ellipse(center_x + 150, center_y - 55, 55, 50, -60, false, SIDE_WIDTH, SIDE_COLOR);
	//画右眼珠
	hdc_ellipse(center_x + 160, center_y - 60, 36, 30, -80, true, 0, SIDE_COLOR);
	return;
}
void hdc_draw_cartoon_2254298(const int base_x,const int base_y)
{
	const int center_x = base_x,center_y = base_y+150;
	hdc_cls();
	hdc_init(8, 7, 800, 800);
	make_bubble(center_x, center_y);
	make_line(center_x, center_y);
	make_dot(center_x, center_y);
	body(center_x, center_y);
return;
}

