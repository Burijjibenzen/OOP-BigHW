/* 2251206 冯羽芯 计科 */
#include "../include/cmd_hdc_tools.h"
#include <iostream>
#include <cmath>
#include <Windows.h>

using namespace std;

//起始位置的纵坐标
static const int point_y = 600;

//最大旋转角
static const int max_angle = 60;

//pi
static const double PI = 3.14159;

//坐标结构体
struct Point {
	int x;
	int y;
};

//直线旋转函数
static Point rotate(Point p1, Point p2, int angle) //逆时针转
{
	Point p;
	p.x = p1.x + (int)((p2.x - p1.x) * cos(angle * PI / 180) + (p2.y - p1.y) * sin(angle * PI / 180));
	p.y = p1.y + (int)((p2.y - p1.y) * cos(angle * PI / 180) - (p2.x - p1.x) * sin(angle * PI / 180));
	return p;
}

//直线放缩函数
static Point shrink(Point p1, Point p2, int angle)
{
	Point p;
	p.x = p1.x + (int)((p2.x - p1.x) * cos(angle * PI / 180));
	p.y = p1.y + (int)((p2.y - p1.y) * cos(angle * PI / 180));
	return p;
}

//画图函数
static void tree(Point p1, Point p2, int angle)
{
	Point p3 = rotate(p1, p2, 90);
	Point p4 = rotate(p2, p1, 270);

	int a, b, c;
	a = rand() % 255;
	b = rand() % 255;
	c = rand() % 255;

	hdc_triangle(p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, true, 2, RGB(a, b, c));
	hdc_triangle(p4.x, p4.y, p2.x, p2.y, p3.x, p3.y, true, 2, RGB(a, b, c));

	if (sqrt((p3.x - p4.x) * (p3.x - p4.x) + (p3.y - p4.y) * (p3.y - p4.y)) > 5) {

		Point p = rotate(p3, p4, angle);
		p = shrink(p3, p, angle);

		tree(p3, p, angle);
		tree(p, p4, angle);

	}
}

void hdc_draw_Mathematical_curve_2251206()
{
	//进入函数后执行的第一个语句必须是 hdc_cls();
	hdc_cls();

	//交互提示
	cout << "勾股树，请输入勾股树的旋转角度(30-60度)";
	int angle;
	cin >> angle;
	if (cin.fail() || angle < 30 || angle > max_angle) //输入错误或超范围直接置上限
		angle = max_angle;
	cout << "勾股树，旋转角度 " << angle << " 度";

	srand((unsigned int)time(0));
	int point_x1 = 800 - 10 * angle;
	int point_x2 = point_x1 + 100;

	//画图过程
	Point p1 = { point_x1,point_y }; //正方形左上顶点
	Point p2 = { point_x2,point_y }; //正方形右上顶点

	tree(p1, p2, angle);
}