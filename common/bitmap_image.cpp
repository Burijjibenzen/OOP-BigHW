/* 2251206 冯羽芯 计科 */
/* 参考资料
* https://blog.csdn.net/wkd_007/article/details/128214157
* https://zhuanlan.zhihu.com/p/260702527
*/
#include <iostream>
#include <fstream>
#include <Windows.h>
#include "../include/bitmap_image.h"
using namespace std;

bitmap_image::bitmap_image(const char* filename)
{
	name = filename;

	ifstream in(filename, ios::in | ios::binary);
	if (in.is_open() == 0) {
		cout << "open failed" << endl;
		return;
	}

	in.seekg(10, ios::beg);
	in.read((char*)&location, sizeof(int));
	in.seekg(0, ios::beg);

	in.seekg(28, ios::beg);
	in.read((char*)&bpp, sizeof(short));
	in.seekg(0, ios::beg);

	in.seekg(18, ios::beg);
	in.read((char*)&w, sizeof(int));
	in.read((char*)&h, sizeof(int));
	in.seekg(0, ios::beg);

	in.close();
	//cout << endl << endl << endl << endl << endl << endl << endl;
	//cout << location << endl;
	//cout << bpp << endl;
}

int bitmap_image::width() const
{
	return w;
}

int bitmap_image::height() const
{
	return h;
}

void bitmap_image::edit_pixel(fstream& edit, int posx, int posy, unsigned char R, unsigned char G, unsigned char B)
{
	int add; // 补齐字节数
	int loc;
	int byte_num; // 原有字节数
	int byte, leftbit;
	int info = 0; // 存颜色的信息 索引

	if (bpp == 1) { // 单色1bit
		int word = 1;
		if (w % 8 == 0)
			byte_num = w / 8;
		else
			byte_num = w / 8 + 1;

		add = (4 - byte_num % 4) % 4;

		loc = (h - 1 - posy) * (add + byte_num) * 8 + posx;

		byte = loc / 8;
		leftbit = loc % 8; // 第几个比特位的数据

		edit.seekg(location + byte, ios::beg);

		edit.read((char*)&info, sizeof(int));
		info = info & ~(word << (7 - leftbit));

		edit.seekp(location + byte, ios::beg);
		edit.write((char*)&info, sizeof(int));
		edit.clear();
	}
	else if (bpp == 4) {
		int word = 0xf;
		if (w % 2 == 0)
			byte_num = w / 2;
		else
			byte_num = w / 2 + 1;

		add = (4 - byte_num % 4) % 4;

		loc = (h - 1 - posy) * (add + byte_num) * 8 + posx * 4;

		byte = loc / 8;
		leftbit = loc % 8; // 第几个比特位的数据 只可能是0或者4

		edit.seekg(location + byte, ios::beg);

		edit.read((char*)&info, sizeof(int));
		if (leftbit == 0)
			info = info & ~(word << 4); //倒着存
		else
			info = info & ~word;

		edit.seekp(location + byte, ios::beg);
		edit.write((char*)&info, sizeof(int));
		edit.clear();
	}
	else if (bpp == 8) {
		int word = 0xff;
		byte_num = w;

		add = (4 - byte_num % 4) % 4;

		loc = (h - 1 - posy) * (add + byte_num) * 8 + posx * 8;

		byte = loc / 8;
		leftbit = loc % 8; // 第几个比特位的数据
		edit.seekg(location + byte, ios::beg);

		edit.read((char*)&info, sizeof(int));

		info &= ~word;

		edit.seekp(location + byte, ios::beg);
		edit.write((char*)&info, sizeof(int));
		edit.clear();
	}
	else if (bpp == 24) {
		byte_num = w * 3;

		add = (4 - byte_num % 4) % 4;

		loc = (h - 1 - posy) * (add + byte_num) * 8 + posx * 24;

		byte = loc / 8;

		edit.seekp(location + byte, ios::beg);
		edit.write((char*)&B, sizeof(char));
		edit.write((char*)&G, sizeof(char));
		edit.write((char*)&R, sizeof(char));
		edit.clear();
	}
}