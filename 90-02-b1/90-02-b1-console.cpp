/* 2251206 ����о �ƿ� */

//��cpp���ڴ��αͼ�ν�����Ҫ�õ��ĺ����ľ���ʵ�� 
#include <iostream>
#include "90-02-b1.h"
#include "../include/cmd_console_tools.h"
#include <time.h>
#include <Windows.h>
using namespace std;

/*������*/
void frame(int& h, int& w)
{
	int i, j;
	cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
	cout << "�X";
	for (j = 1; j <= w; j++)
		cout << "�T�T�T";
	cout << "�[";
	cct_setcolor();
	cout << endl;

	for (i = 1; i <= h; i++) {
		cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
		cout << "�U";
		for (j = 1; j <= w; j++)
			cout << "      ";
		cout << "�U";
		cct_setcolor();
		cout << endl;

		cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
		cout << "�U";
		for (j = 1; j <= w; j++)
			cout << "      ";
		cout << "�U";
		cct_setcolor();
		cout << endl;

		cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
		cout << "�U";
		for (j = 1; j <= w; j++)
			cout << "      ";
		cout << "�U";
		cct_setcolor();
		cout << endl;
	}

	cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
	cout << "�^";
	for (j = 1; j <= w; j++)
		cout << "�T�T�T";
	cout << "�a";
	cct_setcolor();
	cout << endl;
}

/*��ʾ��Ϣ*/
void tips(int& next_num, int score, int line, int& w)
{
	cct_gotoxy(w * 6 + 10, 3);
	cct_setcolor();
	cout << "��һ�������ǣ�" << next_num;
	cct_gotoxy(w * 6 + 10, 4);
	cout << "��ǰ�÷֣�" << score;
	cct_gotoxy(w * 6 + 10, 5);
	cout << "������������" << line;
}