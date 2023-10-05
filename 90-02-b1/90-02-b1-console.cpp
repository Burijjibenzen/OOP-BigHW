/* 2251206 冯羽芯 计科 */

//该cpp用于存放伪图形界面需要用到的函数的具体实现 
#include <iostream>
#include "90-02-b1.h"
#include "../include/cmd_console_tools.h"
#include <time.h>
#include <Windows.h>
#include <conio.h>
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
	cct_gotoxy(w * 6 + 10, 6);
	cout << "按esc键退出";
}

/*打印星星*/
void star(int x_star, int y_star, int current_num)
{
	if (current_num == 0)
		cct_setcolor(COLOR_BLUE, COLOR_BLACK);
	if (current_num == 1)
		cct_setcolor(COLOR_GREEN, COLOR_BLACK);
	if (current_num == 2)
		cct_setcolor(COLOR_CYAN, COLOR_BLACK);
	if (current_num == 3)
		cct_setcolor(COLOR_RED, COLOR_BLACK);
	if (current_num == 4)
		cct_setcolor(COLOR_PINK, COLOR_BLACK);
	if (current_num == 5)
		cct_setcolor(COLOR_YELLOW, COLOR_BLACK);
	if (current_num == 6)
		cct_setcolor(COLOR_HYELLOW, COLOR_BLACK);
	if (current_num == 7)
		cct_setcolor(COLOR_HRED, COLOR_BLACK);
	if (current_num == 8)
		cct_setcolor(COLOR_HBLUE, COLOR_BLACK);
	if (current_num == 9)
		cct_setcolor(COLOR_HGREEN, COLOR_BLACK);
	cct_gotoxy(x_star, y_star);
	cout << "╔═╗";
	cct_gotoxy(x_star, y_star + 1);
	cout << "║★║";
	cct_gotoxy(x_star, y_star + 2);
	cout << "╚═╝";
	cct_setcolor();
}

/*恢复原状*/
void clear(int x_star, int y_star)
{
	cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
	cct_gotoxy(x_star, y_star);
	cout << "      ";
	cct_gotoxy(x_star, y_star + 1);
	cout << "      ";
	cct_gotoxy(x_star, y_star + 2);
	cout << "      ";
	cct_setcolor();
}

/*下落的函数*/
void fall(char(*p)[23], int current_num, int cntr_x, int cntr_y, int& judge)
{
	//下落的本质
	// 能否下落的判断 以中心坐标为中心的5*5方格，从头开始遍历，如果有当前为对应数字且下方为0，则停止下落，否则继续
	//以中心坐标为中心，从最后一排开始向上循环，如果有当前为对应数字，则置*，下方*变成当前数字
	cntr_y += 5; //方便人看，纵坐标一直加5怪烦的
	int i, j; //mark是否下落
	for (i = cntr_y - 2; i <= cntr_y + 2; i++)
		for (j = cntr_x - 2; j <= cntr_x + 2; j++)
			if (p[i][j] == current_num + 48 && p[i + 1][j] == '#')
				judge = 1;
	if (judge == 1) {
		//当前内容变成0
		for (i = cntr_y - 2; i <= cntr_y + 2; i++)
			for (j = cntr_x - 2; j <= cntr_x + 2; j++)
				if (p[i][j] == current_num + 48)
					p[i][j] = '#';
		return; //停止下落
	}
	else {
		//下落
		for (i = cntr_y + 2; i >= cntr_y - 2; i--)
			for (j = cntr_x - 2; j <= cntr_x + 2; j++)
				if (p[i][j] == current_num + 48 && p[i + 1][j] == '*') {
					//ij处变成白的
					if (i > 5)
						clear(6 * j - 4, 3 * i - 17);
					p[i][j] = '*';
					//i+1j处变成星星
					if (i + 1 > 5)
						star(6 * j - 4, 3 * (i + 1) - 17, current_num);
					p[i + 1][j] = current_num + 48;
				}
	}
}

