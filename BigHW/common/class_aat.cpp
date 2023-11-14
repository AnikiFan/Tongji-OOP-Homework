/* ѧ�� ���� �༶ */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include "../include/class_aat.h"
//���б�Ҫ�����Լ�������ͷ�ļ�
using namespace std;

#if !ENABLE_LIB_COMMON_TOOLS //��ʹ��lib����Ч

/* ---------------------------------------------------------------
	 �������������Ҫstatic�������ڲ������ã�
   ---------------------------------------------------------------- */
/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����null
 ***************************************************************************/
args_analyse_tools::args_analyse_tools()
{
	extargs_type =  ST_EXTARGS_TYPE::null;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����boolean
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const ST_EXTARGS_TYPE type, const int ext_num, const bool def)
{
	args_name = name;
	extargs_type = type;
	extargs_num = ext_num;
	extargs_bool_default = def;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����int_with_default��int_with_error
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
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����int_with_set_default��int_with_set_error
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
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����str��ipaddr_with_default��ipaddr_with_error
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
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����str_with_set_default��str_with_set_error
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
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
 ***************************************************************************/
args_analyse_tools::~args_analyse_tools()
{
}

/* ---------------------------------------------------------------
	 ����AAT���Զ����Ա������ʵ�֣�private��
   ---------------------------------------------------------------- */

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ������ʵ�֣���Ҫ��
 ***************************************************************************/
const string args_analyse_tools::get_name() const
{
	return this->args_name;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ������!!��ֻ����0/1
			��ʵ�֣���Ҫ��
 ***************************************************************************/
const int args_analyse_tools::existed() const
{
	return !!this->args_existed;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ������ʵ�֣���Ҫ��
 ***************************************************************************/
const int args_analyse_tools::get_int() const
{
	return this->extargs_int_value;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ������ʵ�֣���Ҫ��
 ***************************************************************************/
const string args_analyse_tools::get_string() const
{
	return this->extargs_string_value;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ������ʵ�֣���Ҫ��
 ***************************************************************************/
const unsigned int args_analyse_tools::get_ipaddr() const
{
	return this->extargs_ipaddr_value;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ������ extargs_ipaddr_value ��ֵ�� 0x7f000001 תΪ "127.0.0.1"
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
	return ipaddr; //�˾������Ҫ�޸�
}


/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������follow_up_args���Ƿ��к�������
			0  ���޺�������
			1  ���к�������
  �� �� ֵ��
  ˵    ������Ԫ����
***************************************************************************/
int args_analyse_process(const int argc, const char* const *const argv, args_analyse_tools* const args, const int follow_up_args)
{
	int i = 1;
	while (i < argc) {
		int j = 0;
		if (strlen(argv[i]) < 3 || argv[i][0] != '-' || argv[i][1] != '-') {
			cout << "����[" << argv[i] << "]��ʽ�Ƿ�(����--��ͷ����Ч����)." << endl;
			return -1;
		}
		while (argv[i]!=args[j].args_name) {
			if (args[j].type == ST_EXTARGS_TYPE::NULL) {//��ƥ�����
				cout << "����["<<argv[i] << "]�Ƿ�." << endl;
				return -1;
			}
			j++;
		}
		if (args[j].exargs_type == ST_EXTARGS_TYPE::boolean) {//�˴�Ĭ��bool�Ͷ����������һ��Ϊ0
			if (args[j].args_existed) {
				cout << "����[" << args[j].args_name << "]�ظ�" << endl;
				return -1;
			}
			args_existed = 1;
		}
		else if (args[j].exargs_type == ST_EXTARGS_TYPE::int_with_default || args[j].exargs_type == ST_EXTARGS_TYPE::int_with_error
			||args[j].exargs_type == ST_EXTARGS_TYPE::int_with_set_default || args[j].exargs_type == ST_EXTARGS_TYPE::int_with_set_error) {
			if (args[j].args_existed) {
				cout << "����[" << args[j].args_name << "]�ظ�" << endl;
				return -1;
			}
			if (i+args[j].extargs_num >= argc) {
				if (args[j].exargs_type == ST_EXTARGS_TYPE::int_with_default || args[j].exargs_type == ST_EXTARGS_TYPE::int_with_error) 
					cout << "����[" << argv[i] << "]�ĸ��Ӳ�������. (����:int, ��Χ[" << args[j].int_min << ".." << args[j].int_max << "])" << endl;
				else {
					cout << "����[" << argv[i] << "]�ĸ��Ӳ�������. (����:int, ��ȡֵ[";
					int* p = args[j].extargs_int_set;
					cout << *p;
					p++;
					while (*p != INVALID_INT_VALUE_OF_SET)
						cout << "/" << *p;
					if (args[j].exargs_types == ST_EXTARGS_TYPE::int_with_set_default)
						cout << "] ȱʡ:" << args[j].extargs_int_default << ")" << endl;
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
						cout << "����[" << argv[i] << "]�ĸ��Ӳ�����������. (����:int, ��Χ[" << args[j].int_min << ".." << args[j].int_max << "])" << endl;
					else {
						cout << "����[" << argv[i] << "]�ĸ��Ӳ�����������. (����:int, ��ȡֵ[";
						int* p = args[j].extargs_int_set;
						cout << *p;
						p++;
						while (*p != INVALID_INT_VALUE_OF_SET)
							cout << "/" << *p;
						if (args[j].exargs_types == ST_EXTARGS_TYPE::int_with_set_default)
							cout << "] ȱʡ:" << args[j].extargs_int_default << ")" << endl;
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
						cout << "����[" << argv[i] << "]�ĸ��Ӳ���ֵ("<<temp<<")�Ƿ�. (����:int, ��Χ[" << args[j].int_min << ".." << args[j].int_max << "])" << endl;
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
							cout << "����[" << argv[i] << "]�ĸ��Ӳ�����������. (����:int, ��ȡֵ[";
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
	return 0; //�˾������Ҫ�޸�
}


/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ������Ԫ����
***************************************************************************/
int args_analyse_print(const args_analyse_tools* const args)
{
	return 0; //�˾������Ҫ�޸�
}

#endif // !ENABLE_LIB_COMMON_TOOLS
