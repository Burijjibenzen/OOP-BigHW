/* 2251206 冯羽芯 计科 */

#pragma once
#include <fstream>
using namespace std;

/* 根据需要加入自己的定义 */

class bitmap_image
{
protected:
	/* 根据需要加入自己的定义 */
	int location; // 像素存储位置
	int w;
	int h;
	short bpp; // 像素位数
	const char* name;

public:
	int width() const;	//返回图片的宽度
	int height() const; //返回图片的高度
	void edit_pixel(fstream& edit, int posx, int posy, unsigned char R, unsigned char G, unsigned char B);

	/* 根据需要加入自己的定义 */
	bitmap_image(const char* filename); // 构造函数
};