/* 2251206 冯羽芯 计科 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <io.h>

#include "../include/class_aat.h"
#include "../include/hw_check.h"
#include "../include/file.h"
#include "../include_mariadb_x86/mysql/mysql.h"      // mysql特有
using namespace std;

const char* suffix1[] = { ".h",".hpp",".c",".cpp","" };

bool Find(const string& cno, const string& num, const string& file, const string& src_rootdir)
{
	string filename = src_rootdir + cno + "-" + num + "/" + file;
	ifstream fin(filename, ios::in);
	if (fin.is_open() == 0) { // 未找到
		fin.close();
		return false;
	}
	else {
		fin.close();
		return true;
	}
}

bool PDF(const string& cno, const string& stu, const string& file, const string& src_rootdir)
{
	const char* ret = strstr(file.c_str(), ".pdf");
	if (ret != NULL) {// pdf
		string filename = src_rootdir + cno + "-" + stu + "/" + file;
		ifstream fin(filename, ios::in);
		char beg[9] = { 0 };
		fin.read(beg, 8);
		ret = strstr(beg, "%PDF-1.");
		if (ret != NULL && beg[7] >= '0' && beg[7] <= '9') {
			fin.close();
			return true;
		}
		else {
			fin.close();
			return false;
		}
	}

	return true;
}

int prenum(unsigned char byte) {
	unsigned char mask = 0x80;
	int num = 0;
	for (int i = 0; i < 8; i++)
		if ((byte & mask) == mask) {
			mask = mask >> 1;
			num++;
		}
		else
			break;

	return num;
}

bool isutf8(const string& cno, const string& stu, const string& file, const string& src_rootdir)
{
	string filename = src_rootdir + cno + "-" + stu + "\\" + file;
	string str;
	ifstream fin(filename, ios::in | ios::binary);
	char isutf8[5] = { '1','1','1','1','1' }; // 1为是utf8 0为不是（GB和纯英文）
	int cnt = 0;
	if (fin.is_open() == 0)
		cout << "Open Failed\n";
	for (int j = 0; j < 5; j++) {
		getline(fin, str);

		int num = 0;
		unsigned int i = 0;
		while (i < str.length())
			if ((str.c_str()[i] & 0x80) == 0x00) {
				// 0XXX_XXXX
				i++;
				cnt++;
				continue;
			}
			else if ((num = prenum(str.c_str()[i])) > 2) {
				/* 110X_XXXX 10XX_XXXX
				 1110_XXXX 10XX_XXXX 10XX_XXXX
				 1111_0XXX 10XX_XXXX 10XX_XXXX 10XX_XXXX
				 1111_10XX 10XX_XXXX 10XX_XXXX 10XX_XXXX 10XX_XXXX
				 1111_110X 10XX_XXXX 10XX_XXXX 10XX_XXXX 10XX_XXXX 10XX_XXXX
				 prenum() 返回首个字节8个bits中首个?0bit前面1bit的个数，该数量也是该字符所使用的字节数  */

				i++;
				for (int j = 0; j < num - 1; j++) {
					//判断后面num - 1 个字节是不是都是10开
					if ((str.c_str()[i] & 0xc0) != 0x80) {
						isutf8[j] = 0;
						break;
					}
					i++;
				}
			}
			else {	//其他情况说明不是utf-8
				isutf8[j] = 0;
				break;
			}

		if (cnt == str.length())
			isutf8[j] = 0;
		cnt = 0;
	}
	fin.close();
	if (isutf8[0] == 0 && isutf8[1] == 0 && isutf8[2] == 0 && isutf8[3] == 0 && isutf8[4] == 0)
		return false;
	else
		return true;
}

