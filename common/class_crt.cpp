/* 2251206 ����о �ƿ� */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "../include/class_crt.h"
using namespace std;

/* ���������Ҫ��ͷ�ļ������� cfgfile_read_tools���ʵ�� */
#include <vector>
#include <string>
#include <string.h>
#include <sstream>
#include "../include/file.h"

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/

/* ������������� */
cfgfile_read_tools::cfgfile_read_tools(const char* _cfgname)
{
	cfgname = _cfgname;
}

cfgfile_read_tools::cfgfile_read_tools(const string& _cfgname)
{
	cfgname = _cfgname;
}

cfgfile_read_tools::~cfgfile_read_tools()
{

}

/* �ж������ļ��Ƿ�򿪳ɹ� */
bool cfgfile_read_tools::is_open()
{
	cfgin.open(cfgname, ios::in);
	if (cfgin.is_open() == 0)
		return false;
	else
		return true;
}

/* ���ȡ�������������еģ�����string�͵�vector�� */
int cfgfile_read_tools::get_all_group(vector <string>& ret)
{
	string str;
	char* s1;

	while (cfgin.eof() == 0) {

		getline(cfgin, str);
		s1 = new(nothrow)char[str.length() + 1];
		if (s1 == NULL) {
			cout << "No Memory" << endl;
			return -1;
		}

		strcpy(s1, str.c_str());
		if (skip(s1) < 0 || trimleft(s1) < 0 || trimright(s1) < 0)
			return -1;

		if (s1[0] == '[' && s1[strlen(s1) - 1] == ']')
			ret.push_back(s1);

		delete[]s1;
	}

	return ret.size();
}

/* ���ȡ���� - ȡĳ��group������item������string�͵�vector�� */
int cfgfile_read_tools::get_all_item(const char* const group_name, vector <string>& ret, const bool ignore_lower_upper_case)	//���Ժ�����ȱʡ���ִ�Сд
{
	cfgin.clear();
	cfgin.seekg(0, ios::beg);
	ret.clear();
	string str1;
	char* s1;
	int cnt = 0;

	while (cfgin.eof() == 0) {

		if (cnt == 1)
			return ret.size();

		getline(cfgin, str1);
		s1 = new (nothrow) char[str1.length() + 1];
		if (s1 == NULL) {
			cout << "No Memory" << endl;
			return -1;
		}

		strcpy(s1, str1.c_str());
		if (skip(s1) < 0 || trimleft(s1) < 0 || trimright(s1) < 0)
			return -1;

		if ((group_name == NULL) || ((ignore_lower_upper_case == false) ? (strcmp(s1, group_name) == 0) : (_stricmp(s1, group_name) == 0))) {
			// ��ȡ��
			string str2;
			char* s2;

			while (cfgin.eof() == 0) {

				getline(cfgin, str2);
				s2 = new (nothrow) char[str2.length() + 1];
				if (s2 == NULL) {
					cout << "No Memory\n";
					return -1;
				}

				strcpy(s2, str2.c_str());
				if (skip(s2) < 0 || trimleft(s2) < 0 || trimright(s2) < 0)
					return -1;

				if (s2[0] == '[' && s2[strlen(s2) - 1] == ']')
					break;

				for (unsigned int i = 0; i < strlen(s2); i++)
					if (s2[i] == '=') {
						ret.push_back(s2);
						break;
					}

				delete[]s2;
			}
			cnt++;
		}

		delete[]s1;

		if (cnt == 1)
			return ret.size();
	}

	return -1;
}

