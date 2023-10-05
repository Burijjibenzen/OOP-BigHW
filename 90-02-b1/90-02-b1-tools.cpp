/* 2251206 冯羽芯 计科 */

//该cpp用于存放内部数组操作需要用到的函数的具体实现
#include <iostream>
#include "90-02-b1.h"
#include "../include/cmd_console_tools.h"
#include <time.h>
#include <Windows.h>
#include <conio.h>
using namespace std;

/*输入行列*/
void input(int* h, int* w)
{
	while (1) {
		cout << "请输入高度(18-26)：\n";
		cin >> *h;
		if (cin.good() == 0) {
			cin.clear();
			cin.ignore(65536, '\n');
		}
		else if (*h > 26 || *h < 18)
			continue;
		else break;
	}
	while (1) {
		cout << "请输入宽度(12-21,且为3的倍数)：\n";
		cin >> *w;
		if (cin.good() == 0) {
			cin.clear();
			cin.ignore(65536, '\n');
		}
		else if (*w > 21 || *w < 12 || *w % 3 != 0)
			continue;
		else break;
	}
	cout << endl;
	cin.ignore(65536, '\n');
}

/*生成内部数组*/
void generate_array(char(*p)[23], int& h, int& w)
{
	int i, j;
	for (i = 0; i < 33; i++)
		for (j = 0; j < 23; j++)
			p[i][j] = '#'; //边界全为#，方便碰撞检测
	for (i = 1; i < h + 5 + 1; i++)
		for (j = 1; j < w + 1; j++)
			p[i][j] = '*'; //初始化为*
}

/*打印当前数组*/
void current_array(char(*p)[23], int& h, int& w)
{
	cout << "当前数组：\n";
	cout << "  |";
	int i, j;
	for (i = 1; i <= w; i++)
		cout << "  " << (char)('A' + i - 1);
	cout << endl;
	cout << "--+-";
	for (i = 0; i < w; i++)
		cout << "---";
	cout << endl;
	for (i = 1; i <= h; i++) {
		cout << (char)('A' + i - 1) << " |";
		for (j = 1; j <= w; j++) {
			cout << "  ";
			if (p[i + 5][j] != '*')
				cct_setcolor(COLOR_HYELLOW, COLOR_BLACK);
			cout << p[i + 5][j];
			cct_setcolor();
		}
		cout << endl;
	}
	cout << endl;
}

/*生成随机数*/
int get_next_num(const bool new_seed = false, const unsigned int seed = 0)
{
	if (new_seed)
		srand(seed);

	return rand() % 10;
}

