/* 2254298 大数据 范潇 */
#include <iostream>
#include "../include/class_crt.h"
using namespace std;

/* 允许加入需要的头文件，给出 cfgfile_read_tools类的实现 */


/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
cfgfile_read_tools::cfgfile_read_tools(const char* _cfgname)
{
	cfgname = _cfgname;
	file.open(cfgname, ios::in);//没有用二进制读
	open = (!!file);
}
/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
cfgfile_read_tools::cfgfile_read_tools(const string& _cfgname)
{
	cfgname = _cfgname;
	file.open(cfgname, ios::in);//没有用二进制读
	open = (!!file);
}
/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
cfgfile_read_tools:: ~cfgfile_read_tools()
{
	if (open)
		file.close();
}
/***************************************************************************
  函数名称：
  功    能：判断配置文件是否打开成功
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
bool cfgfile_read_tools::is_open()
{
	return open;
}
/***************************************************************************
  函数名称：
  功    能：组读取函数，读出所有的，放在string型的vector中
  输入参数：
  返 回 值：返回成功组的数量，失败返回-1
  说    明：
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
  函数名称：
  功    能：项读取函数 - 取某个group的所有item，放在string型的vector中
  输入参数：ignore_lower_upper_case 为 true 表示 group_name 大小写不敏感，false 表示大小写敏感，默认为 false
  返 回 值：成功返回该组中项的数量，失败返回-1
  说    明：测试函数中缺省区分大小写
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
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：适合 string 类型的 group_name，其余同上
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
  函数名称：
  功    能：项读取函数 - 取某个group的指定item，放在string中
  输入参数：ignore_lower_upper_case 为 true 表示 group_name 大小写不敏感，false 表示大小写敏感，默认为 false
  返 回 值：成功返回 0，失败返回-1
  说    明： 返回形式是“项名 = 值”的完整形式（供后续自行处理）
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
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：适合 string 类型的 group_name/item_name，其余同上
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
  函数名称：
  功    能：项读取函数 - 按数据类型读取某个group的某个item，放在对应数据类型的变量中
  输入参数：
  返 回 值： 返回值放在 str 中，限定最大长度（含尾零）为 str_maxlen（调用者要保证传入足够空间，不越界）
			如果取不到，则返回 def_str（例：“name = ”形式）
			如果值是含空格、tab 的字符串，则返回第一个空格、tab 前的内容即可
  说    明：取 group_name 组中 item_name 的值，返回为 char *形式
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
  函数名称：
  功    能：
  输入参数：
  返 回 值： 返回值放在 value 中
			如果取不到，则返回 def_str（例：“name = ”形式）
			如果值是含空格、tab 的字符串，则返回全部内容
  说    明：
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
  函数名称：
  功    能：
  输入参数：
  返 回 值：返回值放在 ch 中
			如果取不到，则返回空格（例：“name = ”形式）
  说    明：
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
  函数名称：
  功    能：
  输入参数：
  返 回 值：返回值放在 value 中
  说    明：如果不在[min_value..max_value]范围内/取不到/数据格式不正确，则返回 def_value
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
  函数名称：
  功    能：
  输入参数：
  返 回 值：返回值放在 value 中
  说    明：如果不在[min_value..max_value]范围内/取不到/数据格式不正确，则返回 def_value
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
