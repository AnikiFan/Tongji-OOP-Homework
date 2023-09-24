#include "../../../BigHW/include/cmd_console_tools.h"
#include"../../../BigHW/include/menu.h"
#include<iostream>
using namespace std;
int main()
{
	//make_colorblock(3, 3, 10, 10);
	//make_lattice(3, 3, 3, 3, 10, 10, '*');
	//make_frame(3, 3, 10, 10);
	make_board(3, 3, 4, 3, 3, 3, true);
	cct_gotoxy(40, 40);
	return 0;
}