bool isanno(bool& wrong_anno_form, const string& cno, const string& stu, const string& file, const string& src_rootdir, const int opt)
{
	string filename = src_rootdir + cno + "-" + stu + "\\" + file;
	ifstream fin(filename, ios::in);
	string str = "";
	char* s;
	if (fin.is_open() == 0) { // 未找到
		fin.close();
		return false;
	}
	while (str == "")
		getline(fin, str);

	if (opt == 2) {
		str = "";
		while (str == "")
			getline(fin, str);
	}

	s = new (nothrow) char[str.length() + 1];
	if (s == NULL)
		cout << "No Memory" << endl;

	strcpy(s, str.c_str());
	trimleft(s);
	trimright(s);
	int len = strlen(s);

	fin.close();

	if ((s[0] == '/' && s[1] == '/')) {
		delete[]s;
		return true;
	}
	if (len >= 4 && s[0] == '/' && s[1] == '*') {
		if (s[len - 1] == '/' && s[len - 2] == '*') {
			delete[]s;
			return true;
		}
		else {
			wrong_anno_form = true;
			delete[]s;
			return false;
		}
	}
	delete[]s;
	return false;
}

bool isthree(const string& cno, const string& num, const string& file, const string& src_rootdir)
{
	string filename = src_rootdir + cno + "-" + num + "\\" + file;
	ifstream fin(filename, ios::in);
	stringstream ss;
	string s1, s2, s3, s4; // 学号 姓名 和班级 顺序乱
	string str = "";
	char* s;
	if (fin.is_open() == 0) { // 未找到
		fin.close();
		return false;
	}

	while (str == "")
		getline(fin, str);
	s = new (nothrow) char[str.length() + 1];
	if (s == NULL)
		cout << "No Memory" << endl;

	strcpy(s, str.c_str());
	trimleft(s);
	trimright(s);

	if (!(s[0] == '/' && s[1] == '/'))
		s[strlen(s) - 2] = '\0';
	ss << &s[2];
	ss >> s1 >> s2 >> s3 >> s4;

	delete[]s;

	fin.close();

	if (s1 == "" || s2 == "" || s3 == "" || s4 != "")
		return false;
	else
		return true;
}

bool iserror(bool& num_wrong, bool& name_wrong, bool& major_wrong, const string& cno, const string& num, const string& file, const string& name, const string& major_s, const string& major, const string& src_rootdir)
{
	string filename = src_rootdir + cno + "-" + num + "\\" + file;
	ifstream fin(filename, ios::in);
	stringstream ss;
	string s1, s2, s3; // 学号 姓名 和班级 顺序乱
	string str = "";
	char* s;

	if (fin.is_open() == 0) { // 未找到
		fin.close();
		return false;
	}

	while (str == "")
		getline(fin, str);
	s = new (nothrow) char[str.length() + 1];
	if (s == NULL)
		cout << "No Memory" << endl;

	strcpy(s, str.c_str());
	trimleft(s);
	trimright(s);

	if (!(s[0] == '/' && s[1] == '/'))
		s[strlen(s) - 2] = '\0';
	ss << &s[2];
	ss >> s1 >> s2 >> s3;

	delete[]s;

	if (s1 == num || s2 == num || s3 == num)
		num_wrong = false;
	else
		num_wrong = true;

	if (s1 == name || s2 == name || s3 == name)
		name_wrong = false;
	else
		name_wrong = true;

	if ((s1 == major || s1 == major_s) || (s2 == major || s2 == major_s) || (s3 == major || s3 == major_s))
		major_wrong = false;
	else
		major_wrong = true;

	fin.close();

	if (num_wrong == true || name_wrong == true || major_wrong == true)
		return true;
	else
		return false;
}

