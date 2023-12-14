/* 2254298 ������ ���� */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
//���������Ҫ��ͷ�ļ� 
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
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
 ***************************************************************************/
static void usage(const char* const argv0)
{
	char procname[256];

	/* ��"xx\\xx\\txt_compare.exe��ʽ��argv[0]�н�ȡtxt_compare����" */
	string temp(argv0);
	if (temp.find('\\') != temp.npos)
		strcpy(procname, temp.substr(temp.find_last_of('\\') + 1).data()); //����滻���Լ��Ľ�ȡ���� 
	else
		strcpy(procname, argv0);
	ostringstream msg;
	const int wkey = 7 + strlen(procname) + 1;
	const int wopt = 7 + strlen(procname) + 4;
	cout << endl;

	msg << procname << " [Ver1.0.1]" << endl;
	msg << endl;

	msg << "Usage: " << procname << " --file1 xxx --file2 xxx [ --trim none/left/rigth/all | --lineskip 0..100 | --lineoffset -100..100 | --ignore_blank | --max_diff 0..100 | --display none/normal/detailed ]" << endl;

	msg << setw(wkey) << ' ' << "��ѡ�" << endl;
	msg << setw(wopt) << ' ' << "--file1 name1              : ָ��Ҫ�Ƚϵĵ�1���ļ�������ѡ��" << endl;
	msg << setw(wopt) << ' ' << "--file2 name2              : ָ��Ҫ�Ƚϵĵ�2���ļ�������ѡ��" << endl;
	msg << endl;

	msg << setw(wkey) << ' ' << "��ѡ�" << endl;
	msg << setw(wopt) << ' ' << "--trim none/left/right/all     : ָ��ÿ�еĿո�/tab�ĺ��Է�ʽ���޴�����Ĭ��Ϊnone��" << endl;
	msg << setw(wopt) << ' ' << "\tnone   : ÿ�о��ϸ�ƥ��" << endl;
	msg << setw(wopt) << ' ' << "\tleft   : ÿ�о�����ͷ���ո�" << endl;
	msg << setw(wopt) << ' ' << "\tright  : ÿ�о�����β���ո�" << endl;
	msg << setw(wopt) << ' ' << "\tall    : ÿ�о�����ͷβ�ո�" << endl;
	msg << setw(wopt) << ' ' << "--lineskip s                   : ָ���ļ���ǰs�в��Ƚϣ��޴�����sΪ0��" << endl;
	msg << setw(wopt) << ' ' << "\tȡֵ[0..100]����ʾͬʱ���������ļ���ǰs��" << endl;
	msg << setw(wopt) << ' ' << "--lineoffset n                 : ָ���ļ���λ���������޴�����nΪ0��" << endl;
	msg << setw(wopt) << ' ' << "\tȡֵ[-100..100]��������ʾ����file1��ǰn�У�������ʾ����file2��ǰn��" << endl;
	msg << setw(wopt) << ' ' << "--ignore_blank                 : �����ļ���--trim������п���(�޴����򲻺���)" << endl;
	msg << setw(wopt) << ' ' << "--CR_CRLF_not_equal            : ������Windows/Linux�ļ��Ļ��з�����(�޴�������Բ���)" << endl;
	msg << setw(wopt) << ' ' << "--max_diff m                   : ָ���ļ���λ���������޴�����mΪ0��" << endl;
	msg << setw(wopt) << ' ' << "\tȡֵ[0..100]����ʾ��m����ͬ����������У����ٽ��к����ıȽ�" << endl;
	msg << setw(wopt) << ' ' << "--max_line x                   : ָ���ļ��Ƚϵ�����������޴�����xΪ0��" << endl;
	msg << setw(wopt) << ' ' << "\tȡֵ[0..10000]����ʾ�Ƚ�x�к���������У����ٽ��к����ıȽ�" << endl;
	msg << setw(wopt) << ' ' << "--display none/normal/detailed : ָ����ʾ����Ϣ���޴�����Ĭ��Ϊnone��" << endl;
	msg << setw(wopt) << ' ' << "\tnone     : ��һ��ƥ��������ʾ" << endl;
	msg << setw(wopt) << ' ' << "\tnormal   : ÿ�������и���������Ϣ" << endl;
	msg << setw(wopt) << ' ' << "\tdetailed : ÿ�������и�������ϸ�Ĳ�����Ϣ" << endl;
	msg << endl;

	msg << "e.g.   " << procname << " --file1 my.txt --file2 std.txt" << endl;
	msg << setw(wopt) << ' ' << " : �Ƚ�my.txt��std.txt��ȫ��ƥ�䣬��һ�����" << endl;
	msg << "       " << procname << " --file1 my.txt --file2 std.txt --trim all" << endl;
	msg << setw(wopt) << ' ' << " : �Ƚ�my.txt��std.txt��ÿ�о�ȥ��ͷβ�ո񣬽�һ�����" << endl;
	msg << "       " << procname << " --file1 my.txt --file2 std.txt --lineoffset -2" << endl;
	msg << setw(wopt) << ' ' << " : �Ƚ�my.txt��std.txt������my.txt��ǰ2��(��my.txt�ĵ�3����std.txt�ĵ�1�н��бȽϣ�ÿ���ϸ�ƥ��)����һ�����" << endl;
	msg << "       " << procname << " --file1 my.txt --file2 std.txt --trim left --lineoffset 3" << endl;
	msg << setw(wopt) << ' ' << " : �Ƚ�my.txt��std.txt������std.txt��ǰ3��(��my.txt�ĵ�1����std.txt�ĵ�4�н��бȽ�)��ÿ��ȥ��ͷ���ո񣬽�һ�����" << endl;
	msg << "       " << procname << " --file1 my.txt --file2 std.txt --ignore_blank" << endl;
	msg << setw(wopt) << ' ' << " : �Ƚ�my.txt��std.txt�������ļ��е����п��У���һ�����" << endl;
	msg << "       " << procname << " --file1 my.txt --file2 std.txt --lineskip 1" << endl;
	msg << setw(wopt) << ' ' << " : �Ƚ�my.txt��std.txt����һ�в��Ƚ�" << endl;
	msg << "       " << procname << " --file1 my.txt --file2 std.txt --ignore_blank --trim right" << endl;
	msg << setw(wopt) << ' ' << " : �Ƚ�my.txt��std.txt�������ļ���ȥ��ͷβ�ո������п��У���һ�����" << endl;
	msg << "       " << procname << " --file1 my.txt --file2 std.txt --max_diff 3" << endl;
	msg << setw(wopt) << ' ' << " : �Ƚ�my.txt��std.txt��ȫ��ƥ�䣬��3�в�ƥ���������У���һ�����" << endl;
	msg << "       " << procname << " --file1 my.txt --file2 std.txt --max_line 7" << endl;
	msg << setw(wopt) << ' ' << " : �Ƚ�my.txt��std.txt��ȫ��ƥ�䣬���Ƚ�ǰ7�У���һ�����" << endl;
	msg << "       " << procname << " --file1 my.txt --file2 std.txt --CR_CRLF_not_queal" << endl;
	msg << setw(wopt) << ' ' << " : �Ƚ�my.txt��std.txt��ȫ��ƥ�䣬������Windows/Linux���ļ����죬��һ�����" << endl;
	msg << "       " << procname << " --file1 my.txt --file2 std.txt --display normal" << endl;
	msg << setw(wopt) << ' ' << " : �Ƚ�my.txt��std.txt��ȫ��ƥ�䣬��ƥ�������ʾ��Ϣ" << endl;
	msg << "       " << procname << " --file1 my.txt --file2 std.txt --display detailed" << endl;
	msg << setw(wopt) << ' ' << " : �Ƚ�my.txt��std.txt��ȫ��ƥ�䣬��ƥ�������ʾ��ϸ��Ϣ" << endl;
	msg << endl;

	/* һ��ȫ����ʾ���� */
	cout << msg.str() << endl;
}
void prompt()
{
	cout << "�Ķ���ʾ��" << endl;
	cout << "	1��������<EMPTY>���" << endl;
	cout << "	2���ļ�������<EOF>���" << endl;
	cout << "	3��������ͬ��λ�õĲ����ַ�����ɫ���" << endl;
	cout << "	4��ÿ���е�CR/LF/VT/BS/BEL��X���(���㿴�������ַ�)" << endl;
	cout << "	5��ÿ��β�Ķ�����ַ�����ɫ�����CR/LF/VT/BS/BEL����ɫX���(���㿴�������ַ�)" << endl;
	cout << "	6��ÿ�������<CR>���(���㿴�������ַ�)" << endl;
	cout << "	7��������Ϊ�������⣬����λ�ÿ��ܱ��ں��������ϣ����������ֶ���ɫ���" << endl;
	return;
}
static void _make_line(int rown, int display_mode)
{
	int width = (rown / 10 + 1) * 10 + 8 + 2;
	if (display_mode == DETAIL_MODE && width < 80)
		width = 80;
	cout << setw(width) << setfill('=') << "=" << setfill(' ') << endl;
	return;
}//TODO:�ʼ�����ļ�ʱҪ��¼�����һ�еĳ���
//TODO:����ɵ��л�ȡ��ĳ��ȡ��ļ���ʧ�ܵĴ����Լ�����������û�漰���Ĳ���
/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int main(int argc, char** argv)
{
	/* ָ��ȥ���ո�ķ�ʽ */
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
		args_analyse_tools()  //���һ�������ڽ���
	};
	int cur_argc, ret = 0;

	//���һ������1����ʾ��ѡ������⣬������������
	if ((cur_argc = args_analyse_process(argc, argv, args, 0)) < 0) {
		//������Ϣ�ں������Ѵ�ӡ
		args_analyse_print(args);
		usage(argv[0]);
		return -1;
	}
	string trim_type(args[OPT_ARGS_TRIM].get_string());

	/* ��help�����⴦�� */
	if (args[OPT_ARGS_HELP].existed()) {
		//ֻҪ�� --help���������������ԣ���ʾ��������
		args_analyse_print(args);
		usage(argv[0]);
		return -1; //ִ�����ֱ���˳�
	}

	if (args[OPT_ARGS_FILE1].existed() + args[OPT_ARGS_FILE2].existed() != 2) {
		usage(argv[0]);
		cout << "����ָ������[" << args[OPT_ARGS_FILE1].get_name() << "��" << args[OPT_ARGS_FILE2].get_name() << "]" << endl;
		return -1;
	}

	if (args[OPT_ARGS_CR_CRLF_NOT_EQUAL].existed() && (trim_type == "right" || trim_type == "all")) {
		usage(argv[0]);
		cout << "����[" << args[OPT_ARGS_CR_CRLF_NOT_EQUAL].get_name() << "]���ܺ�[" << args[OPT_ARGS_TRIM].get_name() << " right/all]ͬʱ����." << endl;
		return -1;
	}

	if (args[OPT_ARGS_DEBUG].existed())
		args_analyse_print(args);

	/* ����ʵ�ʵĹ��ܵ��ã������Ӧ�Ĺ��� */
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
		cout << "��1���ļ�[" << args[OPT_ARGS_FILE1].get_string() << "]�޷���." << endl;
		infile1.close();
		infile2.close();
		return -1;
	}
	else if (!infile2) {
		cout << "��2���ļ�[" << args[OPT_ARGS_FILE2].get_string() << "]�޷���." << endl;
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
	//TODO: ��ȫ������һ�飬����Ƿ���ĳһ�г�������ַ�����ͬʱ��ȡ��������
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
		cout << "�ļ�[" << args[OPT_ARGS_FILE1].get_string() << "]�ĵ�(" << rown1 + 1 << ")�в�����Ҫ�󣬳�����󳤶�[" << MAXN << "]." << endl;
	else if (args[OPT_ARGS_DEBUG].existed()) {
		cout << "��1���ļ��Ļ�����Ϣ��" << endl;
		_make_line(maxlen, display_mode);
		cout << "�� �� ����" << args[OPT_ARGS_FILE1].get_string() << endl;
		cout << "��    С��";
		infile1.seekg(0, ios::end);
		cout << infile1.tellg() << endl;
		infile1.seekg(0, ios::beg);
		cout << "��    ����" << rown1 << endl;
		cout << "����г���" << maxlen1 + 1 << endl;
		cout << "�ļ���ʽ��" << (sys1 == LINUX ? "Linux" : "Windows") << endl;
		_make_line(maxlen, display_mode);
		cout << endl;
	}
	if (status2 == -1)
		cout << "�ļ�[" << args[OPT_ARGS_FILE2].get_string() << "]�ĵ�(" << rown2 + 1 << ")�в�����Ҫ�󣬳�����󳤶�[" << MAXN << "]." << endl;
	else if (args[OPT_ARGS_DEBUG].existed()) {
		cout << "��2���ļ��Ļ�����Ϣ��" << endl;
		_make_line(maxlen, display_mode);
		cout << "�� �� ����" << args[OPT_ARGS_FILE2].get_string() << endl;
		cout << "��    С��";
		infile2.seekg(0, ios::end);
		cout << infile2.tellg() << endl;
		infile2.seekg(0, ios::beg);
		cout << "��    ����" << rown2 << endl;
		cout << "����г���" << maxlen2 + 1 << endl;
		cout << "�ļ���ʽ��" << (sys2 == LINUX ? "Linux" : "Windows") << endl;
		_make_line(maxlen, display_mode);
		cout << endl;
		cout << endl;
	}
	if (status1 == -1 || status2 == -1) {
		infile1.close();
		infile2.close();
		return -1;
	}
	//TODO: ����offset��skip
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
	//ѭ�����벢�Ƚϣ����뺯������trim��ignore_blank������ignore_blank�� line_offset�����ȼ�Ҫ�ߣ��ȽϺ�������CR_CRLF_not_equal��ѭ��������������max_diff��max_line
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
		cout << "�ȽϽ�������" << endl;
		_make_line(maxlen, display_mode);
	}
	else if (args[OPT_ARGS_DISPLAY].get_string() == "detailed") {
		cout << "�ȽϽ�������" << endl;
		_make_line(maxlen, display_mode);
	}
	else if (args[OPT_ARGS_DEBUG].existed()) {
		cout << "�ȽϽ�������" << endl;
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
		//////	if (eof1) {//��ʱ�ж�file2�����������Ƿ��ǿ���
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
		//////	if (eof2) {//��ʱ�ж�file1�����������Ƿ��ǿ���
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
				cout << "��ʼ��: " << setiosflags(ios::left) << setw(int_len(cur_line1 - 2) + 1) << cur_line1 - 2 << "/" << setw(int_len(cur_line2) + 1)
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
		cout << (count ? "�ļ���ͬ." : "�ļ���ͬ.") << endl;
	else if (args[OPT_ARGS_DEBUG].existed()) {
		if (!count) {
			cout << "��ָ�������������ȫһ��." << endl;
			_make_line(maxlen, display_mode);
		}
		else {
			_make_line(maxlen, display_mode);
			cout << "��ָ����������¹�" << count << "���в���"
				<< ((args[OPT_ARGS_MAX_DIFFNUM].get_int() && count == args[OPT_ARGS_MAX_DIFFNUM].get_int()) ? "[�ѵ��趨��������ֵ]" : "") << "." << endl;
			prompt();
			if (display_mode != DETAIL_MODE)
				cout << "	8����--display detailed���Եõ�����ϸ����Ϣ" << endl;
			_make_line(maxlen, display_mode);
		}
	}
	else {
		if (!count) {
			cout << "��ָ�������������ȫһ��." << endl;
			_make_line(maxlen, display_mode);
		}
		else {
			_make_line(maxlen, display_mode);
			cout << "��ָ����������¹�" << count << "���в���"
				<< ((args[OPT_ARGS_MAX_DIFFNUM].get_int() && count == args[OPT_ARGS_MAX_DIFFNUM].get_int()) ? "[�ѵ��趨��������ֵ]" : "") << "." << endl;
			prompt();
			if (display_mode != DETAIL_MODE)
				cout << "	8����--display detailed���Եõ�����ϸ����Ϣ" << endl;
			_make_line(maxlen, display_mode);
		}
	}
	//ѭ�����д���display
	infile1.close();
	infile2.close();
	return 0;
}
//TODO: demo���߼���ֻ�ж���'\n'�˲���Ϊ�ǻ��У�������<CR>��ʾ
//TODO: ���г��ȳ�����ΧҲ����Ӧ�ı���
//TODO: ���˹涨�Ĳ���ʾ�ַ���X��ʾ�⣬EOF�÷����ʾ,��Щ�ַ���<EMPTY>��Ҫ������������ָ�ļ�x����ͷ��һ��.<tmpty>���<CR>����Ϊһ�����бض���Ӧһ���س�
//TODO: Ĭ��\r\n��Ϊ\n����
//TODO: normal��detailed���������ں��߻���в������һ�е�hex��ӡ������ͬʱ�ѱ��Ҳ����ӡ����
//TODO: hex��ʽ�»����<EOF>,<EMPTY>,���ǲ������<CR>,ͬʱ��û����ɫ�ġ�����ֻ�е�����Ϊ��ʱ���Ż��ӡ��<EOF>�����߶��Ƕ����ӡ
//TODO: x/x�� ��һ���еĴ�����Ϣ�����֣����������ַ����бȽϳ���ʱ����ʾΪ"��[x]���ַ���ʼ�в���"�������ļ�1��һ���ַ���Ӧ������һ���ļ���<EMPTY>��<EOF>ʱ����ʾΪ���ļ�1��β���ж����ַ����������ļ�1��<EOF>��Ӧ�ļ�2��<CR>��<EMPTY>ʱ����ʾΪ���ļ�1�ѽ���/�ļ�2�������ݡ�
//TODO: display�������ȴ���msg�У���������еĳ��ȷ���Ҫ����һ�����
/*
�Ķ���ʾ��
1�������� xxx ���
2���ļ������� xxx ���
3��������ͬ��λ�õĲ����ַ�����ɫ���
4��ÿ���е�CR/LF/VT/BS/BEL��X���(���㿴�������ַ�)
5��ÿ��β�Ķ�����ַ�����ɫ�����CR/LF/VT/BS/BEL����ɫX���(���㿴�������ַ�)
6��ÿ������� xxx ���(���㿴�������ַ�)"
7��������Ϊ�������⣬����λ�ÿ��ܱ��ں��������ϣ����������ֶ���ɫ���
8����--display detailed���Եõ�����ϸ����Ϣ
*/

/* �����ļ�׼��
	1.txt �������ļ�
	2.txt ����1.txt�Ļ����ϣ�ĳЩ��ǰ���޿ո�
	3.txt ����1.txt�Ļ����ϣ�ĳЩ�к����޿ո�
	4.txt ����1.txt�Ļ����ϣ����һ��û�лس�
	5.txt ����1.txt�Ļ����ϣ���һЩ����
	6.txt ����1.txt�Ļ����ϣ���һЩ���У�����ĳЩ���пո��tab
	7.txt ����1.txt��ȫ��ͬ
	8.txt ����1.txt��Linux��ʽ��

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

rem ����ͬ������
txt_compare --file1 1.txt --file2 2.txt
txt_compare --file1 1.txt --file2 2.txt --trim right
txt_compare --file1 1.txt --file2 5.txt
txt_compare --file1 1.txt --file2 5.txt --trim right
txt_compare --file1 1.txt --file2 6.txt
txt_compare --file1 1.txt --file2 6.txt --ignore_blank
txt_compare --file1 1.txt --file2 8.txt --CR_CRLF_not_equal

*/
