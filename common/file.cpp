/* 2251206 冯羽芯 计科 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>

using namespace std;

int trimleft(char* s)
{
	if (!s)
		return -1;
	char* p = s;
	while (*p && ((' ' == *p) || ('\t' == *p) || ('\n' == *p) || ('\r' == *p)))
		p++;

	if (*p)
		strcpy(s, p);

	return 0;
}

int trimright(char* s)
{
	if (!s)
		return -1;
	char* p = s + strlen(s) - 1;

	while (*p && (p - s) && ((' ' == *p) || ('\t' == *p) || ('\n' == *p) || ('\r' == *p)))
		p--;

	*(p + 1) = 0;
	if ((' ' == *p) || ('\t' == *p) || ('\n' == *p) || ('\r' == *p))
		*p = 0;

	return 0;
}

void filetohex(const char* s, bool eof)
{
	if (eof == true) {
		cout << "<EOF>" << endl;
		return;
	}
	if (strcmp(s, "") == 0) {
		cout << "<EMPTY>" << endl;
		return;
	}
	char str[16] = { 0 };
	//先获取文件大小，移动文件指针
	int size = strlen(s);

	unsigned char ch;
	for (int i = 1; i <= size; i++) {
		if ((i - 1) % 16 == 0) {
			cout << setw(8) << setfill('0') << hex << i - 1 << " " << ':' << " ";
			cout << setfill(' ');
		}

		ch = s[i - 1];
		if (ch >= 32 && ch <= 126)
			str[(i - 1) % 16] = ch;
		else
			str[(i - 1) % 16] = '.';

		cout << hex << setw(2) << setfill('0') << int(ch) << ' ';
		cout << setfill(' ');

		cout << dec;
		if (i % 8 == 0 && i % 16 != 0 && i != size)
			cout << char('-') << ' ';

		if (i % 16 == 0) {
			cout << ' ';
			for (int j = 0; j < 16; j++)
				cout << str[j];
			cout << endl;
		}
	}

	//对于剩余字符的处理 输出右侧的字符形式
	int left = size % 16;
	if (left != 0) {
		if (left <= 8) {
			for (int i = 1; i <= 8 - left; i++)
				cout << "   ";
			cout << "  ";
			for (int i = 1; i <= 8; i++)
				cout << "   ";
			cout << " ";
		}
		else {
			for (int i = 1; i <= 16 - left; i++)
				cout << "   ";
			cout << " ";
		}
		for (int i = 0; i < left; i++)
			cout << str[i];
		cout << endl;
	}
}