bool checkcontent(const string& cno, const string& num, const string& name, const string& file, const string& src_rootdir, const char& display, const int& j)
{
	string filename = src_rootdir + cno + "-" + num + "\\" + file;
	ifstream fin(filename, ios::in);
	stringstream ss;
	string str;
	int i = 1;

	char* s;
	if (fin.is_open() == 0) { // 未找到
		fin.close();
		return false;
	}

	// 读第二行
	while (str == "")
		getline(fin, str);
	str = "";
	while (str == "")
		getline(fin, str);

	s = new (nothrow) char[str.length() + 1];
	if (s == NULL)
		cout << "No Memory" << endl;

	strcpy(s, str.c_str());
	trimleft(s);
	trimright(s);

	if (!(s[0] == '/' && s[1] == '/'))
		s[strlen(s) - 2] = '\0';
	ss << &s[2];
	delete[]s;

	while (1) {
		string number = "", nam = "";
		ss >> number >> nam;

		if (number == "" && nam == "")
			break;

		if (nam == "" && display == '1') {
			cout << setw(3) << j << ": " << setw(16) << num + "/" + name << " : ";
			cout << "第[" << i - 1 << "]个学生后面的信息不全(只读到一项)，后续内容忽略" << endl;
			return false;
		}

		if (number.length() != 7 && display == '1') {
			cout << setw(3) << j << ": " << setw(16) << num + "/" + name << " : ";
			cout << "第" << i << "位同学的学号[" << number << "]不是7位，后续内容忽略" << endl;
			return false;
		}

		if (number.length() == 7)
			for (int j = 0; j < 7; j++)
				if ((number.c_str()[j] > '9' || number.c_str()[j] < '0') && display == '1') {
					cout << setw(3) << j << ": " << setw(16) << num + "/" + name << " : ";
					cout << "第" << i << "位同学的学号[" << number << "]中有非数字存在，后续内容忽略" << endl;
					return false;
				}

		if (number == num && display == '1') {
			cout << setw(3) << j << ": " << setw(16) << num + "/" + name << " : ";
			cout << "第[" << i << "]项写了自己，后续内容忽略" << endl;
			return false;
		}

		i++;
	}

	return true;
}

bool source(const string& file)
{
	const char* ret = NULL;
	for (int i = 0; suffix1[i] != ""; i++) {
		ret = strstr(file.c_str(), suffix1[i]);
		if (ret != NULL)
			break;
	}
	if (ret == NULL)
		return false;
	else
		return true;
}

void base_detail_info(const int& nosubmit, const int& right, const int& wrongpdf, const int& notgb, const unsigned long long& stu_num)
{
	int len;
	if (notgb != 0)
		len = 38;
	else if (wrongpdf != 0)
		len = 29;
	else if (nosubmit != 0)
		len = 18;
	else if (right != 0)
		len = 16;
	else
		len = 12;
	cout << resetiosflags(ios::left);
	if (right == stu_num)
		cout << "全部";
	else
		cout << "检查";
	cout << "通过" << right << "/" << stu_num << "个学生，本次通过" << right << "个" << endl;
	cout << setfill('=') << setw(len) << '=' << endl;
	cout << "详细信息" << endl;
	cout << setfill('=') << setw(len) << '=' << endl;
	cout << setfill(' ');
	if (right != 0)
		cout << setw(len - 7) << "正确 : " << right << endl;
	if (nosubmit != 0)
		cout << setw(len - 7) << "未提交 : " << nosubmit << endl;
	if (wrongpdf != 0)
		cout << setw(len - 7) << "PDF文件格式不正确 : " << wrongpdf << endl;
	if (notgb != 0)
		cout << "  源文件格式不正确(非GB编码) : " << notgb << endl;
	cout << setfill('=') << setw(len) << '=' << endl;
	cout << setfill(' ');
}

void base_stu_detail_info(const int& nosubmit, const int& right, const int& wrongpdf, const int& notgb, const unsigned long long& file_num)
{
	int len;
	if (notgb != 0)
		len = 38;
	else if (wrongpdf != 0)
		len = 29;
	else if (nosubmit != 0)
		len = 18;
	else if (right != 0)
		len = 16;
	else
		len = 12;
	cout << resetiosflags(ios::left);
	if (right == file_num)
		cout << "全部";
	else
		cout << "检查";
	cout << "通过" << right << "/" << file_num << "个文件，本次通过" << right << "个" << endl;
	cout << setfill('-') << setw(len) << '-' << endl;
	cout << "学生详细信息" << endl;
	cout << setfill('-') << setw(len) << '-' << endl;
	cout << setfill(' ');
	if (right != 0)
		cout << setw(len - 7) << "正确 : " << right << endl;
	if (nosubmit != 0)
		cout << setw(len - 7) << "未提交 : " << nosubmit << endl;
	if (wrongpdf != 0)
		cout << setw(len - 7) << "PDF文件格式不正确 : " << wrongpdf << endl;
	if (notgb != 0)
		cout << "  源文件格式不正确(非GB编码) : " << notgb << endl;
	cout << setfill('-') << setw(len) << '-' << endl;
	cout << setfill(' ');
	cout << endl;
}

