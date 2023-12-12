/* 2251206 ����о �ƿ� */
/* �ο�����
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

unsigned int bitmap_image::get_pixel(int row, int col) const
{
	//һ���������͵�RGBֵͨ���Ժ�ɫͨ����ͣ���ɫͨ����ߵ�˳��洢���ڴ���!!!
	//bmp�д��µ��ϣ�������
	ifstream in(name, ios::in | ios::binary);
	if (in.is_open() == 0) {
		cout << "open failed" << endl;
		return -1;
	}

	int add; // �����ֽ���
	int loc;
	int byte_num; // ԭ���ֽ���
	int byte, leftbit;
	int info = 0; // ����ɫ����Ϣ ����
	char R, G, B;
	//���ص�(h-1-row)*w+col�����ص��RGBֵ

	//����ע��ÿһ��4�ֽڲ���
	if (bpp == 1) { // ��ɫ1bit

		if (w % 8 == 0)
			byte_num = w / 8;
		else
			byte_num = w / 8 + 1;

		add = (4 - byte_num % 4) % 4;

		loc = (h - 1 - row) * (add + byte_num) * 8 + col;

		byte = loc / 8;
		leftbit = loc % 8; // �ڼ�������λ������
		in.seekg(location, ios::beg);
		in.seekg(byte, ios::cur);

		in.read((char*)&info, sizeof(int));
		in.clear();

		info = (info >> (7 - leftbit)) & 1; //���Ŵ�

		in.seekg(0x36 + info * 4, ios::beg);
	}
	else if (bpp == 4) { // 16ɫ4bit

		if (w % 2 == 0)
			byte_num = w / 2;
		else
			byte_num = w / 2 + 1;

		add = (4 - byte_num % 4) % 4;

		loc = (h - 1 - row) * (add + byte_num) * 8 + col * 4;

		byte = loc / 8;
		leftbit = loc % 8; // �ڼ�������λ������ ֻ������0����4
		in.seekg(location, ios::beg);
		in.seekg(byte, ios::cur);

		in.read((char*)&info, sizeof(int));
		in.clear();

		if (leftbit == 0)
			info = (info >> 4) & 0xf; //���Ŵ�
		else
			info &= 0xf;

		in.seekg(0x36 + info * 4, ios::beg);
	}
	else if (bpp == 8) { // 256ɫ8bit
		byte_num = w;

		add = (4 - byte_num % 4) % 4;

		loc = (h - 1 - row) * (add + byte_num) * 8 + col * 8;

		byte = loc / 8;
		leftbit = loc % 8; // �ڼ�������λ������
		in.seekg(location, ios::beg);
		in.seekg(byte, ios::cur);

		in.read((char*)&info, sizeof(int));
		in.clear();

		info &= 0xff;

		in.seekg(0x36 + info * 4, ios::beg);
	}
	else if (bpp == 24) { // 24bit
		byte_num = w * 3;

		add = (4 - byte_num % 4) % 4;

		loc = (h - 1 - row) * (add + byte_num) * 8 + col * 24;

		byte = loc / 8;
		leftbit = loc % 8; // �ڼ�������λ������

		in.seekg(location, ios::beg);
		in.seekg(byte, ios::cur);

		/*in.read((char*)&info, sizeof(int));
		in.clear();

		info &= 0xffffff;

		in.seekg(0x36 + info * 4, ios::beg);*/
	}

	in.read(&B, sizeof(char));
	in.read(&G, sizeof(char));
	in.read(&R, sizeof(char));
	in.clear();

	in.close();
	return RGB(R, G, B);
}

void bitmap_image::edit_pixel(fstream& edit, int posx, int posy, unsigned char R, unsigned char G, unsigned char B)
{
	int add; // �����ֽ���
	int loc;
	int byte_num; // ԭ���ֽ���
	int byte, leftbit;
	int info = 0; // ����ɫ����Ϣ ����

	if (bpp == 1) { // ��ɫ1bit
		int word = 1;
		if (w % 8 == 0)
			byte_num = w / 8;
		else
			byte_num = w / 8 + 1;

		add = (4 - byte_num % 4) % 4;

		loc = (h - 1 - posy) * (add + byte_num) * 8 + posx;

		byte = loc / 8;
		leftbit = loc % 8; // �ڼ�������λ������

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
		leftbit = loc % 8; // �ڼ�������λ������ ֻ������0����4

		edit.seekg(location + byte, ios::beg);

		edit.read((char*)&info, sizeof(int));
		if (leftbit == 0)
			info = info & ~(word << 4); //���Ŵ�
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
		leftbit = loc % 8; // �ڼ�������λ������
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