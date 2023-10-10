/* 2254298 ���� ������ */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include "../include/cmd_hdc_tools.h"
using namespace std;

#if !HDC_SERIES_BY_TEACHER	//δ���������²Ŵ���������

/* ���������Ҫ��ͷ�ļ� */

extern "C" WINBASEAPI HWND WINAPI GetConsoleWindow(); //VS�д˴����в����ߣ���Ӱ������ʹ��

/* �Ѷ���ľ�̬ȫ�ֱ��� */
static HWND hWnd = GetConsoleWindow();
static HDC hdc = NULL;
static const double PI = 3.14159;
static int _BgColor_, _FgColor_, _Width_, _High;
static int _Delay_ms;

/* �����ʶ�ʹ�þ�̬ȫ�ֱ�����������static�����ⲿ���ɼ� */
/* �˴���������Զ��庯����������static�����ⲿ���ɼ� */
/***************************************************************************
  �������ƣ�from_system_to_custom
  ��    �ܣ�
  ���������DIRECTION 1 ˳ʱ�� -1 ��ʱ��
			INIT_ANGLE Ϊ��ʱ��ϵͳ����ϵ���Զ�������ϵ�غ�
  �� �� ֵ��
  ˵    ����SYTEM_ANGLE ָ�����·�,˳ʱ��
***************************************************************************/
static int from_custom_to_system(const int ANGLE, const int INIT_ANGLE = 0, const int DIRECTION = 1)
{
	const int SYSTEM_ANGLE = 0;
	return (SYSTEM_ANGLE + INIT_ANGLE + DIRECTION * ANGLE) ;
}
/***************************************************************************
  �������ƣ�area
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
static double area(const int x1,const int y1, const int x2, const int y2, const int x3, const int y3)
{
	return abs((x1*y2+x2*y3+x3*y1-x1*y3-x2*y1-x3*y2)/2.0);
}
/***************************************************************************
  ��������largest
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
/***************************************************************************/
static int largest(int a, int b, int c)
{
	int max = a;
	if (b > max)
		max = b;
	if (c > max)
		max = c;
	return max;
}
/***************************************************************************
  ��������smallest
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
/***************************************************************************/
static int smallest(int a, int b, int c)
{
	int smallest = a;
	if (b < smallest)
		smallest = b;
	if (c < smallest)
		smallest = c;
	return smallest;
}
/* ��������˼�����������������ʵ�֣���Ҫ�Ķ� */
/***************************************************************************
  �������ƣ�
  ��    �ܣ���ʼ��
  ���������const int bgcolor������ɫ
			const int fgcolor��ǰ��ɫ
			const int width  ����Ļ��ȣ�����
			const int high   ����Ļ�߶ȣ�����
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void hdc_init(const int bgcolor, const int fgcolor, const int width, const int high)
{
	/* ���ͷţ���ֹ��release���ٴ�init��hdc_release�����룩 */
	hdc_release();

	/* ����init����һ����̬ȫ������¼������hdc_cls()���õ� */
	_BgColor_ = bgcolor;
	_FgColor_ = fgcolor;
	_Width_ = width;
	_High = high;

	hdc = GetDC(hWnd);

	cct_setcursor(CURSOR_INVISIBLE);
	cct_setcolor(bgcolor, fgcolor);
	cct_setfontsize("��������", 16);
	cct_setconsoleborder(width / 8 + !!(width % 8), high / 16 + !!(high % 16)); //������Ŀ�ȼ��߶�ת��Ϊ�ض��������������!!�ĺ��壺�������8/16�ı��������ж�+1
	cct_cls();
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ��ͷŻ�ͼ��Դ
  ���������
  �� �� ֵ��
  ˵    ����������
***************************************************************************/
void hdc_release()
{
	if (hdc) {
		ReleaseDC(hWnd, hdc);
		hdc = NULL;
		cct_setcursor(CURSOR_VISIBLE_NORMAL);
	}
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void hdc_set_delay(int ms)
{
	if (ms > 0)
		_Delay_ms = ms;
	else
		_Delay_ms = 0;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ����û�����ɫ������RGBֵ
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void hdc_set_pencolor(const int RGB_value)
{
	SelectObject(hdc, GetStockObject(DC_PEN));
	SetDCPenColor(hdc, RGB_value);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ����û�����ɫ������RGB��ɫ��ֵ0-255
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void hdc_set_pencolor(const unsigned char red, const unsigned char green, const unsigned char blue)
{
	hdc_set_pencolor(RGB(red, green, blue));
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ������Ļ�����е�ͼ��
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void hdc_cls()
{
	/* ����һ��Ҫ��һ����ɫ��ʼ������������ص㣬�ҵ�����㷽����ͬѧ����֪ͨ�� */
	hdc_init(_BgColor_, (_FgColor_ + 1) % 16, _Width_, _High);

	hdc_init(_BgColor_, _FgColor_, _Width_, _High);

	/* ���ֻ���������demoʱ�������hdc_cls()���һ������ȱ�ߵ����������ʱ����
	   ������ֻ������л������⣬���ߴ���ʱֵ */
	Sleep(30);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���(x,y)λ�ô���ָ����ɫ����һ�����ص�
  ���������const int x��x���꣬���Ͻ�Ϊ(0,0)
			const int y��y���꣬���Ͻ�Ϊ(0,0)
  �� �� ֵ��
  ˵    ������ɫֱ���õ�ǰ�趨�������ڵ��ô�ָ��
***************************************************************************/
static inline void hdc_base_point(const int x, const int y)
{
	MoveToEx(hdc, x - 1, y - 1, NULL);
	LineTo(hdc, x, y);
	if (_Delay_ms > 0)
		Sleep(_Delay_ms);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���(x1,y1)-(x2,y2)֮�仭��һ�����ص������
  ���������const int x1�����x���꣬���Ͻ�Ϊ(0,0)
			const int y1�����y���꣬���Ͻ�Ϊ(0,0)
			const int x2���յ�y���꣬���Ͻ�Ϊ(0,0)
			const int y2���յ�y���꣬���Ͻ�Ϊ(0,0)
  �� �� ֵ��
  ˵    ������ɫֱ���õ�ǰ�趨
***************************************************************************/
static inline void hdc_base_line(const int x1, const int y1, const int x2, const int y2)
{
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
	if (_Delay_ms > 0)
		Sleep(_Delay_ms);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���(x,y)λ�ô���ָ����ɫ��һ��ָ����ϸ�ĵ�(�û�ʵ��Բ��ģ��)
  ���������const int x			��x���꣬���Ͻ�Ϊ(0,0)
			const int y			��y���꣬���Ͻ�Ϊ(0,0)
			const int thickness	����Ĵ�ϸ������λ1�����޲���(�����ᵼ�²���ȫ���)����ȱʡֵ��
			const int RGB_value	�������ɫ����ȱʡֵ��
  �� �� ֵ��
  ˵    �����Ľ�����Ч��
***************************************************************************/
void hdc_point(const int x, const int y, const int thickness, const int RGB_value)
{
	int tn = thickness;
	if (tn < 1)
		tn = 1;		//��������
	/* ������ֱ�������ޣ����ǵ����޳���һ����С�ǣ�������Բ����λ��δʵ�� */

	const int tn_end = (tn <= 1) ? 1 : tn / 2;

	int angle, level;
	int old_x1 = INT_MAX, old_y1 = INT_MAX, x1, y1;
	int count = 0;

	if (RGB_value != INVALID_RGB)
		hdc_set_pencolor(RGB_value);

	/* �û�Բ�ķ�ʽģ��ֵ� */
	for (level = 1; level <= tn_end; level++) {
		for (angle = 0; angle <= 360; angle++) {
			/* ע�⣬ϵͳ�������ᣬ0����Բ�����·� */
			x1 = x + (int)(level * sin(angle * PI / 180));
			y1 = y - (int)(level * cos(angle * PI / 180));

			/* ���뾶��Сʱ���Ƕȱ仯��������int�͵�x1/y1�仯����˼��ж���䣬�����ظ���ͬһ���ص� */
			if (x1 != old_x1 || y1 != old_y1) {
				old_x1 = x1;
				old_y1 = y1;
				hdc_base_point(x1, y1);
				++count;
			}
		}
	}
#if 0
	/* �ſ���ע�ͣ����Կ���һ���ֵ����˼������ص���� */
	cct_gotoxy(0, 41);
	printf("count=%d           ", count);
	getchar();
#endif
}

/* -------------------------------------------------------------------------
	�������к�����ʵ�֣���������������׼�Ķ�
	1������Ҫ����ϵͳ�������й�ͼ�β����ĺ���
	2�����к�����ʵ�ֶ�����hdc_base_point/hdc_base_line���������
	3����һ�룬�ǲ������к�������Ҫ����������ʵ�ֹ��̣�Ӧ����ʵ����Щ������
	4�������ʵ������ӵĲ���
	5��ϵͳ�ĽǶ��뺯�������еĽǶȺ������180��
   ------------------------------------------------------------------------- */

   /***************************************************************************
	 �������ƣ�
	 ��    �ܣ����߶�
	 ���������const int x1		������x
			   const int y1		������y
			   const int x2		���յ��x
			   const int y2		���յ��y
			   const int thickness	���߶εĴ�ϸ����ȱʡֵ��
			   const int RGB_value	���߶ε���ɫ����ȱʡֵ��
	 �� �� ֵ��
	 ˵    ���������������û���hdc_point����ϣ��ٶ�����
					 Ҳ������hdc_base_point/hdc_base_line����ϣ��ٶȿ죩
   ***************************************************************************/
void hdc_line(const int x1, const int y1, const int x2, const int y2, const int thickness, const int RGB_value)
{
	if (RGB_value != INVALID_RGB)
		hdc_set_pencolor(RGB_value);
	int UPPER = 1 + thickness / 2 ;
	for (int rel_x = -UPPER; rel_x <= UPPER; rel_x++)
		for (int rel_y = -UPPER; rel_y <= UPPER; rel_y++)
			if (rel_x * rel_x + rel_y * rel_y <= UPPER * UPPER)
				hdc_base_line(x1 + rel_x, y1 + rel_y, x2 + rel_x, y2 + rel_y);
	return;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�������������꣬��һ��������
  ���������const int x1		����1�����x
			const int y1		����1�����y
			const int x2		����2�����x
			const int y2		����2�����y
			const int x3		����3�����x
			const int y3		����3�����y
			bool filled			���Ƿ���Ҫ��䣨��ȱʡֵ��
			const int thickness	���ߵĴ�ϸ����ȱʡֵ��
			const int RGB_value	����ɫ����ȱʡֵ��
  �� �� ֵ��
  ˵    �������ж������Ƿ��ߣ�������ߣ�����һ��ֱ�߼���
***************************************************************************/
void hdc_triangle(const int x1, const int y1, const int x2, const int y2, const int x3, const int y3, bool filled, const int thickness, const int RGB_value)
{
	if (RGB_value != INVALID_RGB)
		hdc_set_pencolor(RGB_value);
	hdc_line(x1,y1,x2,y2,thickness/2,RGB_value);
	hdc_line(x2,y2,x3,y3,thickness/2,RGB_value);
	hdc_line(x3,y3,x1,y1,thickness/2,RGB_value);
	if (filled) {
		int UPPER_X= largest(x1,x2,x3),LOWER_X=smallest(x1,x2,x3);
		int UPPER_Y= largest(y1,y2,y3),LOWER_Y=smallest(y1,y2,y3);
		const int  AREA = (int)area(x1,y1,x2,y2,x3,y3);
		for(int x = LOWER_X;x<=UPPER_X;x++)
			for(int y = LOWER_Y;y<=UPPER_Y;y++)
				if (AREA == (int)(area(x1, y1, x2, y2, x, y) + area(x1, y1, x3, y3, x, y) + area(x2, y2, x3, y3, x, y))||
					AREA == (int)(area(x1, y1, x2, y2, x, y) + area(x1, y1, x3, y3, x, y) + area(x2, y2, x3, y3, x, y))+1||
					AREA == (int)(area(x1, y1, x2, y2, x, y) + area(x1, y1, x3, y3, x, y) + area(x2, y2, x3, y3, x, y)) + 2||
					AREA == (int)(area(x1, y1, x2, y2, x, y) + area(x1, y1, x3, y3, x, y) + area(x2, y2, x3, y3, x, y)) +3 )
					hdc_base_point(x,y);
	}
	return;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ��������Ͻ����꼰��ȡ��߶ȣ�����һ��������
  ���������const int left_up_x			�����Ͻ�x
			const int left_up_y			�����Ͻ�y
			const int width				�����
			const int high				���߶�
			const int rotation_angles	�������Ͻ�Ϊ֧�㣬��x�����ת��ǣ�����תΪ����
			bool filled					���Ƿ���Ҫ��䣨��ȱʡֵ��
			const int thickness			���ߵĴ�ϸ����ȱʡֵ��
			const int RGB_value			����ɫ����ȱʡֵ��
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void hdc_rectangle(const int left_up_x, const int left_up_y, const int width, const int high, const int rotation_angles, const bool filled, const int thickness, const int RGB_value)
{
	const int angle = from_custom_to_system(rotation_angles, 270, 1);
	if (RGB_value != INVALID_RGB)
		hdc_set_pencolor(RGB_value);
	const int x1 = left_up_x,y1=left_up_y,x2=x1-(int)(width*sin(angle *PI/180)),y2=y1+(int)(width*cos(angle *PI/180));
	const int x3 = x2-(int)(high*sin((angle+90) *PI/180)),y3=y2+(int)(high*cos((angle+90) *PI/180));
	const int x4 = x1-(int)(high*sin((angle+90) *PI/180)),y4=y1+(int)(high*cos((angle+90) *PI/180));
	if (filled) {
		hdc_triangle(x1,y1,x2,y2,x3,y3,true,thickness,RGB_value);
		hdc_triangle(x1,y1,x3,y3,x4,y4,true,thickness,RGB_value);
	}
	else {
	hdc_line(x1,y1,x2,y2,thickness/2,RGB_value);
	hdc_line(x2,y2,x3,y3,thickness/2,RGB_value);
	hdc_line(x3,y3,x4,y4,thickness/2,RGB_value);
	hdc_line(x4,y4,x1,y1,thickness/2,RGB_value);
	}

}

/***************************************************************************
  �������ƣ�
  ��    �ܣ��������Ͻ����꼰�߳�������һ��������
  ���������const int left_up_x			�����Ͻ�x
			const int left_up_y			�����Ͻ�y
			const int length			���߳�
			const int rotation_angles	�������Ͻ�Ϊ֧�㣬��x�����ת��ǣ�����תΪ��������ȱʡֵ��
			const bool filled			���Ƿ���Ҫ��䣨��ȱʡֵ��
			const int thickness			���ߵĴ�ϸ����ȱʡֵ��
			const int RGB_value			����ɫ����ȱʡֵ��
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void hdc_square(const int left_up_x, const int left_up_y, const int length, const int rotation_angles, const bool filled, const int thickness, const int RGB_value)
{
	hdc_rectangle(left_up_x,left_up_y,length,length,rotation_angles,filled,thickness,RGB_value);
	return;
}
/***************************************************************************
  �������ƣ�
  ��    �ܣ����ո����Ĳ�����һ��Բ��
  ���������const int point_x		��Բ�ĵ�x
			const int point_y		��Բ�ĵ�y
			const int radius		���뾶
			const int angle_begin	����ʼ�Ƕȣ���Բ�����Ϸ�Ϊ0�㣬˳ʱ��Ϊ����ע�⣺��ϵͳ�������180��!!!������ȱʡֵ��
			const int angle_end		�������Ƕȣ�ͬ�ϣ�����ȱʡֵ��
			const int thickness		����ϸ����ȱʡֵ��
			const int RGB_value		����ɫ����ȱʡֵ��
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void hdc_arc(const int point_x, const int point_y, const int radius, const int angle_begin, const int angle_end, const int thickness, const int RGB_value)
{
	int begin = from_custom_to_system(angle_begin, 180, 1), end = from_custom_to_system(angle_end, 180, 1);
	if ((angle_begin - angle_end) % 360 == 0 || (angle_end - angle_begin >= 360)) {
		hdc_circle(point_x, point_y, radius, false,thickness, RGB_value);
		return;
	}
	while (end - begin < 0)
		end += 360;
	while (begin < 0) {
		begin += 360;
		end += 360;
	}
	while (begin >= 360) {
		begin -= 360;
		end -= 360;
	}
	if (RGB_value != INVALID_RGB)
		hdc_set_pencolor(RGB_value);
	int UPPER = radius + thickness / 2, LOWER = radius - thickness / 2;
	double begin_radian = begin * PI / 180, end_radian = end * PI / 180, radian_angle;
	for (int rel_x = -UPPER; rel_x <= UPPER; rel_x++)
		for (int rel_y = -UPPER; rel_y <= UPPER; rel_y++) {
			if (rel_x < 0)
				radian_angle = acos(((double)rel_y) / sqrt(rel_x * rel_x + rel_y * rel_y));
			else
				radian_angle = 2 * PI - acos(((double)rel_y) / sqrt(rel_x * rel_x + rel_y * rel_y));
			if (rel_x * rel_x + rel_y * rel_y <= UPPER * UPPER && rel_x * rel_x + rel_y * rel_y >= LOWER * LOWER &&
				((end <= 360 && radian_angle > begin_radian && radian_angle < end_radian) ||
					(end > 360 && (radian_angle > begin_radian || radian_angle < end_radian - 2 * PI))))
				hdc_base_point(point_x + rel_x, point_y + rel_y);
		}
	return;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ����ո����Ĳ�����һ������
  ���������const int point_x		��Բ�ĵ�x
			const int point_y		��Բ�ĵ�y
			const int radius		���뾶
			const int angle_begin	����ʼ�Ƕȣ���Բ�����Ϸ�Ϊ0�㣬˳ʱ��Ϊ����ע�⣺��ϵͳ�������180��!!!������ȱʡֵ��
			const int angle_end		�������Ƕȣ�ͬ�ϣ�����ȱʡֵ��
			const bool filled		���Ƿ���Ҫ��䣨��ȱʡֵ��
			const int thickness		����ϸ����ȱʡֵ��
			const int RGB_value		����ɫ����ȱʡֵ��
  ���������
  �� �� ֵ��
  ˵    ��������ʼ/�����ǶȲ�ֵΪ360�ı���ʱ������������
***************************************************************************/
void hdc_sector(const int point_x, const int point_y, const int radius, const int angle_begin, const int angle_end, const bool filled, const int thickness, const int RGB_value)
{
	int begin = from_custom_to_system(angle_begin, 180, 1),end = from_custom_to_system(angle_end,180,1);
	if ((angle_begin - angle_end) % 360 == 0||(angle_end-angle_begin>=360)) {
		hdc_circle(point_x,point_y,radius,filled,thickness,RGB_value);
		return;
	}
	while(end-begin<0)
         end += 360;
	while (begin < 0) {
		begin+=360;
		end += 360;
	}
	while (begin >= 360) {
		begin-=360;
		end -= 360;
	}
	if (RGB_value != INVALID_RGB)
		hdc_set_pencolor(RGB_value);
	int UPPER = radius+thickness/2,LOWER= filled ? 0 : radius - thickness/2;
	double begin_radian = begin  * PI / 180, end_radian = end  * PI / 180,radian_angle;
	for(int rel_x = -UPPER;rel_x<= UPPER;rel_x++)
		for (int rel_y = -UPPER; rel_y <= UPPER; rel_y++) {
			if (rel_x< 0)
				radian_angle = acos(((double)rel_y)/sqrt(rel_x*rel_x+rel_y*rel_y));
			else
				radian_angle =2* PI-acos(((double)rel_y) / sqrt(rel_x*rel_x+rel_y*rel_y));
			if(rel_x*rel_x+rel_y*rel_y<=UPPER*UPPER&&rel_x*rel_x+rel_y*rel_y>=LOWER*LOWER&&
				((end<=360&&radian_angle > begin_radian && radian_angle < end_radian)||
			(end>360&&	(radian_angle>begin_radian||radian_angle<end_radian-2*PI))	))
				hdc_base_point(point_x+rel_x,point_y+rel_y);
		}
	if (!filled) {
		hdc_line(point_x, point_y, point_x - (int)(radius * sin(begin_radian)), point_y + (int)(radius * cos(begin_radian)), thickness/2, RGB_value);
		hdc_line(point_x, point_y, point_x - (int)(radius * sin(end_radian)), point_y + (int)(radius * cos(end_radian)), thickness/2, RGB_value);
	}
	return;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ����ո����Ĳ�����һ��Բ
  ���������const int point_x		��Բ�ĵ�x
			const int point_y		��Բ�ĵ�y
			const int radius		���뾶
			const bool filled		���Ƿ���Ҫ��䣨��ȱʡֵ��
			const int thickness		����ϸ����ȱʡֵ��
			const int RGB_value		����ɫ����ȱʡֵ��
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void hdc_circle(const int point_x, const int point_y, const int radius, const bool filled, const int thickness, const int RGB_value)
{
	if (RGB_value != INVALID_RGB)
		hdc_set_pencolor(RGB_value);
	int UPPER = radius+thickness/2,LOWER= filled ? 0 : radius - thickness/2;
	for(int rel_x = -UPPER;rel_x<= UPPER;rel_x++)
		for(int rel_y =  -UPPER;rel_y<= UPPER;rel_y++)
			if(rel_x*rel_x+rel_y*rel_y<=UPPER*UPPER&&rel_x*rel_x+rel_y*rel_y>=LOWER*LOWER)
				hdc_base_point(point_x+rel_x,point_y+rel_y);
	return;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ����ո����Ĳ�����һ����Բ
  ���������const int point_x			��Բ�ĵ�x
			const int point_y			��Բ�ĵ�y
			const int radius_a			��ƽ����X��İ뾶
			const int radius_b			��ƽ����Y��İ뾶
			const int rotation_angles	����Բ��Ϊ֧�㣬��x�����ת��ǣ�����תΪ��������ȱʡֵ��
			const bool filled			���Ƿ���Ҫ��䣨��ȱʡֵ��
			const int thickness			����ϸ����ȱʡֵ��
			const int RGB_value			����ɫ����ȱʡֵ��
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void hdc_ellipse(const int point_x, const int point_y, const int radius_a, const int radius_b, const int rotation_angles, const bool filled, const int thickness, const int RGB_value)
{
	if (RGB_value != INVALID_RGB)
		hdc_set_pencolor(RGB_value);
	int BOUND;
	if(radius_a > radius_b)
		BOUND = radius_a+thickness/2;
	else
		BOUND = radius_b+thickness/2;
	const int UPPER_A = radius_a + thickness / 2, LOWER_A =  radius_a - thickness / 2;
	const int UPPER_B = radius_b + thickness / 2, LOWER_B =  radius_b - thickness / 2;
	double da, db;
	double radian_angles = rotation_angles * PI / 180;
	for(int rel_x = -BOUND;rel_x<= BOUND;rel_x++)
		for (int rel_y = -BOUND; rel_y <= BOUND; rel_y++) {
        	 da = cos(radian_angles)*rel_x+sin(radian_angles)*rel_y, db = -sin(radian_angles)*rel_x+cos(radian_angles)*rel_y;
					if (da * da / (UPPER_A * UPPER_A) + db * db / (UPPER_B* UPPER_B) <= 1 &&
						(filled|| da * da / (LOWER_A * LOWER_A) + db * db / (LOWER_B * LOWER_B) >= 1))
				hdc_base_point(point_x + rel_x, point_y + rel_y);
		}
	return;
}

#endif !HDC_SERIES_BY_TEACHER