void base_all_detail_info(const int& nosubmit, const int& right, const int& wrongpdf, const int& notgb, const unsigned long long& stu_num, const unsigned long long& file_num)
{
	int len;
	if (notgb != 0)
		len = 38;
	else if (wrongpdf != 0)
		len = 29;
	else if (nosubmit != 0)
		len = 18;
	else if (right != 0)
		len = 16;
	else
		len = 12;
	cout << resetiosflags(ios::left);
	cout << "共完成" << stu_num << "个学生的检查，文件总数:" << stu_num * file_num << "，通过总数:" << right << "，本次通过" << right << "个" << endl;
	cout << setfill('=') << setw(len) << '=' << endl;
	cout << "整体详细信息" << endl;
	cout << setfill('=') << setw(len) << '=' << endl;
	cout << setfill(' ');
	if (right != 0)
		cout << setw(len - 7) << "正确 : " << right << endl;
	if (nosubmit != 0)
		cout << setw(len - 7) << "未提交 : " << nosubmit << endl;
	if (wrongpdf != 0)
		cout << setw(len - 7) << "PDF文件格式不正确 : " << wrongpdf << endl;
	if (notgb != 0)
		cout << "  源文件格式不正确(非GB编码) : " << notgb << endl;
	cout << setfill('=') << setw(len) << '=' << endl;
	cout << setfill(' ');
}

void firstline_detail_info(const int& nosubmit, const int& right, const int& notgb, const int& noanno, const int& notthree, const int& nomatch, const int& wrongform, const unsigned long long& stu_num)
{
	int len;
	if (notgb != 0)
		len = 38;
	else if (wrongform != 0)
		len = 34;
	else if (noanno != 0)
		len = 26;
	else if (notthree != 0 || nomatch != 0)
		len = 24;
	else if (nosubmit != 0)
		len = 18;
	else if (right != 0)
		len = 16;
	else
		len = 12;
	cout << resetiosflags(ios::left);
	if (right == stu_num)
		cout << "全部";
	else
		cout << "检查";
	cout << "通过" << right << "/" << stu_num << "个学生，本次通过" << right << "个" << endl;
	cout << setfill('=') << setw(len) << '=' << endl;
	cout << "详细信息" << endl;
	cout << setfill('=') << setw(len) << '=' << endl;
	cout << setfill(' ');
	if (right != 0)
		cout << setw(len - 7) << "正确 : " << right << endl;
	if (nosubmit != 0)
		cout << setw(len - 7) << "未提交 : " << nosubmit << endl;
	if (notgb != 0)
		cout << "  源文件格式不正确(非GB编码) : " << notgb << endl;
	if (wrongform != 0)
		cout << setw(len - 7) << "首行多行注释格式不正确 : " << wrongform << endl;
	if (noanno != 0)
		cout << setw(len - 7) << "首行不是注释行 : " << noanno << endl;
	if (notthree != 0)
		cout << setw(len - 7) << "首行不是三项 : " << notthree << endl;
	if (nomatch != 0)
		cout << setw(len - 7) << "首行检查出错 : " << nomatch << endl;

	cout << setfill('=') << setw(len) << '=' << endl;
	cout << setfill(' ');
}

