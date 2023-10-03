/* 2251206 冯羽芯 计科 */


/* ----------------------------------------------------------------------------------

	 本文件功能：
	1、存放被 hanoi_main.cpp 中根据菜单返回值调用的各菜单项对应的执行函数

	 本文件要求：
	1、不允许定义外部全局变量（const及#define不在限制范围内）
	2、允许定义静态全局变量（具体需要的数量不要超过文档显示，全局变量的使用准则是：少用、慎用、能不用尽量不用）
	3、静态局部变量的数量不限制，但使用准则也是：少用、慎用、能不用尽量不用
	4、按需加入系统头文件、自定义头文件、命名空间等

   ----------------------------------------------------------------------------------- */
#include "../include/cmd_console_tools.h"
#include "./90-01-b1-hanoi.h"
#include <iostream>
#include <iomanip>
#include <conio.h>
#include <Windows.h>
using namespace std;

int v;//延时
int step = 0;//总步数
int topa = 0, topb = 0, topc = 0;//栈顶指针
int A[10] = { 0 }, B[10] = { 0 }, C[10] = { 0 };
const int xa = 12, xb = 44, xc = 76;

/***************************************************************************
  函数名称：
  功    能：根据菜单返回值调用各菜单项对应的执行函数
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void choice(int choose)
{
	if (choose == 0) {
		cct_gotoxy(0, 38);
		return;
	}
	if (choose == 1)
		basic();
	if (choose == 2)
		basic_step_record();
	if (choose == 3)
		innerarray_horizontal();
	if (choose == 4) {
		innerarray_hori_verti();
		cct_setcursor(CURSOR_VISIBLE_NORMAL);
	}
	if (choose == 5) {
		cct_cls();
		column_print_only();
		cct_gotoxy(0, 37);
		cct_setcursor(CURSOR_VISIBLE_NORMAL);
	}

	if (choose == 6) {
		column_plate_print();
		cct_gotoxy(0, 37);
		cct_setcursor(CURSOR_VISIBLE_NORMAL);
	}

	if (choose == 7) {
		first_move();
		cct_gotoxy(0, 37);
		cct_setcursor(CURSOR_VISIBLE_NORMAL);
	}

	if (choose == 8) {
		auto_move();
		cct_gotoxy(0, 37);
		cct_setcursor(CURSOR_VISIBLE_NORMAL);
	}

	if (choose == 9) {
		game();
		cct_gotoxy(0, 37);
		cct_setcursor(CURSOR_VISIBLE_NORMAL);
	}
	cout << endl << "按回车键继续";
	/* 忽略除回车键外的所有输入（注意：_getch的回车是\r，而getchar是\n）*/
	while (_getch() != '\r')
		;

	cct_cls();
	return;
}

/***************************************************************************
	 函数名称：
	 功    能：基本输入层数n 输入起始柱src
	 输入参数：
	 返 回 值：
	 说    明：
   ***************************************************************************/
int basic_input(int* layer, char* bgn, char* mid, char* end, int option)
{
	cout << endl;
	while (1) {
		cout << "请输入汉诺塔的层数(1-10)\n";
		cin >> *layer;
		if (cin.good() && *layer >= 1 && *layer <= MAX_LAYER) {
			cin.clear();
			cin.ignore(65536, '\n');
			break;
		}
		else {
			cin.clear();
			cin.ignore(65536, '\n');
			continue;
		}
	}

	while (1) {
		cout << "请输入起始柱(A-C)\n";
		cin >> *bgn;//不管本次输入多少字符，只取第一个，后面清除
		cin.ignore(65536, '\n');
		if (*bgn >= 'a' && *bgn <= 'c')
			*bgn -= 32;//小写变大写
		if (*bgn >= 'A' && *bgn <= 'C')
			break;
	}

	while (1) {
		cout << "请输入目标柱(A-C)\n";
		cin >> *end;
		cin.ignore(65536, '\n');
		if (*end >= 'a' && *end <= 'c')
			*end -= 32;//小写变大写
		if (*end == *bgn) {
			cout << "目标柱(" << *end << ")不能与起始柱(" << *bgn << ")相同\n";
			continue;
		}
		if (*end >= 'A' && *end <= 'C')
			break;
	}

	*mid = 'A' + 'B' + 'C' - *bgn - *end;

	int velocity;//移动速度
	if (option == 1) {
		while (1) {
			cout << "请输入移动速度(0-5: 0-按回车单步演示 1-延时最长 5-延时最短) ";
			cin >> velocity;
			if (cin.good() && velocity >= 0 && velocity <= 5) {
				cin.clear();
				cin.ignore(65536, '\n');
				break;
			}
			else {
				cin.clear();
				cin.ignore(65536, '\n');
				continue;
			}
		}
		return velocity;
	}
	else
		return -1;

}