int cfgfile_read_tools::get_all_item(const string& group_name, vector <string>& ret, const bool ignore_lower_upper_case)
{
	cfgin.clear();
	cfgin.seekg(0, ios::beg);
	ret.clear();
	string str1;
	char* s1;
	int cnt = 0;

	while (cfgin.eof() == 0) {

		getline(cfgin, str1);
		s1 = new (nothrow) char[str1.length() + 1];
		if (s1 == NULL) {
			cout << "No Memory" << endl;
			return -1;
		}

		strcpy(s1, str1.c_str());
		if (skip(s1) < 0 || trimleft(s1) < 0 || trimright(s1) < 0)
			return -1;

		if ((ignore_lower_upper_case == false) ? (strcmp(s1, group_name.c_str()) == 0) : (_stricmp(s1, group_name.c_str()) == 0)) {
			// ��ȡ��
			string str2;
			char* s2;

			while (cfgin.eof() == 0) {

				getline(cfgin, str2);
				s2 = new (nothrow) char[str2.length() + 1];
				if (s2 == NULL) {
					cout << "No Memory\n";
					return -1;
				}

				strcpy(s2, str2.c_str());
				if (skip(s2) < 0 || trimleft(s2) < 0 || trimright(s2) < 0)
					return -1;

				if (s2[0] == '[' && s2[strlen(s2) - 1] == ']')
					break;

				for (unsigned int i = 0; i < strlen(s2); i++)
					if (s2[i] == '=') {
						ret.push_back(s2);
						break;
					}

				delete[]s2;
			}

			cnt++;
		}

		delete[]s1;

		if (cnt == 1)
			return ret.size();
	}

	return -1;
}

/* ���ȡ���� - ȡĳ��group������item������string�� */
int cfgfile_read_tools::get_one_item(const char* const group_name, const char* const item_name, string& ret, const bool ignore_lower_upper_case)
{
	cfgin.clear();
	cfgin.seekg(0, ios::beg);
	string str1;
	char* s1;

	while (cfgin.eof() == 0) {

		getline(cfgin, str1);
		s1 = new (nothrow) char[str1.length() + 1];
		if (s1 == NULL) {
			cout << "No Memory" << endl;
			return -1;
		}

		strcpy(s1, str1.c_str());
		if (skip(s1) < 0 || trimleft(s1) < 0 || trimright(s1) < 0)
			return -1;

		if ((group_name == NULL) || ((ignore_lower_upper_case == false) ? (strcmp(s1, group_name) == 0) : (_stricmp(s1, group_name) == 0))) {
			// ��ȡ��
			string str2;
			char* s2;

			while (cfgin.eof() == 0) {

				getline(cfgin, str2);
				s2 = new (nothrow) char[str2.length() + 1];
				if (s2 == NULL) {
					cout << "No Memory\n";
					return -1;
				}

				strcpy(s2, str2.c_str());
				if (skip(s2) < 0 || trimleft(s2) < 0 || trimright(s2) < 0)
					return -1;

				if ((ignore_lower_upper_case == false) ? (strncmp(s2, item_name, strlen(item_name)) == 0) : (_strnicmp(s2, item_name, strlen(item_name)) == 0)) {
					ret = s2;
					return 0;
				}

				if (s2[0] == '[' && s2[strlen(s2) - 1] == ']')
					return -1;

				delete[]s2;
			}
		}
		delete[]s1;
	}

	return -1;
}

int cfgfile_read_tools::get_one_item(const string& group_name, const string& item_name, string& ret, const bool ignore_lower_upper_case)
{
	cfgin.clear();
	cfgin.seekg(0, ios::beg);
	string str1;
	char* s1;

	while (cfgin.eof() == 0) {

		getline(cfgin, str1);
		s1 = new (nothrow) char[str1.length() + 1];
		if (s1 == NULL) {
			cout << "No Memory" << endl;
			return -1;
		}

		strcpy(s1, str1.c_str());
		if (skip(s1) < 0 || trimleft(s1) < 0 || trimright(s1) < 0)
			return -1;

		if (((ignore_lower_upper_case == false) ? (strcmp(s1, group_name.c_str()) == 0) : (_stricmp(s1, group_name.c_str()) == 0))) {
			// ��ȡ��
			string str2;
			char* s2;

			while (cfgin.eof() == 0) {

				getline(cfgin, str2);
				s2 = new (nothrow) char[str2.length() + 1];
				if (s2 == NULL) {
					cout << "No Memory\n";
					return -1;
				}

				strcpy(s2, str2.c_str());
				if (skip(s2) < 0 || trimleft(s2) < 0 || trimright(s2) < 0)
					return -1;

				if ((ignore_lower_upper_case == false) ? (strncmp(s2, item_name.c_str(), strlen(item_name.c_str())) == 0) : (_strnicmp(s2, item_name.c_str(), strlen(item_name.c_str())) == 0)) {
					ret = s2;
					return 0;
				}

				if (s2[0] == '[' && s2[strlen(s2) - 1] == ']')
					return -1;

				delete[]s2;
			}
		}
		delete[]s1;
	}

	return -1;
}

