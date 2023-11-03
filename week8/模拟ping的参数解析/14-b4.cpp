#define _CRT_SECURE_NO_WARNINGS
/* 2254298 ������ ���� */
#include<iostream>
#include<iomanip>
#include<stdlib.h>
#include<string.h>
using namespace std;
#define MAXPARANUM 10
#define MAXRANGESIZE 20
#define DEFAULTPARA "IP��ַ"
#define HEADER {"����","���Ӳ���","��Χ","Ĭ��ֵ"}
#define HEADER_LEN {5,9,12,7}
#define TAB 7
#define PARANUM 3
struct para {
	char code;
	const char* name;
	int parac;
	int min, max;
	int def;
};
void usage(para *para_list ,const char* filename)
{
	cout << "Usage��" << filename << " ";
	for (int i = 0; i < PARANUM; i++)
		cout << "[-" << para_list[i].code << " " << para_list[i].name << "] ";
	cout << DEFAULTPARA << endl;
	const char* header[4] = HEADER;
	const int header_len[4] = HEADER_LEN;
	int sum = 0;
	for (int i = 0; i < 4; i++)
		sum += header_len[i];
	cout << setw(TAB) << setfill(' ') <<" " << setw(sum) << setfill('=') <<"=" << endl;
	cout << setw(TAB) << setfill(' ')<<" ";
	cout << setiosflags(ios::left);
	for (int i = 0; i < 4; i++)
		cout << setw(header_len[i]) << header[i];
	cout << endl;
	cout << setw(TAB) << setfill(' ') <<' ' << setw(sum) << setfill('=') << '=' << endl;
	for (int i = 0; i < PARANUM; i++) { 
		char temp[MAXRANGESIZE];
		cout << setw(TAB) << setfill(' ')<<' ';
		cout << '-' << setw(header_len[0]-1) << para_list[i].code;
		cout << setw(header_len[1]) << para_list[i].parac;
		sprintf(temp, "[%d..%d]", para_list[i].min, para_list[i].max);
		cout << setw(header_len[2]) << temp;
		cout << setw(header_len[3]) << para_list[i].def;
		cout << endl;
	}
	cout << setw(TAB) << setfill(' ') << ' '<<setw(sum) << setfill('=') << '=' << endl;
}
int check_ip(char* ip)
{
	int  dotc = 0,temp;
	if (*ip < '0' || *ip>'9')
		return 0;
	while (*ip) {
		if (*ip != '.' && (*ip < '0' || *ip>'9'))
			return 0;
		if (*ip == '.') {
			//cout << '-' << endl;
			if (!*(ip+1) || (*(ip+1) == '.') || dotc == 3)
				return 0;
			dotc++;
			ip++;
			continue;
		}
		temp = atoi(ip);
		//cout << "temp=" << temp << endl;
		if (temp < 0 || temp>255)
			return 0;
		ip++;
	}
	if (dotc != 3)
		return 0;
	return 1;
}
int main(int argc,char ** argv)
{
	para para_list[MAXPARANUM] = {
		{'l',"��С",1,32,64000,64},
		{'n',"����",1,1,1024,4},
		{'t',"",0,0,1,0}
	};
	if (argc == 1) {
		usage(para_list, argv[0]);
		return 0;
	}
	if (!check_ip(argv[argc - 1])) {
		cout << "IP��ַ����" << endl;
		return 0;
	}
	for (int i = 1; i < argc - 1; i++) {
		//����һ���������ж��Ƿ�Ϊ�Ϸ�������Ȼ���ж��Ƿ���ڣ������������ǺϷ��������и��Ӳ���������Ϊ�丽�Ӳ���
		if (argv[i][0] != '-'&& strlen(argv[i])!=2) {
			cout << "����" << argv[i] << "������-��ͷ�ĺϷ�����" << endl;
			return 0;
		}
		int valid = 0;
		int j;
		for ( j = 0; j < PARANUM; j++) 
			if (para_list[j].code == argv[i][1]) {
				valid = 1;
				break;
			}
		if (!valid) {
			cout << "����" << argv[i] << "������" << endl;
			return 0;
		}
		//��һ���Ϸ��Ҵ��ڵĲ���
		if (para_list[j].parac == 0)//�޶������
			para_list[j].def = 1;
		else {
			int k = para_list[j].parac;
			int now = i;
			while (k) {
				i++;
				if ( i >= argc-1||argv[i][0]=='-') {
					cout << "����" << argv[now] << "û�к�̲���" << endl;
					return 0;
				}
				int para = atoi((const char*)argv[i]);
				if (para >= para_list[j].min && para <= para_list[j].max)
					para_list[j].def = para;
				k--;
			}
		}
		
	}
	cout << "�������ͨ��" << endl;
	for (int i = 0; i < PARANUM; i++) 
		cout << "-" << para_list[i].code << " ������" << para_list[i].def << endl;
	cout << DEFAULTPARA << "��" << argv[argc - 1] << endl;
	return 0;
}