void firstline_stu_detail_info(const int& nosubmit, const int& right, const int& notgb, const int& noanno, const int& notthree, const int& nomatch, const int& wrongform, const unsigned long long& file_num)
{
	int len;
	if (notgb != 0)
		len = 38;
	else if (wrongform != 0)
		len = 34;
	else if (noanno != 0)
		len = 26;
	else if (notthree != 0 || nomatch != 0)
		len = 24;
	else if (nosubmit != 0)
		len = 18;
	else if (right != 0)
		len = 16;
	else
		len = 12;
	cout << resetiosflags(ios::left);
	if (right == file_num)
		cout << "全部";
	else
		cout << "检查";
	cout << "通过" << right << "/" << file_num << "个文件，本次通过" << right << "个" << endl;
	cout << setfill('-') << setw(len) << '-' << endl;
	cout << "学生详细信息" << endl;
	cout << setfill('-') << setw(len) << '-' << endl;
	cout << setfill(' ');
	if (right != 0)
		cout << setw(len - 7) << "正确 : " << right << endl;
	if (nosubmit != 0)
		cout << setw(len - 7) << "未提交 : " << nosubmit << endl;
	if (notgb != 0)
		cout << "  源文件格式不正确(非GB编码) : " << notgb << endl;
	if (wrongform != 0)
		cout << setw(len - 7) << "首行多行注释格式不正确 : " << wrongform << endl;
	if (noanno != 0)
		cout << setw(len - 7) << "首行不是注释行 : " << noanno << endl;
	if (notthree != 0)
		cout << setw(len - 7) << "首行不是三项 : " << notthree << endl;
	if (nomatch != 0)
		cout << setw(len - 7) << "首行检查出错 : " << nomatch << endl;

	cout << setfill('-') << setw(len) << '-' << endl;
	cout << setfill(' ');
}

void firstline_all_detail_info(const int& nosubmit, const int& right, const int& notgb, const int& noanno, const int& notthree, const int& nomatch, const int& wrongform, const unsigned long long& file_num, const unsigned long long& stu_num)
{
	int len;
	if (notgb != 0)
		len = 38;
	else if (wrongform != 0)
		len = 34;
	else if (noanno != 0)
		len = 26;
	else if (notthree != 0 || nomatch != 0)
		len = 24;
	else if (nosubmit != 0)
		len = 18;
	else if (right != 0)
		len = 16;
	else
		len = 12;
	cout << resetiosflags(ios::left);
	cout << "共完成" << stu_num << "个学生的检查，文件总数:" << stu_num * file_num << "，通过总数:" << right << "，本次通过" << right << "个" << endl;
	cout << setfill('=') << setw(len) << '=' << endl;
	cout << "整体详细信息" << endl;
	cout << setfill('=') << setw(len) << '=' << endl;
	cout << setfill(' ');
	if (right != 0)
		cout << setw(len - 7) << "正确 : " << right << endl;
	if (nosubmit != 0)
		cout << setw(len - 7) << "未提交 : " << nosubmit << endl;
	if (notgb != 0)
		cout << "  源文件格式不正确(非GB编码) : " << notgb << endl;
	if (wrongform != 0)
		cout << setw(len - 7) << "首行多行注释格式不正确 : " << wrongform << endl;
	if (noanno != 0)
		cout << setw(len - 7) << "首行不是注释行 : " << noanno << endl;
	if (notthree != 0)
		cout << setw(len - 7) << "首行不是三项 : " << notthree << endl;
	if (nomatch != 0)
		cout << setw(len - 7) << "首行检查出错 : " << nomatch << endl;
	cout << setfill('=') << setw(len) << '=' << endl;
	cout << setfill(' ');
}

void secondline_detail_info(const int& nosubmit, const int& right, const int& noanno, const int& notgb, const unsigned long long& stu_num)
{
	int len;
	if (notgb != 0)
		len = 38;
	else if (noanno != 0)
		len = 24;
	else if (nosubmit != 0)
		len = 18;
	else if (right != 0)
		len = 16;
	else
		len = 12;
	cout << resetiosflags(ios::left);
	if (right == stu_num)
		cout << "全部";
	else
		cout << "检查";
	cout << "通过" << right << "/" << stu_num << "个学生，本次通过" << right << "个" << endl;
	cout << setfill('=') << setw(len) << '=' << endl;
	cout << "详细信息" << endl;
	cout << setfill('=') << setw(len) << '=' << endl;
	cout << setfill(' ');
	if (right != 0)
		cout << setw(len - 7) << "正确 : " << right << endl;
	if (nosubmit != 0)
		cout << setw(len - 7) << "未提交 : " << nosubmit << endl;
	if (notgb != 0)
		cout << "  源文件格式不正确(非GB编码) : " << notgb << endl;
	if (noanno != 0)
		cout << setw(len - 7) << "次行不是注释 : " << noanno << endl;
	cout << setfill('=') << setw(len) << '=' << endl;
	cout << setfill(' ');
}

