//2150244 信06 黄隽阳
#include "../include/cmd_hdc_tools.h"
#include <iostream>
#include <cmath>
using namespace std;

//起始位置的横纵坐标
static const int point_x = 400;
static const int point_y = 500;

//起始和结束角度
static const int start_angle = -45;
static const int end_angle = 45;

//颜色
static const int color[2][3] = { { 0x00000000 ,0x00000000, 0x00CCCCCC },{ 0x00C0C0C0 ,0x00C0C0C0, 0x00CCCCCC } };

//信号条宽度
static const int width = 30;
static const int wid_all = 270;

//满格是三格WiFi信号
static const int total_num = 3;

//存在需要输入参数的情况，字体比较小，希望能看得到吧
void hdc_draw_Mathematical_curve_2150244()
{
	//进入函数后执行的第一个语句必须是 hdc_cls();
	hdc_cls();

	//交互提示
	cout << "WiFi 图标，请输入 WiFi 信号格数（满格3格，请输入1-3，默认3格）： ";
	int num;		//实际显示信号格数，由键盘输入
	cin >> num;
	if (cin.fail() || num < 1 || num > total_num)	//输入错误或超范围直接置上限
		num = total_num;
	cout << "WiFi 图标 " << num << " 格";

	//画图过程
	for (int i = 0; i < 3 * total_num - 1; i++) {
		if (i / 3 >= (total_num - num))	//无信号
			hdc_sector(point_x, point_y, wid_all - width * i, start_angle, end_angle, true, 5, color[0][i % 3]);
		else							//有信号
			hdc_sector(point_x, point_y, wid_all - width * i, start_angle, end_angle, true, 5, color[1][i % 3]);
	}
}