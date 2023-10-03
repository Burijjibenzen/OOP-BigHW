/* 2251206 冯羽芯 计科 */
#pragma once

/* ------------------------------------------------------------------------------------------------------

	 本文件功能：
	1、为了保证 hanoi_main.cpp/hanoi_menu.cpp/hanoi_multiple_solutions.cpp 能相互访问函数的函数声明
	2、一个以上的cpp中用到的宏定义（#define）或全局只读（const）变量，个数不限
	3、可以参考 cmd_console_tools.h 的写法（认真阅读并体会）
   ------------------------------------------------------------------------------------------------------ */
#define MAX_LAYER 10

void choice(int choice);
int basic_input(int* layer, char* bgn, char* mid, char* end, int option);//层数起始柱目标柱共用输入函数
void hanoi_print(int n, char src, char dst, int option);//汉诺塔中的输出选项函数
void initialize(int layer, char src, char tmp, char dst);//初始化数组
void innerarray(char src, char dst);//内部数组变化
void innerarray_hori_print(int n, char src, char dst, int option);//打印内部数组 348
void hanoi(int n, char src, char tmp, char dst, int option);//汉诺塔递归
void innerarray_verti_print(int n, char src, char dst, int option);//纵向打印 48
void suspension(int v);//延时
void plate_print_only(int n, char src);//打印盘子
void move_plate(int n, char src, char dst, int v);//平移

void basic(void);//1
void basic_step_record(void);//2
void innerarray_horizontal(void);//3
void innerarray_hori_verti(void);//4
void column_print_only(void);//5
void column_plate_print(void);//6
void first_move(void);//7
void auto_move(void);//8
void game(void);//9