/***************************************************************************
  函数名称：
  功    能：初始化数组
  输入参数：
  返 回 值：
***************************************************************************/
void initialize(int layer, char src, char tmp, char dst)
{
	step = 0;
	topa = 0;
	topb = 0;
	topc = 0;
	int i;
	if (src == 'A') {
		topa = layer;
		for (i = 0; i < 10; i++) {
			A[i] = layer;
			layer--;
			if (layer == 0)
				break;
		}
	}
	if (src == 'B') {
		topb = layer;
		for (i = 0; i < 10; i++) {
			B[i] = layer;
			layer--;
			if (layer == 0)
				break;
		}
	}
	if (src == 'C') {
		topc = layer;
		for (i = 0; i < 10; i++) {
			C[i] = layer;
			layer--;
			if (layer == 0)
				break;
		}
	}
}

/***************************************************************************
  函数名称：
  功    能：内部数组变化
  输入参数：
  返 回 值：
***************************************************************************/
void innerarray(char src, char dst)
{
	if (src == 'A') {
		if (dst == 'B')
			B[topb++] = A[--topa];
		else
			C[topc++] = A[--topa];
	}
	if (src == 'B') {
		if (dst == 'A')
			A[topa++] = B[--topb];
		else
			C[topc++] = B[--topb];
	}
	if (src == 'C') {
		if (dst == 'A')
			A[topa++] = C[--topc];
		else
			B[topb++] = C[--topc];
	}
}

/***************************************************************************
  函数名称：
  功    能：移动延时
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void suspension(int v)
{
	if (v == 5)
		Sleep(5);
	if (v == 4)
		Sleep(20);
	if (v == 3)
		Sleep(100);
	if (v == 2)
		Sleep(300);
	if (v == 1)
		Sleep(500);
	if (v == 0) {
		/* 忽略除回车键外的所有输入（注意：_getch的回车是\r，而getchar是\n）*/
		while (_getch() != '\r')
			;
	}
}

/***************************************************************************
	 函数名称：
	 功    能：打印内部数组（横向）
	 输入参数：
	 返 回 值：
	 说    明：
   ***************************************************************************/
void innerarray_hori_print(int n, char src, char dst, int option)
{
	if (option == 4)
		cct_gotoxy(0, 17);

	if (option == 8 || option == 9)
		cct_gotoxy(0, 32);

	if (option != 0)
		cout << "第" << setw(4) << ++step << " 步(" << setw(2) << n << "#: " << src << "-->" << dst << ")  ";

	int i;
	cout << "A:";
	for (i = 0; i < 10; i++) {
		if (i < topa) {
			if (A[i] != 10)
				cout << " ";
			cout << A[i];
		}
		else
			cout << "  ";
	}
	cout << " B:";
	for (i = 0; i < 10; i++) {
		if (i < topb) {
			if (B[i] != 10)
				cout << " ";
			cout << B[i];
		}
		else
			cout << "  ";
	}
	cout << " C:";
	for (i = 0; i < 10; i++) {
		if (i < topc) {
			if (C[i] != 10)
				cout << " ";
			cout << C[i];
		}
		else
			cout << "  ";
	}
}

/***************************************************************************
	 函数名称：
	 功    能：打印内部数组（纵向）
	 输入参数：
	 返 回 值：
	 说    明：
   ***************************************************************************/
void innerarray_verti_print(int n, char src, char dst, int option)
{
	if (option == 4 || option == 8) {
		cct_gotoxy(0, 0);
		cout << "从 " << src << " 移动到 " << dst << "，共 " << n << " 层，延时设置为 " << v;
	}

	int xa = 11, y = 0, xb = 21, xc = 31, i = 0;
	/*
 定义一个基准位置，其余用相对位置来计算
 假设“A”的位置 BASE_X=10
			  BASE_Y=15
	则B的位置 BASE_X+10 BASE_Y
	方便后续移动，不用去数，可维护性好
 */

	if (option == 4 || option == 0) {
		y = 11;
		cct_gotoxy(9, 12);
		cout << "=========================";
		cct_gotoxy(11, 13);
		cout << "A         B         C";
	}

	if (option == 8 || option == 88 || option == 9) {
		y = 26;
		cct_gotoxy(9, 27);
		cout << "=========================";
		cct_gotoxy(11, 28);
		cout << "A         B         C";
	}

	for (i = 0; i < 10; i++) {//“清除作用”
		cct_gotoxy(xa - 1, y - i);
		cout << "  ";
		cct_gotoxy(xb - 1, y - i);
		cout << "  ";
		cct_gotoxy(xc - 1, y - i);
		cout << "  ";
	}

	for (i = 0; i < topa; i++) {
		if (A[i] == 10)
			cct_gotoxy(xa - 1, y - i);
		else
			cct_gotoxy(xa, y - i);
		cout << A[i];
	}
	for (i = 0; i < topb; i++) {
		if (B[i] == 10)
			cct_gotoxy(xb - 1, y - i);
		else
			cct_gotoxy(xb, y - i);
		cout << B[i];
	}
	for (i = 0; i < topc; i++) {
		if (C[i] == 10)
			cct_gotoxy(xc - 1, y - i);
		else
			cct_gotoxy(xc, y - i);
		cout << C[i];
	}

}

