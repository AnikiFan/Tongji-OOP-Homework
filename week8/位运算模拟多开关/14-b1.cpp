/* 2254298 大数据 范潇 */
#include<iostream>
#include<iomanip>
using namespace std;
#define ALPHA cout<<"A   B   C   D   E   F   G   H   I   J"<<endl;
#define INPUTSIZE 100
void show(short light);
int main()
{
	short  light = 0;
	char opt[INPUTSIZE]="";
	char input;
	cout << "初始状态：0x0000" << endl;
	ALPHA
		for (int i = 0; i < 10; i++)
			cout << "OFF ";
	cout << endl<<endl;
	while (1) {
		if (opt[0] == 'Q' || opt[0] == 'q')
			return 0;
		cout << "请以(\"A On / J Off\"形式输入，输入\"Q on / off\"退出)" << endl;
		cin >> opt;
		if (strlen(opt) != 1 || !((opt[0] >= 'a' && opt[0] <= 'j') || (opt[0] >= 'A' && opt[0] <= 'J')))
			continue;
		else {
			if (opt[0] >= 'A' && opt[0] <= 'J')
				input = opt[0] + 'a' - 'A';
			else
				input = opt[0];
			cin >> opt;
			if (strlen(opt) > 3)
				continue;
			for (int i = 0; i < (int)strlen(opt); i++)
				if (opt[i] >= 'A' && opt[i] <= 'Z')
					opt[i] = opt[i] + 'a' - 'A';
			if (!strcmp("on", (const char*)opt)) {
				light |= (short)(1 << (input - 'a'));
				show(light);
			}
			else if (!strcmp("off", (const char*)opt)) {
				light &= (short)~(1 << (input - 'a'));
				show(light);
			}
		}
	}
	return 0;
}
void show(short light) {
	cout << "当前状态：0x"<<hex<<setfill('0')<<setw(4) << light << dec << endl;
	ALPHA;
	for (int i = 0; i < 10 ; i++)
		if ((light >> i) % 2)
			cout << "ON  ";
		else
			cout << "OFF ";
	cout << endl << endl;
	return;
}