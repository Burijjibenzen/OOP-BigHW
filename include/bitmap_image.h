/* 2251206 ����о �ƿ� */

#pragma once
#include <fstream>
using namespace std;

/* ������Ҫ�����Լ��Ķ��� */

class bitmap_image
{
protected:
	/* ������Ҫ�����Լ��Ķ��� */
	int location; // ���ش洢λ��
	int w;
	int h;
	short bpp; // ����λ��
	const char* name;

public:
	int width() const;	//����ͼƬ�Ŀ��
	int height() const; //����ͼƬ�ĸ߶�
	void edit_pixel(fstream& edit, int posx, int posy, unsigned char R, unsigned char G, unsigned char B);

	/* ������Ҫ�����Լ��Ķ��� */
	bitmap_image(const char* filename); // ���캯��
};