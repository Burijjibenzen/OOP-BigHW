/* 2251206 冯羽芯 计科 */
#include <Windows.h>
#include <cmath>
#include "../include/cmd_hdc_tools.h"

#define WHITE_COLOR RGB(255,255,255)
#define BLACK_COLOR RGB(0,0,0)
#define FACE_COLOR RGB(244,237,211)
#define SHADOW_COLOR RGB(253,228,190)
#define TATOO_COLOR RGB(143,130,188)
#define GREY_COLOR RGB(127,127,127)
#define PI          3.1415926			

static void facelessman(const int base_x, const int base_y)
{
	const int body_a = 460;
	const int body_b = 220;
	const int y_body = 280;

	const int head_a = 320;
	const int head_b = 180;
	const int y_head = 20;

	const int face_a = 170;
	const int face_b = 105;
	const int x_face = 20;
	const int y_face = 80;

	const int face_shadow_a = 180;
	const int face_shadow_b = 125;
	const int y_face_shadow = 80;

	const int mouth_a = 30;
	const int mouth_b = 10;
	const int y_mouth = 15;

	const int mouth_tatoo_a = 20;
	const int mouth_tatoo_b = 5;
	const int y_mouth_tatoo = 50;

	const int eye_a = 25;
	const int eye_b = 15;
	const int x_eye = 60;
	const int y_eye = 120;

	hdc_ellipse(base_x, base_y + y_head, head_a, head_b, 90, true, 5, BLACK_COLOR); //头
	hdc_ellipse(base_x, base_y + y_body, body_a, body_b, 90, true, 5, BLACK_COLOR); //身体
	hdc_ellipse(base_x, base_y - y_face_shadow, face_shadow_a, face_shadow_b, 90, true, 5, SHADOW_COLOR); //脸 阴影
	hdc_ellipse(base_x - x_face, base_y - y_face, face_a, face_b, 90, true, 5, FACE_COLOR); //脸
	hdc_ellipse(base_x, base_y + y_mouth, mouth_a, mouth_b, 0, true, 5, BLACK_COLOR); //嘴巴
	hdc_ellipse(base_x, base_y + y_mouth_tatoo, mouth_tatoo_a, mouth_tatoo_b, 0, true, 2, TATOO_COLOR); //嘴巴下面的纹路
	hdc_ellipse(base_x - x_eye, base_y - y_eye, eye_a, eye_b, 0, true, 5, BLACK_COLOR); //左眼
	hdc_ellipse(base_x + x_eye, base_y - y_eye, eye_a, eye_b, 0, true, 5, BLACK_COLOR); //右眼


	//纹路
	const int eye_tatoo_a = 20;
	const int eye_tatoo_b = 4;

	const int eye_tatoo_purple_a = 15;
	const int eye_tatoo_purple_b = 4;

	const int y_triangle_up = 220;
	const int y_triangle_down = 4;

	hdc_ellipse(base_x - x_eye, base_y - y_eye + 30, eye_tatoo_a, eye_tatoo_b, 0, true, 2, BLACK_COLOR); //左眼纹路
	hdc_ellipse(base_x + x_eye, base_y - y_eye + 30, eye_tatoo_a, eye_tatoo_b, 0, true, 2, BLACK_COLOR); //右眼纹路
	hdc_ellipse(base_x - x_eye, base_y - y_eye + 60, eye_tatoo_purple_a, eye_tatoo_purple_b, 0, true, 2, TATOO_COLOR); //左眼下纹路
	hdc_ellipse(base_x + x_eye, base_y - y_eye + 60, eye_tatoo_purple_a, eye_tatoo_purple_b, 0, true, 2, TATOO_COLOR); //右眼下纹路
	hdc_ellipse(base_x - x_eye, base_y - y_eye - 40, eye_tatoo_purple_a, eye_tatoo_purple_b, 0, true, 2, TATOO_COLOR); //左眼上纹路
	hdc_ellipse(base_x + x_eye, base_y - y_eye - 40, eye_tatoo_purple_a, eye_tatoo_purple_b, 0, true, 2, TATOO_COLOR); //右眼上纹路

	hdc_triangle(base_x - x_eye - eye_tatoo_purple_a, base_y - y_eye - 40, base_x - x_eye + eye_tatoo_purple_a, base_y - y_eye - 40, base_x - x_eye, base_y - y_triangle_up, true, 2, TATOO_COLOR);
	hdc_triangle(base_x - x_eye - eye_tatoo_purple_a, base_y - y_eye + 60, base_x - x_eye + eye_tatoo_purple_a, base_y - y_eye + 60, base_x - x_eye, base_y + y_triangle_down, true, 2, TATOO_COLOR);
	hdc_triangle(base_x + x_eye - eye_tatoo_purple_a, base_y - y_eye - 40, base_x + x_eye + eye_tatoo_purple_a, base_y - y_eye - 40, base_x + x_eye, base_y - y_triangle_up, true, 2, TATOO_COLOR);
	hdc_triangle(base_x + x_eye - eye_tatoo_purple_a, base_y - y_eye + 60, base_x + x_eye + eye_tatoo_purple_a, base_y - y_eye + 60, base_x + x_eye, base_y + y_triangle_down, true, 2, TATOO_COLOR);

	//手
	const int x_hand = 150;
	const int y_hand = 320;

	hdc_arc(base_x + x_hand, base_y + y_hand, 350, 225, 300, 4, GREY_COLOR);
	hdc_arc(base_x + x_hand + 45, base_y + y_hand, 350, 225, 290, 4, GREY_COLOR);
	hdc_arc(base_x - x_hand, base_y + y_hand, 350, 60, 135, 4, GREY_COLOR);
	hdc_arc(base_x - x_hand - 45, base_y + y_hand, 350, 70, 135, 4, GREY_COLOR);
}

static void briquettes(const int base_x, const int base_y)
{
	const int x_body = 286;
	const int y_body = 170;
	const int body = 75;

	hdc_circle(base_x + x_body, base_y - y_body, body, true, 2, BLACK_COLOR);

	for (int angle = 0; angle <= 360; angle += 5)
		hdc_line(base_x + x_body, base_y - y_body, (int)(base_x + x_body + (body + 5) * sin(angle * PI / 180)), (int)(base_y - y_body - (body + 5) * cos(angle * PI / 180)), 5, BLACK_COLOR);

	const int x_left_eye = 266;
	const int x_right_eye = 315;
	const int eye = 25;
	const int y_left_eye = 200;
	const int y_right_eye = 170;

	hdc_circle(base_x + x_left_eye, base_y - y_left_eye, eye, true, 2, WHITE_COLOR);
	hdc_circle(base_x + x_right_eye, base_y - y_right_eye, eye, true, 2, WHITE_COLOR);

	const int x_left_eyeball = 272;
	const int y_left_eyeball = 194; 
	const int x_right_eyeball = 310;
	const int y_right_eyeball = 180;

	hdc_point(base_x + x_left_eyeball, base_y - y_left_eyeball, 10, BLACK_COLOR);
	hdc_point(base_x + x_right_eyeball, base_y - y_right_eyeball, 10, BLACK_COLOR);
}

void hdc_draw_cartoon_2251206(const int base_x, const int base_y)
{
	//进入函数后执行的第一个语句必须是 hdc_cls();
	hdc_cls();

	facelessman(base_x - 100, base_y);

	briquettes(base_x - 80, base_y);
}