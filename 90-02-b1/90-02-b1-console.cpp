/* 2251206 ����о �ƿ� */

//��cpp���ڴ��αͼ�ν�����Ҫ�õ��ĺ����ľ���ʵ�� 
#include <iostream>
#include "90-02-b1.h"
#include "../include/cmd_console_tools.h"
#include <time.h>
#include <Windows.h>
#include <conio.h>
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
	cout << "��������������" << line;
	cct_gotoxy(w * 6 + 10, 6);
	cout << "��esc���˳�";
}

/*��ӡ����*/
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
	cout << "�X�T�[";
	cct_gotoxy(x_star, y_star + 1);
	cout << "�U��U";
	cct_gotoxy(x_star, y_star + 2);
	cout << "�^�T�a";
	cct_setcolor();
}

/*�ָ�ԭ״*/
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

/*����ĺ���*/
int fall(char(*p)[23], char(*q)[23], int current_num, int cntr_x, int cntr_y, int& h, int& w, int& judge, int& line, int mode)
{
	//����ı���
	// �ܷ�������ж� ����������Ϊ���ĵ�5*5���񣬴�ͷ��ʼ����������е�ǰΪ��Ӧ�������·�Ϊ0����ֹͣ���䣬�������
	//����������Ϊ���ģ������һ�ſ�ʼ����ѭ��������е�ǰΪ��Ӧ���֣�����*���·�*��ɵ�ǰ����
	cntr_y += 5; //�����˿���������һֱ��5�ַ���
	int i, j; //judge�Ƿ�����
	for (i = cntr_y - 2; i <= cntr_y + 2; i++)
		for (j = cntr_x - 2; j <= cntr_x + 2; j++)
			if (p[i][j] == current_num + 48 && p[i + 1][j] == '#')
				judge = 1;
	if (judge == 1) {
		//��ǰ���ݱ��# color�����д���ɫ��Ϣ
		for (i = cntr_y - 2; i <= cntr_y + 2; i++)
			for (j = cntr_x - 2; j <= cntr_x + 2; j++)
				if (p[i][j] == current_num + 48) {
					p[i][j] = '#';
					q[i][j] = current_num + 48;
				}
		line = clearup(p, q, h, w);
		if (line != 0 && mode == 5)
			return 1; //ֹͣ����
		else
			return 0;
	}
	else {
		//����
		for (i = cntr_y + 2; i >= cntr_y - 2; i--)
			for (j = cntr_x - 2; j <= cntr_x + 2; j++)
				if (p[i][j] == current_num + 48 && p[i + 1][j] == '*') {
					//ij����ɰ׵�
					if (i > 5)
						clear(6 * j - 4, 3 * i - 17);
					p[i][j] = '*';
					//i+1j���������
					if (i + 1 > 5)
						star(6 * j - 4, 3 * (i + 1) - 17, current_num);
					p[i + 1][j] = current_num + 48;
				}
	}
	return 0;
}

/*����*/
void left(char(*p)[23], int current_num, int& cntr_x, int cntr_y)
{
	//ƽ�Ƶı���
	// �ܷ����Ƶ��ж� �ж�cntr_x
	//������ԣ�����������Ϊ���ģ���������ѭ��������е�ǰΪ��Ӧ���֣�����*����*��ɵ�ǰ����
	cntr_y += 5; //�����˿���������һֱ��5�ַ���
	int i, j, judge = 0; //mark�Ƿ�����
	if ((current_num == 1 && cntr_x <= 1) || (current_num != 1 && cntr_x <= 2))
		return; //ԭʼ��״����ԭʼ�߽�
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
					//ij����ɰ׵�
					if (i > 5)
						clear(6 * j - 4, 3 * i - 17);
					p[i][j] = '*';
					//ij-1���������
					if (i > 5)
						star(6 * (j - 1) - 4, 3 * i - 17, current_num);
					p[i][j - 1] = current_num + 48;
				}
		cntr_x--;
	}
}

