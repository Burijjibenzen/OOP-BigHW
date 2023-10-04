/* 2251206 ����о �ƿ� */

//��cpp���ڴ���ڲ����������Ҫ�õ��ĺ����ľ���ʵ��
#include <iostream>
#include "90-02-b1.h"
#include "../include/cmd_console_tools.h"
#include <time.h>
#include <Windows.h>
using namespace std;

/*��������*/
void input(int* h, int* w)
{
	while (1) {
		cout << "������߶�(18-26)��\n";
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
		cout << "��������(12-21,��Ϊ3�ı���)��\n";
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

/*�����ڲ�����*/
void generate_array(char(*p)[22], int& h, int& w)
{
	int i, j;
	for (i = 0; i < h + 5 + 1; i++)
		for (j = 0; j < w + 1; j++)
			p[i][j] = '*'; //��ʼ��Ϊ*
	for (j = 0; j < w + 1; j++)
		p[i][j] = '0';//���һ��ȫΪ0�����������ж�
}

/*��ӡ��ǰ����*/
void current_array(char(*p)[22], int& h, int& w)
{
	cout << "��ǰ���飺\n";
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

/*���������*/
int get_next_num(const bool new_seed = false, const unsigned int seed = 0)
{
	if (new_seed)
		srand(seed);

	return rand() % 10;
}

/*���������������ֳ�ʼλ��/��ʼ����������*/
void generate_num(char(*p)[22], int& h, int& w, int& cntr_x, int& cntr_y, int& current_num, int mode)
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

/*��С�����*/
void end(void)
{
	while (1) {
		cct_setcolor();
		cout << "��С�������������End����";
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
			cout << "�����������������";
			cout << "\n";
			continue;
		}
	}
}

/*��ת*/
void rotate(char(*p)[22], int& h, int& w, int& cntr_x, int& cntr_y, int next_num)
{
	int MX = 0, MY = 0;
	int ret, maction;
	int keycode1, keycode2;
	int loop = 1;
	int sum = 0;
	cout << "�밴����������ת����esc���˳�����\n";
	while (loop) {
		ret = cct_read_keyboard_and_mouse(MX, MY, maction, keycode1, keycode2);
		if (ret == CCT_KEYBOARD_EVENT) {
			switch (keycode1) {
				case 224:
					switch (keycode2) {
						case KB_ARROW_UP:
							//���ж��Ƿ������ת
							if (cntr_x <= 2 || cntr_x >= w - 1 || cntr_y >= h - 1) {
								cout << "�޷���ת";
								return;
							}
							else {
								sum++;
								if (sum % 4 == 0) {
									// �������
									switch (next_num) {
										case 1:
											p[cntr_y + 5][cntr_x] = '*';
											p[cntr_y + 5][cntr_x - 1] = '*';
											p[cntr_y + 5][cntr_x - 2] = '*';
											p[cntr_y + 5][cntr_x + 1] = '*';
											p[cntr_y + 5][cntr_x + 2] = '*';
											break;
										case 2:
											p[cntr_y + 5][cntr_x] = '*';
											p[cntr_y + 5][cntr_x + 2] = '*';
											p[cntr_y + 5][cntr_x - 2] = '*';
											p[cntr_y + 4][cntr_x - 1] = '*';
											p[cntr_y + 4][cntr_x - 2] = '*';
											p[cntr_y + 4][cntr_x + 2] = '*';
											p[cntr_y + 4][cntr_x] = '*';
											p[cntr_y + 6][cntr_x] = '*';
											p[cntr_y + 6][cntr_x - 2] = '*';
											p[cntr_y + 6][cntr_x + 1] = '*';
											p[cntr_y + 6][cntr_x + 2] = '*';
											break;
										case 3:
											p[cntr_y + 5][cntr_x] = '*';
											p[cntr_y + 5][cntr_x + 2] = '*';
											p[cntr_y + 5][cntr_x - 2] = '*';
											p[cntr_y + 4][cntr_x] = '*';
											p[cntr_y + 4][cntr_x - 2] = '*';
											p[cntr_y + 4][cntr_x + 2] = '*';
											p[cntr_y + 6][cntr_x + 1] = '*';
											p[cntr_y + 6][cntr_x - 1] = '*';
											p[cntr_y + 6][cntr_x - 2] = '*';
											p[cntr_y + 6][cntr_x] = '*';
											p[cntr_y + 6][cntr_x + 2] = '*';
											break;
										case 4:
											p[cntr_y + 5][cntr_x] = '*';
											p[cntr_y + 4][cntr_x + 2] = '*';
											p[cntr_y + 4][cntr_x + 1] = '*';
											p[cntr_y + 4][cntr_x] = '*';
											p[cntr_y + 6][cntr_x - 2] = '*';
											p[cntr_y + 6][cntr_x + 2] = '*';
											p[cntr_y + 6][cntr_x - 1] = '*';
											p[cntr_y + 6][cntr_x] = '*';
											p[cntr_y + 6][cntr_x + 1] = '*';
											break;
										case 5:
											p[cntr_y + 5][cntr_x] = '*';
											p[cntr_y + 5][cntr_x + 2] = '*';
											p[cntr_y + 5][cntr_x - 2] = '*';
											p[cntr_y + 4][cntr_x - 2] = '*';
											p[cntr_y + 4][cntr_x] = '*';
											p[cntr_y + 4][cntr_x + 2] = '*';
											p[cntr_y + 4][cntr_x + 1] = '*';
											p[cntr_y + 6][cntr_x + 2] = '*';
											p[cntr_y + 6][cntr_x] = '*';
											p[cntr_y + 6][cntr_x - 1] = '*';
											p[cntr_y + 6][cntr_x - 2] = '*';
											break;
										case 6:
											p[cntr_y + 5][cntr_x] = '*';
											p[cntr_y + 5][cntr_x + 2] = '*';
											p[cntr_y + 5][cntr_x - 2] = '*';
											p[cntr_y + 4][cntr_x - 2] = '*';
											p[cntr_y + 4][cntr_x] = '*';
											p[cntr_y + 4][cntr_x + 2] = '*';
											p[cntr_y + 4][cntr_x + 1] = '*';
											p[cntr_y + 4][cntr_x - 1] = '*';
											p[cntr_y + 6][cntr_x - 1] = '*';
											p[cntr_y + 6][cntr_x] = '*';
											p[cntr_y + 6][cntr_x + 2] = '*';
											p[cntr_y + 6][cntr_x - 2] = '*';
											break;
										case 7:
											p[cntr_y + 5][cntr_x + 2] = '*';
											p[cntr_y + 4][cntr_x + 2] = '*';
											p[cntr_y + 6][cntr_x] = '*';
											p[cntr_y + 6][cntr_x + 2] = '*';
											p[cntr_y + 6][cntr_x - 2] = '*';
											p[cntr_y + 6][cntr_x + 1] = '*';
											p[cntr_y + 6][cntr_x - 1] = '*';
											break;
										case 8:
											p[cntr_y + 5][cntr_x] = '*';
											p[cntr_y + 5][cntr_x + 2] = '*';
											p[cntr_y + 5][cntr_x - 2] = '*';
											p[cntr_y + 4][cntr_x - 2] = '*';
											p[cntr_y + 4][cntr_x + 2] = '*';
											p[cntr_y + 4][cntr_x] = '*';
											p[cntr_y + 4][cntr_x + 1] = '*';
											p[cntr_y + 4][cntr_x - 1] = '*';
											p[cntr_y + 6][cntr_x + 2] = '*';
											p[cntr_y + 6][cntr_x - 2] = '*';
											p[cntr_y + 6][cntr_x] = '*';
											p[cntr_y + 6][cntr_x + 1] = '*';
											p[cntr_y + 6][cntr_x - 1] = '*';
											break;
										case 9:
											p[cntr_y + 5][cntr_x] = '*';
											p[cntr_y + 5][cntr_x + 2] = '*';
											p[cntr_y + 5][cntr_x - 2] = '*';
											p[cntr_y + 4][cntr_x - 2] = '*';
											p[cntr_y + 4][cntr_x + 2] = '*';
											p[cntr_y + 4][cntr_x] = '*';
											p[cntr_y + 4][cntr_x + 1] = '*';
											p[cntr_y + 6][cntr_x - 1] = '*';
											p[cntr_y + 6][cntr_x - 2] = '*';
											p[cntr_y + 6][cntr_x] = '*';
											p[cntr_y + 6][cntr_x + 2] = '*';
											p[cntr_y + 6][cntr_x + 1] = '*';
											break;
										case 0:
											p[cntr_y + 5][cntr_x + 2] = '*';
											p[cntr_y + 5][cntr_x - 2] = '*';
											p[cntr_y + 4][cntr_x - 2] = '*';
											p[cntr_y + 4][cntr_x + 2] = '*';
											p[cntr_y + 4][cntr_x] = '*';
											p[cntr_y + 4][cntr_x + 1] = '*';
											p[cntr_y + 4][cntr_x - 1] = '*';
											p[cntr_y + 6][cntr_x + 2] = '*';
											p[cntr_y + 6][cntr_x - 2] = '*';
											p[cntr_y + 6][cntr_x] = '*';
											p[cntr_y + 6][cntr_x + 1] = '*';
											p[cntr_y + 6][cntr_x - 1] = '*';
											break;
										default:
											break;
									}
									switch (next_num) {
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
								if (sum % 4 == 1) {
									switch (next_num) {
										case 1:
											p[cntr_y + 5][cntr_x] = '*';
											p[cntr_y + 4][cntr_x] = '*';
											p[cntr_y + 3][cntr_x] = '*';
											p[cntr_y + 6][cntr_x] = '*';
											p[cntr_y + 7][cntr_x] = '*';
											break;
										case 2:
											p[cntr_y + 5][cntr_x] = '*';
											p[cntr_y + 5][cntr_x + 1] = '*';
											p[cntr_y + 5][cntr_x - 1] = '*';
											p[cntr_y + 4][cntr_x + 1] = '*';
											p[cntr_y + 3][cntr_x] = '*';
											p[cntr_y + 3][cntr_x + 1] = '*';
											p[cntr_y + 3][cntr_x - 1] = '*';
											p[cntr_y + 6][cntr_x - 1] = '*';
											p[cntr_y + 7][cntr_x] = '*';
											p[cntr_y + 7][cntr_x + 1] = '*';
											p[cntr_y + 7][cntr_x - 1] = '*';
											break;
										case 3:
											p[cntr_y + 5][cntr_x] = '*';
											p[cntr_y + 5][cntr_x + 1] = '*';
											p[cntr_y + 5][cntr_x - 1] = '*';
											p[cntr_y + 4][cntr_x + 1] = '*';
											p[cntr_y + 3][cntr_x] = '*';
											p[cntr_y + 3][cntr_x + 1] = '*';
											p[cntr_y + 3][cntr_x - 1] = '*';
											p[cntr_y + 6][cntr_x + 1] = '*';
											p[cntr_y + 7][cntr_x] = '*';
											p[cntr_y + 7][cntr_x + 1] = '*';
											p[cntr_y + 7][cntr_x - 1] = '*';
											break;
										case 4:
											p[cntr_y + 5][cntr_x] = '*';
											p[cntr_y + 5][cntr_x + 1] = '*';
											p[cntr_y + 5][cntr_x - 1] = '*';
											p[cntr_y + 4][cntr_x + 1] = '*';
											p[cntr_y + 4][cntr_x - 1] = '*';
											p[cntr_y + 3][cntr_x + 1] = '*';
											p[cntr_y + 3][cntr_x - 1] = '*';
											p[cntr_y + 6][cntr_x + 1] = '*';
											p[cntr_y + 7][cntr_x + 1] = '*';
											break;
										case 5:
											p[cntr_y + 5][cntr_x] = '*';
											p[cntr_y + 5][cntr_x + 1] = '*';
											p[cntr_y + 5][cntr_x - 1] = '*';
											p[cntr_y + 4][cntr_x - 1] = '*';
											p[cntr_y + 3][cntr_x] = '*';
											p[cntr_y + 3][cntr_x + 1] = '*';
											p[cntr_y + 3][cntr_x - 1] = '*';
											p[cntr_y + 6][cntr_x + 1] = '*';
											p[cntr_y + 7][cntr_x] = '*';
											p[cntr_y + 7][cntr_x + 1] = '*';
											p[cntr_y + 7][cntr_x - 1] = '*';
											break;
										case 6:
											p[cntr_y + 5][cntr_x] = '*';
											p[cntr_y + 5][cntr_x + 1] = '*';
											p[cntr_y + 5][cntr_x - 1] = '*';
											p[cntr_y + 4][cntr_x - 1] = '*';
											p[cntr_y + 3][cntr_x] = '*';
											p[cntr_y + 3][cntr_x + 1] = '*';
											p[cntr_y + 3][cntr_x - 1] = '*';
											p[cntr_y + 6][cntr_x + 1] = '*';
											p[cntr_y + 6][cntr_x - 1] = '*';
											p[cntr_y + 7][cntr_x] = '*';
											p[cntr_y + 7][cntr_x + 1] = '*';
											p[cntr_y + 7][cntr_x - 1] = '*';
											break;
										case 7:
											p[cntr_y + 5][cntr_x + 1] = '*';
											p[cntr_y + 4][cntr_x + 1] = '*';
											p[cntr_y + 3][cntr_x] = '*';
											p[cntr_y + 3][cntr_x + 1] = '*';
											p[cntr_y + 3][cntr_x - 1] = '*';
											p[cntr_y + 6][cntr_x + 1] = '*';
											p[cntr_y + 7][cntr_x + 1] = '*';
											break;
										case 8:
											p[cntr_y + 5][cntr_x] = '*';
											p[cntr_y + 5][cntr_x + 1] = '*';
											p[cntr_y + 5][cntr_x - 1] = '*';
											p[cntr_y + 4][cntr_x - 1] = '*';
											p[cntr_y + 4][cntr_x + 1] = '*';
											p[cntr_y + 3][cntr_x] = '*';
											p[cntr_y + 3][cntr_x + 1] = '*';
											p[cntr_y + 3][cntr_x - 1] = '*';
											p[cntr_y + 6][cntr_x + 1] = '*';
											p[cntr_y + 6][cntr_x - 1] = '*';
											p[cntr_y + 7][cntr_x] = '*';
											p[cntr_y + 7][cntr_x + 1] = '*';
											p[cntr_y + 7][cntr_x - 1] = '*';
											break;
										case 9:
											p[cntr_y + 5][cntr_x] = '*';
											p[cntr_y + 5][cntr_x + 1] = '*';
											p[cntr_y + 5][cntr_x - 1] = '*';
											p[cntr_y + 4][cntr_x - 1] = '*';
											p[cntr_y + 4][cntr_x + 1] = '*';
											p[cntr_y + 3][cntr_x] = '*';
											p[cntr_y + 3][cntr_x + 1] = '*';
											p[cntr_y + 3][cntr_x - 1] = '*';
											p[cntr_y + 6][cntr_x + 1] = '*';
											p[cntr_y + 7][cntr_x] = '*';
											p[cntr_y + 7][cntr_x + 1] = '*';
											p[cntr_y + 7][cntr_x - 1] = '*';
											break;
										case 0:
											p[cntr_y + 5][cntr_x + 1] = '*';
											p[cntr_y + 5][cntr_x - 1] = '*';
											p[cntr_y + 4][cntr_x - 1] = '*';
											p[cntr_y + 4][cntr_x + 1] = '*';
											p[cntr_y + 3][cntr_x] = '*';
											p[cntr_y + 3][cntr_x + 1] = '*';
											p[cntr_y + 3][cntr_x - 1] = '*';
											p[cntr_y + 6][cntr_x + 1] = '*';
											p[cntr_y + 6][cntr_x - 1] = '*';
											p[cntr_y + 7][cntr_x] = '*';
											p[cntr_y + 7][cntr_x + 1] = '*';
											p[cntr_y + 7][cntr_x - 1] = '*';
											break;
										default:
											break;
									}
									switch (next_num) {
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
								}
								if (sum % 4 == 2) {
									switch (next_num) {
										case 1:
											p[cntr_y + 5][cntr_x] = '*';
											p[cntr_y + 5][cntr_x - 1] = '*';
											p[cntr_y + 5][cntr_x - 2] = '*';
											p[cntr_y + 5][cntr_x + 1] = '*';
											p[cntr_y + 5][cntr_x + 2] = '*';
											break;
										case 2:
											p[cntr_y + 5][cntr_x] = '*';
											p[cntr_y + 5][cntr_x + 2] = '*';
											p[cntr_y + 5][cntr_x - 2] = '*';
											p[cntr_y + 4][cntr_x - 1] = '*';
											p[cntr_y + 4][cntr_x - 2] = '*';
											p[cntr_y + 4][cntr_x + 2] = '*';
											p[cntr_y + 4][cntr_x] = '*';
											p[cntr_y + 6][cntr_x] = '*';
											p[cntr_y + 6][cntr_x - 2] = '*';
											p[cntr_y + 6][cntr_x + 1] = '*';
											p[cntr_y + 6][cntr_x + 2] = '*';
											break;
										case 3:
											p[cntr_y + 5][cntr_x] = '*';
											p[cntr_y + 5][cntr_x + 2] = '*';
											p[cntr_y + 5][cntr_x - 2] = '*';
											p[cntr_y + 4][cntr_x - 1] = '*';
											p[cntr_y + 4][cntr_x - 2] = '*';
											p[cntr_y + 4][cntr_x + 2] = '*';
											p[cntr_y + 4][cntr_x + 1] = '*';
											p[cntr_y + 4][cntr_x] = '*';
											p[cntr_y + 6][cntr_x - 2] = '*';
											p[cntr_y + 6][cntr_x] = '*';
											p[cntr_y + 6][cntr_x + 2] = '*';
											break;
										case 4:
											p[cntr_y + 5][cntr_x] = '*';
											p[cntr_y + 4][cntr_x + 1] = '*';
											p[cntr_y + 4][cntr_x - 1] = '*';
											p[cntr_y + 4][cntr_x] = '*';
											p[cntr_y + 4][cntr_x - 2] = '*';
											p[cntr_y + 4][cntr_x + 2] = '*';
											p[cntr_y + 6][cntr_x - 1] = '*';
											p[cntr_y + 6][cntr_x] = '*';
											p[cntr_y + 6][cntr_x - 2] = '*';
											break;
										case 5:
											p[cntr_y + 5][cntr_x] = '*';
											p[cntr_y + 5][cntr_x + 2] = '*';
											p[cntr_y + 5][cntr_x - 2] = '*';
											p[cntr_y + 4][cntr_x - 2] = '*';
											p[cntr_y + 4][cntr_x] = '*';
											p[cntr_y + 4][cntr_x + 2] = '*';
											p[cntr_y + 4][cntr_x + 1] = '*';
											p[cntr_y + 6][cntr_x + 2] = '*';
											p[cntr_y + 6][cntr_x] = '*';
											p[cntr_y + 6][cntr_x - 1] = '*';
											p[cntr_y + 6][cntr_x - 2] = '*';
											break;
										case 6:
											p[cntr_y + 5][cntr_x] = '*';
											p[cntr_y + 5][cntr_x + 2] = '*';
											p[cntr_y + 5][cntr_x - 2] = '*';
											p[cntr_y + 4][cntr_x - 2] = '*';
											p[cntr_y + 4][cntr_x] = '*';
											p[cntr_y + 4][cntr_x + 2] = '*';
											p[cntr_y + 4][cntr_x + 1] = '*';
											p[cntr_y + 6][cntr_x + 1] = '*';
											p[cntr_y + 6][cntr_x - 1] = '*';
											p[cntr_y + 6][cntr_x] = '*';
											p[cntr_y + 6][cntr_x + 2] = '*';
											p[cntr_y + 6][cntr_x - 2] = '*';
											break;
										case 7:
											p[cntr_y + 5][cntr_x - 2] = '*';
											p[cntr_y + 6][cntr_x - 2] = '*';
											p[cntr_y + 4][cntr_x] = '*';
											p[cntr_y + 4][cntr_x + 2] = '*';
											p[cntr_y + 4][cntr_x - 2] = '*';
											p[cntr_y + 4][cntr_x + 1] = '*';
											p[cntr_y + 4][cntr_x - 1] = '*';
											break;
										case 8:
											p[cntr_y + 5][cntr_x] = '*';
											p[cntr_y + 5][cntr_x + 2] = '*';
											p[cntr_y + 5][cntr_x - 2] = '*';
											p[cntr_y + 4][cntr_x - 2] = '*';
											p[cntr_y + 4][cntr_x + 2] = '*';
											p[cntr_y + 4][cntr_x] = '*';
											p[cntr_y + 4][cntr_x + 1] = '*';
											p[cntr_y + 4][cntr_x - 1] = '*';
											p[cntr_y + 6][cntr_x + 2] = '*';
											p[cntr_y + 6][cntr_x - 2] = '*';
											p[cntr_y + 6][cntr_x] = '*';
											p[cntr_y + 6][cntr_x + 1] = '*';
											p[cntr_y + 6][cntr_x - 1] = '*';
											break;
										case 9:
											p[cntr_y + 5][cntr_x] = '*';
											p[cntr_y + 5][cntr_x + 2] = '*';
											p[cntr_y + 5][cntr_x - 2] = '*';
											p[cntr_y + 4][cntr_x - 2] = '*';
											p[cntr_y + 4][cntr_x + 2] = '*';
											p[cntr_y + 4][cntr_x] = '*';
											p[cntr_y + 4][cntr_x + 1] = '*';
											p[cntr_y + 4][cntr_x - 1] = '*';
											p[cntr_y + 6][cntr_x - 2] = '*';
											p[cntr_y + 6][cntr_x] = '*';
											p[cntr_y + 6][cntr_x + 2] = '*';
											p[cntr_y + 6][cntr_x - 1] = '*';
											break;
										case 0:
											p[cntr_y + 5][cntr_x + 2] = '*';
											p[cntr_y + 5][cntr_x - 2] = '*';
											p[cntr_y + 4][cntr_x - 2] = '*';
											p[cntr_y + 4][cntr_x + 2] = '*';
											p[cntr_y + 4][cntr_x] = '*';
											p[cntr_y + 4][cntr_x + 1] = '*';
											p[cntr_y + 4][cntr_x - 1] = '*';
											p[cntr_y + 6][cntr_x + 2] = '*';
											p[cntr_y + 6][cntr_x - 2] = '*';
											p[cntr_y + 6][cntr_x] = '*';
											p[cntr_y + 6][cntr_x + 1] = '*';
											p[cntr_y + 6][cntr_x - 1] = '*';
											break;
										default:
											break;
									}
									switch (next_num) {
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
								}
								if (sum % 4 == 3) {
									switch (next_num) {
										case 1:
											p[cntr_y + 5][cntr_x] = '*';
											p[cntr_y + 4][cntr_x] = '*';
											p[cntr_y + 3][cntr_x] = '*';
											p[cntr_y + 6][cntr_x] = '*';
											p[cntr_y + 7][cntr_x] = '*';
											break;
										case 2:
											p[cntr_y + 5][cntr_x] = '*';
											p[cntr_y + 5][cntr_x + 1] = '*';
											p[cntr_y + 5][cntr_x - 1] = '*';
											p[cntr_y + 4][cntr_x + 1] = '*';
											p[cntr_y + 3][cntr_x] = '*';
											p[cntr_y + 3][cntr_x + 1] = '*';
											p[cntr_y + 3][cntr_x - 1] = '*';
											p[cntr_y + 6][cntr_x - 1] = '*';
											p[cntr_y + 7][cntr_x] = '*';
											p[cntr_y + 7][cntr_x + 1] = '*';
											p[cntr_y + 7][cntr_x - 1] = '*';
											break;
										case 3:
											p[cntr_y + 5][cntr_x] = '*';
											p[cntr_y + 5][cntr_x + 1] = '*';
											p[cntr_y + 5][cntr_x - 1] = '*';
											p[cntr_y + 4][cntr_x - 1] = '*';
											p[cntr_y + 3][cntr_x] = '*';
											p[cntr_y + 3][cntr_x + 1] = '*';
											p[cntr_y + 3][cntr_x - 1] = '*';
											p[cntr_y + 6][cntr_x - 1] = '*';
											p[cntr_y + 7][cntr_x] = '*';
											p[cntr_y + 7][cntr_x + 1] = '*';
											p[cntr_y + 7][cntr_x - 1] = '*';
											break;
										case 4:
											p[cntr_y + 5][cntr_x] = '*';
											p[cntr_y + 5][cntr_x + 1] = '*';
											p[cntr_y + 5][cntr_x - 1] = '*';
											p[cntr_y + 4][cntr_x - 1] = '*';
											p[cntr_y + 3][cntr_x - 1] = '*';
											p[cntr_y + 6][cntr_x + 1] = '*';
											p[cntr_y + 6][cntr_x - 1] = '*';
											p[cntr_y + 7][cntr_x + 1] = '*';
											p[cntr_y + 7][cntr_x - 1] = '*';
											break;
										case 5:
											p[cntr_y + 5][cntr_x] = '*';
											p[cntr_y + 5][cntr_x + 1] = '*';
											p[cntr_y + 5][cntr_x - 1] = '*';
											p[cntr_y + 4][cntr_x - 1] = '*';
											p[cntr_y + 3][cntr_x] = '*';
											p[cntr_y + 3][cntr_x + 1] = '*';
											p[cntr_y + 3][cntr_x - 1] = '*';
											p[cntr_y + 6][cntr_x + 1] = '*';
											p[cntr_y + 7][cntr_x] = '*';
											p[cntr_y + 7][cntr_x + 1] = '*';
											p[cntr_y + 7][cntr_x - 1] = '*';
											break;
										case 6:
											p[cntr_y + 5][cntr_x] = '*';
											p[cntr_y + 5][cntr_x + 1] = '*';
											p[cntr_y + 5][cntr_x - 1] = '*';
											p[cntr_y + 4][cntr_x - 1] = '*';
											p[cntr_y + 4][cntr_x + 1] = '*';
											p[cntr_y + 3][cntr_x] = '*';
											p[cntr_y + 3][cntr_x + 1] = '*';
											p[cntr_y + 3][cntr_x - 1] = '*';
											p[cntr_y + 6][cntr_x + 1] = '*';
											p[cntr_y + 7][cntr_x] = '*';
											p[cntr_y + 7][cntr_x + 1] = '*';
											p[cntr_y + 7][cntr_x - 1] = '*';
											break;
										case 7:
											p[cntr_y + 5][cntr_x - 1] = '*';
											p[cntr_y + 4][cntr_x - 1] = '*';
											p[cntr_y + 3][cntr_x - 1] = '*';
											p[cntr_y + 6][cntr_x - 1] = '*';
											p[cntr_y + 7][cntr_x - 1] = '*';
											p[cntr_y + 7][cntr_x] = '*';
											p[cntr_y + 7][cntr_x + 1] = '*';
											break;
										case 8:
											p[cntr_y + 5][cntr_x] = '*';
											p[cntr_y + 5][cntr_x + 1] = '*';
											p[cntr_y + 5][cntr_x - 1] = '*';
											p[cntr_y + 4][cntr_x - 1] = '*';
											p[cntr_y + 4][cntr_x + 1] = '*';
											p[cntr_y + 3][cntr_x] = '*';
											p[cntr_y + 3][cntr_x + 1] = '*';
											p[cntr_y + 3][cntr_x - 1] = '*';
											p[cntr_y + 6][cntr_x + 1] = '*';
											p[cntr_y + 6][cntr_x - 1] = '*';
											p[cntr_y + 7][cntr_x] = '*';
											p[cntr_y + 7][cntr_x + 1] = '*';
											p[cntr_y + 7][cntr_x - 1] = '*';
											break;
										case 9:
											p[cntr_y + 5][cntr_x] = '*';
											p[cntr_y + 5][cntr_x + 1] = '*';
											p[cntr_y + 5][cntr_x - 1] = '*';
											p[cntr_y + 4][cntr_x - 1] = '*';
											p[cntr_y + 3][cntr_x] = '*';
											p[cntr_y + 3][cntr_x + 1] = '*';
											p[cntr_y + 3][cntr_x - 1] = '*';
											p[cntr_y + 6][cntr_x + 1] = '*';
											p[cntr_y + 6][cntr_x - 1] = '*';
											p[cntr_y + 7][cntr_x] = '*';
											p[cntr_y + 7][cntr_x + 1] = '*';
											p[cntr_y + 7][cntr_x - 1] = '*';
											break;
										case 0:
											p[cntr_y + 5][cntr_x + 1] = '*';
											p[cntr_y + 5][cntr_x - 1] = '*';
											p[cntr_y + 4][cntr_x - 1] = '*';
											p[cntr_y + 4][cntr_x + 1] = '*';
											p[cntr_y + 3][cntr_x] = '*';
											p[cntr_y + 3][cntr_x + 1] = '*';
											p[cntr_y + 3][cntr_x - 1] = '*';
											p[cntr_y + 6][cntr_x + 1] = '*';
											p[cntr_y + 6][cntr_x - 1] = '*';
											p[cntr_y + 7][cntr_x] = '*';
											p[cntr_y + 7][cntr_x + 1] = '*';
											p[cntr_y + 7][cntr_x - 1] = '*';
											break;
										default:
											break;
									}
									switch (next_num) {
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
								}
							}
							break;
						default:
							continue;
							break;
					}
					cout << "��ת�������Ϊ��";
					current_array(p, h, w);
					break;
				case 27:	//ESC��
					return;
					break;
				default:
					break;
			}
		}
	}

}