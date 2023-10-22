/* 2251206 �ƿ� ����о */
#include <iostream>
#include "../include/cmd_console_tools.h"
#include "../include/common_functions.h"
#include "90-02-b1.h"
#include <Windows.h>
using namespace std;

void menu1()
{
	cct_cls();
	int width, height;
	input(&height, &width, 3);
	char inner_array[26 + 1 + 5 + 1][23];//�ඨ��߽磬ͳһ�±꣬�����Լ����  ��5����Ϊ�洢δ��ʾ��ֵ

	int cntr_x = 0, cntr_y = 0, current_num = get_next_num(true, (unsigned int)time(0));
	generate_array(inner_array, height, width);
	generate_num(inner_array, height, width, cntr_x, cntr_y, current_num, 1);
	current_array(inner_array, height, width);
	int sum = 0;
	rotate1(inner_array, height, width, cntr_x, cntr_y, current_num, sum, 1);
	end();
}

void menu2()
{
	cct_cls();
	int width, height;
	input(&height, &width, 3);
	cct_setconsoleborder(width * 3 * 2 + 40, height * 3 + 6);
	cct_setcursor(CURSOR_INVISIBLE);
	frame(height, width);
	char inner_array[26 + 1 + 5 + 1][23];//�ඨ��һ����ͳһ�±꣬�����Լ����  ��5����Ϊ�洢δ��ʾ��ֵ
	char color_array[26 + 1 + 5 + 1][23];
	int cntr_x = 0, cntr_y = 0;
	int score = 0, line = 0;
	int current_num = get_next_num(true, (unsigned int)time(0));
	int next_num = get_next_num(false, (unsigned int)time(0));
	tips(next_num, 0, 0, width);
	generate_array(inner_array, height, width);
	generate_array(color_array, height, width);

	generate_num(inner_array, height, width, cntr_x, cntr_y, current_num, 2);

	opr(inner_array, color_array, current_num, height, width, cntr_x, cntr_y, score, line, 2);
	current_num = next_num;
	cct_gotoxy(0, height * 3 + 3);
	end();
}

void menu3()
{
	cct_cls();
	int width, height;
	input(&height, &width, 3);
	cct_setconsoleborder(width * 3 * 2 + 40, height * 3 + 6);
	cct_setcursor(CURSOR_INVISIBLE);
	frame(height, width);
	char inner_array[26 + 1 + 5 + 1][23];//�ඨ��һ����ͳһ�±꣬�����Լ����  ��5����Ϊ�洢δ��ʾ��ֵ
	char color_array[26 + 1 + 5 + 1][23];
	int cntr_x = 0, cntr_y = 0;
	int score = 0, line = 0;
	int current_num = get_next_num(true, (unsigned int)time(0));
	int next_num = get_next_num(false, (unsigned int)time(0));
	tips(next_num, 0, 0, width);
	generate_array(inner_array, height, width);
	generate_array(color_array, height, width);

	generate_num(inner_array, height, width, cntr_x, cntr_y, current_num, 3);

	opr(inner_array, color_array, current_num, height, width, cntr_x, cntr_y, score, line, 3);
	current_num = next_num;
	cct_gotoxy(0, height * 3 + 3);
	end();
}

void menu4()
{
	cct_cls();
	int width, height;
	input(&height, &width, 3);
	cct_setconsoleborder(width * 3 * 2 + 40, height * 3 + 6);
	cct_setcursor(CURSOR_INVISIBLE);
	frame(height, width);
	char inner_array[26 + 1 + 5 + 1][23];//�ඨ��һ����ͳһ�±꣬�����Լ���� ��5����Ϊ�洢δ��ʾ��ֵ
	char color_array[26 + 1 + 5 + 1][23];
	int cntr_x = 0, cntr_y = 0;
	int score = 0, line = 0;
	int current_num = get_next_num(true, (unsigned int)time(0));
	current_num = 1;
	int next_num = get_next_num(false, (unsigned int)time(0));
	tips(next_num, 0, 0, width);
	generate_array(inner_array, height, width);
	generate_array(color_array, height, width);
	generate_num(inner_array, height, width, cntr_x, cntr_y, current_num, 4);

	opr(inner_array, color_array, current_num, height, width, cntr_x, cntr_y, score, line, 4);
	current_num = next_num;
	cct_gotoxy(0, height * 3 + 3);
	end();
}

