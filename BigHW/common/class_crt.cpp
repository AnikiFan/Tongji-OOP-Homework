/* 2254298 ������ ���� */
#include <iostream>
#include "../include/class_crt.h"
using namespace std;

/* ���������Ҫ��ͷ�ļ������� cfgfile_read_tools���ʵ�� */


/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
cfgfile_read_tools::cfgfile_read_tools(const char* _cfgname)
{
	cfgname = _cfgname;
	file.open(cfgname, ios::in);//û���ö����ƶ�
	open = (!!file);
}
/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
cfgfile_read_tools::cfgfile_read_tools(const string& _cfgname)
{
	cfgname = _cfgname;
	file.open(cfgname, ios::in);//û���ö����ƶ�
	open = (!!file);
}
/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
cfgfile_read_tools:: ~cfgfile_read_tools()
{
	if (open)
		file.close();
}
/***************************************************************************
  �������ƣ�
  ��    �ܣ��ж������ļ��Ƿ�򿪳ɹ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
bool cfgfile_read_tools::is_open()
{
	return open;
}
/***************************************************************************
  �������ƣ�
  ��    �ܣ����ȡ�������������еģ�����string�͵�vector��
  ���������
  �� �� ֵ�����سɹ����������ʧ�ܷ���-1
  ˵    ����
***************************************************************************/
int cfgfile_read_tools::get_all_group(vector <string>& ret)
{
	const char* const stop_key = { ";#" };
	const char* const trim_key = { "\t " };
	char buffer[MAXN];
	file.clear();
	file.seekg(0, ios::beg);
	while (!file.eof()) {
		file.getline(buffer, MAXN);
		split(buffer, stop_key);
		trim(buffer, trim_key, 3);
		if ((strlen(buffer) > 2) && (buffer[0] == '[') && (buffer[strlen(buffer) - 1] == ']')) {
			buffer[strlen(buffer)] = '\0';
			trim(buffer + 1, " \b", 3);
			ret.push_back(string(buffer));
		}
	}
	return ret.size();
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ����ȡ���� - ȡĳ��group������item������string�͵�vector��
  ���������ignore_lower_upper_case Ϊ true ��ʾ group_name ��Сд�����У�false ��ʾ��Сд���У�Ĭ��Ϊ false
  �� �� ֵ���ɹ����ظ��������������ʧ�ܷ���-1
  ˵    �������Ժ�����ȱʡ���ִ�Сд
***************************************************************************/
int cfgfile_read_tools::get_all_item(const char* const group_name, vector <string>& ret, const bool ignore_lower_upper_case)
{
	if (!group_name) {
		const char* const stop_key = { ";#" };
		const char* const trim_key = { "\t " };
		char buffer[MAXN];
		file.clear();
		file.seekg(0, ios::beg);
		while (!file.eof()) {
			file.getline(buffer, MAXN);
			split(buffer, stop_key);
			trim(buffer, trim_key, 3);
			if ((strlen(buffer) > 2) && (buffer[0] == '[') && (buffer[strlen(buffer) - 1] == ']'))
				continue;
			if (strlen(buffer) && ch_in_str('=', buffer, strlen(buffer)))
				ret.push_back(string(buffer));
		}
		return ret.size();
	}
	int flag = 0;
	string test = "a";
	string name = group_name;
	if (ignore_lower_upper_case)
		to_upper(name);
	const char* const stop_key = { ";#" };
	const char* const trim_key = { "\t " };
	char buffer[MAXN];
	file.clear();
	file.seekg(0, ios::beg);
	while (!file.eof()) {
		file.getline(buffer, MAXN);
		split(buffer, stop_key);
		trim(buffer, trim_key, 3);
		if ((strlen(buffer) > 2) && (buffer[0] == '[') && (buffer[strlen(buffer) - 1] == ']')) {
			buffer[strlen(buffer)] = '\0';
			string temp = buffer;
			if (ignore_lower_upper_case)
				to_upper(temp);
			if (temp == name) {
				flag = 1;
				break;
			}
		}
	}
	if (!flag)
		return -1;
	while (!file.eof()) {
		file.getline(buffer, MAXN);
		split(buffer, stop_key);
		trim(buffer, trim_key, 3);
		if ((strlen(buffer) > 2) && (buffer[0] == '[') && (buffer[strlen(buffer) - 1] == ']'))
			break;
		if (strlen(buffer) && ch_in_str('=', buffer, strlen(buffer)))
			ret.push_back(string(buffer));
	}
	return ret.size();
}
/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    �����ʺ� string ���͵� group_name������ͬ��
***************************************************************************/
int cfgfile_read_tools::get_all_item(const string& group_name, vector <string>& ret, const bool ignore_lower_upper_case)
{
	if (!group_name.size()) {
		const char* const stop_key = { ";#" };
		const char* const trim_key = { "\t " };
		char buffer[MAXN];
		file.clear();
		file.seekg(0, ios::beg);
		while (!file.eof()) {
			file.getline(buffer, MAXN);
			split(buffer, stop_key);
			trim(buffer, trim_key, 3);
			if ((strlen(buffer) > 2) && (buffer[0] == '[') && (buffer[strlen(buffer) - 1] == ']'))
				continue;
			if (strlen(buffer) && ch_in_str('=', buffer, strlen(buffer)))
				ret.push_back(string(buffer));
		}
		return ret.size();
	}
	int flag = 0;
	string test = "a";
	string name = group_name;
	if (ignore_lower_upper_case)
		to_upper(name);
	const char* const stop_key = { ";#" };
	const char* const trim_key = { "\t " };
	char buffer[MAXN];
	file.clear();
	file.seekg(0, ios::beg);
	while (!file.eof()) {
		file.getline(buffer, MAXN);
		split(buffer, stop_key);
		trim(buffer, trim_key, 3);
		if ((strlen(buffer) > 2) && (buffer[0] == '[') && (buffer[strlen(buffer) - 1] == ']')) {
			buffer[strlen(buffer)] = '\0';
			string temp = buffer;
			if (ignore_lower_upper_case)
				to_upper(temp);
			if (temp == name) {
				flag = 1;
				break;
			}
		}
	}
	if (!flag)
		return -1;
	while (!file.eof()) {
		file.getline(buffer, MAXN);
		split(buffer, stop_key);
		trim(buffer, trim_key, 3);
		if ((strlen(buffer) > 2) && (buffer[0] == '[') && (buffer[strlen(buffer) - 1] == ']'))
			break;
		if (strlen(buffer) && ch_in_str('=', buffer, strlen(buffer)))
			ret.push_back(string(buffer));
	}
	return ret.size();
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ����ȡ���� - ȡĳ��group��ָ��item������string��
  ���������ignore_lower_upper_case Ϊ true ��ʾ group_name ��Сд�����У�false ��ʾ��Сд���У�Ĭ��Ϊ false
  �� �� ֵ���ɹ����� 0��ʧ�ܷ���-1
  ˵    ���� ������ʽ�ǡ����� = ֵ����������ʽ�����������д���
***************************************************************************/
int cfgfile_read_tools::get_one_item(const char* const group_name, const char* const item_name, string& ret, const bool ignore_lower_upper_case)
{
	vector	<string> group;
	int num;
	num = get_all_item(group_name, group, ignore_lower_upper_case);
	if (num == -1)
		return -1;
	char buffer[MAXN];
	string name = item_name;
	if (ignore_lower_upper_case)
		to_upper(name);
	int i;
	for (i = 0; i < num; i++) {
		strcpy_s(buffer, group[i].data());
		split(buffer, "=");
		trim(buffer, " \t", 3);
		string temp = buffer;
		if (ignore_lower_upper_case)
			to_upper(temp);
		if (temp == name) {
			ret = group[i];
			return 0;
		}
	}
	return -1;
}
/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    �����ʺ� string ���͵� group_name/item_name������ͬ��
***************************************************************************/
int cfgfile_read_tools::get_one_item(const string& group_name, const string& item_name, string& ret, const bool ignore_lower_upper_case)
{
	vector	<string> group;
	int num;
	num = get_all_item(group_name, group, ignore_lower_upper_case);
	if (num == -1)
		return -1;
	char buffer[MAXN];
	string name = item_name;
	if (ignore_lower_upper_case)
		to_upper(name);
	int i;
	for (i = 0; i < num; i++) {
		strcpy_s(buffer, group[i].data());
		split(buffer, "=");
		trim(buffer, " \t", 3);
		string temp = buffer;
		if (ignore_lower_upper_case)
			to_upper(temp);
		if (temp == name) {
			ret = group[i];
			return 0;
		}
	}
	return -1;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ����ȡ���� - ���������Ͷ�ȡĳ��group��ĳ��item�����ڶ�Ӧ�������͵ı�����
  ���������
  �� �� ֵ�� ����ֵ���� str �У��޶���󳤶ȣ���β�㣩Ϊ str_maxlen��������Ҫ��֤�����㹻�ռ䣬��Խ�磩
			���ȡ�������򷵻� def_str��������name = ����ʽ��
			���ֵ�Ǻ��ո�tab ���ַ������򷵻ص�һ���ո�tab ǰ�����ݼ���
  ˵    ����ȡ group_name ���� item_name ��ֵ������Ϊ char *��ʽ
***************************************************************************/
int cfgfile_read_tools::item_get_value(const char* const group_name, const char* const item_name, const char* const def_str, char* str, const int str_maxlen, const bool ignore_lower_upper_case)
{
	string target;
	int result = get_one_item(group_name, item_name, target, ignore_lower_upper_case);
	if (result == -1) {
		strcpy_s(str, str_maxlen, def_str);
		return 0;
	}
	int pos = target.find_first_of('=')+1;
	char* ret = (char*)(target.data() + pos);
	trim(ret, "\t ", 3);
	split(ret, " \t");
	if (!ret[0]) {
		char  temp[MAXN];
		strcpy_s(temp, def_str);
		temp[str_maxlen - 1] = '\0';
		strcpy_s(str,str_maxlen,temp);
		return 0;
	}
	char  temp[MAXN];
	strcpy_s(temp, ret);
	temp[str_maxlen - 1] = '\0';
	strcpy_s(str,str_maxlen,temp);
	return 0;
}
/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ�� ����ֵ���� value ��
			���ȡ�������򷵻� def_str��������name = ����ʽ��
			���ֵ�Ǻ��ո�tab ���ַ������򷵻�ȫ������
  ˵    ����
***************************************************************************/
int cfgfile_read_tools::item_get_value(const char* const group_name, const char* const item_name, const char* const def_str, string& value, const bool ignore_lower_upper_case)
{
	string target;
	int result = get_one_item(group_name, item_name, target, ignore_lower_upper_case);
	if (result == -1) {
		value = def_str;
		return 0;
	}
	int pos = target.find_first_of('=')+1;
	char* ret = (char*)(target.data() + pos);
	trim(ret, "\t ", 3);
	if (!ret[0]) {
		value = def_str;
		return 0;
	}
	value = ret;
	return 0;
}
/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ������ֵ���� ch ��
			���ȡ�������򷵻ؿո�������name = ����ʽ��
  ˵    ����
***************************************************************************/
int cfgfile_read_tools::item_get_value(const char* const group_name, const char* const item_name, char& ch, const bool ignore_lower_upper_case)
{
	string target;
	int result = get_one_item(group_name, item_name, target, ignore_lower_upper_case);
	if (result == -1) {
		ch = ' ';
		return -1;
	}
	int pos = target.find_first_of('=')+1;
	char* ret = (char*)(target.data() + pos);
	trim(ret, "\t ", 3);
	split(ret, " \t");
	if (!ret[0]) {
		ch = ' ';
		return 0;
	}
	ch = ret[0];
	return 0;
}
/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ������ֵ���� value ��
  ˵    �����������[min_value..max_value]��Χ��/ȡ����/���ݸ�ʽ����ȷ���򷵻� def_value
***************************************************************************/
int cfgfile_read_tools::item_get_value(const char* const group_name, const char* const item_name, const int min_value, const int max_value, const int def_value, int& value, const bool ignore_lower_upper_case)
{
	string target;
	int result = get_one_item(group_name, item_name, target, ignore_lower_upper_case);
	if (result == -1) {
		value = def_value;
		return -1;
	}
	int pos = target.find_first_of('=')+1;
	char* ret = (char*)(target.data() + pos);
	trim(ret, "\t ", 3);
	split(ret, " \t");
	if (!between(ret[0],'0','9')) {
		value = def_value;
		return 0;
	}
	int val = stoi(ret);
	if (val<min_value || value>max_value) {
		value = def_value;
		return 0;
	}
	value = val;
	return 0;
}
/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ������ֵ���� value ��
  ˵    �����������[min_value..max_value]��Χ��/ȡ����/���ݸ�ʽ����ȷ���򷵻� def_value
***************************************************************************/
int cfgfile_read_tools::item_get_value(const char* const group_name, const char* const item_name, const double min_value, const double max_value, const double def_value, double& value, const bool ignore_lower_upper_case)
{
	string target;
	int result = get_one_item(group_name, item_name, target, ignore_lower_upper_case);
	if (result == -1) {
		value = def_value;
		return -1;
	}
	int pos = target.find_first_of('=')+1;
	char* ret = (char*)(target.data() + pos);
	trim(ret, "\t ", 3);
	split(ret, " \t");
	if (!between(ret[0],'0','9')) {
		value = def_value;
		return 0;
	}
	double val = stof(ret);
	if (val<min_value || value>max_value) {
		value = def_value;
		return 0;
	}
	value = val;
	return 0;
}
