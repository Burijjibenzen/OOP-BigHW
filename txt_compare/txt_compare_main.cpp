/* 2251206 ����о �ƿ� */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include "../include/class_aat.h"
#include "../include/file.h"
#include "../include/cmd_console_tools.h"
//���������Ҫ��ͷ�ļ� 
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
	strcpy(procname, cut(argv0)); //����滻���Լ��Ľ�ȡ���� 

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

	string trim_type;
	trim_type = trim_judge(argc, argv);

	if (args[OPT_ARGS_CR_CRLF_NOT_EQUAL].existed() && (trim_type == "right" || trim_type == "all")) {
		usage(argv[0]);
		cout << "����[" << args[OPT_ARGS_CR_CRLF_NOT_EQUAL].get_name() << "]���ܺ�[" << args[OPT_ARGS_TRIM].get_name() << " right/all]ͬʱ����." << endl;
		return -1;
	}

	if (args[OPT_ARGS_DEBUG].existed())
		args_analyse_print(args);

	/* ����ʵ�ʵĹ��ܵ��ã������Ӧ�Ĺ��� */
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
		cout << "��1���ļ�[" << args[OPT_ARGS_FILE1].get_string() << "]�޷���.\n";
		return -1;
	}
	if (fin2.is_open() == 0) {
		cout << "��2���ļ�[" << args[OPT_ARGS_FILE2].get_string() << "]�޷���.\n";
		return -1;
	}

	//����line_maxlen
	if (args[OPT_ARGS_DISPLAY].existed() == 1) {
		while (fin1.eof() == 0 && fin2.eof() == 0) { // �κ�һ������eof�ͻ�ģ������ٶ���

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
				//�ٶ�һ�� 
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

				if (offset < 0) { // �ļ�1
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

				if (offset > 0) { // �ļ�2
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
		cout << "�ȽϽ�������" << endl;
		for (int i = 1; i <= width; i++)
			cout << '=';
		cout << endl;
	}

	//�������¿�ʼ��
	correct = 0, diff = 0, count = 0;
	line1 = 0, line2 = 0;
	is_skipped = false;
	is_offset = false;
	fin1.clear();
	fin2.clear();
	fin1.seekg(0, ios::beg);
	fin2.seekg(0, ios::beg);

	while (fin1.eof() == 0 && fin2.eof() == 0) { // �κ�һ������eof�ͻ�ģ������ٶ���

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
			//�ٶ�һ��

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

			if (offset < 0) { // �ļ�1
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

			if (offset > 0) { // �ļ�2
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
				cout << "�ļ���ͬ.\n";
				return 0;
			}
			else {

				// ��ʾ�ؼ�������Ϣ
				cout << "��[" << line1 << " / " << line2 << "]�� - ";
				len1 = strlen(s1);
				len2 = strlen(s2);
				int minlen = min(len1, len2);
				int i, type;
				// ��������ж�
				for (i = 0; i < minlen; i++) {
					if (s1[i] != s2[i]) {
						cout << "��[" << i << "]���ַ���ʼ�в��죺" << endl;
						type = 0;
						break;
					}
				}
				if (i == minlen) {
					if (len1 < len2) {
						cout << "�ļ�2��β���ж����ַ���" << endl;
						type = 1;
					}
					if (len2 < len1) {
						cout << "�ļ�1��β���ж����ַ���" << endl;
						type = 2;
					}
					if (len1 == len2) {
						if (fin1.eof() == 1 && fin2.eof() == 0) {
							cout << "�ļ�1�ѽ���/�ļ�2�������ݣ�" << endl;
							type = 3;
						}
						if (fin2.eof() == 1 && fin1.eof() == 0) {
							cout << "�ļ�2�ѽ���/�ļ�1�������ݣ�" << endl;
							type = 4;
						}
					}
				}

				if (args[OPT_ARGS_DISPLAY].get_string() == "detailed") {
					//���
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

				//���ļ�
				cout << "�ļ�1 : ";
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

				cout << "�ļ�2 : ";
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

				//hex��ʽ
				if (args[OPT_ARGS_DISPLAY].get_string() == "detailed") {
					cout << "�ļ�1(HEX) :" << endl;
					filetohex(s1, fin1.eof());
					cout << "�ļ�2(HEX) :" << endl;
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
			cout << "�ļ���ͬ.\n";
			return 0;
		}
		else {
			cout << "��ָ�������������ȫһ��." << endl;
			for (int i = 1; i <= width; i++)
				cout << '=';
			cout << endl;
			return 0;
		}
	if (correct != count && args[OPT_ARGS_DISPLAY].existed() == 1) {
		for (int i = 1; i <= width; i++)
			cout << '=';
		cout << endl;
		cout << "��ָ����������¹�" << diff << "���в���." << endl;
		cout << "�Ķ���ʾ��" << endl;
		cout << "        " << "1��������<EMPTY>���" << endl;
		cout << "        " << "2���ļ�������<EOF>���" << endl;
		cout << "        " << "3��������ͬ��λ�õĲ����ַ�����ɫ���" << endl;
		cout << "        " << "4��ÿ���е�CR/LF/VT/BS/BEL��X���(���㿴�������ַ�)" << endl;
		cout << "        " << "5��ÿ��β�Ķ�����ַ�����ɫ�����CR/LF/VT/BS/BEL����ɫX���(���㿴�������ַ�)" << endl;
		cout << "        " << "6��ÿ�������<CR>���(���㿴�������ַ�)" << endl;
		cout << "        " << "7��������Ϊ�������⣬����λ�ÿ��ܱ��ں��������ϣ����������ֶ���ɫ���" << endl;
		if (args[OPT_ARGS_DISPLAY].get_string() == "normal")
			cout << "        " << "8����--display detailed���Եõ�����ϸ����Ϣ" << endl;
		for (int i = 1; i <= width; i++)
			cout << '=';
		cout << endl;
	}

	/*delete[]s1;
	delete[]s2;*/
	return 0;
}

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

#if 0
//�ָ���===�Ŀ�ȼ��� 
int width = (this->line_maxlen / 10 + 1) * 10 + 8 + 2; //��---�ı�߶�2����line_maxlen����ȡ10��������8��"�ļ�1 : "

/* �������hex���������С���Ϊ80 */
if (this->display_detailed && width < 80)
	width = 80;
#endif

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
txt_compare --file1 1.txt --file2 5.txt --display detailed
txt_compare --file1 1.txt --file2 5.txt --trim right --display detailed
txt_compare --file1 1.txt --file2 6.txt --display detailed
txt_compare --file1 1.txt --file2 6.txt --ignore_blank --display detailed
txt_compare --file1 1.txt --file2 8.txt --CR_CRLF_not_equal --display detailed

*/
