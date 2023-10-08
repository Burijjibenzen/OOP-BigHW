//2251206 ����о �ƿ� 
#include <iostream>
#include <iomanip>
#include <Windows.h>
#include "../include/cmd_console_tools.h"
#include "./90-01-b2.h"
#include "../include/common_functions.h"
using namespace std;

/*��Ļ����*/
void screen_set(int cmd_col, int cmd_row)
{
	cct_setconsoleborder(cmd_col, cmd_row);
	cct_gotoxy(0, 0);
	cout << "��Ļ��ǰ����Ϊ��" << cmd_row << "��" << cmd_col << "��\n";
}

/*����*/
void frame(int r, int c, bool split)
{
	int i, j;
	if (split == 0) {
		cct_gotoxy(0, 1);
		cout << ' ';
		for (j = 0; j < c; j++)
			cout << setw(6) << j;
		cout << endl;

		//��һ���Ʊ��
		cout << "  ";
		cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
		cout << "�X";
		for (j = 0; j < c; j++) {
			cout << "�T�T�T";
			Sleep(1);
		}
		cout << "�[";
		cct_setcolor();
		cout << endl;

		//�м�
		for (i = 0; i < r; i++) {
			cout << "  ";
			cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
			cout << "�U";
			for (j = 0; j < c; j++) {
				cout << "      ";
				Sleep(1);
			}
			cout << "�U";
			cct_setcolor();
			cout << endl;

			cout << (char)(i + 'A') << ' ';
			cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
			cout << "�U";
			for (j = 0; j < c; j++) {
				cout << "      ";
				Sleep(1);
			}
			cout << "�U";
			cct_setcolor();
			cout << endl;

			cout << "  ";
			cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
			cout << "�U";
			for (j = 0; j < c; j++) {
				cout << "      ";
				Sleep(1);
			}
			cout << "�U";
			cct_setcolor();
			cout << endl;
		}

		//���һ��
		cout << "  ";
		cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
		cout << "�^";
		for (j = 0; j < c; j++) {
			cout << "�T�T�T";
			Sleep(10);
		}
		cout << "�a";
		cct_setcolor();
		cout << endl;
	}
	else {
		cct_gotoxy(0, 1);
		cout << "  ";
		for (j = 0; j < c; j++)
			cout << "    " << j << "   ";
		cout << endl;

		//��һ���Ʊ��
		cout << "  ";
		cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
		cout << "�X";
		for (j = 0; j < c - 1; j++) {
			cout << "�T�T�T�j";
			Sleep(1);
		}
		cout << "�T�T�T�[";
		cct_setcolor();
		cout << endl;

		//�м�
		for (i = 0; i < r; i++) {
			cout << "  ";
			cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
			cout << "�U";
			for (j = 0; j < c; j++) {
				cout << "      �U";
				Sleep(1);
			}
			cct_setcolor();
			cout << endl;

			cout << (char)(i + 'A') << ' ';
			cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
			cout << "�U";
			for (j = 0; j < c; j++) {
				cout << "      �U";
				Sleep(1);
			}
			cct_setcolor();
			cout << endl;

			cout << "  ";
			cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
			cout << "�U";
			for (j = 0; j < c; j++) {
				cout << "      �U";
				Sleep(1);
			}
			cct_setcolor();
			cout << endl;

			if (i != r - 1) {
				cout << "  ";
				cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
				cout << "�d";
				for (j = 0; j < c - 1; j++) {
					cout << "�T�T�T�p";
					Sleep(1);
				}
				cout << "�T�T�T�g";
				cct_setcolor();
				cout << endl;
			}
		}

		//���һ��
		cout << "  ";
		cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
		cout << "�^";
		for (j = 0; j < c - 1; j++) {
			cout << "�T�T�T�m";
			Sleep(1);
		}
		cout << "�T�T�T�a";
		cct_setcolor();
		cout << endl;
	}
}

/*��ɫ��*/
void color_block(int p[][12], int r, int c, bool split)
{
	int X = 4, Y = 3, i, j;
	if (split == 0) {
		for (i = 1; i <= r; i++) {
			for (j = 1; j <= c; j++) {
				change_color(p, i, j, COLOR_BLACK);
				star(X, Y);
				X += 6;
			}
			X = 4;
			Y += 3;
		}
		cct_setcolor();
		cct_gotoxy(0, Y + 1);
		cout << "��ͷ��/����ƶ����س���/�������ѡ�񲢽���";
	}
	else {
		for (i = 1; i <= r; i++) {
			for (j = 1; j <= c; j++) {
				change_color(p, i, j, COLOR_BLACK);
				star(X, Y);
				X += 8;
			}
			X = 4;
			Y += 4;
		}
		cct_setcolor();
		cct_gotoxy(0, Y);
		cout << "��ͷ��/����ƶ����س���/�������ѡ�񲢽���";
	}
}

