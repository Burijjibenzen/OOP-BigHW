/* 2251206 冯羽芯 计科 */

//该cpp用于存放伪图形界面需要用到的函数的具体实现 
#include <iostream>
#include "90-02-b1.h"
#include "../include/cmd_console_tools.h"
#include <time.h>
#include <Windows.h>
using namespace std;

/*画格子*/
void frame(int& h, int& w)
{
	int i, j;
	cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
	cout << "╔";
	for (j = 1; j <= w; j++)
		cout << "═══";
	cout << "╗";
	cct_setcolor();
	cout << endl;

	for (i = 1; i <= h; i++) {
		cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
		cout << "║";
		for (j = 1; j <= w; j++)
			cout << "      ";
		cout << "║";
		cct_setcolor();
		cout << endl;

		cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
		cout << "║";
		for (j = 1; j <= w; j++)
			cout << "      ";
		cout << "║";
		cct_setcolor();
		cout << endl;

		cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
		cout << "║";
		for (j = 1; j <= w; j++)
			cout << "      ";
		cout << "║";
		cct_setcolor();
		cout << endl;
	}

	cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
	cout << "╚";
	for (j = 1; j <= w; j++)
		cout << "═══";
	cout << "╝";
	cct_setcolor();
	cout << endl;
}

/*提示信息*/
void tips(int& next_num, int score, int line, int& w)
{
	cct_gotoxy(w * 6 + 10, 3);
	cct_setcolor();
	cout << "下一个数字是：" << next_num;
	cct_gotoxy(w * 6 + 10, 4);
	cout << "当前得分：" << score;
	cct_gotoxy(w * 6 + 10, 5);
	cout << "消除总行数：" << line;
}