/*����*/
void right(char(*p)[23], int current_num, int& cntr_x, int cntr_y, int w)
{
	cntr_y += 5; //�����˿���������һֱ��5�ַ���
	int i, j, judge = 0; //mark�Ƿ�����
	if ((current_num == 1 && cntr_x >= w) || (current_num != 1 && cntr_x >= w - 1))
		return; //ԭʼ��״����ԭʼ�߽�
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
					//ij����ɰ׵�
					if (i > 5)
						clear(6 * j - 4, 3 * i - 17);
					p[i][j] = '*';
					//ij-1���������
					if (i > 5)
						star(6 * (j + 1) - 4, 3 * i - 17, current_num);
					p[i][j + 1] = current_num + 48;
				}
		cntr_x++;
	}
}

/*��������*/
int opr(char(*p)[23], char(*q)[23], int current_num, int& h, int& w, int cntr_x, int cntr_y, int& score, int& line, int mode)
{
	int ret;
	int keycode1, keycode2;
	int loop = 1;
	int sum = 0; //����ÿһ�����ֵ���ת ����һ�����

	unsigned int interval;
	DWORD t1, t2;
	while (1) {
		t1 = GetTickCount();
		while (1) {
			if (score < 120) //�����ʱ����
				interval = (int)((1 - score / 15 * 0.1) * 1000);
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
									interval = interval / 8;
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
						case 27:	//ESC��
							return 1;
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
				return -1;
			if ((t2 - t1) >= interval) {
				int judge = 0;
				if (fall(p, q, current_num, cntr_x, cntr_y, h, w, judge, line, mode) == 1)
					return 2;

				if (judge == 1) {   //�޷�����
					//�ж��Ƿ���Խ�������
					if (line == 1)
						score += 1;
					else if (line == 2)
						score += 3;
					else if (line == 3)
						score += 6;
					else if (line == 4)
						score += 10;
					else if (line == 5)
						score += 15;
					return -1;
				}
				else {
					cntr_y++;
					break;
				}
			}
		}
	}
	return 0;
}

/*��û��*/
int death(char(*p)[23], int w)
{
	//�ж�ǰ������û��# ������Ϸ����
	for (int i = 1; i <= 5; i++)
		for (int j = 1; j <= w; j++)
			if (p[i][j] == '#') {
				cct_gotoxy(w * 6 + 10, 7);
				cout << "Game Over";
				return 1;
			}
	return 0;
}

/*����*/
int clearup(char(*p)[23], char(*q)[23], int& h, int& w)
{
	int line = 0;
	//���������ң���û��һ����#�ģ��еĻ�һ������*��#�����棬��ɫͬ��
	for (int i = h + 5; i >= 1 + 5; i--) {
		int num = 0;
		for (int j = 1; j <= w; j++) {
			if (p[i][j] == '#')
				num++;
		}
		if (num == w) {
			line++;
			for (int j = 1; j <= w; j++) {
				p[i][j] = '*';
				q[i][j] = '*';
			}
		}
	}
	//�Ϸ������ƣ���һ�б��*
	for (int k = 1; k <= line; k++) {
		for (int i = h + 5; i >= 1 + 5; i--) {
			int num = 0;
			for (int j = 1; j <= w; j++) {
				if (p[i][j] == '*')
					num++;
			}
			if (num == w) {
				for (int m = i; m >= 1 + 5 + 1; m--) {
					for (int j = 1; j <= w; j++) {
						p[m][j] = p[m - 1][j];
						q[m][j] = q[m - 1][j];
					}
				}
				for (int j = 1; j <= w; j++) {
					p[6][j] = '*';
					q[6][j] = '*';
				}
			}
		}
	}

	for (int i = 1 + 5; i <= h + 5; i++)
		for (int j = 1; j <= w; j++) {
			if (q[i][j] == '*')
				clear(6 * j - 4, 3 * i - 17);
			else
				star(6 * j - 4, 3 * i - 17, q[i][j] - '0');
		}
	return line;
}