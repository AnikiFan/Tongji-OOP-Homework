/* 2254298 大数据 范潇 */
/*

打印的信息框架：

1.查询对象信息
2.汇总信息
3.详细信息
（打印顺序是132）

1 查询对象信息：

当stu，file均不为all时：
课号、学生数量、源文件名
例：
课号 : 10108001 学生数量 : 1 源文件名 : 16-b2-2.hpp <回车>

当stu特定，file为all时，
编号、学号、姓名、课号、文件数量
例：
1  : 学号-2254298 姓名-范潇 课号-10108001 文件数量-69

当学生为all，文件特定时：
课号、学生数量、源文件名
例：
课号 : 10108001 学生数量 : 90 源文件名 : 16-b2-2 <回车>

当学生，文件均为all时：
编号、学号、姓名、课号、文件数量
例：
1  : 学号-2254298 姓名-范潇 课号-10108001 文件数量-69

2 汇总信息：
当stu，file均不为all时：
例：
全部通过1/1个学生，本次通过1个
================
详细信息
================
  正确 : 1
================

当stu特定，file为all时，
例：
全部通过69/69个文件，本次通过69个
----------------
学生详细信息
----------------
  正确 : 69
----------------

当学生为all，文件特定时：
例：
检查通过80/90个学生，本次通过80个
======================================
详细信息
======================================
						正确 : 80
					  未提交 : 9
  源文件格式不正确(非GB编码) : 1
======================================


当学生，文件均为all时：
例：
共完成90个学生的检查，文件总数:6210，通过总数:5348，本次通过5348个
======================================
整体详细信息
======================================
						正确 : 5348
					  未提交 : 854
  源文件格式不正确(非GB编码) : 8
======================================

注：当有格式不正确信息时，长度会发生变化
========================
详细信息
========================
		  正确 : 1
		未提交 : 6
  首行检查出错 : 83
========================
======================================
整体详细信息
======================================
						正确 : 3375
					  未提交 : 619
  源文件格式不正确(非GB编码) : 8
			  首行不是注释行 : 231
				首行不是三项 : 4
				首行检查出错 : 623
======================================
3 详细信息：

	单文件时：
	1  : 2254298/范潇     : 正确
	多文件时
	 12-b1-1.cpp                 : 正确
  12-b1-2.cpp                 : 正确
  12-b2.cpp                   : 正确

 错误信息：
  16-b2-2.hpp                 : 源文件格式不正确(非GB编码)
 15-b5-1.cpp                 : 首行不是注释行 [#include<iostream>]
   13-b9-linear_list_sq.h      : 首行学号不匹配 姓名不匹配 班级不匹配  [//#define ELEMTYPE_IS_INT                //不定义也行]
  17-b1-main.cpp              : 首行不是三项 [/*2153538 刘博*]
 display xxxxx
 第一个x：1时会将正确的名单打印
第二个x：1时会将未提交的名单打印
第三个x：1时会将错误的名单打印
第四个x：汇总信息，即正确、未提交、错误个数，无论是0还是1都会打印
如果汇总信息中有一行为0，则不显示
第五个x：严重错误指的是source文件夹不存在，但是无论是0还是1都会报错

secondline:
display只决定是否要再详细详细前打印为提交名单,交了就算正确
==================
详细信息
==================
	正确 : 82
  未提交 : 8
==================


交叉检查结果：
1  : 1850772 张哲源
		2153731 胡语诺
		2154270 赵楚钧
		2152988 杨恺铭
		2152202 戚峻榕
		2150792 牛禄阳
2  : 1851107 蓝振楠
3  : 1852524 林葳崴
4  : 1950617 罗楠
		2154146 吴金轩
		2152969 李咏桓  抛弃了你
		2253328 许翰林  抛弃了你
		2152153 李欣晨
		2152768 袁锐声

		--action secondline --cno 10108001 --stu all --file all --display 00000
HW_Check_SecondLine 只能针对单文件

C:\Users\15800\Desktop\OOP\大作业\学生作业检查>C:\Users\15800\Desktop\OOP\大作业\学生作业检查\hw_check_demo.exe --action secondline --cno 10108001 --stu 2254298 --file 15-b4.cpp --display 00000
HW_Check_SecondLine 只能针对全体学生

C:\Users\15800\Desktop\OOP\大作业\学生作业检查>C:\Users\15800\Desktop\OOP\大作业\学生作业检查\hw_check_demo.exe --action secondline --cno 10108001 --stu 2254298 --file all --display 00000
HW_Check_SecondLine 只能针对单文件
*/
#include<iostream>
#include<iomanip>
#include<io.h>
#include<sstream>
#include"../include/class_aat.h"
#include"../include/class_crt.h"
#include "../include_mariadb_x86/mysql/mysql.h"      // mysql特有
using namespace std;
#define ACT_Max 10
enum OPT_ARGS {
	OPT_ARGS_HELP = 0,
	OPT_ARGS_DEBUG,
	OPT_ARGS_ACTION,
	OPT_ARGS_CNO,
	OPT_ARGS_STU,
	OPT_ARGS_FILE,
	OPT_ARGS_CHAPTER,
	OPT_ARGS_WEEK,
	OPT_ARGS_DISPLAY,
	OPT_ARGS_CFGFILE
};
/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
 ***************************************************************************/
