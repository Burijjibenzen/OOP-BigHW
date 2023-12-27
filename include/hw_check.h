/* 2251206 冯羽芯 计科 */
#pragma once

#include <iostream>
#include <fstream>
#include "../include/class_aat.h"
#include "../include_mariadb_x86/mysql/mysql.h"      // mysql特有
using namespace std;

bool Find(const string& cno, const string& stu, const string& file, const string& src_rootdir);
bool PDF(const string& cno, const string& stu, const string& file, const string& src_rootdir);
int prenum(unsigned char byte);
bool isutf8(const string& cno, const string& stu, const string& file, const string& src_rootdir);
bool source(const string& file);
bool isanno(bool& wrong_anno_form, const string& cno, const string& stu, const string& file, const string& src_rootdir, const int opt);
bool isthree(const string& cno, const string& stu, const string& file, const string& src_rootdir);
bool iserror(bool& num_wrong, bool& name_wrong, bool& major_wrong,
	const string& cno, const string& num, const string& file, const string& name, const string& major_s, const string& major, const string& src_rootdir);
bool checkcontent(const string& cno, const string& num, const string& name, const string& file, const string& src_rootdir, const char& display, const int& i);

//输出详细信息
void base_detail_info(const int& nosubmit, const int& right, const int& wrongpdf, const int& notgb, const unsigned long long& stu_num);
void base_stu_detail_info(const int& nosubmit, const int& right, const int& wrongpdf, const int& notgb, const unsigned long long& file_num);
void base_all_detail_info(const int& nosubmit, const int& right, const int& wrongpdf, const int& notgb, const unsigned long long& stu_num, const unsigned long long& file_num);
void firstline_detail_info(const int& nosubmit, const int& right, const int& notgb, const int& noanno, const int& notthree, const int& nomatch, const int& wrongform, const unsigned long long& stu_num);
void firstline_stu_detail_info(const int& nosubmit, const int& right, const int& notgb, const int& noanno, const int& notthree, const int& nomatch, const int& wrongform, const unsigned long long& file_num);
void firstline_all_detail_info(const int& nosubmit, const int& right, const int& notgb, const int& noanno, const int& notthree, const int& nomatch, const int& wrongform, const unsigned long long& file_num, const unsigned long long& stu_num);
void secondline_detail_info(const int& nosubmit, const int& right, const int& noanno, const int& notgb, const unsigned long long& stu_num);

//根据各种错误类型计数
void base_StateType(int& nosubmit, int& right, int& wrongpdf, int& notgb, const bool& found, const bool& pdf_right, const bool& is_utf8, const char& ch1, const char& ch2, const char& ch3);
void firstline_StateType(int& nosubmit, int& right, int& noanno, int& notgb, int& notthree, int& nomatch, int& wrongform,
	const bool& found, const bool& is_utf8, const bool& is_anno, const bool& three, const bool& error, const bool& num_wrong, const bool& name_wrong, const bool& major_wrong, const bool& wrong_anno_form,
	const char& ch1, const char& ch2, const char& ch3,
	const string& cno, const string& num, const string& file, const string& src_rootdir);

//判断各种错误类型
void base_ErrorType(bool& found, bool& pdf_right, bool& is_utf8, bool& is_source_code,
	const string& cno, const string& stu, const string& file, const string& src_rootdir);
void firstline_ErrorType(bool& found, bool& is_utf8, bool& is_anno, bool& three, bool& error, bool& num_wrong, bool& name_wrong, bool& major_wrong, bool& wrong_anno_form,
	const string& cno, const string& num, const string& file, const string& name, const string& major_s, const string& major, const string& src_rootdir);
void secondline_ErrorType(bool& found, bool& is_utf8, bool& is_anno,
	int& nosubmit, int& right, int& noanno, int& notgb, const int& i,
	const char& ch1, const char& ch2, const char& ch3,
	const string& cno, const string& num, const string& file, const string& name, const string& src_rootdir);

void doublecheck(const string& cno, const string& num, const string& file, const string& name, const string& src_rootdir, MYSQL* mysql, MYSQL_RES* result, MYSQL_ROW& row);