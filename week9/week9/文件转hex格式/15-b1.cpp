/* 2254298 ������ ���� */
/* 2050215 ����ǿ 2151188 ½���� 2153538 ������ 2251320 Ϳ�к� 2253716 ŷ���� 2252313 ������ 2253733 ��ҫ�� 2251882 ��ʦ�� 2151753 ������ 2253204 ���ղ� 2252086 �ﾸ�� 2251924 �̾��� */
#include<iostream>
#include<iomanip>
#include<fstream>
#define INPUTSIZE 10
#define MAXNAMESIZE 200
using namespace std;
int main()
{
	clog << "�ļ���������ʽ������:" << endl;
	clog << "    a.txt                     : ����·����ʽ" << endl;
	clog << "    ..\\data\\b.dat             : ���·����ʽ" << endl;
	clog << "    C:\\Windows\\System32\\c.dat : �������·����ʽ" << endl;
	clog << "�������ļ��� : ";
	char input[INPUTSIZE], buff[20] = { 0 },filename[MAXNAMESIZE];
	int top = 0;
	cin >> filename;
	ifstream infile (filename, ios::in|ios::binary);
	if (!infile) {
		cout << "�����ļ�"<<filename<<" ��ʧ��!" << endl;
		infile.close();
		return -1;
	}
	infile.seekg(0, ios::end);
	long long end = infile.tellg(),count = 0;
	infile.seekg(0, ios::beg);
	while (count < end) {
		if (!((count - 8) % 16))
			cout << " -";
		if (!(count % 16)) 
			cout << setw(8) << setfill('0') << setiosflags(ios::right)<<setiosflags(ios::uppercase) << hex << count  << ": ";
		infile.read(input,1);
		cout << " " << setw(2) << setfill('0') << setiosflags(ios::right) <<setiosflags(ios::uppercase)<< hex << ((int)(unsigned char)input[0]);
		buff[top++] = input[0];
		if (top == 16) {
			cout << "  ";
			top = 0;
			for (int i = 0; i < 16; i++)
				if (buff[i] >= 33 && buff[i] <= 126)
					putchar(buff[i]);
				else
					putchar('.');
			cout << endl;
		}
		count++;
	}
	if (!top)
		return 0;
	cout << "  ";
	for (int i = 0; i < 16 - top; i++)
		cout << "   ";
	if (top <= 8)
		cout << "  ";
	for (int i = 0; i < top; i++)
				if (buff[i] >= 33 && buff[i] <= 126)
					putchar(buff[i]);
				else
					putchar('.');
	cout << endl;
	infile.close();
	return 0;
}