/* ���ȡ���� - ���������Ͷ�ȡĳ��group��ĳ��item�����ڶ�Ӧ�������͵ı�����
	�������Ͱ�����int/double/string/char * /char */
int cfgfile_read_tools::item_get_value(const char* const group_name, const char* const item_name, const char* const def_str, char* str, const int str_maxlen, const bool ignore_lower_upper_case)
{
	cfgin.clear();
	cfgin.seekg(0, ios::beg);
	string str1;
	char* s1;

	while (cfgin.eof() == 0) {

		getline(cfgin, str1);
		s1 = new (nothrow) char[str1.length() + 1];
		if (s1 == NULL) {
			cout << "No Memory" << endl;
			return -1;
		}

		strcpy(s1, str1.c_str());
		if (skip(s1) < 0 || trimleft(s1) < 0 || trimright(s1) < 0)
			return -1;

		if ((group_name == NULL) || ((ignore_lower_upper_case == false) ? (strcmp(s1, group_name) == 0) : (_stricmp(s1, group_name) == 0))) {
			// ��ȡ��
			string str2;
			char* s2;

			while (cfgin.eof() == 0) {

				getline(cfgin, str2);
				s2 = new (nothrow) char[str2.length() + 1];
				if (s2 == NULL) {
					cout << "No Memory\n";
					return -1;
				}

				strcpy(s2, str2.c_str());
				if (skip(s2) < 0 || trimleft(s2) < 0 || trimright(s2) < 0)
					return -1;

				if ((ignore_lower_upper_case == false) ? (strncmp(s2, item_name, strlen(item_name)) == 0) : (_strnicmp(s2, item_name, strlen(item_name)) == 0)) {

					for (unsigned int i = 0; i < strlen(s2); i++)
						if (s2[i] == '=') {
							strcpy(s2, &s2[i + 1]);
							if (skip(s2) < 0 || trimleft(s2) < 0 || trimright(s2) < 0)
								return -1;
							break;
						}

					if (strcmp(s2, "") == 0) {// û�ж���ֵ
						if (strlen(def_str) <= unsigned int(str_maxlen - 1))
							strcpy(str, def_str);
						else {
							strncpy(str, def_str, str_maxlen - 1);
							str[str_maxlen - 1] = '\0';
						}
						return 0;
					}

					stringstream get;
					get << s2; // �����ո�֮ǰ��
					get >> s2;

					if (strlen(s2) <= unsigned int(str_maxlen - 1))
						strcpy(str, s2);
					else
						strncpy(str, s2, str_maxlen - 1);
					return 0;
				}

				if (s2[0] == '[' && s2[strlen(s2) - 1] == ']')
					return -1;

				delete[]s2;
			}
		}
		delete[]s1;
	}

	return -1;
}

