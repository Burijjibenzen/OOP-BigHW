/* 2251206 冯羽芯 计科 */
#define _CRT_SECURE_NO_WARNINGS
//按需加入需要的头文件 
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>

#include "../include/class_aat.h"
#include "../include/class_crt.h"
#include "../include/file.h"
#include "../include/hw_check.h"
#include "../include_mariadb_x86/mysql/mysql.h"      // mysql特有

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
static int readconfig(const string& cfgfile_name, string& dbserver, string& dbuser, string& dbpasswd, string& dbname, string& src_rootdir)
{
	cfgfile_read_tools cfg(cfgfile_name);
	if (cfg.is_open() == 0) {
		cout << "配置文件 [" << cfgfile_name << "] 无法打开." << endl;
		return -1;
	}

	if (cfg.item_get_value("[数据库]", "db_host", "Hello", dbserver) < 0) {
		cout << "取配置文件 [" << cfgfile_name << "] 的" << "[数据库]" << "组的[" << "db_host" << "]项的值出错." << endl;
		return -1;
	}

	if (cfg.item_get_value("[数据库]", "db_username", "Hello", dbuser) < 0) {
		cout << "取配置文件 [" << cfgfile_name << "] 的" << "[数据库]" << "组的[" << "db_username" << "]项的值出错." << endl;
		return -1;
	}

	if (cfg.item_get_value("[数据库]", "db_passwd", "Hello", dbpasswd) < 0) {
		cout << "取配置文件 [" << cfgfile_name << "] 的" << "[数据库]" << "组的[" << "db_passwd" << "]项的值出错." << endl;
		return -1;
	}

	if (cfg.item_get_value("[数据库]", "db_name", "Hello", dbname) < 0) {
		cout << "取配置文件 [" << cfgfile_name << "] 的" << "[数据库]" << "组的[" << "db_name" << "]项的值出错." << endl;
		return -1;
	}

	if (cfg.item_get_value("[文件目录]", "src_rootdir", "Hello", src_rootdir) < 0) {
		cout << "取配置文件 [" << cfgfile_name << "] 的" << "[文件目录]" << "组的[" << "src_rootdir" << "]项的值出错." << endl;
		return -1;
	}

	return 0;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
 ***************************************************************************/
static int check_args(args_analyse_tools* args, const char* prompt)
{
	// 判断兼容性
	if ((args[HW_ARGS_WEEK].existed() || args[HW_ARGS_CHAPTER].existed()) && args[HW_ARGS_FILE].get_string() != "all") {
		usage(prompt);
		cout << "参数[--chapter/--week]不能出现在[--file 单个文件名]时." << endl;
		return -1;
	}
	// 判断display是否正确
	if (args[HW_ARGS_DISPLAY].get_string().size() != 5) {
		usage(prompt);
		cout << "参数[--display]的长度不正确，只能是[5]位的0/1." << endl;
		return -1;
	}
	// 判断学号是否是7位 或是全体学生
	if (!(args[HW_ARGS_STU].get_string().size() == 7 || args[HW_ARGS_STU].get_string() == "all")) {
		cout << "文件[" << args[HW_ARGS_STU].get_string() << "]无法打开." << endl;
		cout << endl;
		if (args[HW_ARGS_DISPLAY].get_string().c_str()[4] == '1')
			cout << "[--严重错误--] 读取 [--stu] 指定的文件出错." << endl;
		return -1;
	}
	if (args[HW_ARGS_ACTION].get_string() != "base") {
		// 判断是否是源文件

		bool is_source = false;
		for (int i = 0; suffix[i] != ""; i++) {
			unsigned int len = args[HW_ARGS_FILE].get_string().length();
			if (len >= strlen(suffix[i]) && strcmp(&args[HW_ARGS_FILE].get_string().c_str()[len - strlen(suffix[i])], suffix[i]) == 0) {
				is_source = true;
				break;
			}
		}
		if (is_source != true) {
			cout << "首行检查的文件[" << args[HW_ARGS_FILE].get_string() << "]必须是源程序文件." << endl;
			return -1;
		}
	}
	if (args[HW_ARGS_ACTION].get_string() == "secondline") {
		// 判断是否单文件
		if (args[HW_ARGS_FILE].get_string() == "all") {
			cout << "HW_Check_SecondLine 只能针对单文件" << endl;
			return -1;
		}
		// 判断stu是否是all
		if (args[HW_ARGS_STU].get_string() != "all") {
			cout << "HW_Check_SecondLine 只能针对全体学生" << endl;
			return -1;
		}
	}
	// 判断课号是不是8/13
	if (args[HW_ARGS_CNO].get_string().size() != 8 && args[HW_ARGS_CNO].get_string().size() != 13) {
		cout << "课号不是8/13位" << endl;
		return -1;
	}

	return 0;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
 ***************************************************************************/
static int base(args_analyse_tools* args, MYSQL* mysql, MYSQL_RES* result, MYSQL_ROW& row, string& src_rootdir)
{
	unsigned long long stu_num; // 学生数量
	unsigned long long file_num; // 文件数量
	string stu; // 存姓名学号的字符串
	vector<string> hw; // 存放文件名的字符串
	unsigned int hw_maxlen = 0; // 文件名最大长度
	const char* ret = NULL;

	bool found = false; // 是否提交
	bool pdf_right = true; // pdf格式正确
	bool cno_right = false; // 课号正确
	bool is_source_code = false; // 是否为源程序
	bool is_utf8 = false; // 是否是UTF8编码

	int nosubmit = 0; // 未提交计数器
	int right = 0; // 正确计数器
	int wrongpdf = 0; // pdf格式错误计数器
	int notgb = 0; // 编码错误计数器

	int total_pass = 0; // 通过总数
	int total_nosubmit = 0; // 未提交计数器
	int total_wrongpdf = 0; // pdf格式错误计数器
	int total_notgb = 0; // 编码错误计数器

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


	// 查询是否有该课号
	{
		if (mysql_query(mysql, search_cno.c_str())) {
			cout << "mysql_query failed(" << mysql_error(mysql) << ")" << endl;
			return -1;
		}

		/* 将查询结果存储起来，出现错误则返回NULL */
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
			cout << "mysql execute [call proc_hwcheck_get_stulist(\"2023/2024/1\", \"" << args[HW_ARGS_CNO].get_string() << "\"); ] 查询到符合要求的记录为[0]." << endl;
			return -1;
		}
	}

	// 查询该课号对应的学生
	{
		if (mysql_query(mysql, search_stu.c_str())) {
			cout << "mysql_query failed(" << mysql_error(mysql) << ")" << endl;
			return -1;
		}

		/* 将查询结果存储起来，出现错误则返回NULL
			注意：查询结果为NULL，不会返回NULL */
		if ((result = mysql_store_result(mysql)) == NULL) {
			cout << "mysql_store_result failed" << endl;
			return -1;
		}
	}

	if (args[HW_ARGS_FILE].get_string() != "all") {
		if (args[HW_ARGS_STU].get_string() != "all") {
			while ((row = mysql_fetch_row(result)) != NULL) {
				ret = strstr(row[2], args[HW_ARGS_STU].get_string().c_str());
				if (ret != NULL) {// 找到了
					stu = row[2];
					stu += "/";
					stu += row[3];
					break;
				}
			}
			if (ret == NULL)  // 没找到
				stu_num = 0;
			else { // 找到了
				stu_num = 1;
				base_ErrorType(found, pdf_right, is_utf8, is_source_code, args[HW_ARGS_CNO].get_string(), args[HW_ARGS_STU].get_string(), args[HW_ARGS_FILE].get_string(), src_rootdir);
			}

			// 输出结果 
			cout << "课号 : " << args[HW_ARGS_CNO].get_string() << ' ' << "学生数量 : " << stu_num << ' ' << "源文件名 : " << args[HW_ARGS_FILE].get_string() << endl;
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
			cout << "课号 : " << args[HW_ARGS_CNO].get_string() << ' ' << "学生数量 : " << stu_num << ' ' << "源文件名 : " << args[HW_ARGS_FILE].get_string() << endl;

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

		// 查找该课号的所有作业
		{
			if (mysql_query(mysql, search_hw.c_str())) {
				cout << "mysql_query failed(" << mysql_error(mysql) << ")" << endl;
				return -1;
			}

			/* 将查询结果存储起来，出现错误则返回NULL
				注意：查询结果为NULL，不会返回NULL */
			if ((result_hw = mysql_store_result(mysql)) == NULL) {
				cout << "mysql_store_result failed" << endl;
				return -1;
			}
		}

		file_num = mysql_num_rows(result_hw);
		if (file_num == 0) {
			cout << "本次操作的学生数量为0/文件数量为0，未执行" << endl;
			return -1;
		}

		while ((row = mysql_fetch_row(result_hw)) != NULL) {
			hw.push_back(row[5]); // 将所有文件传入vector 以便计算最大长度
			if (strlen(row[5]) > hw_maxlen)
				hw_maxlen = strlen(row[5]);
		}

		if (args[HW_ARGS_STU].get_string() != "all") {
			while ((row = mysql_fetch_row(result)) != NULL) {
				ret = strstr(row[2], args[HW_ARGS_STU].get_string().c_str());
				if (ret != NULL) {// 找到了
					stu = row[3];
					break;
				}
			}
			if (ret == NULL) { // 没找到
				cout << "本次操作的学生数量为0/文件数量为0，未执行" << endl;
				return -1;
			}
			else { // 找到了
				stu_num = 1;

				cout << "1  : 学号-" << args[HW_ARGS_STU].get_string() << ' ' << "姓名-" << stu << ' ' << "课号-" << args[HW_ARGS_CNO].get_string() << ' ' << "文件数量-" << file_num << endl;

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
				cout << setw(3) << i << ": 学号-" << row[2] << ' ' << "姓名-" << stu << ' ' << "课号-" << args[HW_ARGS_CNO].get_string() << ' ' << "文件数量-" << file_num << endl;
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

	/* 释放result，否则会丢失内存 */
	mysql_free_result(result);
	return 0;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
 ***************************************************************************/
static int firstline(args_analyse_tools* args, MYSQL* mysql, MYSQL_RES* result, MYSQL_ROW& row, string& src_rootdir)
{
	const char* ret = NULL;
	unsigned long long stu_num; // 学生数量
	unsigned long long file_num; // 文件数量
	unsigned int hw_maxlen = 0; // 文件名最大长度
	vector<string> hw; // 存放文件名的字符串
	string num; // 存学号的字符串
	string name; // 存姓名的字符串
	string major_s; // 存专业简称的字符串
	string major; // 存专业全称的字符串

	bool found = true; // 是否提交
	bool cno_right = false; // 课号正确
	bool is_anno = true; // 是否是注释
	bool three = true; // 是否是三项
	bool error = false; // 是否错误
	bool is_utf8 = false; // 是否是UTF8编码
	bool num_wrong = false; // 学号是否匹配
	bool name_wrong = false; // 姓名是否匹配
	bool major_wrong = false; // 班级是否匹配
	bool is_source = true; // 是否是源程序
	bool wrong_anno_form = false; // 注释本身格式是否错误

	int nosubmit = 0; // 未提交计数器
	int right = 0; // 正确计数器
	int noanno = 0; // 非注释计数器
	int notgb = 0; // 编码错误计数器
	int notthree = 0; // 不是三项计数器
	int nomatch = 0; // 注释不匹配计数器
	int wrongform = 0; // 注释本身格式错误计数器

	int total_pass = 0; // 通过总数
	int total_nosubmit = 0; // 未提交计数器
	int total_noanno = 0; // 非注释计数器
	int total_notgb = 0; // 编码错误计数器
	int total_notthree = 0; // 非三项计数器
	int total_nomatch = 0; // 不匹配计数器
	int total_wrongform = 0; // 注释本身格式错误计数器

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

	// 查询是否有该课号
	{
		if (mysql_query(mysql, search_cno.c_str())) {
			cout << "mysql_query failed(" << mysql_error(mysql) << ")" << endl;
			return -1;
		}

		/* 将查询结果存储起来，出现错误则返回NULL */
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
			cout << "mysql execute [call proc_hwcheck_get_stulist(\"2023/2024/1\", \"" << args[HW_ARGS_CNO].get_string() << "\"); ] 查询到符合要求的记录为[0]." << endl;
			return -1;
		}
	}

	// 查询该课号对应的学生
	{
		if (mysql_query(mysql, search_stu.c_str())) {
			cout << "mysql_query failed(" << mysql_error(mysql) << ")" << endl;
			return -1;
		}

		/* 将查询结果存储起来，出现错误则返回NULL
			注意：查询结果为NULL，不会返回NULL */
		if ((result = mysql_store_result(mysql)) == NULL) {
			cout << "mysql_store_result failed" << endl;
			return -1;
		}
	}

	if (args[HW_ARGS_FILE].get_string() != "all") {
		if (args[HW_ARGS_STU].get_string() != "all") {
			while ((row = mysql_fetch_row(result)) != NULL) {
				ret = strstr(row[2], args[HW_ARGS_STU].get_string().c_str());
				if (ret != NULL) {// 找到了
					name = row[3];
					num = row[2];
					major_s = row[6];
					major = row[5];
					break;
				}
			}
			if (ret == NULL)  // 没找到
				stu_num = 0;
			else { // 找到了
				stu_num = 1;
				firstline_ErrorType(found, is_utf8, is_anno, three, error, num_wrong, name_wrong, major_wrong, wrong_anno_form,
					args[HW_ARGS_CNO].get_string(), num, args[HW_ARGS_FILE].get_string(), name, major_s, major, src_rootdir);
			}

			// 输出结果 
			cout << "课号 : " << args[HW_ARGS_CNO].get_string() << ' ' << "学生数量 : " << stu_num << ' ' << "源文件名 : " << args[HW_ARGS_FILE].get_string() << endl;
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
			cout << "课号 : " << args[HW_ARGS_CNO].get_string() << ' ' << "学生数量 : " << stu_num << ' ' << "源文件名 : " << args[HW_ARGS_FILE].get_string() << endl;

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

		// 查找该课号的所有作业
		{
			if (mysql_query(mysql, search_hw.c_str())) {
				cout << "mysql_query failed(" << mysql_error(mysql) << ")" << endl;
				return -1;
			}

			/* 将查询结果存储起来，出现错误则返回NULL
				注意：查询结果为NULL，不会返回NULL */
			if ((result_hw = mysql_store_result(mysql)) == NULL) {
				cout << "mysql_store_result failed" << endl;
				return -1;
			}
		}

		while ((row = mysql_fetch_row(result_hw)) != NULL) {
			is_source = source(row[5]);
			if (is_source == true)
				hw.push_back(row[5]); // 将所有文件传入vector 以便计算最大长度
			if (is_source == true && strlen(row[5]) > hw_maxlen)
				hw_maxlen = strlen(row[5]);
		}

		file_num = hw.size();
		if (file_num == 0) {
			cout << "本次操作的学生数量为0/文件数量为0，未执行" << endl;
			return -1;
		}

		if (args[HW_ARGS_STU].get_string() != "all") {
			while ((row = mysql_fetch_row(result)) != NULL) {
				ret = strstr(row[2], args[HW_ARGS_STU].get_string().c_str());
				if (ret != NULL) {// 找到了
					name = row[3];
					num = row[2];
					major_s = row[6];
					major = row[5];
					break;
				}
			}
			if (ret == NULL) { // 没找到
				cout << "本次操作的学生数量为0/文件数量为0，未执行" << endl;
				return -1;
			}
			else { // 找到了
				stu_num = 1;

				cout << "1  : 学号-" << args[HW_ARGS_STU].get_string() << ' ' << "姓名-" << name << ' ' << "课号-" << args[HW_ARGS_CNO].get_string() << ' ' << "文件数量-" << file_num << endl;

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
				cout << setw(3) << i << ": 学号-" << row[2] << ' ' << "姓名-" << name << ' ' << "课号-" << args[HW_ARGS_CNO].get_string() << ' ' << "文件数量-" << file_num << endl;
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

	/* 释放result，否则会丢失内存 */
	mysql_free_result(result);
	return 0;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
 ***************************************************************************/
static int secondline(args_analyse_tools* args, MYSQL* mysql, MYSQL_RES* result, MYSQL_ROW& row, string& src_rootdir)
{
	bool cno_right = false; // 课号正确
	unsigned long long stu_num; // 学生数量
	string num; // 存学号的字符串
	string name; // 存姓名的字符串

	bool found = true; // 是否提交
	bool is_anno = true; // 是否是注释
	bool is_utf8 = false; // 是否是UTF8编码
	bool num_wrong = false; // 学号是否匹配
	bool name_wrong = false; // 姓名是否匹配
	bool is_seven = true; // 学号是否7位
	bool lack = false; // 是否缺失项

	int nosubmit = 0; // 未提交计数器
	int right = 0; // 正确计数器
	int noanno = 0; // 非注释计数器
	int notgb = 0; // 编码错误计数器

	string search_cno = "select * from view_hwcheck_hwlist where hw_cno = \"" + args[HW_ARGS_CNO].get_string() + "\"";
	string search_stu = "select * from view_hwcheck_stulist where stu_cno = \"" + args[HW_ARGS_CNO].get_string() + "\"";
	string search_hw = "select * from view_hwcheck_hwlist where hw_cno = \"" + args[HW_ARGS_CNO].get_string() + "\"";

	// 查询是否有该课号
	{
		if (mysql_query(mysql, search_cno.c_str())) {
			cout << "mysql_query failed(" << mysql_error(mysql) << ")" << endl;
			return -1;
		}

		/* 将查询结果存储起来，出现错误则返回NULL */
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
			cout << "mysql execute [call proc_hwcheck_get_stulist(\"2023/2024/1\", \"" << args[HW_ARGS_CNO].get_string() << "\"); ] 查询到符合要求的记录为[0]." << endl;
			return -1;
		}
	}

	// 查询该课号对应的学生
	{
		if (mysql_query(mysql, search_stu.c_str())) {
			cout << "mysql_query failed(" << mysql_error(mysql) << ")" << endl;
			return -1;
		}

		/* 将查询结果存储起来，出现错误则返回NULL
			注意：查询结果为NULL，不会返回NULL */
		if ((result = mysql_store_result(mysql)) == NULL) {
			cout << "mysql_store_result failed" << endl;
			return -1;
		}
	}

	stu_num = mysql_num_rows(result);
	cout << "课号 : " << args[HW_ARGS_CNO].get_string() << ' ' << "学生数量 : " << stu_num << ' ' << "源文件名 : " << args[HW_ARGS_FILE].get_string() << endl;

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
	cout << "交叉检查结果：" << endl;

	// 查询该课号对应的学生
	{
		if (mysql_query(mysql, search_stu.c_str())) {
			cout << "mysql_query failed(" << mysql_error(mysql) << ")" << endl;
			return -1;
		}

		/* 将查询结果存储起来，出现错误则返回NULL
			注意：查询结果为NULL，不会返回NULL */
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

	/* 释放result，否则会丢失内存 */
	mysql_free_result(result);
	return 0;
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
	int cur_argc;

	//参数输入正确性分析
	{
		if ((cur_argc = args_analyse_process(argc, argv, args, 0)) < 0)
		{
			//错误信息在函数中已打印
			return -1;
		}

		/* 对help做特殊处理 */
		if (args[HW_ARGS_HELP].existed()) {
			//只要有 --help，其它参数都忽略，显示帮助即可
			args_analyse_print(args);
			usage(argv[0]);
			return -1; //执行完成直接退出
		}

		// 必选
		{
			if (args[HW_ARGS_ACTION].existed() == 0) {
				cout << "参数[" << args[HW_ARGS_ACTION].get_name() << "]必须指定." << endl;
				return -1;
			}

			if (args[HW_ARGS_CNO].existed() == 0) {
				cout << "参数[" << args[HW_ARGS_CNO].get_name() << "]必须指定." << endl;
				return -1;
			}

			if (args[HW_ARGS_STU].existed() == 0) {
				cout << "参数[" << args[HW_ARGS_STU].get_name() << "]必须指定." << endl;
				return -1;
			}

			if (args[HW_ARGS_FILE].existed() == 0) {
				cout << "参数[" << args[HW_ARGS_FILE].get_name() << "]必须指定." << endl;
				return -1;
			}
		}

		if (args[HW_ARGS_DEBUG].existed())
			args_analyse_print(args);
	}

	/* 进入实际的功能调用，完成相应的功能 */

	//数据库初始化部分
#if 1
	string dbserver, dbuser, dbpasswd, dbname, src_rootdir;
	string cfgfile_name = args[HW_ARGS_CFGFILE].get_string();
	readconfig(cfgfile_name, dbserver, dbuser, dbpasswd, dbname, src_rootdir);

	MYSQL* mysql;
	MYSQL_RES* result = NULL;
	MYSQL_ROW  row;

	/* 初始化 mysql 变量，失败返回NULL */
	if ((mysql = mysql_init(NULL)) == NULL) {
		cout << "mysql_init failed" << endl;
		return -1;
	}

	/* 连接数据库，失败返回NULL
		1、mysqld没运行
		2、没有指定名称的数据库存在 */
	if (mysql_real_connect(mysql, dbserver.c_str(), dbuser.c_str(), dbpasswd.c_str(), dbname.c_str(), 0, NULL, 0) == NULL) {
		cout << "mysql_real_connect failed(" << mysql_error(mysql) << ")" << endl;
		return -1;
	}

	/* 设置字符集，否则读出的字符乱码 */
	mysql_set_character_set(mysql, "gbk");
#endif
	//参数范围正确性分析
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