/***************************************************************************
	 函数名称：
	 功    能：汉诺塔中的输出选项函数
	 输入参数：
	 返 回 值：
	 说    明：
   ***************************************************************************/
void hanoi_print(int n, char src, char dst, int option)
{
	if (option == 1)
		cout << n << "# " << src << "---->" << dst << endl;

	if (option == 2)
		cout << "第" << setw(4) << ++step << " 步(" << setw(2) << n << "#: " << src << "-->" << dst << ")" << endl;

	if (option == 3) {
		innerarray(src, dst);
		innerarray_hori_print(n, src, dst, 3);
		cout << endl;
	}

	if (option == 4) {
		innerarray(src, dst);
		innerarray_verti_print(n, src, dst, 0);
		innerarray_hori_print(n, src, dst, 4);
		suspension(v);
	}

	if (option == 8) {
		innerarray(src, dst);
		innerarray_verti_print(n, src, dst, 88);
		innerarray_hori_print(n, src, dst, 8);

		move_plate(n, src, dst, v);
		suspension(v);
	}
}

/***************************************************************************
	 函数名称：
	 功    能：汉诺塔递归
	 输入参数：
	 返 回 值：
	 说    明：
   ***************************************************************************/
void hanoi(int n, char src, char tmp, char dst, int option)
{
	if (n == 1)
		hanoi_print(n, src, dst, option);
	if (n >= 2) {//else
		hanoi(n - 1, src, dst, tmp, option);
		hanoi_print(n, src, dst, option);//n表示几号盘
		hanoi(n - 1, tmp, src, dst, option);
	}
}

/***************************************************************************
	 函数名称：
	 功    能：打印盘子
	 输入参数：
	 返 回 值：
	 说    明：
   ***************************************************************************/
void plate_print_only(int n, char src)
{
	int y, x, layer;//n表示层数,这里几层就能表示几号盘
	layer = n;
	if (src == 'A')
		for (y = 14; y > 14 - n; y--) {
			for (x = xa - layer; x <= xa + layer; x++) {
				cct_showch(x, y, ' ', layer, COLOR_WHITE, 1);
			}
			suspension(4);
			layer--;
		}

	if (src == 'B')
		for (y = 14; y > 14 - n; y--) {
			for (x = xb - layer; x <= xb + layer; x++) {
				cct_showch(x, y, ' ', layer, COLOR_WHITE, 1);
			}
			suspension(4);
			layer--;
		}

	if (src == 'C')
		for (y = 14; y > 14 - n; y--) {
			for (x = xc - layer; x <= xc + layer; x++) {
				cct_showch(x, y, ' ', layer, COLOR_WHITE, 1);
			}
			suspension(4);
			layer--;
		}

	cct_setcolor(COLOR_BLACK, COLOR_WHITE);
}

/***************************************************************************
	 函数名称：
	 功    能：平移
	 输入参数：
	 返 回 值：
	 说    明：
   ***************************************************************************/