/*������*/
int MouseKey(int p[][12], int r, int c, bool split, char menu, int* total_score)
{
	while (1) {
		int X = 0, Y = 0;//�������
		int x = 4, y = 3;//һС��������
		int x_key = 4, y_key = 3;//��������
		int ret, maction;
		int keycode1, keycode2;
		int loop = 1;
		int i, j, k;
		char coordinate[2] = { 0 };

		cct_enable_mouse();
		cct_setcursor(CURSOR_INVISIBLE);

		if (split == 0) {
			Sleep(10);
			change_color(p, 1, 1, COLOR_WHITE);
			star(x, y);

			while (loop) {
				/* �����/���̣�����ֵΪ���������е�ĳһ��, ��ǰ���λ����<X,Y>�� */
				ret = cct_read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);
				if (ret == CCT_MOUSE_EVENT) {
					switch (maction) {
						case MOUSE_ONLY_MOVED:
							//�ָ���ɫ
							if (!(X >= x && X <= x + 5 && Y >= y && Y <= y + 2)) {
								change_color(p, (y - 3) / 3 + 1, (x - 4) / 6 + 1, COLOR_BLACK);
								if (p[(y - 3) / 3 + 1][(x - 4) / 6 + 1] == 0)
									cct_setcolor(COLOR_HWHITE, COLOR_HWHITE);
								star(x, y);
							}
							/*���*/
							for (i = 1; i <= r; i++) {
								for (j = 1; j <= c; j++) {
									if (X >= 4 + (j - 1) * 6 && X <= 9 + (j - 1) * 6 && Y >= 3 + (i - 1) * 3 && Y <= 5 + (i - 1) * 3 && p[i][j] != 0) {
										x_key = X;
										y_key = Y;
										x = 4 + (j - 1) * 6;
										y = 3 + (i - 1) * 3;
										coordinate[1] = j - 1 + '0';
										coordinate[0] = i - 1 + 'A';
										cct_setcolor();
										cct_gotoxy(0, 4 + r * 3);
										cout << "[��ǰ���] " << coordinate[0] << "��" << coordinate[1] << "��                                                                                                                                                    ";
										change_color(p, i, j, COLOR_WHITE);
										star(x, y);
									}
								}
							}
							if ((X <= 3 || X >= 10 + (c - 1) * 6) || (Y <= 2 || Y >= 6 + (r - 1) * 3)) {
								cct_gotoxy(0, 4 + r * 3);
								cct_setcolor();
								cout << "[��ǰ���] " << "λ�÷Ƿ�                                                                                                                                              ";
							}//����

							for (i = 1; i <= r; i++)
								for (j = 1; j <= c; j++)
									if (p[i][j] == 0 && X >= 4 + (j - 1) * 6 && X <= 9 + (j - 1) * 6 && Y >= 3 + (i - 1) * 3 && Y <= 5 + (i - 1) * 3) {
										cct_gotoxy(0, 4 + r * 3);
										cct_setcolor();
										cout << "[��ǰ���] " << "λ�÷Ƿ�                                                                                                                                              ";
									}//��Ϊ0

							break;
						case MOUSE_LEFT_BUTTON_CLICK:			//�������/

							//���ָ̻���ɫ
							change_color(p, (y - 3) / 3 + 1, (x - 4) / 6 + 1, COLOR_BLACK);
							if (p[(y - 3) / 3 + 1][(x - 4) / 6 + 1] == 0)
								cct_setcolor(COLOR_HWHITE, COLOR_HWHITE);
							star(x, y);

							for (i = 1; i <= r; i++) {
								for (j = 1; j <= c; j++) {
									if (X >= 4 + (j - 1) * 6 && X <= 9 + (j - 1) * 6 && Y >= 3 + (i - 1) * 3 && Y <= 5 + (i - 1) * 3 && p[i][j] != 0) {
										x = 4 + (j - 1) * 6;
										y = 3 + (i - 1) * 3;
										coordinate[1] = j - 1 + '0';
										coordinate[0] = i - 1 + 'A';
										change_color(p, i, j, COLOR_WHITE);
										star(x, y);
										cct_setcolor();
										cct_gotoxy(0, 4 + r * 3);
										if (menu == 'd' || menu == 'e') {
											cout << "ѡ����" << coordinate[0] << "��" << coordinate[1] << "��                                                                                                                ";
											cct_gotoxy(0, 5 + r * 3);
											cct_setcursor(CURSOR_VISIBLE_NORMAL);
											end();
											return 0;
										}
										if (menu == 'f') {
											char result[12][12] = { 0 };
											int k, m, select;
											for (k = 1; k <= r; k++)
												for (m = 1; m <= c; m++)
													result[k][m] = '0';
											same_array(i, j, result, p);//Ѱ����ͬ
											select = selected(result, p, x, y, r, c, 0, &x_key, &y_key, coordinate, total_score);
											x = x_key;
											y = y_key;
											if (select == 1) {
												cct_setcolor();
												return 0;
											}
											if (select == 2) {
												move(p, r, c, 'f', 0);
												cct_gotoxy(0, 5 + r * 3);
												cct_setcursor(CURSOR_VISIBLE_NORMAL);
												end();
												return 0;
											}
										}
									}
								}
							}
							break;
						case MOUSE_RIGHT_BUTTON_CLICK:			//�����Ҽ�
							for (i = 1; i <= r; i++) {
								for (j = 1; j <= c; j++) {
									if (X >= 4 + (j - 1) * 6 && X <= 9 + (j - 1) * 6 && Y >= 3 + (i - 1) * 3 && Y <= 5 + (i - 1) * 3 && p[i][j] != 0) {
										x = 4 + (j - 1) * 6;
										y = 3 + (i - 1) * 3;
										coordinate[1] = j - 1 + '0';
										coordinate[0] = i - 1 + 'A';
										change_color(p, i, j, COLOR_WHITE);
										star(x, y);
										cct_setcolor();
										cct_gotoxy(0, 4 + r * 3);

										if (menu == 'd' || menu == 'e') {
											cout << "ѡ����" << coordinate[0] << "��" << coordinate[1] << "��                                                                                                             ";
											cct_gotoxy(0, 5 + r * 3);
											cct_disable_mouse();	//�������
											cct_setcursor(CURSOR_VISIBLE_NORMAL);
											end();
											return 0;
										}
										if (menu == 'f') {
											cct_gotoxy(0, 4 + r * 3);
											cout << "                                                                ";
											cct_gotoxy(0, 5 + r * 3);
											cct_disable_mouse();	//�������
											cct_setcursor(CURSOR_VISIBLE_NORMAL);
											end();
											return 0;
										}
									}
								}
							}
							break;
						default:
							break;
					} //end of switch(maction)
				} //end of if (CCT_MOUSE_EVENT)
				else if (ret == CCT_KEYBOARD_EVENT) {

					switch (keycode1) {
						case 224:
							//�ָ���ɫ
							change_color(p, (y - 3) / 3 + 1, (x - 4) / 6 + 1, COLOR_BLACK);
							if (p[(y - 3) / 3 + 1][(x - 4) / 6 + 1] == 0)
								cct_setcolor(COLOR_HWHITE, COLOR_HWHITE);
							star(x, y);
							switch (keycode2) {
								case KB_ARROW_UP:

									/*���*/
									for (i = 1; i <= r; i++) {
										for (j = 1; j <= c; j++) {
											if (x_key >= 4 + (j - 1) * 6 && x_key <= 9 + (j - 1) * 6 && y_key >= 3 + (i - 1) * 3 && y_key <= 5 + (i - 1) * 3 && p[i][j] != 0) {

												if (i == 1) {//A������
													change_color(p, r, j, COLOR_WHITE);
													x = 4 + (j - 1) * 6;
													y = 3 + (r - 1) * 3;
													coordinate[1] = j - 1 + '0';
													coordinate[0] = 'A' + r - 1;
												}
												else {
													change_color(p, i - 1, j, COLOR_WHITE);
													x = 4 + (j - 1) * 6;
													y = (i - 1) * 3;
													coordinate[1] = j - 1 + '0';
													coordinate[0] = i - 1 + 'A' - 1;
												}

												star(x, y);

												cct_setcolor();
												cct_gotoxy(0, 4 + r * 3);
												cout << "[��ǰ����] " << coordinate[0] << "��" << coordinate[1] << "��                                                                                                                                                           ";
											}
										}
									}
									if (y_key >= 3 && y_key <= 5)
										y_key = 3 + (r - 1) * 3;
									else
										y_key -= 3;
									break;
								case KB_ARROW_DOWN:
									/*���*/
									for (i = 1; i <= r; i++) {
										for (j = 1; j <= c; j++) {
											if (x_key >= 4 + (j - 1) * 6 && x_key <= 9 + (j - 1) * 6 && y_key >= 3 + (i - 1) * 3 && y_key <= 5 + (i - 1) * 3 && p[i][j] != 0) {

												if (i == r) {//�����������
													change_color(p, 1, j, COLOR_WHITE);
													x = 4 + (j - 1) * 6;
													y = 3;
													coordinate[1] = j - 1 + '0';
													coordinate[0] = 'A';
												}
												else {
													change_color(p, i + 1, j, COLOR_WHITE);
													x = 4 + (j - 1) * 6;
													y = 3 + 3 + (i - 1) * 3;
													coordinate[1] = j - 1 + '0';
													coordinate[0] = i - 1 + 'A' + 1;
												}

												star(x, y);

												cct_setcolor();
												cct_gotoxy(0, 4 + r * 3);
												cout << "[��ǰ����] " << coordinate[0] << "��" << coordinate[1] << "��                                                                                                                                             ";
											}
										}
									}
									if (y_key >= 3 + (r - 1) * 3 && y_key <= 5 + (r - 1) * 3)
										y_key = 3;
									else
										y_key += 3;
									break;
								case KB_ARROW_LEFT:
									/*���*/
									for (i = 1; i <= r; i++) {
										for (j = 1; j <= c; j++) {
											if (x_key >= 4 + (j - 1) * 6 && x_key <= 9 + (j - 1) * 6 && y_key >= 3 + (i - 1) * 3 && y_key <= 5 + (i - 1) * 3 && p[i][j] != 0) {

												if (j == 1) {//����������
													change_color(p, i, c, COLOR_WHITE);
													x = 4 + (c - 1) * 6;
													y = 3 + (i - 1) * 3;
													coordinate[1] = '0' + c - 1;
													coordinate[0] = i - 1 + 'A';
												}
												else {
													change_color(p, i, j - 1, COLOR_WHITE);
													x = 4 + (j - 1) * 6 - 6;
													y = 3 + (i - 1) * 3;
													coordinate[1] = j - 1 + '0' - 1;
													coordinate[0] = i - 1 + 'A';
												}

												star(x, y);

												cct_setcolor();
												cct_gotoxy(0, 4 + r * 3);
												cout << "[��ǰ����] " << coordinate[0] << "��" << coordinate[1] << "��                                                                                                                                               ";
											}
										}
									}
									if (x_key >= 4 && x_key <= 9)
										x_key = 4 + (c - 1) * 6;
									else
										x_key -= 6;
									break;
								case KB_ARROW_RIGHT:
									/*���*/
									for (i = 1; i <= r; i++) {
										for (j = 1; j <= c; j++) {
											if (x_key >= 4 + (j - 1) * 6 && x_key <= 9 + (j - 1) * 6 && y_key >= 3 + (i - 1) * 3 && y_key <= 5 + (i - 1) * 3 && p[i][j] != 0) {

												if (j == c) {//����������
													change_color(p, i, 1, COLOR_WHITE);
													x = 4;
													y = 3 + (i - 1) * 3;
													coordinate[1] = '0';
													coordinate[0] = i - 1 + 'A';
												}
												else {
													change_color(p, i, j + 1, COLOR_WHITE);
													x = 4 + (j - 1) * 6 + 6;
													y = 3 + (i - 1) * 3;
													coordinate[1] = j - 1 + '0' + 1;
													coordinate[0] = i - 1 + 'A';
												}

												star(x, y);

												cct_setcolor();
												cct_gotoxy(0, 4 + r * 3);
												cout << "[��ǰ����] " << coordinate[0] << "��" << coordinate[1] << "��                                                                                                                                             ";
											}
										}
									}
									if (x_key >= 4 + (c - 1) * 6 && x_key <= 9 + (c - 1) * 6)
										x_key = 4;
									else
										x_key += 6;
									break;
							}
							break;
						case 13:
						case 81:
						case 113:
							for (i = 1; i <= r; i++) {
								for (j = 1; j <= c; j++) {
									if (x_key >= 4 + (j - 1) * 6 && x_key <= 9 + (j - 1) * 6 && y_key >= 3 + (i - 1) * 3 && y_key <= 5 + (i - 1) * 3 && p[i][j] != 0) {
										x = 4 + (j - 1) * 6;
										y = 3 + (i - 1) * 3;
										coordinate[1] = j - 1 + '0';
										coordinate[0] = i - 1 + 'A';
										change_color(p, i, j, COLOR_WHITE);
										star(x, y);
										cct_setcolor();
										cct_gotoxy(0, 4 + r * 3);
										if (menu == 'd' || menu == 'e') {
											cout << "ѡ����" << coordinate[0] << "��" << coordinate[1] << "��                                                                                                            ";
											cct_gotoxy(0, 5 + r * 3);
											cct_setcursor(CURSOR_VISIBLE_NORMAL);
											end();
											return 0;
										}
										if (menu == 'f' && keycode1 != 13) {
											cct_gotoxy(0, 4 + r * 3);
											cout << "                                                                ";
											cct_gotoxy(0, 5 + r * 3);
											cct_disable_mouse();	//�������
											cct_setcursor(CURSOR_VISIBLE_NORMAL);
											end();
											return 0;
										}
									}
								}
							}
							if (menu == 'f' && keycode1 == 13) {
								char result[12][12] = { 0 };
								int k, m, select;
								for (k = 1; k <= r; k++)
									for (m = 1; m <= c; m++)
										result[k][m] = '0';
								same_array((y - 3) / 3 + 1, (x - 4) / 6 + 1, result, p);//Ѱ����ͬ
								select = selected(result, p, x, y, r, c, 0, &x_key, &y_key, coordinate, total_score);
								x = x_key;
								y = y_key;
								if (select == 1) {
									cct_setcolor();
									return 0;
								}
								if (select == 2) {
									move(p, r, c, 'f', 0);
									cct_gotoxy(0, 5 + r * 3);
									cct_setcursor(CURSOR_VISIBLE_NORMAL);
									end();
									return 0;
								}
							}
							break;
						default:
							break;
					}//end of swicth(keycode1)
				}//end of else if(ret == CCT_KEYBOARD_EVENT��
			} //end of while(1)

			cct_disable_mouse();	//�������
			cct_setcursor(CURSOR_VISIBLE_NORMAL);	//�򿪹��
		}
		else {
			Sleep(10);
			for (j = 1; j <= c; j++) {
				for (i = 1; i <= r; i++)
					if (p[i][j] != 0)
						break;
				if (p[i][j] != 0)
					break;
			}
			change_color(p, i, j, COLOR_WHITE);
			star(8 * j - 4, 4 * i - 1);
			x_key = 8 * j - 4;
			y_key = 4 * i - 1;

			cct_setcolor();
			cct_gotoxy(0, 3 + r * 4);
			cout << "��ͷ��/����ƶ����س���/�������ѡ��Q/�����Ҽ�����";

			while (loop) {
				/* �����/���̣�����ֵΪ���������е�ĳһ��, ��ǰ���λ����<X,Y>�� */
				ret = cct_read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);
				if (ret == CCT_MOUSE_EVENT) {
					switch (maction) {
						case MOUSE_ONLY_MOVED:

							for (j = 1; j <= c; j++) {
								for (i = 1; i <= r; i++)
									if (p[i][j] != 0)
										break;
								if (p[i][j] != 0)
									break;
							}
							change_color(p, i, j, COLOR_BLACK);
							star(8 * j - 4, 4 * i - 1);

							//�ָ���ɫ
							if (!(X >= x && X <= x + 5 && Y >= y && Y <= y + 2)) {
								change_color(p, (y + 1) / 4, (x + 4) / 8, COLOR_BLACK);
								if (p[(y + 1) / 4][(x + 4) / 8] == 0)
									cct_setcolor(COLOR_HWHITE, COLOR_HWHITE);

								star(x, y);
							}
							/*���*/
							for (i = 1; i <= r; i++) {
								for (j = 1; j <= c; j++) {
									if (X >= 8 * j - 4 && X <= 8 * j - 4 + 5 && Y >= 4 * i - 1 && Y <= 4 * i - 1 + 2 && p[i][j] != 0) {
										x = 8 * j - 4;
										y = 4 * i - 1;
										x_key = x;
										y_key = y;
										coordinate[1] = j - 1 + '0';
										coordinate[0] = i - 1 + 'A';
										cct_setcolor();
										cct_gotoxy(0, 3 + r * 4);
										cout << "[��ǰ���] " << coordinate[0] << "��" << coordinate[1] << "��                                                                                                         ";
										change_color(p, i, j, COLOR_WHITE);
										star(x, y);
									}
								}
							}
							for (i = 1; i <= r; i++)
								for (j = 1; j <= c; j++)
									if (X >= 8 * j - 4 && X <= 8 * j - 4 + 5 && Y >= 4 * i - 1 && Y <= 4 * i - 1 + 2 && p[i][j] == 0) {
										cct_gotoxy(0, 3 + r * 4);
										cct_setcolor();
										cout << "[��ǰ���] " << "λ�÷Ƿ�                                                                                                           ";
									}
							//��Ϊ0

							if ((X <= 3 || X >= 8 * c - 4 + 6) || (Y <= 2 || Y >= 4 * r - 1 + 4) || (X % 8 == 2 || X % 8 == 3) || (Y % 4 == 2)) {
								cct_gotoxy(0, 3 + r * 4);
								cct_setcolor();
								cout << "[��ǰ���] " << "λ�÷Ƿ�                                                                                                                                              ";
								
							}

							break;
						case MOUSE_LEFT_BUTTON_CLICK:			//������� /

							//���ָ̻���ɫ/
							change_color(p, (y + 1) / 4, (x + 4) / 8, COLOR_BLACK);
							if (p[(y + 1) / 4][(x + 4) / 8] == 0)
								cct_setcolor(COLOR_HWHITE, COLOR_HWHITE);

							star(x, y);

							for (i = 1; i <= r; i++) {
								for (j = 1; j <= c; j++) {
									if (X >= 8 * j - 4 && X <= 8 * j - 4 + 5 && Y >= 4 * i - 1 && Y <= 4 * i - 1 + 2 && p[i][j] != 0) {
										x = 8 * j - 4;
										y = 4 * i - 1;
										coordinate[1] = j - 1 + '0';
										coordinate[0] = i - 1 + 'A';
										change_color(p, i, j, COLOR_WHITE);
										star(x, y);
										cct_setcolor();
										cct_gotoxy(0, 3 + r * 4);
										if (menu == 'd' || menu == 'e') {
											cout << "ѡ����" << coordinate[0] << "��" << coordinate[1] << "��                                                ";
											cct_gotoxy(0, 4 + r * 4);
											cct_setcursor(CURSOR_VISIBLE_NORMAL);
											end();
											return 0;
										}
										if (menu == 'g') {
											char result[12][12] = { 0 };
											int k, m, select;
											for (k = 1; k <= r; k++)
												for (m = 1; m <= c; m++)
													result[k][m] = '0';
											same_array(i, j, result, p);//Ѱ����ͬ
											select = selected(result, p, x, y, r, c, 1, &x_key, &y_key, coordinate, total_score);
											x = x_key;
											y = y_key;
											if (select == 1) {
												cct_setcolor();
												return 0;
											}
											if (select == 2) {
												move(p, r, c, 'g', 1);
												loop = 0;
											}
										}
									}
								}
							}
							break;
						case MOUSE_RIGHT_BUTTON_CLICK:			//�����Ҽ� /
							for (i = 1; i <= r; i++) {
								for (j = 1; j <= c; j++) {
									if (X >= 8 * j - 4 && X <= 8 * j - 4 + 5 && Y >= 4 * i - 1 && Y <= 4 * i - 1 + 2 && p[i][j] != 0) {
										x = 8 * j - 4;
										y = 4 * i - 1;
										coordinate[1] = j - 1 + '0';
										coordinate[0] = i - 1 + 'A';
										change_color(p, i, j, COLOR_WHITE);
										star(x, y);
										cct_setcolor();
										cct_gotoxy(0, 3 + r * 4);
										if (menu == 'd' || menu == 'e') {
											cout << "ѡ����" << coordinate[0] << "��" << coordinate[1] << "��                                                ";
											cct_gotoxy(0, 4 + r * 4);
											cct_setcursor(CURSOR_VISIBLE_NORMAL);
											end();
											return 0;
										}
										if (menu == 'g') {
											cout << "                                                                ";
											cct_gotoxy(0, 4 + r * 4);
											cct_disable_mouse();	//�������
											cct_setcursor(CURSOR_VISIBLE_NORMAL);
											end();
											return 0;
										}
									}
								}
							}
							break;
						default:
							break;
					} //end of switch(maction)
				} //end of if (CCT_MOUSE_EVENT)
				else if (ret == CCT_KEYBOARD_EVENT) {

					switch (keycode1) {
						case 224:
							//�ָ���ɫ
							change_color(p, (y_key + 1) / 4, (x_key + 4) / 8, COLOR_BLACK);
							if (p[(y_key + 1) / 4][(x_key + 4) / 8] == 0)
								cct_setcolor(COLOR_HWHITE, COLOR_HWHITE);
							star(x_key, y_key);

							switch (keycode2) {
								case KB_ARROW_UP:

									/*���*/
									for (i = 1; i <= r; i++)
										for (j = 1; j <= c; j++) {
											if (x_key >= 8 * j - 4 && x_key <= 8 * j - 4 + 5 && y_key >= 4 * i - 1 && y_key <= 4 * i - 1 + 2 && p[i][j] != 0) {

												if (p[i - 1][j] == 0) {//A������
													change_color(p, r, j, COLOR_WHITE);
													x = 8 * j - 4;
													y = 4 * r - 1;
													coordinate[1] = j - 1 + '0';
													coordinate[0] = 'A' + r - 1;
												}
												else {
													change_color(p, i - 1, j, COLOR_WHITE);
													x = 8 * j - 4;
													y = 4 * i - 1 - 4;
													coordinate[1] = j - 1 + '0';
													coordinate[0] = i - 1 + 'A' - 1;
												}

												star(x, y);
												cct_setcolor();
												cct_gotoxy(0, 3 + r * 4);
												cout << "[��ǰ����] " << coordinate[0] << "��" << coordinate[1] << "��                                                                                                         ";
											}
										}

									if (p[(y_key + 1) / 4 - 1][(x_key + 4) / 8] == 0)
										y_key = 4 * r - 1;
									else
										y_key -= 4;
									break;
								case KB_ARROW_DOWN:
									/*���*/
									for (i = 1; i <= r; i++)
										for (j = 1; j <= c; j++) {
											if (x_key >= 8 * j - 4 && x_key <= 8 * j - 4 + 5 && y_key >= 4 * i - 1 && y_key <= 4 * i - 1 + 2 && p[i][j] != 0) {

												for (k = 1; p[k][j] == 0; k++)
													;

												if (i == r) {//�����������
													change_color(p, k, j, COLOR_WHITE);
													x = 8 * j - 4;
													y = 4 * k - 1;
													coordinate[1] = j - 1 + '0';
													coordinate[0] = k - 1 + 'A';
												}
												else {
													change_color(p, i + 1, j, COLOR_WHITE);
													x = 8 * j - 4;
													y = 4 * i - 1 + 4;
													coordinate[1] = j - 1 + '0';
													coordinate[0] = i - 1 + 'A' + 1;
												}

												star(x, y);

												cct_setcolor();
												cct_gotoxy(0, 3 + r * 4);
												cout << "[��ǰ����] " << coordinate[0] << "��" << coordinate[1] << "��                                                                                                         ";
											}
										}

									if (y_key >= 4 * r - 1 && y_key <= 4 * r - 1 + 3)
										y_key = 4 * k - 1;
									else
										y_key += 4;
									break;
								case KB_ARROW_LEFT:
									/*���*/
									for (i = 1; i <= r; i++) {
										for (j = 1; j <= c; j++) {
											if (x_key >= 8 * j - 4 && x_key <= 8 * j - 4 + 5 && y_key >= 4 * i - 1 && y_key <= 4 * i - 1 + 2 && p[i][j] != 0) {

												if (j == 1) {
													for (k = c; p[i][k] == 0; k--)
														;
													change_color(p, i, k, COLOR_WHITE);
													x = 8 * k - 4;
													y = 4 * i - 1;
													coordinate[1] = '0' + k - 1;
													coordinate[0] = i - 1 + 'A';
												}
												else {
													for (k = j - 1; p[i][k] == 0; k--)
														if (k == 0)
															break;
													if (k == 0)
														for (k = c; p[i][k] == 0; k--)
															;

													change_color(p, i, k, COLOR_WHITE);
													x = 8 * k - 4;
													y = 4 * i - 1;
													coordinate[1] = k - 1 + '0';
													coordinate[0] = i - 1 + 'A';
												}

												star(x, y);

												cct_setcolor();
												cct_gotoxy(0, 3 + r * 4);
												cout << "[��ǰ����] " << coordinate[0] << "��" << coordinate[1] << "��                                                                                                         ";
											}
										}
									}
									x_key = 8 * k - 4;

									break;
								case KB_ARROW_RIGHT:
									/*���*/
									for (i = 1; i <= r; i++) {
										for (j = 1; j <= c; j++) {
											if (x_key >= 8 * j - 4 && x_key <= 8 * j - 4 + 5 && y_key >= 4 * i - 1 && y_key <= 4 * i - 1 + 2 && p[i][j] != 0) {

												if (j == c) {//����������
													for (k = 1; p[i][k] == 0; k++)
														;
													change_color(p, i, k, COLOR_WHITE);
													x = 8 * k - 4;
													y = 4 * i - 1;
													coordinate[1] = '0' + k - 1;
													coordinate[0] = i - 1 + 'A';
												}
												else {
													for (k = j + 1; p[i][k] == 0; k++)
														if (k == c + 1)
															break;
													if (k == c + 1)
														for (k = 0; p[i][k] == 0; k++)
															;
													change_color(p, i, k, COLOR_WHITE);
													x = 8 * k - 4;
													y = 4 * i - 1;
													coordinate[1] = k - 1 + '0';
													coordinate[0] = i - 1 + 'A';
												}

												star(x, y);

												cct_setcolor();
												cct_gotoxy(0, 3 + r * 4);
												cout << "[��ǰ����] " << coordinate[0] << "��" << coordinate[1] << "��                                                                                                         ";
											}
										}
									}
									x_key = 8 * k - 4;
									break;
							}
							break;
						case 13:
						case 81:
						case 113:
							for (i = 1; i <= r; i++) {
								for (j = 1; j <= c; j++) {
									if (x_key >= 8 * j - 4 && x_key <= 8 * j - 4 + 5 && y_key >= 4 * i - 1 && y_key <= 4 * i - 1 + 2 && p[i][j] != 0) {
										x = 8 * j - 4;
										y = 4 * i - 1;
										coordinate[1] = j - 1 + '0';
										coordinate[0] = i - 1 + 'A';
										change_color(p, i, j, COLOR_WHITE);
										star(x, y);
										cct_setcolor();
										cct_gotoxy(0, 3 + r * 4);
										if (menu == 'd' || menu == 'e') {
											cout << "ѡ����" << coordinate[0] << "��" << coordinate[1] << "��                                                ";
											cct_gotoxy(0, 4 + r * 4);
											cct_setcursor(CURSOR_VISIBLE_NORMAL);
											end();
											return 0;
										}
										if (menu == 'g' && keycode1 != 13) {
											cout << "                                                                ";
											cct_gotoxy(0, 4 + r * 4);
											cct_disable_mouse();	//�������
											cct_setcursor(CURSOR_VISIBLE_NORMAL);
											end();
											return 0;
										}
									}
								}
							}
							if (menu == 'g' && keycode1 == 13) {
								char result[12][12] = { 0 };
								int k, m, select;
								for (k = 1; k <= r; k++)
									for (m = 1; m <= c; m++)
										result[k][m] = '0';
								same_array((y + 1) / 4, (x + 4) / 8, result, p);//Ѱ����ͬ
								select = selected(result, p, x, y, r, c, 1, &x_key, &y_key, coordinate, total_score);
								x = x_key;
								y = y_key;
								if (select == 1) {
									cct_setcolor();
									return 0;
								}
								if (select == 2) {
									move(p, r, c, 'g', 1);
									loop = 0;
								}
							}
							break;
						default:
							break;
					}//end of swicth(keycode1)
				}//end of else if(ret == CCT_KEYBOARD_EVENT��
			} //end of while(1)

			if (over(p, r, c) != 0) {
				bonus(over(p, r, c), total_score);
				cct_setcolor(COLOR_BLACK, COLOR_HYELLOW);
				cct_gotoxy(0, 3 + r * 4);
				cout << "ʣ��" << over(p, r, c) << "�����ǣ��޿���������ؽ���!";
				cct_setcolor();
				cout << "�س�������һ��";
				while (1) {
					ret = cct_read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);
					if (ret == CCT_KEYBOARD_EVENT && keycode1 == 13)
						return 1;
				}
			}

			cct_disable_mouse();	//�������
			cct_setcursor(CURSOR_VISIBLE_NORMAL);	//�򿪹��

		}
	}
}

