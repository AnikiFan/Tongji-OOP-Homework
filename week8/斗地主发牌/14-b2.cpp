/* 2254298 大数据 范潇 */
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <time.h>
/* 如果有需要，此处可以添加头文件 */

using namespace std;

/* 允许定义常变量/宏定义，但不允许定义全局变量 */

/* 可以添加自己需要的函数 */
//deck中为1说明已经发走，player中为1说明有
void addnew(unsigned long long& deck, unsigned long long& player)
{
	while (1) {
		int pos = rand() % 54;
		if ((deck >> pos) % 2)
			continue;
		deck |= (1ULL << pos);
		player |= (1ULL << pos);
		break;
	}
	return;
}
void showcard(int i) {
			if (i == 53)
				cout << "RJ ";
			else if (i == 52)
				cout << "BJ ";
			else {
				int suit = i % 4;
				int pt = i / 4;
#if (__Linux__)
				switch (suit) {
					case 0: 
						cout << "C";
						break;
					case 1:
						cout << "D";
						break;
					case 2:
						cout << "H";
						break;
					case 3:
						cout << "S";
						break;
				}
#else
				switch (suit) {
					case 0:
						cout << '\5';
						break;
					case 1:
						cout << '\4';
						break;
					case 2:
						cout << '\3';
						break;
					case 3:
						cout << '\6';
						break;
				}
#endif
				switch (pt) {
					case 11:
						cout << "A";
						break;
					case 7:
						cout << "T";
						break;
					default:
						cout << pt+3;
						break;
					case 8:
						cout << "J";
						break;
					case 9:
						cout << "Q";
						break;
					case 10:
						cout << "K";
						break;
					case 12:
						cout << 2;
						break;
				}
				cout << ' ';
			}
	return;
}
void display(unsigned long long player)
{
	for(int i = 0;i<54;i++)
		if ((player >> i) % 2) 
			showcard(i);
	return;
}
/***************************************************************************
  函数名称：
  功    能：打印某个玩家的牌面信息，如果是地主，后面加标记
  输入参数：
  返 回 值：
  说    明：
 ***************************************************************************/
int print(const char* prompt, const bool landlord, const unsigned long long player)
{
	/* 只允许定义不超过三个基本类型的简单变量，不能定义数组变量、结构体、string等 */
	cout << prompt;
	display(player);
	if (landlord)
		cout << "(地主)";
	cout << endl;
	return 0;
}

/***************************************************************************
  函数名称：
  功    能：发牌（含键盘输入地主）
  输入参数：
  返 回 值：
  说    明：
 ***************************************************************************/
int deal(unsigned long long* player)
{
	/* 只允许定义不超过十个基本类型的简单变量，不能定义数组变量、结构体、string等 */
	int landlord;
	srand((unsigned)time(0));
	unsigned long long deck = 0;
	for (int i = 1; i <= 17; i++) {
		cout << "第" << i << "轮结束：" << endl;
		cout << "甲的牌：";
		addnew(deck, player[0]);
		display(player[0]);
		cout << endl<<"乙的牌：";
		addnew(deck, player[1]);
		display(player[1]);
		cout <<endl<< "丙的牌：";
		addnew(deck, player[2]);
		display(player[2]);
		cout << endl;
		cout << endl;
	}
		cout << "请选择一个地主[0-2]："<<endl;
		cin >> landlord;
		for (int pos = 0; pos < 54; pos++) {
			if ((deck >> pos) % 2)
				continue;
			deck |= (1ULL << pos);
			player[landlord] |= (1ULL << pos);
		}
	return landlord; //此处修改为选定的地主(0-2)
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：main函数，不准修改
 ***************************************************************************/
int main()
{
	unsigned long long player[3] = { 0 }; //存放三个玩家的发牌信息
	int landlord; //返回0-2表示哪个玩家是地主

	cout << "按回车键开始发牌";
	while (getchar() != '\n')
		;

	landlord = deal(player);
	print("甲的牌：", (landlord == 0), player[0]);
	print("乙的牌：", (landlord == 1), player[1]);
	print("丙的牌：", (landlord == 2), player[2]);

	return 0;
}
