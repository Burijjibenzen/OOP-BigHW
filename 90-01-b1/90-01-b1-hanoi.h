/* 2251206 ����о �ƿ� */
#pragma once

/* ------------------------------------------------------------------------------------------------------

	 ���ļ����ܣ�
	1��Ϊ�˱�֤ hanoi_main.cpp/hanoi_menu.cpp/hanoi_multiple_solutions.cpp ���໥���ʺ����ĺ�������
	2��һ�����ϵ�cpp���õ��ĺ궨�壨#define����ȫ��ֻ����const����������������
	3�����Բο� cmd_console_tools.h ��д���������Ķ�����ᣩ
   ------------------------------------------------------------------------------------------------------ */
#define MAX_LAYER 10

void choice(int choice);
int basic_input(int* layer, char* bgn, char* mid, char* end, int option);//������ʼ��Ŀ�����������뺯��
void hanoi_print(int n, char src, char dst, int option);//��ŵ���е����ѡ���
void initialize(int layer, char src, char tmp, char dst);//��ʼ������
void innerarray(char src, char dst);//�ڲ�����仯
void innerarray_hori_print(int n, char src, char dst, int option);//��ӡ�ڲ����� 348
void hanoi(int n, char src, char tmp, char dst, int option);//��ŵ���ݹ�
void innerarray_verti_print(int n, char src, char dst, int option);//�����ӡ 48
void suspension(int v);//��ʱ
void plate_print_only(int n, char src);//��ӡ����
void move_plate(int n, char src, char dst, int v);//ƽ��

void basic(void);//1
void basic_step_record(void);//2
void innerarray_horizontal(void);//3
void innerarray_hori_verti(void);//4
void column_print_only(void);//5
void column_plate_print(void);//6
void first_move(void);//7
void auto_move(void);//8
void game(void);//9