void base_StateType(int& nosubmit, int& right, int& wrongpdf, int& notgb, const bool& found, const bool& pdf_right, const bool& is_utf8, const char& ch1, const char& ch2, const char& ch3)
{
	if (found == false) {
		if (ch2 == '1')
			cout << "未提交" << endl;
		nosubmit++;
	}
	else {
		if (pdf_right == false) {
			if (ch3 == '1')
				cout << "PDF文件格式不正确" << endl;
			wrongpdf++;
		}
		if (is_utf8 == true) {
			if (ch3 == '1')
				cout << "源文件格式不正确(非GB编码)" << endl;
			notgb++;
		}
	}
	if (found == true && pdf_right == true && is_utf8 == false) {
		if (ch1 == '1')
			cout << "正确" << endl;
		right++;
	}
}

void firstline_StateType(int& nosubmit, int& right, int& noanno, int& notgb, int& notthree, int& nomatch, int& wrongform,
	const bool& found, const bool& is_utf8, const bool& is_anno, const bool& three, const bool& error, const bool& num_wrong, const bool& name_wrong, const bool& major_wrong, const bool& wrong_anno_form,
	const char& ch1, const char& ch2, const char& ch3,
	const string& cno, const string& num, const string& file, const string& src_rootdir)
{
	if (found == false) {
		if (ch2 == '1')
			cout << "未提交" << endl;
		nosubmit++;
		return;
	}
	else if (is_utf8 == true) {
		if (ch3 == '1')
			cout << "源文件格式不正确(非GB编码)" << endl;
		notgb++;
		return;
	}
	else {
		string filename = src_rootdir + cno + "-" + num + "\\" + file;
		ifstream fin(filename, ios::in);
		string str = "";
		char* s;
		if (fin.is_open() == 0) { // 未找到
			cout << "Open Failed\n";
			return;
		}

		while (str == "")
			getline(fin, str);
		s = new (nothrow) char[str.length() + 1];
		if (s == NULL)
			cout << "No Memory" << endl;

		strcpy(s, str.c_str());
		trimleft(s);
		trimright(s);

		fin.close();
		if (wrong_anno_form == true) {
			if (ch3 == '1') {
				cout << "首行多行注释格式不正确";
				cout << ' ' << '[' << s << ']' << endl;
			}
			wrongform++;
			delete[]s;
			return;
		}
		if (is_anno == false) {
			if (ch3 == '1') {
				cout << "首行不是注释行";
				cout << ' ' << '[' << s << ']' << endl;
			}
			noanno++;
			delete[]s;
			return;
		}
		if (three == false) {
			if (ch3 == '1') {
				cout << "首行不是三项";
				cout << ' ' << '[' << s << ']' << endl;
			}
			notthree++;
			delete[]s;
			return;
		}
		if (error == true) {
			nomatch++;
			if (ch3 == '1') {
				cout << "首行";
				if (num_wrong == true)
					cout << "学号不匹配 ";
				if (name_wrong == true)
					cout << "姓名不匹配 ";
				if (major_wrong == true)
					cout << "班级不匹配 ";
				cout << ' ' << '[' << s << ']' << endl;
			}
			delete[]s;
			return;
		}
	}
	if (ch1 == '1')
		cout << "正确" << endl;
	right++;
}

void base_ErrorType(bool& found, bool& pdf_right, bool& is_utf8, bool& is_source_code,
	const string& cno, const string& stu, const string& file, const string& src_rootdir)
{
	found = false; // 是否提交
	pdf_right = true; // pdf格式正确

	is_source_code = false; // 是否为源程序
	is_utf8 = false; // 是否是UTF8编码

	// 进一步寻找是否提交该文件
	found = Find(cno, stu, file, src_rootdir);

	// pdf正确性
	if (found == true)
		pdf_right = PDF(cno, stu, file, src_rootdir);

	// 是否是UTF8
	is_source_code = source(file);
	if (found == true && is_source_code == true)
		is_utf8 = isutf8(cno, stu, file, src_rootdir);
}

