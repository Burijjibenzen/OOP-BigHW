/* 2251206 ����о �ƿ� */

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include "../include/cmd_hdc_tools.h"
using namespace std;

#if !HDC_SERIES_BY_TEACHER	//δ���������²Ŵ���������

/* ���������Ҫ��ͷ�ļ� */
#include <cmath>

extern "C" WINBASEAPI HWND WINAPI GetConsoleWindow(); //VS�д˴����в����ߣ���Ӱ������ʹ��

/* �Ѷ���ľ�̬ȫ�ֱ��� */
static HWND hWnd = GetConsoleWindow();
static HDC hdc = NULL;
static const double PI = 3.14159;
static int _BgColor_, _FgColor_, _Width_, _High;
static int _Delay_ms;

/* �����ʶ�ʹ�þ�̬ȫ�ֱ�����������static�����ⲿ���ɼ� */

/* �˴���������Զ��庯����������static�����ⲿ���ɼ� */

static void hdc_convert_angle(int& angle_begin, int& angle_end, int difference, bool isClockWise)
{
	angle_begin += difference;
	angle_end += difference;

	// ֻҪ����С�ڵ���ǰ�ߣ��ͼ�360��ֱ������ǰ��Ϊֹ ˳ʱ��
	if (isClockWise == true)
		while (angle_end <= angle_begin)
			angle_end += 360;
	else
		while (angle_end >= angle_begin)
			angle_end -= 360;
}

/* ��������˼�����������������ʵ�֣���Ҫ�Ķ� */
/***************************************************************************
  �������ƣ�
  ��    �ܣ���ʼ��
  ���������const int bgcolor������ɫ
			const int fgcolor��ǰ��ɫ
			const int width  ����Ļ��ȣ�����
			const int high   ����Ļ�߶ȣ�����
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void hdc_init(const int bgcolor, const int fgcolor, const int width, const int high)
{
	/* ���ͷţ���ֹ��release���ٴ�init��hdc_release�����룩 */
	hdc_release();

	/* ����init����һ����̬ȫ������¼������hdc_cls()���õ� */
	_BgColor_ = bgcolor;
	_FgColor_ = fgcolor;
	_Width_ = width;
	_High = high;

	hdc = GetDC(hWnd);

	cct_setcursor(CURSOR_INVISIBLE);
	cct_setcolor(bgcolor, fgcolor);
	cct_setfontsize("��������", 16);
	cct_setconsoleborder(width / 8 + !!(width % 8), high / 16 + !!(high % 16)); //������Ŀ�ȼ��߶�ת��Ϊ�ض��������������!!�ĺ��壺�������8/16�ı��������ж�+1
	cct_cls();
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ��ͷŻ�ͼ��Դ
  ���������
  �� �� ֵ��
  ˵    ����������
***************************************************************************/
void hdc_release()
{
	if (hdc) {
		ReleaseDC(hWnd, hdc);
		hdc = NULL;
		cct_setcursor(CURSOR_VISIBLE_NORMAL);
	}
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void hdc_set_delay(int ms)
{
	if (ms > 0)
		_Delay_ms = ms;
	else
		_Delay_ms = 0;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ����û�����ɫ������RGBֵ
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void hdc_set_pencolor(const int RGB_value)
{
	SelectObject(hdc, GetStockObject(DC_PEN));
	SetDCPenColor(hdc, RGB_value);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ����û�����ɫ������RGB��ɫ��ֵ0-255
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void hdc_set_pencolor(const unsigned char red, const unsigned char green, const unsigned char blue)
{
	hdc_set_pencolor(RGB(red, green, blue));
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ������Ļ�����е�ͼ��
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void hdc_cls()
{
	/* ����һ��Ҫ��һ����ɫ��ʼ������������ص㣬�ҵ�����㷽����ͬѧ����֪ͨ�� */
	hdc_init(_BgColor_, (_FgColor_ + 1) % 16, _Width_, _High);

	hdc_init(_BgColor_, _FgColor_, _Width_, _High);

	/* ���ֻ���������demoʱ�������hdc_cls()���һ������ȱ�ߵ����������ʱ����
	   ������ֻ������л������⣬���ߴ���ʱֵ */
	Sleep(30);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���(x,y)λ�ô���ָ����ɫ����һ�����ص�
  ���������const int x��x���꣬���Ͻ�Ϊ(0,0)
			const int y��y���꣬���Ͻ�Ϊ(0,0)
  �� �� ֵ��
  ˵    ������ɫֱ���õ�ǰ�趨�������ڵ��ô�ָ��
***************************************************************************/
static inline void hdc_base_point(const int x, const int y)
{
	MoveToEx(hdc, x - 1, y - 1, NULL);
	LineTo(hdc, x, y);
	if (_Delay_ms > 0)
		Sleep(_Delay_ms);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���(x1,y1)-(x2,y2)֮�仭��һ�����ص������
  ���������const int x1�����x���꣬���Ͻ�Ϊ(0,0)
			const int y1�����y���꣬���Ͻ�Ϊ(0,0)
			const int x2���յ�y���꣬���Ͻ�Ϊ(0,0)
			const int y2���յ�y���꣬���Ͻ�Ϊ(0,0)
  �� �� ֵ��
  ˵    ������ɫֱ���õ�ǰ�趨
***************************************************************************/
static inline void hdc_base_line(const int x1, const int y1, const int x2, const int y2)
{
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
	if (_Delay_ms > 0)
		Sleep(_Delay_ms);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���(x,y)λ�ô���ָ����ɫ��һ��ָ����ϸ�ĵ�(�û�ʵ��Բ��ģ��)
  ���������const int x			��x���꣬���Ͻ�Ϊ(0,0)
			const int y			��y���꣬���Ͻ�Ϊ(0,0)
			const int thickness	����Ĵ�ϸ������λ1�����޲���(�����ᵼ�²���ȫ���)����ȱʡֵ��
			const int RGB_value	�������ɫ����ȱʡֵ��
  �� �� ֵ��
  ˵    �����Ľ�����Ч��
***************************************************************************/
void hdc_point(const int x, const int y, const int thickness, const int RGB_value)
{
	int tn = thickness;
	if (tn < 1)
		tn = 1;		//��������
	/* ������ֱ�������ޣ����ǵ����޳���һ����С�ǣ�������Բ����λ��δʵ�� */

	const int tn_end = (tn <= 1) ? 1 : tn / 2;

	int angle, level;
	int old_x1 = INT_MAX, old_y1 = INT_MAX, x1, y1;
	int count = 0;

	if (RGB_value != INVALID_RGB)
		hdc_set_pencolor(RGB_value);

	/* �û�Բ�ķ�ʽģ��ֵ� */
	for (level = 1; level <= tn_end; level++) {
		for (angle = 0; angle <= 360; angle++) {
			/* ע�⣬ϵͳ�������ᣬ0����Բ�����·� */
			x1 = x + (int)(level * sin(angle * PI / 180));
			y1 = y - (int)(level * cos(angle * PI / 180));

			/* ���뾶��Сʱ���Ƕȱ仯��������int�͵�x1/y1�仯����˼��ж���䣬�����ظ���ͬһ���ص� */
			if (x1 != old_x1 || y1 != old_y1) {
				old_x1 = x1;
				old_y1 = y1;
				hdc_base_point(x1, y1);
				++count;
			}
		}
	}
#if 0
	/* �ſ���ע�ͣ����Կ���һ���ֵ����˼������ص���� */
	cct_gotoxy(0, 41);
	printf("count=%d           ", count);
	getchar();
#endif
}

/* -------------------------------------------------------------------------
	�������к�����ʵ�֣���������������׼�Ķ�
	1������Ҫ����ϵͳ�������й�ͼ�β����ĺ���
	2�����к�����ʵ�ֶ�����hdc_base_point/hdc_base_line���������
	3����һ�룬�ǲ������к�������Ҫ����������ʵ�ֹ��̣�Ӧ����ʵ����Щ������
	4�������ʵ������ӵĲ���
	5��ϵͳ�ĽǶ��뺯�������еĽǶȺ������180��
   ------------------------------------------------------------------------- */

   /***************************************************************************
	 �������ƣ�
	 ��    �ܣ����߶�
	 ���������const int x1		������x
			   const int y1		������y
			   const int x2		���յ��x
			   const int y2		���յ��y
			   const int thickness	���߶εĴ�ϸ����ȱʡֵ��
			   const int RGB_value	���߶ε���ɫ����ȱʡֵ��
	 �� �� ֵ��
	 ˵    ���������������û���hdc_point����ϣ��ٶ�����
					 Ҳ������hdc_base_point/hdc_base_line����ϣ��ٶȿ죩
   ***************************************************************************/
void hdc_line(const int x1, const int y1, const int x2, const int y2, const int thickness, const int RGB_value)
{
	int tn = thickness;
	if (tn < 1)
		tn = 1;		//��������

	int level;
	int x_1, y_1, x_2, y_2;

	if (RGB_value != INVALID_RGB)
		hdc_set_pencolor(RGB_value);

	for (level = -tn / 2; level < -tn / 2 + tn; level++) {
		x_1 = x1 + level;
		x_2 = x2 + level;

		hdc_base_line(x_1, y1, x_2, y2);
	}

	for (level = -tn / 2; level < -tn / 2 + tn; level++) {
		y_1 = y1 + level;
		y_2 = y2 + level;

		hdc_base_line(x1, y_1, x2, y_2);
	}
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�������������꣬��һ��������
  ���������const int x1		����1�����x
			const int y1		����1�����y
			const int x2		����2�����x
			const int y2		����2�����y
			const int x3		����3�����x
			const int y3		����3�����y
			bool filled			���Ƿ���Ҫ��䣨��ȱʡֵ��
			const int thickness	���ߵĴ�ϸ����ȱʡֵ��
			const int RGB_value	����ɫ����ȱʡֵ��
  �� �� ֵ��
  ˵    �������ж������Ƿ��ߣ�������ߣ�����һ��ֱ�߼���
***************************************************************************/
void hdc_triangle(const int x1, const int y1, const int x2, const int y2, const int x3, const int y3, bool filled, const int thickness, const int RGB_value)
{
	int startX, endX;
	int x_1 = x1, x_2 = x2, x_3 = x3, y_1 = y1, y_2 = y2, y_3 = y3;

	if (RGB_value != INVALID_RGB)
		hdc_set_pencolor(RGB_value);

	hdc_line(x1, y1, x2, y2, thickness, RGB_value);
	hdc_line(x1, y1, x3, y3, thickness, RGB_value);
	hdc_line(x2, y2, x3, y3, thickness, RGB_value);

	if ((y3 - y2) * (x3 - x2) == (y3 - y1) * (x3 - x1))
		return;

	if (filled == true) {
		if (y_1 > y_2) {
			swap(x_1, x_2);
			swap(y_1, y_2);
		}
		if (y_1 > y_3) {
			swap(x_1, x_3);
			swap(y_1, y_3);
		}
		if (y_2 > y_3) {
			swap(x_2, x_3);
			swap(y_2, y_3);
		} // y1 y2 y3����

		// ����ߵ�б��
		float slope1 = (x_2 - x_1) / (float)(y_2 - y_1);
		float slope2 = (x_3 - x_1) / (float)(y_3 - y_1);
		float slope3 = (x_3 - x_2) / (float)(y_3 - y_2);

		if (y_1 != y_2)
			for (int y = y_1; y <= y_2; y++) {
				// ����ɨ������ߵĽ���
				startX = (int)(x_1 + (y - y_1) * slope1);
				endX = (int)(x_1 + (y - y_1) * slope2);

				// ��佻��֮�������
				hdc_line(startX, y, endX, y, thickness, RGB_value);
			}

		if (y_3 != y_2)
			for (int y = y_2; y <= y_3; y++) {
				// ����ɨ������ߵĽ���
				startX = (int)(x_2 + (y - y_2) * slope3);
				endX = (int)(x_1 + (y - y_1) * slope2);

				// ��佻��֮�������
				hdc_line(startX, y, endX, y, thickness, RGB_value);
			}
	}
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ��������Ͻ����꼰��ȡ��߶ȣ�����һ��������
  ���������const int left_up_x			�����Ͻ�x
			const int left_up_y			�����Ͻ�y
			const int width				�����
			const int high				���߶�
			const int rotation_angles	�������Ͻ�Ϊ֧�㣬��x�����ת��ǣ�����תΪ����
			bool filled					���Ƿ���Ҫ��䣨��ȱʡֵ��
			const int thickness			���ߵĴ�ϸ����ȱʡֵ��
			const int RGB_value			����ɫ����ȱʡֵ��
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void hdc_rectangle(const int left_up_x, const int left_up_y, const int width, const int high, const int rotation_angles, const bool filled, const int thickness, const int RGB_value)
{
	int left_down_x, left_down_y, right_up_x, right_up_y, right_down_x, right_down_y;
	right_up_x = left_up_x + (int)(width * cos(rotation_angles * PI / 180));
	right_up_y = left_up_y + (int)(width * sin(rotation_angles * PI / 180));

	left_down_x = left_up_x + (int)(high * cos((rotation_angles + 90) * PI / 180));
	left_down_y = left_up_y + (int)(high * sin((rotation_angles + 90) * PI / 180));

	right_down_x = left_down_x + (int)(width * cos(rotation_angles * PI / 180));
	right_down_y = left_down_y + (int)(width * sin(rotation_angles * PI / 180));

	hdc_line(left_up_x, left_up_y, right_up_x, right_up_y, thickness, RGB_value);
	hdc_line(right_up_x, right_up_y, right_down_x, right_down_y, thickness, RGB_value);
	hdc_line(right_down_x, right_down_y, left_down_x, left_down_y, thickness, RGB_value);
	hdc_line(left_down_x, left_down_y, left_up_x, left_up_y, thickness, RGB_value);

	if (filled == true) {
		hdc_triangle(left_up_x, left_up_y, right_up_x, right_up_y, right_down_x, right_down_y, true, thickness, RGB_value);
		hdc_triangle(left_up_x, left_up_y, left_down_x, left_down_y, right_down_x, right_down_y, true, thickness, RGB_value);
	}
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ��������Ͻ����꼰�߳�������һ��������
  ���������const int left_up_x			�����Ͻ�x
			const int left_up_y			�����Ͻ�y
			const int length			���߳�
			const int rotation_angles	�������Ͻ�Ϊ֧�㣬��x�����ת��ǣ�����תΪ��������ȱʡֵ��
			const bool filled			���Ƿ���Ҫ��䣨��ȱʡֵ��
			const int thickness			���ߵĴ�ϸ����ȱʡֵ��
			const int RGB_value			����ɫ����ȱʡֵ��
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void hdc_square(const int left_up_x, const int left_up_y, const int length, const int rotation_angles, const bool filled, const int thickness, const int RGB_value)
{
	hdc_rectangle(left_up_x, left_up_y, length, length, rotation_angles, filled, thickness, RGB_value);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ����ո����Ĳ�����һ��Բ��
  ���������const int point_x		��Բ�ĵ�x
			const int point_y		��Բ�ĵ�y
			const int radius		���뾶
			const int angle_begin	����ʼ�Ƕȣ���Բ�����Ϸ�Ϊ0�㣬˳ʱ��Ϊ����ע�⣺��ϵͳ�������180��!!!������ȱʡֵ��
			const int angle_end		�������Ƕȣ�ͬ�ϣ�����ȱʡֵ��
			const int thickness		����ϸ����ȱʡֵ��
			const int RGB_value		����ɫ����ȱʡֵ��
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void hdc_arc(const int point_x, const int point_y, const int radius, const int angle_begin, const int angle_end, const int thickness, const int RGB_value)
{
	int angle_b = angle_begin, angle_e = angle_end, x, y, angle, t_x, t_y;
	hdc_convert_angle(angle_b, angle_e, 180, true);

	if (RGB_value != INVALID_RGB)
		hdc_set_pencolor(RGB_value);

	x = point_x - (int)(radius * sin(angle_b * PI / 180));
	y = point_y + (int)(radius * cos(angle_b * PI / 180));

	hdc_point(x, y, thickness, RGB_value);

	for (angle = angle_b; angle <= angle_e; angle++) {

		t_x = x;
		t_y = y;

		x = point_x - (int)(radius * sin(angle * PI / 180));
		y = point_y + (int)(radius * cos(angle * PI / 180));

		hdc_line(t_x, t_y, x, y, thickness, RGB_value);
	}
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ����ո����Ĳ�����һ������
  ���������const int point_x		��Բ�ĵ�x
			const int point_y		��Բ�ĵ�y
			const int radius		���뾶
			const int angle_begin	����ʼ�Ƕȣ���Բ�����Ϸ�Ϊ0�㣬˳ʱ��Ϊ����ע�⣺��ϵͳ�������180��!!!������ȱʡֵ��
			const int angle_end		�������Ƕȣ�ͬ�ϣ�����ȱʡֵ��
			const bool filled		���Ƿ���Ҫ��䣨��ȱʡֵ��
			const int thickness		����ϸ����ȱʡֵ��
			const int RGB_value		����ɫ����ȱʡֵ��
  ���������
  �� �� ֵ��
  ˵    ��������ʼ/�����ǶȲ�ֵΪ360�ı���ʱ������������
***************************************************************************/
void hdc_sector(const int point_x, const int point_y, const int radius, const int angle_begin, const int angle_end, const bool filled, const int thickness, const int RGB_value)
{
	int angle_b = angle_begin, angle_e = angle_end, x_begin, x_end, y_begin, y_end;
	int x, y;
	double angle;
	hdc_convert_angle(angle_b, angle_e, 180, true);

	if (RGB_value != INVALID_RGB)
		hdc_set_pencolor(RGB_value);

	if (abs(angle_e - angle_b) % 360 != 0) {
		x_begin = point_x - (int)(radius * sin(angle_b * PI / 180));
		y_begin = point_y + (int)(radius * cos(angle_b * PI / 180));
		hdc_line(point_x, point_y, x_begin, y_begin, thickness, RGB_value);
		x_end = point_x - (int)(radius * sin(angle_e * PI / 180));
		y_end = point_y + (int)(radius * cos(angle_e * PI / 180));
		hdc_line(point_x, point_y, x_end, y_end, thickness, RGB_value);
	}

	hdc_arc(point_x, point_y, radius, angle_begin, angle_end, thickness, RGB_value);

	//��������
	/*if (filled == true) {
		x = point_x - (int)(radius * sin(angle_b * PI / 180));
		y = point_y + (int)(radius * cos(angle_b * PI / 180));
		for (angle = angle_b; angle <= angle_e; angle++) {

			t_x = x;
			t_y = y;

			x = point_x - (int)(radius * sin(angle * PI / 180));
			y = point_y + (int)(radius * cos(angle * PI / 180));

			for (level = -tn / 2; level < -tn / 2 + tn; level++)
				hdc_triangle(t_x, t_y, x, y, point_x, point_y, thickness, RGB_value);
		}
	}*/
	//������
	if (filled == true) {
		for (angle = angle_b; angle <= angle_e; angle += 0.1) {

			x = (int)(point_x - (double)(radius * sin(angle * PI / 180)));
			y = (int)(point_y + (double)(radius * cos(angle * PI / 180)));

			hdc_line(point_x, point_y, x, y, thickness + 1, RGB_value);
		}
	}
	//��Բ��
	/*if (filled == true)
		for (level = 1; level <= radius; level ++)
			hdc_arc(point_x, point_y, level, angle_begin, angle_end, thickness, RGB_value);*/

}

/***************************************************************************
  �������ƣ�
  ��    �ܣ����ո����Ĳ�����һ��Բ
  ���������const int point_x		��Բ�ĵ�x
			const int point_y		��Բ�ĵ�y
			const int radius		���뾶
			const bool filled		���Ƿ���Ҫ��䣨��ȱʡֵ��
			const int thickness		����ϸ����ȱʡֵ��
			const int RGB_value		����ɫ����ȱʡֵ��
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void hdc_circle(const int point_x, const int point_y, const int radius, const bool filled, const int thickness, const int RGB_value)
{
	//hdc_sector(point_x, point_y, radius, 0, 0, filled, thickness, RGB_value);
	int x, y;
	double angle;

	if (RGB_value != INVALID_RGB)
		hdc_set_pencolor(RGB_value);

	hdc_arc(point_x, point_y, radius, 0, 360, thickness, RGB_value);

	if (filled == true) {
		for (angle = 180; angle <= 360; angle += 0.1) {

			x = (int)(point_x - (double)(radius * sin(angle * PI / 180)));
			y = (int)(point_y + (double)(radius * cos(angle * PI / 180)));

			hdc_line(point_x * 2 - x, y, x, y, thickness + 1, RGB_value);
		}
	}
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ����ո����Ĳ�����һ����Բ
  ���������const int point_x			��Բ�ĵ�x
			const int point_y			��Բ�ĵ�y
			const int radius_a			��ƽ����X��İ뾶
			const int radius_b			��ƽ����Y��İ뾶
			const int rotation_angles	����Բ��Ϊ֧�㣬��x�����ת��ǣ�����תΪ��������ȱʡֵ��
			const bool filled			���Ƿ���Ҫ��䣨��ȱʡֵ��
			const int thickness			����ϸ����ȱʡֵ��
			const int RGB_value			����ɫ����ȱʡֵ��
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void hdc_ellipse(const int point_x, const int point_y, const int radius_a, const int radius_b, const int rotation_angles, const bool filled, const int thickness, const int RGB_value)
{
	int current_x, current_y, new_x, new_y, x, y;
	double angle;

	if (RGB_value != INVALID_RGB)
		hdc_set_pencolor(RGB_value);

	/*distance = radius_a;//��ʼ����

	x = point_x + (int)(distance * cos(rotation_angles * PI / 180));//��׼��Բ�����Ǳ�׼���������Բ�ĳ�ʼλ�õ��Ҷ���
	y = point_y + (int)(distance * sin(rotation_angles * PI / 180));

	for (angle = 0; angle <= 360; angle++) {

		current_x = x;
		current_y = y;

		x_fix = point_x + (int)(radius_a * cos(angle * PI / 180));
		y_fix = point_y + (int)(radius_b * sin(angle * PI / 180)); //��׼��Բ�ϵĵ����꣬Ϊfix

		distance = sqrt((x_fix - point_x) * (x_fix - point_x) + (y_fix - point_y) * (y_fix - point_y));//��׼��Բ�ϵ㵽Բ�ĵľ���

		x = point_x + (int)(distance * cos((rotation_angles + angle) * PI / 180));//��distanceΪ�뾶������תrotation_angles�Ƕȣ��õ���ת��
		y = point_y + (int)(distance * sin((rotation_angles + angle) * PI / 180));

		hdc_line(current_x, current_y, x, y, thickness, RGB_value);
		//�������distance���ǲ��ԣ�Ϊʲô������Ϊ����任����rotation_angles + angle��������ת�ǣ�angle�ĳ�arctan(bsin angle/acos angle)
	}*/

	for (angle = 0; angle <= 360; angle++) {
		current_x = point_x + (int)(radius_a * cos(angle * PI / 180) * cos(rotation_angles * PI / 180) - radius_b * sin(angle * PI / 180) * sin(rotation_angles * PI / 180));
		current_y = point_y + (int)(radius_b * sin(angle * PI / 180) * cos(rotation_angles * PI / 180) + radius_a * cos(angle * PI / 180) * sin(rotation_angles * PI / 180));

		new_x = point_x + (int)(radius_a * cos((angle + 1) * PI / 180) * cos(rotation_angles * PI / 180) - radius_b * sin((angle + 1) * PI / 180) * sin(rotation_angles * PI / 180));
		new_y = point_y + (int)(radius_b * sin((angle + 1) * PI / 180) * cos(rotation_angles * PI / 180) + radius_a * cos((angle + 1) * PI / 180) * sin(rotation_angles * PI / 180));

		hdc_line(current_x, current_y, new_x, new_y, thickness, RGB_value);
	}

	if (filled == true) {
		for (angle = 0; angle <= 360; angle += 0.4) {

			x = point_x + (int)(radius_a * cos(angle * PI / 180) * cos(rotation_angles * PI / 180) - radius_b * sin(angle * PI / 180) * sin(rotation_angles * PI / 180));
			y = point_y + (int)(radius_b * sin(angle * PI / 180) * cos(rotation_angles * PI / 180) + radius_a * cos(angle * PI / 180) * sin(rotation_angles * PI / 180));

			hdc_line(point_x, point_y, x, y, thickness + 1, RGB_value);
		}
	}
}

#endif !HDC_SERIES_BY_TEACHER