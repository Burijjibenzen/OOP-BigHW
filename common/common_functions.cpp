/* 2251206 ����о �ƿ� */

/* ----------------------------------------------------------------------------------

	 ���ļ�Ҫ��
	1�����������ⲿȫ�ֱ�����const��#define�������Ʒ�Χ�ڣ�
	2���������徲̬ȫ�ֱ�����ȫ�ֱ�����ʹ��׼���ǣ����á����á��ܲ��þ������ã�
	3����̬�ֲ����������������ƣ���ʹ��׼��Ҳ�ǣ����á����á��ܲ��þ�������
	4���������ϵͳͷ�ļ����Զ���ͷ�ļ��������ռ��

   ----------------------------------------------------------------------------------- */
#include "../include/cmd_console_tools.h"
#include "../90-01-b1/90-01-b1-hanoi.h"
#include <iostream>
#include <iomanip>
#include <conio.h>
#include <Windows.h>
using namespace std;

/***************************************************************************
  �������ƣ�
  ��    �ܣ��˵���������ʾ���˵��������ȷ��ѡ��󷵻�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int Menu(const char* p[], const char* chc, int size, int prj)
{
	//��һ��������ָ�����飬��������ʾ���ַ���
	//�ڶ���������һ��ָ�룬ָ�����ŵ��ַ���������"12345670"
	cct_cls();
	cct_setcolor(); /* �ָ�Ϊ��ʼ��ɫ */
	cct_setcursor(CURSOR_VISIBLE_NORMAL);//�򿪹��
	int cmd_y = -1;
	char choice;
	const char* str;
	cout << "--------------------------------------------" << endl;
	for (int i = 0; i < size; i++) {
		cout << *(chc + i) << '.';
		cout << p[i] << endl;
	}
	cout << "--------------------------------------------" << endl;
	cout << "[��ѡ��:] ";

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


/*��������*/
void input(int* row, int* col, int mode)//row h;col w
{
	if (mode == 2) {
		while (1) {
			cout << "����������(8-10)��\n";
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
			cout << "����������(8-10)��\n";
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
			cout << "������߶�(18-26)��\n";
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
			cout << "��������(12-21,��Ϊ3�ı���)��\n";
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

/*��ӡ����*/
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
	cout << "�X�T�[";
	cct_gotoxy(x_star, y_star + 1);
	cout << "�U��U";
	cct_gotoxy(x_star, y_star + 2);
	cout << "�^�T�a";
}