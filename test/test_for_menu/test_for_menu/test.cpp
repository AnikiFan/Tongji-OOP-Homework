#include "../../../BigHW/include/cmd_console_tools.h"
#include"../../../BigHW/include/menu.h"
#include<iostream>
#include<conio.h>
#include<windows.h>
using namespace std;
int main()
{
	//make_colorblock(3, 3, 10, 10);
	//make_lattice(3, 3, 3, 3, 10, 10, '*');
	//make_frame(3, 3, 10, 10);
	//make_board(3, 3, 4, 3, 1, 1, true);
	//cct_gotoxy(40, 40);
	struct num {
		int a;
		int b;
	};
	struct	num test[2] = { {1,2},{1,2} };
	//cout << GetTickCount() << endl;
	//Sleep(10000);
	//cout << GetTickCount() << endl;
	//cout << GetTickCount() << endl;
	//cout << GetTickCount() << endl;
	//for (int i = 20; i < 50; i++) {
		//cct_setfontsize("ÐÂËÎÌå", i);
		//cout << i*100000 << endl;
		//Sleep(2000);
	//}
	cct_setconsoleborder(100, 100, 100, 100);
	for (int i = 0; i < 100; i++)
		cout << i << endl;
	return 0;
}