/*生成命令行下数字初始位置/初始化下落数字*/
void generate_num(char(*p)[23], int& h, int& w, int& cntr_x, int& cntr_y, int& current_num, int mode)
{
	if (mode == 1) {
		srand((unsigned int)time(0));
		if (current_num == 1) {
			cntr_x = rand() % w + 1;
			cntr_y = rand() % (h - 2) - 1;
		}
		else {
			cntr_x = rand() % (w - 2) + 2;
			cntr_y = rand() % (h - 2) - 1;
		}
	}
	else {
		if (w % 2 == 0) {
			cntr_x = w / 2;
			cntr_y = 3 - 5;
		}
		else {
			cntr_x = (w + 1) / 2;
			cntr_y = 3 - 5;
		}
	}
	switch (current_num) {
		case 1:
			p[cntr_y + 5][cntr_x] = '1';
			p[cntr_y + 4][cntr_x] = '1';
			p[cntr_y + 3][cntr_x] = '1';
			p[cntr_y + 6][cntr_x] = '1';
			p[cntr_y + 7][cntr_x] = '1';
			break;
		case 2:
			p[cntr_y + 5][cntr_x] = '2';
			p[cntr_y + 5][cntr_x + 1] = '2';
			p[cntr_y + 5][cntr_x - 1] = '2';
			p[cntr_y + 4][cntr_x + 1] = '2';
			p[cntr_y + 3][cntr_x] = '2';
			p[cntr_y + 3][cntr_x + 1] = '2';
			p[cntr_y + 3][cntr_x - 1] = '2';
			p[cntr_y + 6][cntr_x - 1] = '2';
			p[cntr_y + 7][cntr_x] = '2';
			p[cntr_y + 7][cntr_x + 1] = '2';
			p[cntr_y + 7][cntr_x - 1] = '2';
			break;
		case 3:
			p[cntr_y + 5][cntr_x] = '3';
			p[cntr_y + 5][cntr_x + 1] = '3';
			p[cntr_y + 5][cntr_x - 1] = '3';
			p[cntr_y + 4][cntr_x + 1] = '3';
			p[cntr_y + 3][cntr_x] = '3';
			p[cntr_y + 3][cntr_x + 1] = '3';
			p[cntr_y + 3][cntr_x - 1] = '3';
			p[cntr_y + 6][cntr_x + 1] = '3';
			p[cntr_y + 7][cntr_x] = '3';
			p[cntr_y + 7][cntr_x + 1] = '3';
			p[cntr_y + 7][cntr_x - 1] = '3';
			break;
		case 4:
			p[cntr_y + 5][cntr_x] = '4';
			p[cntr_y + 5][cntr_x + 1] = '4';
			p[cntr_y + 5][cntr_x - 1] = '4';
			p[cntr_y + 4][cntr_x + 1] = '4';
			p[cntr_y + 4][cntr_x - 1] = '4';
			p[cntr_y + 3][cntr_x + 1] = '4';
			p[cntr_y + 3][cntr_x - 1] = '4';
			p[cntr_y + 6][cntr_x + 1] = '4';
			p[cntr_y + 7][cntr_x + 1] = '4';
			break;
		case 5:
			p[cntr_y + 5][cntr_x] = '5';
			p[cntr_y + 5][cntr_x + 1] = '5';
			p[cntr_y + 5][cntr_x - 1] = '5';
			p[cntr_y + 4][cntr_x - 1] = '5';
			p[cntr_y + 3][cntr_x] = '5';
			p[cntr_y + 3][cntr_x + 1] = '5';
			p[cntr_y + 3][cntr_x - 1] = '5';
			p[cntr_y + 6][cntr_x + 1] = '5';
			p[cntr_y + 7][cntr_x] = '5';
			p[cntr_y + 7][cntr_x + 1] = '5';
			p[cntr_y + 7][cntr_x - 1] = '5';
			break;
		case 6:
			p[cntr_y + 5][cntr_x] = '6';
			p[cntr_y + 5][cntr_x + 1] = '6';
			p[cntr_y + 5][cntr_x - 1] = '6';
			p[cntr_y + 4][cntr_x - 1] = '6';
			p[cntr_y + 3][cntr_x] = '6';
			p[cntr_y + 3][cntr_x + 1] = '6';
			p[cntr_y + 3][cntr_x - 1] = '6';
			p[cntr_y + 6][cntr_x + 1] = '6';
			p[cntr_y + 6][cntr_x - 1] = '6';
			p[cntr_y + 7][cntr_x] = '6';
			p[cntr_y + 7][cntr_x + 1] = '6';
			p[cntr_y + 7][cntr_x - 1] = '6';
			break;
		case 7:
			p[cntr_y + 5][cntr_x + 1] = '7';
			p[cntr_y + 4][cntr_x + 1] = '7';
			p[cntr_y + 3][cntr_x] = '7';
			p[cntr_y + 3][cntr_x + 1] = '7';
			p[cntr_y + 3][cntr_x - 1] = '7';
			p[cntr_y + 6][cntr_x + 1] = '7';
			p[cntr_y + 7][cntr_x + 1] = '7';
			break;
		case 8:
			p[cntr_y + 5][cntr_x] = '8';
			p[cntr_y + 5][cntr_x + 1] = '8';
			p[cntr_y + 5][cntr_x - 1] = '8';
			p[cntr_y + 4][cntr_x - 1] = '8';
			p[cntr_y + 4][cntr_x + 1] = '8';
			p[cntr_y + 3][cntr_x] = '8';
			p[cntr_y + 3][cntr_x + 1] = '8';
			p[cntr_y + 3][cntr_x - 1] = '8';
			p[cntr_y + 6][cntr_x + 1] = '8';
			p[cntr_y + 6][cntr_x - 1] = '8';
			p[cntr_y + 7][cntr_x] = '8';
			p[cntr_y + 7][cntr_x + 1] = '8';
			p[cntr_y + 7][cntr_x - 1] = '8';
			break;
		case 9:
			p[cntr_y + 5][cntr_x] = '9';
			p[cntr_y + 5][cntr_x + 1] = '9';
			p[cntr_y + 5][cntr_x - 1] = '9';
			p[cntr_y + 4][cntr_x - 1] = '9';
			p[cntr_y + 4][cntr_x + 1] = '9';
			p[cntr_y + 3][cntr_x] = '9';
			p[cntr_y + 3][cntr_x + 1] = '9';
			p[cntr_y + 3][cntr_x - 1] = '9';
			p[cntr_y + 6][cntr_x + 1] = '9';
			p[cntr_y + 7][cntr_x] = '9';
			p[cntr_y + 7][cntr_x + 1] = '9';
			p[cntr_y + 7][cntr_x - 1] = '9';
			break;
		case 0:
			p[cntr_y + 5][cntr_x + 1] = '0';
			p[cntr_y + 5][cntr_x - 1] = '0';
			p[cntr_y + 4][cntr_x - 1] = '0';
			p[cntr_y + 4][cntr_x + 1] = '0';
			p[cntr_y + 3][cntr_x] = '0';
			p[cntr_y + 3][cntr_x + 1] = '0';
			p[cntr_y + 3][cntr_x - 1] = '0';
			p[cntr_y + 6][cntr_x + 1] = '0';
			p[cntr_y + 6][cntr_x - 1] = '0';
			p[cntr_y + 7][cntr_x] = '0';
			p[cntr_y + 7][cntr_x + 1] = '0';
			p[cntr_y + 7][cntr_x - 1] = '0';
			break;
		default:
			break;
	}

}