void move_plate(int n, char src, char dst, int v)//n表示几号盘，一定是最上面那个盘
{
	suspension(2);
	const int y_bottom = 15;
	int y;
	if (src == 'A') {
		/* 将一串字符从下向上移动 */
		for (y = y_bottom - topa - 1; y >= 1; y--) {
			cct_showstr(xa - n, y, " ", n, COLOR_WHITE, 2 * n + 1);

			if (v != 0)
				suspension(v);
			else
				suspension(3);

			if (y >= 2) {
				/* 清除显示(最后一次保留)，清除方法为用正常颜色+空格重画一遍刚才的位置 */
				cct_showch(xa - n, y, ' ', COLOR_BLACK, COLOR_WHITE, 2 * n + 1);
				if (y != 2)
					cct_showch(xa, y, ' ', COLOR_HYELLOW, COLOR_WHITE, 1);
			}
		} //end of for
	}
	if (src == 'B') {
		/* 将一串字符从下向上移动 */
		for (y = y_bottom - topb - 1; y >= 1; y--) {
			cct_showstr(xb - n, y, " ", n, COLOR_WHITE, 2 * n + 1);

			if (v != 0)
				suspension(v);
			else
				suspension(3);

			if (y >= 2) {
				/* 清除显示(最后一次保留)，清除方法为用正常颜色+空格重画一遍刚才的位置 */
				cct_showch(xb - n, y, ' ', COLOR_BLACK, COLOR_WHITE, 2 * n + 1);
				if (y != 2)
					cct_showch(xb, y, ' ', COLOR_HYELLOW, COLOR_WHITE, 1);
			}
		} //end of for
	}
	if (src == 'C') {
		/* 将一串字符从下向上移动 */
		for (y = y_bottom - topc - 1; y >= 1; y--) {
			cct_showstr(xc - n, y, " ", n, COLOR_WHITE, 2 * n + 1);

			if (v != 0)
				suspension(v);
			else
				suspension(3);

			if (y >= 2) {
				/* 清除显示(最后一次保留)，清除方法为用正常颜色+空格重画一遍刚才的位置 */
				cct_showch(xc - n, y, ' ', COLOR_BLACK, COLOR_WHITE, 2 * n + 1);
				if (y != 2)
					cct_showch(xc, y, ' ', COLOR_HYELLOW, COLOR_WHITE, 1);
			}
		} //end of for
	}
	cct_setcolor(COLOR_BLACK, COLOR_WHITE);

	int x;
	if (src == 'A')
		if (dst == 'B') {
			/* 将一串字符从下向上移动 */
			for (x = xa - n; x <= xb - n; x++) {
				cct_showstr(x, 1, " ", n, COLOR_WHITE, 2 * n + 1);

				if (v != 0)
					suspension(v);
				else
					suspension(3);

				if (x <= xb - n - 1)
					/* 清除显示(最后一次保留)，清除方法为用正常颜色+空格重画一遍刚才的位置 */
					cct_showch(x, 1, ' ', COLOR_BLACK, COLOR_WHITE, 2 * n + 1);

			} //end of for
		}
		else {
			/* 将一串字符从下向上移动 */
			for (x = xa - n; x <= xc - n; x++) {
				cct_showstr(x, 1, " ", n, COLOR_WHITE, 2 * n + 1);

				if (v != 0)
					suspension(v);
				else
					suspension(3);

				if (x <= xc - n - 1)
					/* 清除显示(最后一次保留)，清除方法为用正常颜色+空格重画一遍刚才的位置 */
					cct_showch(x, 1, ' ', COLOR_BLACK, COLOR_WHITE, 2 * n + 1);

			} //end of for
		}
	if (src == 'B')
		if (dst == 'A') {
			/* 将一串字符从下向上移动 */
			for (x = xb - n; x >= xa - n; x--) {
				cct_showstr(x, 1, " ", n, COLOR_WHITE, 2 * n + 1);

				if (v != 0)
					suspension(v);
				else
					suspension(3);

				if (x >= xa - n + 1)
					/* 清除显示(最后一次保留)，清除方法为用正常颜色+空格重画一遍刚才的位置 */
					cct_showch(x, 1, ' ', COLOR_BLACK, COLOR_WHITE, 2 * n + 1);

			} //end of for
		}
		else {
			/* 将一串字符从下向上移动 */
			for (x = xb - n; x <= xc - n; x++) {
				cct_showstr(x, 1, " ", n, COLOR_WHITE, 2 * n + 1);

				if (v != 0)
					suspension(v);
				else
					suspension(3);

				if (x <= xc - n - 1)
					/* 清除显示(最后一次保留)，清除方法为用正常颜色+空格重画一遍刚才的位置 */
					cct_showch(x, 1, ' ', COLOR_BLACK, COLOR_WHITE, 2 * n + 1);

			} //end of for
		}
	if (src == 'C')
		if (dst == 'A') {
			/* 将一串字符从下向上移动 */
			for (x = xc - n; x >= xa - n; x--) {
				cct_showstr(x, 1, " ", n, COLOR_WHITE, 2 * n + 1);

				if (v != 0)
					suspension(v);
				else
					suspension(3);

				if (x >= xa - n + 1)
					/* 清除显示(最后一次保留)，清除方法为用正常颜色+空格重画一遍刚才的位置 */
					cct_showch(x, 1, ' ', COLOR_BLACK, COLOR_WHITE, 2 * n + 1);

			} //end of for
		}
		else {
			/* 将一串字符从下向上移动 */
			for (x = xc - n; x >= xb - n; x--) {
				cct_showstr(x, 1, " ", n, COLOR_WHITE, 2 * n + 1);

				if (v != 0)
					suspension(v);
				else
					suspension(3);

				if (x >= xb - n + 1)
					/* 清除显示(最后一次保留)，清除方法为用正常颜色+空格重画一遍刚才的位置 */
					cct_showch(x, 1, ' ', COLOR_BLACK, COLOR_WHITE, 2 * n + 1);

			} //end of for
		}
	cct_setcolor(COLOR_BLACK, COLOR_WHITE);

	if (dst == 'A') {
		/* 将一串字符从上向下移动 */
		for (y = 1; y <= y_bottom - topa; y++) {
			cct_showstr(xa - n, y, " ", n, COLOR_WHITE, 2 * n + 1);

			if (v != 0)
				suspension(v);
			else
				suspension(3);

			if (y <= y_bottom - topa - 1) {
				/* 清除显示(最后一次保留)，清除方法为用正常颜色+空格重画一遍刚才的位置 */
				cct_showch(xa - n, y, ' ', COLOR_BLACK, COLOR_WHITE, 2 * n + 1);
				if (y >= 3)
					cct_showch(xa, y, ' ', COLOR_HYELLOW, COLOR_WHITE, 1);
			}
		} //end of for
	}
	if (dst == 'B') {
		/* 将一串字符从上向下移动 */
		for (y = 1; y <= y_bottom - topb; y++) {
			cct_showstr(xb - n, y, " ", n, COLOR_WHITE, 2 * n + 1);

			if (v != 0)
				suspension(v);
			else
				suspension(3);

			if (y <= y_bottom - topb - 1) {
				/* 清除显示(最后一次保留)，清除方法为用正常颜色+空格重画一遍刚才的位置 */
				cct_showch(xb - n, y, ' ', COLOR_BLACK, COLOR_WHITE, 2 * n + 1);
				if (y >= 3)
					cct_showch(xb, y, ' ', COLOR_HYELLOW, COLOR_WHITE, 1);
			}
		} //end of for
	}
	if (dst == 'C') {
		/* 将一串字符从上向下移动 */
		for (y = 1; y <= y_bottom - topc; y++) {
			cct_showstr(xc - n, y, " ", n, COLOR_WHITE, 2 * n + 1);

			if (v != 0)
				suspension(v);
			else
				suspension(3);

			if (y <= y_bottom - topc - 1) {
				/* 清除显示(最后一次保留)，清除方法为用正常颜色+空格重画一遍刚才的位置 */
				cct_showch(xc - n, y, ' ', COLOR_BLACK, COLOR_WHITE, 2 * n + 1);
				if (y >= 3)
					cct_showch(xc, y, ' ', COLOR_HYELLOW, COLOR_WHITE, 1);
			}
		} //end of for
	}
	cct_setcolor(COLOR_BLACK, COLOR_WHITE);
}

