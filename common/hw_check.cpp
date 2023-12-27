/* 2251206 ����о �ƿ� */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <io.h>

#include "../include/class_aat.h"
#include "../include/hw_check.h"
#include "../include/file.h"
#include "../include_mariadb_x86/mysql/mysql.h"      // mysql����
using namespace std;

const char* suffix1[] = { ".h",".hpp",".c",".cpp","" };

bool Find(const string& cno, const string& num, const string& file, const string& src_rootdir)
{
	string filename = src_rootdir + cno + "-" + num + "/" + file;
	ifstream fin(filename, ios::in);
	if (fin.is_open() == 0) { // δ�ҵ�
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
	char isutf8[5] = { '1','1','1','1','1' }; // 1Ϊ��utf8 0Ϊ���ǣ�GB�ʹ�Ӣ�ģ�
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
				 prenum() �����׸��ֽ�8��bits���׸�?0bitǰ��1bit�ĸ�����������Ҳ�Ǹ��ַ���ʹ�õ��ֽ���  */

				i++;
				for (int j = 0; j < num - 1; j++) {
					//�жϺ���num - 1 ���ֽ��ǲ��Ƕ���10��
					if ((str.c_str()[i] & 0xc0) != 0x80) {
						isutf8[j] = 0;
						break;
					}
					i++;
				}
			}
			else {	//�������˵������utf-8
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
	if (fin.is_open() == 0) { // δ�ҵ�
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
	string s1, s2, s3, s4; // ѧ�� ���� �Ͱ༶ ˳����
	string str = "";
	char* s;
	if (fin.is_open() == 0) { // δ�ҵ�
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
	string s1, s2, s3; // ѧ�� ���� �Ͱ༶ ˳����
	string str = "";
	char* s;

	if (fin.is_open() == 0) { // δ�ҵ�
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
	if (fin.is_open() == 0) { // δ�ҵ�
		fin.close();
		return false;
	}

	// ���ڶ���
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
			cout << "��[" << i - 1 << "]��ѧ���������Ϣ��ȫ(ֻ����һ��)���������ݺ���" << endl;
			return false;
		}

		if (number.length() != 7 && display == '1') {
			cout << setw(3) << j << ": " << setw(16) << num + "/" + name << " : ";
			cout << "��" << i << "λͬѧ��ѧ��[" << number << "]����7λ���������ݺ���" << endl;
			return false;
		}

		if (number.length() == 7)
			for (int j = 0; j < 7; j++)
				if ((number.c_str()[j] > '9' || number.c_str()[j] < '0') && display == '1') {
					cout << setw(3) << j << ": " << setw(16) << num + "/" + name << " : ";
					cout << "��" << i << "λͬѧ��ѧ��[" << number << "]���з����ִ��ڣ��������ݺ���" << endl;
					return false;
				}

		if (number == num && display == '1') {
			cout << setw(3) << j << ": " << setw(16) << num + "/" + name << " : ";
			cout << "��[" << i << "]��д���Լ����������ݺ���" << endl;
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
		cout << "ȫ��";
	else
		cout << "���";
	cout << "ͨ��" << right << "/" << stu_num << "��ѧ��������ͨ��" << right << "��" << endl;
	cout << setfill('=') << setw(len) << '=' << endl;
	cout << "��ϸ��Ϣ" << endl;
	cout << setfill('=') << setw(len) << '=' << endl;
	cout << setfill(' ');
	if (right != 0)
		cout << setw(len - 7) << "��ȷ : " << right << endl;
	if (nosubmit != 0)
		cout << setw(len - 7) << "δ�ύ : " << nosubmit << endl;
	if (wrongpdf != 0)
		cout << setw(len - 7) << "PDF�ļ���ʽ����ȷ : " << wrongpdf << endl;
	if (notgb != 0)
		cout << "  Դ�ļ���ʽ����ȷ(��GB����) : " << notgb << endl;
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
		cout << "ȫ��";
	else
		cout << "���";
	cout << "ͨ��" << right << "/" << file_num << "���ļ�������ͨ��" << right << "��" << endl;
	cout << setfill('-') << setw(len) << '-' << endl;
	cout << "ѧ����ϸ��Ϣ" << endl;
	cout << setfill('-') << setw(len) << '-' << endl;
	cout << setfill(' ');
	if (right != 0)
		cout << setw(len - 7) << "��ȷ : " << right << endl;
	if (nosubmit != 0)
		cout << setw(len - 7) << "δ�ύ : " << nosubmit << endl;
	if (wrongpdf != 0)
		cout << setw(len - 7) << "PDF�ļ���ʽ����ȷ : " << wrongpdf << endl;
	if (notgb != 0)
		cout << "  Դ�ļ���ʽ����ȷ(��GB����) : " << notgb << endl;
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
	cout << "�����" << stu_num << "��ѧ���ļ�飬�ļ�����:" << stu_num * file_num << "��ͨ������:" << right << "������ͨ��" << right << "��" << endl;
	cout << setfill('=') << setw(len) << '=' << endl;
	cout << "������ϸ��Ϣ" << endl;
	cout << setfill('=') << setw(len) << '=' << endl;
	cout << setfill(' ');
	if (right != 0)
		cout << setw(len - 7) << "��ȷ : " << right << endl;
	if (nosubmit != 0)
		cout << setw(len - 7) << "δ�ύ : " << nosubmit << endl;
	if (wrongpdf != 0)
		cout << setw(len - 7) << "PDF�ļ���ʽ����ȷ : " << wrongpdf << endl;
	if (notgb != 0)
		cout << "  Դ�ļ���ʽ����ȷ(��GB����) : " << notgb << endl;
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
		cout << "ȫ��";
	else
		cout << "���";
	cout << "ͨ��" << right << "/" << stu_num << "��ѧ��������ͨ��" << right << "��" << endl;
	cout << setfill('=') << setw(len) << '=' << endl;
	cout << "��ϸ��Ϣ" << endl;
	cout << setfill('=') << setw(len) << '=' << endl;
	cout << setfill(' ');
	if (right != 0)
		cout << setw(len - 7) << "��ȷ : " << right << endl;
	if (nosubmit != 0)
		cout << setw(len - 7) << "δ�ύ : " << nosubmit << endl;
	if (notgb != 0)
		cout << "  Դ�ļ���ʽ����ȷ(��GB����) : " << notgb << endl;
	if (wrongform != 0)
		cout << setw(len - 7) << "���ж���ע�͸�ʽ����ȷ : " << wrongform << endl;
	if (noanno != 0)
		cout << setw(len - 7) << "���в���ע���� : " << noanno << endl;
	if (notthree != 0)
		cout << setw(len - 7) << "���в������� : " << notthree << endl;
	if (nomatch != 0)
		cout << setw(len - 7) << "���м����� : " << nomatch << endl;

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
		cout << "ȫ��";
	else
		cout << "���";
	cout << "ͨ��" << right << "/" << file_num << "���ļ�������ͨ��" << right << "��" << endl;
	cout << setfill('-') << setw(len) << '-' << endl;
	cout << "ѧ����ϸ��Ϣ" << endl;
	cout << setfill('-') << setw(len) << '-' << endl;
	cout << setfill(' ');
	if (right != 0)
		cout << setw(len - 7) << "��ȷ : " << right << endl;
	if (nosubmit != 0)
		cout << setw(len - 7) << "δ�ύ : " << nosubmit << endl;
	if (notgb != 0)
		cout << "  Դ�ļ���ʽ����ȷ(��GB����) : " << notgb << endl;
	if (wrongform != 0)
		cout << setw(len - 7) << "���ж���ע�͸�ʽ����ȷ : " << wrongform << endl;
	if (noanno != 0)
		cout << setw(len - 7) << "���в���ע���� : " << noanno << endl;
	if (notthree != 0)
		cout << setw(len - 7) << "���в������� : " << notthree << endl;
	if (nomatch != 0)
		cout << setw(len - 7) << "���м����� : " << nomatch << endl;

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
	cout << "�����" << stu_num << "��ѧ���ļ�飬�ļ�����:" << stu_num * file_num << "��ͨ������:" << right << "������ͨ��" << right << "��" << endl;
	cout << setfill('=') << setw(len) << '=' << endl;
	cout << "������ϸ��Ϣ" << endl;
	cout << setfill('=') << setw(len) << '=' << endl;
	cout << setfill(' ');
	if (right != 0)
		cout << setw(len - 7) << "��ȷ : " << right << endl;
	if (nosubmit != 0)
		cout << setw(len - 7) << "δ�ύ : " << nosubmit << endl;
	if (notgb != 0)
		cout << "  Դ�ļ���ʽ����ȷ(��GB����) : " << notgb << endl;
	if (wrongform != 0)
		cout << setw(len - 7) << "���ж���ע�͸�ʽ����ȷ : " << wrongform << endl;
	if (noanno != 0)
		cout << setw(len - 7) << "���в���ע���� : " << noanno << endl;
	if (notthree != 0)
		cout << setw(len - 7) << "���в������� : " << notthree << endl;
	if (nomatch != 0)
		cout << setw(len - 7) << "���м����� : " << nomatch << endl;
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
		cout << "ȫ��";
	else
		cout << "���";
	cout << "ͨ��" << right << "/" << stu_num << "��ѧ��������ͨ��" << right << "��" << endl;
	cout << setfill('=') << setw(len) << '=' << endl;
	cout << "��ϸ��Ϣ" << endl;
	cout << setfill('=') << setw(len) << '=' << endl;
	cout << setfill(' ');
	if (right != 0)
		cout << setw(len - 7) << "��ȷ : " << right << endl;
	if (nosubmit != 0)
		cout << setw(len - 7) << "δ�ύ : " << nosubmit << endl;
	if (notgb != 0)
		cout << "  Դ�ļ���ʽ����ȷ(��GB����) : " << notgb << endl;
	if (noanno != 0)
		cout << setw(len - 7) << "���в���ע�� : " << noanno << endl;
	cout << setfill('=') << setw(len) << '=' << endl;
	cout << setfill(' ');
}

void base_StateType(int& nosubmit, int& right, int& wrongpdf, int& notgb, const bool& found, const bool& pdf_right, const bool& is_utf8, const char& ch1, const char& ch2, const char& ch3)
{
	if (found == false) {
		if (ch2 == '1')
			cout << "δ�ύ" << endl;
		nosubmit++;
	}
	else {
		if (pdf_right == false) {
			if (ch3 == '1')
				cout << "PDF�ļ���ʽ����ȷ" << endl;
			wrongpdf++;
		}
		if (is_utf8 == true) {
			if (ch3 == '1')
				cout << "Դ�ļ���ʽ����ȷ(��GB����)" << endl;
			notgb++;
		}
	}
	if (found == true && pdf_right == true && is_utf8 == false) {
		if (ch1 == '1')
			cout << "��ȷ" << endl;
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
			cout << "δ�ύ" << endl;
		nosubmit++;
		return;
	}
	else if (is_utf8 == true) {
		if (ch3 == '1')
			cout << "Դ�ļ���ʽ����ȷ(��GB����)" << endl;
		notgb++;
		return;
	}
	else {
		string filename = src_rootdir + cno + "-" + num + "\\" + file;
		ifstream fin(filename, ios::in);
		string str = "";
		char* s;
		if (fin.is_open() == 0) { // δ�ҵ�
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
				cout << "���ж���ע�͸�ʽ����ȷ";
				cout << ' ' << '[' << s << ']' << endl;
			}
			wrongform++;
			delete[]s;
			return;
		}
		if (is_anno == false) {
			if (ch3 == '1') {
				cout << "���в���ע����";
				cout << ' ' << '[' << s << ']' << endl;
			}
			noanno++;
			delete[]s;
			return;
		}
		if (three == false) {
			if (ch3 == '1') {
				cout << "���в�������";
				cout << ' ' << '[' << s << ']' << endl;
			}
			notthree++;
			delete[]s;
			return;
		}
		if (error == true) {
			nomatch++;
			if (ch3 == '1') {
				cout << "����";
				if (num_wrong == true)
					cout << "ѧ�Ų�ƥ�� ";
				if (name_wrong == true)
					cout << "������ƥ�� ";
				if (major_wrong == true)
					cout << "�༶��ƥ�� ";
				cout << ' ' << '[' << s << ']' << endl;
			}
			delete[]s;
			return;
		}
	}
	if (ch1 == '1')
		cout << "��ȷ" << endl;
	right++;
}

void base_ErrorType(bool& found, bool& pdf_right, bool& is_utf8, bool& is_source_code,
	const string& cno, const string& stu, const string& file, const string& src_rootdir)
{
	found = false; // �Ƿ��ύ
	pdf_right = true; // pdf��ʽ��ȷ

	is_source_code = false; // �Ƿ�ΪԴ����
	is_utf8 = false; // �Ƿ���UTF8����

	// ��һ��Ѱ���Ƿ��ύ���ļ�
	found = Find(cno, stu, file, src_rootdir);

	// pdf��ȷ��
	if (found == true)
		pdf_right = PDF(cno, stu, file, src_rootdir);

	// �Ƿ���UTF8
	is_source_code = source(file);
	if (found == true && is_source_code == true)
		is_utf8 = isutf8(cno, stu, file, src_rootdir);
}

void firstline_ErrorType(bool& found, bool& is_utf8, bool& is_anno, bool& three, bool& error, bool& num_wrong, bool& name_wrong, bool& major_wrong, bool& wrong_anno_form,
	const string& cno, const string& num, const string& file, const string& name, const string& major_s, const string& major, const string& src_rootdir)
{
	found = false; // �Ƿ��ύ
	is_utf8 = false; // �Ƿ���UTF8����
	is_anno = true; // �Ƿ���ע��
	three = true; // �Ƿ�������
	error = false; // �Ƿ����
	num_wrong = false; // ѧ���Ƿ�ƥ��
	name_wrong = false; // �����Ƿ�ƥ��
	major_wrong = false; // �༶�Ƿ�ƥ��
	wrong_anno_form = false; // ע�ͱ����ʽ�Ƿ����

	// Ѱ���Ƿ��ύ���ļ�
	found = Find(cno, num, file, src_rootdir);

	// �Ƿ���UTF8
	if (found == true)
		is_utf8 = isutf8(cno, num, file, src_rootdir);

	// �Ƿ���ע����
	if (is_utf8 == false)
		is_anno = isanno(wrong_anno_form, cno, num, file, src_rootdir, 1);

	// �Ƿ�������
	if (is_anno == true)
		three = isthree(cno, num, file, src_rootdir);

	// �Ƿ�����ƥ��
	if (three == true)
		error = iserror(num_wrong, name_wrong, major_wrong, cno, num, file, name, major_s, major, src_rootdir);
}

void secondline_ErrorType(bool& found, bool& is_utf8, bool& is_anno,
	int& nosubmit, int& right, int& noanno, int& notgb, const int& i,
	const char& ch1, const char& ch2, const char& ch3,
	const string& cno, const string& num, const string& file, const string& name, const string& src_rootdir)
{
	found = false; // �Ƿ��ύ
	is_utf8 = false; // �Ƿ���UTF8����
	is_anno = true;  // �Ƿ���ע��

	// Ѱ���Ƿ��ύ���ļ�
	found = Find(cno, num, file, src_rootdir);
	if (found == false) {
		if (ch2 == '1') {
			cout << setw(3) << i << ": " << setw(16) << num + "/" + name << " : ";
			cout << "δ�ύ" << endl;
		}
		nosubmit++;
		return;
	}

	// �Ƿ���UTF8
	if (found == true)
		is_utf8 = isutf8(cno, num, file, src_rootdir);
	if (is_utf8 == true) {
		if (ch3 == '1') {
			cout << setw(3) << i << ": " << setw(16) << num + "/" + name << " : ";
			cout << "Դ�ļ���ʽ����ȷ(��GB����)" << endl;
		}
		notgb++;
		return;
	}

	// �Ƿ���ע����
	bool useless;
	if (is_utf8 == false)
		is_anno = isanno(useless, cno, num, file, src_rootdir, 2);
	if (is_anno == false) {
		if (ch3 == '1') {
			cout << setw(3) << i << ": " << setw(16) << num + "/" + name << " : ";
			cout << "���в���ע��" << endl;
		}
		noanno++;
		return;
	}

	right++; // ��Ϊ������ȷ����ʼ�������
	if (checkcontent(cno, num, name, file, src_rootdir, ch1, i) == true && ch1 == '1') {
		cout << setw(3) << i << ": " << setw(16) << num + "/" + name << " : ";
		cout << "��ȷ" << endl;
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
	if (fin.is_open() == 0) { // δ�ҵ�
		fin.close();
		return;
	}

	// ���ڶ���
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
		// �������
		{
			ss >> number >> nam;

			if (number == "" && nam == "")
				break;

			if (isutf8(cno, num, file, src_rootdir) == true) // utf8
				break;

			if (nam == "")  // ûдȫ
				break;

			if (number.length() != 7) // ѧ�Ų���7λ
				break;

			if (number.length() == 7) // �������ַ�
				for (int j = 0; j < 7; j++)
					if (number.c_str()[j] > '9' || number.c_str()[j] < '0')
						return;

			if (number == num) // д�Լ�
				break;
		}

		cout << "     \t" << number << ' ' << nam << '\t';

		string dir = src_rootdir + cno + "-" + number;
		if (_access(dir.c_str(), 0) == -1) {
			right = false;
			cout << "�Է�ѧ�Ų�����" << endl;
			continue;
		}

		string search_stu = "select * from view_hwcheck_stulist where stu_cno = \"" + cno + "\"";
		// ��ѯ�ÿκŶ�Ӧ��ѧ��
		{
			if (mysql_query(mysql, search_stu.c_str())) {
				cout << "mysql_query failed(" << mysql_error(mysql) << ")" << endl;
				return;
			}

			/* ����ѯ����洢���������ִ����򷵻�NULL
				ע�⣺��ѯ���ΪNULL�����᷵��NULL */
			if ((result = mysql_store_result(mysql)) == NULL) {
				cout << "mysql_store_result failed" << endl;
				return;
			}
		}

		while ((row = mysql_fetch_row(result)) != NULL)
			if (number == row[2] && nam != row[3]) {
				cout << "�Է���������ȷ" << endl;
				right = false;
				nameright = false;
				break;
			}

		if (nameright == false)
			continue;

		string checkfile = src_rootdir + cno + "-" + number + "\\" + file; // �򿪶Է��ļ�
		ifstream check(checkfile, ios::in);
		if (check.is_open() == 0) { // δ�ҵ�
			check.close();
			right = false;
			cout << "��������" << endl;
			continue;
		}

		// ����
		stringstream ss1;
		string str1;
		char* s1;

		// ���ڶ���
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

				if (number1 == "" && nam1 == "") { // ������
					if (right == false)
						cout << "��������" << endl;
					break;
				}

				if (number1 == num && nam1 == name) { // ��ȷ
					right = true;
					break;
				}

				if (number1 == num && nam1 != name) { // ��������ȷ
					right = false;
					cout << "ûд��������" << endl;
					break;
				}

				if (nam1 == "") {
					right = false;
					cout << "��������" << endl;
					break;
				}

				if (number1.length() != 7) {
					right = false;
					cout << "��������" << endl;
					break;
				}

				if (number1.length() == 7)
					for (int j = 0; j < 7; j++)
						if ((number1.c_str()[j] > '9' || number1.c_str()[j] < '0')) {
							right = false;
							cout << "��������" << endl;
							break;
						}

				if (number1 == number) {// д���Լ�
					right = false;
					cout << "��������" << endl;
					break;
				}
			}
		else {
			right = false;
			cout << "��������" << endl;
		}

		if (right == true)
			cout << endl;
	}
}