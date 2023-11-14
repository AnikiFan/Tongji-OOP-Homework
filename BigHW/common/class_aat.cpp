/* 学号 姓名 班级 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include "../include/class_aat.h"
//如有必要，可以加入其它头文件
using namespace std;

#if !ENABLE_LIB_COMMON_TOOLS //不使用lib才有效

/* ---------------------------------------------------------------
	 允许加入其它需要static函数（内部工具用）
   ---------------------------------------------------------------- */
/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：null
 ***************************************************************************/
args_analyse_tools::args_analyse_tools()
{
	extargs_type =  ST_EXTARGS_TYPE::null;
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
	int n=0;
	int temp=0;
	if (type == ST_EXTARGS_TYPE::str)
		extargs_string_default = def;
	else
		for (int i = def.size()-1;i>0; i--) {
			if (def[i] == '.') {
				extargs_ipaddr_default += (temp / 16) << 2 * n + 1;
				extargs_ipaddr_default += (temp %16) << 2 * n ;
				n++;
				temp = 0;
			}
			temp *= 10;
			temp += def[i];
		}
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
	extargs_string_default =set[def_of_set_pos];
	extargs_string_set = (string*)set;
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
	string ipaddr();
	int h, t, o,temp;
	for (int i = 0; i < 3; i++) {
		o = extargs_ipaddr_value >> ((3 * i) + 1);
		t = extargs_ipaddr_value >> ((3 * i) + 2);
		h = extargs_ipaddr_value >> ((3 * i) + 3);
		temp = 100 * h + 10 * t + o;
		while (temp) {
			ipaddr.insert(ipaddr.begin(), temp%10+'0');
			temp /= 10;
		}
		ipaddr.insert(ipaddr.begin(), '.');
	}
	o = extargs_ipaddr_value >> ((3 * i) + 1);
	t = extargs_ipaddr_value >> ((3 * i) + 2);
	h = extargs_ipaddr_value >> ((3 * i) + 3);
	temp = 100 * h + 10 * t + o;
	while (temp) {
		ipaddr.insert(ipaddr.begin(), temp%10+'0');
		temp /= 10;
	}
	return ipaddr; //此句根据需要修改
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
int args_analyse_process(const int argc, const char* const *const argv, args_analyse_tools* const args, const int follow_up_args)
{
	int i = 1;
	while (i < argc) {
		int j = 0;
		if (strlen(argv[i]) < 3 || argv[i][0] != '-' || argv[i][1] != '-') {
			cout << "参数[" << argv[i] << "]格式非法(不是--开头的有效内容)." << endl;
			return -1;
		}
		while (argv[i]!=args[j].args_name) {
			if (args[j].type == ST_EXTARGS_TYPE::NULL) {//无匹配参数
				cout << "参数["<<argv[i] << "]非法." << endl;
				return -1;
			}
			j++;
		}
		if (args[j].exargs_type == ST_EXTARGS_TYPE::boolean) {//此处默认bool型额外参数数量一定为0
			if (args[j].args_existed) {
				cout << "参数[" << args[j].args_name << "]重复" << endl;
				return -1;
			}
			args_existed = 1;
		}
		else if (args[j].exargs_type == ST_EXTARGS_TYPE::int_with_default || args[j].exargs_type == ST_EXTARGS_TYPE::int_with_error
			||args[j].exargs_type == ST_EXTARGS_TYPE::int_with_set_default || args[j].exargs_type == ST_EXTARGS_TYPE::int_with_set_error) {
			if (args[j].args_existed) {
				cout << "参数[" << args[j].args_name << "]重复" << endl;
				return -1;
			}
			if (i+args[j].extargs_num >= argc) {
				if (args[j].exargs_type == ST_EXTARGS_TYPE::int_with_default || args[j].exargs_type == ST_EXTARGS_TYPE::int_with_error) 
					cout << "参数[" << argv[i] << "]的附加参数不足. (类型:int, 范围[" << args[j].int_min << ".." << args[j].int_max << "])" << endl;
				else {
					cout << "参数[" << argv[i] << "]的附加参数不足. (类型:int, 可取值[";
					int* p = args[j].extargs_int_set;
					cout << *p;
					p++;
					while (*p != INVALID_INT_VALUE_OF_SET)
						cout << "/" << *p;
					if (args[j].exargs_types == ST_EXTARGS_TYPE::int_with_set_default)
						cout << "] 缺省:" << args[j].extargs_int_default << ")" << endl;
					else
						cout << "])" << endl;
				}
				return -1;
			}
			i++;
			int k = 0;
			int temp = 0;
			while (argv[i][k]) {
				if (argv[i][k] < '0' || argv[i][k]>'9') {
					if (args[j].exargs_type == ST_EXTARGS_TYPE::int_with_default || args[j].exargs_type == ST_EXTARGS_TYPE::int_with_error) 
						cout << "参数[" << argv[i] << "]的附加参数不是整数. (类型:int, 范围[" << args[j].int_min << ".." << args[j].int_max << "])" << endl;
					else {
						cout << "参数[" << argv[i] << "]的附加参数不是整数. (类型:int, 可取值[";
						int* p = args[j].extargs_int_set;
						cout << *p;
						p++;
						while (*p != INVALID_INT_VALUE_OF_SET)
							cout << "/" << *p;
						if (args[j].exargs_types == ST_EXTARGS_TYPE::int_with_set_default)
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
			if (args[j].exargs_type == ST_EXTARGS_TYPE::int_with_default || args[j].exargs_type == ST_EXTARGS_TYPE::int_with_error) {
				if (temp<args[j].int_min || temp> args[j].int_max)
					if (args[j].exargs_type == ST_EXTARGS_TYPE::int_with_default)
						extargs_int_value = extargs_int_default;
					else {
						cout << "参数[" << argv[i] << "]的附加参数值("<<temp<<")非法. (类型:int, 范围[" << args[j].int_min << ".." << args[j].int_max << "])" << endl;
						return -1;
					}
				else
					extargs_int_value = temp;
			}
			else {
				int* p = args[j].exargs_int_set;
				while (*p != INVALID_INT_VALUE_OF_SET) {
					if (*p == temp)
						break;
					p++;
				}
				if (*p == INVALID_INT_VALUE_OF_SET)
					if (type == ST_EXTARGS_TYPE::int_with_default)
						extargs_int_value = extargs_int_default;
					else {
							cout << "参数[" << argv[i] << "]的附加参数不是整数. (类型:int, 可取值[";
						int* p = args[j].extargs_int_set;
						cout << *p;
						p++;
						while (*p != INVALID_INT_VALUE_OF_SET)
							cout << "/" << *p;
						cout << "])" << endl;
						return -1;
					}
				else
					args[j].extargs_int_value = temp;
			}
		args[j].args_existed = 1;
		}
		else if (args[j].exargs_type == ST_EXTARGS_TYPE::ipaddr_default || args[j].exargs_type == ST_EXTARGS_TYPE::ipaddr_error) {

		}
		else if (args[j].exargs_type == ST_EXTARGS_TYPE::str ) {
		}
		else if (args[j].exargs_type == st_extargs_type::str_with_set_default || args[j].exargs_type == st_extargs_type::str_with_set_error) {

		}
	}
	return 0; //此句根据需要修改
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
	return 0; //此句根据需要修改
}

#endif // !ENABLE_LIB_COMMON_TOOLS
