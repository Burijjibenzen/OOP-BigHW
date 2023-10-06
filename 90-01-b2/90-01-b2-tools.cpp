//2251206 冯羽芯 信06
#include <iostream>
#include "../include/cmd_console_tools.h"
#include "./90-01-b2.h"
#include <iomanip>
#include <conio.h>
#include <Windows.h>
using namespace std;

/*生成内部数组*/
void generate_array(int p[][12], int& r, int& c)
{
	srand((unsigned int)(time(0)));
	int i, j;
	for (i = 1; i <= r; i++)
		for (j = 1; j <= c; j++)
			p[i][j] = rand() % 5 + 1;
}

/*查找相同项*/
void same_array(int x, int y, char result[][12], int p[][12])
{
	result[x][y] = '*';
	if (p[x][y] == p[x - 1][y])
		if (result[x - 1][y] != '*')
			same_array(x - 1, y, result, p);

	if (p[x][y] == p[x + 1][y])
		if (result[x + 1][y] != '*')
			same_array(x + 1, y, result, p);

	if (p[x][y] == p[x][y + 1])
		if (result[x][y + 1] != '*')
			same_array(x, y + 1, result, p);

	if (p[x][y] == p[x][y - 1])
		if (result[x][y - 1] != '*')
			same_array(x, y - 1, result, p);
}

/*本小题结束*/
void end(void)
{
	while (1) {
		cct_setcolor();
		cout << "本小题结束，请输入End继续...";
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

/*相同值归并*/
void vanish_array(char result[][12], int p[][12], int& r, int& c)
{
	int i, j;
	for (i = 1; i <= r; i++)
		for (j = 1; j <= c; j++)
			if (result[i][j] == '*')
				p[i][j] = 0;
}

/*分数*/
void SCORE(char result[][12], int& r, int& c, int* total)
{
	int i, j, score = 0, sum = 0;
	for (i = 1; i <= r; i++)
		for (j = 1; j <= c; j++)
			if (result[i][j] == '*')
				sum++;
	score = sum * sum * 5;
	*total += score;

	cout << "本次得分：" << score << ' ' << "总分：" << *total << "         " << endl;
	cout << endl;
}

/*奖励得分*/
void bonus(int left, int* total)
{
	int bonus = 0;
	if (left >= 10)
		bonus = 0;
	else
		bonus = (10 - left) * 180;

	cct_gotoxy(0, 0);
	cct_setcolor();
	cout << "奖励得分:" << bonus << " 总分:" << *total<<"              ";
}

/*回车继续*/
void wait_for_enter(const char* prompt)
{
	cct_setcolor(); //恢复缺省颜色
	cout << prompt << endl;
	/* 忽略除回车键外的所有输入（注意：_getch的回车是\r，而getchar是\n）*/
	while (_getch() != '\r')
		;
	return;
}

/*下落+移动*/
void fall_array(int p[][12], int& r, int& c)
{
	int i, j, k, m, t, sum1 = 0, sum2 = 0;
	for (j = 1; j <= c; j++)
		for (i = r; i >= 1; i--)
			if (p[i][j] == 0)
				for (k = i - 1; k >= 1; k--)
					if (p[k][j] != 0) {
						t = p[i][j];
						p[i][j] = p[k][j];
						p[k][j] = t;
						break;
					}

	for (j = 1; j <= c; j++) {
		for (i = r; i >= 1; i--)
			if (p[i][j] == 0)
				sum1++;

		for (k = j + 1; k <= c; k++) {
			for (m = r; m >= 1; m--)
				if (p[m][k] == 0)
					sum2++;

			if (sum1 == r && sum1 != sum2) {
				for (i = r; i >= 1; i--) {
					t = p[i][j];
					p[i][j] = p[i][k];
					p[i][k] = t;
				}
				break;
			}
			sum2 = 0;
		}
		sum2 = 0;
		sum1 = 0;
	}
}

/*是否结束*/
int over(int p[][12], int& r, int& c)
{
	int i, j, sum = 0;
	for (i = 1; i <= r; i++)
		for (j = 1; j < c; j++) {
			if (p[i][j] == 0)
				continue;
			else if (p[i][j] != p[i][j + 1] && p[i][j] != p[i][j - 1] && p[i][j] != p[i - 1][j] && p[i][j] != p[i + 1][j]) {
				sum++;
				continue;
			}
			else return 0;
		}
	return sum;
}