/***************************************************************************
	 函数名称：
	 功    能：判断输入是否合法
	 输入参数：
	 返 回 值：
	 说    明：
   ***************************************************************************/
int judge(char src, char dst)
{
	if (src == 'A') {
		if (topa == 0) {
			cout << "\n源柱为空!";
			suspension(1);
			cct_showstr(0, 35, " ", COLOR_BLACK, COLOR_WHITE, 30);
			cct_showstr(60, 34, " ", COLOR_BLACK, COLOR_WHITE, 20);
			cct_gotoxy(60, 34);
			return 0;
		}
		else {
			if (dst == 'B') {
				if (A[topa - 1] > B[topb - 1] && topb != 0) {
					cout << "\n大盘压小盘，非法移动!";
					suspension(1);
					cct_showstr(0, 35, " ", COLOR_BLACK, COLOR_WHITE, 30);
					cct_showstr(60, 34, " ", COLOR_BLACK, COLOR_WHITE, 20);
					cct_gotoxy(60, 34);
					return 0;
				}
				else {
					cct_setcursor(CURSOR_INVISIBLE);
					return 1;
				}
			}
			else {
				if (A[topa - 1] > C[topc - 1] && topc != 0) {
					cout << "\n大盘压小盘，非法移动!";
					suspension(1);
					cct_showstr(0, 35, " ", COLOR_BLACK, COLOR_WHITE, 30);
					cct_showstr(60, 34, " ", COLOR_BLACK, COLOR_WHITE, 20);
					cct_gotoxy(60, 34);
					return 0;
				}
				else {
					cct_setcursor(CURSOR_INVISIBLE);
					return 1;
				}
			}
		}
	}

	if (src == 'B') {
		if (topb == 0) {
			cout << "\n源柱为空!";
			suspension(1);
			cct_showstr(0, 35, " ", COLOR_BLACK, COLOR_WHITE, 30);
			cct_showstr(60, 34, " ", COLOR_BLACK, COLOR_WHITE, 20);
			cct_gotoxy(60, 34);
			return 0;
		}
		else {
			if (dst == 'A') {
				if (B[topb - 1] > A[topa - 1] && topa != 0) {
					cout << "\n大盘压小盘，非法移动!";
					suspension(1);
					cct_showstr(0, 35, " ", COLOR_BLACK, COLOR_WHITE, 30);
					cct_showstr(60, 34, " ", COLOR_BLACK, COLOR_WHITE, 20);
					cct_gotoxy(60, 34);
					return 0;
				}
				else {
					cct_setcursor(CURSOR_INVISIBLE);
					return 1;
				}
			}
			else {
				if (B[topb - 1] > C[topc - 1] && topc != 0) {
					cout << "\n大盘压小盘，非法移动!";
					suspension(1);
					cct_showstr(0, 35, " ", COLOR_BLACK, COLOR_WHITE, 30);
					cct_showstr(60, 34, " ", COLOR_BLACK, COLOR_WHITE, 20);
					cct_gotoxy(60, 34);
					return 0;
				}
				else {
					cct_setcursor(CURSOR_INVISIBLE);
					return 1;
				}
			}
		}
	}

	if (src == 'C') {
		if (topc == 0) {
			cout << "\n源柱为空!";
			suspension(1);
			cct_showstr(0, 35, " ", COLOR_BLACK, COLOR_WHITE, 30);
			cct_showstr(60, 34, " ", COLOR_BLACK, COLOR_WHITE, 20);
			cct_gotoxy(60, 34);
			return 0;
		}
		else {
			if (dst == 'A') {
				if (C[topc - 1] > A[topa - 1] && topa != 0) {
					cout << "\n大盘压小盘，非法移动!";
					suspension(1);
					cct_showstr(0, 35, " ", COLOR_BLACK, COLOR_WHITE, 30);
					cct_showstr(60, 34, " ", COLOR_BLACK, COLOR_WHITE, 20);
					cct_gotoxy(60, 34);
					return 0;
				}
				else {
					cct_setcursor(CURSOR_INVISIBLE);
					return 1;
				}
			}
			else {
				if (C[topc - 1] > B[topb - 1] && topb != 0) {
					cout << "\n大盘压小盘，非法移动!";
					suspension(1);
					cct_showstr(0, 35, " ", COLOR_BLACK, COLOR_WHITE, 30);
					cct_showstr(60, 34, " ", COLOR_BLACK, COLOR_WHITE, 20);
					cct_gotoxy(60, 34);
					return 0;
				}
				else {
					cct_setcursor(CURSOR_INVISIBLE);
					return 1;
				}
			}
		}
	}
	return 0;//消除warning
}