/*本小题结束*/
void end(void)
{
	while (1) {
		cct_setcolor();
		cout << "本小题结束，请输入End继续";
		char ending[4] = { 0 };
		cin.get(ending, 4, '\n');
		cin.clear();
		cin.ignore(65536, '\n');
		int i;
		for (i = 0; i < 4; i++)
			if (ending[i] >= 'a' && ending[i] <= 'z')
				ending[i] -= 32;
		if (strcmp(ending, "END") == 0)
			return;
		else {
			cout << "输入错误，请重新输入";
			cout << "\n";
			continue;
		}
	}
}

/*旋转*/
void rotate1(char(*p)[23], int& h, int& w, int& cntr_x, int& cntr_y, int current_num, int& sum, int mode)
{
	int ret;
	int keycode1, keycode2;
	int loop = 1;
	if (mode == 1)
		cout << "请按↑键进行旋转，按esc键退出测试\n";

	while (loop) {
		ret = _kbhit();
		if (ret == 1) {
			keycode1 = _getch();
			switch (keycode1) {
				case 224:
					keycode2 = _getch();
					switch (keycode2) {
						case KB_ARROW_UP:
							//先判断是否可以旋转
							rotate(p, h, w, cntr_x, cntr_y, current_num, sum, mode);
							break;
						default:
							continue;
							break;
					}
					if (mode == 1) {
						cout << "旋转后的数字为：";
						current_array(p, h, w);
					}
					break;
				case 27:	//ESC键
					return;
					break;
				default:
					break;
			}
		}
	}

}