int cfgfile_read_tools::item_get_value(const char* const group_name, const char* const item_name, const char* const def_str, string& value, const bool ignore_lower_upper_case)
{
	cfgin.clear();
	cfgin.seekg(0, ios::beg);
	string str1;
	char* s1;

	while (cfgin.eof() == 0) {

		getline(cfgin, str1);
		s1 = new (nothrow) char[str1.length() + 1];
		if (s1 == NULL) {
			cout << "No Memory" << endl;
			return -1;
		}

		strcpy(s1, str1.c_str());
		if (skip(s1) < 0 || trimleft(s1) < 0 || trimright(s1) < 0)
			return -1;

		if ((group_name == NULL) || ((ignore_lower_upper_case == false) ? (strcmp(s1, group_name) == 0) : (_stricmp(s1, group_name) == 0))) {
			// ��ȡ��
			string str2;
			char* s2;

			while (cfgin.eof() == 0) {

				getline(cfgin, str2);
				s2 = new (nothrow) char[str2.length() + 1];
				if (s2 == NULL) {
					cout << "No Memory\n";
					return -1;
				}

				strcpy(s2, str2.c_str());
				if (skip(s2) < 0 || trimleft(s2) < 0 || trimright(s2) < 0)
					return -1;

				if ((ignore_lower_upper_case == false) ? (strncmp(s2, item_name, strlen(item_name)) == 0) : (_strnicmp(s2, item_name, strlen(item_name)) == 0)) {

					for (unsigned int i = 0; i < strlen(s2); i++)
						if (s2[i] == '=') {
							strcpy(s2, &s2[i + 1]);
							if (skip(s2) < 0 || trimleft(s2) < 0 || trimright(s2) < 0)
								return -1;
							break;
						}

					if (strcmp(s2, "") == 0) {// û�ж���ֵ
						value = def_str;
						return 0;
					}

					value = s2;
					return 0;
				}

				if (s2[0] == '[' && s2[strlen(s2) - 1] == ']')
					return -1;

				delete[]s2;
			}
		}
		delete[]s1;
	}

	return -1;

}

int cfgfile_read_tools::item_get_value(const char* const group_name, const char* const item_name, char& ch, const bool ignore_lower_upper_case)
{
	cfgin.clear();
	cfgin.seekg(0, ios::beg);
	string str1;
	char* s1;

	while (cfgin.eof() == 0) {

		getline(cfgin, str1);
		s1 = new (nothrow) char[str1.length() + 1];
		if (s1 == NULL) {
			cout << "No Memory" << endl;
			return -1;
		}

		strcpy(s1, str1.c_str());
		if (skip(s1) < 0 || trimleft(s1) < 0 || trimright(s1) < 0)
			return -1;

		if ((group_name == NULL) || ((ignore_lower_upper_case == false) ? (strcmp(s1, group_name) == 0) : (_stricmp(s1, group_name) == 0))) {
			// ��ȡ��
			string str2;
			char* s2;

			while (cfgin.eof() == 0) {

				getline(cfgin, str2);
				s2 = new (nothrow) char[str2.length() + 1];
				if (s2 == NULL) {
					cout << "No Memory\n";
					return -1;
				}

				strcpy(s2, str2.c_str());
				if (skip(s2) < 0 || trimleft(s2) < 0 || trimright(s2) < 0)
					return -1;

				if ((ignore_lower_upper_case == false) ? (strncmp(s2, item_name, strlen(item_name)) == 0) : (_strnicmp(s2, item_name, strlen(item_name)) == 0)) {

					for (unsigned int i = 0; i < strlen(s2); i++)
						if (s2[i] == '=') {
							strcpy(s2, &s2[i + 1]);
							if (skip(s2) < 0 || trimleft(s2) < 0 || trimright(s2) < 0)
								return -1;
							break;
						}

					if (strcmp(s2, "") == 0) { // û�ж���ֵ
						ch = ' ';
						return 0;
					}

					ch = s2[0];
					return 0;
				}

				if (s2[0] == '[' && s2[strlen(s2) - 1] == ']')
					return -1;

				delete[]s2;
			}
		}
		delete[]s1;
	}

	return -1;
}

