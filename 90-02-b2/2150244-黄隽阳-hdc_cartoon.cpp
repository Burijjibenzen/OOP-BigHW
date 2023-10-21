//2150244 信06 黄隽阳
#include <Windows.h>
#include <cmath>
#include "../include/cmd_hdc_tools.h"

#define HAT_COLOR   RGB(255,151,0)		//草帽的颜色
#define HAT_RED     RGB(170,14,2)		//草帽上的红色
#define WHITE_COLOR RGB(255,255,255)	//部分区域需要用到的白色
#define PI          3.1415926			//圆周率

//角度转弧度
static inline double hdc_inner_deg2rad(const double angle)
{
	return angle * PI / 180;
}

//画背后两根骨头
static void hdc_cartoon_inner_bone(const int base_x, const int base_y)
{
	const int reg_len = 283;	//x和y坐标的变化量
	const int reg_wid = 900;	//实际长度
	const int reg_high = 94;	//实际宽度
	const int radius_s = 60;	//骨头的圆半径

	//左上角到右下角的骨头
	hdc_rectangle(base_x - reg_len, base_y - reg_len - (int)(reg_high / sqrt(2)), reg_wid, reg_high, 45, true, 5, WHITE_COLOR);		//骨头长方形
	//再通过四个圆模拟一下骨头
	hdc_circle(base_x - reg_len, base_y - reg_len - reg_high / 2, radius_s, true, 5, WHITE_COLOR);
	hdc_circle(base_x - reg_len - reg_high / 2, base_y - reg_len, radius_s, true, 5, WHITE_COLOR);
	hdc_circle(base_x + reg_len, base_y + reg_len + reg_high / 2, radius_s, true, 5, WHITE_COLOR);
	hdc_circle(base_x + reg_len + reg_high / 2, base_y + reg_len, radius_s, true, 5, WHITE_COLOR);

	//右上角到左下角的骨头
	hdc_rectangle(base_x + reg_len + (int)(reg_high / sqrt(2)), base_y - reg_len, reg_wid, reg_high, 135, true, 5, WHITE_COLOR);	//骨头长方形
	//再通过两个圆模拟一下骨头
	hdc_circle(base_x - reg_len, base_y + reg_len + reg_high / 2, radius_s, true, 5, WHITE_COLOR);
	hdc_circle(base_x - reg_len - reg_high / 2, base_y + reg_len, radius_s, true, 5, WHITE_COLOR);
	hdc_circle(base_x + reg_len, base_y - reg_len - reg_high / 2, radius_s, true, 5, WHITE_COLOR);
	hdc_circle(base_x + reg_len + reg_high / 2, base_y - reg_len, radius_s, true, 5, WHITE_COLOR);

}

//画路飞的草帽
static void hdc_cartoon_inner_hat(const int base_x, const int base_y)
{
	const int hat_a = 330;				//草帽椭圆的长半轴
	const int hat_b = 30;				//草帽椭圆的短半轴
	const int red_b = 30;				//草帽椭圆的短半轴
	const int r_head = 250;				//头的大小

	hdc_sector(base_x, base_y, r_head, -90, 90, true, 5, HAT_COLOR);				//上半部分
	hdc_arc(base_x, base_y, r_head, -90, 90, 10, COLOR_BLACK);					//上半部分轮廓
	hdc_ellipse(base_x, base_y - hat_b, r_head, red_b, 0, true, 5, HAT_RED);		//红色部分
	hdc_ellipse(base_x, base_y - hat_b, r_head, red_b, 0, false, 9, COLOR_BLACK);	//红色部分轮廓
	hdc_ellipse(base_x, base_y, hat_a, hat_b, 0, true, 5, HAT_COLOR);				//椭圆部分
	hdc_ellipse(base_x, base_y, hat_a, hat_b, 0, false, 9, COLOR_BLACK);			//椭圆部分轮廓
	hdc_ellipse(base_x, base_y, r_head, hat_b / 2, 0, true, 5, WHITE_COLOR);		//多余部分恢复白色
	hdc_ellipse(base_x, base_y, r_head, hat_b / 2, 0, false, 9, COLOR_BLACK);		//多余部分轮廓
	hdc_sector(base_x, base_y, r_head, 90, 270, true, 5, WHITE_COLOR);				//下半部分
	hdc_arc(base_x, base_y, r_head, 90, 270, 9, COLOR_BLACK);					//下半部分轮廓
}

//画头部
static void hdc_cartoon_inner_head(const int base_x, const int base_y)
{
	const int r_head = 250;			//头的大小
	const int y_mouth = 280;			//嘴的纵坐标偏移量
	const int r_mouth = 100;			//嘴部圆的大小
	const int y_nose = 167;			//鼻子纵坐标偏移量
	const int r_nose = 20;				//鼻子半径
	const int x_eyes = 110;			//眼睛横坐标偏移量
	const int y_eyes = 90;				//眼睛纵坐标偏移量
	const int r_eyes = 80;				//眼睛半径
	const int d_teeth = 10;				//牙齿起点旋转角度
	const int y1 = 133;					//牙齿第一段弧圆心偏移量
	const int r1 = 150;					//牙齿第一段弧半径
	const int y2 = 200;					//牙齿第二段弧圆心偏移量
	const int r2 = 130;					//牙齿第二段弧半径

	//先画嘴部的圆，等后续覆盖掉
	hdc_circle(base_x, base_y + y_mouth, r_mouth, true, 5, WHITE_COLOR);	//内圈

	//画草帽
	hdc_cartoon_inner_hat(base_x, base_y);

	//眼睛
	hdc_circle(base_x - x_eyes, base_y + y_eyes, r_eyes, true, 9, COLOR_BLACK);
	hdc_circle(base_x + x_eyes, base_y + y_eyes, r_eyes, true, 9, COLOR_BLACK);

	//鼻子
	hdc_circle(base_x, base_y + y_nose, r_nose, true, 9, COLOR_BLACK);

	//嘴巴牙齿细节
	hdc_arc(base_x, base_y + y1, r1, 135, 225, 9, COLOR_BLACK);
	hdc_arc(base_x, base_y + y2, r2, 105, 255, 9, COLOR_BLACK);
	hdc_line(base_x, base_y + r_head, base_x, base_y + y2 + r2, 9, COLOR_BLACK);
	hdc_line(base_x - (int)(r_head * sin(hdc_inner_deg2rad(d_teeth))), base_y + (int)(r_head * cos(hdc_inner_deg2rad(d_teeth))), base_x - (int)(r2 * sin(hdc_inner_deg2rad(3 * d_teeth))), base_y + y2 + (int)(r2 * cos(hdc_inner_deg2rad(3 * d_teeth))), 9, COLOR_BLACK);
	hdc_line(base_x + (int)(r_head * sin(hdc_inner_deg2rad(d_teeth))), base_y + (int)(r_head * cos(hdc_inner_deg2rad(d_teeth))), base_x + (int)(r2 * sin(hdc_inner_deg2rad(3 * d_teeth))), base_y + y2 + (int)(r2 * cos(hdc_inner_deg2rad(3 * d_teeth))), 9, COLOR_BLACK);
}

void hdc_draw_cartoon_2150244(const int base_x, const int base_y)
{
	//进入函数后执行的第一个语句必须是 hdc_cls();
	hdc_cls();

	//初始化下背景，我要的是黑色背景
	hdc_init(0, 7, 800, 800);

	//画背后两根骨头
	hdc_cartoon_inner_bone(base_x, base_y);

	//头部和草帽
	hdc_cartoon_inner_head(base_x, base_y);
}