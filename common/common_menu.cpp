/* 2251206 冯羽芯 计科 */

/* ----------------------------------------------------------------------------------

	 本文件功能：
	1、放被 hanoi_main.cpp 调用的菜单函数，要求显示各菜单项，读入正确的选项后返回

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
int menu(int i)
{
	if (i == 1) {
		cct_cls();
		cout << "---------------------------------" << endl;
		cout << "1.基本解" << endl;
		cout << "2.基本解(步数记录)" << endl;
		cout << "3.内部数组显示(横向)" << endl;
		cout << "4.内部数组显示(纵向+横向)" << endl;
		cout << "5.图形解-预备-画三个圆柱" << endl;
		cout << "6.图形解-预备-在起始柱上画n个盘子" << endl;
		cout << "7.图形解-预备-第一次移动" << endl;
		cout << "8.图形解-自动移动版本" << endl;
		cout << "9.图形解-游戏版" << endl;
		cout << "0.退出" << endl;
		cout << "---------------------------------" << endl;
		cout << "[请选择:] ";

		char choice;
		while (1) {
			choice = _getche();
			if (choice == '0')
				return 0;
			else if (choice == '1')
				return 1;
			else if (choice == '2')
				return 2;
			else if (choice == '3')
				return 3;
			else if (choice == '4')
				return 4;
			else if (choice == '5')
				return 5;
			else if (choice == '6')
				return 6;
			else if (choice == '7')
				return 7;
			else if (choice == '8')
				return 8;
			else if (choice == '9')
				return 9;
			else {
				cct_gotoxy(10, 12);
				cout << ' ';
				cct_gotoxy(10, 12);
				continue;
			}
		}
	}
	if (i == 2) {
		cct_cls();
		cct_setcolor(); /* 恢复为初始颜色 */
		cct_setcursor(CURSOR_VISIBLE_NORMAL);//打开光标

		cout << "--------------------------------------------" << endl;
		cout << "A.命令行找出可消除项并标识" << endl;
		cout << "B.命令行完成一次消除（分步骤显示）" << endl;
		cout << "C.命令行完成一关（分步骤显示）" << endl;
		cout << "D.伪图形界面下用鼠标选择一个色块（无分隔线）" << endl;
		cout << "E.伪图形界面下用鼠标选择一个色块（有分隔线）" << endl;
		cout << "F.伪图形界面完成一次消除（分步骤）" << endl;
		cout << "G.伪图形界面完整版" << endl;
		cout << "Q.退出" << endl;
		cout << "--------------------------------------------" << endl;
		cout << "[请选择:] ";

		char choice;
		while (1) {
			choice = _getche();
			Sleep(200);
			if (choice == 'q' || choice == 'Q')
				return 0;
			else if (choice == 'a' || choice == 'A')
				return 1;
			else if (choice == 'b' || choice == 'B')
				return 2;
			else if (choice == 'c' || choice == 'C')
				return 3;
			else if (choice == 'd' || choice == 'D')
				return 4;
			else if (choice == 'e' || choice == 'E')
				return 5;
			else if (choice == 'f' || choice == 'F')
				return 6;
			else if (choice == 'g' || choice == 'G')
				return 7;
			else {
				cct_gotoxy(10, 10);
				cout << ' ';
				cct_gotoxy(10, 10);
				continue;
			}
		}
	}
	if (i == 3) {
		cct_cls();
		cct_setcolor(); /* 恢复为初始颜色 */
		cct_setcursor(CURSOR_VISIBLE_NORMAL);//打开光标

		cout << "--------------------------------------------" << endl;
		cout << "1.命令行完成一个数字的旋转" << endl;
		cout << "2.伪图形界面下完成一个数字的下落(可加速)" << endl;
		cout << "3.伪图形界面下完成一个数字的下落和旋转" << endl;
		cout << "4.伪图形界面下完成一个数字的所有功能" << endl;
		cout << "5.伪图形界面下实现一次消除" << endl;
		cout << "6.伪图形界面下完整游戏" << endl;
		cout << "0.退出" << endl;
		cout << "--------------------------------------------" << endl;
		cout << "[请选择:] ";

		char choice;
		while (1) {
			choice = _getche();
			if (choice == '0')
				return 0;
			else if (choice == '1')
				return 1;
			else if (choice == '2')
				return 2;
			else if (choice == '3')
				return 3;
			else if (choice == '4')
				return 4;
			else if (choice == '5')
				return 5;
			else if (choice == '6')
				return 6;
			else {
				cct_gotoxy(10, 9);
				cout << ' ';
				cct_gotoxy(10, 9);
				continue;
			}
		}
	}
	return -1;
}