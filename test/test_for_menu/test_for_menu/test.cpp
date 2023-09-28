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
	cout << _getch() << endl;
	cout << _getch() << endl;
	cout << _getch() << endl;
	return 0;
}