/*左移*/
void left(char(*p)[23], int current_num, int& cntr_x, int cntr_y)
{
	//平移的本质
	// 能否左移的判断 判断cntr_x
	//如果可以，以中心坐标为中心，从左向右循环，如果有当前为对应数字，则置*，左方*变成当前数字
	cntr_y += 5; //方便人看，纵坐标一直加5怪烦的
	int i, j, judge = 0; //mark是否下落
	if ((current_num == 1 && cntr_x <= 1) || cntr_x <= 2)
		return; //原始形状触碰原始边界
	for (j = cntr_x - 2; j <= cntr_x + 2; j++)
		for (i = cntr_y - 2; i <= cntr_y + 2; i++)
			if (p[i][j] == current_num + 48 && p[i][j - 1] == '#') {
				judge = 1;
				return;
			}
	if (judge != 1) {
		for (j = cntr_x - 2; j <= cntr_x + 2; j++)
			for (i = cntr_y + 2; i >= cntr_y - 2; i--)
				if (p[i][j] == current_num + 48 && p[i][j - 1] == '*') {
					//ij处变成白的
					if (i > 5)
						clear(6 * j - 4, 3 * i - 17);
					p[i][j] = '*';
					//ij-1处变成星星
					if (i > 5)
						star(6 * (j - 1) - 4, 3 * i - 17, current_num);
					p[i][j - 1] = current_num + 48;
				}
		cntr_x--;
	}
}

/*右移*/
void right(char(*p)[23], int current_num, int& cntr_x, int cntr_y, int w)
{
	cntr_y += 5; //方便人看，纵坐标一直加5怪烦的
	int i, j, judge = 0; //mark是否下落
	if ((current_num == 1 && cntr_x >= w) || cntr_x >= w - 1)
		return; //原始形状触碰原始边界
	for (j = cntr_x + 2; j >= cntr_x - 2; j--)
		for (i = cntr_y - 2; i <= cntr_y + 2; i++)
			if (p[i][j] == current_num + 48 && p[i][j + 1] == '#') {
				judge = 1;
				return;
			}
	if (judge != 1) {
		for (j = cntr_x + 2; j >= cntr_x - 2; j--)
			for (i = cntr_y + 2; i >= cntr_y - 2; i--)
				if (p[i][j] == current_num + 48 && p[i][j + 1] == '*') {
					//ij处变成白的
					if (i > 5)
						clear(6 * j - 4, 3 * i - 17);
					p[i][j] = '*';
					//ij-1处变成星星
					if (i > 5)
						star(6 * (j + 1) - 4, 3 * i - 17, current_num);
					p[i][j + 1] = current_num + 48;
				}
		cntr_x++;
	}
}

/*上下左右*/
void opr(char(*p)[23], int current_num, int& h, int& w, int cntr_x, int cntr_y, int score, int mode)
{
	int ret;
	int keycode1, keycode2;
	int loop = 1;
	int sum = 0; //对于每一个数字的旋转 给予一个标号

	unsigned int interval;
	DWORD t1, t2;
	while (1) {
		t1 = GetTickCount();
		while (1) {
			if (score < 120) //下落的时间间隔
				interval = (int)((1 - score % 15 * 0.1) * 1000);
			else
				interval = 300;

			loop = 1;
			while (loop) {
				ret = _kbhit();
				if (ret == 1) {
					keycode1 = _getch();
					switch (keycode1) {
						case 224:
							keycode2 = _getch();
							switch (keycode2) {
								case KB_ARROW_DOWN:
									interval = interval / 4;
									break;
								case KB_ARROW_UP:
									if (mode != 2)
										rotate(p, h, w, cntr_x, cntr_y, current_num, sum, mode);
									break;
								case KB_ARROW_LEFT:
									if (mode != 2 && mode != 3)
										left(p, current_num, cntr_x, cntr_y);
									break;
								case KB_ARROW_RIGHT:
									if (mode != 2 && mode != 3)
										right(p, current_num, cntr_x, cntr_y, w);
									break;
								default:
									break;
							}
							break;
						case 27:	//ESC键
							return;
							break;
						default:
							break;
					}
				}
				else
					loop = 0;
			}
			t2 = GetTickCount();
			if (mode == 2 && cntr_y == h - 2)
				return;
			if ((t2 - t1) >= interval) {
				int judge = 0;
				fall(p, current_num, cntr_x, cntr_y, judge);
				if (judge == 1)//无法继续
					return;
				else {
					cntr_y++;
					break;
				}
			}
		}
	}
}
