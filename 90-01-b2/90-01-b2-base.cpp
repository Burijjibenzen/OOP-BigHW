//2251206 冯羽芯 信06
#include <iostream>
#include "../include/cmd_console_tools.h"
#include "./90-01-b2.h"
#include <conio.h>
using namespace std;

/*打印当前数组*/
void current_array(int p[][12], int& r, int& c)
{
	cout << "当前数组：\n";
	cout << "  |";
	int i, j;
	for (i = 0; i < c; i++)
		cout << "  " << i;
	cout << endl;
	cout << "--+-";
	for (i = 0; i < c; i++)
		cout << "---";
	cout << endl;
	for (i = 1; i <= r; i++) {
		cout << (char)('A' + i - 1) << " |";
		for (j = 1; j <= c; j++) {
			cout << "  ";
			if (p[i][j] == 0)
				cct_setcolor(COLOR_HYELLOW, COLOR_BLACK);
			cout << p[i][j];
			cct_setcolor();
		}
		cout << endl;
	}
	cout << endl;
}

/*输入坐标*/
void coordinate_input(char* coordinate, int p[][12], int& r, int& c)
{
	int X, Y;
	//cin.ignore();如果计数值达到 a 或者被抛弃的字符是 ch ，则cin.ignore() 函数执行终止；否则，它继续等待。
	//应该在前面清空缓冲区，而不是在这里
	while (1) {
		cout << "请以字母+数字形式[例：c2]输入矩阵坐标：";
		cct_getxy(X, Y);//取当前光标位置
		cin.get(coordinate, 3, '\n');//如果不清空缓冲区，回车一直留着，死循环，cin.getline超出个数比较复杂,cin变成fail了
		/* https://blog.csdn.net/weixin_40064300/article/details/128191604 */
		cin.clear();
		cin.ignore(65536, '\n');

		if (coordinate[0] >= 'a' && coordinate[0] <= 'a' + r - 1)
			coordinate[0] -= 32;
		if ((coordinate[0] >= 'A') && (coordinate[0] <= 'A' + r - 1) && (coordinate[1] >= '0') && (coordinate[1] <= c - 1 + '0')) {
			cout << "输入为" << coordinate[0] << "行" << coordinate[1] << "列\n";
			if (p[coordinate[0] - 'A' + 1][coordinate[1] - '0' + 1] != p[coordinate[0] - 'A'][coordinate[1] - '0' + 1]
				&& p[coordinate[0] - 'A' + 1][coordinate[1] - '0' + 1] != p[coordinate[0] - 'A' + 2][coordinate[1] - '0' + 1]
				&& p[coordinate[0] - 'A' + 1][coordinate[1] - '0' + 1] != p[coordinate[0] - 'A' + 1][coordinate[1] - '0']
				&& p[coordinate[0] - 'A' + 1][coordinate[1] - '0' + 1] != p[coordinate[0] - 'A' + 1][coordinate[1] - '0' + 2]) {
				cout << "输入的矩阵坐标位置处无连续相同值，请重新输入\n";
				cout << endl;
				continue;
			}
			else if (p[coordinate[0] - 'A' + 1][coordinate[1] - '0' + 1] == 0) {
				cout << "输入的矩阵坐标位置为0（非法位置），请重新输入\n";
				cout << endl;
				continue;
			}
			else
				break;
		}
		else {
			cct_gotoxy(X, Y);
			for (int i = 0; i < 18; i++)
				cout << ' ';
			cct_gotoxy(0, Y + 1);
			cout << "输入错误，请重新输入.";
			cct_gotoxy(0, Y);
			continue;
		}
	}
	cout << endl;
}

/*当前数组(不同色标识)*/
void color_array(char result[][12], int p[][12], int& r, int& c)
{
	cout << "当前数组(不同色标识)：\n";
	cout << "  |";
	int i, j;
	for (i = 0; i < c; i++)
		cout << "  " << i;
	cout << endl;
	cout << "--+-";
	for (i = 0; i < c; i++)
		cout << "---";
	cout << endl;
	for (i = 1; i <= r; i++) {
		cout << (char)('A' + i - 1) << " |";
		for (j = 1; j <= c; j++) {
			cout << "  ";
			if (result[i][j] == '*')
				cct_setcolor(COLOR_HYELLOW, COLOR_BLACK);
			cout << p[i][j];
			cct_setcolor();
		}
		cout << endl;
	}
	cout << endl;
}

/*查找结果数组*/
void result_array(char result[][12], int& r, int& c)
{
	cout << "查找结果数组：\n";
	cout << "  |";
	int i, j;
	for (i = 0; i < c; i++)
		cout << "  " << i;
	cout << endl;
	cout << "--+-";
	for (i = 0; i < c; i++)
		cout << "---";
	cout << endl;
	for (i = 1; i <= r; i++) {
		cout << (char)('A' + i - 1) << " |";
		for (j = 1; j <= c; j++)
			cout << "  " << result[i][j];
		cout << endl;
	}
	cout << endl;
}

/*确认是否把相同值消除*/
char confirm(char* coordinate)
{
	cout << "请确认是否把" <<coordinate<< "及周围的相同值消除(Y/N/Q)：";
	char option;
	int X, Y;
	cct_getxy(X, Y);
	while (1) {
		option = _getche();
		if (option == 'y' || option == 'Y' || option == 'n' || option == 'N' || option == 'q' || option == 'Q')
			return option;
		else
			cct_gotoxy(X, Y);
	}
}

/*相同值归并后的数组(不同色标识)*/
void color_vanish_array(char result[][12], int p[][12], int& r, int& c)
{
	cout << "相同值归并后的数组(不同色标识)：\n";
	cout << "  |";
	int i, j;
	for (i = 0; i < c; i++)
		cout << "  " << i;
	cout << endl;
	cout << "--+-";
	for (i = 0; i < c; i++)
		cout << "---";
	cout << endl;
	for (i = 1; i <= r; i++) {
		cout << (char)('A' + i - 1) << " |";
		for (j = 1; j <= c; j++) {
			cout << "  ";
			if (result[i][j] == '*')
				cct_setcolor(COLOR_HYELLOW, COLOR_BLACK);
			cout << p[i][j];
			cct_setcolor();
		}
		cout << endl;
	}
	cout << endl;
}

/*打印下落后的数组*/
void print_fall_array(char result[][12], int p[][12], int& r, int& c)
{
	cout << "下落后的数组：\n";
	cout << "  |";
	int i, j;
	for (i = 0; i < c; i++)
		cout << "  " << i;
	cout << endl;
	cout << "--+-";
	for (i = 0; i < c; i++)
		cout << "---";
	cout << endl;
	for (i = 1; i <= r; i++) {
		cout << (char)('A' + i - 1) << " |";
		for (j = 1; j <= c; j++) {
			cout << "  ";
			if (p[i][j] == 0)
				cct_setcolor(COLOR_HYELLOW, COLOR_BLACK);
			cout << p[i][j];
			cct_setcolor();
		}
		cout << endl;
	}
	cout << endl;
}