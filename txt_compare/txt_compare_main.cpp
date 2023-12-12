/* 2251206 冯羽芯 计科 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include "../include/class_aat.h"
#include "../include/file.h"
#include "../include/cmd_console_tools.h"
//按需加入需要的头文件 
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

static const char* cut(const char* const argv0)
{
	const char* p = argv0;
	bool is_correct = false;
	for (p = argv0; *p != '\0'; p++) {
		const char* q = p;
		for (q = p; *q != '\0'; q++)
			if (*q == '\\') {
				is_correct = false;
				break;
			}
		if (*q == '\0') {
			is_correct = true;
			return p;
		}
	}
	return NULL;
}

static string trim_judge(int argc, char** argv)
{
	int i;
	for (i = 0; i < argc; i++)
		if (strcmp(argv[i], "--trim") == 0)
			return argv[i + 1];

	return "OK";
}

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
	strcpy(procname, cut(argv0)); //这句替换成自己的截取函数 

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
		args_analyse_tools("--help",			ST_EXTARGS_TYPE::boolean, 0, false),
		args_analyse_tools("--debug",			ST_EXTARGS_TYPE::boolean, 0, false),
		args_analyse_tools("--file1",			ST_EXTARGS_TYPE::str, 1, string("")),
		args_analyse_tools("--file2",			ST_EXTARGS_TYPE::str, 1, string("")),
		args_analyse_tools("--trim",			ST_EXTARGS_TYPE::str_with_set_error, 1, 0, TrimType),
		args_analyse_tools("--lineskip",		ST_EXTARGS_TYPE::int_with_default,   1, 0, 0, 100),
		args_analyse_tools("--lineoffset",		ST_EXTARGS_TYPE::int_with_default,   1, 0, -100, 100),
		args_analyse_tools("--ignore_blank",	ST_EXTARGS_TYPE::boolean, 0, false),
		args_analyse_tools("--CR_CRLF_not_equal",ST_EXTARGS_TYPE::boolean, 0, false),
		args_analyse_tools("--max_diff",		ST_EXTARGS_TYPE::int_with_default,   1, 0, 0, 100),
		args_analyse_tools("--max_line",		ST_EXTARGS_TYPE::int_with_default,   1, 0, 0, 10000),
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

	string trim_type;
	trim_type = trim_judge(argc, argv);

	if (args[OPT_ARGS_CR_CRLF_NOT_EQUAL].existed() && (trim_type == "right" || trim_type == "all")) {
		usage(argv[0]);
		cout << "参数[" << args[OPT_ARGS_CR_CRLF_NOT_EQUAL].get_name() << "]不能和[" << args[OPT_ARGS_TRIM].get_name() << " right/all]同时存在." << endl;
		return -1;
	}

	if (args[OPT_ARGS_DEBUG].existed())
		args_analyse_print(args);

	/* 进入实际的功能调用，完成相应的功能 */
	ifstream fin1;
	ifstream fin2;

	if (args[OPT_ARGS_CR_CRLF_NOT_EQUAL].existed() == 1) {
		fin1.open(args[OPT_ARGS_FILE1].get_string(), ios::in | ios::binary);
		fin2.open(args[OPT_ARGS_FILE2].get_string(), ios::in | ios::binary);
	}
	else {
		fin1.open(args[OPT_ARGS_FILE1].get_string(), ios::in);
		fin2.open(args[OPT_ARGS_FILE2].get_string(), ios::in);
	}

	string str1, str2;
	char* s1 = NULL, * s2 = NULL;
	bool is_same;
	int correct = 0, diff = 0, count = 0;
	int width = 0, line_maxlen = 0;
	int line1 = 0, line2 = 0;
	int len1 = 0, len2 = 0;
	bool is_offset = false, is_skipped = false;
	if (fin1.is_open() == 0) {
		cout << "第1个文件[" << args[OPT_ARGS_FILE1].get_string() << "]无法打开.\n";
		return -1;
	}
	if (fin2.is_open() == 0) {
		cout << "第2个文件[" << args[OPT_ARGS_FILE2].get_string() << "]无法打开.\n";
		return -1;
	}

	//计算line_maxlen
	if (args[OPT_ARGS_DISPLAY].existed() == 1) {
		while (fin1.eof() == 0 && fin2.eof() == 0) { // 任何一个读到eof就会寄，不会再读了

			if (args[OPT_ARGS_MAX_DIFFNUM].existed() == 1 && diff == args[OPT_ARGS_MAX_DIFFNUM].get_int())
				break;
			if (args[OPT_ARGS_MAX_LINENUM].existed() == 1 && count == args[OPT_ARGS_MAX_LINENUM].get_int())
				break;

			getline(fin1, str1);
			getline(fin2, str2);
			s1 = new(nothrow)char[str1.length() + 1];
			if (s1 == NULL) {
				cout << "No Memory" << endl;
				return OVERFLOW;
			}
			s2 = new(nothrow)char[str2.length() + 1];
			if (s2 == NULL) {
				cout << "No Memory" << endl;
				return OVERFLOW;
			}
			strcpy(s1, str1.c_str());
			strcpy(s2, str2.c_str());
			line1++;
			line2++;

			// trim
			if (args[OPT_ARGS_TRIM].existed() == 1) {
				if (args[OPT_ARGS_TRIM].get_string() == "right") {
					trimright(s1);
					trimright(s2);
				}
				if (args[OPT_ARGS_TRIM].get_string() == "left") {
					trimleft(s1);
					trimleft(s2);
				}
				if (args[OPT_ARGS_TRIM].get_string() == "all") {
					trimleft(s1);
					trimleft(s2);
					trimright(s1);
					trimright(s2);
				}
			}
			// ignore_blank
			if (args[OPT_ARGS_IGNORE_BLANK].existed() == 1) {
				//再读一行 
				while (strcmp(s1, "") == 0 && fin1.eof() == 0) {
					getline(fin1, str1);
					delete[]s1;
					s1 = new(nothrow)char[str1.length() + 1];
					if (s1 == NULL) {
						cout << "No Memory" << endl;
						return OVERFLOW;
					}
					strcpy(s1, str1.c_str());
					if (args[OPT_ARGS_TRIM].existed() == 1) {
						if (args[OPT_ARGS_TRIM].get_string() == "right")
							trimright(s1);
						if (args[OPT_ARGS_TRIM].get_string() == "left")
							trimleft(s1);
						if (args[OPT_ARGS_TRIM].get_string() == "all") {
							trimleft(s1);
							trimright(s1);
						}
					}

				}
				while (strcmp(s2, "") == 0 && fin2.eof() == 0) {
					getline(fin2, str2);
					delete[]s2;
					s2 = new(nothrow)char[str2.length() + 1];
					if (s2 == NULL) {
						cout << "No Memory" << endl;
						return OVERFLOW;
					}
					strcpy(s2, str2.c_str());
					if (args[OPT_ARGS_TRIM].existed() == 1) {
						if (args[OPT_ARGS_TRIM].get_string() == "right")
							trimright(s2);
						if (args[OPT_ARGS_TRIM].get_string() == "left")
							trimleft(s2);
						if (args[OPT_ARGS_TRIM].get_string() == "all") {
							trimleft(s2);
							trimright(s2);
						}
					}
				}
			}
			// lineoffset
			if (args[OPT_ARGS_LINE_OFFSET].existed() == 1 && is_offset == false) {
				int offset;
				offset = args[OPT_ARGS_LINE_OFFSET].get_int();

				if (offset < 0) { // 文件1
					int abs_offset = -offset;
					for (int i = 1; i <= abs_offset; i++) {
						getline(fin1, str1);
						line1++;

						if (args[OPT_ARGS_IGNORE_BLANK].existed() == 1)
							while (str1 == "") {
								getline(fin1, str1);
								delete[]s1;
								s1 = new(nothrow)char[str1.length() + 1];
								if (s1 == NULL) {
									cout << "No Memory" << endl;
									return OVERFLOW;
								}
								strcpy(s1, str1.c_str());
							}
					}

					s1 = new(nothrow)char[str1.length() + 1];
					if (s1 == NULL) {
						cout << "No Memory" << endl;
						return OVERFLOW;
					}
					strcpy(s1, str1.c_str());
				}

				if (offset > 0) { // 文件2
					for (int i = 1; i <= offset; i++) {
						getline(fin2, str2);
						line2++;

						if (args[OPT_ARGS_IGNORE_BLANK].existed() == 1)
							while (str2 == "") {
								getline(fin2, str2);
								delete[]s2;
								s2 = new(nothrow)char[str2.length() + 1];
								if (s2 == NULL) {
									cout << "No Memory" << endl;
									return OVERFLOW;
								}
								strcpy(s2, str2.c_str());
							}
					}

					s2 = new(nothrow)char[str2.length() + 1];
					if (s2 == NULL) {
						cout << "No Memory" << endl;
						return OVERFLOW;
					}
					strcpy(s2, str2.c_str());
				}
				is_offset = true;
			}
			// lineskip
			if (args[OPT_ARGS_LINE_SKIP].existed() == 1 && is_skipped == false) {
				int skip = args[OPT_ARGS_LINE_SKIP].get_int();

				for (int i = 1; i <= skip; i++) {
					getline(fin1, str1);
					line1++;

					if (args[OPT_ARGS_IGNORE_BLANK].existed() == 1)
						while (str1 == "") {
							getline(fin1, str1);
							delete[]s1;
							s1 = new(nothrow)char[str1.length() + 1];
							if (s1 == NULL) {
								cout << "No Memory" << endl;
								return OVERFLOW;
							}
							strcpy(s1, str1.c_str());
						}
				}

				s1 = new(nothrow)char[str1.length() + 1];
				if (s1 == NULL) {
					cout << "No Memory" << endl;
					return OVERFLOW;
				}
				strcpy(s1, str1.c_str());

				for (int i = 1; i <= skip; i++) {
					getline(fin2, str2);
					line2++;

					if (args[OPT_ARGS_IGNORE_BLANK].existed() == 1)
						while (str2 == "") {
							getline(fin2, str2);
							delete[]s2;
							s2 = new(nothrow)char[str2.length() + 1];
							if (s2 == NULL) {
								cout << "No Memory" << endl;
								return OVERFLOW;
							}
							strcpy(s2, str2.c_str());
						}
				}

				s2 = new(nothrow)char[str2.length() + 1];
				if (s2 == NULL) {
					cout << "No Memory" << endl;
					return OVERFLOW;
				}
				strcpy(s2, str2.c_str());

				is_skipped = true;
			}

			int cmp = strcmp(s1, s2);
			bool equal = true;
			count++;

			if (cmp == 0 && args[OPT_ARGS_IGNORE_BLANK].existed() == 1) {
				if (fin1.eof() == 1 && fin2.eof() == 0) {
					while (fin2.eof() == 0) {
						getline(fin2, str2);
						if (str2 != "") {
							equal = false;
							break;
						}
					}
				}
				else if (fin2.eof() == 1 && fin1.eof() == 0) {
					while (fin1.eof() == 0) {
						getline(fin1, str1);
						if (str1 != "") {
							equal = false;
							break;
						}
					}
				}
			}

			if (cmp == 0 && fin1.eof() == fin2.eof() && equal == true) {
				is_same = true;
				correct++;
			}
			else {
				is_same = false;
				diff++;
				len1 = strlen(s1);
				if (len1 == 0) {//empty
					if (fin1.eof() == 1)
						len1 = 12;
					else
						len1 = 11;
				}
				else {
					if (fin1.eof() == 1) //eof
						len1 += 5;
					else //cr
						len1 += 4;
				}

				len2 = strlen(s2);
				if (len2 == 0) {//empty
					if (fin2.eof() == 1)
						len2 = 12;
					else
						len2 = 11;
				}
				else {
					if (fin2.eof() == 1) //eof
						len2 += 5;
					else //cr
						len2 += 4;
				}

				int maxlen = max(len1, len2);
				if (line_maxlen < maxlen)
					line_maxlen = maxlen;
			}

			delete[]s1;
			delete[]s2;
		}
		width = (line_maxlen / 10 + 1) * 10 + 8 + 2;
		if (args[OPT_ARGS_DISPLAY].get_string() == "detailed" && width < 80)
			width = 80;
		cout << "比较结果输出：" << endl;
		for (int i = 1; i <= width; i++)
			cout << '=';
		cout << endl;
	}

	//清零重新开始读
	correct = 0, diff = 0, count = 0;
	line1 = 0, line2 = 0;
	is_skipped = false;
	is_offset = false;
	fin1.clear();
	fin2.clear();
	fin1.seekg(0, ios::beg);
	fin2.seekg(0, ios::beg);

	while (fin1.eof() == 0 && fin2.eof() == 0) { // 任何一个读到eof就会寄，不会再读了

		if (args[OPT_ARGS_MAX_DIFFNUM].existed() == 1 && diff == args[OPT_ARGS_MAX_DIFFNUM].get_int())
			break;
		if (args[OPT_ARGS_MAX_LINENUM].existed() == 1 && count == args[OPT_ARGS_MAX_LINENUM].get_int())
			break;

		getline(fin1, str1);
		getline(fin2, str2);
		s1 = new(nothrow)char[str1.length() + 1];
		if (s1 == NULL) {
			cout << "No Memory" << endl;
			return OVERFLOW;
		}
		s2 = new(nothrow)char[str2.length() + 1];
		if (s2 == NULL) {
			cout << "No Memory" << endl;
			return OVERFLOW;
		}
		strcpy(s1, str1.c_str());
		strcpy(s2, str2.c_str());
		line1++;
		line2++;

		// trim
		if (args[OPT_ARGS_TRIM].existed() == 1) {
			if (args[OPT_ARGS_TRIM].get_string() == "right") {
				trimright(s1);
				trimright(s2);
			}
			if (args[OPT_ARGS_TRIM].get_string() == "left") {
				trimleft(s1);
				trimleft(s2);
			}
			if (args[OPT_ARGS_TRIM].get_string() == "all") {
				trimleft(s1);
				trimleft(s2);
				trimright(s1);
				trimright(s2);
			}
		}
		// ignore_blank
		if (args[OPT_ARGS_IGNORE_BLANK].existed() == 1) {
			//再读一行

			while (strcmp(s1, "") == 0 && fin1.eof() == 0) {
				getline(fin1, str1);
				delete[]s1;
				s1 = new(nothrow)char[str1.length() + 1];
				if (s1 == NULL) {
					cout << "No Memory" << endl;
					return OVERFLOW;
				}
				strcpy(s1, str1.c_str());
				if (args[OPT_ARGS_TRIM].existed() == 1) {
					if (args[OPT_ARGS_TRIM].get_string() == "right")
						trimright(s1);
					if (args[OPT_ARGS_TRIM].get_string() == "left")
						trimleft(s1);
					if (args[OPT_ARGS_TRIM].get_string() == "all") {
						trimleft(s1);
						trimright(s1);
					}
				}

			}
			while (strcmp(s2, "") == 0 && fin2.eof() == 0) {
				getline(fin2, str2);
				delete[]s2;
				s2 = new(nothrow)char[str2.length() + 1];
				if (s2 == NULL) {
					cout << "No Memory" << endl;
					return OVERFLOW;
				}
				strcpy(s2, str2.c_str());
				if (args[OPT_ARGS_TRIM].existed() == 1) {
					if (args[OPT_ARGS_TRIM].get_string() == "right")
						trimright(s2);
					if (args[OPT_ARGS_TRIM].get_string() == "left")
						trimleft(s2);
					if (args[OPT_ARGS_TRIM].get_string() == "all") {
						trimleft(s2);
						trimright(s2);
					}
				}
			}
		}
		// lineoffset
		if (args[OPT_ARGS_LINE_OFFSET].existed() == 1 && is_offset == false) {
			int offset;
			offset = args[OPT_ARGS_LINE_OFFSET].get_int();

			if (offset < 0) { // 文件1
				int abs_offset = -offset;
				for (int i = 1; i <= abs_offset; i++) {
					getline(fin1, str1);
					line1++;

					if (args[OPT_ARGS_IGNORE_BLANK].existed() == 1)
						while (str1 == "") {
							getline(fin1, str1);
							delete[]s1;
							s1 = new(nothrow)char[str1.length() + 1];
							if (s1 == NULL) {
								cout << "No Memory" << endl;
								return OVERFLOW;
							}
							strcpy(s1, str1.c_str());
						}
				}

				s1 = new(nothrow)char[str1.length() + 1];
				if (s1 == NULL) {
					cout << "No Memory" << endl;
					return OVERFLOW;
				}
				strcpy(s1, str1.c_str());
			}

			if (offset > 0) { // 文件2
				for (int i = 1; i <= offset; i++) {
					getline(fin2, str2);
					line2++;

					if (args[OPT_ARGS_IGNORE_BLANK].existed() == 1)
						while (str2 == "") {
							getline(fin2, str2);
							delete[]s2;
							s2 = new(nothrow)char[str2.length() + 1];
							if (s2 == NULL) {
								cout << "No Memory" << endl;
								return OVERFLOW;
							}
							strcpy(s2, str2.c_str());
						}
				}

				s2 = new(nothrow)char[str2.length() + 1];
				if (s2 == NULL) {
					cout << "No Memory" << endl;
					return OVERFLOW;
				}
				strcpy(s2, str2.c_str());
			}
			is_offset = true;
		}
		// lineskip
		if (args[OPT_ARGS_LINE_SKIP].existed() == 1 && is_skipped == false) {
			int skip = args[OPT_ARGS_LINE_SKIP].get_int();

			for (int i = 1; i <= skip; i++) {
				getline(fin1, str1);
				line1++;

				if (args[OPT_ARGS_IGNORE_BLANK].existed() == 1)
					while (str1 == "") {
						getline(fin1, str1);
						delete[]s1;
						s1 = new(nothrow)char[str1.length() + 1];
						if (s1 == NULL) {
							cout << "No Memory" << endl;
							return OVERFLOW;
						}
						strcpy(s1, str1.c_str());
					}
			}

			s1 = new(nothrow)char[str1.length() + 1];
			if (s1 == NULL) {
				cout << "No Memory" << endl;
				return OVERFLOW;
			}
			strcpy(s1, str1.c_str());

			for (int i = 1; i <= skip; i++) {
				getline(fin2, str2);
				line2++;

				if (args[OPT_ARGS_IGNORE_BLANK].existed() == 1)
					while (str2 == "") {
						getline(fin2, str2);
						delete[]s2;
						s2 = new(nothrow)char[str2.length() + 1];
						if (s2 == NULL) {
							cout << "No Memory" << endl;
							return OVERFLOW;
						}
						strcpy(s2, str2.c_str());
					}
			}

			s2 = new(nothrow)char[str2.length() + 1];
			if (s2 == NULL) {
				cout << "No Memory" << endl;
				return OVERFLOW;
			}
			strcpy(s2, str2.c_str());

			is_skipped = true;
		}

		int cmp = strcmp(s1, s2);
		bool equal = true;
		count++;

		if (cmp == 0 && args[OPT_ARGS_IGNORE_BLANK].existed() == 1) {
			if (fin1.eof() == 1 && fin2.eof() == 0) {
				while (fin2.eof() == 0) {
					getline(fin2, str2);
					if (str2 != "") {
						equal = false;
						break;
					}
				}
			}
			else if (fin2.eof() == 1 && fin1.eof() == 0) {
				while (fin1.eof() == 0) {
					getline(fin1, str1);
					if (str1 != "") {
						equal = false;
						break;
					}
				}
			}
		}

		if (cmp == 0 && fin1.eof() == fin2.eof() && equal == true) {
			is_same = true;
			correct++;
		}
		else {
			is_same = false;
			diff++;
		}

		if (is_same == true) {
			delete[]s1;
			delete[]s2;
			continue;
		}
		else {
			if (args[OPT_ARGS_DISPLAY].existed() == 0) {
				cout << "文件不同.\n";
				return 0;
			}
			else {

				// 显示关键部份信息
				cout << "第[" << line1 << " / " << line2 << "]行 - ";
				len1 = strlen(s1);
				len2 = strlen(s2);
				int minlen = min(len1, len2);
				int i, type;
				// 差异类别判断
				for (i = 0; i < minlen; i++) {
					if (s1[i] != s2[i]) {
						cout << "第[" << i << "]个字符开始有差异：" << endl;
						type = 0;
						break;
					}
				}
				if (i == minlen) {
					if (len1 < len2) {
						cout << "文件2的尾部有多余字符：" << endl;
						type = 1;
					}
					if (len2 < len1) {
						cout << "文件1的尾部有多余字符：" << endl;
						type = 2;
					}
					if (len1 == len2) {
						if (fin1.eof() == 1 && fin2.eof() == 0) {
							cout << "文件1已结束/文件2仍有内容：" << endl;
							type = 3;
						}
						if (fin2.eof() == 1 && fin1.eof() == 0) {
							cout << "文件2已结束/文件1仍有内容：" << endl;
							type = 4;
						}
					}
				}

				if (args[OPT_ARGS_DISPLAY].get_string() == "detailed") {
					//标尺
					//(line_maxlen / 10 + 1) * 10

					int maxlen = max(len1, len2);
					int hyphen = (maxlen / 10 + 1) * 10;
					int times = maxlen / 10 + 1;

					cout << "        ";
					for (int i = 1; i <= hyphen; i++)
						cout << '-';
					cout << endl;
					cout << "        ";
					for (int i = 1; i <= times; i++)
						cout << (i - 1) % 10 << "         ";
					cout << endl;
					cout << "        ";
					for (int i = 1; i <= times; i++)
						cout << "0123456789";
					cout << endl;
					cout << "        ";
					for (int i = 1; i <= hyphen; i++)
						cout << '-';
					cout << endl;
				}

				//读文件
				cout << "文件1 : ";
				if (str1 == "" && fin1.eof() == 0) {
					cct_setcolor(COLOR_HYELLOW, COLOR_HRED);
					cout << "<EMPTY>";
					cct_setcolor();
				}
				else {
					for (i = 0; i < minlen; i++) {
						if (s1[i] != s2[i]) {
							cct_setcolor(COLOR_HYELLOW, COLOR_HRED);
							if (s1[i] == '\r' || s1[i] == '\n' || s1[i] == '\t' || s1[i] == '\b' || s1[i] == '\a')
								cout << 'X';
							else
								cout << s1[i];
							cct_setcolor();
						}
						else {
							if (s1[i] == '\r' || s1[i] == '\n' || s1[i] == '\t' || s1[i] == '\b' || s1[i] == '\a')
								cout << 'X';
							else
								cout << s1[i];
						}
					}
					for (i = minlen; i < len1; i++) {
						cct_setcolor(COLOR_HYELLOW, COLOR_HRED);
						if (s1[i] == '\r' || s1[i] == '\n' || s1[i] == '\t' || s1[i] == '\b' || s1[i] == '\a')
							cout << 'X';
						else
							cout << s1[i];
						cct_setcolor();
					}
				}
				if (fin1.eof() == 1)
					cout << "<EOF>";
				else
					cout << "<CR>";
				cout << endl;

				cout << "文件2 : ";
				if (str2 == "" && fin2.eof() == 0) {
					cct_setcolor(COLOR_HYELLOW, COLOR_HRED);
					cout << "<EMPTY>";
					cct_setcolor();
				}
				else {
					for (i = 0; i < minlen; i++) {
						if (s1[i] != s2[i]) {
							cct_setcolor(COLOR_HYELLOW, COLOR_HRED);
							if (s2[i] == '\r' || s2[i] == '\n' || s2[i] == '\t' || s2[i] == '\b' || s2[i] == '\a')
								cout << 'X';
							else
								cout << s2[i];
							cct_setcolor();
						}
						else {
							if (s2[i] == '\r' || s2[i] == '\n' || s2[i] == '\t' || s2[i] == '\b' || s2[i] == '\a')
								cout << 'X';
							else
								cout << s2[i];
						}
					}
					for (i = minlen; i < len2; i++) {
						cct_setcolor(COLOR_HYELLOW, COLOR_HRED);
						if (s2[i] == '\r' || s2[i] == '\n' || s2[i] == '\t' || s2[i] == '\b' || s2[i] == '\a')
							cout << 'X';
						else
							cout << s2[i];
						cct_setcolor();
					}
				}
				if (fin2.eof() == 1)
					cout << "<EOF>";
				else
					cout << "<CR>";
				cout << endl;

				//hex方式
				if (args[OPT_ARGS_DISPLAY].get_string() == "detailed") {
					cout << "文件1(HEX) :" << endl;
					filetohex(s1, fin1.eof());
					cout << "文件2(HEX) :" << endl;
					filetohex(s2, fin2.eof());
				}
				cout << endl;
			}
			delete[]s1;
			delete[]s2;
		}
	}

	if (correct == count)
		if (args[OPT_ARGS_DISPLAY].existed() == 0) {
			cout << "文件相同.\n";
			return 0;
		}
		else {
			cout << "在指定检查条件下完全一致." << endl;
			for (int i = 1; i <= width; i++)
				cout << '=';
			cout << endl;
			return 0;
		}
	if (correct != count && args[OPT_ARGS_DISPLAY].existed() == 1) {
		for (int i = 1; i <= width; i++)
			cout << '=';
		cout << endl;
		cout << "在指定检查条件下共" << diff << "行有差异." << endl;
		cout << "阅读提示：" << endl;
		cout << "        " << "1、空行用<EMPTY>标出" << endl;
		cout << "        " << "2、文件结束用<EOF>标出" << endl;
		cout << "        " << "3、两行相同列位置的差异字符用亮色标出" << endl;
		cout << "        " << "4、每行中的CR/LF/VT/BS/BEL用X标出(方便看清隐含字符)" << endl;
		cout << "        " << "5、每行尾的多余的字符用亮色标出，CR/LF/VT/BS/BEL用亮色X标出(方便看清隐含字符)" << endl;
		cout << "        " << "6、每行最后用<CR>标出(方便看清隐含字符)" << endl;
		cout << "        " << "7、中文因为编码问题，差异位置可能报在后半个汉字上，但整个汉字都亮色标出" << endl;
		if (args[OPT_ARGS_DISPLAY].get_string() == "normal")
			cout << "        " << "8、用--display detailed可以得到更详细的信息" << endl;
		for (int i = 1; i <= width; i++)
			cout << '=';
		cout << endl;
	}

	/*delete[]s1;
	delete[]s2;*/
	return 0;
}

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

#if 0
//分隔行===的宽度计算 
int width = (this->line_maxlen / 10 + 1) * 10 + 8 + 2; //比---的标尺多2个：line_maxlen向上取10倍整数，8是"文件1 : "

/* 如果加了hex输出，则最小宽度为80 */
if (this->display_detailed && width < 80)
	width = 80;
#endif

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
txt_compare --file1 1.txt --file2 5.txt --display detailed
txt_compare --file1 1.txt --file2 5.txt --trim right --display detailed
txt_compare --file1 1.txt --file2 6.txt --display detailed
txt_compare --file1 1.txt --file2 6.txt --ignore_blank --display detailed
txt_compare --file1 1.txt --file2 8.txt --CR_CRLF_not_equal --display detailed

*/
