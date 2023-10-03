/* 2251206 ����о �ƿ� */


/* ----------------------------------------------------------------------------------

	 ���ļ����ܣ�
	1����ű� hanoi_main.cpp �и��ݲ˵�����ֵ���õĸ��˵����Ӧ��ִ�к���

	 ���ļ�Ҫ��
	1�����������ⲿȫ�ֱ�����const��#define�������Ʒ�Χ�ڣ�
	2�������徲̬ȫ�ֱ�����������Ҫ��������Ҫ�����ĵ���ʾ��ȫ�ֱ�����ʹ��׼���ǣ����á����á��ܲ��þ������ã�
	3����̬�ֲ����������������ƣ���ʹ��׼��Ҳ�ǣ����á����á��ܲ��þ�������
	4���������ϵͳͷ�ļ����Զ���ͷ�ļ��������ռ��

   ----------------------------------------------------------------------------------- */
#include "../include/cmd_console_tools.h"
#include "./90-01-b1-hanoi.h"
#include <iostream>
#include <iomanip>
#include <conio.h>
#include <Windows.h>
using namespace std;

int v;//��ʱ
int step = 0;//�ܲ���
int topa = 0, topb = 0, topc = 0;//ջ��ָ��
int A[10] = { 0 }, B[10] = { 0 }, C[10] = { 0 };
const int xa = 12, xb = 44, xc = 76;

/***************************************************************************
  �������ƣ�
  ��    �ܣ����ݲ˵�����ֵ���ø��˵����Ӧ��ִ�к���
  ���������
  �� �� ֵ��
  ˵    ����
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
	cout << endl << "���س�������";
	/* ���Գ��س�������������루ע�⣺_getch�Ļس���\r����getchar��\n��*/
	while (_getch() != '\r')
		;

	cct_cls();
	return;
}

/***************************************************************************
	 �������ƣ�
	 ��    �ܣ������������n ������ʼ��src
	 ���������
	 �� �� ֵ��
	 ˵    ����
   ***************************************************************************/
