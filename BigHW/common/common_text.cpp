/* 2254298 ������ ���� */
#include"../include/common_text.h"
#include"../include/cmd_console_tools.h"
//====================================================
//�� �� ��:int_len
//��������:���������ĳ���
//�������:
//�� �� ֵ:
//˵    ��:��������
//=====================================================	
int int_len(int num)
{
	if (!num)
		return 1;
	int len = (num < 0 ? 1 : 0);
	num = (num < 0 ? -num : num);
	while (num) {
		len++;
		num /= 10;
	}
	return len;
}
//====================================================
//�� �� ��:ch_in_str
//��������:�ж�ָ���ַ��Ƿ��ڸ����ַ�����
//�������:
//�� �� ֵ:1Ϊ�棬0Ϊ��
//˵    ��:
//=====================================================
int ch_in_str(char ch, char* str, int strlen)
{
	for (int i = 0; i < strlen; i++)
		if (str[i] == ch)
			return 1;
	return 0;
}
//====================================================
//�� �� ��:get_line
//��������:�Ӹ����ļ�ָ�룬��ȡ��ָ���ַ�Ϊֹ
//�������:�ļ�ָ�룬�洢��������飬�Լ����ն����ַ�����int�������ַ���������trim��ʽ��trim�ַ����������
//�� �� ֵ:,������1ʱ��ʾ�����ļ���β����Ϊ��ӵ�EOF���㣩���������ַ�������maxn��Ż�-1�������������0
//˵    ��:�����ַ����������������ַ��ͱ�trim�ַ���
//=====================================================
int get_line(ifstream& infile, char* buffer, int& inputn, int trim, char* trim_ch, char ch_num, char* end, int end_len,  enum system& sys, int maxn, int CR_CRLF_not_equal)
{
	inputn = 0;
	int cur_pos = (int)infile.tellg();
	infile.seekg(0, ios::end);
	int end_pos =(int) infile.tellg();
	infile.seekg(cur_pos, ios::beg);
	if (cur_pos == end_pos)
		return 1;
	char input;
	int trim_left = 0;
	int comp_p = 0;
	int D = 0;
	if (trim == TRIM_LEFT || trim == TRIM_ALL)
		trim_left = 1;
	while (infile.tellg() != end_pos) {
		input = infile.get();
		if (input == 0x0D)
			D = 1;
		else if (input == 0x0A && D) {
			sys = WINDOWS;
			D = 0;
		}
		else
			D = 0;
		if (trim_left && ch_in_str(input, trim_ch, ch_num))
			continue;
		else {
			trim_left = 0;
			buffer[inputn++] = input;
			if (input == end[comp_p])
				comp_p++;
			else
				comp_p = 0;
			if (comp_p == end_len)
				break;
			else if (inputn == maxn)
				return -1;
		}
	}
	if (comp_p == end_len)
		inputn -= end_len;
	if (!CR_CRLF_not_equal && !strcmp("\n", end) && (buffer[inputn - 1] == '\r'))
		inputn--;
	if (trim == TRIM_RIGHT || trim == TRIM_ALL)
		while (inputn && ch_in_str(buffer[inputn - 1], trim_ch, ch_num))
			inputn--;
	buffer[inputn] = '\0';
	//�������Ӧ����whileѭ��������Ϊ����end��return
	return 0;
}
//====================================================
//�� �� ��:print_row
//��������:��ӡһ���е�����
//�������:
//�� �� ֵ:
//˵    ��:������
//=====================================================
void print_row(char* row1, char* row2, int len1, int len2, int eof1, int eof2)
{
	char highlight_char[5] = "\r\v\b\a";
	cout << "�ļ�1 : ";
	if (!len1) {
		if (eof1)
			cout << "<EOF>" << endl;
		else {
			cct_setcolor(HIGHLIGHT);
			cout << "<EMPTY>";
			cct_setcolor();
			cout << "<CR>" << endl;
		}
	}
	else {
		int i = 0;
		while (i < len2 && i < len1) {
			if (row1[i] != row2[i])
				cct_setcolor(HIGHLIGHT);
			char output = row1[i];
			if (ch_in_str(row1[i], highlight_char, 4))
				output = 'X';
			else if (row1[i] == EOF)
				output = '�';
			cout << output;
			cct_setcolor();
			i++;
		}
		while (i < len1) {
			cct_setcolor(HIGHLIGHT);
			char output = row1[i];
			if (ch_in_str(row1[i], highlight_char, 4))
				output = 'X';
			else if (row1[i] == EOF)
				output = '�';
			cout << output;
			cct_setcolor();
			i++;
		}
		if (eof1)
			cout << "<EOF>" << endl;
		else
			cout << "<CR>" << endl;
	}
	cout << "�ļ�2 : ";
	if (!len2) {
		if (eof2)
			cout << "<EOF>" << endl;
		else {
			cct_setcolor(HIGHLIGHT);
			cout << "<EMPTY>";
			cct_setcolor();
			cout << "<CR>" << endl;
		}
	}
	else {
		int i = 0;
		while (i < len2 && i < len1) {
			if (row1[i] != row2[i])
				cct_setcolor(HIGHLIGHT);
			char output = row2[i];
			if (ch_in_str(row2[i], highlight_char, 4))
				output = 'X';
			else if (row2[i] == EOF)
				output = '�';
			cout << output;
			cct_setcolor();
			i++;
		}
		while (i < len2) {
			cct_setcolor(HIGHLIGHT);
			char output = row2[i];
			if (ch_in_str(row2[i], highlight_char, 4))
				output = 'X';
			else if (row2[i] == EOF)
				output = '�';
			cout << output;
			cct_setcolor();
			i++;
		}
		if (eof2)
			cout << "<EOF>" << endl;
		else
			cout << "<CR>" << endl;
	}

	return;
}
//====================================================
//�� �� ��:print_rule
//��������:��ӡ����
//�������:
//�� �� ֵ:
//˵    ��:
//=====================================================
void print_rule(int length)
{
	cout << dec;
	int n = length / 10 + 1;
	cout << setw(8) << " ";
	for (int i = 0; i < n; i++)
		cout << setw(10) << setfill('-') << "-";
	cout << setfill(' ') << endl;;
	cout << setw(8) << " ";
	for (int i = 0; i < n; i++)
		cout << setw(10) << resetiosflags(ios::right) << setiosflags(ios::left) << i;
	cout << endl;
	cout << setw(8) << " ";
	for (int i = 0; i < n; i++)
		for (int j = 0; j < 10; j++)
			cout << j;
	cout << endl;
	cout << setw(8) << " ";
	for (int i = 0; i < n; i++)
		cout << setw(10) << setfill('-') << "-";
	cout << setfill('-') << endl;
	return;
}
//====================================================
//�� �� ��:print_hex
//��������:��ӡhex��ʽ
//�������:
//�� �� ֵ:
//˵    ��:
//=====================================================
void print_hex(char* buffer, int len, int eof)
{
	if (!len&&eof) {
		cout << "<EOF>" << endl;
		return;
	}
	else if (!len) {
		cout << "<EMPTY>" << endl;
		return;
	}
	int i = 0;
	while (i + 16 <= len) {
		cout << setw(8) << setfill('0') << setiosflags(ios::right)  << hex << i << " :";
		for (int j = 0; j < 8; j++)
			cout << " " << setw(2) << setfill('0') << setiosflags(ios::right)  << hex << ((int)(unsigned char)buffer[i + j]);
		cout << " -";
		for (int j = 8; j < 16; j++)
			cout << " " << setw(2) << setfill('0') << setiosflags(ios::right)  << hex << ((int)(unsigned char)buffer[i + j]);
		cout << "  ";
		for (int j = 0; j < 16; j++)
			if (buffer[i + j] < 33 || buffer[i + j]>136)
				cout << ".";
			else
				putchar(buffer[i + j]);
		cout << endl;
		i += 16;
	}
	int temp = i;
	if (len % 16) {
		cout << setw(8) << setfill('0') << setiosflags(ios::right)  << hex << i << " :";
		while (i < len) {
			if (i % 16 == 8)
				cout << " -";
			cout << " " << setw(2) << setfill('0') << setiosflags(ios::right)  << hex << ((int)(unsigned char)buffer[i]);
			i++;
		}
		for (int j = 0; j < (16 - i % 16); j++)
			cout << "   ";
		if (i % 16 <= 8)
			cout << "  ";
		cout << "  ";
		while (temp < len) {
			if (buffer[temp] < 33 || buffer[temp]>136)
				cout << ".";
			else
				putchar(buffer[temp]);
			temp++;
		}
		if (len % 16)
			cout << endl;
	}
	return;
}
//====================================================
//�� �� ��:display
//��������:���������������Ϣ
//�������:
//�� �� ֵ:
//˵    ��:
//=====================================================
void display(int error_type, char* buffer1, char* buffer2, int len1, int len2, int rown1, int rown2, int eof1, int eof2, int display_mode)
{
	int i = 0;
	int llen = int_len(rown1) + 1, rlen = int_len(rown2) + 1;
	switch (error_type) {
		case CHAR_DIFF:
			while (buffer1[i] == buffer2[i])
				i++;
			cout << dec<<setfill(' ') << resetiosflags(ios::right) << "��[" << setiosflags(ios::left) << setw(llen) << rown1 << "/" << setw(rlen) << setiosflags(ios::right)
				<< rown2 << "]�� - ��[" << i << "]���ַ���ʼ�в��죺" << endl;
			break;
		case MORE_CHAR:
			cout << dec<<setfill(' ') << resetiosflags(ios::right) << "��[" << setiosflags(ios::left) << setw(llen) << rown1 << "/" << setw(rlen) << setiosflags(ios::right)
				<< rown2 << "]�� - �ļ�" << (len1 > len2 ? 1 : 2) << "��β���ж����ַ���" << endl;
			break;
		case NOT_END:
			cout << dec<<setfill(' ') << resetiosflags(ios::right) << "��[" << setiosflags(ios::left) << setw(llen) << rown1 << "/" << setw(rlen) << setiosflags(ios::right)
				<< rown2 << "]�� - �ļ�" << (eof1 > eof2 ? "1�ѽ���/�ļ�2�������ݣ�" : "1��������/�ļ�2�ѽ�����") << endl;
			break;
	}
	switch (display_mode) {
		case NORMAL_MODE:
			print_row(buffer1, buffer2, len1, len2, eof1, eof2);
			cout << endl;
			break;
		case DETAIL_MODE:
			print_rule((len1 > len2) ? len1 : len2);
			print_row(buffer1, buffer2, len1, len2, eof1, eof2);
			cout << "�ļ�1(HEX) : " << endl;
			print_hex(buffer1, len1, eof1);
			cout << "�ļ�2(HEX) : " << endl;
			print_hex(buffer2, len2, eof2);
			cout << endl;
			break;
	}
	return;
}

