/* 2254298 大数据 范潇 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
//按需加入需要的头文件 
#include <sstream>
#include<fstream>
#include <iomanip>
#include"../include/class_aat.h"
#include"../include/common_text.h"
#include"../include/cmd_hdc_tools.h"
#define MAXN 0x10000
using namespace std;

enum OPT_ARGS {
	OPT_ARGS_HELP = 0,
	OPT_ARGS_DEBUG,
	OPT_ARGS_FILE1,
	OPT_ARGS_FILE2,
	OPT_ARGS_TRIM,
	OPT_ARGS_LINE_SKIP,
	OPT_ARGS_LINE_OFFSET,
	OPT_ARGS_IGNORE_BLANK,
	OPT_ARGS_CR_CRLF_NOT_EQUAL,
	OPT_ARGS_MAX_DIFFNUM,
	OPT_ARGS_MAX_LINENUM,
	OPT_ARGS_DISPLAY 
};

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
 ***************************************************************************/
static void usage(const char* const argv0)
{
	char procname[256];

	/* 从"xx\\xx\\txt_compare.exe形式的argv[0]中截取txt_compare出来" */
	string temp(argv0);
	if (temp.find('\\') != temp.npos)
		strcpy(procname, temp.substr(temp.find_last_of('\\') + 1).data()); //这句替换成自己的截取函数 
	else
		strcpy(procname, argv0);
	ostringstream msg;
	const int wkey = 7 + strlen(procname) + 1;
	const int wopt = 7 + strlen(procname) + 4;
	cout << endl;

	msg << procname << " [Ver1.0.1]" << endl;
	msg << endl;

	msg << "Usage: " << procname << " --file1 xxx --file2 xxx [ --trim none/left/rigth/all | --lineskip 0..100 | --lineoffset -100..100 | --ignore_blank | --max_diff 0..100 | --display none/normal/detailed ]" << endl;

	msg << setw(wkey) << ' ' << "必选项：" << endl;
	msg << setw(wopt) << ' ' << "--file1 name1              : 指定要比较的第1个文件名（必选）" << endl;
	msg << setw(wopt) << ' ' << "--file2 name2              : 指定要比较的第2个文件名（必选）" << endl;
	msg << endl;

	msg << setw(wkey) << ' ' << "可选项：" << endl;
	msg << setw(wopt) << ' ' << "--trim none/left/right/all     : 指定每行的空格/tab的忽略方式（无此项则默认为none）" << endl;
	msg << setw(wopt) << ' ' << "\tnone   : 每行均严格匹配" << endl;
	msg << setw(wopt) << ' ' << "\tleft   : 每行均忽略头部空格" << endl;
	msg << setw(wopt) << ' ' << "\tright  : 每行均忽略尾部空格" << endl;
	msg << setw(wopt) << ' ' << "\tall    : 每行均忽略头尾空格" << endl;
	msg << setw(wopt) << ' ' << "--lineskip s                   : 指定文件的前s行不比较（无此项则s为0）" << endl;
	msg << setw(wopt) << ' ' << "\t取值[0..100]，表示同时跳过两个文件的前s行" << endl;
	msg << setw(wopt) << ' ' << "--lineoffset n                 : 指定文件错位的行数（无此项则n为0）" << endl;
	msg << setw(wopt) << ' ' << "\t取值[-100..100]，负数表示忽略file1的前n行，正数表示忽略file2的前n行" << endl;
	msg << setw(wopt) << ' ' << "--ignore_blank                 : 忽略文件中--trim后的所有空行(无此项则不忽略)" << endl;
	msg << setw(wopt) << ' ' << "--CR_CRLF_not_equal            : 不忽略Windows/Linux文件的换行符差异(无此项则忽略差异)" << endl;
	msg << setw(wopt) << ' ' << "--max_diff m                   : 指定文件错位的行数（无此项则m为0）" << endl;
	msg << setw(wopt) << ' ' << "\t取值[0..100]，表示满m个不同行则结束运行，不再进行后续的比较" << endl;
	msg << setw(wopt) << ' ' << "--max_line x                   : 指定文件比较的最大行数（无此项则x为0）" << endl;
	msg << setw(wopt) << ' ' << "\t取值[0..10000]，表示比较x行后则结束运行，不再进行后续的比较" << endl;
	msg << setw(wopt) << ' ' << "--display none/normal/detailed : 指定显示的信息（无此项则默认为none）" << endl;
	msg << setw(wopt) << ' ' << "\tnone     : 仅一行匹配与否的提示" << endl;
	msg << setw(wopt) << ' ' << "\tnormal   : 每个差异行给出差异信息" << endl;
	msg << setw(wopt) << ' ' << "\tdetailed : 每个差异行给出更详细的差异信息" << endl;
	msg << endl;

	msg << "e.g.   " << procname << " --file1 my.txt --file2 std.txt" << endl;
	msg << setw(wopt) << ' ' << " : 比较my.txt和std.txt，全部匹配，仅一行输出" << endl;
	msg << "       " << procname << " --file1 my.txt --file2 std.txt --trim all" << endl;
	msg << setw(wopt) << ' ' << " : 比较my.txt和std.txt，每行均去除头尾空格，仅一行输出" << endl;
	msg << "       " << procname << " --file1 my.txt --file2 std.txt --lineoffset -2" << endl;
	msg << setw(wopt) << ' ' << " : 比较my.txt和std.txt，忽略my.txt的前2行(即my.txt的第3行与std.txt的第1行进行比较，每行严格匹配)，仅一行输出" << endl;
	msg << "       " << procname << " --file1 my.txt --file2 std.txt --trim left --lineoffset 3" << endl;
	msg << setw(wopt) << ' ' << " : 比较my.txt和std.txt，忽略std.txt的前3行(即my.txt的第1行与std.txt的第4行进行比较)，每行去除头部空格，仅一行输出" << endl;
	msg << "       " << procname << " --file1 my.txt --file2 std.txt --ignore_blank" << endl;
	msg << setw(wopt) << ' ' << " : 比较my.txt和std.txt，忽略文件中的所有空行，仅一行输出" << endl;
	msg << "       " << procname << " --file1 my.txt --file2 std.txt --lineskip 1" << endl;
	msg << setw(wopt) << ' ' << " : 比较my.txt和std.txt，第一行不比较" << endl;
	msg << "       " << procname << " --file1 my.txt --file2 std.txt --ignore_blank --trim right" << endl;
	msg << setw(wopt) << ' ' << " : 比较my.txt和std.txt，忽略文件中去除头尾空格后的所有空行，仅一行输出" << endl;
	msg << "       " << procname << " --file1 my.txt --file2 std.txt --max_diff 3" << endl;
	msg << setw(wopt) << ' ' << " : 比较my.txt和std.txt，全部匹配，有3行不匹配后结束运行，仅一行输出" << endl;
	msg << "       " << procname << " --file1 my.txt --file2 std.txt --max_line 7" << endl;
	msg << setw(wopt) << ' ' << " : 比较my.txt和std.txt，全部匹配，仅比较前7行，仅一行输出" << endl;
	msg << "       " << procname << " --file1 my.txt --file2 std.txt --CR_CRLF_not_queal" << endl;
	msg << setw(wopt) << ' ' << " : 比较my.txt和std.txt，全部匹配，不忽略Windows/Linux的文件差异，仅一行输出" << endl;
	msg << "       " << procname << " --file1 my.txt --file2 std.txt --display normal" << endl;
	msg << setw(wopt) << ' ' << " : 比较my.txt和std.txt，全部匹配，不匹配的行显示信息" << endl;
	msg << "       " << procname << " --file1 my.txt --file2 std.txt --display detailed" << endl;
	msg << setw(wopt) << ' ' << " : 比较my.txt和std.txt，全部匹配，不匹配的行显示详细信息" << endl;
	msg << endl;

	/* 一次全部显示出来 */
	cout << msg.str() << endl;
}
void prompt()
{
	cout << "阅读提示：" << endl;
	cout << "	1、空行用<EMPTY>标出" << endl;
	cout << "	2、文件结束用<EOF>标出" << endl;
	cout << "	3、两行相同列位置的差异字符用亮色标出" << endl;
	cout << "	4、每行中的CR/LF/VT/BS/BEL用X标出(方便看清隐含字符)" << endl;
	cout << "	5、每行尾的多余的字符用亮色标出，CR/LF/VT/BS/BEL用亮色X标出(方便看清隐含字符)" << endl;
	cout << "	6、每行最后用<CR>标出(方便看清隐含字符)" << endl;
	cout << "	7、中文因为编码问题，差异位置可能报在后半个汉字上，但整个汉字都亮色标出" << endl;
	return;
}
static void _make_line(int rown, int display_mode)
{
	int width = (rown / 10 + 1) * 10 + 8 + 2;
	if (display_mode == DETAIL_MODE && width < 80)
		width = 80;
	cout << setw(width) << setfill('=') << "=" << setfill(' ') << endl;
	return;
}//TODO:最开始遍历文件时要记录最长的那一行的长度
//TODO:待完成的有获取最长的长度、文件打开失败的处理，以及其他测试中没涉及到的参数
/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int main(int argc, char** argv)
{
	/* 指定去除空格的方式 */
	const string TrimType[] = { "none",	"left",	"right",	"all", "" };
	const string DisplayType[] = { "none",	"normal",	"detailed", "" };

	args_analyse_tools args[] = {
		args_analyse_tools("--help",				ST_EXTARGS_TYPE::boolean, 0, false),
		args_analyse_tools("--debug",			ST_EXTARGS_TYPE::boolean, 0, false),
		args_analyse_tools("--file1",			ST_EXTARGS_TYPE::str, 1, string("")),
		args_analyse_tools("--file2",			ST_EXTARGS_TYPE::str, 1, string("")),
		args_analyse_tools("--trim",				ST_EXTARGS_TYPE::str_with_set_error, 1, 0, TrimType),
		args_analyse_tools("--lineskip",			ST_EXTARGS_TYPE::int_with_default,   1, 0, 0, 100),
		args_analyse_tools("--lineoffset",		ST_EXTARGS_TYPE::int_with_default,   1, 0, -100, 100),
		args_analyse_tools("--ignore_blank",		ST_EXTARGS_TYPE::boolean, 0, false),
		args_analyse_tools("--CR_CRLF_not_equal",	ST_EXTARGS_TYPE::boolean, 0, false),
		args_analyse_tools("--max_diff",			ST_EXTARGS_TYPE::int_with_default,   1, 0, 0, 100),
		args_analyse_tools("--max_line",			ST_EXTARGS_TYPE::int_with_default,   1, 0, 0, 10000),
		args_analyse_tools("--display",			ST_EXTARGS_TYPE::str_with_set_error, 1, 0, DisplayType),
		args_analyse_tools()  //最后一个，用于结束
	};
	int cur_argc, ret = 0;

	//最后一个参数1，表示除选项参数外，还有其它参数
	if ((cur_argc = args_analyse_process(argc, argv, args, 0)) < 0) {
		//错误信息在函数中已打印
		args_analyse_print(args);
		usage(argv[0]);
		return -1;
	}
	string trim_type(args[OPT_ARGS_TRIM].get_string());

	/* 对help做特殊处理 */
	if (args[OPT_ARGS_HELP].existed()) {
		//只要有 --help，其它参数都忽略，显示帮助即可
		args_analyse_print(args);
		usage(argv[0]);
		return -1; //执行完成直接退出
	}

	if (args[OPT_ARGS_FILE1].existed() + args[OPT_ARGS_FILE2].existed() != 2) {
		usage(argv[0]);
		cout << "必须指定参数[" << args[OPT_ARGS_FILE1].get_name() << "和" << args[OPT_ARGS_FILE2].get_name() << "]" << endl;
		return -1;
	}

	if (args[OPT_ARGS_CR_CRLF_NOT_EQUAL].existed() && (trim_type == "right" || trim_type == "all")) {
		usage(argv[0]);
		cout << "参数[" << args[OPT_ARGS_CR_CRLF_NOT_EQUAL].get_name() << "]不能和[" << args[OPT_ARGS_TRIM].get_name() << " right/all]同时存在." << endl;
		return -1;
	}

	if (args[OPT_ARGS_DEBUG].existed())
		args_analyse_print(args);

	/* 进入实际的功能调用，完成相应的功能 */
	if (args[OPT_ARGS_DEBUG].existed()) {
		cout << setw(13) << "File1" << ": " << args[OPT_ARGS_FILE1].get_string() << endl;
		cout << setw(13) << "File2" << ": " << args[OPT_ARGS_FILE2].get_string() << endl;
		cout << setw(13) << "Trim" << ": " << args[OPT_ARGS_TRIM].get_string() << endl;
		cout << setw(13) << "Display" << ": " << args[OPT_ARGS_DISPLAY].get_string() << endl;
		cout << setw(13) << "Skip" << ": " << args[OPT_ARGS_LINE_SKIP].get_int() << endl;
		cout << setw(13) << "Offset" << ": " << args[OPT_ARGS_LINE_OFFSET].get_int() << endl;
		cout << setw(13) << "MaxDiff" << ": " << args[OPT_ARGS_MAX_DIFFNUM].get_int() << endl;
		cout << setw(13) << "MaxLine" << ": " << args[OPT_ARGS_MAX_LINENUM].get_int() << endl;
		cout << setw(13) << "IgnoreBlank" << ": " << args[OPT_ARGS_IGNORE_BLANK].existed() << endl;
		cout << setw(13) << "CR/CRLF" << ": " << args[OPT_ARGS_CR_CRLF_NOT_EQUAL].existed() << endl;
		cout << setw(13) << "Debug" << ": " << args[OPT_ARGS_DEBUG].existed() << endl;
		cout << endl;
	}
	ifstream infile1(args[OPT_ARGS_FILE1].get_string(), ios::in | ios::binary);
	ifstream infile2(args[OPT_ARGS_FILE2].get_string(), ios::in | ios::binary);
	if (!infile1) {
		cout << "第1个文件[" << args[OPT_ARGS_FILE1].get_string() << "]无法打开." << endl;
		infile1.close();
		infile2.close();
		return -1;
	}
	else if (!infile2) {
		cout << "第2个文件[" << args[OPT_ARGS_FILE2].get_string() << "]无法打开." << endl;
		infile1.close();
		infile2.close();
		return -1;
	}

	int rown1 = 0, rown2 = 0;
	char buffer1[MAXN + 1], buffer2[MAXN + 1];
	int status1, status2;
	char trim_ch[10] = { ' ','\t','\0' };
	char end[10] = { '\n' };
	int inputn1, inputn2;
	//TODO: 先全部读入一遍，检查是否有某一行超过最大字符数，同时获取总行数。
	int maxlen1 = 0, maxlen2 = 0;
	int templen = 0;
	enum system sys1 = LINUX, sys2 = LINUX, dummy = WINDOWS;
	while (!(status1 = get_line(infile1, buffer1, templen, TRIM_NONE, trim_ch, strlen(trim_ch), end, 1, sys1))) {
		rown1++;
		if (templen > maxlen1)
			maxlen1 = templen;
		templen = 0;
	}
	if (templen > maxlen1)
		maxlen1 = templen;
	templen = 0;
	while (!(status2 = get_line(infile2, buffer2, templen, TRIM_NONE, trim_ch, strlen(trim_ch), end, 1, sys2))) {
		rown2++;
		if (templen > maxlen2)
			maxlen2 = templen;
		templen = 0;
	}
	if (templen > maxlen2)
		maxlen2 = templen;
	int maxlen = (maxlen1 > maxlen2 ? maxlen1 : maxlen2);
	int display_mode = NONE_MODE;
	if (args[OPT_ARGS_DISPLAY].get_string() == "normal")
		display_mode = NORMAL_MODE;
	else if (args[OPT_ARGS_DISPLAY].get_string() == "detailed")
		display_mode = DETAIL_MODE;
	if (status1 == -1)
		cout << "文件[" << args[OPT_ARGS_FILE1].get_string() << "]的第(" << rown1 + 1 << ")行不符合要求，超过最大长度[" << MAXN << "]." << endl;
	else if (args[OPT_ARGS_DEBUG].existed()) {
		cout << "第1个文件的基本信息：" << endl;
		_make_line(maxlen, display_mode);
		cout << "文 件 名：" << args[OPT_ARGS_FILE1].get_string() << endl;
		cout << "大    小：";
		infile1.seekg(0, ios::end);
		cout << infile1.tellg() << endl;
		infile1.seekg(0, ios::beg);
		cout << "行    数：" << rown1 << endl;
		cout << "最大行长：" << maxlen1 + 1 << endl;
		cout << "文件格式：" << (sys1 == LINUX ? "Linux" : "Windows") << endl;
		_make_line(maxlen, display_mode);
		cout << endl;
	}
	if (status2 == -1)
		cout << "文件[" << args[OPT_ARGS_FILE2].get_string() << "]的第(" << rown2 + 1 << ")行不符合要求，超过最大长度[" << MAXN << "]." << endl;
	else if (args[OPT_ARGS_DEBUG].existed()) {
		cout << "第2个文件的基本信息：" << endl;
		_make_line(maxlen, display_mode);
		cout << "文 件 名：" << args[OPT_ARGS_FILE2].get_string() << endl;
		cout << "大    小：";
		infile2.seekg(0, ios::end);
		cout << infile2.tellg() << endl;
		infile2.seekg(0, ios::beg);
		cout << "行    数：" << rown2 << endl;
		cout << "最大行长：" << maxlen2 + 1 << endl;
		cout << "文件格式：" << (sys2 == LINUX ? "Linux" : "Windows") << endl;
		_make_line(maxlen, display_mode);
		cout << endl;
		cout << endl;
	}
	if (status1 == -1 || status2 == -1) {
		infile1.close();
		infile2.close();
		return -1;
	}
	//TODO: 处理offset和skip
	infile1.seekg(0, ios::beg);
	infile2.seekg(0, ios::beg);
	int offset1 = args[OPT_ARGS_LINE_SKIP].get_int() + (args[OPT_ARGS_LINE_OFFSET].get_int() < 0 ? -args[OPT_ARGS_LINE_OFFSET].get_int() : 0);
	int offset2 = args[OPT_ARGS_LINE_SKIP].get_int() + (args[OPT_ARGS_LINE_OFFSET].get_int() > 0 ? args[OPT_ARGS_LINE_OFFSET].get_int() : 0);
	int cur_line1 = 1, cur_line2 = 1;
	while (offset1--) {
		int status = get_line(infile1, buffer1, inputn1, TRIM_NONE, trim_ch, strlen(trim_ch), end, 1, dummy);
		if (status == 1)
			break;
		else if (!inputn1 && args[OPT_ARGS_IGNORE_BLANK].existed())
			offset1++;
		cur_line1++;
	}
	while (offset2--) {
		int status = get_line(infile2, buffer2, inputn2, TRIM_NONE, trim_ch, strlen(trim_ch), end, 1, dummy);
		if (status == 1)
			break;
		else if (!inputn2 && args[OPT_ARGS_IGNORE_BLANK].existed())
			offset2++;
		cur_line2++;
	}
	//循环读入并比较，读入函数处理trim，ignore_blank，其中ignore_blank比 line_offset的优先级要高，比较函数处理CR_CRLF_not_equal，循环结束条件依赖max_diff和max_line
	int cur_num = 0;
	int trim;
	if (!args[OPT_ARGS_TRIM].existed() || args[OPT_ARGS_TRIM].get_string() == "none")
		trim = TRIM_NONE;
	else if (args[OPT_ARGS_TRIM].get_string() == "right")
		trim = TRIM_RIGHT;
	else if (args[OPT_ARGS_TRIM].get_string() == "left")
		trim = TRIM_LEFT;
	else if (args[OPT_ARGS_TRIM].get_string() == "all")
		trim = TRIM_ALL;
	int eof1 = 0, eof2 = 0;
	if (args[OPT_ARGS_DISPLAY].get_string() == "normal") {
		cout << "比较结果输出：" << endl;
		_make_line(maxlen, display_mode);
	}
	else if (args[OPT_ARGS_DISPLAY].get_string() == "detailed") {
		cout << "比较结果输出：" << endl;
		_make_line(maxlen, display_mode);
	}
	else if (args[OPT_ARGS_DEBUG].existed()) {
		cout << "比较结果输出：" << endl;
		_make_line(maxlen, display_mode);
	}
	int count = 0;
	int first = 1;
	int curline = 0;
	while (1) {
		while (1) {
			int status = get_line(infile1, buffer1, inputn1, trim, trim_ch, strlen(trim_ch), end, 1, dummy, MAXN, args[OPT_ARGS_CR_CRLF_NOT_EQUAL].existed());
			if (status == 1) {
				eof1 = 1;
				cur_line1++;
				break;
			}
			cur_line1++;
			if (!inputn1 && args[OPT_ARGS_IGNORE_BLANK].existed())
				continue;
			if (args[OPT_ARGS_CR_CRLF_NOT_EQUAL].existed() && strlen(buffer1) == 1 && buffer1[0] == '\r') {
				if ((args[OPT_ARGS_TRIM].existed() && args[OPT_ARGS_TRIM].get_string() != "none") && args[OPT_ARGS_IGNORE_BLANK].existed())
					continue;
				break;
			}
			break;
		}

		while (1) {
			int status = get_line(infile2, buffer2, inputn2, trim, trim_ch, strlen(trim_ch), end, 1, dummy, MAXN, args[OPT_ARGS_CR_CRLF_NOT_EQUAL].existed());
			if (status == 1) {
				eof2 = 1;
				cur_line2++;
				break;
			}
			cur_line2++;
			if (!inputn2 && args[OPT_ARGS_IGNORE_BLANK].existed())
				continue;
			if (args[OPT_ARGS_CR_CRLF_NOT_EQUAL].existed() && strlen(buffer2) == 1 && buffer2[0] == '\r') {
				if ((args[OPT_ARGS_TRIM].existed() && args[OPT_ARGS_TRIM].get_string() != "none") && args[OPT_ARGS_IGNORE_BLANK].existed())
					continue;
				break;
			}
			break;
		}
		cur_num++;
		//////if ((eof1 ^ eof2) && args[OPT_ARGS_IGNORE_BLANK].existed()) {
		//////	int temp = 0;
		//////	char tempbuffer[MAXN];
		//////	if (eof1) {//此时判断file2后面多出来的是否都是空行
		//////		while (1) {
		//////			temp = 0;
		//////			int status = get_line(infile2, tempbuffer, temp, trim, trim_ch, strlen(trim_ch), end, 1, dummy, MAXN, args[OPT_ARGS_CR_CRLF_NOT_EQUAL].existed());
		//////			if (temp)
		//////				break;
		//////			if (status == 1) {
		//////				eof2 = 1;
		//////				break;
		//////			}
		//////		}
		//////	}
		//////	if (eof2) {//此时判断file1后面多出来的是否都是空行
		//////		while (1) {
		//////			temp = 0;
		//////			int status = get_line(infile1, tempbuffer, temp, trim, trim_ch, strlen(trim_ch), end, 1, dummy, MAXN, args[OPT_ARGS_CR_CRLF_NOT_EQUAL].existed());
		//////			if (temp)
		//////				break;
		//////			if (status == 1) {
		//////				eof1 = 1;
		//////				break;
		//////			}
		//////		}
		//////	}
		//////}
		if (first) {
			first = 0;
			if (args[OPT_ARGS_DEBUG].existed()) {
				cout << "起始行: " << setiosflags(ios::left) << setw(int_len(cur_line1 - 2) + 1) << cur_line1 - 2 << "/" << setw(int_len(cur_line2) + 1)
					<< setiosflags(ios::right) << cur_line2 - 2 << endl;
			}
		}
		if (args[OPT_ARGS_MAX_DIFFNUM].get_int() && (count >= args[OPT_ARGS_MAX_DIFFNUM].get_int())
			|| args[OPT_ARGS_MAX_LINENUM].get_int() && (curline >= args[OPT_ARGS_MAX_LINENUM].get_int()))
			break;
		count += diff(buffer1, buffer2, inputn1, inputn2, cur_line1 - 1, cur_line2 - 1, eof1, eof2, display_mode, trim, args[OPT_ARGS_DEBUG].existed(), first);
		curline++;
		if (eof1 || eof2)
			break;
		if (display_mode == NONE_MODE && count)
			break;
	}
	cout << dec;
	if (display_mode == NONE_MODE && !args[OPT_ARGS_DEBUG].existed())
		cout << (count ? "文件不同." : "文件相同.") << endl;
	else if (args[OPT_ARGS_DEBUG].existed()) {
		if (!count) {
			cout << "在指定检查条件下完全一致." << endl;
			_make_line(maxlen, display_mode);
		}
		else {
			_make_line(maxlen, display_mode);
			cout << "在指定检查条件下共" << count << "行有差异"
				<< ((args[OPT_ARGS_MAX_DIFFNUM].get_int() && count == args[OPT_ARGS_MAX_DIFFNUM].get_int()) ? "[已到设定的最大差异值]" : "") << "." << endl;
			prompt();
			if (display_mode != DETAIL_MODE)
				cout << "	8、用--display detailed可以得到更详细的信息" << endl;
			_make_line(maxlen, display_mode);
		}
	}
	else {
		if (!count) {
			cout << "在指定检查条件下完全一致." << endl;
			_make_line(maxlen, display_mode);
		}
		else {
			_make_line(maxlen, display_mode);
			cout << "在指定检查条件下共" << count << "行有差异"
				<< ((args[OPT_ARGS_MAX_DIFFNUM].get_int() && count == args[OPT_ARGS_MAX_DIFFNUM].get_int()) ? "[已到设定的最大差异值]" : "") << "." << endl;
			prompt();
			if (display_mode != DETAIL_MODE)
				cout << "	8、用--display detailed可以得到更详细的信息" << endl;
			_make_line(maxlen, display_mode);
		}
	}
	//循环体中处理display
	infile1.close();
	infile2.close();
	return 0;
}
//TODO: demo的逻辑是只有读到'\n'了才认为是换行，并会用<CR>显示
//TODO: 单行长度超出范围也有相应的报错
//TODO: 除了规定的不显示字符用X表示外，EOF用方框表示,这些字符和<EMPTY>都要高亮，这里是指文件x：开头那一行.<tmpty>后跟<CR>，因为一个空行必定对应一个回车
//TODO: 默认\r\n作为\n读入
//TODO: normal和detailed的区别在于后者会把有差异的那一行的hex打印出来，同时把标尺也给打印出来
//TODO: hex格式下会出现<EOF>,<EMPTY>,但是不会出现<CR>,同时是没有颜色的。并且只有当该行为空时，才会打印出<EOF>，两者都是顶格打印
//TODO: x/x行 那一行中的错误信息有三种：当是两个字符进行比较出错时，提示为"第[x]个字符开始有差异"；当是文件1的一个字符对应着另外一个文件的<EMPTY>或<EOF>时，提示为“文件1的尾部有多余字符”；当是文件1的<EOF>对应文件2的<CR>或<EMPTY>时，提示为“文件1已结束/文件2仍有内容”
//TODO: display的内容先存在msg中，如果所有行的长度符合要求，再一起输出
/*
阅读提示：
1、空行用 xxx 标出
2、文件结束用 xxx 标出
3、两行相同列位置的差异字符用亮色标出
4、每行中的CR/LF/VT/BS/BEL用X标出(方便看清隐含字符)
5、每行尾的多余的字符用亮色标出，CR/LF/VT/BS/BEL用亮色X标出(方便看清隐含字符)
6、每行最后用 xxx 标出(方便看清隐含字符)"
7、中文因为编码问题，差异位置可能报在后半个汉字上，但整个汉字都亮色标出
8、用--display detailed可以得到更详细的信息
*/

