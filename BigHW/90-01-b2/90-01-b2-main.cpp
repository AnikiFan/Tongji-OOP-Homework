/* 2254298 大数据 范潇 */
#include"90-01-b2.h"
#include"../include/menu.h"
int main()
{
	char option;
	int rowMax, colMax, matrix[10][10], i, j;
	cct_setconsoleborder(boardwidth, boardheight, boardwidth, boardheight);
	cct_setfontsize("点阵字体", 15);
	const	char* menu_list[] = { "命令行找出可消除项并标识","命令行完成一次消除(分步骤显示)","命令行完成一关(分步骤显示)",
	"伪图形界面下用鼠标选择一个色块(无分隔线)","伪图形界面下用鼠标选择一个色块(有分隔线)","伪图形界面完成一次消除(分步骤)","伪图形界面完整版" },
		* quit_key = "Q";
	srand((unsigned int)(time(0)));
	while (1) {
		for (i = 0; i < 10; i++)
			for (j = 0; j < 10; j++)
				matrix[i][j] = (rand() % 5) + 1;
		//matrix[i][j] =  1;
		//测试用
		//for (i = 0; i < 10; i++)
		//	for (j = 0; j < 10; j++)
		//		matrix[i][j] = j;
		//
		//int temp = menu(menu_list,7,quit_key,true);

		//cout << temp;
		//return 0;
		option = 'a'+menu(menu_list,7,quit_key,true)-1;
		cct_setfontsize("点阵字体", 20);

		if (option == 'a'-1)
			break;
		else {
			cct_cls();
			cout << "请输入行数(8-10)：" << endl;
			while (1) {
				cin >> rowMax;
				if (rowMax >= 8 && rowMax <= 10 && !cin.rdstate())
					break;
				else if (cin.rdstate()) {
					cin.clear();
					cin.ignore(10000000, '\n');//删了这个以后会死循环
				}
				cout << "请输入行数(8-10)：" << endl;
			}
			cout << "请输入列数(8-10)：" << endl;
			while (1) {
				cin >> colMax;
				if (colMax >= 8 && colMax <= 10 && !cin.rdstate())
					break;
				else if (cin.rdstate()) {
					cin.clear();
					cin.ignore(10000000, '\n');//删了这个以后会死循环
				}
				cout << "请输入列数(8-10)：" << endl;
			}
		}

		switch (option) {
			case 'a':
				module1(rowMax, colMax, matrix);
				break;
			case 'b':
				module2(rowMax, colMax, matrix);
				break;
			case 'c':
				module3(rowMax, colMax, matrix);
				break;
			case 'd':
				module4(rowMax, colMax, matrix);
				break;
			case 'e':
				module5(rowMax, colMax, matrix);
				break;
			case 'f':
				module6(rowMax, colMax, matrix);
				break;
			case 'g':
				module7(rowMax, colMax, matrix);
				break;
		}
		reload();
	}
	return 0;
}