int cfgfile_read_tools::item_get_value(const char* const group_name, const char* const item_name, const int min_value, const int max_value, const int def_value, int& value, const bool ignore_lower_upper_case)
{
	cfgin.clear();
	cfgin.seekg(0, ios::beg);
	string str1;
	char* s1;

	while (cfgin.eof() == 0) {

		getline(cfgin, str1);
		s1 = new (nothrow) char[str1.length() + 1];
		if (s1 == NULL) {
			cout << "No Memory" << endl;
			return -1;
		}

		strcpy(s1, str1.c_str());
		if (skip(s1) < 0 || trimleft(s1) < 0 || trimright(s1) < 0)
			return -1;

		if ((group_name == NULL) || ((ignore_lower_upper_case == false) ? (strcmp(s1, group_name) == 0) : (_stricmp(s1, group_name) == 0))) {
			// ��ȡ��
			string str2;
			char* s2;

			while (cfgin.eof() == 0) {

				getline(cfgin, str2);
				s2 = new (nothrow) char[str2.length() + 1];
				if (s2 == NULL) {
					cout << "No Memory\n";
					return -1;
				}

				strcpy(s2, str2.c_str());
				if (skip(s2) < 0 || trimleft(s2) < 0 || trimright(s2) < 0)
					return -1;

				if ((ignore_lower_upper_case == false) ? (strncmp(s2, item_name, strlen(item_name)) == 0) : (_strnicmp(s2, item_name, strlen(item_name)) == 0)) {

					for (unsigned int i = 0; i < strlen(s2); i++)
						if (s2[i] == '=') {
							strcpy(s2, &s2[i + 1]);
							if (skip(s2) < 0 || trimleft(s2) < 0 || trimright(s2) < 0)
								return -1;
							break;
						}

					if (strcmp(s2, "") == 0) { // û�ж���ֵ
						value = def_value;
						return 0;
					}

					value = atoi(s2);

					for (unsigned int i = 0; i < strlen(s2); i++) // ��ʽ����
						if (!(s2[i] >= '0' && s2[i] <= '9' || s2[i] == '.')) {
							value = def_value;
							break;
						}

					if (value < min_value || value > max_value) // ���ڷ�Χ��
						value = def_value;
					return 0;
				}

				if (s2[0] == '[' && s2[strlen(s2) - 1] == ']')
					return -1;

				delete[]s2;
			}
		}
		delete[]s1;
	}

	return -1;
}

int cfgfile_read_tools::item_get_value(const char* const group_name, const char* const item_name, const double min_value, const double max_value, const double def_value, double& value, const bool ignore_lower_upper_case)
{
	cfgin.clear();
	cfgin.seekg(0, ios::beg);
	string str1;
	char* s1;

	while (cfgin.eof() == 0) {

		getline(cfgin, str1);
		s1 = new (nothrow) char[str1.length() + 1];
		if (s1 == NULL) {
			cout << "No Memory" << endl;
			return -1;
		}

		strcpy(s1, str1.c_str());
		if (skip(s1) < 0 || trimleft(s1) < 0 || trimright(s1) < 0)
			return -1;

		if ((group_name == NULL) || ((ignore_lower_upper_case == false) ? (strcmp(s1, group_name) == 0) : (_stricmp(s1, group_name) == 0))) {
			// ��ȡ��
			string str2;
			char* s2;

			while (cfgin.eof() == 0) {

				getline(cfgin, str2);
				s2 = new (nothrow) char[str2.length() + 1];
				if (s2 == NULL) {
					cout << "No Memory\n";
					return -1;
				}

				strcpy(s2, str2.c_str());
				if (skip(s2) < 0 || trimleft(s2) < 0 || trimright(s2) < 0)
					return -1;

				if ((ignore_lower_upper_case == false) ? (strncmp(s2, item_name, strlen(item_name)) == 0) : (_strnicmp(s2, item_name, strlen(item_name)) == 0)) {

					for (unsigned int i = 0; i < strlen(s2); i++)
						if (s2[i] == '=') {
							strcpy(s2, &s2[i + 1]);
							if (skip(s2) < 0 || trimleft(s2) < 0 || trimright(s2) < 0)
								return -1;
							break;
						}

					if (strcmp(s2, "") == 0) { // û�ж���ֵ
						value = def_value;
						return 0;
					}

					value = atof(s2);

					for (unsigned int i = 0; i < strlen(s2); i++)
						if (!(s2[i] >= '0' && s2[i] <= '9' || s2[i] == '.')) {
							value = def_value;
							break;
						}

					if (value < min_value || value > max_value)
						value = def_value;
					return 0;
				}

				if (s2[0] == '[' && s2[strlen(s2) - 1] == ']')
					return -1;

				delete[]s2;
			}
		}
		delete[]s1;
	}

	return -1;
}