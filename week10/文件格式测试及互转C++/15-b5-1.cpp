/* 2254298 ������ ���� */
#include<iostream>
#include<fstream>
#include<string.h>
#define MAXFILESIZE 200
using namespace std;
void Usage(char*name)
{
	cout << "Usage : "<<name<<" --check �ļ��� | --convert { wtol|ltow } Դ�ļ��� Ŀ���ļ���" << endl;
	cout << "        "<<name<<" --check a.txt" << endl;
	cout << "        "<<name<<" --convert wtol a.win.txt a.linux.txt" << endl;
	cout << "        "<<name<<" --convert ltow a.linux.txt a.win.txt" << endl;
	return;
}
int main(int argc, char** argv)
{
	char  input[10];
	if (argc != 3 && argc != 5) {
		Usage(argv[0]);
		return 0;
	}
	int wtol = 0;
	int ltow = 0;
	int in=0, out=0;
	if (argc == 3 && strcmp(argv[1], "--check")) {
		Usage(argv[0]);
		return 0;
	}
	if (argc == 5 && (strcmp(argv[1], "--convert") ||( strcmp(argv[2], "wtol") && strcmp(argv[2], "ltow")))) {
		Usage(argv[0]);
		return 0;
	}
	if (argc == 3) 
		in = 2;
	else {
		in = 3;
		out = 4;
		if (!strcmp(argv[2], "ltow"))
			ltow = 1;
		else if (!strcmp(argv[2], "wtol"))
			wtol = 1;
		else {
			Usage(argv[0]);
			return 0;
		}
	}
	ifstream infile(argv[in], ios::in | ios::binary);
	if (!infile) {
		cout << "�ļ���ʧ��" << endl;
		infile.close();
		return -1;
	}
	infile.seekg(0, ios::end);
	long long end = infile.tellg(), count = 0;
	infile.seekg(0, ios::beg);
	int windows = 0, Linux = 0;
	int D = 0;
	while (count < end) {
		infile.read(input, 1);
		if (input[0] == 0x0D)
			D = 1;
		else if (input[0] == 0x0A && D) {
			windows = 1;
			D = 0;
		}
		else if (input[0] == 0x0A) {
			Linux = 1;
		}
		else
			D = 0;
		if (windows && Linux)
			break;
		count++;
	}
int invalid = !(windows ^ Linux);
	if (invalid) {
		cout << "�ļ���ʽ�޷�ʶ��" << endl;
		return 0;
	}
	if (argc == 3) {
		if (windows)
			cout << "Windows��ʽ" << endl;
		else
			cout << "Linux��ʽ" << endl;
		infile.close();
		return 0;
	}
	if ((wtol && Linux)||(ltow&&windows)) {
		cout << "�ļ���ʽ�޷�ʶ��" << endl;
		return 0;
	}
	ofstream outfile(argv[out], ios::out|ios::binary);
	if (!outfile) {
		cout << "�ļ���ʧ��" << endl;
		infile.close();
		outfile.close();
		return -1;
	}
	count = 0;
	int num = 0;
	infile.seekg(0, ios::beg);
	while (count < end) {//wtolʱ������0D0Aֻд0A��ltowʱ������0Aд0A0D
		infile.read(input, 1);
		if (input[0] == 0x0A && ltow) {
			outfile.put(0x0D).put(0x0A);
			num++;
		}
		else if (input[0] == 0x0D && wtol && (infile.peek() == 0x0A)) {
			infile.read(input, 1);
			outfile.put(0x0A);
			count++;
			num++;
		}
		else
			outfile.put(input[0]);
		count++;
	}
	cout << "ת����ɣ�" << (wtol ? "ȥ��" : "����") << num << "��0x0D" << endl;
	infile.close();
	outfile.close();
	return 0;
}