#include<iostream>
using namespace std;
int main()
{
	if (0) {
		char ch[10]="123456789";
		ch[10] = 'a';    //�˾�Խ��
		ch[14] = 'A';    //�˾�Խ��
		ch[15] = 'B';    //�˾�Խ��
		ch[10] = '\xcc'; //�˾�Խ��
		cout << "addr:" << hex << (void*)(ch) << endl;
		for (int i = -4; i < 16; i++) //ע�⣬ֻ��0-9�Ǻ���Χ�����඼��Խ���
			cout <<dec<< "ch["<< i <<"] :" << hex << (void*)(ch + i)
			<< ":" << int(ch[i]) << endl;
	}
	if (1) {
		int integer[10]={1,2,3,4,5,6,7,8,9,10};
		integer[10] = 11;    //�˾�Խ��
		integer[14] = 12;    //�˾�Խ��
		integer[15] = 13;    //�˾�Խ��
		integer[10] = 0xcccccccc; //�˾�Խ��
		cout << "addr:" << hex << (void*)(integer) << endl;
		for (int i = -4; i < 16; i++) //ע�⣬ֻ��0-9�Ǻ���Χ�����඼��Խ���
			cout << dec<<"integer["<<i<<"] :" << hex << 
			(void*)(integer + i) << ":" << int(integer[i]) << endl;
	}
	return 0;
}
