#include<iostream>
using namespace std;
int main()
{
	if (0) {
		char ch[10]="123456789";
		ch[10] = 'a';    //此句越界
		ch[14] = 'A';    //此句越界
		ch[15] = 'B';    //此句越界
		ch[10] = '\xcc'; //此句越界
		cout << "addr:" << hex << (void*)(ch) << endl;
		for (int i = -4; i < 16; i++) //注意，只有0-9是合理范围，其余都是越界读
			cout <<dec<< "ch["<< i <<"] :" << hex << (void*)(ch + i)
			<< ":" << int(ch[i]) << endl;
	}
	if (1) {
		int integer[10]={1,2,3,4,5,6,7,8,9,10};
		integer[10] = 11;    //此句越界
		integer[14] = 12;    //此句越界
		integer[15] = 13;    //此句越界
		integer[10] = 0xcccccccc; //此句越界
		cout << "addr:" << hex << (void*)(integer) << endl;
		for (int i = -4; i < 16; i++) //注意，只有0-9是合理范围，其余都是越界读
			cout << dec<<"integer["<<i<<"] :" << hex << 
			(void*)(integer + i) << ":" << int(integer[i]) << endl;
	}
	return 0;
}