void rotate(char(*p)[23], int& h, int& w, int& cntr_x, int& cntr_y, int current_num, int& sum, int mode)
{
	if (cntr_x <= 2 || cntr_x >= w - 1 || cntr_y >= h - 1) {
		if (mode == 1)
			cout << "无法旋转";
		return;
	}
	else {
		sum++;
		if (sum % 4 == 0) {
			// 还需归零
			cmd_rotate_clear(p, cntr_x, cntr_y, current_num, mode);
			switch (current_num) {
				case 1:
					p[cntr_y + 5][cntr_x] = '1';
					p[cntr_y + 4][cntr_x] = '1';
					p[cntr_y + 3][cntr_x] = '1';
					p[cntr_y + 6][cntr_x] = '1';
					p[cntr_y + 7][cntr_x] = '1';
					break;
				case 2:
					p[cntr_y + 5][cntr_x] = '2';
					p[cntr_y + 5][cntr_x + 1] = '2';
					p[cntr_y + 5][cntr_x - 1] = '2';
					p[cntr_y + 4][cntr_x + 1] = '2';
					p[cntr_y + 3][cntr_x] = '2';
					p[cntr_y + 3][cntr_x + 1] = '2';
					p[cntr_y + 3][cntr_x - 1] = '2';
					p[cntr_y + 6][cntr_x - 1] = '2';
					p[cntr_y + 7][cntr_x] = '2';
					p[cntr_y + 7][cntr_x + 1] = '2';
					p[cntr_y + 7][cntr_x - 1] = '2';
					break;
				case 3:
					p[cntr_y + 5][cntr_x] = '3';
					p[cntr_y + 5][cntr_x + 1] = '3';
					p[cntr_y + 5][cntr_x - 1] = '3';
					p[cntr_y + 4][cntr_x + 1] = '3';
					p[cntr_y + 3][cntr_x] = '3';
					p[cntr_y + 3][cntr_x + 1] = '3';
					p[cntr_y + 3][cntr_x - 1] = '3';
					p[cntr_y + 6][cntr_x + 1] = '3';
					p[cntr_y + 7][cntr_x] = '3';
					p[cntr_y + 7][cntr_x + 1] = '3';
					p[cntr_y + 7][cntr_x - 1] = '3';
					break;
				case 4:
					p[cntr_y + 5][cntr_x] = '4';
					p[cntr_y + 5][cntr_x + 1] = '4';
					p[cntr_y + 5][cntr_x - 1] = '4';
					p[cntr_y + 4][cntr_x + 1] = '4';
					p[cntr_y + 4][cntr_x - 1] = '4';
					p[cntr_y + 3][cntr_x + 1] = '4';
					p[cntr_y + 3][cntr_x - 1] = '4';
					p[cntr_y + 6][cntr_x + 1] = '4';
					p[cntr_y + 7][cntr_x + 1] = '4';
					break;
				case 5:
					p[cntr_y + 5][cntr_x] = '5';
					p[cntr_y + 5][cntr_x + 1] = '5';
					p[cntr_y + 5][cntr_x - 1] = '5';
					p[cntr_y + 4][cntr_x - 1] = '5';
					p[cntr_y + 3][cntr_x] = '5';
					p[cntr_y + 3][cntr_x + 1] = '5';
					p[cntr_y + 3][cntr_x - 1] = '5';
					p[cntr_y + 6][cntr_x + 1] = '5';
					p[cntr_y + 7][cntr_x] = '5';
					p[cntr_y + 7][cntr_x + 1] = '5';
					p[cntr_y + 7][cntr_x - 1] = '5';
					break;
				case 6:
					p[cntr_y + 5][cntr_x] = '6';
					p[cntr_y + 5][cntr_x + 1] = '6';
					p[cntr_y + 5][cntr_x - 1] = '6';
					p[cntr_y + 4][cntr_x - 1] = '6';
					p[cntr_y + 3][cntr_x] = '6';
					p[cntr_y + 3][cntr_x + 1] = '6';
					p[cntr_y + 3][cntr_x - 1] = '6';
					p[cntr_y + 6][cntr_x + 1] = '6';
					p[cntr_y + 6][cntr_x - 1] = '6';
					p[cntr_y + 7][cntr_x] = '6';
					p[cntr_y + 7][cntr_x + 1] = '6';
					p[cntr_y + 7][cntr_x - 1] = '6';
					break;
				case 7:
					p[cntr_y + 5][cntr_x + 1] = '7';
					p[cntr_y + 4][cntr_x + 1] = '7';
					p[cntr_y + 3][cntr_x] = '7';
					p[cntr_y + 3][cntr_x + 1] = '7';
					p[cntr_y + 3][cntr_x - 1] = '7';
					p[cntr_y + 6][cntr_x + 1] = '7';
					p[cntr_y + 7][cntr_x + 1] = '7';
					break;
				case 8:
					p[cntr_y + 5][cntr_x] = '8';
					p[cntr_y + 5][cntr_x + 1] = '8';
					p[cntr_y + 5][cntr_x - 1] = '8';
					p[cntr_y + 4][cntr_x - 1] = '8';
					p[cntr_y + 4][cntr_x + 1] = '8';
					p[cntr_y + 3][cntr_x] = '8';
					p[cntr_y + 3][cntr_x + 1] = '8';
					p[cntr_y + 3][cntr_x - 1] = '8';
					p[cntr_y + 6][cntr_x + 1] = '8';
					p[cntr_y + 6][cntr_x - 1] = '8';
					p[cntr_y + 7][cntr_x] = '8';
					p[cntr_y + 7][cntr_x + 1] = '8';
					p[cntr_y + 7][cntr_x - 1] = '8';
					break;
				case 9:
					p[cntr_y + 5][cntr_x] = '9';
					p[cntr_y + 5][cntr_x + 1] = '9';
					p[cntr_y + 5][cntr_x - 1] = '9';
					p[cntr_y + 4][cntr_x - 1] = '9';
					p[cntr_y + 4][cntr_x + 1] = '9';
					p[cntr_y + 3][cntr_x] = '9';
					p[cntr_y + 3][cntr_x + 1] = '9';
					p[cntr_y + 3][cntr_x - 1] = '9';
					p[cntr_y + 6][cntr_x + 1] = '9';
					p[cntr_y + 7][cntr_x] = '9';
					p[cntr_y + 7][cntr_x + 1] = '9';
					p[cntr_y + 7][cntr_x - 1] = '9';
					break;
				case 0:
					p[cntr_y + 5][cntr_x + 1] = '0';
					p[cntr_y + 5][cntr_x - 1] = '0';
					p[cntr_y + 4][cntr_x - 1] = '0';
					p[cntr_y + 4][cntr_x + 1] = '0';
					p[cntr_y + 3][cntr_x] = '0';
					p[cntr_y + 3][cntr_x + 1] = '0';
					p[cntr_y + 3][cntr_x - 1] = '0';
					p[cntr_y + 6][cntr_x + 1] = '0';
					p[cntr_y + 6][cntr_x - 1] = '0';
					p[cntr_y + 7][cntr_x] = '0';
					p[cntr_y + 7][cntr_x + 1] = '0';
					p[cntr_y + 7][cntr_x - 1] = '0';
					break;
				default:
					break;
			}
			cmd_rotate_draw(p, cntr_x, cntr_y, current_num, mode);
		}
		if (sum % 4 == 1) {
			cmd_rotate_clear(p, cntr_x, cntr_y, current_num, mode);
			switch (current_num) {
				case 1:
					p[cntr_y + 5][cntr_x] = '1';
					p[cntr_y + 5][cntr_x - 1] = '1';
					p[cntr_y + 5][cntr_x - 2] = '1';
					p[cntr_y + 5][cntr_x + 1] = '1';
					p[cntr_y + 5][cntr_x + 2] = '1';
					break;
				case 2:
					p[cntr_y + 5][cntr_x] = '2';
					p[cntr_y + 5][cntr_x + 2] = '2';
					p[cntr_y + 5][cntr_x - 2] = '2';
					p[cntr_y + 4][cntr_x - 1] = '2';
					p[cntr_y + 4][cntr_x - 2] = '2';
					p[cntr_y + 4][cntr_x + 2] = '2';
					p[cntr_y + 4][cntr_x] = '2';
					p[cntr_y + 6][cntr_x] = '2';
					p[cntr_y + 6][cntr_x - 2] = '2';
					p[cntr_y + 6][cntr_x + 1] = '2';
					p[cntr_y + 6][cntr_x + 2] = '2';
					break;
				case 3:
					p[cntr_y + 5][cntr_x] = '3';
					p[cntr_y + 5][cntr_x + 2] = '3';
					p[cntr_y + 5][cntr_x - 2] = '3';
					p[cntr_y + 4][cntr_x - 1] = '3';
					p[cntr_y + 4][cntr_x - 2] = '3';
					p[cntr_y + 4][cntr_x + 2] = '3';
					p[cntr_y + 4][cntr_x + 1] = '3';
					p[cntr_y + 4][cntr_x] = '3';
					p[cntr_y + 6][cntr_x - 2] = '3';
					p[cntr_y + 6][cntr_x] = '3';
					p[cntr_y + 6][cntr_x + 2] = '3';
					break;
				case 4:
					p[cntr_y + 5][cntr_x] = '4';
					p[cntr_y + 4][cntr_x + 1] = '4';
					p[cntr_y + 4][cntr_x - 1] = '4';
					p[cntr_y + 4][cntr_x] = '4';
					p[cntr_y + 4][cntr_x - 2] = '4';
					p[cntr_y + 4][cntr_x + 2] = '4';
					p[cntr_y + 6][cntr_x - 1] = '4';
					p[cntr_y + 6][cntr_x] = '4';
					p[cntr_y + 6][cntr_x - 2] = '4';
					break;
				case 5:
					p[cntr_y + 5][cntr_x] = '5';
					p[cntr_y + 5][cntr_x + 2] = '5';
					p[cntr_y + 5][cntr_x - 2] = '5';
					p[cntr_y + 4][cntr_x - 2] = '5';
					p[cntr_y + 4][cntr_x] = '5';
					p[cntr_y + 4][cntr_x + 2] = '5';
					p[cntr_y + 4][cntr_x + 1] = '5';
					p[cntr_y + 6][cntr_x + 2] = '5';
					p[cntr_y + 6][cntr_x] = '5';
					p[cntr_y + 6][cntr_x - 1] = '5';
					p[cntr_y + 6][cntr_x - 2] = '5';
					break;
				case 6:
					p[cntr_y + 5][cntr_x] = '6';
					p[cntr_y + 5][cntr_x + 2] = '6';
					p[cntr_y + 5][cntr_x - 2] = '6';
					p[cntr_y + 4][cntr_x - 2] = '6';
					p[cntr_y + 4][cntr_x] = '6';
					p[cntr_y + 4][cntr_x + 2] = '6';
					p[cntr_y + 4][cntr_x + 1] = '6';
					p[cntr_y + 6][cntr_x + 1] = '6';
					p[cntr_y + 6][cntr_x - 1] = '6';
					p[cntr_y + 6][cntr_x] = '6';
					p[cntr_y + 6][cntr_x + 2] = '6';
					p[cntr_y + 6][cntr_x - 2] = '6';
					break;
				case 7:
					p[cntr_y + 5][cntr_x - 2] = '7';
					p[cntr_y + 6][cntr_x - 2] = '7';
					p[cntr_y + 4][cntr_x] = '7';
					p[cntr_y + 4][cntr_x + 2] = '7';
					p[cntr_y + 4][cntr_x - 2] = '7';
					p[cntr_y + 4][cntr_x + 1] = '7';
					p[cntr_y + 4][cntr_x - 1] = '7';
					break;
				case 8:
					p[cntr_y + 5][cntr_x] = '8';
					p[cntr_y + 5][cntr_x + 2] = '8';
					p[cntr_y + 5][cntr_x - 2] = '8';
					p[cntr_y + 4][cntr_x - 2] = '8';
					p[cntr_y + 4][cntr_x + 2] = '8';
					p[cntr_y + 4][cntr_x] = '8';
					p[cntr_y + 4][cntr_x + 1] = '8';
					p[cntr_y + 4][cntr_x - 1] = '8';
					p[cntr_y + 6][cntr_x + 2] = '8';
					p[cntr_y + 6][cntr_x - 2] = '8';
					p[cntr_y + 6][cntr_x] = '8';
					p[cntr_y + 6][cntr_x + 1] = '8';
					p[cntr_y + 6][cntr_x - 1] = '8';
					break;
				case 9:
					p[cntr_y + 5][cntr_x] = '9';
					p[cntr_y + 5][cntr_x + 2] = '9';
					p[cntr_y + 5][cntr_x - 2] = '9';
					p[cntr_y + 4][cntr_x - 2] = '9';
					p[cntr_y + 4][cntr_x + 2] = '9';
					p[cntr_y + 4][cntr_x] = '9';
					p[cntr_y + 4][cntr_x + 1] = '9';
					p[cntr_y + 4][cntr_x - 1] = '9';
					p[cntr_y + 6][cntr_x - 2] = '9';
					p[cntr_y + 6][cntr_x] = '9';
					p[cntr_y + 6][cntr_x + 2] = '9';
					p[cntr_y + 6][cntr_x - 1] = '9';
					break;
				case 0:
					p[cntr_y + 5][cntr_x + 2] = '0';
					p[cntr_y + 5][cntr_x - 2] = '0';
					p[cntr_y + 4][cntr_x - 2] = '0';
					p[cntr_y + 4][cntr_x + 2] = '0';
					p[cntr_y + 4][cntr_x] = '0';
					p[cntr_y + 4][cntr_x + 1] = '0';
					p[cntr_y + 4][cntr_x - 1] = '0';
					p[cntr_y + 6][cntr_x + 2] = '0';
					p[cntr_y + 6][cntr_x - 2] = '0';
					p[cntr_y + 6][cntr_x] = '0';
					p[cntr_y + 6][cntr_x + 1] = '0';
					p[cntr_y + 6][cntr_x - 1] = '0';
					break;
				default:
					break;
			}
			cmd_rotate_draw(p, cntr_x, cntr_y, current_num, mode);
		}
		if (sum % 4 == 2) {
			cmd_rotate_clear(p, cntr_x, cntr_y, current_num, mode);
			switch (current_num) {
				case 1:
					p[cntr_y + 5][cntr_x] = '1';
					p[cntr_y + 4][cntr_x] = '1';
					p[cntr_y + 3][cntr_x] = '1';
					p[cntr_y + 6][cntr_x] = '1';
					p[cntr_y + 7][cntr_x] = '1';
					break;
				case 2:
					p[cntr_y + 5][cntr_x] = '2';
					p[cntr_y + 5][cntr_x + 1] = '2';
					p[cntr_y + 5][cntr_x - 1] = '2';
					p[cntr_y + 4][cntr_x + 1] = '2';
					p[cntr_y + 3][cntr_x] = '2';
					p[cntr_y + 3][cntr_x + 1] = '2';
					p[cntr_y + 3][cntr_x - 1] = '2';
					p[cntr_y + 6][cntr_x - 1] = '2';
					p[cntr_y + 7][cntr_x] = '2';
					p[cntr_y + 7][cntr_x + 1] = '2';
					p[cntr_y + 7][cntr_x - 1] = '2';
					break;
				case 3:
					p[cntr_y + 5][cntr_x] = '3';
					p[cntr_y + 5][cntr_x + 1] = '3';
					p[cntr_y + 5][cntr_x - 1] = '3';
					p[cntr_y + 4][cntr_x - 1] = '3';
					p[cntr_y + 3][cntr_x] = '3';
					p[cntr_y + 3][cntr_x + 1] = '3';
					p[cntr_y + 3][cntr_x - 1] = '3';
					p[cntr_y + 6][cntr_x - 1] = '3';
					p[cntr_y + 7][cntr_x] = '3';
					p[cntr_y + 7][cntr_x + 1] = '3';
					p[cntr_y + 7][cntr_x - 1] = '3';
					break;
				case 4:
					p[cntr_y + 5][cntr_x] = '4';
					p[cntr_y + 5][cntr_x + 1] = '4';
					p[cntr_y + 5][cntr_x - 1] = '4';
					p[cntr_y + 4][cntr_x - 1] = '4';
					p[cntr_y + 3][cntr_x - 1] = '4';
					p[cntr_y + 6][cntr_x + 1] = '4';
					p[cntr_y + 6][cntr_x - 1] = '4';
					p[cntr_y + 7][cntr_x + 1] = '4';
					p[cntr_y + 7][cntr_x - 1] = '4';
					break;
				case 5:
					p[cntr_y + 5][cntr_x] = '5';
					p[cntr_y + 5][cntr_x + 1] = '5';
					p[cntr_y + 5][cntr_x - 1] = '5';
					p[cntr_y + 4][cntr_x - 1] = '5';
					p[cntr_y + 3][cntr_x] = '5';
					p[cntr_y + 3][cntr_x + 1] = '5';
					p[cntr_y + 3][cntr_x - 1] = '5';
					p[cntr_y + 6][cntr_x + 1] = '5';
					p[cntr_y + 7][cntr_x] = '5';
					p[cntr_y + 7][cntr_x + 1] = '5';
					p[cntr_y + 7][cntr_x - 1] = '5';
					break;
				case 6:
					p[cntr_y + 5][cntr_x] = '6';
					p[cntr_y + 5][cntr_x + 1] = '6';
					p[cntr_y + 5][cntr_x - 1] = '6';
					p[cntr_y + 4][cntr_x - 1] = '6';
					p[cntr_y + 4][cntr_x + 1] = '6';
					p[cntr_y + 3][cntr_x] = '6';
					p[cntr_y + 3][cntr_x + 1] = '6';
					p[cntr_y + 3][cntr_x - 1] = '6';
					p[cntr_y + 6][cntr_x + 1] = '6';
					p[cntr_y + 7][cntr_x] = '6';
					p[cntr_y + 7][cntr_x + 1] = '6';
					p[cntr_y + 7][cntr_x - 1] = '6';
					break;
				case 7:
					p[cntr_y + 5][cntr_x - 1] = '7';
					p[cntr_y + 4][cntr_x - 1] = '7';
					p[cntr_y + 3][cntr_x - 1] = '7';
					p[cntr_y + 6][cntr_x - 1] = '7';
					p[cntr_y + 7][cntr_x - 1] = '7';
					p[cntr_y + 7][cntr_x] = '7';
					p[cntr_y + 7][cntr_x + 1] = '7';
					break;
				case 8:
					p[cntr_y + 5][cntr_x] = '8';
					p[cntr_y + 5][cntr_x + 1] = '8';
					p[cntr_y + 5][cntr_x - 1] = '8';
					p[cntr_y + 4][cntr_x - 1] = '8';
					p[cntr_y + 4][cntr_x + 1] = '8';
					p[cntr_y + 3][cntr_x] = '8';
					p[cntr_y + 3][cntr_x + 1] = '8';
					p[cntr_y + 3][cntr_x - 1] = '8';
					p[cntr_y + 6][cntr_x + 1] = '8';
					p[cntr_y + 6][cntr_x - 1] = '8';
					p[cntr_y + 7][cntr_x] = '8';
					p[cntr_y + 7][cntr_x + 1] = '8';
					p[cntr_y + 7][cntr_x - 1] = '8';
					break;
				case 9:
					p[cntr_y + 5][cntr_x] = '9';
					p[cntr_y + 5][cntr_x + 1] = '9';
					p[cntr_y + 5][cntr_x - 1] = '9';
					p[cntr_y + 4][cntr_x - 1] = '9';
					p[cntr_y + 3][cntr_x] = '9';
					p[cntr_y + 3][cntr_x + 1] = '9';
					p[cntr_y + 3][cntr_x - 1] = '9';
					p[cntr_y + 6][cntr_x + 1] = '9';
					p[cntr_y + 6][cntr_x - 1] = '9';
					p[cntr_y + 7][cntr_x] = '9';
					p[cntr_y + 7][cntr_x + 1] = '9';
					p[cntr_y + 7][cntr_x - 1] = '9';
					break;
				case 0:
					p[cntr_y + 5][cntr_x + 1] = '0';
					p[cntr_y + 5][cntr_x - 1] = '0';
					p[cntr_y + 4][cntr_x - 1] = '0';
					p[cntr_y + 4][cntr_x + 1] = '0';
					p[cntr_y + 3][cntr_x] = '0';
					p[cntr_y + 3][cntr_x + 1] = '0';
					p[cntr_y + 3][cntr_x - 1] = '0';
					p[cntr_y + 6][cntr_x + 1] = '0';
					p[cntr_y + 6][cntr_x - 1] = '0';
					p[cntr_y + 7][cntr_x] = '0';
					p[cntr_y + 7][cntr_x + 1] = '0';
					p[cntr_y + 7][cntr_x - 1] = '0';
					break;
				default:
					break;
			}
			cmd_rotate_draw(p, cntr_x, cntr_y, current_num, mode);
		}
		if (sum % 4 == 3) {
			cmd_rotate_clear(p, cntr_x, cntr_y, current_num, mode);
			switch (current_num) {
				case 1:
					p[cntr_y + 5][cntr_x] = '1';
					p[cntr_y + 5][cntr_x - 1] = '1';
					p[cntr_y + 5][cntr_x - 2] = '1';
					p[cntr_y + 5][cntr_x + 1] = '1';
					p[cntr_y + 5][cntr_x + 2] = '1';
					break;
				case 2:
					p[cntr_y + 5][cntr_x] = '2';
					p[cntr_y + 5][cntr_x + 2] = '2';
					p[cntr_y + 5][cntr_x - 2] = '2';
					p[cntr_y + 4][cntr_x - 1] = '2';
					p[cntr_y + 4][cntr_x - 2] = '2';
					p[cntr_y + 4][cntr_x + 2] = '2';
					p[cntr_y + 4][cntr_x] = '2';
					p[cntr_y + 6][cntr_x] = '2';
					p[cntr_y + 6][cntr_x - 2] = '2';
					p[cntr_y + 6][cntr_x + 1] = '2';
					p[cntr_y + 6][cntr_x + 2] = '2';
					break;
				case 3:
					p[cntr_y + 5][cntr_x] = '3';
					p[cntr_y + 5][cntr_x + 2] = '3';
					p[cntr_y + 5][cntr_x - 2] = '3';
					p[cntr_y + 4][cntr_x] = '3';
					p[cntr_y + 4][cntr_x - 2] = '3';
					p[cntr_y + 4][cntr_x + 2] = '3';
					p[cntr_y + 6][cntr_x + 1] = '3';
					p[cntr_y + 6][cntr_x - 1] = '3';
					p[cntr_y + 6][cntr_x - 2] = '3';
					p[cntr_y + 6][cntr_x] = '3';
					p[cntr_y + 6][cntr_x + 2] = '3';
					break;
				case 4:
					p[cntr_y + 5][cntr_x] = '4';
					p[cntr_y + 4][cntr_x + 2] = '4';
					p[cntr_y + 4][cntr_x + 1] = '4';
					p[cntr_y + 4][cntr_x] = '4';
					p[cntr_y + 6][cntr_x - 2] = '4';
					p[cntr_y + 6][cntr_x + 2] = '4';
					p[cntr_y + 6][cntr_x - 1] = '4';
					p[cntr_y + 6][cntr_x] = '4';
					p[cntr_y + 6][cntr_x + 1] = '4';
					break;
				case 5:
					p[cntr_y + 5][cntr_x] = '5';
					p[cntr_y + 5][cntr_x + 2] = '5';
					p[cntr_y + 5][cntr_x - 2] = '5';
					p[cntr_y + 4][cntr_x - 2] = '5';
					p[cntr_y + 4][cntr_x] = '5';
					p[cntr_y + 4][cntr_x + 2] = '5';
					p[cntr_y + 4][cntr_x + 1] = '5';
					p[cntr_y + 6][cntr_x + 2] = '5';
					p[cntr_y + 6][cntr_x] = '5';
					p[cntr_y + 6][cntr_x - 1] = '5';
					p[cntr_y + 6][cntr_x - 2] = '5';
					break;
				case 6:
					p[cntr_y + 5][cntr_x] = '6';
					p[cntr_y + 5][cntr_x + 2] = '6';
					p[cntr_y + 5][cntr_x - 2] = '6';
					p[cntr_y + 4][cntr_x - 2] = '6';
					p[cntr_y + 4][cntr_x] = '6';
					p[cntr_y + 4][cntr_x + 2] = '6';
					p[cntr_y + 4][cntr_x + 1] = '6';
					p[cntr_y + 4][cntr_x - 1] = '6';
					p[cntr_y + 6][cntr_x - 1] = '6';
					p[cntr_y + 6][cntr_x] = '6';
					p[cntr_y + 6][cntr_x + 2] = '6';
					p[cntr_y + 6][cntr_x - 2] = '6';
					break;
				case 7:
					p[cntr_y + 5][cntr_x + 2] = '7';
					p[cntr_y + 4][cntr_x + 2] = '7';
					p[cntr_y + 6][cntr_x] = '7';
					p[cntr_y + 6][cntr_x + 2] = '7';
					p[cntr_y + 6][cntr_x - 2] = '7';
					p[cntr_y + 6][cntr_x + 1] = '7';
					p[cntr_y + 6][cntr_x - 1] = '7';
					break;
				case 8:
					p[cntr_y + 5][cntr_x] = '8';
					p[cntr_y + 5][cntr_x + 2] = '8';
					p[cntr_y + 5][cntr_x - 2] = '8';
					p[cntr_y + 4][cntr_x - 2] = '8';
					p[cntr_y + 4][cntr_x + 2] = '8';
					p[cntr_y + 4][cntr_x] = '8';
					p[cntr_y + 4][cntr_x + 1] = '8';
					p[cntr_y + 4][cntr_x - 1] = '8';
					p[cntr_y + 6][cntr_x + 2] = '8';
					p[cntr_y + 6][cntr_x - 2] = '8';
					p[cntr_y + 6][cntr_x] = '8';
					p[cntr_y + 6][cntr_x + 1] = '8';
					p[cntr_y + 6][cntr_x - 1] = '8';
					break;
				case 9:
					p[cntr_y + 5][cntr_x] = '9';
					p[cntr_y + 5][cntr_x + 2] = '9';
					p[cntr_y + 5][cntr_x - 2] = '9';
					p[cntr_y + 4][cntr_x - 2] = '9';
					p[cntr_y + 4][cntr_x + 2] = '9';
					p[cntr_y + 4][cntr_x] = '9';
					p[cntr_y + 4][cntr_x + 1] = '9';
					p[cntr_y + 6][cntr_x - 1] = '9';
					p[cntr_y + 6][cntr_x - 2] = '9';
					p[cntr_y + 6][cntr_x] = '9';
					p[cntr_y + 6][cntr_x + 2] = '9';
					p[cntr_y + 6][cntr_x + 1] = '9';
					break;
				case 0:
					p[cntr_y + 5][cntr_x + 2] = '0';
					p[cntr_y + 5][cntr_x - 2] = '0';
					p[cntr_y + 4][cntr_x - 2] = '0';
					p[cntr_y + 4][cntr_x + 2] = '0';
					p[cntr_y + 4][cntr_x] = '0';
					p[cntr_y + 4][cntr_x + 1] = '0';
					p[cntr_y + 4][cntr_x - 1] = '0';
					p[cntr_y + 6][cntr_x + 2] = '0';
					p[cntr_y + 6][cntr_x - 2] = '0';
					p[cntr_y + 6][cntr_x] = '0';
					p[cntr_y + 6][cntr_x + 1] = '0';
					p[cntr_y + 6][cntr_x - 1] = '0';
					break;
				default:
					break;
			}
			cmd_rotate_draw(p, cntr_x, cntr_y, current_num, mode);
		}
	}
}

/*旋转对应的画格子函数*/
void cmd_rotate_clear(char(*p)[23], int& cntr_x, int& cntr_y, int current_num, int mode)
{
	int i, j;
	for (i = cntr_y + 2 + 5; i >= cntr_y - 2 + 5; i--)
		for (j = cntr_x - 2; j <= cntr_x + 2; j++)
			if (p[i][j] == current_num + 48) {
				//ij处变成白的
				if (i > 5 && mode != 1)
					clear(6 * j - 4, 3 * i - 17);
				p[i][j] = '*';
			}
}

void cmd_rotate_draw(char(*p)[23], int& cntr_x, int& cntr_y, int current_num, int mode)
{
	if (mode == 1)
		return;
	int i, j;
	for (i = cntr_y + 2 + 5; i >= cntr_y - 2 + 5; i--)
		for (j = cntr_x - 2; j <= cntr_x + 2; j++)
			if (p[i][j] == current_num + 48) {
				if (i > 5)
					star(6 * j - 4, 3 * i - 17, current_num);
			}
}