void firstline_ErrorType(bool& found, bool& is_utf8, bool& is_anno, bool& three, bool& error, bool& num_wrong, bool& name_wrong, bool& major_wrong, bool& wrong_anno_form,
	const string& cno, const string& num, const string& file, const string& name, const string& major_s, const string& major, const string& src_rootdir)
{
	found = false; // 是否提交
	is_utf8 = false; // 是否是UTF8编码
	is_anno = true; // 是否是注释
	three = true; // 是否是三项
	error = false; // 是否错误
	num_wrong = false; // 学号是否匹配
	name_wrong = false; // 姓名是否匹配
	major_wrong = false; // 班级是否匹配
	wrong_anno_form = false; // 注释本身格式是否错误

	// 寻找是否提交该文件
	found = Find(cno, num, file, src_rootdir);

	// 是否是UTF8
	if (found == true)
		is_utf8 = isutf8(cno, num, file, src_rootdir);

	// 是否是注释行
	if (is_utf8 == false)
		is_anno = isanno(wrong_anno_form, cno, num, file, src_rootdir, 1);

	// 是否是三项
	if (is_anno == true)
		three = isthree(cno, num, file, src_rootdir);

	// 是否三项匹配
	if (three == true)
		error = iserror(num_wrong, name_wrong, major_wrong, cno, num, file, name, major_s, major, src_rootdir);
}

void secondline_ErrorType(bool& found, bool& is_utf8, bool& is_anno,
	int& nosubmit, int& right, int& noanno, int& notgb, const int& i,
	const char& ch1, const char& ch2, const char& ch3,
	const string& cno, const string& num, const string& file, const string& name, const string& src_rootdir)
{
	found = false; // 是否提交
	is_utf8 = false; // 是否是UTF8编码
	is_anno = true;  // 是否是注释

	// 寻找是否提交该文件
	found = Find(cno, num, file, src_rootdir);
	if (found == false) {
		if (ch2 == '1') {
			cout << setw(3) << i << ": " << setw(16) << num + "/" + name << " : ";
			cout << "未提交" << endl;
		}
		nosubmit++;
		return;
	}

	// 是否是UTF8
	if (found == true)
		is_utf8 = isutf8(cno, num, file, src_rootdir);
	if (is_utf8 == true) {
		if (ch3 == '1') {
			cout << setw(3) << i << ": " << setw(16) << num + "/" + name << " : ";
			cout << "源文件格式不正确(非GB编码)" << endl;
		}
		notgb++;
		return;
	}

	// 是否是注释行
	bool useless;
	if (is_utf8 == false)
		is_anno = isanno(useless, cno, num, file, src_rootdir, 2);
	if (is_anno == false) {
		if (ch3 == '1') {
			cout << setw(3) << i << ": " << setw(16) << num + "/" + name << " : ";
			cout << "次行不是注释" << endl;
		}
		noanno++;
		return;
	}

	right++; // 认为基本正确。开始后续检查
	if (checkcontent(cno, num, name, file, src_rootdir, ch1, i) == true && ch1 == '1') {
		cout << setw(3) << i << ": " << setw(16) << num + "/" + name << " : ";
		cout << "正确" << endl;
	}
}

