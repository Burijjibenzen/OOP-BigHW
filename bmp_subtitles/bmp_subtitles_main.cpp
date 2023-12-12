/* 2251206 ����о �ƿ� */
#define _CRT_SECURE_NO_WARNINGS
#define WIDTH 8
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <sstream>
#include <fstream>
#include "../include/bitmap_image.h"
#include "../include/class_aat.h"
using namespace std;

enum OPT_BMP {
	OPT_BMP_HELP = 0,
	OPT_BMP_BMPFILE,
	OPT_BMP_OUTFILE,
	OPT_BMP_TRADITIONAL,
	OPT_BMP_SUBTITLES,
	OPT_BMP_POSX,
	OPT_BMP_POSY,
	OPT_BMP_COLOR,
	OPT_BMP_STYLE,
};

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void usage(const char* procname)
{
	ostringstream msg;

	msg << "Usage: " << procname << " --bmpfile xxx --outfile xxx [ --traditional | --subtitles xxx | --posx 0..1919 | --posy 0..1079 | --color xxxxxx | --style none/horizontal/vertical ]" << endl;
	msg << "       " << "��ѡ�" << endl;
	msg << "       " << "--bmpfile name1              : ָ��ԭʼbmpͼƬ������ѡ��" << endl;
	msg << "       " << "--outfile name2              : ָ������Ļ���bmp�ļ�������ѡ��" << endl;
	msg << endl;

	msg << "       " << "��ѡ�" << endl;
	msg << "       " << "--traditional                    : boolֵ��true��ʾ�����ַ����������" << endl;
	msg << "       " << "--subtitles str                  : Ҫ�������Ļ���֣�������10�����֣�������GB2312�еĺ��֣�" << endl;
	msg << "       " << "--posx [0..1919]                 : Ҫ����ĵ�һ�����ֵ����Ͻ�x����" << endl;
	msg << "       " << "--posy [0..1079]                 : Ҫ����ĵ�һ�����ֵ����Ͻ�y����" << endl;
	msg << "       " << "--color HHHHHH                   : ����ǰ��ɫ��6��16�����ַ����ֱ�ΪRGB" << endl;
	msg << "       " << "--style none/horizontal/vertical : ��ʾ����޴�����Ĭ��Ϊnone��" << endl;
	msg << "       " << "\tnone         : Ĭ�Ϻ���" << endl;
	msg << "       " << "\thorizontal   : ����" << endl;
	msg << "       " << "\tvertical     : ����" << endl;
	msg << endl;

	cout << msg.str() << endl;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int main(int argc, char** argv)
{
	const string DisplayType[] = { "none",	"horizontal",	"vertical", "" };

	args_analyse_tools args[] = {

		args_analyse_tools("--help",			ST_EXTARGS_TYPE::boolean, 0, false),
		args_analyse_tools("--bmpfile",			ST_EXTARGS_TYPE::str, 1, string("")),
		args_analyse_tools("--outfile",			ST_EXTARGS_TYPE::str, 1, string("")),
		args_analyse_tools("--traditional",	    ST_EXTARGS_TYPE::boolean, 0, false),
		args_analyse_tools("--subtitles",		ST_EXTARGS_TYPE::str, 1, string("")),
		args_analyse_tools("--posx",		    ST_EXTARGS_TYPE::int_with_default,   1, 0, 0, 1919),
		args_analyse_tools("--posy",		    ST_EXTARGS_TYPE::int_with_default,   1, 0, 0, 1079),
		args_analyse_tools("--color",			ST_EXTARGS_TYPE::str, 1, string("")),
		args_analyse_tools("--style",			ST_EXTARGS_TYPE::str_with_set_error, 1, 0, DisplayType),

		args_analyse_tools()  //���һ�������ڽ���
	};

	int cur_argc;

	//���һ������1����ʾ��ѡ������⣬������������
	if ((cur_argc = args_analyse_process(argc, argv, args, 0)) < 0) {
		//������Ϣ�ں������Ѵ�ӡ
		args_analyse_print(args);
		usage(argv[0]);
		return -1;
	}

	/* ��help�����⴦�� */
	if (args[OPT_BMP_HELP].existed()) {
		//ֻҪ�� --help���������������ԣ���ʾ��������
		args_analyse_print(args);
		usage(argv[0]);
		return -1; //ִ�����ֱ���˳�
	}

	if (args[OPT_BMP_BMPFILE].existed() + args[OPT_BMP_OUTFILE].existed() != 2) {
		usage(argv[0]);
		cout << "����ָ������[" << args[OPT_BMP_BMPFILE].get_name() << "��" << args[OPT_BMP_OUTFILE].get_name() << "]" << endl;
		return -1;
	}

	ifstream bmp;
	ofstream out;
	fstream edit;
	unsigned char* str; // һ�������10������

	bmp.open(args[OPT_BMP_BMPFILE].get_string(), ios::in | ios::binary);
	out.open(args[OPT_BMP_OUTFILE].get_string(), ios::out | ios::binary);
	edit.open(args[OPT_BMP_OUTFILE].get_string(), ios::in | ios::out | ios::binary);

	if (bmp.is_open() == 0) {
		cout << "ԭʼbmpͼƬ[" << args[OPT_BMP_BMPFILE].get_string() << "]�޷���.\n";
		return -1;
	}
	if (out.is_open() == 0) {
		cout << "����Ļ��bmpͼƬ[" << args[OPT_BMP_OUTFILE].get_string() << "]�޷���.\n";
		return -1;
	}
	if (edit.is_open() == 0) {
		cout << "����Ļ��bmpͼƬ[" << args[OPT_BMP_OUTFILE].get_string() << "]�޷���.\n";
		return -1;
	}

	int posx, posy;
	posx = args[OPT_BMP_POSX].get_int();
	posy = args[OPT_BMP_POSY].get_int();

	char color[3] = { 0 };
	if (args[OPT_BMP_COLOR].existed() == 1) {
		char C1, C2;
		for (int i = 0; i < 6; i += 2) {
			C1 = args[OPT_BMP_COLOR].get_string().c_str()[i];
			C2 = args[OPT_BMP_COLOR].get_string().c_str()[i + 1];
			if (C1 >= 'a' && C1 <= 'f')
				C1 -= 87;
			if (C1 >= '0' && C1 <= '9')
				C1 -= 48;
			if (C2 >= 'a' && C2 <= 'f')
				C2 -= 87;
			if (C2 >= '0' && C2 <= '9')
				C2 -= 48;
			color[i / 2] = C1 * 16 + C2;
		}
	}

	// ����bmp��Ϣ
	out << bmp.rdbuf();
	out.close();

	bitmap_image BMP(args[OPT_BMP_OUTFILE].get_string().c_str()); // BMP �ĳ�ʼ��

	if (args[OPT_BMP_SUBTITLES].existed() == 1) {
		str = new (nothrow) unsigned char[args[OPT_BMP_SUBTITLES].get_string().length() + 1];
		if (str == NULL) {
			cout << "No Memory\n";
			return -1;
		}
		strcpy((char*)str, args[OPT_BMP_SUBTITLES].get_string().c_str());

		for (unsigned int i = 0; i < strlen((char*)str); i += 2) {
			int qh, wh; // ǰ��� �����ڲ���
			qh = str[i] - 0xa0;
			wh = str[i + 1] - 0xa0;
			int offset = (94 * (qh - 1) + (wh - 1)) * 32;

			ifstream in;
			if (args[OPT_BMP_TRADITIONAL].existed() == 1)
				in.open("HZK16F", ios::in | ios::binary);
			else
				in.open("HZK16", ios::in | ios::binary);

			if (in.is_open() == 0) {
				cout << "open failed" << endl;
				return -1;
			}

			// ��ȡ������Ϣ
			unsigned short info[16]; // �溺����Ϣ�ֽ�
			in.seekg(offset, ios::beg);
			for (int k = 0; k < 16; k++) {
				in.read((char*)&info[k] + 1, sizeof(char));
				in.read((char*)&info[k], sizeof(char));

				for (int j = 16 - 1; j >= 0; j--)
					if (((info[k] >> j) & 0x1) == 1) // ��Ҫ���
						if (args[OPT_BMP_STYLE].get_string() != "vertical")
							BMP.edit_pixel(edit, posx + (15 - j) + WIDTH * i, posy + k, color[0], color[1], color[2]);
						else
							BMP.edit_pixel(edit, posx + (15 - j), posy + k + WIDTH * i, color[0], color[1], color[2]);
			}
			in.seekg(0, ios::beg);
			/*
			unsigned char info[16];
			in.seekg(offset, ios::beg);
			for (int k = 0; k < 16; k++) {
				in.read((char*)&info[k], sizeof(char));
				for (int j = 7; j >= 0; j--) {
					if (((info[k] >> j) & 0x1) == 1) // ��Ҫ���
						BMP.edit_pixel(edit, posx + (7 - j), posy + k);
				}

				in.read((char*)&info[k], sizeof(char));
				for (int j = 15; j >= 8; j--) {
					if (((info[k] >> (j - 8)) & 0x1) == 1) // ��Ҫ���
						BMP.edit_pixel(edit, posx + (23 - j), posy + k);
				}
			}
			in.seekg(0, ios::beg);
			*/
		}
		// ������뺺�ֵı�
		/*
		for (unsigned int i = 0; i < strlen((char*)str); i += 2) {
			int qh, wh; // ǰ��� �����ڲ���
			qh = str[i] - 0xa0;
			wh = str[i + 1] - 0xa0;
			int offset = (94 * (qh - 1) + (wh - 1)) * 32;
			int cnt = 0;

			ifstream in;
			unsigned char info[32]; // �溺����Ϣ�ֽ�
			if (args[OPT_BMP_TRADITIONAL].existed() == 1)
				in.open("HZK16F", ios::in | ios::binary);
			else
				in.open("HZK16", ios::in | ios::binary);

			if (in.is_open() == 0) {
				cout << "open failed" << endl;
				return -1;
			}

			// ��ȡ������Ϣ
			in.seekg(offset, ios::beg);
			for (int k = 0; k < 32; k++) {
				in.read((char*)&info[k], sizeof(char));
				for (int j = 8 - 1; j >= 0; j--) {
					if (((info[k] >> j) & 0x1) == 0)
						cout << "  ";
					else
						cout << "* ";
					cnt++;
					if (cnt % 16 == 0)
						cout << endl;
				}
			}
			in.seekg(0, ios::beg);
		}*/
	}
	return 0;
}