static void usage(const char* const full_procname)
{
	const char* procname = strrchr(full_procname, '\\');
	if (procname == NULL)
		procname = full_procname;

	const int wkey = 7 + strlen(procname) + 1;
	const int wopt = 7 + strlen(procname) + 4;
	cout << endl;

	cout << "Usage: " << procname << " 必选项/可选项" << endl;
	cout << endl;
	cout << setw(wkey) << ' ' << "必选项：指定操作" << endl;
	cout << setw(wopt) << ' ' << "--action opname : 支持的opname如下" << endl;
	cout << setw(wopt) << ' ' << "\t base              : 基础检查(文件是否提交、是否被改动、编码是否正确)" << endl;
	cout << setw(wopt) << ' ' << "\t firstline         : 首行检查（仅源程序文件需要）" << endl;
	cout << setw(wopt) << ' ' << "\t secondline        : 次行检查（仅部分源程序文件需要）" << endl;

	cout << setw(wkey) << ' ' << "必选项：指定课号" << endl;
	cout << setw(wopt) << ' ' << "--cno course_no     : 课号" << endl;

	cout << setw(wkey) << ' ' << "必选项：指定学生" << endl;
	cout << setw(wopt) << ' ' << "--stu no/all        : 指定单个/全部(7位数字为学号,all为全部)" << endl;

	cout << setw(wkey) << ' ' << "必选项：指定文件" << endl;
	cout << setw(wopt) << ' ' << "--file filename/all : 具体文件名/全部(all为全部,其余为具体文件名)" << endl;

	cout << setw(wkey) << ' ' << "可选项：" << endl;
	cout << setw(wopt) << ' ' << "--chapter n         : 在--file的基础上再进行章节的筛选(无/-1则全部章节,可与--week共存)" << endl;
	cout << setw(wopt) << ' ' << "--week n            : 在--file的基础上再进行周次的筛选(无/-1则全部周次,可与--chapter共存)" << endl;
	cout << setw(wopt) << ' ' << "--display xxxxx     : 每位0/1分别表示正常信息/未提交信息/错误信息/汇总信息/严重错误信息" << endl;
	cout << setw(wopt) << ' ' << "--cfgfile filename  : 指定配置文件名(缺省:hw_check.conf)" << endl;
	cout << endl;

	const char* DEMO_CNO = "10108001";
	const char* DEMO_SRC_FNAME = "12-b1.cpp";
	const char* DEMO_STUNO = "2259999";

	cout << "e.g.   " << procname << " --action base --cno " << DEMO_CNO << " --stu all --file all             : 检查" << DEMO_CNO << "所有学生的所有作业的基本信息" << endl;
	cout << "       " << procname << " --action base --cno " << DEMO_CNO << " --stu all --file all --chapter 4 : 检查" << DEMO_CNO << "所有学生的第4章作业的基本信息" << endl;
	cout << "       " << procname << " --action base --cno " << DEMO_CNO << " --stu all --file all --week 6    : 检查" << DEMO_CNO << "所有学生的第6周作业的基本信息" << endl;
	cout << "       " << procname << " --action base --cno " << DEMO_CNO << " --stu " << DEMO_STUNO << " --file all         : 检查" << DEMO_CNO << "的" << DEMO_STUNO << "学生的所有作业的基本信息" << endl;
	cout << "       " << procname << " --action base --cno " << DEMO_CNO << " --stu " << DEMO_STUNO << " --file " << DEMO_SRC_FNAME << "   : 检查" << DEMO_CNO << "的" << DEMO_STUNO << "学生的" << DEMO_SRC_FNAME << "作业的基本信息" << endl;
	cout << endl;

	cout << "       " << procname << " --action firstline --cno " << DEMO_CNO << " --stu all --file all             : 检查" << DEMO_CNO << "所有学生的所有作业的首行信息" << endl;
	cout << "       " << procname << " --action firstline --cno " << DEMO_CNO << " --stu all --file all --chapter 4 : 检查" << DEMO_CNO << "所有学生的第4章作业的首行信息" << endl;
	cout << "       " << procname << " --action firstline --cno " << DEMO_CNO << " --stu all --file all --week 6    : 检查" << DEMO_CNO << "所有学生的第6周作业的首行信息" << endl;
	cout << "       " << procname << " --action firstline --cno " << DEMO_CNO << " --stu " << DEMO_STUNO << " --file all         : 检查" << DEMO_CNO << "的" << DEMO_STUNO << "学生的所有作业的首行信息" << endl;
	cout << "       " << procname << " --action firstline --cno " << DEMO_CNO << " --stu " << DEMO_STUNO << " --file " << DEMO_SRC_FNAME << "   : 检查" << DEMO_CNO << "的" << DEMO_STUNO << "学生的" << DEMO_SRC_FNAME << "作业的首行信息" << endl;
	cout << endl;

	cout << "       " << procname << " --action secondline --cno " << DEMO_CNO << " --stu all --file " << DEMO_SRC_FNAME << " : 检查" << DEMO_CNO << "的所有学生的" << DEMO_SRC_FNAME << "作业的次行信息" << endl;
	cout << endl;

	cout << "       " << procname << " --cfgfile E:\\test\\my.conf --action base --cno " << DEMO_CNO << " --stu all --file all : 检查" << DEMO_CNO << "所有学生的所有作业的基本信息(指定配置文件)" << endl;
	cout << endl;


	cout << endl;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
 ***************************************************************************/
int main(int argc, char** argv)
{
	/*
	总体逻辑是根据用户指定的学生和文件，到数据库中查找，以查找到的为准，再进行比较

	stu:正确，file错误，则
课号 : 10108001 学生数量 : 0 源文件名 : 15-b.cpp

全部通过0/0个学生，本次通过0个
============
详细信息
============
============

stu all，file错误，则
检查通过0/90个学生，本次通过0个
==================
详细信息
==================
  未提交 : 90
==================

	*/
	/*------------------------------------------------参数处理--------------------------------------------------------------------*/
	const string Action_Name[ACT_Max + 1] = { "base","firstline","secondline","" }; //也可以根据需要，放入头文件中以便共享 

	args_analyse_tools args[] = {
		args_analyse_tools("--help",     ST_EXTARGS_TYPE::boolean,            0, false),
		args_analyse_tools("--debug",    ST_EXTARGS_TYPE::boolean,            0, false),
		args_analyse_tools("--action",   ST_EXTARGS_TYPE::str_with_set_error, 1, -1, Action_Name),	//参数-1无意义，表示无默认，必须指定
		args_analyse_tools("--cno",      ST_EXTARGS_TYPE::str,                1, string("")),
		args_analyse_tools("--stu",      ST_EXTARGS_TYPE::str,                1, string("")),
		args_analyse_tools("--file",     ST_EXTARGS_TYPE::str,                1, string("")),
		args_analyse_tools("--chapter",  ST_EXTARGS_TYPE::int_with_error,     1, -1, -1, 99), //参数-1表示不进行章节选择
		args_analyse_tools("--week",     ST_EXTARGS_TYPE::int_with_error,     1, -1, -1, 20), //参数-1表示不进行周次选择
		args_analyse_tools("--display",  ST_EXTARGS_TYPE::str,                1, string("11111")),
		args_analyse_tools("--cfgfile",  ST_EXTARGS_TYPE::str,                1, string("hw_check.conf")),
		args_analyse_tools()  //最后一个，用于结束
	};
	int need_fixed_args = 0;	//试试改为1
	int cur_argc;

	/* 最后一个参数：1-表示除选项参数外，还需要其它参数
				  0-表示除选项参数外，不需要其它参数 */
	if ((cur_argc = args_analyse_process(argc, argv, args, need_fixed_args)) < 0)
	{
		//错误信息在函数中已打印
		return -1;
	}

	/* 参数分析完成后的错误处理 */
	if (need_fixed_args) {
		if (cur_argc == argc) {  //说明后面没有跟需要的固定参数
			cout << "指定需要固定参数，但未给出" << endl;
			return -1;
		}
	}
	/* 打印当前参数的分析结果 */
	if (args[OPT_ARGS_ACTION].existed() == 0) {
		usage(argv[0]);
		cout << "必须给出指定操作." << endl;
		return -1;
	}
	if (args[OPT_ARGS_CNO].existed() == 0) {
		usage(argv[0]);
		cout << "必须给出指定课号." << endl;
		return -1;
	}
	if (args[OPT_ARGS_STU].existed() == 0) {
		usage(argv[0]);
		cout << "必须给出指定学生学号." << endl;
		return -1;
	}
	if (args[OPT_ARGS_FILE].existed() == 0) {
		usage(argv[0]);
		cout << "必须给出待检查文件名." << endl;
		return -1;
	}
	/* 判断参数组合是否合法*/
	if (args[OPT_ARGS_ACTION].get_string() == "secondline")
		if (args[OPT_ARGS_FILE].get_string() == "all") {
			usage(argv[0]);
			cout << "HW_Check_SecondLine 只能针对单文件" << endl;
			return -1;
		}
		else if (args[OPT_ARGS_STU].get_string() != "all") {
			usage(argv[0]);
			cout << "HW_Check_SecondLine 只能针对全体学生" << endl;
			return -1;
		}
	if (args[OPT_ARGS_FILE].get_string() != "all" && (args[OPT_ARGS_CHAPTER].existed() || args[OPT_ARGS_WEEK].existed())) {
		usage(argv[0]);
		cout << "参数[--chapter/--week]不能出现在[--file 单个文件名]时." << endl;
		return -1;
	}
	int correct = 1, no = 1, wrong = 1;
	if (args[OPT_ARGS_DISPLAY].existed()) {
		if (args[OPT_ARGS_DISPLAY].get_string().length() != 5) {
			usage(argv[0]);
			cout << "参数[--display]的长度不正确，只能是[5]位的0/1." << endl;
			return -1;
		}
		for (int i = 0; i < 5; i++)
			if (args[OPT_ARGS_DISPLAY].get_string()[i] != '0' && args[OPT_ARGS_DISPLAY].get_string()[i] != '1') {
				usage(argv[0]);
				cout << "参数[--display]的长度不正确，只能是[5]位的0/1." << endl;
				return -1;
			}
		correct = args[OPT_ARGS_DISPLAY].get_string()[0] - '0';
		no = args[OPT_ARGS_DISPLAY].get_string()[1] - '0';
		wrong = args[OPT_ARGS_DISPLAY].get_string()[2] - '0';
	}
	/*--------------------------------------------配置读取------------------------------------------------*/
	cfgfile_read_tools cfg(args[OPT_ARGS_CFGFILE].get_string());
	if (cfg.is_open() == 0) {
		cout << "无法打开配置文件 [" << args[OPT_ARGS_CFGFILE].get_string() << "]，结束运行." << endl;
		return -1;
	}
	const char* const group = "[数据库]";
	char src_folder[MAXN];
	char dbserver[MAXN];
	char dbuser[MAXN];
	char dbpasswd[MAXN];
	char dbname[MAXN];
	if (cfg.item_get_value(group, "db_host", "10.80.42.244", dbserver, MAXN) == -1) {
		cout << "读取db_host发生错误" << endl;
		return -1;
	}
	if (cfg.item_get_value(group, "db_user", "hwcheck", dbuser, MAXN) == -1) {
		cout << "读取db_user发生错误" << endl;
		return -1;
	}
	if (cfg.item_get_value(group, "db_passwd", "hw_CheCk-For23241*oOP", dbpasswd, MAXN) == -1) {
		cout << "读取db_passwd发生错误" << endl;
		return -1;
	}
	if (cfg.item_get_value(group, "db_name", "homework", dbname, MAXN) == -1) {
		cout << "读取db_name发生错误" << endl;
		return -1;
	}
	if (cfg.item_get_value("[文件目录]", "src_rootdir", "G:\\23241-source\\", src_folder, MAXN) == -1) {
		cout << "读取src_rootdir发生错误" << endl;
		return -1;
	}
	if (_access(src_folder, 0) != 0) {
		cout << "[--严重错误--] 源文件根目录 [" << src_folder << "] 不存在(2/No such file or directory)." << endl;
		return -1;
	}
	/*--------------------------------------------初始化数据库------------------------------------------------*/
	MYSQL* mysql;
	MYSQL_RES* result;
	MYSQL_ROW  row;
	const  char* const encoding = "gbk";

	/* 初始化 mysql 变量，失败返回NULL */
	if ((mysql = mysql_init(NULL)) == NULL) {
		cout << "mysql_init failed" << endl;
		return -1;
	}

	/* 连接数据库，失败返回NULL
		1、mysqld没运行
		2、没有指定名称的数据库存在 */
	if (mysql_real_connect(mysql, dbserver, dbuser, dbpasswd, dbname, 0, NULL, 0) == NULL) {
		cout << "mysql_real_connect failed(" << mysql_error(mysql) << ")" << endl;
		return -1;
	}
	/* 设置字符集，否则读出的字符乱码 */
	mysql_set_character_set(mysql, encoding);
	/*--------------------------------------------确认检查名单------------------------------------------------*/
	vector<student> stu_list;
	vector<file>file_list;
	if (args[OPT_ARGS_STU].get_string() != "all") {
		string key;
		key = "select stu_name, stu_class_sname from view_hwcheck_stulist where stu_no = \"" + args[OPT_ARGS_STU].get_string()
			+ "\" and stu_cno = \"" + args[OPT_ARGS_CNO].get_string() + "\"";
		if (mysql_query(mysql, key.c_str())) {
			cout << "mysql_query failed(" << mysql_error(mysql) << ")" << endl;
			mysql_close(mysql);
			return -1;
		}
		if ((result = mysql_store_result(mysql)) == NULL) {
			cout << "mysql_store_result failed" << endl;
			mysql_free_result(result);
			mysql_close(mysql);
			return -1;
		}
		if (!(int)mysql_num_rows(result)) {
			cout << "本次操作的学生数量为0/文件数量为0，未执行" << endl;
			mysql_free_result(result);
			mysql_close(mysql);
			return -1;
		}
		row = mysql_fetch_row(result);
		student stu;
		stu.code = args[OPT_ARGS_STU].get_string();
		stu.stu_name = row[0];
		stu.major = row[1];
		stu_list.push_back(stu);
		mysql_free_result(result);
	}
	else {
		string key;
		key = "select stu_no, stu_name, stu_class_sname from view_hwcheck_stulist where stu_cno = \"" + args[OPT_ARGS_CNO].get_string() + "\"";
		if (mysql_query(mysql, key.c_str())) {
			cout << "mysql_query failed(" << mysql_error(mysql) << ")" << endl;
			mysql_close(mysql);
			return -1;
		}
		if ((result = mysql_store_result(mysql)) == NULL) {
			cout << "mysql_store_result failed" << endl;
			mysql_free_result(result);
			mysql_close(mysql);
			return -1;
		}
		while ((row = mysql_fetch_row(result)) != NULL) {
			student stu;
			stu.code = row[0];
			stu.stu_name = row[1];
			stu.major = row[2];
			stu_list.push_back(stu);
		}
		mysql_free_result(result);
	}
	if (args[OPT_ARGS_FILE].get_string() != "all") {
		string key;
		key = "select * from view_hwcheck_hwlist where hw_filename = \"" + args[OPT_ARGS_FILE].get_string()
			+ "\" and hw_cno = \"" + args[OPT_ARGS_CNO].get_string() + "\"";
		if (mysql_query(mysql, key.c_str())) {
			cout << "mysql_query failed(" << mysql_error(mysql) << ")" << endl;
			mysql_close(mysql);
			return -1;
		}
		if ((result = mysql_store_result(mysql)) == NULL) {
			cout << "mysql_store_result failed" << endl;
			mysql_free_result(result);
			mysql_close(mysql);
			return -1;
		}
		if (!(int)mysql_num_rows(result)) {
			cout << "本次操作的学生数量为0/文件数量为0，未执行" << endl;
			mysql_free_result(result);
			mysql_close(mysql);
			return -1;
		}
		file hw;
		hw.file_name = args[OPT_ARGS_FILE].get_string();
		if (args[OPT_ARGS_FILE].get_string().substr(args[OPT_ARGS_FILE].get_string().length() - 3, args[OPT_ARGS_FILE].get_string().length() - 1) == "rar")
			hw.type = RAR;
		else if (args[OPT_ARGS_FILE].get_string().substr(args[OPT_ARGS_FILE].get_string().length() - 3, args[OPT_ARGS_FILE].get_string().length() - 1) == "pdf")
			hw.type = PDF;
		else
			hw.type = TXT;
		file_list.push_back(hw);
		mysql_free_result(result);
	}
	else {
		string opt = "select hw_filename from view_hwcheck_hwlist where hw_cno = \"" + args[OPT_ARGS_CNO].get_string() + "\"";
		if (args[OPT_ARGS_CHAPTER].existed())
			opt += " and hw_chapter = \"" + args[OPT_ARGS_CHAPTER].get_string() + "\"";
		if (args[OPT_ARGS_WEEK].existed())
			opt += " and hw_week = \"" + args[OPT_ARGS_WEEK].get_string() + "\"";
		if (mysql_query(mysql, opt.c_str())) {
			cout << "mysql_query failed(" << mysql_error(mysql) << ")" << endl;
			mysql_close(mysql);
			return -1;
		}
		if ((result = mysql_store_result(mysql)) == NULL) {
			cout << "mysql_store_result failed" << endl;
			mysql_free_result(result);
			mysql_close(mysql);
			return -1;
		}
		while ((row = mysql_fetch_row(result)) != NULL) {
			file hw;
			hw.file_name = row[0];
			if (hw.file_name.substr(hw.file_name.length() - 3, hw.file_name.length() - 1) == "rar")
				hw.type = RAR;
			else if (hw.file_name.substr(hw.file_name.length() - 3, hw.file_name.length() - 1) == "pdf")
				hw.type = PDF;
			else
				hw.type = TXT;
			file_list.push_back(hw);
		}
		mysql_free_result(result);
	}
	mysql_close(mysql);
	/*--------------------------------------------debug------------------------------------------------*/
	if (args[OPT_ARGS_DEBUG].existed()) {
		cout << "参数分析结果" << endl;
		args_analyse_print(args);
		cout << "待检查学生名单" << endl;
		for (int i = 0; i < (int)stu_list.size(); i++)
			cout << setiosflags(ios::left) << setw(4) << i + 1 << setw(10) << stu_list[i].code << setw(10) << stu_list[i].stu_name << setw(10) << stu_list[i].major << endl;
		cout << "待检查文件名单" << endl;
		for (int i = 0; i < (int)file_list.size(); i++)
			cout << setiosflags(ios::left) << setw(4) << i + 1 << setw(30) << file_list[i].file_name << setw(5) << file_list[i].type << endl;
	}
	/*--------------------------------------------打印查询信息------------------------------------------------*/
	if (args[OPT_ARGS_FILE].get_string() != "all")
		cout << "课号 : " << args[OPT_ARGS_CNO].get_string() << " 学生数量 : " << stu_list.size() << " 源文件名 : " << args[OPT_ARGS_FILE].get_string() << endl;
	/*--------------------------------------------打印详细信息------------------------------------------------*/
	int sum[10] = {0};
	if (args[OPT_ARGS_FILE].get_string() != "all")
		for (int i = 0; i < (int)stu_list.size(); i++) {
			cout << setiosflags(ios::left) << setw(3) << i + 1 << " : " << "学号-" << stu_list[i].code << " 姓名-" 
				<< stu_list[i].stu_name << " 课号-" << args[OPT_ARGS_CNO].get_string() << " 文件数量-" << file_list.size() << endl;
			for (int j = 0; j < (int)file_list.size(); j++) {
				//print check result

			}
		}
	else 
		for (int i = 0; i < (int)file_list.size(); i++) {
			//print check result
		}
	/*--------------------------------------------打印详细信息------------------------------------------------*/

				



	/*--------------------------------------------进行检查------------------------------------------------*/

	for (int i = 0; i < (int)stu_list.size(); i++) {
		for (int j = 0; j < (int)file_list.size(); j++) {


		}
	}

	return 0;
}

