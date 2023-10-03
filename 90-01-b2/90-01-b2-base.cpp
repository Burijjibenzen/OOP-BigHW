//2251206 ����о ��06
#include <iostream>
#include "../include/cmd_console_tools.h"
#include "./90-01-b2.h"
#include <conio.h>
using namespace std;

/*��ӡ��ǰ����*/
void current_array(int p[][12], int& r, int& c)
{
	cout << "��ǰ���飺\n";
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

/*��������*/
void coordinate_input(char* coordinate, int p[][12], int& r, int& c)
{
	int X, Y;
	//cin.ignore();�������ֵ�ﵽ a ���߱��������ַ��� ch ����cin.ignore() ����ִ����ֹ�������������ȴ���
	//Ӧ����ǰ����ջ�������������������
	while (1) {
		cout << "������ĸ+������ʽ[����c2]����������꣺";
		cct_getxy(X, Y);//ȡ��ǰ���λ��
		cin.get(coordinate, 3, '\n');//�������ջ��������س�һֱ���ţ���ѭ����cin.getline���������Ƚϸ���,cin���fail��
		/* https://blog.csdn.net/weixin_40064300/article/details/128191604 */
		cin.clear();
		cin.ignore(65536, '\n');

		if (coordinate[0] >= 'a' && coordinate[0] <= 'a' + r - 1)
			coordinate[0] -= 32;
		if ((coordinate[0] >= 'A') && (coordinate[0] <= 'A' + r - 1) && (coordinate[1] >= '0') && (coordinate[1] <= c - 1 + '0')) {
			cout << "����Ϊ" << coordinate[0] << "��" << coordinate[1] << "��\n";
			if (p[coordinate[0] - 'A' + 1][coordinate[1] - '0' + 1] != p[coordinate[0] - 'A'][coordinate[1] - '0' + 1]
				&& p[coordinate[0] - 'A' + 1][coordinate[1] - '0' + 1] != p[coordinate[0] - 'A' + 2][coordinate[1] - '0' + 1]
				&& p[coordinate[0] - 'A' + 1][coordinate[1] - '0' + 1] != p[coordinate[0] - 'A' + 1][coordinate[1] - '0']
				&& p[coordinate[0] - 'A' + 1][coordinate[1] - '0' + 1] != p[coordinate[0] - 'A' + 1][coordinate[1] - '0' + 2]) {
				cout << "����ľ�������λ�ô���������ֵͬ������������\n";
				cout << endl;
				continue;
			}
			else if (p[coordinate[0] - 'A' + 1][coordinate[1] - '0' + 1] == 0) {
				cout << "����ľ�������λ��Ϊ0���Ƿ�λ�ã�������������\n";
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
			cout << "�����������������.";
			cct_gotoxy(0, Y);
			continue;
		}
	}
	cout << endl;
}

/*��ǰ����(��ͬɫ��ʶ)*/
void color_array(char result[][12], int p[][12], int& r, int& c)
{
	cout << "��ǰ����(��ͬɫ��ʶ)��\n";
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

/*���ҽ������*/
void result_array(char result[][12], int& r, int& c)
{
	cout << "���ҽ�����飺\n";
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

/*ȷ���Ƿ����ֵͬ����*/
char confirm(char* coordinate)
{
	cout << "��ȷ���Ƿ��" <<coordinate<< "����Χ����ֵͬ����(Y/N/Q)��";
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

/*��ֵͬ�鲢�������(��ͬɫ��ʶ)*/
void color_vanish_array(char result[][12], int p[][12], int& r, int& c)
{
	cout << "��ֵͬ�鲢�������(��ͬɫ��ʶ)��\n";
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

/*��ӡ����������*/
void print_fall_array(char result[][12], int p[][12], int& r, int& c)
{
	cout << "���������飺\n";
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