/*ѡ�к���ʧ*/
int selected(char result[][12], int p[][12], int x, int y, int r, int c, bool split, int* x_key, int* y_key, char* coordinate, int* total_score)
{
	//�β�x,y��ѡ�񷽿��������
	int i, j, k, sum = 0;
	int x_array, y_array;
	int X, Y;//�������
	int ret, maction;
	int keycode1, keycode2;
	int loop = 1;

	*x_key = x;
	*y_key = y;

	/*�ݹ�ѡ��*/
	if (split == 0) {
		for (i = 1; i <= r; i++) {
			for (j = 1; j <= c; j++) {
				if (result[i][j] == '*') {
					x_array = 4 + (j - 1) * 6;
					y_array = 3 + (i - 1) * 3;
					change_color(p, i, j, COLOR_WHITE);
					star(x_array, y_array);
					sum++;
				}
			}
		}
		if (sum == 1) {
			cct_gotoxy(0, 4 + r * 3);
			cct_setcolor(COLOR_BLACK, COLOR_HYELLOW);
			cout << "��Χ����ֵͬ��";
			cct_setcolor();
			cout << "��ͷ��/����ƶ����س���/�������ѡ��Q/�����Ҽ�����";
		}
		else {
			change_color(p, (y - 3) / 3 + 1, (x - 4) / 6 + 1, COLOR_HWHITE);
			star(x, y);
			cct_setcolor();
			cct_gotoxy(0, 4 + r * 3);
			cout << "��ͷ��/����ƶ�ȡ����ǰѡ�񣬻س���/��������ϳ�";
		}
		while (loop) {
			/* �����/���̣�����ֵΪ���������е�ĳһ��, ��ǰ���λ����<X,Y>�� */
			ret = cct_read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);
			if (ret == CCT_MOUSE_EVENT) {
				switch (maction) {
					case MOUSE_ONLY_MOVED:
						if (!(X >= x && X <= x + 5 && Y >= y && Y <= y + 2)) {//�ָ���ɫ
							for (i = 1; i <= r; i++) {
								for (j = 1; j <= c; j++) {
									if (result[i][j] == '*') {
										x_array = 4 + (j - 1) * 6;
										y_array = 3 + (i - 1) * 3;
										change_color(p, i, j, COLOR_BLACK);
										star(x_array, y_array);
									}
								}
							}
							return 0;
						}
						break;
					case MOUSE_RIGHT_BUTTON_CLICK:
						cct_setcolor();
						cct_gotoxy(0, 4 + r * 3);
						cout << "                                                                                                                                                      ";
						cct_gotoxy(0, 5 + r * 3);
						cct_disable_mouse();	//�������
						cct_setcursor(CURSOR_VISIBLE_NORMAL);
						end();
						return 1;
						break;
					case MOUSE_LEFT_BUTTON_CLICK:
						if (sum == 1)
							break;
						else {
							vanish_array(result, p, r, c);
							for (i = 1; i <= r; i++) {
								for (j = 1; j <= c; j++) {
									if (p[i][j] == 0) {
										x_array = 4 + (j - 1) * 6;
										y_array = 3 + (i - 1) * 3;
										cct_setcolor(COLOR_HWHITE, COLOR_HWHITE);
										star(x_array, y_array);
									}
								}
							}
							cct_setcolor();
							cct_gotoxy(0, 0);
							SCORE(result, r, c, total_score);
							cct_gotoxy(0, 4 + r * 3);
							cout << "�ϳ���ɣ��س���/�����������                                                ";
							return 2;
							break;
						}
					default:
						break;

				}
			}
			else if (ret == CCT_KEYBOARD_EVENT) {
				switch (keycode1) {
					case 224:
						//�ָ���ɫ
						for (i = 1; i <= r; i++) {
							for (j = 1; j <= c; j++) {
								if (result[i][j] == '*') {
									x_array = 4 + (j - 1) * 6;
									y_array = 3 + (i - 1) * 3;
									change_color(p, i, j, COLOR_BLACK);
									star(x_array, y_array);
								}
							}
						}
						i = (y - 3) / 3 + 1;
						j = (x - 4) / 6 + 1;
						switch (keycode2) {
							case KB_ARROW_UP:
								if (i == 1) {//A������
									change_color(p, r, j, COLOR_WHITE);
									x_array = 4 + (j - 1) * 6;
									y_array = 3 + (r - 1) * 3;
									coordinate[1] = j - 1 + '0';
									coordinate[0] = i - 1 + 'A' + r - 1;
								}
								else {
									change_color(p, i - 1, j, COLOR_WHITE);
									x_array = 4 + (j - 1) * 6;
									y_array = (i - 1) * 3;
									coordinate[1] = j - 1 + '0';
									coordinate[0] = i - 1 + 'A' - 1;
								}
								star(x_array, y_array);

								cct_setcolor();
								cct_gotoxy(0, 4 + r * 3);
								cout << "[��ǰ����] " << coordinate[0] << "��" << coordinate[1] << "��                                                                                                                                                           ";


								if (*y_key >= 3 && *y_key <= 5)
									*y_key = 3 + (r - 1) * 3;
								else
									*y_key -= 3;
								return 0;
								break;
							case KB_ARROW_DOWN:
								if (i == r) {//�����������
									change_color(p, 1, j, COLOR_WHITE);
									x_array = 4 + (j - 1) * 6;
									y_array = 3;
									coordinate[1] = j - 1 + '0';
									coordinate[0] = 'A';
								}
								else {
									change_color(p, i + 1, j, COLOR_WHITE);
									x_array = 4 + (j - 1) * 6;
									y_array = 3 + 3 + (i - 1) * 3;
									coordinate[1] = j - 1 + '0';
									coordinate[0] = i - 1 + 'A' + 1;
								}
								star(x_array, y_array);

								cct_setcolor();
								cct_gotoxy(0, 4 + r * 3);
								cout << "[��ǰ����] " << coordinate[0] << "��" << coordinate[1] << "��                                                                                                                                                           ";


								if (*y_key >= 3 + (r - 1) * 3 && *y_key <= 5 + (r - 1) * 3)
									*y_key = 3;
								else
									*y_key += 3;
								return 0;
								break;
							case KB_ARROW_LEFT:
								if (j == 1) {//����������
									change_color(p, i, c, COLOR_WHITE);
									x_array = 4 + (c - 1) * 6;
									y_array = 3 + (i - 1) * 3;
									coordinate[1] = '0' + c - 1;
									coordinate[0] = i - 1 + 'A';
								}
								else {
									change_color(p, i, j - 1, COLOR_WHITE);
									x_array = 4 + (j - 1) * 6 - 6;
									y_array = 3 + (i - 1) * 3;
									coordinate[1] = j - 1 + '0' - 1;
									coordinate[0] = i - 1 + 'A';
								}
								star(x_array, y_array);
								cct_setcolor();
								cct_gotoxy(0, 4 + r * 3);
								cout << "[��ǰ����] " << coordinate[0] << "��" << coordinate[1] << "��                                                                                                                                                           ";


								if (*x_key >= 4 && *x_key <= 9)
									*x_key = 4 + (c - 1) * 6;
								else
									*x_key -= 6;
								return 0;
								break;
							case KB_ARROW_RIGHT:
								if (j == c) {//����������
									change_color(p, i, 1, COLOR_WHITE);
									x_array = 4;
									y_array = 3 + (i - 1) * 3;
									coordinate[1] = '0';
									coordinate[0] = i - 1 + 'A';
								}
								else {
									change_color(p, i, j + 1, COLOR_WHITE);
									x_array = 4 + (j - 1) * 6 + 6;
									y_array = 3 + (i - 1) * 3;
									coordinate[1] = j - 1 + '0' + 1;
									coordinate[0] = i - 1 + 'A';
								}
								star(x_array, y_array);

								cct_setcolor();
								cct_gotoxy(0, 4 + r * 3);
								cout << "[��ǰ����] " << coordinate[0] << "��" << coordinate[1] << "��                                                                                                                                                           ";
								if (*x_key >= 4 + (c - 1) * 6 && *x_key <= 9 + (c - 1) * 6)
									*x_key = 4;
								else
									*x_key += 6;
								return 0;
								break;
						}
					case 13:
						if (sum == 1)
							break;
						else {
							vanish_array(result, p, r, c);
							for (i = 1; i <= r; i++) {
								for (j = 1; j <= c; j++) {
									if (p[i][j] == 0) {
										x_array = 4 + (j - 1) * 6;
										y_array = 3 + (i - 1) * 3;
										cct_setcolor(COLOR_HWHITE, COLOR_HWHITE);
										star(x_array, y_array);
									}
								}
							}
							cct_setcolor();
							cct_gotoxy(0, 0);
							SCORE(result, r, c, total_score);
							cct_gotoxy(0, 4 + r * 3);
							cout << "�ϳ���ɣ��س���/�����������                                                ";
							return 2;
							break;
						}
					case 81:
					case 113:
						cct_setcolor();
						cct_gotoxy(0, 4 + r * 3);
						cout << "                                                                                                                                                      ";
						cct_gotoxy(0, 5 + r * 3);
						cct_disable_mouse();	//�������
						cct_setcursor(CURSOR_VISIBLE_NORMAL);
						end();
						return 1;
						break;
				}
			}
		}
	}
	//for G 
	else {
		for (i = 1; i <= r; i++) {
			for (j = 1; j <= c; j++) {
				if (result[i][j] == '*') {
					x_array = 8 * j - 4;
					y_array = 4 * i - 1;
					change_color(p, i, j, COLOR_WHITE);
					star(x_array, y_array);
					sum++;
				}
			}
		}
		if (sum == 1) {
			cct_gotoxy(0, 3 + r * 4);
			cct_setcolor(COLOR_BLACK, COLOR_HYELLOW);
			cout << "��Χ����ֵͬ��";
			cct_setcolor();
			cout << "��ͷ��/����ƶ����س���/�������ѡ��Q/�����Ҽ�����";
		}
		else {
			change_color(p, (y + 1) / 4, (x + 4) / 8, COLOR_HWHITE);
			star(x, y);
			cct_setcolor();
			cct_gotoxy(0, 3 + r * 4);
			cout << "��ͷ��/����ƶ�ȡ����ǰѡ�񣬻س���/��������ϳ�";
		}
		while (loop) {
			/* �����/���̣�����ֵΪ���������е�ĳһ��, ��ǰ���λ����<X,Y>�� */
			ret = cct_read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);
			if (ret == CCT_MOUSE_EVENT) {
				switch (maction) {
					case MOUSE_ONLY_MOVED:
						if (!(X >= x && X <= x + 5 && Y >= y && Y <= y + 2)) {//�ָ���ɫ
							for (i = 1; i <= r; i++) {
								for (j = 1; j <= c; j++) {
									if (result[i][j] == '*') {
										x_array = 8 * j - 4;
										y_array = 4 * i - 1;
										change_color(p, i, j, COLOR_BLACK);
										star(x_array, y_array);
									}
								}
							}
							return 0;
						}
						break;
					case MOUSE_RIGHT_BUTTON_CLICK:
						cct_setcolor();
						cct_gotoxy(0, 3 + r * 4);
						cout << "                                                                                                                                                      ";
						cct_gotoxy(0, 4 + r * 4);
						cct_disable_mouse();	//�������
						cct_setcursor(CURSOR_VISIBLE_NORMAL);
						end();
						return 1;
						break;
					case MOUSE_LEFT_BUTTON_CLICK:
						if (sum == 1)
							break;
						else {
							vanish_array(result, p, r, c);
							for (i = 1; i <= r; i++) {
								for (j = 1; j <= c; j++) {
									if (p[i][j] == 0) {
										x_array = 8 * j - 4;
										y_array = 4 * i - 1;
										cct_gotoxy(x_array, y_array);
										cct_setcolor(COLOR_HWHITE, COLOR_HWHITE);
										star(x_array, y_array);
									}
								}
							}
							cct_setcolor();
							cct_gotoxy(0, 0);
							SCORE(result, r, c, total_score);
							cct_gotoxy(0, 3 + r * 4);
							cout << "                                                                                                      ";
							return 2;
							break;
						}
					default:
						break;

				}
			}
			else if (ret == CCT_KEYBOARD_EVENT) {
				switch (keycode1) {
					case 224:
						//�ָ���ɫ
						for (i = 1; i <= r; i++) {
							for (j = 1; j <= c; j++) {
								if (result[i][j] == '*') {
									x_array = 8 * j - 4;
									y_array = 4 * i - 1;
									cct_gotoxy(x_array, y_array);
									change_color(p, i, j, COLOR_BLACK);
									star(x_array, y_array);
								}
							}
						}
						i = (y + 1) / 4;
						j = (x + 4) / 8;
						switch (keycode2) {
							case KB_ARROW_UP:
								if (p[i - 1][j] == 0) {//A������
									change_color(p, r, j, COLOR_WHITE);
									*x_key = 8 * j - 4;
									*y_key = 4 * r - 1;
									coordinate[1] = j - 1 + '0';
									coordinate[0] = 'A' + r - 1;
								}
								else {
									change_color(p, i - 1, j, COLOR_WHITE);
									*x_key = 8 * j - 4;
									*y_key = 4 * i - 1 - 4;
									coordinate[1] = j - 1 + '0';
									coordinate[0] = i - 1 + 'A' - 1;
								}

								star(*x_key, *y_key);
								cct_setcolor();
								cct_gotoxy(0, 3 + r * 4);
								cout << "[��ǰ����] " << coordinate[0] << "��" << coordinate[1] << "��                                                                                                         ";

								return 0;
								break;
							case KB_ARROW_DOWN:
								for (k = 1; p[k][j] == 0; k++)
									;

								if (i == r) {//�����������
									change_color(p, k, j, COLOR_WHITE);
									*x_key = 8 * j - 4;
									*y_key = 4 * k - 1;
									coordinate[1] = j - 1 + '0';
									coordinate[0] = k - 1 + 'A';
								}
								else {
									change_color(p, i + 1, j, COLOR_WHITE);
									*x_key = 8 * j - 4;
									*y_key = 4 * i - 1 + 4;
									coordinate[1] = j - 1 + '0';
									coordinate[0] = i - 1 + 'A' + 1;
								}

								star(*x_key, *y_key);

								cct_setcolor();
								cct_gotoxy(0, 3 + r * 4);
								cout << "[��ǰ����] " << coordinate[0] << "��" << coordinate[1] << "��                                                                                                         ";
								return 0;
								break;
							case KB_ARROW_LEFT:
								if (j == 1) {
									for (k = c; p[i][k] == 0; k--)
										;
									change_color(p, i, k, COLOR_WHITE);
									*x_key = 8 * k - 4;
									*y_key = 4 * i - 1;
									coordinate[1] = '0' + k - 1;
									coordinate[0] = i - 1 + 'A';
								}
								else {
									for (k = j - 1; p[i][k] == 0; k--)
										if (k == 0)
											break;
									if (k == 0)
										for (k = c; p[i][k] == 0; k--)
											;

									change_color(p, i, k, COLOR_WHITE);
									*x_key = 8 * k - 4;
									*y_key = 4 * i - 1;
									coordinate[1] = k - 1 + '0';
									coordinate[0] = i - 1 + 'A';
								}

								star(*x_key, *y_key);

								cct_setcolor();
								cct_gotoxy(0, 3 + r * 4);
								cout << "[��ǰ����] " << coordinate[0] << "��" << coordinate[1] << "��                                                                                                         ";
								return 0;
								break;
							case KB_ARROW_RIGHT:
								if (j == c) {//����������
									for (k = 1; p[i][k] == 0; k++)
										;
									change_color(p, i, k, COLOR_WHITE);
									*x_key = 8 * k - 4;
									*y_key = 4 * i - 1;
									coordinate[1] = '0' + k - 1;
									coordinate[0] = i - 1 + 'A';
								}
								else {
									for (k = j + 1; p[i][k] == 0; k++)
										if (k == c + 1)
											break;
									if (k == c + 1)
										for (k = 0; p[i][k] == 0; k++)
											;
									change_color(p, i, k, COLOR_WHITE);
									*x_key = 8 * k - 4;
									*y_key = 4 * i - 1;
									coordinate[1] = k - 1 + '0';
									coordinate[0] = i - 1 + 'A';
								}

								star(*x_key, *y_key);

								cct_setcolor();
								cct_gotoxy(0, 3 + r * 4);
								cout << "[��ǰ����] " << coordinate[0] << "��" << coordinate[1] << "��                                                                                                         ";
								return 0;
								break;
						}
					case 13:
						if (sum == 1)
							break;
						else {
							vanish_array(result, p, r, c);
							for (i = 1; i <= r; i++) {
								for (j = 1; j <= c; j++) {
									if (p[i][j] == 0) {
										x_array = 8 * j - 4;
										y_array = 4 * i - 1;
										cct_gotoxy(x_array, y_array);
										cct_setcolor(COLOR_HWHITE, COLOR_HWHITE);
										star(x_array, y_array);
									}
								}
							}
							cct_setcolor();
							cct_gotoxy(0, 0);
							SCORE(result, r, c, total_score);
							cct_gotoxy(0, 3 + r * 4);
							cout << "                                                                                                      ";
							return 2;
							break;
						}
					case 81:
					case 113:
						cct_setcolor();
						cct_gotoxy(0, 3 + r * 4);
						cout << "                                                                                                                                                      ";
						cct_gotoxy(0, 4 + r * 4);
						cct_disable_mouse();	//�������
						cct_setcursor(CURSOR_VISIBLE_NORMAL);
						end();
						return 1;
						break;
				}
			}
		}
	}
	return 0;
}

