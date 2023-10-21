/* 2251206 ����о �ƿ� */
#include "../include/cmd_hdc_tools.h"
#include <iostream>
#include <cmath>
#include <Windows.h>

using namespace std;

//��ʼλ�õ�������
static const int point_y = 600;

//�����ת��
static const int max_angle = 60;

//pi
static const double PI = 3.14159;

//����ṹ��
struct Point {
	int x;
	int y;
};

//ֱ����ת����
static Point rotate(Point p1, Point p2, int angle) //��ʱ��ת
{
	Point p;
	p.x = p1.x + (int)((p2.x - p1.x) * cos(angle * PI / 180) + (p2.y - p1.y) * sin(angle * PI / 180));
	p.y = p1.y + (int)((p2.y - p1.y) * cos(angle * PI / 180) - (p2.x - p1.x) * sin(angle * PI / 180));
	return p;
}

//ֱ�߷�������
static Point shrink(Point p1, Point p2, int angle)
{
	Point p;
	p.x = p1.x + (int)((p2.x - p1.x) * cos(angle * PI / 180));
	p.y = p1.y + (int)((p2.y - p1.y) * cos(angle * PI / 180));
	return p;
}

//��ͼ����
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
	//���뺯����ִ�еĵ�һ���������� hdc_cls();
	hdc_cls();

	//������ʾ
	cout << "�������������빴��������ת�Ƕ�(30-60��)";
	int angle;
	cin >> angle;
	if (cin.fail() || angle < 30 || angle > max_angle) //�������򳬷�Χֱ��������
		angle = max_angle;
	cout << "����������ת�Ƕ� " << angle << " ��";

	srand((unsigned int)time(0));
	int point_x1 = 800 - 10 * angle;
	int point_x2 = point_x1 + 100;

	//��ͼ����
	Point p1 = { point_x1,point_y }; //���������϶���
	Point p2 = { point_x2,point_y }; //���������϶���

	tree(p1, p2, angle);
}