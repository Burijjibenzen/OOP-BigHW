/* 2251206 计科 冯羽芯 */
#include <iostream>
#include "../include/cmd_console_tools.h"
#include "../include/common_menu.h"
#include "90-02-b1.h"
#include <Windows.h>
using namespace std;

void menu1()
{
	cct_cls();
	int width, height;
	input(&height, &width);
	char inner_array[26 + 1 + 5 + 1][22];//多定义一个，统一下标，方便自己理解 加5是因为一点点下落，有一个逐步的过程

	int cntr_x = 0, cntr_y = 0, current_num = get_next_num(true, (unsigned int)time(0));
	generate_array(inner_array, height, width);
	generate_num(inner_array, height, width, cntr_x, cntr_y, current_num, 1);
	current_array(inner_array, height, width);
	rotate(inner_array, height, width, cntr_x, cntr_y, current_num);
	end();
}

void menu2()
{
	cct_cls();
	int width, height;
	input(&height, &width);
	cct_setconsoleborder(width * 3 * 2 + 40, height * 3 + 6);
	cct_setcursor(CURSOR_INVISIBLE);
	frame(height, width);
	char inner_array[26 + 1 + 5 + 1][22];//多定义一个，统一下标，方便自己理解 加5是因为一点点下落，有一个逐步的过程
	int cntr_x = 0, cntr_y = 0;
	int current_num = get_next_num(true, (unsigned int)time(0));
	int next_num = get_next_num(false, (unsigned int)time(0));
	tips(next_num, 0, 0, width);
	generate_array(inner_array, height, width);
	generate_num(inner_array, height, width, cntr_x, cntr_y, current_num, 2);

	opr(inner_array, current_num, height, width, cntr_x, cntr_y, 0, 2);
	current_num = next_num;
	cct_gotoxy(width * 6 + 10, 7);
	end();
}

void menu3()
{

}

void menu4()
{

}

void menu5()
{

}

void menu6()
{

}

int main()
{
	cct_cls();
	cct_setconsoleborder(84, 46);//cmd窗口大小
	cct_setfontsize("新宋体", 20);/* 设置新宋体，28点阵 */
	//cct_showstr(10, 10, "Hello, world!", COLOR_HYELLOW, COLOR_HBLUE);
	cct_setcolor();

	int choose;
	while (1) {
		choose = menu(3);
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
		if (choose == 0)
			break;
	}
	for (int i = 0; i < 13; i++)
		cout << endl;
	return 0;
}
