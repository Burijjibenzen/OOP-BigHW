/* 2251206 ����о �ƿ� */
#define _CRT_SECURE_NO_WARNINGS
//���������Ҫ��ͷ�ļ� 
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>

#include "../include/class_aat.h"
#include "../include/class_crt.h"
#include "../include/file.h"
#include "../include/hw_check.h"
#include "../include_mariadb_x86/mysql/mysql.h"      // mysql����

using namespace std;

const string Action_Name[] = { "base","firstline","secondline","" };
const char* suffix[] = { ".h",".hpp",".c",".cpp","all","" };

enum HW_ARGS {
	HW_ARGS_HELP = 0,
	HW_ARGS_DEBUG,
	HW_ARGS_ACTION,
	HW_ARGS_CNO,
	HW_ARGS_STU,
	HW_ARGS_FILE,
	HW_ARGS_CHAPTER,
	HW_ARGS_WEEK,
	HW_ARGS_DISPLAY,
	HW_ARGS_CFGFILE,
};

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
 ***************************************************************************/
static void usage(const char* const full_procname)
{
	const char* procname = strrchr(full_procname, '\\');
	if (procname == NULL)
		procname = full_procname;

	const int wkey = 7 + strlen(procname) + 1;
	const int wopt = 7 + strlen(procname) + 4;
	cout << endl;

	cout << "Usage: " << procname << " ��ѡ��/��ѡ��" << endl;
	cout << endl;
	cout << setw(wkey) << ' ' << "��ѡ�ָ������" << endl;
	cout << setw(wopt) << ' ' << "--action opname : ֧�ֵ�opname����" << endl;
	cout << setw(wopt) << ' ' << "\t base              : �������(�ļ��Ƿ��ύ���Ƿ񱻸Ķ��������Ƿ���ȷ)" << endl;
	cout << setw(wopt) << ' ' << "\t firstline         : ���м�飨��Դ�����ļ���Ҫ��" << endl;
	cout << setw(wopt) << ' ' << "\t secondline        : ���м�飨������Դ�����ļ���Ҫ��" << endl;

	cout << setw(wkey) << ' ' << "��ѡ�ָ���κ�" << endl;
	cout << setw(wopt) << ' ' << "--cno course_no     : �κ�" << endl;

	cout << setw(wkey) << ' ' << "��ѡ�ָ��ѧ��" << endl;
	cout << setw(wopt) << ' ' << "--stu no/all        : ָ������/ȫ��(7λ����Ϊѧ��,allΪȫ��)" << endl;

	cout << setw(wkey) << ' ' << "��ѡ�ָ���ļ�" << endl;
	cout << setw(wopt) << ' ' << "--file filename/all : �����ļ���/ȫ��(allΪȫ��,����Ϊ�����ļ���)" << endl;

	cout << setw(wkey) << ' ' << "��ѡ�" << endl;
	cout << setw(wopt) << ' ' << "--chapter n         : ��--file�Ļ������ٽ����½ڵ�ɸѡ(��/-1��ȫ���½�,����--week����)" << endl;
	cout << setw(wopt) << ' ' << "--week n            : ��--file�Ļ������ٽ����ܴε�ɸѡ(��/-1��ȫ���ܴ�,����--chapter����)" << endl;
	cout << setw(wopt) << ' ' << "--display xxxxx     : ÿλ0/1�ֱ��ʾ������Ϣ/δ�ύ��Ϣ/������Ϣ/������Ϣ/���ش�����Ϣ" << endl;
	cout << setw(wopt) << ' ' << "--cfgfile filename  : ָ�������ļ���(ȱʡ:hw_check.conf)" << endl;
	cout << endl;

	const char* DEMO_CNO = "10108001";
	const char* DEMO_SRC_FNAME = "12-b1.cpp";
	const char* DEMO_STUNO = "2259999";

	cout << "e.g.   " << procname << " --action base --cno " << DEMO_CNO << " --stu all --file all             : ���" << DEMO_CNO << "����ѧ����������ҵ�Ļ�����Ϣ" << endl;
	cout << "       " << procname << " --action base --cno " << DEMO_CNO << " --stu all --file all --chapter 4 : ���" << DEMO_CNO << "����ѧ���ĵ�4����ҵ�Ļ�����Ϣ" << endl;
	cout << "       " << procname << " --action base --cno " << DEMO_CNO << " --stu all --file all --week 6    : ���" << DEMO_CNO << "����ѧ���ĵ�6����ҵ�Ļ�����Ϣ" << endl;
	cout << "       " << procname << " --action base --cno " << DEMO_CNO << " --stu " << DEMO_STUNO << " --file all         : ���" << DEMO_CNO << "��" << DEMO_STUNO << "ѧ����������ҵ�Ļ�����Ϣ" << endl;
	cout << "       " << procname << " --action base --cno " << DEMO_CNO << " --stu " << DEMO_STUNO << " --file " << DEMO_SRC_FNAME << "   : ���" << DEMO_CNO << "��" << DEMO_STUNO << "ѧ����" << DEMO_SRC_FNAME << "��ҵ�Ļ�����Ϣ" << endl;
	cout << endl;

	cout << "       " << procname << " --action firstline --cno " << DEMO_CNO << " --stu all --file all             : ���" << DEMO_CNO << "����ѧ����������ҵ��������Ϣ" << endl;
	cout << "       " << procname << " --action firstline --cno " << DEMO_CNO << " --stu all --file all --chapter 4 : ���" << DEMO_CNO << "����ѧ���ĵ�4����ҵ��������Ϣ" << endl;
	cout << "       " << procname << " --action firstline --cno " << DEMO_CNO << " --stu all --file all --week 6    : ���" << DEMO_CNO << "����ѧ���ĵ�6����ҵ��������Ϣ" << endl;
	cout << "       " << procname << " --action firstline --cno " << DEMO_CNO << " --stu " << DEMO_STUNO << " --file all         : ���" << DEMO_CNO << "��" << DEMO_STUNO << "ѧ����������ҵ��������Ϣ" << endl;
	cout << "       " << procname << " --action firstline --cno " << DEMO_CNO << " --stu " << DEMO_STUNO << " --file " << DEMO_SRC_FNAME << "   : ���" << DEMO_CNO << "��" << DEMO_STUNO << "ѧ����" << DEMO_SRC_FNAME << "��ҵ��������Ϣ" << endl;
	cout << endl;

	cout << "       " << procname << " --action secondline --cno " << DEMO_CNO << " --stu all --file " << DEMO_SRC_FNAME << " : ���" << DEMO_CNO << "������ѧ����" << DEMO_SRC_FNAME << "��ҵ�Ĵ�����Ϣ" << endl;
	cout << endl;

	cout << "       " << procname << " --cfgfile E:\\test\\my.conf --action base --cno " << DEMO_CNO << " --stu all --file all : ���" << DEMO_CNO << "����ѧ����������ҵ�Ļ�����Ϣ(ָ�������ļ�)" << endl;
	cout << endl;


	cout << endl;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
 ***************************************************************************/
static int readconfig(const string& cfgfile_name, string& dbserver, string& dbuser, string& dbpasswd, string& dbname, string& src_rootdir)
{
	cfgfile_read_tools cfg(cfgfile_name);
	if (cfg.is_open() == 0) {
		cout << "�����ļ� [" << cfgfile_name << "] �޷���." << endl;
		return -1;
	}

	if (cfg.item_get_value("[���ݿ�]", "db_host", "Hello", dbserver) < 0) {
		cout << "ȡ�����ļ� [" << cfgfile_name << "] ��" << "[���ݿ�]" << "���[" << "db_host" << "]���ֵ����." << endl;
		return -1;
	}

	if (cfg.item_get_value("[���ݿ�]", "db_username", "Hello", dbuser) < 0) {
		cout << "ȡ�����ļ� [" << cfgfile_name << "] ��" << "[���ݿ�]" << "���[" << "db_username" << "]���ֵ����." << endl;
		return -1;
	}

	if (cfg.item_get_value("[���ݿ�]", "db_passwd", "Hello", dbpasswd) < 0) {
		cout << "ȡ�����ļ� [" << cfgfile_name << "] ��" << "[���ݿ�]" << "���[" << "db_passwd" << "]���ֵ����." << endl;
		return -1;
	}

	if (cfg.item_get_value("[���ݿ�]", "db_name", "Hello", dbname) < 0) {
		cout << "ȡ�����ļ� [" << cfgfile_name << "] ��" << "[���ݿ�]" << "���[" << "db_name" << "]���ֵ����." << endl;
		return -1;
	}

	if (cfg.item_get_value("[�ļ�Ŀ¼]", "src_rootdir", "Hello", src_rootdir) < 0) {
		cout << "ȡ�����ļ� [" << cfgfile_name << "] ��" << "[�ļ�Ŀ¼]" << "���[" << "src_rootdir" << "]���ֵ����." << endl;
		return -1;
	}

	return 0;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
 ***************************************************************************/
static int check_args(args_analyse_tools* args, const char* prompt)
{
	// �жϼ�����
	if ((args[HW_ARGS_WEEK].existed() || args[HW_ARGS_CHAPTER].existed()) && args[HW_ARGS_FILE].get_string() != "all") {
		usage(prompt);
		cout << "����[--chapter/--week]���ܳ�����[--file �����ļ���]ʱ." << endl;
		return -1;
	}
	// �ж�display�Ƿ���ȷ
	if (args[HW_ARGS_DISPLAY].get_string().size() != 5) {
		usage(prompt);
		cout << "����[--display]�ĳ��Ȳ���ȷ��ֻ����[5]λ��0/1." << endl;
		return -1;
	}
	// �ж�ѧ���Ƿ���7λ ����ȫ��ѧ��
	if (!(args[HW_ARGS_STU].get_string().size() == 7 || args[HW_ARGS_STU].get_string() == "all")) {
		cout << "�ļ�[" << args[HW_ARGS_STU].get_string() << "]�޷���." << endl;
		cout << endl;
		if (args[HW_ARGS_DISPLAY].get_string().c_str()[4] == '1')
			cout << "[--���ش���--] ��ȡ [--stu] ָ�����ļ�����." << endl;
		return -1;
	}
	if (args[HW_ARGS_ACTION].get_string() != "base") {
		// �ж��Ƿ���Դ�ļ�

		bool is_source = false;
		for (int i = 0; suffix[i] != ""; i++) {
			unsigned int len = args[HW_ARGS_FILE].get_string().length();
			if (len >= strlen(suffix[i]) && strcmp(&args[HW_ARGS_FILE].get_string().c_str()[len - strlen(suffix[i])], suffix[i]) == 0) {
				is_source = true;
				break;
			}
		}
		if (is_source != true) {
			cout << "���м����ļ�[" << args[HW_ARGS_FILE].get_string() << "]������Դ�����ļ�." << endl;
			return -1;
		}
	}
	if (args[HW_ARGS_ACTION].get_string() == "secondline") {
		// �ж��Ƿ��ļ�
		if (args[HW_ARGS_FILE].get_string() == "all") {
			cout << "HW_Check_SecondLine ֻ����Ե��ļ�" << endl;
			return -1;
		}
		// �ж�stu�Ƿ���all
		if (args[HW_ARGS_STU].get_string() != "all") {
			cout << "HW_Check_SecondLine ֻ�����ȫ��ѧ��" << endl;
			return -1;
		}
	}
	// �жϿκ��ǲ���8/13
	if (args[HW_ARGS_CNO].get_string().size() != 8 && args[HW_ARGS_CNO].get_string().size() != 13) {
		cout << "�κŲ���8/13λ" << endl;
		return -1;
	}

	return 0;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
 ***************************************************************************/
static int base(args_analyse_tools* args, MYSQL* mysql, MYSQL_RES* result, MYSQL_ROW& row, string& src_rootdir)
{
	unsigned long long stu_num; // ѧ������
	unsigned long long file_num; // �ļ�����
	string stu; // ������ѧ�ŵ��ַ���
	vector<string> hw; // ����ļ������ַ���
	unsigned int hw_maxlen = 0; // �ļ�����󳤶�
	const char* ret = NULL;

	bool found = false; // �Ƿ��ύ
	bool pdf_right = true; // pdf��ʽ��ȷ
	bool cno_right = false; // �κ���ȷ
	bool is_source_code = false; // �Ƿ�ΪԴ����
	bool is_utf8 = false; // �Ƿ���UTF8����

	int nosubmit = 0; // δ�ύ������
	int right = 0; // ��ȷ������
	int wrongpdf = 0; // pdf��ʽ���������
	int notgb = 0; // ������������

	int total_pass = 0; // ͨ������
	int total_nosubmit = 0; // δ�ύ������
	int total_wrongpdf = 0; // pdf��ʽ���������
	int total_notgb = 0; // ������������

	string search_cno = "select * from view_hwcheck_hwlist where hw_cno = \"" + args[HW_ARGS_CNO].get_string() + "\"";
	string search_stu = "select * from view_hwcheck_stulist where stu_cno = \"" + args[HW_ARGS_CNO].get_string() + "\"";
	string search_hw;
	if (args[HW_ARGS_CHAPTER].existed() == 1 && args[HW_ARGS_CHAPTER].get_int() != -1)
		if (args[HW_ARGS_WEEK].existed() == 1 && args[HW_ARGS_WEEK].get_int() != -1) {
			stringstream a, b;
			a << args[HW_ARGS_WEEK].get_int();
			b << args[HW_ARGS_CHAPTER].get_int();
			string week;
			a >> week;
			string chap;
			b >> chap;
			search_hw = "select * from view_hwcheck_hwlist where hw_cno = \"" + args[HW_ARGS_CNO].get_string() + "\" and hw_chapter = \"" + chap + "\" and hw_week = \"" + week + "\"";
		}
		else {
			stringstream a;
			a << args[HW_ARGS_CHAPTER].get_int();
			string chap;
			a >> chap;
			search_hw = "select * from view_hwcheck_hwlist where hw_cno = \"" + args[HW_ARGS_CNO].get_string() + "\" and hw_chapter = \"" + chap + "\"";
		}
	else
		if (args[HW_ARGS_WEEK].existed() == 1 && args[HW_ARGS_WEEK].get_int() != -1) {
			stringstream a;
			a << args[HW_ARGS_WEEK].get_int();
			string week;
			a >> week;
			search_hw = "select * from view_hwcheck_hwlist where hw_cno = \"" + args[HW_ARGS_CNO].get_string() + "\" and hw_week = \"" + week + "\"";
		}
		else
			search_hw = "select * from view_hwcheck_hwlist where hw_cno = \"" + args[HW_ARGS_CNO].get_string() + "\"";


	// ��ѯ�Ƿ��иÿκ�
	{
		if (mysql_query(mysql, search_cno.c_str())) {
			cout << "mysql_query failed(" << mysql_error(mysql) << ")" << endl;
			return -1;
		}

		/* ����ѯ����洢���������ִ����򷵻�NULL */
		if ((result = mysql_store_result(mysql)) == NULL) {
			cout << "mysql_store_result failed" << endl;
			return -1;
		}

		while ((row = mysql_fetch_row(result)) != NULL)
			if (args[HW_ARGS_CNO].get_string() == row[1]) {
				cno_right = true;
				break;
			}

		if (cno_right == false) {
			cout << "mysql execute [call proc_hwcheck_get_stulist(\"2023/2024/1\", \"" << args[HW_ARGS_CNO].get_string() << "\"); ] ��ѯ������Ҫ��ļ�¼Ϊ[0]." << endl;
			return -1;
		}
	}

	// ��ѯ�ÿκŶ�Ӧ��ѧ��
	{
		if (mysql_query(mysql, search_stu.c_str())) {
			cout << "mysql_query failed(" << mysql_error(mysql) << ")" << endl;
			return -1;
		}

		/* ����ѯ����洢���������ִ����򷵻�NULL
			ע�⣺��ѯ���ΪNULL�����᷵��NULL */
		if ((result = mysql_store_result(mysql)) == NULL) {
			cout << "mysql_store_result failed" << endl;
			return -1;
		}
	}

	if (args[HW_ARGS_FILE].get_string() != "all") {
		if (args[HW_ARGS_STU].get_string() != "all") {
			while ((row = mysql_fetch_row(result)) != NULL) {
				ret = strstr(row[2], args[HW_ARGS_STU].get_string().c_str());
				if (ret != NULL) {// �ҵ���
					stu = row[2];
					stu += "/";
					stu += row[3];
					break;
				}
			}
			if (ret == NULL)  // û�ҵ�
				stu_num = 0;
			else { // �ҵ���
				stu_num = 1;
				base_ErrorType(found, pdf_right, is_utf8, is_source_code, args[HW_ARGS_CNO].get_string(), args[HW_ARGS_STU].get_string(), args[HW_ARGS_FILE].get_string(), src_rootdir);
			}

			// ������ 
			cout << "�κ� : " << args[HW_ARGS_CNO].get_string() << ' ' << "ѧ������ : " << stu_num << ' ' << "Դ�ļ��� : " << args[HW_ARGS_FILE].get_string() << endl;
			if (stu_num != 0) {
				cout << setiosflags(ios::left);
				if (found == false && args[HW_ARGS_DISPLAY].get_string().c_str()[1] == '1')
					cout << setw(3) << stu_num << ": " << setw(16) << stu << " : ";
				else {
					if (pdf_right == false && args[HW_ARGS_DISPLAY].get_string().c_str()[2] == '1')
						cout << setw(3) << stu_num << ": " << setw(16) << stu << " : ";
					if (is_utf8 == true && args[HW_ARGS_DISPLAY].get_string().c_str()[2] == '1')
						cout << setw(3) << stu_num << ": " << setw(16) << stu << " : ";
				}
				if (found == true && pdf_right == true && is_utf8 == false && args[HW_ARGS_DISPLAY].get_string().c_str()[0] == '1')
					cout << setw(3) << stu_num << ": " << setw(16) << stu << " : ";
				base_StateType(nosubmit, right, wrongpdf, notgb, found, pdf_right, is_utf8,
					args[HW_ARGS_DISPLAY].get_string().c_str()[0], args[HW_ARGS_DISPLAY].get_string().c_str()[1], args[HW_ARGS_DISPLAY].get_string().c_str()[2]);
			}
		}
		else {
			stu_num = mysql_num_rows(result);
			cout << "�κ� : " << args[HW_ARGS_CNO].get_string() << ' ' << "ѧ������ : " << stu_num << ' ' << "Դ�ļ��� : " << args[HW_ARGS_FILE].get_string() << endl;

			int i = 1;
			while ((row = mysql_fetch_row(result)) != NULL) {
				stu.clear();
				stu = row[2];
				stu += "/";
				stu += row[3];
				cout << setiosflags(ios::left);

				base_ErrorType(found, pdf_right, is_utf8, is_source_code, args[HW_ARGS_CNO].get_string(), row[2], args[HW_ARGS_FILE].get_string(), src_rootdir);

				if (found == false && args[HW_ARGS_DISPLAY].get_string().c_str()[1] == '1')
					cout << setw(3) << i << ": " << setw(16) << stu << " : ";
				else {
					if (pdf_right == false && args[HW_ARGS_DISPLAY].get_string().c_str()[2] == '1')
						cout << setw(3) << i << ": " << setw(16) << stu << " : ";
					if (is_utf8 == true && args[HW_ARGS_DISPLAY].get_string().c_str()[2] == '1')
						cout << setw(3) << i << ": " << setw(16) << stu << " : ";
				}
				if (found == true && pdf_right == true && is_utf8 == false && args[HW_ARGS_DISPLAY].get_string().c_str()[0] == '1')
					cout << setw(3) << i << ": " << setw(16) << stu << " : ";
				base_StateType(nosubmit, right, wrongpdf, notgb, found, pdf_right, is_utf8,
					args[HW_ARGS_DISPLAY].get_string().c_str()[0], args[HW_ARGS_DISPLAY].get_string().c_str()[1], args[HW_ARGS_DISPLAY].get_string().c_str()[2]);

				i++;
			}
		}
		cout << endl;
		base_detail_info(nosubmit, right, wrongpdf, notgb, stu_num);
	}
	else {
		MYSQL_RES* result_hw;

		// ���Ҹÿκŵ�������ҵ
		{
			if (mysql_query(mysql, search_hw.c_str())) {
				cout << "mysql_query failed(" << mysql_error(mysql) << ")" << endl;
				return -1;
			}

			/* ����ѯ����洢���������ִ����򷵻�NULL
				ע�⣺��ѯ���ΪNULL�����᷵��NULL */
			if ((result_hw = mysql_store_result(mysql)) == NULL) {
				cout << "mysql_store_result failed" << endl;
				return -1;
			}
		}

		file_num = mysql_num_rows(result_hw);
		if (file_num == 0) {
			cout << "���β�����ѧ������Ϊ0/�ļ�����Ϊ0��δִ��" << endl;
			return -1;
		}

		while ((row = mysql_fetch_row(result_hw)) != NULL) {
			hw.push_back(row[5]); // �������ļ�����vector �Ա������󳤶�
			if (strlen(row[5]) > hw_maxlen)
				hw_maxlen = strlen(row[5]);
		}

		if (args[HW_ARGS_STU].get_string() != "all") {
			while ((row = mysql_fetch_row(result)) != NULL) {
				ret = strstr(row[2], args[HW_ARGS_STU].get_string().c_str());
				if (ret != NULL) {// �ҵ���
					stu = row[3];
					break;
				}
			}
			if (ret == NULL) { // û�ҵ�
				cout << "���β�����ѧ������Ϊ0/�ļ�����Ϊ0��δִ��" << endl;
				return -1;
			}
			else { // �ҵ���
				stu_num = 1;

				cout << "1  : ѧ��-" << args[HW_ARGS_STU].get_string() << ' ' << "����-" << stu << ' ' << "�κ�-" << args[HW_ARGS_CNO].get_string() << ' ' << "�ļ�����-" << file_num << endl;

				for (unsigned int i = 0; i < hw.size(); i++) {
					cout << setiosflags(ios::left);
					base_ErrorType(found, pdf_right, is_utf8, is_source_code, args[HW_ARGS_CNO].get_string(), args[HW_ARGS_STU].get_string(), hw[i], src_rootdir);

					if (found == false && args[HW_ARGS_DISPLAY].get_string().c_str()[1] == '1')
						cout << "  " << setw(hw_maxlen) << hw[i] << " : ";
					else {
						if (pdf_right == false && args[HW_ARGS_DISPLAY].get_string().c_str()[2] == '1')
							cout << "  " << setw(hw_maxlen) << hw[i] << " : ";
						if (is_utf8 == true && args[HW_ARGS_DISPLAY].get_string().c_str()[2] == '1')
							cout << "  " << setw(hw_maxlen) << hw[i] << " : ";
					}
					if (found == true && pdf_right == true && is_utf8 == false && args[HW_ARGS_DISPLAY].get_string().c_str()[0] == '1')
						cout << "  " << setw(hw_maxlen) << hw[i] << " : ";
					base_StateType(nosubmit, right, wrongpdf, notgb, found, pdf_right, is_utf8,
						args[HW_ARGS_DISPLAY].get_string().c_str()[0], args[HW_ARGS_DISPLAY].get_string().c_str()[1], args[HW_ARGS_DISPLAY].get_string().c_str()[2]);

				}
				cout << resetiosflags(ios::left);
				base_stu_detail_info(nosubmit, right, wrongpdf, notgb, file_num);

				if (args[HW_ARGS_DISPLAY].get_string().c_str()[3] == '1') {
					cout << endl;
					base_all_detail_info(nosubmit, right, wrongpdf, notgb, stu_num, file_num);
				}
			}
		}
		else {
			stu_num = mysql_num_rows(result);

			int i = 1;
			while ((row = mysql_fetch_row(result)) != NULL) {
				stu = row[3];
				cout << setiosflags(ios::left);
				cout << setw(3) << i << ": ѧ��-" << row[2] << ' ' << "����-" << stu << ' ' << "�κ�-" << args[HW_ARGS_CNO].get_string() << ' ' << "�ļ�����-" << file_num << endl;
				i++;

				for (unsigned int j = 0; j < hw.size(); j++) {
					cout << setiosflags(ios::left);
					base_ErrorType(found, pdf_right, is_utf8, is_source_code, args[HW_ARGS_CNO].get_string(), row[2], hw[j], src_rootdir);

					if (found == false && args[HW_ARGS_DISPLAY].get_string().c_str()[1] == '1')
						cout << "  " << setw(hw_maxlen) << hw[j] << " : ";
					else {
						if (pdf_right == false && args[HW_ARGS_DISPLAY].get_string().c_str()[2] == '1')
							cout << "  " << setw(hw_maxlen) << hw[j] << " : ";
						if (is_utf8 == true && args[HW_ARGS_DISPLAY].get_string().c_str()[2] == '1')
							cout << "  " << setw(hw_maxlen) << hw[j] << " : ";
					}
					if (found == true && pdf_right == true && is_utf8 == false && args[HW_ARGS_DISPLAY].get_string().c_str()[0] == '1')
						cout << "  " << setw(hw_maxlen) << hw[j] << " : ";
					base_StateType(nosubmit, right, wrongpdf, notgb, found, pdf_right, is_utf8,
						args[HW_ARGS_DISPLAY].get_string().c_str()[0], args[HW_ARGS_DISPLAY].get_string().c_str()[1], args[HW_ARGS_DISPLAY].get_string().c_str()[2]);

				}
				cout << resetiosflags(ios::left);
				base_stu_detail_info(nosubmit, right, wrongpdf, notgb, file_num);
				total_pass += right;
				total_nosubmit += nosubmit;
				total_wrongpdf += wrongpdf;
				total_notgb += notgb;

				nosubmit = 0;
				right = 0;
				wrongpdf = 0;
				notgb = 0;
			}
			if (args[HW_ARGS_DISPLAY].get_string().c_str()[3] == '1') {
				cout << endl;
				base_all_detail_info(total_nosubmit, total_pass, total_wrongpdf, total_notgb, stu_num, file_num);
			}
		}
	}

	/* �ͷ�result������ᶪʧ�ڴ� */
	mysql_free_result(result);
	return 0;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
 ***************************************************************************/
static int firstline(args_analyse_tools* args, MYSQL* mysql, MYSQL_RES* result, MYSQL_ROW& row, string& src_rootdir)
{
	const char* ret = NULL;
	unsigned long long stu_num; // ѧ������
	unsigned long long file_num; // �ļ�����
	unsigned int hw_maxlen = 0; // �ļ�����󳤶�
	vector<string> hw; // ����ļ������ַ���
	string num; // ��ѧ�ŵ��ַ���
	string name; // ���������ַ���
	string major_s; // ��רҵ��Ƶ��ַ���
	string major; // ��רҵȫ�Ƶ��ַ���

	bool found = true; // �Ƿ��ύ
	bool cno_right = false; // �κ���ȷ
	bool is_anno = true; // �Ƿ���ע��
	bool three = true; // �Ƿ�������
	bool error = false; // �Ƿ����
	bool is_utf8 = false; // �Ƿ���UTF8����
	bool num_wrong = false; // ѧ���Ƿ�ƥ��
	bool name_wrong = false; // �����Ƿ�ƥ��
	bool major_wrong = false; // �༶�Ƿ�ƥ��
	bool is_source = true; // �Ƿ���Դ����
	bool wrong_anno_form = false; // ע�ͱ����ʽ�Ƿ����

	int nosubmit = 0; // δ�ύ������
	int right = 0; // ��ȷ������
	int noanno = 0; // ��ע�ͼ�����
	int notgb = 0; // ������������
	int notthree = 0; // �������������
	int nomatch = 0; // ע�Ͳ�ƥ�������
	int wrongform = 0; // ע�ͱ����ʽ���������

	int total_pass = 0; // ͨ������
	int total_nosubmit = 0; // δ�ύ������
	int total_noanno = 0; // ��ע�ͼ�����
	int total_notgb = 0; // ������������
	int total_notthree = 0; // �����������
	int total_nomatch = 0; // ��ƥ�������
	int total_wrongform = 0; // ע�ͱ����ʽ���������

	string search_cno = "select * from view_hwcheck_hwlist where hw_cno = \"" + args[HW_ARGS_CNO].get_string() + "\"";
	string search_stu = "select * from view_hwcheck_stulist where stu_cno = \"" + args[HW_ARGS_CNO].get_string() + "\"";
	string search_hw;
	if (args[HW_ARGS_CHAPTER].existed() == 1 && args[HW_ARGS_CHAPTER].get_int() != -1)
		if (args[HW_ARGS_WEEK].existed() == 1 && args[HW_ARGS_WEEK].get_int() != -1) {
			stringstream a, b;
			a << args[HW_ARGS_WEEK].get_int();
			b << args[HW_ARGS_CHAPTER].get_int();
			string week;
			a >> week;
			string chap;
			b >> chap;
			search_hw = "select * from view_hwcheck_hwlist where hw_cno = \"" + args[HW_ARGS_CNO].get_string() + "\" and hw_chapter = \"" + chap + "\" and hw_week = \"" + week + "\"";
		}
		else {
			stringstream a;
			a << args[HW_ARGS_CHAPTER].get_int();
			string chap;
			a >> chap;
			search_hw = "select * from view_hwcheck_hwlist where hw_cno = \"" + args[HW_ARGS_CNO].get_string() + "\" and hw_chapter = \"" + chap + "\"";
		}
	else
		if (args[HW_ARGS_WEEK].existed() == 1 && args[HW_ARGS_WEEK].get_int() != -1) {
			stringstream a;
			a << args[HW_ARGS_WEEK].get_int();
			string week;
			a >> week;
			search_hw = "select * from view_hwcheck_hwlist where hw_cno = \"" + args[HW_ARGS_CNO].get_string() + "\" and hw_week = \"" + week + "\"";
		}
		else
			search_hw = "select * from view_hwcheck_hwlist where hw_cno = \"" + args[HW_ARGS_CNO].get_string() + "\"";

	// ��ѯ�Ƿ��иÿκ�
	{
		if (mysql_query(mysql, search_cno.c_str())) {
			cout << "mysql_query failed(" << mysql_error(mysql) << ")" << endl;
			return -1;
		}

		/* ����ѯ����洢���������ִ����򷵻�NULL */
		if ((result = mysql_store_result(mysql)) == NULL) {
			cout << "mysql_store_result failed" << endl;
			return -1;
		}

		while ((row = mysql_fetch_row(result)) != NULL)
			if (args[HW_ARGS_CNO].get_string() == row[1]) {
				cno_right = true;
				break;
			}

		if (cno_right == false) {
			cout << "mysql execute [call proc_hwcheck_get_stulist(\"2023/2024/1\", \"" << args[HW_ARGS_CNO].get_string() << "\"); ] ��ѯ������Ҫ��ļ�¼Ϊ[0]." << endl;
			return -1;
		}
	}

	// ��ѯ�ÿκŶ�Ӧ��ѧ��
	{
		if (mysql_query(mysql, search_stu.c_str())) {
			cout << "mysql_query failed(" << mysql_error(mysql) << ")" << endl;
			return -1;
		}

		/* ����ѯ����洢���������ִ����򷵻�NULL
			ע�⣺��ѯ���ΪNULL�����᷵��NULL */
		if ((result = mysql_store_result(mysql)) == NULL) {
			cout << "mysql_store_result failed" << endl;
			return -1;
		}
	}

	if (args[HW_ARGS_FILE].get_string() != "all") {
		if (args[HW_ARGS_STU].get_string() != "all") {
			while ((row = mysql_fetch_row(result)) != NULL) {
				ret = strstr(row[2], args[HW_ARGS_STU].get_string().c_str());
				if (ret != NULL) {// �ҵ���
					name = row[3];
					num = row[2];
					major_s = row[6];
					major = row[5];
					break;
				}
			}
			if (ret == NULL)  // û�ҵ�
				stu_num = 0;
			else { // �ҵ���
				stu_num = 1;
				firstline_ErrorType(found, is_utf8, is_anno, three, error, num_wrong, name_wrong, major_wrong, wrong_anno_form,
					args[HW_ARGS_CNO].get_string(), num, args[HW_ARGS_FILE].get_string(), name, major_s, major, src_rootdir);
			}

			// ������ 
			cout << "�κ� : " << args[HW_ARGS_CNO].get_string() << ' ' << "ѧ������ : " << stu_num << ' ' << "Դ�ļ��� : " << args[HW_ARGS_FILE].get_string() << endl;
			if (stu_num != 0) {
				cout << setiosflags(ios::left);

				for (int k = 0; k < 1; k++) {
					if (found == false) {
						if (args[HW_ARGS_DISPLAY].get_string().c_str()[1] == '1')
							cout << setw(3) << stu_num << ": " << setw(16) << num + "/" + name << " : ";
						break;
					}
					else if (is_utf8 == true && args[HW_ARGS_DISPLAY].get_string().c_str()[2] == '1')
						cout << setw(3) << stu_num << ": " << setw(16) << num + "/" + name << " : ";
					else {
						if (wrong_anno_form == true && args[HW_ARGS_DISPLAY].get_string().c_str()[2] == '1')
							cout << setw(3) << stu_num << ": " << setw(16) << num + "/" + name << " : ";
						else if (is_anno == false && args[HW_ARGS_DISPLAY].get_string().c_str()[2] == '1')
							cout << setw(3) << stu_num << ": " << setw(16) << num + "/" + name << " : ";
						else if (three == false && args[HW_ARGS_DISPLAY].get_string().c_str()[2] == '1')
							cout << setw(3) << stu_num << ": " << setw(16) << num + "/" + name << " : ";
						else if (error == true && args[HW_ARGS_DISPLAY].get_string().c_str()[2] == '1')
							cout << setw(3) << stu_num << ": " << setw(16) << num + "/" + name << " : ";
					}
					if (found == true && is_anno == true && is_utf8 == false && three == true && error == false && wrong_anno_form == false && args[HW_ARGS_DISPLAY].get_string().c_str()[0] == '1')
						cout << setw(3) << stu_num << ": " << setw(16) << num + "/" + name << " : ";
				}

				firstline_StateType(nosubmit, right, noanno, notgb, notthree, nomatch, wrongform, found, is_utf8, is_anno, three, error, num_wrong, name_wrong, major_wrong, wrong_anno_form,
					args[HW_ARGS_DISPLAY].get_string().c_str()[0], args[HW_ARGS_DISPLAY].get_string().c_str()[1], args[HW_ARGS_DISPLAY].get_string().c_str()[2],
					args[HW_ARGS_CNO].get_string(), num, args[HW_ARGS_FILE].get_string(), src_rootdir);
			}
		}
		else {
			stu_num = mysql_num_rows(result);
			cout << "�κ� : " << args[HW_ARGS_CNO].get_string() << ' ' << "ѧ������ : " << stu_num << ' ' << "Դ�ļ��� : " << args[HW_ARGS_FILE].get_string() << endl;

			int i = 1;
			while ((row = mysql_fetch_row(result)) != NULL) {
				name = row[3];
				num = row[2];
				major_s = row[6];
				major = row[5];

				cout << setiosflags(ios::left);
				firstline_ErrorType(found, is_utf8, is_anno, three, error, num_wrong, name_wrong, major_wrong, wrong_anno_form,
					args[HW_ARGS_CNO].get_string(), num, args[HW_ARGS_FILE].get_string(), name, major_s, major, src_rootdir);

				for (int k = 0; k < 1; k++) {
					if (found == false) {
						if (args[HW_ARGS_DISPLAY].get_string().c_str()[1] == '1')
							cout << setw(3) << i << ": " << setw(16) << num + "/" + name << " : ";
						break;
					}
					else if (is_utf8 == true && args[HW_ARGS_DISPLAY].get_string().c_str()[2] == '1')
						cout << setw(3) << i << ": " << setw(16) << num + "/" + name << " : ";
					else {
						if (wrong_anno_form == true && args[HW_ARGS_DISPLAY].get_string().c_str()[2] == '1')
							cout << setw(3) << i << ": " << setw(16) << num + "/" + name << " : ";
						else if (is_anno == false && args[HW_ARGS_DISPLAY].get_string().c_str()[2] == '1')
							cout << setw(3) << i << ": " << setw(16) << num + "/" + name << " : ";
						else if (three == false && args[HW_ARGS_DISPLAY].get_string().c_str()[2] == '1')
							cout << setw(3) << i << ": " << setw(16) << num + "/" + name << " : ";
						else if (error == true && args[HW_ARGS_DISPLAY].get_string().c_str()[2] == '1')
							cout << setw(3) << i << ": " << setw(16) << num + "/" + name << " : ";
					}
					if (found == true && is_anno == true && is_utf8 == false && three == true && error == false && wrong_anno_form == false && args[HW_ARGS_DISPLAY].get_string().c_str()[0] == '1')
						cout << setw(3) << i << ": " << setw(16) << num + "/" + name << " : ";
				}


				firstline_StateType(nosubmit, right, noanno, notgb, notthree, nomatch, wrongform, found, is_utf8, is_anno, three, error, num_wrong, name_wrong, major_wrong, wrong_anno_form,
					args[HW_ARGS_DISPLAY].get_string().c_str()[0], args[HW_ARGS_DISPLAY].get_string().c_str()[1], args[HW_ARGS_DISPLAY].get_string().c_str()[2],
					args[HW_ARGS_CNO].get_string(), num, args[HW_ARGS_FILE].get_string(), src_rootdir);

				i++;
			}
		}
		cout << endl;
		firstline_detail_info(nosubmit, right, notgb, noanno, notthree, nomatch, wrongform, stu_num);
	}
	else {
		MYSQL_RES* result_hw;

		// ���Ҹÿκŵ�������ҵ
		{
			if (mysql_query(mysql, search_hw.c_str())) {
				cout << "mysql_query failed(" << mysql_error(mysql) << ")" << endl;
				return -1;
			}

			/* ����ѯ����洢���������ִ����򷵻�NULL
				ע�⣺��ѯ���ΪNULL�����᷵��NULL */
			if ((result_hw = mysql_store_result(mysql)) == NULL) {
				cout << "mysql_store_result failed" << endl;
				return -1;
			}
		}

		while ((row = mysql_fetch_row(result_hw)) != NULL) {
			is_source = source(row[5]);
			if (is_source == true)
				hw.push_back(row[5]); // �������ļ�����vector �Ա������󳤶�
			if (is_source == true && strlen(row[5]) > hw_maxlen)
				hw_maxlen = strlen(row[5]);
		}

		file_num = hw.size();
		if (file_num == 0) {
			cout << "���β�����ѧ������Ϊ0/�ļ�����Ϊ0��δִ��" << endl;
			return -1;
		}

		if (args[HW_ARGS_STU].get_string() != "all") {
			while ((row = mysql_fetch_row(result)) != NULL) {
				ret = strstr(row[2], args[HW_ARGS_STU].get_string().c_str());
				if (ret != NULL) {// �ҵ���
					name = row[3];
					num = row[2];
					major_s = row[6];
					major = row[5];
					break;
				}
			}
			if (ret == NULL) { // û�ҵ�
				cout << "���β�����ѧ������Ϊ0/�ļ�����Ϊ0��δִ��" << endl;
				return -1;
			}
			else { // �ҵ���
				stu_num = 1;

				cout << "1  : ѧ��-" << args[HW_ARGS_STU].get_string() << ' ' << "����-" << name << ' ' << "�κ�-" << args[HW_ARGS_CNO].get_string() << ' ' << "�ļ�����-" << file_num << endl;

				for (unsigned int i = 0; i < hw.size(); i++) {
					cout << setiosflags(ios::left);
					firstline_ErrorType(found, is_utf8, is_anno, three, error, num_wrong, name_wrong, major_wrong, wrong_anno_form,
						args[HW_ARGS_CNO].get_string(), num, hw[i], name, major_s, major, src_rootdir);

					for (int k = 0; k < 1; k++) {
						if (found == false) {
							if (args[HW_ARGS_DISPLAY].get_string().c_str()[1] == '1')
								cout << "  " << setw(hw_maxlen) << hw[i] << " : ";
							break;
						}
						else if (is_utf8 == true && args[HW_ARGS_DISPLAY].get_string().c_str()[2] == '1')
							cout << "  " << setw(hw_maxlen) << hw[i] << " : ";
						else {
							if (wrong_anno_form == true && args[HW_ARGS_DISPLAY].get_string().c_str()[2] == '1')
								cout << "  " << setw(hw_maxlen) << hw[i] << " : ";
							else if (is_anno == false && args[HW_ARGS_DISPLAY].get_string().c_str()[2] == '1')
								cout << "  " << setw(hw_maxlen) << hw[i] << " : ";
							else if (three == false && args[HW_ARGS_DISPLAY].get_string().c_str()[2] == '1')
								cout << "  " << setw(hw_maxlen) << hw[i] << " : ";
							else if (error == true && args[HW_ARGS_DISPLAY].get_string().c_str()[2] == '1')
								cout << "  " << setw(hw_maxlen) << hw[i] << " : ";
						}
						if (found == true && is_anno == true && is_utf8 == false && three == true && error == false && wrong_anno_form == false && args[HW_ARGS_DISPLAY].get_string().c_str()[0] == '1')
							cout << "  " << setw(hw_maxlen) << hw[i] << " : ";
					}

					firstline_StateType(nosubmit, right, noanno, notgb, notthree, nomatch, wrongform, found, is_utf8, is_anno, three, error, num_wrong, name_wrong, major_wrong, wrong_anno_form,
						args[HW_ARGS_DISPLAY].get_string().c_str()[0], args[HW_ARGS_DISPLAY].get_string().c_str()[1], args[HW_ARGS_DISPLAY].get_string().c_str()[2],
						args[HW_ARGS_CNO].get_string(), num, hw[i], src_rootdir);

				}
				cout << resetiosflags(ios::left);
				firstline_stu_detail_info(nosubmit, right, notgb, noanno, notthree, nomatch, wrongform, file_num);
				if (args[HW_ARGS_DISPLAY].get_string().c_str()[3] == '1') {
					cout << endl;
					firstline_all_detail_info(nosubmit, right, notgb, noanno, notthree, nomatch, wrongform, file_num, stu_num);
				}
			}
		}
		else {
			stu_num = mysql_num_rows(result);

			int i = 1;
			while ((row = mysql_fetch_row(result)) != NULL) {
				name = row[3];
				num = row[2];
				major_s = row[6];
				major = row[5];
				cout << setiosflags(ios::left);
				cout << setw(3) << i << ": ѧ��-" << row[2] << ' ' << "����-" << name << ' ' << "�κ�-" << args[HW_ARGS_CNO].get_string() << ' ' << "�ļ�����-" << file_num << endl;
				i++;

				for (unsigned int j = 0; j < hw.size(); j++) {
					cout << setiosflags(ios::left);
					firstline_ErrorType(found, is_utf8, is_anno, three, error, num_wrong, name_wrong, major_wrong, wrong_anno_form,
						args[HW_ARGS_CNO].get_string(), num, hw[j], name, major_s, major, src_rootdir);

					for (int k = 0; k < 1; k++) {
						if (found == false) {
							if (args[HW_ARGS_DISPLAY].get_string().c_str()[1] == '1')
								cout << "  " << setw(hw_maxlen) << hw[j] << " : ";
							break;
						}
						else if (is_utf8 == true && args[HW_ARGS_DISPLAY].get_string().c_str()[2] == '1')
							cout << "  " << setw(hw_maxlen) << hw[j] << " : ";
						else {
							if (wrong_anno_form == true && args[HW_ARGS_DISPLAY].get_string().c_str()[2] == '1')
								cout << "  " << setw(hw_maxlen) << hw[j] << " : ";
							else if (is_anno == false && args[HW_ARGS_DISPLAY].get_string().c_str()[2] == '1')
								cout << "  " << setw(hw_maxlen) << hw[j] << " : ";
							else if (three == false && args[HW_ARGS_DISPLAY].get_string().c_str()[2] == '1')
								cout << "  " << setw(hw_maxlen) << hw[j] << " : ";
							else if (error == true && args[HW_ARGS_DISPLAY].get_string().c_str()[2] == '1')
								cout << "  " << setw(hw_maxlen) << hw[j] << " : ";
						}
						if (found == true && is_anno == true && is_utf8 == false && three == true && error == false && wrong_anno_form == false && args[HW_ARGS_DISPLAY].get_string().c_str()[0] == '1')
							cout << "  " << setw(hw_maxlen) << hw[j] << " : ";
					}

					firstline_StateType(nosubmit, right, noanno, notgb, notthree, nomatch, wrongform, found, is_utf8, is_anno, three, error, num_wrong, name_wrong, major_wrong, wrong_anno_form,
						args[HW_ARGS_DISPLAY].get_string().c_str()[0], args[HW_ARGS_DISPLAY].get_string().c_str()[1], args[HW_ARGS_DISPLAY].get_string().c_str()[2],
						args[HW_ARGS_CNO].get_string(), num, hw[j], src_rootdir);

				}
				cout << resetiosflags(ios::left);
				firstline_stu_detail_info(nosubmit, right, notgb, noanno, notthree, nomatch, wrongform, file_num);
				cout << endl;
				total_pass += right;
				total_nosubmit += nosubmit;
				total_noanno += noanno;
				total_notthree += notthree;
				total_nomatch += nomatch;
				total_notgb += notgb;
				total_wrongform += wrongform;

				nosubmit = 0;
				right = 0;
				noanno = 0;
				nomatch = 0;
				notthree = 0;
				notgb = 0;
				wrongform = 0;
			}
			if (args[HW_ARGS_DISPLAY].get_string().c_str()[3] == '1') {
				cout << endl;
				firstline_all_detail_info(total_nosubmit, total_pass, total_notgb, total_noanno, total_notthree, total_nomatch, wrongform, file_num, stu_num);
			}
		}
	}

	/* �ͷ�result������ᶪʧ�ڴ� */
	mysql_free_result(result);
	return 0;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
 ***************************************************************************/
static int secondline(args_analyse_tools* args, MYSQL* mysql, MYSQL_RES* result, MYSQL_ROW& row, string& src_rootdir)
{
	bool cno_right = false; // �κ���ȷ
	unsigned long long stu_num; // ѧ������
	string num; // ��ѧ�ŵ��ַ���
	string name; // ���������ַ���

	bool found = true; // �Ƿ��ύ
	bool is_anno = true; // �Ƿ���ע��
	bool is_utf8 = false; // �Ƿ���UTF8����
	bool num_wrong = false; // ѧ���Ƿ�ƥ��
	bool name_wrong = false; // �����Ƿ�ƥ��
	bool is_seven = true; // ѧ���Ƿ�7λ
	bool lack = false; // �Ƿ�ȱʧ��

	int nosubmit = 0; // δ�ύ������
	int right = 0; // ��ȷ������
	int noanno = 0; // ��ע�ͼ�����
	int notgb = 0; // ������������

	string search_cno = "select * from view_hwcheck_hwlist where hw_cno = \"" + args[HW_ARGS_CNO].get_string() + "\"";
	string search_stu = "select * from view_hwcheck_stulist where stu_cno = \"" + args[HW_ARGS_CNO].get_string() + "\"";
	string search_hw = "select * from view_hwcheck_hwlist where hw_cno = \"" + args[HW_ARGS_CNO].get_string() + "\"";

	// ��ѯ�Ƿ��иÿκ�
	{
		if (mysql_query(mysql, search_cno.c_str())) {
			cout << "mysql_query failed(" << mysql_error(mysql) << ")" << endl;
			return -1;
		}

		/* ����ѯ����洢���������ִ����򷵻�NULL */
		if ((result = mysql_store_result(mysql)) == NULL) {
			cout << "mysql_store_result failed" << endl;
			return -1;
		}

		while ((row = mysql_fetch_row(result)) != NULL)
			if (args[HW_ARGS_CNO].get_string() == row[1]) {
				cno_right = true;
				break;
			}

		if (cno_right == false) {
			cout << "mysql execute [call proc_hwcheck_get_stulist(\"2023/2024/1\", \"" << args[HW_ARGS_CNO].get_string() << "\"); ] ��ѯ������Ҫ��ļ�¼Ϊ[0]." << endl;
			return -1;
		}
	}

	// ��ѯ�ÿκŶ�Ӧ��ѧ��
	{
		if (mysql_query(mysql, search_stu.c_str())) {
			cout << "mysql_query failed(" << mysql_error(mysql) << ")" << endl;
			return -1;
		}

		/* ����ѯ����洢���������ִ����򷵻�NULL
			ע�⣺��ѯ���ΪNULL�����᷵��NULL */
		if ((result = mysql_store_result(mysql)) == NULL) {
			cout << "mysql_store_result failed" << endl;
			return -1;
		}
	}

	stu_num = mysql_num_rows(result);
	cout << "�κ� : " << args[HW_ARGS_CNO].get_string() << ' ' << "ѧ������ : " << stu_num << ' ' << "Դ�ļ��� : " << args[HW_ARGS_FILE].get_string() << endl;

	int i = 1;
	while ((row = mysql_fetch_row(result)) != NULL) {
		name = row[3];
		num = row[2];

		cout << setiosflags(ios::left);
		secondline_ErrorType(found, is_utf8, is_anno, nosubmit, right, noanno, notgb, i,
			args[HW_ARGS_DISPLAY].get_string().c_str()[0], args[HW_ARGS_DISPLAY].get_string().c_str()[1], args[HW_ARGS_DISPLAY].get_string().c_str()[2],
			args[HW_ARGS_CNO].get_string(), num, args[HW_ARGS_FILE].get_string(), name, src_rootdir);

		i++;
	}
	cout << endl;
	secondline_detail_info(nosubmit, right, noanno, notgb, stu_num);
	cout << endl;
	cout << "����������" << endl;

	// ��ѯ�ÿκŶ�Ӧ��ѧ��
	{
		if (mysql_query(mysql, search_stu.c_str())) {
			cout << "mysql_query failed(" << mysql_error(mysql) << ")" << endl;
			return -1;
		}

		/* ����ѯ����洢���������ִ����򷵻�NULL
			ע�⣺��ѯ���ΪNULL�����᷵��NULL */
		if ((result = mysql_store_result(mysql)) == NULL) {
			cout << "mysql_store_result failed" << endl;
			return -1;
		}
	}

	i = 1;
	while ((row = mysql_fetch_row(result)) != NULL) {
		name = row[3];
		num = row[2];

		cout << setiosflags(ios::left);
		cout << setw(3) << i << ": " << num << ' ' << name << endl;
		doublecheck(args[HW_ARGS_CNO].get_string(), num, args[HW_ARGS_FILE].get_string(), name, src_rootdir, mysql, result, row);

		i++;
	}

	/* �ͷ�result������ᶪʧ�ڴ� */
	mysql_free_result(result);
	return 0;
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
	args_analyse_tools args[] = {
		args_analyse_tools("--help",     ST_EXTARGS_TYPE::boolean,            0, false),
		args_analyse_tools("--debug",    ST_EXTARGS_TYPE::boolean,            0, false),
		args_analyse_tools("--action",   ST_EXTARGS_TYPE::str_with_set_error, 1, -1, Action_Name),	//����-1�����壬��ʾ��Ĭ�ϣ�����ָ��
		args_analyse_tools("--cno",      ST_EXTARGS_TYPE::str,                1, string("")),
		args_analyse_tools("--stu",      ST_EXTARGS_TYPE::str,                1, string("")),
		args_analyse_tools("--file",     ST_EXTARGS_TYPE::str,                1, string("")),
		args_analyse_tools("--chapter",  ST_EXTARGS_TYPE::int_with_error,     1, -1, -1, 99), //����-1��ʾ�������½�ѡ��
		args_analyse_tools("--week",     ST_EXTARGS_TYPE::int_with_error,     1, -1, -1, 20), //����-1��ʾ�������ܴ�ѡ��
		args_analyse_tools("--display",  ST_EXTARGS_TYPE::str,                1, string("11111")),
		args_analyse_tools("--cfgfile",  ST_EXTARGS_TYPE::str,                1, string("hw_check.conf")),
		args_analyse_tools()  //���һ�������ڽ���
	};
	int cur_argc;

	//����������ȷ�Է���
	{
		if ((cur_argc = args_analyse_process(argc, argv, args, 0)) < 0)
		{
			//������Ϣ�ں������Ѵ�ӡ
			return -1;
		}

		/* ��help�����⴦�� */
		if (args[HW_ARGS_HELP].existed()) {
			//ֻҪ�� --help���������������ԣ���ʾ��������
			args_analyse_print(args);
			usage(argv[0]);
			return -1; //ִ�����ֱ���˳�
		}

		// ��ѡ
		{
			if (args[HW_ARGS_ACTION].existed() == 0) {
				cout << "����[" << args[HW_ARGS_ACTION].get_name() << "]����ָ��." << endl;
				return -1;
			}

			if (args[HW_ARGS_CNO].existed() == 0) {
				cout << "����[" << args[HW_ARGS_CNO].get_name() << "]����ָ��." << endl;
				return -1;
			}

			if (args[HW_ARGS_STU].existed() == 0) {
				cout << "����[" << args[HW_ARGS_STU].get_name() << "]����ָ��." << endl;
				return -1;
			}

			if (args[HW_ARGS_FILE].existed() == 0) {
				cout << "����[" << args[HW_ARGS_FILE].get_name() << "]����ָ��." << endl;
				return -1;
			}
		}

		if (args[HW_ARGS_DEBUG].existed())
			args_analyse_print(args);
	}

	/* ����ʵ�ʵĹ��ܵ��ã������Ӧ�Ĺ��� */

	//���ݿ��ʼ������
#if 1
	string dbserver, dbuser, dbpasswd, dbname, src_rootdir;
	string cfgfile_name = args[HW_ARGS_CFGFILE].get_string();
	readconfig(cfgfile_name, dbserver, dbuser, dbpasswd, dbname, src_rootdir);

	MYSQL* mysql;
	MYSQL_RES* result = NULL;
	MYSQL_ROW  row;

	/* ��ʼ�� mysql ������ʧ�ܷ���NULL */
	if ((mysql = mysql_init(NULL)) == NULL) {
		cout << "mysql_init failed" << endl;
		return -1;
	}

	/* �������ݿ⣬ʧ�ܷ���NULL
		1��mysqldû����
		2��û��ָ�����Ƶ����ݿ���� */
	if (mysql_real_connect(mysql, dbserver.c_str(), dbuser.c_str(), dbpasswd.c_str(), dbname.c_str(), 0, NULL, 0) == NULL) {
		cout << "mysql_real_connect failed(" << mysql_error(mysql) << ")" << endl;
		return -1;
	}

	/* �����ַ���������������ַ����� */
	mysql_set_character_set(mysql, "gbk");
#endif
	//������Χ��ȷ�Է���
	{
		if (check_args(args, argv[0]) < 0)
			return -1;
	}

	//base
	if (args[HW_ARGS_ACTION].get_string() == "base")
		base(args, mysql, result, row, src_rootdir);
	if (args[HW_ARGS_ACTION].get_string() == "firstline")
		firstline(args, mysql, result, row, src_rootdir);
	if (args[HW_ARGS_ACTION].get_string() == "secondline")
		secondline(args, mysql, result, row, src_rootdir);

	return 0;
}