/* 测试文件准备
	1.txt ：正常文件
	2.txt ：在1.txt的基础上，某些行前面无空格
	3.txt ：在1.txt的基础上，某些行后面无空格
	4.txt ：在1.txt的基础上，最后一行没有回车
	5.txt ：在1.txt的基础上，多一些空行
	6.txt ：在1.txt的基础上，多一些空行，其中某些行有空格和tab
	7.txt ：和1.txt完全相同
	8.txt ：是1.txt的Linux格式版

txt_compare --file1 1.txt --file2 2.txt --trim left
txt_compare --file1 1.txt --file2 2.txt --trim all
txt_compare --file1 2.txt --file2 3.txt --trim all
txt_compare --file1 1.txt --file2 4.txt --trim right --ignore_blank
txt_compare --file1 1.txt --file2 4.txt --trim all --ignore_blank
txt_compare --file1 2.txt --file2 4.txt --trim all --ignore_blank
txt_compare --file1 3.txt --file2 4.txt --trim right --ignore_blank
txt_compare --file1 3.txt --file2 4.txt --trim all --ignore_blank
txt_compare --file1 1.txt --file2 5.txt --trim right --ignore_blank
txt_compare --file1 1.txt --file2 6.txt --ignore_blank --trim right
txt_compare --file1 5.txt --file2 6.txt --ignore_blank --trim all
txt_compare --file1 1.txt --file2 7.txt
txt_compare --file1 1.txt --file2 8.txt

rem 不相同的例子
txt_compare --file1 1.txt --file2 2.txt
txt_compare --file1 1.txt --file2 2.txt --trim right
txt_compare --file1 1.txt --file2 5.txt
txt_compare --file1 1.txt --file2 5.txt --trim right
txt_compare --file1 1.txt --file2 6.txt
txt_compare --file1 1.txt --file2 6.txt --ignore_blank
txt_compare --file1 1.txt --file2 8.txt --CR_CRLF_not_equal

*/
