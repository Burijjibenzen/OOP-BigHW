/* 2251206 冯羽芯 计科 */

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include "../include/cmd_hdc_tools.h"
using namespace std;

#if !HDC_SERIES_BY_TEACHER	//未定义的情况下才打开条件编译

/* 允许添加需要的头文件 */
#include <cmath>

extern "C" WINBASEAPI HWND WINAPI GetConsoleWindow(); //VS中此处会有波浪线，不影响正常使用

/* 已定义的静态全局变量 */
static HWND hWnd = GetConsoleWindow();
static HDC hdc = NULL;
static const double PI = 3.14159;
static int _BgColor_, _FgColor_, _Width_, _High;
static int _Delay_ms;

/* 允许适度使用静态全局变量，但仅限static，即外部不可见 */

/* 此处允许添加自定义函数，但仅限static，即外部不可见 */

static void hdc_convert_angle(int& angle_begin, int& angle_end, int difference, bool isClockWise)
{
	angle_begin += difference;
	angle_end += difference;

	// 只要后者小于等于前者，就加360，直到大于前者为止 顺时针
	if (isClockWise == true)
		while (angle_end <= angle_begin)
			angle_end += 360;
	else
		while (angle_end >= angle_begin)
			angle_end -= 360;
}

/* 下面给出了几个基本函数的完整实现，不要改动 */
/***************************************************************************
  函数名称：
  功    能：初始化
  输入参数：const int bgcolor：背景色
			const int fgcolor：前景色
			const int width  ：屏幕宽度（点阵）
			const int high   ：屏幕高度（点阵）
  返 回 值：
  说    明：
***************************************************************************/
void hdc_init(const int bgcolor, const int fgcolor, const int width, const int high)
{
	/* 先释放，防止不release而再次init（hdc_release可重入） */
	hdc_release();

	/* 窗口init后，用一个静态全局量记录，后续hdc_cls()会用到 */
	_BgColor_ = bgcolor;
	_FgColor_ = fgcolor;
	_Width_ = width;
	_High = high;

	hdc = GetDC(hWnd);

	cct_setcursor(CURSOR_INVISIBLE);
	cct_setcolor(bgcolor, fgcolor);
	cct_setfontsize("点阵字体", 16);
	cct_setconsoleborder(width / 8 + !!(width % 8), high / 16 + !!(high % 16)); //将点阵的宽度及高度转换为特定字体的行列数，!!的含义：如果不是8/16的倍数，行列多+1
	cct_cls();
}

/***************************************************************************
  函数名称：
  功    能：释放画图资源
  输入参数：
  返 回 值：
  说    明：可重入
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
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void hdc_set_delay(int ms)
{
	if (ms > 0)
		_Delay_ms = ms;
	else
		_Delay_ms = 0;
}

/***************************************************************************
  函数名称：
  功    能：设置画笔颜色，传入RGB值
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void hdc_set_pencolor(const int RGB_value)
{
	SelectObject(hdc, GetStockObject(DC_PEN));
	SetDCPenColor(hdc, RGB_value);
}

/***************************************************************************
  函数名称：
  功    能：设置画笔颜色，传入RGB三色，值0-255
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void hdc_set_pencolor(const unsigned char red, const unsigned char green, const unsigned char blue)
{
	hdc_set_pencolor(RGB(red, green, blue));
}

/***************************************************************************
  函数名称：
  功    能：清除屏幕上现有的图形
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void hdc_cls()
{
	/* 发现一定要换一种颜色初始化才能清除像素点，找到更简便方法的同学可以通知我 */
	hdc_init(_BgColor_, (_FgColor_ + 1) % 16, _Width_, _High);

	hdc_init(_BgColor_, _FgColor_, _Width_, _High);

	/* 部分机器上运行demo时，会出现hdc_cls()后第一根线有缺线的情况，加延时即可
	   如果部分机器运行还有问题，调高此延时值 */
	Sleep(30);
}