/*�����ƽ��*/
void move(int p[][12], int r, int c, char menu, bool split)
{
	int i, j, sum1 = 0, sum2 = 0, k, t, m;
	int color = 0;
	int x_srt, y_srt, x_fin, y_fin, x_now, y_now;//x,y�Ƿ����������
	int X, Y;//�������
	int ret, maction;
	int keycode1, keycode2;
	int loop = 1;

	if (split == 0) {

		cct_enable_mouse();
		cct_setcursor(CURSOR_INVISIBLE);
		while (loop) {
			/* �����/���̣�����ֵΪ���������е�ĳһ��, ��ǰ���λ����<X,Y>�� */
			ret = cct_read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);
			if ((ret == CCT_MOUSE_EVENT && maction == MOUSE_LEFT_BUTTON_CLICK) || (ret == CCT_KEYBOARD_EVENT && keycode1 == 13)) {

				/*����*/
				for (j = 1; j <= c; j++)
					for (i = r; i >= 1; i--)
						if (p[i][j] == 0)
							for (k = i - 1; k >= 1; k--)
								if (p[k][j] != 0) {

									x_srt = 4 + (j - 1) * 6;
									y_srt = 3 + (k - 1) * 3;
									x_fin = 4 + (j - 1) * 6;
									y_fin = 3 + (i - 1) * 3;
									x_now = x_fin;

									if (p[k][j] == 1)
										color = COLOR_BLUE;
									if (p[k][j] == 2)
										color = COLOR_HYELLOW;
									if (p[k][j] == 3)
										color = COLOR_HCYAN;
									if (p[k][j] == 4)
										color = COLOR_CYAN;
									if (p[k][j] == 5)
										color = COLOR_HRED;

									for (y_now = y_srt; y_now <= y_fin; y_now++) {
										cct_showstr(x_now, y_now, "�X�T�[", color, COLOR_BLACK);
										cct_showstr(x_now, y_now + 1, "�U��U", color, COLOR_BLACK);
										cct_showstr(x_now, y_now + 2, "�^�T�a", color, COLOR_BLACK);
										Sleep(1);
										if (y_now != y_fin) {
											cct_showstr(x_now, y_now, "�X�T�[", COLOR_HWHITE, COLOR_HWHITE);
											cct_showstr(x_now, y_now + 1, "�U��U", COLOR_HWHITE, COLOR_HWHITE);
											cct_showstr(x_now, y_now + 2, "�^�T�a", COLOR_HWHITE, COLOR_HWHITE);
										}
									}


									t = p[i][j];
									p[i][j] = p[k][j];
									p[k][j] = t;
									break;
								}

				/*����ƽ��*/
				for (j = 1; j <= c; j++) {
					for (i = r; i >= 1; i--)
						if (p[i][j] == 0)
							sum1++;

					for (k = j + 1; k <= c; k++) {
						for (m = r; m >= 1; m--)
							if (p[m][k] == 0)
								sum2++;

						if (sum1 == r && sum1 != sum2) {
							for (i = r; i >= 1; i--) {

								x_srt = 4 + (k - 1) * 6;
								y_srt = 3 + (i - 1) * 3;
								x_fin = 4 + (j - 1) * 6;
								y_fin = 3 + (i - 1) * 3;
								y_now = y_fin;

								if (p[i][k] == 1)
									color = COLOR_BLUE;
								if (p[i][k] == 2)
									color = COLOR_HYELLOW;
								if (p[i][k] == 3)
									color = COLOR_HCYAN;
								if (p[i][k] == 4)
									color = COLOR_CYAN;
								if (p[i][k] == 5)
									color = COLOR_HRED;

								for (x_now = x_srt; x_now >= x_fin; x_now--) {
									cct_showstr(x_now, y_now, "�X�T�[", color, COLOR_BLACK);
									cct_showstr(x_now, y_now + 1, "�U��U", color, COLOR_BLACK);
									cct_showstr(x_now, y_now + 2, "�^�T�a", color, COLOR_BLACK);
									Sleep(1);
									if (x_now != x_fin) {
										cct_showstr(x_now, y_now, "�X�T�[", COLOR_HWHITE, COLOR_HWHITE);
										cct_showstr(x_now, y_now + 1, "�U��U", COLOR_HWHITE, COLOR_HWHITE);
										cct_showstr(x_now, y_now + 2, "�^�T�a", COLOR_HWHITE, COLOR_HWHITE);
									}
								}

								t = p[i][j];
								p[i][j] = p[i][k];
								p[i][k] = t;
							}
							break;
						}
					}
					sum1 = 0;
					sum2 = 0;
				}
				cct_showstr(0, 4 + r * 3, "���κϳɽ�������C/������������µ�һ�κϳ�", COLOR_BLACK, COLOR_HYELLOW);
				while (1) {
					ret = cct_read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);
					if ((ret == CCT_MOUSE_EVENT && maction == MOUSE_LEFT_BUTTON_CLICK) || (ret == CCT_KEYBOARD_EVENT && (keycode1 == 67 || keycode1 == 99))) {
						cct_showstr(0, 4 + r * 3, "                                                                                                 ", COLOR_BLACK, COLOR_WHITE);
						return;
					}
				}
			}
		}
	}
	//for G
	else {
		/*����*/
		for (j = 1; j <= c; j++)
			for (i = r; i >= 1; i--)
				if (p[i][j] == 0)
					for (k = i - 1; k >= 1; k--)
						if (p[k][j] != 0) {

							x_srt = 8 * j - 4;
							y_srt = 4 * k - 1;
							x_fin = 8 * j - 4;
							y_fin = 4 * i - 1;
							x_now = x_fin;

							if (p[k][j] == 1)
								color = COLOR_BLUE;
							if (p[k][j] == 2)
								color = COLOR_HYELLOW;
							if (p[k][j] == 3)
								color = COLOR_HCYAN;
							if (p[k][j] == 4)
								color = COLOR_CYAN;
							if (p[k][j] == 5)
								color = COLOR_HRED;

							for (y_now = y_srt; y_now <= y_fin; y_now++) {
								if (y_now % 4 == 3)
									cct_showstr(x_now, y_now - 1, "�T�T�T", COLOR_HWHITE, COLOR_BLACK);
								cct_showstr(x_now, y_now, "�X�T�[", color, COLOR_BLACK);
								cct_showstr(x_now, y_now + 1, "�U��U", color, COLOR_BLACK);
								cct_showstr(x_now, y_now + 2, "�^�T�a", color, COLOR_BLACK);
								Sleep(1);
								if (y_now != y_fin) {
									cct_showstr(x_now, y_now, "�X�T�[", COLOR_HWHITE, COLOR_HWHITE);
									cct_showstr(x_now, y_now + 1, "�U��U", COLOR_HWHITE, COLOR_HWHITE);
									cct_showstr(x_now, y_now + 2, "�^�T�a", COLOR_HWHITE, COLOR_HWHITE);
								}
							}


							t = p[i][j];
							p[i][j] = p[k][j];
							p[k][j] = t;
							break;
						}

		/*����ƽ��*/
		for (j = 1; j <= c; j++) {
			for (i = r; i >= 1; i--)
				if (p[i][j] == 0)
					sum1++;

			for (k = j + 1; k <= c; k++) {
				for (m = r; m >= 1; m--)
					if (p[m][k] == 0)
						sum2++;

				if (sum1 == r && sum1 != sum2) {
					for (i = r; p[i][k] != 0; i--) {

						x_srt = 8 * k - 4;
						y_srt = 4 * i - 1;
						x_fin = 8 * j - 4;
						y_fin = 4 * i - 1;
						y_now = y_fin;

						if (p[i][k] == 1)
							color = COLOR_BLUE;
						if (p[i][k] == 2)
							color = COLOR_HYELLOW;
						if (p[i][k] == 3)
							color = COLOR_HCYAN;
						if (p[i][k] == 4)
							color = COLOR_CYAN;
						if (p[i][k] == 5)
							color = COLOR_HRED;

						for (x_now = x_srt; x_now >= x_fin; x_now--) {
							if (x_now % 8 == 4) {
								cct_showstr(x_now + 6, y_now, "�U", COLOR_HWHITE, COLOR_BLACK);
								cct_showstr(x_now, y_now, "�X�T�[", color, COLOR_BLACK);
								cct_showstr(x_now + 6, y_now + 1, "�U", COLOR_HWHITE, COLOR_BLACK);
								cct_showstr(x_now, y_now + 1, "�U��U", color, COLOR_BLACK);
								cct_showstr(x_now + 6, y_now + 2, "�U", COLOR_HWHITE, COLOR_BLACK);
								cct_showstr(x_now, y_now + 2, "�^�T�a", color, COLOR_BLACK);
							}
							cct_showstr(x_now, y_now, "�X�T�[", color, COLOR_BLACK);
							cct_showstr(x_now, y_now + 1, "�U��U", color, COLOR_BLACK);
							cct_showstr(x_now, y_now + 2, "�^�T�a", color, COLOR_BLACK);
							Sleep(1);
							if (x_now != x_fin) {
								cct_showstr(x_now, y_now, "�X�T�[", COLOR_HWHITE, COLOR_HWHITE);
								cct_showstr(x_now, y_now + 1, "�U��U", COLOR_HWHITE, COLOR_HWHITE);
								cct_showstr(x_now, y_now + 2, "�^�T�a", COLOR_HWHITE, COLOR_HWHITE);
							}
						}

						t = p[i][j];
						p[i][j] = p[i][k];
						p[i][k] = t;
					}
					break;
				}
				sum2 = 0;
			}
			sum2 = 0;
			sum1 = 0;
		}
	}
}

/*���Ƿ��Իָ��ȵȵĸ���ɫ*/
void change_color(int p[][12], int x_p, int y_p, int fg_color)
{
	if (p[x_p][y_p] == 1)
		cct_setcolor(COLOR_BLUE, fg_color);
	if (p[x_p][y_p] == 2)
		cct_setcolor(COLOR_HYELLOW, fg_color);
	if (p[x_p][y_p] == 3)
		cct_setcolor(COLOR_HCYAN, fg_color);
	if (p[x_p][y_p] == 4)
		cct_setcolor(COLOR_CYAN, fg_color);
	if (p[x_p][y_p] == 5)
		cct_setcolor(COLOR_HRED, fg_color);
}