/***************************************************************************
	 函数名称：
	 功    能：基本解
	 输入参数：
	 返 回 值：
	 说    明：
   ***************************************************************************/
void basic(void)//1
{
	cout << endl << endl;
	int n;
	char src, tmp, dst;
	basic_input(&n, &src, &tmp, &dst, 0);

	step = 0;
	hanoi(n, src, tmp, dst, 1);
}

/***************************************************************************
	 函数名称：
	 功    能：基本解(步数)
	 输入参数：
	 返 回 值：
	 说    明：
   ***************************************************************************/
void basic_step_record(void)
{
	cout << endl << endl;
	int n;
	char src, tmp, dst;
	basic_input(&n, &src, &tmp, &dst, 0);

	step = 0;
	hanoi(n, src, tmp, dst, 2);
}

/***************************************************************************
	 函数名称：
	 功    能：内部数组(横向)
	 输入参数：
	 返 回 值：
	 说    明：
   ***************************************************************************/
void innerarray_horizontal(void)
{
	cout << endl << endl;
	int n;
	char src, tmp, dst;
	basic_input(&n, &src, &tmp, &dst, 0);
	initialize(n, src, tmp, dst);

	hanoi(n, src, tmp, dst, 3);
}

/***************************************************************************
	 函数名称：
	 功    能：内部数组(横向+纵向)
	 输入参数：
	 返 回 值：
	 说    明：
   ***************************************************************************/
