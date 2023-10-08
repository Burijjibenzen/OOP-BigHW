/* 2251206 冯羽芯 计科 */

/* ----------------------------------------------------------------------------------

	 本文件要求：
	1、不允许定义外部全局变量（const及#define不在限制范围内）
	2、不允许定义静态全局变量（全局变量的使用准则是：少用、慎用、能不用尽量不用）
	3、静态局部变量的数量不限制，但使用准则也是：少用、慎用、能不用尽量不用
	4、按需加入系统头文件、自定义头文件、命名空间等

   ----------------------------------------------------------------------------------- */
#include "../include/cmd_console_tools.h"
#include "../90-01-b1/90-01-b1-hanoi.h"
#include <iostream>
#include <iomanip>
#include <conio.h>
#include <Windows.h>
using namespace std;

/***************************************************************************
  函数名称：
  功    能：菜单函数，显示各菜单项，读入正确的选项后返回
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int Menu(const char* p[], const char* chc, int size, int prj)
{
	//第一个参数是指针数组，用来存提示的字符串
	//第二个参数是一个指针，指向存序号的字符串，类似"12345670"
	cct_cls();
	cct_setcolor(); /* 恢复为初始颜色 */
	cct_setcursor(CURSOR_VISIBLE_NORMAL);//打开光标
	int cmd_y = -1;
	char choice;
	const char* str;
	cout << "--------------------------------------------" << endl;
	for (int i = 0; i < size; i++) {
		cout << *(chc + i) << '.';
		cout << p[i] << endl;
	}
	cout << "--------------------------------------------" << endl;
	cout << "[请选择:] ";

	if (prj == 1)
		cmd_y = 12;
	if (prj == 2)
		cmd_y = 10;
	if (prj == 3)
		cmd_y = 9;

	while (1) {
		choice = _getche();
		str = strchr(chc, choice);
		if (str == NULL) {
			cct_gotoxy(10, cmd_y);
			cout << ' ';
			cct_gotoxy(10, cmd_y);
		}
		else
			return str - chc + 1;
	}
	return -1;
}


/*输入行列*/
void input(int* row, int* col, int mode)//row h;col w
{
	if (mode == 2) {
		while (1) {
			cout << "请输入行数(8-10)：\n";
			cin >> *row;
			if (cin.good() == 0) {
				cin.clear();
				cin.ignore(65536, '\n');
			}
			else if (*row > 10 || *row < 8)
				continue;
			else break;
		}
		while (1) {
			cout << "请输入列数(8-10)：\n";
			cin >> *col;
			if (cin.good() == 0) {
				cin.clear();
				cin.ignore(65536, '\n');
			}
			else if (*col > 10 || *col < 8)
				continue;
			else break;
		}
		cout << endl;
		cin.ignore(65536, '\n');
	}
	if (mode == 3) {
		while (1) {
			cout << "请输入高度(18-26)：\n";
			cin >> *row;
			if (cin.good() == 0) {
				cin.clear();
				cin.ignore(65536, '\n');
			}
			else if (*row > 26 || *row < 18)
				continue;
			else break;
		}
		while (1) {
			cout << "请输入宽度(12-21,且为3的倍数)：\n";
			cin >> *col;
			if (cin.good() == 0) {
				cin.clear();
				cin.ignore(65536, '\n');
			}
			else if (*col > 21 || *col < 12 || *col % 3 != 0)
				continue;
			else break;
		}
		cout << endl;
		cin.ignore(65536, '\n');
	}
}

/*打印星星*/
void star(int x_star, int y_star, int current_num = -1)
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
}