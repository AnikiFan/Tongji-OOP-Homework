/* 2254298 大数据 范潇 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include "../include/class_aat.h"
//如有必要，可以加入其它头文件
using namespace std;
#define HEADER {"name","type","default","exists","value","range/set"}
#define TAB " "
#if !ENABLE_LIB_COMMON_TOOLS //不使用lib才有效

/* ---------------------------------------------------------------
	 允许加入其它需要static函数（内部工具用）
   ---------------------------------------------------------------- */
static int num_length(int num)
{
	int length = 0;
	if (!num)
		length = 1;
	while (num) {
		num /= 10;
		length++;
	}
	return length;
}
static string from_ipaddr_to_str(unsigned int ip)
{
	string ipaddr;
	unsigned int* temp = &ip;
	const char* p = (const char*)temp;
	p += 3;
	char num[10];
	for (int i = 0; i < 3; i++) {
		ipaddr.append(_itoa(*p < 0 ? 256 + *p : *p, num, 10));
		ipaddr.append(".");
		p--;
	}
	ipaddr.append(_itoa(*p < 0 ? 256 + *p : *p, num, 10));
	return ipaddr; //此句根据需要修改
}
/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：null
 ***************************************************************************/
args_analyse_tools::args_analyse_tools()
{
	extargs_type = ST_EXTARGS_TYPE::null;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：boolean
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const ST_EXTARGS_TYPE type, const int ext_num, const bool def)
{
	args_name = name;
	extargs_type = type;
	extargs_num = ext_num;
	extargs_bool_default = def;
	args_existed = 0;
	args_name_length = strlen(name);
	type_length = 4;
	default_length = def ? 4 : 5;
	value_length = 1;
	range_set_length = 1;
	strcpy(type_name, "Bool");
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：int_with_default、int_with_error
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const ST_EXTARGS_TYPE type, const int ext_num, const int def, const int _min, const int _max)
{
	args_name = name;
	extargs_type = type;
	extargs_num = ext_num;
	extargs_int_default = def;
	extargs_int_min = _min;
	extargs_int_max = _max;
	args_existed = 0;
	args_name_length = strlen(name);
	type_length = (type == ST_EXTARGS_TYPE::int_with_default ? 14 : 12);
	default_length = (type == ST_EXTARGS_TYPE::int_with_default ? num_length(def) : 1);
	exists_length = 1;
	value_length = 1;
	range_set_length = 4 + num_length(_min) + num_length(_max);
	if (type == ST_EXTARGS_TYPE::int_with_default)
		strcpy(type_name, "IntWithDefault");
	else
		strcpy(type_name, "IntWithError");
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：int_with_set_default、int_with_set_error
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const enum ST_EXTARGS_TYPE type, const int ext_num, const int def_of_set_pos, const int* const set)
{
	args_name = name;
	extargs_type = type;
	extargs_num = ext_num;
	extargs_int_default = set[def_of_set_pos];
	extargs_int_set = (int*)set;
	args_existed = 0;
	args_name_length = strlen(name);
	type_length = (type == ST_EXTARGS_TYPE::int_with_set_default ? 17 : 15);
	default_length = (type == ST_EXTARGS_TYPE::int_with_set_default ? num_length(set[def_of_set_pos]) : 1);
	exists_length = 1;
	value_length = 1;
	range_set_length = 0;
	int  i = 0;
	while (set[i] != INVALID_INT_VALUE_OF_SET) {
		range_set_length += num_length(set[i]);
		i++;
	}
	range_set_length += i - 1;
	if (type == ST_EXTARGS_TYPE::int_with_set_default)
		strcpy(type_name, "IntSETWithDefault");
	else
		strcpy(type_name, "IntSETWithError");
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：str、ipaddr_with_default、ipaddr_with_error
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const ST_EXTARGS_TYPE type, const int ext_num, const string def)
{
	args_name = name;
	extargs_type = type;
	extargs_num = ext_num;
	args_existed = 0;
	int n = 0;
	int temp = 0;
	int time = 1;
	if (type == ST_EXTARGS_TYPE::str)
		extargs_string_default = def;
	else {
		extargs_ipaddr_default = 0;
		for (int i = def.size() - 1; i >= 0; i--) {
			if (def[i] == '.') {
				extargs_ipaddr_default += (temp << (8 * n));
				n++;
				temp = 0;
				time = 1;
				continue;
			}
			temp += (def[i] - '0') * time;
			time *= 10;
		}
		extargs_ipaddr_default += (temp << (8 * n));
	}
	args_name_length = strlen(name);
	if (type == ST_EXTARGS_TYPE::str)
		type_length = 6;
	else if (type == ST_EXTARGS_TYPE::ipaddr_with_default)
		type_length = 17;
	else
		type_length = 15;
	if (type == ST_EXTARGS_TYPE::str)
		default_length = def.length() ? def.length() : 1;
	else if (type == ST_EXTARGS_TYPE::ipaddr_with_default)
		default_length = def.length();
	else
		default_length = 1;
	exists_length = 1;
	value_length = 1;
	range_set_length = 1;
	if (type == ST_EXTARGS_TYPE::str)
		strcpy(type_name, "String");
	else if (type == ST_EXTARGS_TYPE::ipaddr_with_default)
		strcpy(type_name, "IPAddrWithDefault");
	else
		strcpy(type_name, "IPAddrWithError");
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：str_with_set_default、str_with_set_error
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const ST_EXTARGS_TYPE type, const int ext_num, const int def_of_set_pos, const string* const set)
{
	args_name = name;
	extargs_type = type;
	extargs_num = ext_num;
	extargs_string_default = set[def_of_set_pos];
	args_existed = 0;
	extargs_string_set = (string*)set;
	args_name_length = strlen(name);
	type_length = (type == ST_EXTARGS_TYPE::str_with_set_default ? 20 : 18);
	default_length = (type == ST_EXTARGS_TYPE::str_with_set_default ? set[def_of_set_pos].length() : 1);
	exists_length = 1;
	value_length = 1;
	range_set_length = 0;
	int  i = 0;
	while (set[i].length()) {
		range_set_length += set[i].length();
		i++;
	}
	range_set_length += i - 1;
	if (type == ST_EXTARGS_TYPE::str_with_set_default)
		strcpy(type_name, "StringSETWithDefault");
	else
		strcpy(type_name, "StringSETWithError");
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
 ***************************************************************************/
args_analyse_tools::~args_analyse_tools()
{
}

/* ---------------------------------------------------------------
	 允许AAT中自定义成员函数的实现（private）
   ---------------------------------------------------------------- */

   /***************************************************************************
	 函数名称：
	 功    能：
	 输入参数：
	 返 回 值：
	 说    明：已实现，不要动
	***************************************************************************/
const string args_analyse_tools::get_name() const
{
	return this->args_name;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：加!!后，只能是0/1
			已实现，不要动
 ***************************************************************************/
const int args_analyse_tools::existed() const
{
	return !!this->args_existed;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：已实现，不要动
 ***************************************************************************/
const int args_analyse_tools::get_int() const
{
	return this->extargs_int_value;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：已实现，不要动
 ***************************************************************************/
const string args_analyse_tools::get_string() const
{
	return this->extargs_string_value;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：已实现，不要动
 ***************************************************************************/
const unsigned int args_analyse_tools::get_ipaddr() const
{
	return this->extargs_ipaddr_value;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：将 extargs_ipaddr_value 的值从 0x7f000001 转为 "127.0.0.1"
 ***************************************************************************/
const string args_analyse_tools::get_str_ipaddr() const
{
	return from_ipaddr_to_str(extargs_ipaddr_value); //此句根据需要修改
}


/***************************************************************************
  函数名称：
  功    能：
  输入参数：follow_up_args：是否有后续参数
			0  ：无后续参数
			1  ：有后续参数
  返 回 值：
  说    明：友元函数
***************************************************************************/
int args_analyse_process(const int argc, const char* const* const argv, args_analyse_tools* const args, const int follow_up_args)
{
	int i = 1;
	while (i < argc) {
		int j = 0;
		if (strlen(argv[i]) < 3 || argv[i][0] != '-' || argv[i][1] != '-') {
			if(!follow_up_args)
				cout << "参数[" << argv[i] << "]格式非法(不是--开头的有效内容)." << endl;
			return follow_up_args?i:-1;
		}
		while (argv[i] != args[j].args_name) {
			if (args[j].extargs_type == ST_EXTARGS_TYPE::null) {//无匹配参数
				if (!follow_up_args || (strlen(argv[i]) > 2 && argv[i][1] == '-')) {
					cout << "参数[" << argv[i] << "]非法." << endl;
					return -1;
				}
			return follow_up_args?i:-1;
			}
			j++;
		}
		if (args[j].extargs_type == ST_EXTARGS_TYPE::boolean) {//此处默认bool型额外参数数量一定为0
			if (args[j].args_existed) {
				cout << "参数[" << args[j].args_name << "]重复." << endl;
				return -1;
			}
			args[j].args_existed = 1;
			args[i].value_length = 4;
		}
		else if (args[j].extargs_type == ST_EXTARGS_TYPE::int_with_default || args[j].extargs_type == ST_EXTARGS_TYPE::int_with_error
			|| args[j].extargs_type == ST_EXTARGS_TYPE::int_with_set_default || args[j].extargs_type == ST_EXTARGS_TYPE::int_with_set_error) {
			if (args[j].args_existed) {
				cout << "参数[" << args[j].args_name << "]重复." << endl;
				return -1;
			}
			if (i + args[j].extargs_num >= argc) {
				if (args[j].extargs_type == ST_EXTARGS_TYPE::int_with_default || args[j].extargs_type == ST_EXTARGS_TYPE::int_with_error) {
					cout << "参数[" << argv[i] << "]的附加参数不足. (类型:int, 范围[" << args[j].extargs_int_min << ".." << args[j].extargs_int_max << "]";
					if (args[j].extargs_type == ST_EXTARGS_TYPE::int_with_default)
						cout << " 缺省:" << args[j].extargs_int_default << ")" << endl;
					else
						cout << ")" << endl;
				}
				else {
					cout << "参数[" << argv[i] << "]的附加参数不足. (类型:int, 可取值[";
					int* p = args[j].extargs_int_set;
					cout << *p;
					p++;
					while (*p != INVALID_INT_VALUE_OF_SET) {
						cout << "/" << *p;
						p++;
					}
					if (args[j].extargs_type == ST_EXTARGS_TYPE::int_with_set_default)
						cout << "] 缺省:" << args[j].extargs_int_default << ")" << endl;
					else
						cout << "])" << endl;
				}
				return -1;
			}
			i++;//只考虑了参数数量为1的情况
			if (strlen(argv[i]) >= 2 && argv[i][0] == '-' && argv[i][1] == '-') {
				if (args[j].extargs_type == ST_EXTARGS_TYPE::int_with_default || args[j].extargs_type == ST_EXTARGS_TYPE::int_with_error) {
					cout << "参数[" << argv[i - 1] << "]缺少附加参数. (类型:int, 范围[" << args[j].extargs_int_min << ".." << args[j].extargs_int_max << "]";
					if (args[j].extargs_type == ST_EXTARGS_TYPE::int_with_default)
						cout << " 缺省:" << args[j].extargs_int_default << ")" << endl;
					else
						cout << ")" << endl;
				}
				else {
					cout << "参数[" << argv[i - 1] << "]缺少附加参数. (类型:int, 可取值[";
					int* p = args[j].extargs_int_set;
					cout << *p;
					p++;
					while (*p != INVALID_INT_VALUE_OF_SET) {
						cout << "/" << *p;
						p++;
					}
					if (args[j].extargs_type == ST_EXTARGS_TYPE::int_with_set_default)
						cout << "] 缺省:" << args[j].extargs_int_default << ")" << endl;
					else
						cout << "])" << endl;
				}
				return -1;
			}
			int k = 0;
			int neg = 0;
			if (argv[i][0] == '-' && !argv[i][1]) {	//单独一个-
				if (args[j].extargs_type == ST_EXTARGS_TYPE::int_with_default || args[j].extargs_type == ST_EXTARGS_TYPE::int_with_error) {
					cout << "参数[" << argv[i - 1] << "]的附加参数不是整数. (类型:int, 范围[" << args[j].extargs_int_min << ".." << args[j].extargs_int_max << "]";
					if (args[j].extargs_type == ST_EXTARGS_TYPE::int_with_default)
						cout << " 缺省:" << args[j].extargs_int_default << ")" << endl;
					else
						cout << ")" << endl;
				}
				else {
					cout << "参数[" << argv[i - 1] << "]的附加参数不是整数. (类型:int, 可取值[";
					int* p = args[j].extargs_int_set;
					cout << *p;
					p++;
					while (*p != INVALID_INT_VALUE_OF_SET) {
						cout << "/" << *p;
						p++;
					}
					if (args[j].extargs_type == ST_EXTARGS_TYPE::int_with_set_default)
						cout << "] 缺省:" << args[j].extargs_int_default << ")" << endl;
					else
						cout << "])" << endl;
				}
				return -1;
			}
			else if (argv[i][0] == '-') {
				neg = 1;
				k = 1;
			}
			int temp = 0;
			while (argv[i][k]) {
				if (argv[i][k] < '0' || argv[i][k]>'9') {
					if (args[j].extargs_type == ST_EXTARGS_TYPE::int_with_default || args[j].extargs_type == ST_EXTARGS_TYPE::int_with_error) {
						cout << "参数[" << argv[i - 1] << "]的附加参数不是整数. (类型:int, 范围[" << args[j].extargs_int_min << ".." << args[j].extargs_int_max << "]";
						if (args[j].extargs_type == ST_EXTARGS_TYPE::int_with_default)
							cout << " 缺省:" << args[j].extargs_int_default << ")" << endl;
						else
							cout << ")" << endl;
					}
					else {
						cout << "参数[" << argv[i - 1] << "]的附加参数不是整数. (类型:int, 可取值[";
						int* p = args[j].extargs_int_set;
						cout << *p;
						p++;
						while (*p != INVALID_INT_VALUE_OF_SET) {
							cout << "/" << *p;
							p++;
						}
						if (args[j].extargs_type == ST_EXTARGS_TYPE::int_with_set_default)
							cout << "] 缺省:" << args[j].extargs_int_default << ")" << endl;
						else
							cout << "])" << endl;
					}
					return -1;
				}
				temp *= 10;
				temp += (argv[i][k] - '0');
				k++;
			}
			temp = neg ? -temp : temp;
			if (args[j].extargs_type == ST_EXTARGS_TYPE::int_with_default || args[j].extargs_type == ST_EXTARGS_TYPE::int_with_error) {
				if (temp<args[j].extargs_int_min || temp> args[j].extargs_int_max)
					if (args[j].extargs_type == ST_EXTARGS_TYPE::int_with_default) {
						args[j].extargs_int_value = args[j].extargs_int_default;
						args[j].value_length = args[j].default_length;
					}
					else {
						cout << "参数[" << argv[i - 1] << "]的附加参数值(" << temp << ")非法. (类型:int, 范围[" << args[j].extargs_int_min << ".." << args[j].extargs_int_max << "])" << endl;
						return -1;
					}
				else {
					args[j].extargs_int_value = temp;
					args[j].value_length = num_length(temp);
				}
			}
			else {
				int* p = args[j].extargs_int_set;
				while (*p != INVALID_INT_VALUE_OF_SET) {
					if (*p == temp)
						break;
					p++;
				}
				if (*p == INVALID_INT_VALUE_OF_SET)
					if (args[j].extargs_type == ST_EXTARGS_TYPE::int_with_set_default) {
						args[j].extargs_int_value = args[j].extargs_int_default;
						args[j].value_length = args[j].default_length;
					}
					else {
						cout << "参数[" << argv[i - 1] << "]的附加参数值(" << temp << ")非法. (类型:int, 可取值[";
						int* p = args[j].extargs_int_set;
						cout << *p;
						p++;
						while (*p != INVALID_INT_VALUE_OF_SET) {
							cout << "/" << *p;
							p++;
						}
						cout << "])" << endl;
						return -1;
					}
				else {
					args[j].extargs_int_value = temp;
					args[j].value_length = num_length(temp);
				}
			}
			args[j].args_existed = 1;
		}
		else if (args[j].extargs_type == ST_EXTARGS_TYPE::ipaddr_with_default || args[j].extargs_type == ST_EXTARGS_TYPE::ipaddr_with_error) {
			if (args[j].args_existed) {
				cout << "参数[" << args[j].args_name << "]重复." << endl;
				return -1;
			}
			if (i + args[j].extargs_num >= argc) {
				if (args[j].extargs_type == ST_EXTARGS_TYPE::int_with_error)
					cout << "参数[" << argv[i] << "]的附加参数不足. (类型:IP地址)" << endl;
				else
					cout << "参数[" << argv[i] << "]的附加参数不足. (类型:IP地址 缺省:" << from_ipaddr_to_str(args[j].extargs_ipaddr_default) << ")" << endl;
				return -1;
			}
			i++;//只考虑了参数数量为1的情况
			if (strlen(argv[i]) >= 2 && argv[i][0] == '-' && argv[i][1] == '-') {
				if (args[j].extargs_type == ST_EXTARGS_TYPE::int_with_error)
					cout << "参数[" << argv[i-1] << "]缺少附加参数. (类型:IP地址)" << endl;
				else
					cout << "参数[" << argv[i-1] << "]缺少附加参数. (类型:IP地址 缺省:" << from_ipaddr_to_str(args[j].extargs_ipaddr_default) << ")" << endl;
				return -1;

			}
			unsigned int tempadd = 0, temp = 0,dotn = 0;
			int invalid = 0;
			string input = argv[i];
			int time = 1;
			int zero= 0;
			if (input[0] == '.' || input[input.length() - 1] == '.')
				invalid = 1;
			else {
				for (int i = input.size() - 1; i >= 0; i--) {
					if (zero && input[i] == '.'&&temp) {
						invalid = 1;
						break;
					}
					else
						zero=0;
					if (input[i] != '.' && (input[i] < '0' || input[i]>'9')) {
						invalid = 1;
						break;
					}
					if (input[i] == '.') {
						if (input[i - 1] == '.') {
							invalid = 1;
							break;
						}
						if (dotn >= 3) {
							invalid = 1;
							break;
						}
						tempadd += (temp << (8 * dotn));
						temp = 0;
						time = 1;
						dotn++;
						continue;
					}
					temp += (input[i] - '0') * time;
					if (input[i]=='0')
						zero = 1;
					time *= 10;
					if (temp > 255) {
						invalid = 1;
						break;
					}
				}
				tempadd += (temp << (8 * 3));
			}
			if (invalid||dotn<3) {
				if (args[j].extargs_type == ST_EXTARGS_TYPE::ipaddr_with_error) {
					cout << "参数[" << argv[i - 1] << "]的附加参数值(" << argv[i] << ")非法. (类型:IP地址)" << endl;
					return -1;
				}
				else {
					args[j].extargs_ipaddr_value = args[j].extargs_ipaddr_default;
					args[j].value_length = args[j].default_length;
				}
			}
			else {
				args[j].extargs_ipaddr_value = tempadd;
				args[j].value_length = args[j].get_str_ipaddr().length();
			}
			args[j].args_existed = 1;
		}
		else if (args[j].extargs_type == ST_EXTARGS_TYPE::str
			|| args[j].extargs_type == ST_EXTARGS_TYPE::str_with_set_default || args[j].extargs_type == ST_EXTARGS_TYPE::str_with_set_error) {
			if (args[j].args_existed) {
				cout << "参数[" << args[j].args_name << "]重复." << endl;
				return -1;
			}
			if (i + args[j].extargs_num >= argc) {
				if (args[j].extargs_type == ST_EXTARGS_TYPE::str)
					cout << "参数[" << argv[i] << "]的附加参数不足. (类型:string" << (args[j].extargs_string_default.length() ? " 缺省:" : "") << args[j].extargs_string_default << ")" << endl;
				else {
					cout << "参数[" << argv[i] << "]的附加参数不足. (类型:string, 可取值[";
					string* p = args[j].extargs_string_set;
					cout << *p;
					p++;
					while (p->length()) {
						cout << "/" << *p;
						p++;
					}
					if (args[j].extargs_type == ST_EXTARGS_TYPE::str_with_set_default)
						cout << "] 缺省:" << args[j].extargs_string_default << ")" << endl;
					else
						cout << "])" << endl;
				}
				return -1;
			}
			int arg_pos = i;
			i++;//只考虑了参数数量为1的情况
			string input(argv[i]);
			if (input.length() >= 2 && input[0] == '-' && input[1] == '-') {
				if (args[j].extargs_type == ST_EXTARGS_TYPE::str)
					cout << "参数[" << argv[arg_pos] << "]缺少附加参数. (类型:string" << (args[j].extargs_string_default.length() ? " 缺省:" : "") << args[j].extargs_string_default << ")" << endl;
				else {
					cout << "参数[" << argv[arg_pos] << "]缺少附加参数. (类型:string, 可取值[";
					string* p = args[j].extargs_string_set;
					cout << *p;
					p++;
					while (p->length()) {
						cout << "/" << *p;
						p++;
					}
					if (args[j].extargs_type == ST_EXTARGS_TYPE::str_with_set_default)
						cout << "] 缺省:" << args[j].extargs_string_default << ")" << endl;
					else
						cout << "])" << endl;
				}
				return -1;
			}
			int flag = (input[0] == '"');
			if (flag) {
				input.erase(0, 1);
				if (input.find('"') > 0) {
					flag = 0;
					int r = 0;
					for (unsigned int i = 0; i < input.size(); i++) {
						if (input[r] == '"') {
							input.erase(r);
							r--;
						}
						r++;
					}
				}
			}
			while (flag && (i + 1 < argc)) {
				i++;
				string temp;
				cin >> temp;
				if (temp.find('"') > 0) {
					flag = 0;
					int r = 0;
					for (unsigned int i = 0; i < input.size(); i++) {
						if (input[r] == '"') {
							input.erase(r);
							r--;
						}
						r++;
					}
				}
				input += temp;
			}
			if (args[j].extargs_type == ST_EXTARGS_TYPE::str) {
				args[j].extargs_string_value = input;
				args[j].value_length = input.length();
			}
			else {
				int k = 0;
				while (args[j].extargs_string_set[k].length()) {
					if (input == args[j].extargs_string_set[k])
						break;
					k++;
				}
				if (args[j].extargs_string_set[k].length()) {
					args[j].extargs_string_value = input;
					args[j].value_length = input.length();
				}
				else
					if (args[j].extargs_type == ST_EXTARGS_TYPE::str_with_set_default) {
						args[j].extargs_string_value = args[j].extargs_string_default;
						args[j].value_length = args[j].default_length;
					}
					else {
						cout << "参数[" << argv[arg_pos] << "]的附加参数值(" << input << ")非法. (类型:string, 可取值[";
						string* p = args[j].extargs_string_set;
						cout << *p;
						p++;
						while (p->length()) {
							cout << "/" << *p;
							p++;
						}
						cout << "])" << endl;
						return -1;
					}
			}
			args[j].args_existed = 1;
		}
		i++;
	}
	return i; //此句根据需要修改
}


/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：友元函数
***************************************************************************/
int args_analyse_print(const args_analyse_tools* const args)
{
	const char* header[6] = HEADER;
	int i = 0;
	int max_args_name_length = 4, max_type_length = 4, max_default_length = 7, max_exists_length = 6, max_value_length = 5, max_range_set_length = 9;
	while (args[i].extargs_type != ST_EXTARGS_TYPE::null) {
		if (args[i].args_name_length > max_args_name_length)
			max_args_name_length = args[i].args_name_length;
		if (args[i].type_length > max_type_length)
			max_type_length = args[i].type_length;
		if (args[i].default_length > max_default_length)
			max_default_length = args[i].default_length;
		if (args[i].exists_length > max_exists_length)
			max_exists_length = args[i].exists_length;
		if (args[i].value_length > max_value_length)
			max_value_length = args[i].value_length;
		if (args[i].range_set_length > max_range_set_length)
			max_range_set_length = args[i].range_set_length;
		i++;
	}
	int sum = 7 + max_args_name_length + max_type_length + max_default_length + max_exists_length + max_value_length + max_range_set_length;
	cout << setiosflags(ios::left);
	cout << setw(sum) << setfill('=') << "=" << setfill(' ') << endl;
	cout << TAB << setw(max_args_name_length) << header[0] << TAB << setw(max_type_length) << header[1]
		<< TAB << setw(max_default_length) << header[2] << TAB << setw(max_exists_length) << header[3]
		<< TAB << setw(max_value_length) << header[4] << TAB << header[5] << endl;
	cout << setw(sum) << setfill('=') << "=" << setfill(' ') << endl;
	i = 0;
	while (args[i].extargs_type != ST_EXTARGS_TYPE::null) {
		cout << TAB << setw(max_args_name_length) << args[i].args_name << TAB << setw(max_type_length) << args[i].type_name
			<< TAB << setw(max_default_length);
		switch (args[i].extargs_type) {
			case ST_EXTARGS_TYPE::boolean:
				cout << (args[i].extargs_bool_default ? "true" : "false");
				break;
			case ST_EXTARGS_TYPE::int_with_default:
				cout << args[i].extargs_int_default;
				break;
			case ST_EXTARGS_TYPE::int_with_error:
				cout << "/";
				break;
			case ST_EXTARGS_TYPE::int_with_set_default:
				cout << args[i].extargs_int_default;
				break;
			case ST_EXTARGS_TYPE::int_with_set_error:
				cout << "/";
				break;
			case ST_EXTARGS_TYPE::str:
				cout << (args[i].extargs_string_default.length() ? args[i].extargs_string_default : "/");
				break;
			case ST_EXTARGS_TYPE::str_with_set_default:
				cout << args[i].extargs_string_default;
				break;
			case ST_EXTARGS_TYPE::str_with_set_error:
				cout << "/";
				break;
			case ST_EXTARGS_TYPE::ipaddr_with_default:
				cout << from_ipaddr_to_str(args[i].extargs_ipaddr_default);
				break;
			case ST_EXTARGS_TYPE::ipaddr_with_error:
				cout << "/";
				break;
		}
		cout << TAB << setw(max_exists_length) << (args[i].args_existed ? '1' : '0') << TAB << setw(max_value_length);
		switch (args[i].extargs_type) {
			case ST_EXTARGS_TYPE::boolean:
				cout << (args[i].args_existed ? "true" : "/");
				break;
			case ST_EXTARGS_TYPE::int_with_default:
				if (args[i].args_existed)
					cout << args[i].extargs_int_value;
				else
					cout << "/";
				break;
			case ST_EXTARGS_TYPE::int_with_error:
				if (args[i].args_existed)
					cout << args[i].extargs_int_value;
				else
					cout << "/";
				break;
			case ST_EXTARGS_TYPE::int_with_set_default:
				if (args[i].args_existed)
					cout << args[i].extargs_int_value;
				else
					cout << "/";
				break;
			case ST_EXTARGS_TYPE::int_with_set_error:
				if (args[i].args_existed)
					cout << args[i].extargs_int_value;
				else
					cout << "/";
				break;
			case ST_EXTARGS_TYPE::str:
				cout << (args[i].args_existed ? args[i].extargs_string_value : "/");
				break;
			case ST_EXTARGS_TYPE::str_with_set_default:
				cout << (args[i].args_existed ? args[i].extargs_string_value : "/");
				break;
			case ST_EXTARGS_TYPE::str_with_set_error:
				cout << (args[i].args_existed ? args[i].extargs_string_value : "/");
				break;
			case ST_EXTARGS_TYPE::ipaddr_with_default:
				cout << (args[i].args_existed ? args[i].get_str_ipaddr() : "/");
				break;
			case ST_EXTARGS_TYPE::ipaddr_with_error:
				cout << (args[i].args_existed ? args[i].get_str_ipaddr() : "/");
				break;
		}
		cout << TAB;
		int* p = args[i].extargs_int_set;
		string* s = args[i].extargs_string_set;
		string* t = args[i].extargs_string_set;
		switch (args[i].extargs_type) {
			case ST_EXTARGS_TYPE::boolean:
				cout << "/";
				break;
			case ST_EXTARGS_TYPE::int_with_default:
				cout << "[" << args[i].extargs_int_min << ".." << args[i].extargs_int_max << "]";
				break;
			case ST_EXTARGS_TYPE::int_with_error:
				cout << "[" << args[i].extargs_int_min << ".." << args[i].extargs_int_max << "]";
				break;
			case ST_EXTARGS_TYPE::int_with_set_default:
				cout << *p;
				p++;
				while (*p != INVALID_INT_VALUE_OF_SET) {
					cout << "/" << *p;
					p++;
				}
				break;
			case ST_EXTARGS_TYPE::int_with_set_error:
				cout << *p;
				p++;
				while (*p != INVALID_INT_VALUE_OF_SET) {
					cout << "/" << *p;
					p++;
				}
				break;
			case ST_EXTARGS_TYPE::str:
				cout << "/";
				break;
			case ST_EXTARGS_TYPE::str_with_set_default:
				cout << *s;
				s++;
				while (s->length()) {
					cout << "/" << *s;
					s++;
				}
				break;
			case ST_EXTARGS_TYPE::str_with_set_error:
				cout << *t;
				t++;
				while (t->length()) {
					cout << "/" << *t;
					t++;
				}
				break;
			case ST_EXTARGS_TYPE::ipaddr_with_default:
				cout << "/";
				break;
			case ST_EXTARGS_TYPE::ipaddr_with_error:
				cout << "/";
				break;
		}
		cout << endl;
		i++;
	}
	cout << setw(sum) << setfill('=') << "=" << setfill(' ') << endl;
	cout << endl;//demo有一行空白
	return 0; //此句根据需要修改
}

#endif // !ENABLE_LIB_COMMON_TOOLS