//====================================================
//�� �� ��:diff_and_display
//��������:�������ַ�������жԱ�
//�������:�洢������Ϣ�������󣬴��Աȵ��ַ����鼴�䳤��,��ǰ������չʾ��ʽ���Ƿ񵽴��ļ���β
//�� �� ֵ:
//˵    ��:�в����򷵻�1���޲��췵��0
//=====================================================
int diff(char* buffer1, char* buffer2, int len1, int len2, int rown1, int rown2, int eof1, int eof2, int display_mode, int trim)
{
	int i = 0;
	int error_type = NO_DIFF;
	while (i < len1 && i < len2) {
		if (buffer1[i] != buffer2[i]) {
			error_type = CHAR_DIFF;
			break;
		}
		i++;
	}
	if (len1 == len2 && !error_type)
		if (eof1 ^ eof2)
			error_type = NOT_END;
		else
			return 0;
	else if (!error_type)
		error_type = MORE_CHAR;
	if (display_mode == NONE_MODE && error_type)
		return 1;
	else {
		if (error_type == NOT_END && (trim == TRIM_RIGHT || trim == TRIM_ALL) && (eof1 ^ eof2) && (!len1 || !len2)) {//����
			cout<<dec << resetiosflags(ios::right) << "��[" << setiosflags(ios::left) << setw(int_len(rown1) + 1) << rown1 << "/" << setw(int_len(rown2) + 1)
				<< setiosflags(ios::right) << rown2 << "]�� - �ļ�" << (eof1 > eof2 ? "1�ѽ���/�ļ�2��������." : "1��������/�ļ�2�ѽ�����") << endl;
		}
		else
			display(error_type, buffer1, buffer2, len1, len2, rown1, rown2, eof1, eof2, display_mode);
		return 1;
	}
}
