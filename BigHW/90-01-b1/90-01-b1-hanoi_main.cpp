/* 2254298 大数据 范潇 */

/* ----------------------------------------------------------------------------------

	 本文件功能：
	1、放main函数
	2、初始化屏幕
	3、调用菜单函数（hanoi_menu.cpp中）并返回选项
	4、根据选项调用菜单各项对应的执行函数（hanoi_multiple_solutions.cpp中）

	 本文件要求：
	1、不允许定义全局变量（含外部全局和静态全局，const及#define不在限制范围内）
	2、静态局部变量的数量不限制，但使用准则也是：少用、慎用、能不用尽量不用
	3、按需加入系统头文件、自定义头文件、命名空间等

   ----------------------------------------------------------------------------------- */
   //TODO:下列内容允许使用全局变量记录，其余均不允许（全局 const 变量/#define 宏定义的 数量不受限制，任意使用）
   //TODO:总移动步数 ：1个全局简单变量;圆柱上现有圆盘的编号：3个全局一维数组或 1 个全局二维数组;圆柱上现有圆盘的数量：3个全局简单变量或 1 个全局一维数组;延时 ：1个全局简单变量

#include"90-01-b1-hanoi.h"
#include"../include/menu.h"

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int main()
{
	char inputnumber, dst, src, tmp;
	const	char* menu_list[] = {
		"基本解",
		"基本解(步数记录)",
		"内部数组显示(横向)",
		"内部数组显示(纵向+横向)",
		"图形解-预备-画三个圆柱",
		"图形解-预备-在起始柱上画n个盘子",
		"图形解-预备-第一次移动",
		"图形解-自动移动版本",
		"图形解-游戏版"
	};
	int level;
	/* demo中首先执行此句，将cmd窗口设置为40行x120列（缓冲区宽度120列，行数9000行，即cmd窗口右侧带有垂直滚动杆）*/

	while (1) {
		inputnumber = '0'+menu(menu_list, 9, "0");
	cct_setconsoleborder(120, 40, 120, 9000);
		//cout <<(int)inputnumber << endl;
		//return 0;


		if (inputnumber == '0')
			break;
		if (inputnumber != '5') {
			initializevariable(inputnumber, &src, &dst, &tmp, &level);
			switch (inputnumber) {
				case '1':
					hanoi(level, src, tmp, dst, '1');
					break;
				case '2':
					hanoi(level, src, tmp, dst, '2');
					break;
				case '3':
					hanoi(level, src, tmp, dst, '3');
					break;
				case '4':
					module4(src, dst, tmp, level);
					break;
				case '6':
					module6(src, dst, tmp, level);
					break;
				case '7':
					module7(src, dst, tmp, level);
					break;
				case '8':
					module8(src, dst, tmp, level);
					break;
				case '9':
					module9(src, dst, tmp, level);
					break;
			}
		}
		else {
			cct_cls();
			column();
		}
		reload();
	}
	return 0;
}
