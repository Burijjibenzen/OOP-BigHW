//2251206 ����о �ƿ�
#include <iostream>
#include "../include/cmd_console_tools.h"
#include "./90-01-b2.h"
#include "../include/common_functions.h"
#include <conio.h>
#include <Windows.h>
using namespace std;

void menu_A(void)
{
	cct_cls();
	int row, col;
	input(&row, &col, 2);

	int inner_array[12][12] = { 0 };
	generate_array(inner_array, row, col);
	current_array(inner_array, row, col);

	char coordinate[3];//���һ��װ�س�
	coordinate_input(coordinate, inner_array, row, col);

	int x_crd = coordinate[0] - 'A' + 1, y_crd = coordinate[1] - '0' + 1;
	char result[12][12] = { 0 };
	int i, j;
	for (i = 1; i <= row; i++)
		for (j = 1; j <= col; j++)
			result[i][j] = '0';
	same_array(x_crd, y_crd, result, inner_array);
	result_array(result, row, col);
	cout << endl;
	color_array(result, inner_array, row, col);

	end();
	return;
}

void menu_B(void)
{
	cct_cls();
	int row, col, total = 0;
	input(&row, &col, 2);

	int inner_array[12][12] = { 0 };
	generate_array(inner_array, row, col);
	current_array(inner_array, row, col);

	char coordinate[3] = { 0 };
	coordinate_input(coordinate, inner_array, row, col);

	int x_crd = coordinate[0] - 'A' + 1, y_crd = coordinate[1] - '0' + 1;
	char result[12][12] = { 0 };
	int i, j;
	for (i = 1; i <= row; i++)
		for (j = 1; j <= col; j++)
			result[i][j] = '0';
	same_array(x_crd, y_crd, result, inner_array);
	result_array(result, row, col);
	cout << endl;
	color_array(result, inner_array, row, col);

	char option;
	option = confirm(coordinate);
	cout << endl << endl;
	if (option == 'n' || option == 'N' || option == 'Q' || option == 'q') {
		end();
		return;
	}
	if (option == 'y' || option == 'Y') {
		vanish_array(result, inner_array, row, col);
		color_vanish_array(result, inner_array, row, col);
		SCORE(result, row, col, &total);
		wait_for_enter("���س������������������...");
		fall_array(inner_array, row, col);
		print_fall_array(result, inner_array, row, col);
		cout << endl;
		end();
		return;
	}
}

void menu_C(void)
{
	cct_cls();
	int row, col, total = 0;
	input(&row, &col, 2);

	int inner_array[12][12] = { 0 };
	generate_array(inner_array, row, col);

	while (1) {
		current_array(inner_array, row, col);

		if (over(inner_array, row, col) != 0) {
			cct_setcolor(COLOR_HYELLOW, COLOR_RED);
			cout << "ʣ��" << over(inner_array, row, col) << "��������������ؽ�����";
			cct_setcolor();
			cout << endl;
			cout << endl;
			end();
			return;
		}

		char coordinate[3];//���һ��װ�س�
		coordinate_input(coordinate, inner_array, row, col);

		int x_crd = coordinate[0] - 'A' + 1, y_crd = coordinate[1] - '0' + 1;
		char result[12][12] = { 0 };
		int i, j;
		for (i = 1; i <= row; i++)
			for (j = 1; j <= col; j++)
				result[i][j] = '0';
		same_array(x_crd, y_crd, result, inner_array);
		result_array(result, row, col);
		cout << endl;
		color_array(result, inner_array, row, col);

		char option;
		option = confirm(coordinate);
		cout << endl << endl;
		if (option == 'Q' || option == 'q') {
			end();
			return;
		}
		if (option == 'y' || option == 'Y') {
			vanish_array(result, inner_array, row, col);
			color_vanish_array(result, inner_array, row, col);
			SCORE(result, row, col, &total);
			wait_for_enter("���س������������������...");
			fall_array(inner_array, row, col);
			print_fall_array(result, inner_array, row, col);
			wait_for_enter("�����������������س���������һ�ε�����...");
			cout << endl;
		}
		if (option == 'n' || option == 'N')
			continue;
	}
}

void menu_D(void)
{
	cct_cls();
	int row, col, total = 0;
	input(&row, &col, 2);
	int inner_array[12][12] = { 0 };
	generate_array(inner_array, row, col);

	cct_cls();
	screen_set(col * 7 - (col - 7), row * 4 - (row - 8));
	frame(row, col, 0);
	color_block(inner_array, row, col, 0);
	MouseKey(inner_array, row, col, 0, 'd', &total);
}

void menu_E(void)
{
	cct_cls();
	int row, col, total = 0;
	input(&row, &col, 2);
	int inner_array[12][12] = { 0 };
	generate_array(inner_array, row, col);

	cct_cls();
	screen_set(col * 8 + 5, row * 5 - (row - 7));
	frame(row, col, 1);
	color_block(inner_array, row, col, 1);
	MouseKey(inner_array, row, col, 1, 'e', &total);
}

void menu_F(void)
{
	cct_cls();
	int row, col, total = 0;
	input(&row, &col, 2);
	int inner_array[12][12] = { 0 };
	generate_array(inner_array, row, col);

	cct_cls();
	screen_set(col * 7 - (col - 7), row * 4 - (row - 8));
	frame(row, col, 0);
	color_block(inner_array, row, col, 0);
	MouseKey(inner_array, row, col, 0, 'f', &total);
}

void menu_G(void)
{
	cct_cls();
	int row, col, total = 0;
	input(&row, &col, 2);
	int inner_array[12][12] = { 0 };
	while (1) {
		generate_array(inner_array, row, col);
		cct_cls();
		screen_set(col * 8 + 5, row * 5 - (row - 7));
		frame(row, col, 1);
		color_block(inner_array, row, col, 1);
		if (MouseKey(inner_array, row, col, 1, 'g', &total) == 0)
			return;
	}
}

int main()
{
	cct_setcolor();
	cct_setconsoleborder(84, 46);//cmd���ڴ�С
	cct_setfontsize("������", 28);/* ���������壬28���� */

	const char* p[8] = { "�������ҳ����������ʶ",
						"���������һ���������ֲ�����ʾ��",
						"���������һ�أ��ֲ�����ʾ��",
						"αͼ�ν����������ѡ��һ��ɫ�飨�޷ָ��ߣ�",
						"αͼ�ν����������ѡ��һ��ɫ�飨�зָ��ߣ�",
						"αͼ�ν������һ���������ֲ��裩",
						"αͼ�ν���������",
						"�˳�" };
	const char* choice = "ABCDEFGQabcdefgq";

	int choose;
	while (1) {
		choose = Menu(p, choice, 8, 2);
		if (choose == 1 || choose == 9)
			menu_A();
		if (choose == 2 || choose == 10)
			menu_B();
		if (choose == 3 || choose == 11)
			menu_C();
		if (choose == 4 || choose == 12)
			menu_D();
		if (choose == 5 || choose == 13)
			menu_E();
		if (choose == 6 || choose == 14)
			menu_F();
		if (choose == 7 || choose == 15)
			menu_G();
		if (choose == 8 || choose == 16)
			break;
	}
	for (int i = 0; i < 13; i++)
		cout << endl;
	return 0;
}