/***************************************************************************
  函数名称：
  功    能：在(x,y)位置处用指定颜色画出一个像素点
  输入参数：const int x：x坐标，左上角为(0,0)
			const int y：y坐标，左上角为(0,0)
  返 回 值：
  说    明：颜色直接用当前设定，可以在调用处指定
***************************************************************************/
static inline void hdc_base_point(const int x, const int y)
{
	MoveToEx(hdc, x - 1, y - 1, NULL);
	LineTo(hdc, x, y);
	if (_Delay_ms > 0)
		Sleep(_Delay_ms);
}

/***************************************************************************
  函数名称：
  功    能：在(x1,y1)-(x2,y2)之间画出一个像素点的连线
  输入参数：const int x1：起点x坐标，左上角为(0,0)
			const int y1：起点y坐标，左上角为(0,0)
			const int x2：终点y坐标，左上角为(0,0)
			const int y2：终点y坐标，左上角为(0,0)
  返 回 值：
  说    明：颜色直接用当前设定
***************************************************************************/
static inline void hdc_base_line(const int x1, const int y1, const int x2, const int y2)
{
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
	if (_Delay_ms > 0)
		Sleep(_Delay_ms);
}

/***************************************************************************
  函数名称：
  功    能：在(x,y)位置处用指定颜色画一个指定粗细的点(用画实心圆来模拟)
  输入参数：const int x			：x坐标，左上角为(0,0)
			const int y			：y坐标，左上角为(0,0)
			const int thickness	：点的粗细，下限位1，上限不限(如过大会导致不完全填充)（有缺省值）
			const int RGB_value	：点的颜色（有缺省值）
  返 回 值：
  说    明：改进运行效率
***************************************************************************/
void hdc_point(const int x, const int y, const int thickness, const int RGB_value)
{
	int tn = thickness;
	if (tn < 1)
		tn = 1;		//处理下限
	/* 不卡点直径的上限，但是单上限超过一定大小是，画出的圆部分位置未实心 */

	const int tn_end = (tn <= 1) ? 1 : tn / 2;

	int angle, level;
	int old_x1 = INT_MAX, old_y1 = INT_MAX, x1, y1;
	int count = 0;

	if (RGB_value != INVALID_RGB)
		hdc_set_pencolor(RGB_value);

	/* 用画圆的方式模拟粗点 */
	for (level = 1; level <= tn_end; level++) {
		for (angle = 0; angle <= 360; angle++) {
			/* 注意，系统的坐标轴，0°在圆的最下方 */
			x1 = x + (int)(level * sin(angle * PI / 180));
			y1 = y - (int)(level * cos(angle * PI / 180));

			/* 当半径很小时，角度变化不会引起int型的x1/y1变化，因此加判断语句，避免重复画同一像素点 */
			if (x1 != old_x1 || y1 != old_y1) {
				old_x1 = x1;
				old_y1 = y1;
				hdc_base_point(x1, y1);
				++count;
			}
		}
	}
#if 0
	/* 放开此注释，可以看到一个粗点用了几个像素点组成 */
	cct_gotoxy(0, 41);
	printf("count=%d           ", count);
	getchar();
#endif
}

/* -------------------------------------------------------------------------
	给出下列函数的实现，函数名及参数表不准改动
	1、不需要调用系统的其他有关图形操作的函数
	2、下列函数的实现都基于hdc_base_point/hdc_base_line函数的组合
	3、想一想，是不是所有函数都需要给出独立的实现过程？应该先实现哪些函数？
	4、填充是实现中最复杂的部分
	5、系统的角度与函数参数中的角度含义相差180°
   ------------------------------------------------------------------------- */

   /***************************************************************************
	 函数名称：
	 功    能：画线段
	 输入参数：const int x1		：起点的x
			   const int y1		：起点的y
			   const int x2		：终点的x
			   const int y2		：终点的y
			   const int thickness	：线段的粗细（有缺省值）
			   const int RGB_value	：线段的颜色（有缺省值）
	 返 回 值：
	 说    明：本函数可以用基于hdc_point的组合（速度慢）
					 也可以用hdc_base_point/hdc_base_line的组合（速度快）
   ***************************************************************************/