void menu5()
{
	cct_cls();
	int width, height;
	input(&height, &width, 3);
	cct_setconsoleborder(width * 3 * 2 + 40, height * 3 + 6);
	cct_setcursor(CURSOR_INVISIBLE);
	frame(height, width);
	char inner_array[26 + 1 + 5 + 1][23];//�ඨ��һ����ͳһ�±꣬�����Լ���� ��5����Ϊ�洢δ��ʾ��ֵ
	char color_array[26 + 1 + 5 + 1][23];
	generate_array(inner_array, height, width);
	generate_array(color_array, height, width);

	int cntr_x = 0, cntr_y = 0;
	int score = 0, line = 0;
	int current_num = get_next_num(true, (unsigned int)time(0));
	int operate;

	while (1) {
		int next_num = get_next_num(false, (unsigned int)time(0));
		tips(next_num, score, line, width);
		generate_num(inner_array, height, width, cntr_x, cntr_y, current_num, 5);
		//�ڴ˴��ж���û��
		if (death(inner_array, width) == 1)
			break;
		operate = opr(inner_array, color_array, current_num, height, width, cntr_x, cntr_y, score, line, 5);
		tips(next_num, score, line, width);
		if (operate == 1 || operate == 2)
			break;
		current_num = next_num;
	}

	cct_gotoxy(0, height * 3 + 3);
	end();
}

void menu6()
{
	cct_cls();
	int width, height;
	input(&height, &width, 3);
	cct_setconsoleborder(width * 3 * 2 + 40, height * 3 + 6);
	cct_setcursor(CURSOR_INVISIBLE);
	frame(height, width);
	char inner_array[26 + 1 + 5 + 1][23];//�ඨ��һ����ͳһ�±꣬�����Լ���� ��5����Ϊ�洢δ��ʾ��ֵ
	char color_array[26 + 1 + 5 + 1][23];
	generate_array(inner_array, height, width);
	generate_array(color_array, height, width);

	int cntr_x = 0, cntr_y = 0;
	int score = 0, line = 0;
	int current_num = get_next_num(true, (unsigned int)time(0));
	int operate;

	while (1) {
		int next_num = get_next_num(false, (unsigned int)time(0));
		tips(next_num, score, line, width);
		generate_num(inner_array, height, width, cntr_x, cntr_y, current_num, 6);
		//�ڴ˴��ж���û��
		if (death(inner_array, width) == 1)
			break;
		operate = opr(inner_array, color_array, current_num, height, width, cntr_x, cntr_y, score, line, 6);
		if (operate == 1)
			break;
		current_num = next_num;
	}

	cct_gotoxy(0, height * 3 + 3);
	end();
}

int main()
{
	cct_cls();
	cct_setconsoleborder(84, 46);//cmd���ڴ�С
	cct_setfontsize("������", 20);/* ���������壬28���� */
	//cct_showstr(10, 10, "Hello, world!", COLOR_HYELLOW, COLOR_HBLUE);
	cct_setcolor();

	const char* p[7] = { "���������һ�����ֵ���ת",
						"αͼ�ν��������һ�����ֵ�����(�������Ĺ���)",
						"αͼ�ν��������һ�����ֵ��������ת(�������Ĺ���)",
						"αͼ�ν��������һ�����ֵ����й���",
						"αͼ�ν�����ʵ��һ������",
						"αͼ�ν�����������Ϸ",
						"�˳�" };
	const char* choice = "1234560";
	int choose;
	while (1) {
		choose = Menu(p, choice, 7, 3);
		if (choose == 1)
			menu1();
		if (choose == 2)
			menu2();
		if (choose == 3)
			menu3();
		if (choose == 4)
			menu4();
		if (choose == 5)
			menu5();
		if (choose == 6)
			menu6();
		if (choose == 7)
			break;
	}
	for (int i = 0; i < 13; i++)
		cout << endl;
	return 0;
}