void innerarray_hori_verti(void)
{
	cout << endl << endl;
	int n;
	char src, tmp, dst;
	v = basic_input(&n, &src, &tmp, &dst, 1);
	initialize(n, src, tmp, dst);

	cct_setcursor(CURSOR_INVISIBLE);
	cct_cls();
	innerarray_verti_print(n, src, dst, 4);
	cct_gotoxy(0, 17);
	cout << "初始:  ";
	innerarray_hori_print(n, src, dst, 0);
	suspension(v);

	hanoi(n, src, tmp, dst, 4);
	cct_gotoxy(0, 37);
}

/***************************************************************************
	 函数名称：
	 功    能：打印柱子
	 输入参数：
	 返 回 值：
	 说    明：
   ***************************************************************************/
void column_print_only(void)
{
	cct_setcursor(CURSOR_INVISIBLE);
	cct_showch(1, 15, ' ', COLOR_HYELLOW, COLOR_WHITE, 23);
	cct_setcolor(COLOR_BLACK, COLOR_WHITE);
	cout << "         ";
	cct_showch(33, 15, ' ', COLOR_HYELLOW, COLOR_WHITE, 23);
	cct_setcolor(COLOR_BLACK, COLOR_WHITE);
	cout << "         ";
	cct_showch(65, 15, ' ', COLOR_HYELLOW, COLOR_WHITE, 23);
	cct_setcolor(COLOR_BLACK, COLOR_WHITE);

	int y;
	for (y = 14; y >= 3; y--) {
		cct_showch(xa, y, ' ', COLOR_HYELLOW, COLOR_WHITE, 1);
		suspension(4);
		cct_showch(xb, y, ' ', COLOR_HYELLOW, COLOR_WHITE, 1);
		suspension(4);
		cct_showch(xc, y, ' ', COLOR_HYELLOW, COLOR_WHITE, 1);
		suspension(4);
	}
	cct_setcolor(COLOR_BLACK, COLOR_WHITE);
}

/***************************************************************************
	 函数名称：
	 功    能：打印盘子和柱子
	 输入参数：
	 返 回 值：
	 说    明：
   ***************************************************************************/
void column_plate_print(void)
{
	cout << endl << endl;
	int n;
	char src, tmp, dst;
	basic_input(&n, &src, &tmp, &dst, 0);

	cct_setcursor(CURSOR_INVISIBLE);
	cct_cls();

	cout << "从 " << src << " 移动到 " << dst << "，共 " << n << " 层";
	column_print_only();
	plate_print_only(n, src);
}

/***************************************************************************
	 函数名称：
	 功    能：打印盘子和柱子加第一步移动
	 输入参数：
	 返 回 值：
	 说    明：
   ***************************************************************************/
void first_move(void)
{
	cout << endl << endl;
	int n;
	char src, tmp, dst;
	basic_input(&n, &src, &tmp, &dst, 0);

	initialize(n, src, tmp, dst);
	cct_setcursor(CURSOR_INVISIBLE);
	cct_cls();

	cout << "从 " << src << " 移动到 " << dst << "，共 " << n << " 层";
	column_print_only();
	plate_print_only(n, src);

	if (n % 2 != 0) {
		innerarray(src, dst);
		move_plate(1, src, dst, 2);
	}
	else {
		innerarray(src, tmp);
		move_plate(1, src, tmp, 2);
	}
}

/***************************************************************************
	 函数名称：
	 功    能：自动移动
	 输入参数：
	 返 回 值：
	 说    明：
   ***************************************************************************/
void auto_move(void)
{
	cout << endl << endl;
	int n;
	char src, tmp, dst;
	v = basic_input(&n, &src, &tmp, &dst, 1);
	initialize(n, src, tmp, dst);

	cct_setcursor(CURSOR_INVISIBLE);
	cct_cls();
	innerarray_verti_print(n, src, dst, 8);
	cct_gotoxy(0, 32);
	cout << "初始:  ";
	innerarray_hori_print(n, src, dst, 0);
	column_print_only();
	plate_print_only(n, src);
	suspension(v);

	hanoi(n, src, tmp, dst, 8);
}

/***************************************************************************
	 函数名称：
	 功    能：游戏版本
	 输入参数：
	 返 回 值：
	 说    明：
   ***************************************************************************/