void hdc_line(const int x1, const int y1, const int x2, const int y2, const int thickness, const int RGB_value)
{
	int tn = thickness;
	if (tn < 1)
		tn = 1;		//处理下限

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
  函数名称：
  功    能：给出三点的坐标，画一个三角形
  输入参数：const int x1		：第1个点的x
			const int y1		：第1个点的y
			const int x2		：第2个点的x
			const int y2		：第2个点的y
			const int x3		：第3个点的x
			const int y3		：第3个点的y
			bool filled			：是否需要填充（有缺省值）
			const int thickness	：边的粗细（有缺省值）
			const int RGB_value	：颜色（有缺省值）
  返 回 值：
  说    明：不判断三点是否共线，如果共线，划出一条直线即可
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
		} // y1 y2 y3递增

		// 计算边的斜率
		float slope1 = (x_2 - x_1) / (float)(y_2 - y_1);
		float slope2 = (x_3 - x_1) / (float)(y_3 - y_1);
		float slope3 = (x_3 - x_2) / (float)(y_3 - y_2);

		if (y_1 != y_2)
			for (int y = y_1; y <= y_2; y++) {
				// 计算扫描线与边的交点
				startX = (int)(x_1 + (y - y_1) * slope1);
				endX = (int)(x_1 + (y - y_1) * slope2);

				// 填充交点之间的像素
				hdc_line(startX, y, endX, y, thickness, RGB_value);
			}

		if (y_3 != y_2)
			for (int y = y_2; y <= y_3; y++) {
				// 计算扫描线与边的交点
				startX = (int)(x_2 + (y - y_2) * slope3);
				endX = (int)(x_1 + (y - y_1) * slope2);

				// 填充交点之间的像素
				hdc_line(startX, y, endX, y, thickness, RGB_value);
			}
	}
}

/***************************************************************************
  函数名称：
  功    能：给出左上角坐标及宽度、高度，画出一个长方形
  输入参数：const int left_up_x			：左上角x
			const int left_up_y			：左上角y
			const int width				：宽度
			const int high				：高度
			const int rotation_angles	：以左上角为支点，与x轴的旋转倾角（向下转为正）
			bool filled					：是否需要填充（有缺省值）
			const int thickness			：边的粗细（有缺省值）
			const int RGB_value			：颜色（有缺省值）
  返 回 值：
  说    明：
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
  函数名称：
  功    能：给出左上角坐标及边长，画出一个长方形
  输入参数：const int left_up_x			：左上角x
			const int left_up_y			：左上角y
			const int length			：边长
			const int rotation_angles	：以左上角为支点，与x轴的旋转倾角（向下转为正）（有缺省值）
			const bool filled			：是否需要填充（有缺省值）
			const int thickness			：边的粗细（有缺省值）
			const int RGB_value			：颜色（有缺省值）
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void hdc_square(const int left_up_x, const int left_up_y, const int length, const int rotation_angles, const bool filled, const int thickness, const int RGB_value)
{
	hdc_rectangle(left_up_x, left_up_y, length, length, rotation_angles, filled, thickness, RGB_value);
}

/***************************************************************************
  函数名称：
  功    能：按照给出的参数画一段圆弧
  输入参数：const int point_x		：圆心的x
			const int point_y		：圆心的y
			const int radius		：半径
			const int angle_begin	：起始角度（以圆的最上方为0°，顺时针为正，注意：与系统坐标差了180°!!!）（有缺省值）
			const int angle_end		：结束角度（同上）（有缺省值）
			const int thickness		：粗细（有缺省值）
			const int RGB_value		：颜色（有缺省值）
  返 回 值：
  说    明：
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
  函数名称：
  功    能：按照给出的参数画一个扇形
  输入参数：const int point_x		：圆心的x
			const int point_y		：圆心的y
			const int radius		：半径
			const int angle_begin	：起始角度（以圆的最上方为0°，顺时针为正，注意：与系统坐标差了180°!!!）（有缺省值）
			const int angle_end		：结束角度（同上）（有缺省值）
			const bool filled		：是否需要填充（有缺省值）
			const int thickness		：粗细（有缺省值）
			const int RGB_value		：颜色（有缺省值）
  输入参数：
  返 回 值：
  说    明：当起始/结束角度差值为360的倍数时，不画两条边
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

	//画三角形
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
	//画辐线
	if (filled == true) {
		for (angle = angle_b; angle <= angle_e; angle += 0.1) {

			x = (int)(point_x - (double)(radius * sin(angle * PI / 180)));
			y = (int)(point_y + (double)(radius * cos(angle * PI / 180)));

			hdc_line(point_x, point_y, x, y, thickness + 1, RGB_value);
		}
	}
	//画圆弧
	/*if (filled == true)
		for (level = 1; level <= radius; level ++)
			hdc_arc(point_x, point_y, level, angle_begin, angle_end, thickness, RGB_value);*/

}