int basic_input(int* layer, char* bgn, char* mid, char* end, int option)
{
	cout << endl;
	while (1) {
		cout << "�����뺺ŵ���Ĳ���(1-10)\n";
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
		cout << "��������ʼ��(A-C)\n";
		cin >> *bgn;//���ܱ�����������ַ���ֻȡ��һ�����������
		cin.ignore(65536, '\n');
		if (*bgn >= 'a' && *bgn <= 'c')
			*bgn -= 32;//Сд���д
		if (*bgn >= 'A' && *bgn <= 'C')
			break;
	}

	while (1) {
		cout << "������Ŀ����(A-C)\n";
		cin >> *end;
		cin.ignore(65536, '\n');
		if (*end >= 'a' && *end <= 'c')
			*end -= 32;//Сд���д
		if (*end == *bgn) {
			cout << "Ŀ����(" << *end << ")��������ʼ��(" << *bgn << ")��ͬ\n";
			continue;
		}
		if (*end >= 'A' && *end <= 'C')
			break;
	}

	*mid = 'A' + 'B' + 'C' - *bgn - *end;

	int velocity;//�ƶ��ٶ�
	if (option == 1) {
		while (1) {
			cout << "�������ƶ��ٶ�(0-5: 0-���س�������ʾ 1-��ʱ� 5-��ʱ���) ";
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
  �������ƣ�
  ��    �ܣ���ʼ������
  ���������
  �� �� ֵ��
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
  �������ƣ�
  ��    �ܣ��ڲ�����仯
  ���������
  �� �� ֵ��
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
  �������ƣ�
  ��    �ܣ��ƶ���ʱ
  ���������
  �� �� ֵ��
  ˵    ����
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
		/* ���Գ��س�������������루ע�⣺_getch�Ļس���\r����getchar��\n��*/
		while (_getch() != '\r')
			;
	}
}

/***************************************************************************
	 �������ƣ�
	 ��    �ܣ���ӡ�ڲ����飨����
	 ���������
	 �� �� ֵ��
	 ˵    ����
   ***************************************************************************/
void innerarray_hori_print(int n, char src, char dst, int option)
{
	if (option == 4)
		cct_gotoxy(0, 17);

	if (option == 8 || option == 9)
		cct_gotoxy(0, 32);

	if (option != 0)
		cout << "��" << setw(4) << ++step << " ��(" << setw(2) << n << "#: " << src << "-->" << dst << ")  ";

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
	 �������ƣ�
	 ��    �ܣ���ӡ�ڲ����飨����
	 ���������
	 �� �� ֵ��
	 ˵    ����
   ***************************************************************************/
void innerarray_verti_print(int n, char src, char dst, int option)
{
	if (option == 4 || option == 8) {
		cct_gotoxy(0, 0);
		cout << "�� " << src << " �ƶ��� " << dst << "���� " << n << " �㣬��ʱ����Ϊ " << v;
	}

	int xa = 11, y = 0, xb = 21, xc = 31, i = 0;
	/*
 ����һ����׼λ�ã����������λ��������
 ���衰A����λ�� BASE_X=10
			  BASE_Y=15
	��B��λ�� BASE_X+10 BASE_Y
	��������ƶ�������ȥ������ά���Ժ�
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

	for (i = 0; i < 10; i++) {//��������á�
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
	 �������ƣ�
	 ��    �ܣ���ŵ���е����ѡ���
	 ���������
	 �� �� ֵ��
	 ˵    ����
   ***************************************************************************/
void hanoi_print(int n, char src, char dst, int option)
{
	if (option == 1)
		cout << n << "# " << src << "---->" << dst << endl;

	if (option == 2)
		cout << "��" << setw(4) << ++step << " ��(" << setw(2) << n << "#: " << src << "-->" << dst << ")" << endl;

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
	 �������ƣ�
	 ��    �ܣ���ŵ���ݹ�
	 ���������
	 �� �� ֵ��
	 ˵    ����
   ***************************************************************************/
void hanoi(int n, char src, char tmp, char dst, int option)
{
	if (n == 1)
		hanoi_print(n, src, dst, option);
	if (n >= 2) {//else
		hanoi(n - 1, src, dst, tmp, option);
		hanoi_print(n, src, dst, option);//n��ʾ������
		hanoi(n - 1, tmp, src, dst, option);
	}
}

/***************************************************************************
	 �������ƣ�
	 ��    �ܣ���ӡ����
	 ���������
	 �� �� ֵ��
	 ˵    ����
   ***************************************************************************/
void plate_print_only(int n, char src)
{
	int y, x, layer;//n��ʾ����,���Ｘ����ܱ�ʾ������
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
	 �������ƣ�
	 ��    �ܣ�ƽ��
	 ���������
	 �� �� ֵ��
	 ˵    ����
   ***************************************************************************/
void move_plate(int n, char src, char dst, int v)//n��ʾ�����̣�һ�����������Ǹ���
{
	suspension(2);
	const int y_bottom = 15;
	int y;
	if (src == 'A') {
		/* ��һ���ַ����������ƶ� */
		for (y = y_bottom - topa - 1; y >= 1; y--) {
			cct_showstr(xa - n, y, " ", n, COLOR_WHITE, 2 * n + 1);

			if (v != 0)
				suspension(v);
			else
				suspension(3);

			if (y >= 2) {
				/* �����ʾ(���һ�α���)���������Ϊ��������ɫ+�ո��ػ�һ��ղŵ�λ�� */
				cct_showch(xa - n, y, ' ', COLOR_BLACK, COLOR_WHITE, 2 * n + 1);
				if (y != 2)
					cct_showch(xa, y, ' ', COLOR_HYELLOW, COLOR_WHITE, 1);
			}
		} //end of for
	}
	if (src == 'B') {
		/* ��һ���ַ����������ƶ� */
		for (y = y_bottom - topb - 1; y >= 1; y--) {
			cct_showstr(xb - n, y, " ", n, COLOR_WHITE, 2 * n + 1);

			if (v != 0)
				suspension(v);
			else
				suspension(3);

			if (y >= 2) {
				/* �����ʾ(���һ�α���)���������Ϊ��������ɫ+�ո��ػ�һ��ղŵ�λ�� */
				cct_showch(xb - n, y, ' ', COLOR_BLACK, COLOR_WHITE, 2 * n + 1);
				if (y != 2)
					cct_showch(xb, y, ' ', COLOR_HYELLOW, COLOR_WHITE, 1);
			}
		} //end of for
	}
	if (src == 'C') {
		/* ��һ���ַ����������ƶ� */
		for (y = y_bottom - topc - 1; y >= 1; y--) {
			cct_showstr(xc - n, y, " ", n, COLOR_WHITE, 2 * n + 1);

			if (v != 0)
				suspension(v);
			else
				suspension(3);

			if (y >= 2) {
				/* �����ʾ(���һ�α���)���������Ϊ��������ɫ+�ո��ػ�һ��ղŵ�λ�� */
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
			/* ��һ���ַ����������ƶ� */
			for (x = xa - n; x <= xb - n; x++) {
				cct_showstr(x, 1, " ", n, COLOR_WHITE, 2 * n + 1);

				if (v != 0)
					suspension(v);
				else
					suspension(3);

				if (x <= xb - n - 1)
					/* �����ʾ(���һ�α���)���������Ϊ��������ɫ+�ո��ػ�һ��ղŵ�λ�� */
					cct_showch(x, 1, ' ', COLOR_BLACK, COLOR_WHITE, 2 * n + 1);

			} //end of for
		}
		else {
			/* ��һ���ַ����������ƶ� */
			for (x = xa - n; x <= xc - n; x++) {
				cct_showstr(x, 1, " ", n, COLOR_WHITE, 2 * n + 1);

				if (v != 0)
					suspension(v);
				else
					suspension(3);

				if (x <= xc - n - 1)
					/* �����ʾ(���һ�α���)���������Ϊ��������ɫ+�ո��ػ�һ��ղŵ�λ�� */
					cct_showch(x, 1, ' ', COLOR_BLACK, COLOR_WHITE, 2 * n + 1);

			} //end of for
		}
	if (src == 'B')
		if (dst == 'A') {
			/* ��һ���ַ����������ƶ� */
			for (x = xb - n; x >= xa - n; x--) {
				cct_showstr(x, 1, " ", n, COLOR_WHITE, 2 * n + 1);

				if (v != 0)
					suspension(v);
				else
					suspension(3);

				if (x >= xa - n + 1)
					/* �����ʾ(���һ�α���)���������Ϊ��������ɫ+�ո��ػ�һ��ղŵ�λ�� */
					cct_showch(x, 1, ' ', COLOR_BLACK, COLOR_WHITE, 2 * n + 1);

			} //end of for
		}
		else {
			/* ��һ���ַ����������ƶ� */
			for (x = xb - n; x <= xc - n; x++) {
				cct_showstr(x, 1, " ", n, COLOR_WHITE, 2 * n + 1);

				if (v != 0)
					suspension(v);
				else
					suspension(3);

				if (x <= xc - n - 1)
					/* �����ʾ(���һ�α���)���������Ϊ��������ɫ+�ո��ػ�һ��ղŵ�λ�� */
					cct_showch(x, 1, ' ', COLOR_BLACK, COLOR_WHITE, 2 * n + 1);

			} //end of for
		}
	if (src == 'C')
		if (dst == 'A') {
			/* ��һ���ַ����������ƶ� */
			for (x = xc - n; x >= xa - n; x--) {
				cct_showstr(x, 1, " ", n, COLOR_WHITE, 2 * n + 1);

				if (v != 0)
					suspension(v);
				else
					suspension(3);

				if (x >= xa - n + 1)
					/* �����ʾ(���һ�α���)���������Ϊ��������ɫ+�ո��ػ�һ��ղŵ�λ�� */
					cct_showch(x, 1, ' ', COLOR_BLACK, COLOR_WHITE, 2 * n + 1);

			} //end of for
		}
		else {
			/* ��һ���ַ����������ƶ� */
			for (x = xc - n; x >= xb - n; x--) {
				cct_showstr(x, 1, " ", n, COLOR_WHITE, 2 * n + 1);

				if (v != 0)
					suspension(v);
				else
					suspension(3);

				if (x >= xb - n + 1)
					/* �����ʾ(���һ�α���)���������Ϊ��������ɫ+�ո��ػ�һ��ղŵ�λ�� */
					cct_showch(x, 1, ' ', COLOR_BLACK, COLOR_WHITE, 2 * n + 1);

			} //end of for
		}
	cct_setcolor(COLOR_BLACK, COLOR_WHITE);

	if (dst == 'A') {
		/* ��һ���ַ����������ƶ� */
		for (y = 1; y <= y_bottom - topa; y++) {
			cct_showstr(xa - n, y, " ", n, COLOR_WHITE, 2 * n + 1);

			if (v != 0)
				suspension(v);
			else
				suspension(3);

			if (y <= y_bottom - topa - 1) {
				/* �����ʾ(���һ�α���)���������Ϊ��������ɫ+�ո��ػ�һ��ղŵ�λ�� */
				cct_showch(xa - n, y, ' ', COLOR_BLACK, COLOR_WHITE, 2 * n + 1);
				if (y >= 3)
					cct_showch(xa, y, ' ', COLOR_HYELLOW, COLOR_WHITE, 1);
			}
		} //end of for
	}
	if (dst == 'B') {
		/* ��һ���ַ����������ƶ� */
		for (y = 1; y <= y_bottom - topb; y++) {
			cct_showstr(xb - n, y, " ", n, COLOR_WHITE, 2 * n + 1);

			if (v != 0)
				suspension(v);
			else
				suspension(3);

			if (y <= y_bottom - topb - 1) {
				/* �����ʾ(���һ�α���)���������Ϊ��������ɫ+�ո��ػ�һ��ղŵ�λ�� */
				cct_showch(xb - n, y, ' ', COLOR_BLACK, COLOR_WHITE, 2 * n + 1);
				if (y >= 3)
					cct_showch(xb, y, ' ', COLOR_HYELLOW, COLOR_WHITE, 1);
			}
		} //end of for
	}
	if (dst == 'C') {
		/* ��һ���ַ����������ƶ� */
		for (y = 1; y <= y_bottom - topc; y++) {
			cct_showstr(xc - n, y, " ", n, COLOR_WHITE, 2 * n + 1);

			if (v != 0)
				suspension(v);
			else
				suspension(3);

			if (y <= y_bottom - topc - 1) {
				/* �����ʾ(���һ�α���)���������Ϊ��������ɫ+�ո��ػ�һ��ղŵ�λ�� */
				cct_showch(xc - n, y, ' ', COLOR_BLACK, COLOR_WHITE, 2 * n + 1);
				if (y >= 3)
					cct_showch(xc, y, ' ', COLOR_HYELLOW, COLOR_WHITE, 1);
			}
		} //end of for
	}
	cct_setcolor(COLOR_BLACK, COLOR_WHITE);
}

/***************************************************************************
	 �������ƣ�
	 ��    �ܣ��ж������Ƿ�Ϸ�
	 ���������
	 �� �� ֵ��
	 ˵    ����
   ***************************************************************************/
int judge(char src, char dst)
{
	if (src == 'A') {
		if (topa == 0) {
			cout << "\nԴ��Ϊ��!";
			suspension(1);
			cct_showstr(0, 35, " ", COLOR_BLACK, COLOR_WHITE, 30);
			cct_showstr(60, 34, " ", COLOR_BLACK, COLOR_WHITE, 20);
			cct_gotoxy(60, 34);
			return 0;
		}
		else {
			if (dst == 'B') {
				if (A[topa - 1] > B[topb - 1] && topb != 0) {
					cout << "\n����ѹС�̣��Ƿ��ƶ�!";
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
					cout << "\n����ѹС�̣��Ƿ��ƶ�!";
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
			cout << "\nԴ��Ϊ��!";
			suspension(1);
			cct_showstr(0, 35, " ", COLOR_BLACK, COLOR_WHITE, 30);
			cct_showstr(60, 34, " ", COLOR_BLACK, COLOR_WHITE, 20);
			cct_gotoxy(60, 34);
			return 0;
		}
		else {
			if (dst == 'A') {
				if (B[topb - 1] > A[topa - 1] && topa != 0) {
					cout << "\n����ѹС�̣��Ƿ��ƶ�!";
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
					cout << "\n����ѹС�̣��Ƿ��ƶ�!";
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
			cout << "\nԴ��Ϊ��!";
			suspension(1);
			cct_showstr(0, 35, " ", COLOR_BLACK, COLOR_WHITE, 30);
			cct_showstr(60, 34, " ", COLOR_BLACK, COLOR_WHITE, 20);
			cct_gotoxy(60, 34);
			return 0;
		}
		else {
			if (dst == 'A') {
				if (C[topc - 1] > A[topa - 1] && topa != 0) {
					cout << "\n����ѹС�̣��Ƿ��ƶ�!";
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
					cout << "\n����ѹС�̣��Ƿ��ƶ�!";
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
	return 0;//����warning
}

/***************************************************************************
	 �������ƣ�
	 ��    �ܣ�������
	 ���������
	 �� �� ֵ��
	 ˵    ����
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
	 �������ƣ�
	 ��    �ܣ�������(����)
	 ���������
	 �� �� ֵ��
	 ˵    ����
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
	 �������ƣ�
	 ��    �ܣ��ڲ�����(����)
	 ���������
	 �� �� ֵ��
	 ˵    ����
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
	 �������ƣ�
	 ��    �ܣ��ڲ�����(����+����)
	 ���������
	 �� �� ֵ��
	 ˵    ����
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
	cout << "��ʼ:  ";
	innerarray_hori_print(n, src, dst, 0);
	suspension(v);

	hanoi(n, src, tmp, dst, 4);
	cct_gotoxy(0, 37);
}

/***************************************************************************
	 �������ƣ�
	 ��    �ܣ���ӡ����
	 ���������
	 �� �� ֵ��
	 ˵    ����
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
	 �������ƣ�
	 ��    �ܣ���ӡ���Ӻ�����
	 ���������
	 �� �� ֵ��
	 ˵    ����
   ***************************************************************************/
void column_plate_print(void)
{
	cout << endl << endl;
	int n;
	char src, tmp, dst;
	basic_input(&n, &src, &tmp, &dst, 0);

	cct_setcursor(CURSOR_INVISIBLE);
	cct_cls();

	cout << "�� " << src << " �ƶ��� " << dst << "���� " << n << " ��";
	column_print_only();
	plate_print_only(n, src);
}

/***************************************************************************
	 �������ƣ�
	 ��    �ܣ���ӡ���Ӻ����Ӽӵ�һ���ƶ�
	 ���������
	 �� �� ֵ��
	 ˵    ����
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

	cout << "�� " << src << " �ƶ��� " << dst << "���� " << n << " ��";
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
	 �������ƣ�
	 ��    �ܣ��Զ��ƶ�
	 ���������
	 �� �� ֵ��
	 ˵    ����
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
	cout << "��ʼ:  ";
	innerarray_hori_print(n, src, dst, 0);
	column_print_only();
	plate_print_only(n, src);
	suspension(v);

	hanoi(n, src, tmp, dst, 8);
}

/***************************************************************************
	 �������ƣ�
	 ��    �ܣ���Ϸ�汾
	 ���������
	 �� �� ֵ��
	 ˵    ����
   ***************************************************************************/
//��cct�����̵Ĵ�������һЩ
void game(void)
{
	cout << endl << endl;
	int n, n0;//n0��n�ı���
	char src, tmp, dst, src0, dst0;//����
	basic_input(&n, &src, &tmp, &dst, 0);
	n0 = n;
	src0 = src;
	dst0 = dst;

	initialize(n, src, tmp, dst);
	cct_setcursor(CURSOR_INVISIBLE);
	cct_cls();

	cout << "�� " << src << " �ƶ��� " << dst << "���� " << n << " ��";
	innerarray_verti_print(n, src, dst, 9);
	cct_gotoxy(0, 32);
	cout << "��ʼ:  ";
	innerarray_hori_print(n, src, dst, 0);
	column_print_only();
	plate_print_only(n, src);

	cct_gotoxy(0, 34);
	cct_setcursor(CURSOR_VISIBLE_NORMAL);
	cout << "�������ƶ�������(������ʽ��AC=A���˵������ƶ���C��Q=�˳�) ��";
	char move[20] = { 0 };
	int i, j, k;
	while (1) {
		cct_setcursor(CURSOR_VISIBLE_NORMAL);
		for (i = 0; i < 20; i++) {

			move[i] = _getch();

			if (move[i] == -32) {//char!!����unsigned char����
				k = _getch();//������� del �������ҵȵ�
			}

			if (move[i] == '\r') {
				//if (move == "AB\r" || move == "AC\r" || move == "BA\r" || move == "BC\r" || move == "CA\r" || move == "CB\r") {ûѧ�ã����������ǵ�ַ
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
					else {//д����
						for (j = 0; j < 20; j++)
							move[j] = 0;
						break;
					}
				}
				else {
					if (move[0] == 'Q' && move[1] == '\r') {
						cout << "\n��Ϸ��ֹ!!!!!";
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
					move[i] -= 32;//Сдת��д
			}
			else {
				move[i] = 0;
				i--;
			}
			if (move[19] != '\0') {//����20�����¶�
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
		innerarray_hori_print(n, src, dst, 9);//������

		move_plate(n, src, dst, 4);

		if (src0 == 'A')
			if (dst0 == 'B') {
				if (topa == 0 && topb == n0) {
					cct_gotoxy(60, 34);
					cout << "\n��Ϸ����!!!!!";
					return;
				}
			}
			else
				if (topa == 0 && topc == n0) {
					cct_gotoxy(60, 34);
					cout << "\n��Ϸ����!!!!!";
					return;
				}
		if (src0 == 'B')
			if (dst0 == 'A') {
				if (topb == 0 && topa == n0) {
					cct_gotoxy(60, 34);
					cout << "\n��Ϸ����!!!!!";
					return;
				}
			}
			else
				if (topb == 0 && topc == n0) {
					cct_gotoxy(60, 34);
					cout << "\n��Ϸ����!!!!!";
					return;
				}
		if (src0 == 'C')
			if (dst0 == 'A') {
				if (topc == 0 && topa == n0) {
					cct_gotoxy(60, 34);
					cout << "\n��Ϸ����!!!!!";
					return;
				}
			}
			else
				if (topc == 0 && topb == n0) {
					cct_gotoxy(60, 34);
					cout << "\n��Ϸ����!!!!!";
					return;
				}

		cct_showstr(60, 34, " ", COLOR_BLACK, COLOR_WHITE, 20);
		cct_gotoxy(60, 34);
	}
}