//用cct读键盘的处理会更快一些
void game(void)
{
	cout << endl << endl;
	int n, n0;//n0是n的备份
	char src, tmp, dst, src0, dst0;//备份
	basic_input(&n, &src, &tmp, &dst, 0);
	n0 = n;
	src0 = src;
	dst0 = dst;

	initialize(n, src, tmp, dst);
	cct_setcursor(CURSOR_INVISIBLE);
	cct_cls();

	cout << "从 " << src << " 移动到 " << dst << "，共 " << n << " 层";
	innerarray_verti_print(n, src, dst, 9);
	cct_gotoxy(0, 32);
	cout << "初始:  ";
	innerarray_hori_print(n, src, dst, 0);
	column_print_only();
	plate_print_only(n, src);

	cct_gotoxy(0, 34);
	cct_setcursor(CURSOR_VISIBLE_NORMAL);
	cout << "请输入移动的柱号(命令形式：AC=A顶端的盘子移动到C，Q=退出) ：";
	char move[20] = { 0 };
	int i, j, k;
	while (1) {
		cct_setcursor(CURSOR_VISIBLE_NORMAL);
		for (i = 0; i < 20; i++) {

			move[i] = _getch();

			if (move[i] == -32) {//char!!不是unsigned char！！
				k = _getch();//读特殊键 del 上下左右等等
			}

			if (move[i] == '\r') {
				//if (move == "AB\r" || move == "AC\r" || move == "BA\r" || move == "BC\r" || move == "CA\r" || move == "CB\r") {没学好！！这玩意是地址
				if ((move[0] == 'A' || move[0] == 'B' || move[0] == 'C') && (move[1] == 'A' || move[1] == 'B' || move[1] == 'C') && move[2] == '\r' && move[0] != move[1]) {
					src = move[0];
					dst = move[1];
					if (judge(src, dst) == 0) {
						for (j = 0; j < 20; j++)
							move[i] = 0;
						i = -1;
						cct_showstr(60, 34, " ", COLOR_BLACK, COLOR_WHITE, 20);
						cct_gotoxy(60, 34);
						continue;
					}
					else {//写对了
						for (j = 0; j < 20; j++)
							move[j] = 0;
						break;
					}
				}
				else {
					if (move[0] == 'Q' && move[1] == '\r') {
						cout << "\n游戏中止!!!!!";
						return;
					}

					for (j = 0; j < 20; j++)
						move[j] = 0;
					i = -1;
					cct_showstr(60, 34, " ", COLOR_BLACK, COLOR_WHITE, 20);
					cct_gotoxy(60, 34);
					continue;
				}
			}
			if ((move[i] >= 33 && move[i] <= 126)) {
				cout << move[i];
				if (move[i] >= 'a' && move[i] <= 'z')
					move[i] -= 32;//小写转大写
			}
			else {
				move[i] = 0;
				i--;
			}
			if (move[19] != '\0') {//读满20个重新读
				for (j = 0; j < 20; j++)
					move[j] = 0;
				i = -1;
				cct_showstr(60, 34, " ", COLOR_BLACK, COLOR_WHITE, 20);
				cct_gotoxy(60, 34);
				continue;
			}
		}

		innerarray(src, dst);
		if (src == 'A')
			n = A[topa];
		if (src == 'B')
			n = B[topb];
		if (src == 'C')
			n = C[topc];
		innerarray_verti_print(n, src, dst, 9);
		innerarray_hori_print(n, src, dst, 9);//几号盘

		move_plate(n, src, dst, 4);

		if (src0 == 'A')
			if (dst0 == 'B') {
				if (topa == 0 && topb == n0) {
					cct_gotoxy(60, 34);
					cout << "\n游戏结束!!!!!";
					return;
				}
			}
			else
				if (topa == 0 && topc == n0) {
					cct_gotoxy(60, 34);
					cout << "\n游戏结束!!!!!";
					return;
				}
		if (src0 == 'B')
			if (dst0 == 'A') {
				if (topb == 0 && topa == n0) {
					cct_gotoxy(60, 34);
					cout << "\n游戏结束!!!!!";
					return;
				}
			}
			else
				if (topb == 0 && topc == n0) {
					cct_gotoxy(60, 34);
					cout << "\n游戏结束!!!!!";
					return;
				}
		if (src0 == 'C')
			if (dst0 == 'A') {
				if (topc == 0 && topa == n0) {
					cct_gotoxy(60, 34);
					cout << "\n游戏结束!!!!!";
					return;
				}
			}
			else
				if (topc == 0 && topb == n0) {
					cct_gotoxy(60, 34);
					cout << "\n游戏结束!!!!!";
					return;
				}

		cct_showstr(60, 34, " ", COLOR_BLACK, COLOR_WHITE, 20);
		cct_gotoxy(60, 34);
	}
}