void doublecheck(const string& cno, const string& num, const string& file, const string& name, const string& src_rootdir, MYSQL* mysql, MYSQL_RES* result, MYSQL_ROW& row)
{
	string filename = src_rootdir + cno + "-" + num + "\\" + file;
	ifstream fin(filename, ios::in);
	stringstream ss;
	string str;
	bool right = false;
	bool nameright = true;
	char* s;
	if (fin.is_open() == 0) { // 未找到
		fin.close();
		return;
	}

	// 读第二行
	while (str == "")
		getline(fin, str);
	str = "";
	while (str == "")
		getline(fin, str);

	s = new (nothrow) char[str.length() + 1];
	if (s == NULL)
		cout << "No Memory" << endl;

	strcpy(s, str.c_str());
	trimleft(s);
	trimright(s);

	if (!(s[0] == '/' && s[1] == '/'))
		s[strlen(s) - 2] = '\0';
	ss << &s[2];
	delete[]s;

	for (int i = 1; ; i++) {
		nameright = true;
		string number = "", nam = "";
		// 输出多少
		{
			ss >> number >> nam;

			if (number == "" && nam == "")
				break;

			if (isutf8(cno, num, file, src_rootdir) == true) // utf8
				break;

			if (nam == "")  // 没写全
				break;

			if (number.length() != 7) // 学号不是7位
				break;

			if (number.length() == 7) // 有特殊字符
				for (int j = 0; j < 7; j++)
					if (number.c_str()[j] > '9' || number.c_str()[j] < '0')
						return;

			if (number == num) // 写自己
				break;
		}

		cout << "     \t" << number << ' ' << nam << '\t';

		string dir = src_rootdir + cno + "-" + number;
		if (_access(dir.c_str(), 0) == -1) {
			right = false;
			cout << "对方学号不存在" << endl;
			continue;
		}

		string search_stu = "select * from view_hwcheck_stulist where stu_cno = \"" + cno + "\"";
		// 查询该课号对应的学生
		{
			if (mysql_query(mysql, search_stu.c_str())) {
				cout << "mysql_query failed(" << mysql_error(mysql) << ")" << endl;
				return;
			}

			/* 将查询结果存储起来，出现错误则返回NULL
				注意：查询结果为NULL，不会返回NULL */
			if ((result = mysql_store_result(mysql)) == NULL) {
				cout << "mysql_store_result failed" << endl;
				return;
			}
		}

		while ((row = mysql_fetch_row(result)) != NULL)
			if (number == row[2] && nam != row[3]) {
				cout << "对方姓名不正确" << endl;
				right = false;
				nameright = false;
				break;
			}

		if (nameright == false)
			continue;

		string checkfile = src_rootdir + cno + "-" + number + "\\" + file; // 打开对方文件
		ifstream check(checkfile, ios::in);
		if (check.is_open() == 0) { // 未找到
			check.close();
			right = false;
			cout << "抛弃了你" << endl;
			continue;
		}

		// 打开了
		stringstream ss1;
		string str1;
		char* s1;

		// 读第二行
		while (str1 == "")
			getline(check, str1);
		str1 = "";
		while (str1 == "")
			getline(check, str1);

		s1 = new (nothrow) char[str1.length() + 1];
		if (s1 == NULL)
			cout << "No Memory" << endl;

		strcpy(s1, str1.c_str());
		trimleft(s1);
		trimright(s1);

		if (!(s1[0] == '/' && s1[1] == '/'))
			s1[strlen(s1) - 2] = '\0';
		ss1 << &s1[2];
		delete[]s1;
		if (isutf8(cno, number, file, src_rootdir) == false)
			while (1) {
				right = false;
				string number1 = "", nam1 = "";
				ss1 >> number1 >> nam1;

				if (number1 == "" && nam1 == "") { // 结束了
					if (right == false)
						cout << "抛弃了你" << endl;
					break;
				}

				if (number1 == num && nam1 == name) { // 正确
					right = true;
					break;
				}

				if (number1 == num && nam1 != name) { // 姓名不正确
					right = false;
					cout << "没写对你名字" << endl;
					break;
				}

				if (nam1 == "") {
					right = false;
					cout << "抛弃了你" << endl;
					break;
				}

				if (number1.length() != 7) {
					right = false;
					cout << "抛弃了你" << endl;
					break;
				}

				if (number1.length() == 7)
					for (int j = 0; j < 7; j++)
						if ((number1.c_str()[j] > '9' || number1.c_str()[j] < '0')) {
							right = false;
							cout << "抛弃了你" << endl;
							break;
						}

				if (number1 == number) {// 写了自己
					right = false;
					cout << "抛弃了你" << endl;
					break;
				}
			}
		else {
			right = false;
			cout << "抛弃了你" << endl;
		}

		if (right == true)
			cout << endl;
	}
}