/***************************************************************************
  函数名称：
  功    能：按照给出的参数画一个圆
  输入参数：const int point_x		：圆心的x
			const int point_y		：圆心的y
			const int radius		：半径
			const bool filled		：是否需要填充（有缺省值）
			const int thickness		：粗细（有缺省值）
			const int RGB_value		：颜色（有缺省值）
  返 回 值：
  说    明：
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
  函数名称：
  功    能：按照给出的参数画一个椭圆
  输入参数：const int point_x			：圆心的x
			const int point_y			：圆心的y
			const int radius_a			：平行于X轴的半径
			const int radius_b			：平行于Y轴的半径
			const int rotation_angles	：以圆心为支点，与x轴的旋转倾角（向下转为正）（有缺省值）
			const bool filled			：是否需要填充（有缺省值）
			const int thickness			：粗细（有缺省值）
			const int RGB_value			：颜色（有缺省值）
  返 回 值：
  说    明：
***************************************************************************/
void hdc_ellipse(const int point_x, const int point_y, const int radius_a, const int radius_b, const int rotation_angles, const bool filled, const int thickness, const int RGB_value)
{
	int current_x, current_y, new_x, new_y, x, y;
	double angle;

	if (RGB_value != INVALID_RGB)
		hdc_set_pencolor(RGB_value);

	/*distance = radius_a;//初始距离

	x = point_x + (int)(distance * cos(rotation_angles * PI / 180));//基准椭圆，就是标准坐标轴的椭圆的初始位置的右顶点
	y = point_y + (int)(distance * sin(rotation_angles * PI / 180));

	for (angle = 0; angle <= 360; angle++) {

		current_x = x;
		current_y = y;

		x_fix = point_x + (int)(radius_a * cos(angle * PI / 180));
		y_fix = point_y + (int)(radius_b * sin(angle * PI / 180)); //基准椭圆上的点坐标，为fix

		distance = sqrt((x_fix - point_x) * (x_fix - point_x) + (y_fix - point_y) * (y_fix - point_y));//基准椭圆上点到圆心的距离

		x = point_x + (int)(distance * cos((rotation_angles + angle) * PI / 180));//以distance为半径进行旋转rotation_angles角度，得到旋转点
		y = point_y + (int)(distance * sin((rotation_angles + angle) * PI / 180));

		hdc_line(current_x, current_y, x, y, thickness, RGB_value);
		//但是这个distance就是不对！为什么？？因为仿射变换！！rotation_angles + angle并不是旋转角！angle改成arctan(bsin angle/acos angle)
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