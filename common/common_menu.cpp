/* 2251206 ����о �ƿ� */

/* ----------------------------------------------------------------------------------

	 ���ļ����ܣ�
	1���ű� hanoi_main.cpp ���õĲ˵�������Ҫ����ʾ���˵��������ȷ��ѡ��󷵻�

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
int menu(int i)
{
	if (i == 1) {
		cct_cls();
		cout << "---------------------------------" << endl;
		cout << "1.������" << endl;
		cout << "2.������(������¼)" << endl;
		cout << "3.�ڲ�������ʾ(����)" << endl;
		cout << "4.�ڲ�������ʾ(����+����)" << endl;
		cout << "5.ͼ�ν�-Ԥ��-������Բ��" << endl;
		cout << "6.ͼ�ν�-Ԥ��-����ʼ���ϻ�n������" << endl;
		cout << "7.ͼ�ν�-Ԥ��-��һ���ƶ�" << endl;
		cout << "8.ͼ�ν�-�Զ��ƶ��汾" << endl;
		cout << "9.ͼ�ν�-��Ϸ��" << endl;
		cout << "0.�˳�" << endl;
		cout << "---------------------------------" << endl;
		cout << "[��ѡ��:] ";

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
		cct_setcolor(); /* �ָ�Ϊ��ʼ��ɫ */
		cct_setcursor(CURSOR_VISIBLE_NORMAL);//�򿪹��

		cout << "--------------------------------------------" << endl;
		cout << "A.�������ҳ����������ʶ" << endl;
		cout << "B.���������һ���������ֲ�����ʾ��" << endl;
		cout << "C.���������һ�أ��ֲ�����ʾ��" << endl;
		cout << "D.αͼ�ν����������ѡ��һ��ɫ�飨�޷ָ��ߣ�" << endl;
		cout << "E.αͼ�ν����������ѡ��һ��ɫ�飨�зָ��ߣ�" << endl;
		cout << "F.αͼ�ν������һ���������ֲ��裩" << endl;
		cout << "G.αͼ�ν���������" << endl;
		cout << "Q.�˳�" << endl;
		cout << "--------------------------------------------" << endl;
		cout << "[��ѡ��:] ";

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
		cct_setcolor(); /* �ָ�Ϊ��ʼ��ɫ */
		cct_setcursor(CURSOR_VISIBLE_NORMAL);//�򿪹��

		cout << "--------------------------------------------" << endl;
		cout << "1.���������һ�����ֵ���ת" << endl;
		cout << "2.αͼ�ν��������һ�����ֵ�����(�ɼ���)" << endl;
		cout << "3.αͼ�ν��������һ�����ֵ��������ת" << endl;
		cout << "4.αͼ�ν��������һ�����ֵ����й���" << endl;
		cout << "5.αͼ�ν�����ʵ��һ������" << endl;
		cout << "6.αͼ�ν�����������Ϸ" << endl;
		cout << "0.�˳�" << endl;
		cout << "--------------------------------------------" << endl;
		cout << "[��ѡ��:] ";

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