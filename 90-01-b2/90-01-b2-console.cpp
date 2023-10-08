//2251206 冯羽芯 计科 
#include <iostream>
#include <iomanip>
#include <Windows.h>
#include "../include/cmd_console_tools.h"
#include "./90-01-b2.h"
#include "../include/common_functions.h"
using namespace std;

/*屏幕设置*/
void screen_set(int cmd_col, int cmd_row)
{
	cct_setconsoleborder(cmd_col, cmd_row);
	cct_gotoxy(0, 0);
	cout << "屏幕当前设置为：" << cmd_row << "行" << cmd_col << "列\n";
}

/*外框架*/
void frame(int r, int c, bool split)
{
	int i, j;
	if (split == 0) {
		cct_gotoxy(0, 1);
		cout << ' ';
		for (j = 0; j < c; j++)
			cout << setw(6) << j;
		cout << endl;

		//第一行制表符
		cout << "  ";
		cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
		cout << "╔";
		for (j = 0; j < c; j++) {
			cout << "═══";
			Sleep(1);
		}
		cout << "╗";
		cct_setcolor();
		cout << endl;

		//中间
		for (i = 0; i < r; i++) {
			cout << "  ";
			cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
			cout << "║";
			for (j = 0; j < c; j++) {
				cout << "      ";
				Sleep(1);
			}
			cout << "║";
			cct_setcolor();
			cout << endl;

			cout << (char)(i + 'A') << ' ';
			cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
			cout << "║";
			for (j = 0; j < c; j++) {
				cout << "      ";
				Sleep(1);
			}
			cout << "║";
			cct_setcolor();
			cout << endl;

			cout << "  ";
			cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
			cout << "║";
			for (j = 0; j < c; j++) {
				cout << "      ";
				Sleep(1);
			}
			cout << "║";
			cct_setcolor();
			cout << endl;
		}

		//最后一行
		cout << "  ";
		cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
		cout << "╚";
		for (j = 0; j < c; j++) {
			cout << "═══";
			Sleep(10);
		}
		cout << "╝";
		cct_setcolor();
		cout << endl;
	}
	else {
		cct_gotoxy(0, 1);
		cout << "  ";
		for (j = 0; j < c; j++)
			cout << "    " << j << "   ";
		cout << endl;

		//第一行制表符
		cout << "  ";
		cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
		cout << "╔";
		for (j = 0; j < c - 1; j++) {
			cout << "═══╦";
			Sleep(1);
		}
		cout << "═══╗";
		cct_setcolor();
		cout << endl;

		//中间
		for (i = 0; i < r; i++) {
			cout << "  ";
			cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
			cout << "║";
			for (j = 0; j < c; j++) {
				cout << "      ║";
				Sleep(1);
			}
			cct_setcolor();
			cout << endl;

			cout << (char)(i + 'A') << ' ';
			cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
			cout << "║";
			for (j = 0; j < c; j++) {
				cout << "      ║";
				Sleep(1);
			}
			cct_setcolor();
			cout << endl;

			cout << "  ";
			cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
			cout << "║";
			for (j = 0; j < c; j++) {
				cout << "      ║";
				Sleep(1);
			}
			cct_setcolor();
			cout << endl;

			if (i != r - 1) {
				cout << "  ";
				cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
				cout << "╠";
				for (j = 0; j < c - 1; j++) {
					cout << "═══╬";
					Sleep(1);
				}
				cout << "═══╣";
				cct_setcolor();
				cout << endl;
			}
		}

		//最后一行
		cout << "  ";
		cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
		cout << "╚";
		for (j = 0; j < c - 1; j++) {
			cout << "═══╩";
			Sleep(1);
		}
		cout << "═══╝";
		cct_setcolor();
		cout << endl;
	}
}

/*画色块*/
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
		cout << "箭头键/鼠标移动，回车键/单击左键选择并结束";
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
		cout << "箭头键/鼠标移动，回车键/单击左键选择并结束";
	}
}

/*鼠标键盘*/
int MouseKey(int p[][12], int r, int c, bool split, char menu, int* total_score)
{
	while (1) {
		int X = 0, Y = 0;//鼠标坐标
		int x = 4, y = 3;//一小格首坐标
		int x_key = 4, y_key = 3;//键盘坐标
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
				/* 读鼠标/键盘，返回值为下述操作中的某一种, 当前鼠标位置在<X,Y>处 */
				ret = cct_read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);
				if (ret == CCT_MOUSE_EVENT) {
					switch (maction) {
						case MOUSE_ONLY_MOVED:
							//恢复颜色
							if (!(X >= x && X <= x + 5 && Y >= y && Y <= y + 2)) {
								change_color(p, (y - 3) / 3 + 1, (x - 4) / 6 + 1, COLOR_BLACK);
								if (p[(y - 3) / 3 + 1][(x - 4) / 6 + 1] == 0)
									cct_setcolor(COLOR_HWHITE, COLOR_HWHITE);
								star(x, y);
							}
							/*变白*/
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
										cout << "[当前鼠标] " << coordinate[0] << "行" << coordinate[1] << "列                                                                                                                                                    ";
										change_color(p, i, j, COLOR_WHITE);
										star(x, y);
									}
								}
							}
							if ((X <= 3 || X >= 10 + (c - 1) * 6) || (Y <= 2 || Y >= 6 + (r - 1) * 3)) {
								cct_gotoxy(0, 4 + r * 3);
								cct_setcolor();
								cout << "[当前鼠标] " << "位置非法                                                                                                                                              ";
							}//出框

							for (i = 1; i <= r; i++)
								for (j = 1; j <= c; j++)
									if (p[i][j] == 0 && X >= 4 + (j - 1) * 6 && X <= 9 + (j - 1) * 6 && Y >= 3 + (i - 1) * 3 && Y <= 5 + (i - 1) * 3) {
										cct_gotoxy(0, 4 + r * 3);
										cct_setcolor();
										cout << "[当前鼠标] " << "位置非法                                                                                                                                              ";
									}//数为0

							break;
						case MOUSE_LEFT_BUTTON_CLICK:			//按下左键/

							//键盘恢复颜色
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
											cout << "选中了" << coordinate[0] << "行" << coordinate[1] << "列                                                                                                                ";
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
											same_array(i, j, result, p);//寻找相同
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
						case MOUSE_RIGHT_BUTTON_CLICK:			//按下右键
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
											cout << "选中了" << coordinate[0] << "行" << coordinate[1] << "列                                                                                                             ";
											cct_gotoxy(0, 5 + r * 3);
											cct_disable_mouse();	//禁用鼠标
											cct_setcursor(CURSOR_VISIBLE_NORMAL);
											end();
											return 0;
										}
										if (menu == 'f') {
											cct_gotoxy(0, 4 + r * 3);
											cout << "                                                                ";
											cct_gotoxy(0, 5 + r * 3);
											cct_disable_mouse();	//禁用鼠标
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
							//恢复颜色
							change_color(p, (y - 3) / 3 + 1, (x - 4) / 6 + 1, COLOR_BLACK);
							if (p[(y - 3) / 3 + 1][(x - 4) / 6 + 1] == 0)
								cct_setcolor(COLOR_HWHITE, COLOR_HWHITE);
							star(x, y);
							switch (keycode2) {
								case KB_ARROW_UP:

									/*变白*/
									for (i = 1; i <= r; i++) {
										for (j = 1; j <= c; j++) {
											if (x_key >= 4 + (j - 1) * 6 && x_key <= 9 + (j - 1) * 6 && y_key >= 3 + (i - 1) * 3 && y_key <= 5 + (i - 1) * 3 && p[i][j] != 0) {

												if (i == 1) {//A往上走
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
												cout << "[当前键盘] " << coordinate[0] << "行" << coordinate[1] << "列                                                                                                                                                           ";
											}
										}
									}
									if (y_key >= 3 && y_key <= 5)
										y_key = 3 + (r - 1) * 3;
									else
										y_key -= 3;
									break;
								case KB_ARROW_DOWN:
									/*变白*/
									for (i = 1; i <= r; i++) {
										for (j = 1; j <= c; j++) {
											if (x_key >= 4 + (j - 1) * 6 && x_key <= 9 + (j - 1) * 6 && y_key >= 3 + (i - 1) * 3 && y_key <= 5 + (i - 1) * 3 && p[i][j] != 0) {

												if (i == r) {//最底下往下走
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
												cout << "[当前键盘] " << coordinate[0] << "行" << coordinate[1] << "列                                                                                                                                             ";
											}
										}
									}
									if (y_key >= 3 + (r - 1) * 3 && y_key <= 5 + (r - 1) * 3)
										y_key = 3;
									else
										y_key += 3;
									break;
								case KB_ARROW_LEFT:
									/*变白*/
									for (i = 1; i <= r; i++) {
										for (j = 1; j <= c; j++) {
											if (x_key >= 4 + (j - 1) * 6 && x_key <= 9 + (j - 1) * 6 && y_key >= 3 + (i - 1) * 3 && y_key <= 5 + (i - 1) * 3 && p[i][j] != 0) {

												if (j == 1) {//最左往左走
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
												cout << "[当前键盘] " << coordinate[0] << "行" << coordinate[1] << "列                                                                                                                                               ";
											}
										}
									}
									if (x_key >= 4 && x_key <= 9)
										x_key = 4 + (c - 1) * 6;
									else
										x_key -= 6;
									break;
								case KB_ARROW_RIGHT:
									/*变白*/
									for (i = 1; i <= r; i++) {
										for (j = 1; j <= c; j++) {
											if (x_key >= 4 + (j - 1) * 6 && x_key <= 9 + (j - 1) * 6 && y_key >= 3 + (i - 1) * 3 && y_key <= 5 + (i - 1) * 3 && p[i][j] != 0) {

												if (j == c) {//最右往右走
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
												cout << "[当前键盘] " << coordinate[0] << "行" << coordinate[1] << "列                                                                                                                                             ";
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
											cout << "选中了" << coordinate[0] << "行" << coordinate[1] << "列                                                                                                            ";
											cct_gotoxy(0, 5 + r * 3);
											cct_setcursor(CURSOR_VISIBLE_NORMAL);
											end();
											return 0;
										}
										if (menu == 'f' && keycode1 != 13) {
											cct_gotoxy(0, 4 + r * 3);
											cout << "                                                                ";
											cct_gotoxy(0, 5 + r * 3);
											cct_disable_mouse();	//禁用鼠标
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
								same_array((y - 3) / 3 + 1, (x - 4) / 6 + 1, result, p);//寻找相同
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
				}//end of else if(ret == CCT_KEYBOARD_EVENT）
			} //end of while(1)

			cct_disable_mouse();	//禁用鼠标
			cct_setcursor(CURSOR_VISIBLE_NORMAL);	//打开光标
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
			cout << "箭头键/鼠标移动，回车键/单击左键选择，Q/单击右键结束";

			while (loop) {
				/* 读鼠标/键盘，返回值为下述操作中的某一种, 当前鼠标位置在<X,Y>处 */
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

							//恢复颜色
							if (!(X >= x && X <= x + 5 && Y >= y && Y <= y + 2)) {
								change_color(p, (y + 1) / 4, (x + 4) / 8, COLOR_BLACK);
								if (p[(y + 1) / 4][(x + 4) / 8] == 0)
									cct_setcolor(COLOR_HWHITE, COLOR_HWHITE);

								star(x, y);
							}
							/*变白*/
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
										cout << "[当前鼠标] " << coordinate[0] << "行" << coordinate[1] << "列                                                                                                         ";
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
										cout << "[当前鼠标] " << "位置非法                                                                                                           ";
									}
							//数为0

							if ((X <= 3 || X >= 8 * c - 4 + 6) || (Y <= 2 || Y >= 4 * r - 1 + 4) || (X % 8 == 2 || X % 8 == 3) || (Y % 4 == 2)) {
								cct_gotoxy(0, 3 + r * 4);
								cct_setcolor();
								cout << "[当前鼠标] " << "位置非法                                                                                                                                              ";
								
							}

							break;
						case MOUSE_LEFT_BUTTON_CLICK:			//按下左键 /

							//键盘恢复颜色/
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
											cout << "选中了" << coordinate[0] << "行" << coordinate[1] << "列                                                ";
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
											same_array(i, j, result, p);//寻找相同
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
						case MOUSE_RIGHT_BUTTON_CLICK:			//按下右键 /
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
											cout << "选中了" << coordinate[0] << "行" << coordinate[1] << "列                                                ";
											cct_gotoxy(0, 4 + r * 4);
											cct_setcursor(CURSOR_VISIBLE_NORMAL);
											end();
											return 0;
										}
										if (menu == 'g') {
											cout << "                                                                ";
											cct_gotoxy(0, 4 + r * 4);
											cct_disable_mouse();	//禁用鼠标
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
							//恢复颜色
							change_color(p, (y_key + 1) / 4, (x_key + 4) / 8, COLOR_BLACK);
							if (p[(y_key + 1) / 4][(x_key + 4) / 8] == 0)
								cct_setcolor(COLOR_HWHITE, COLOR_HWHITE);
							star(x_key, y_key);

							switch (keycode2) {
								case KB_ARROW_UP:

									/*变白*/
									for (i = 1; i <= r; i++)
										for (j = 1; j <= c; j++) {
											if (x_key >= 8 * j - 4 && x_key <= 8 * j - 4 + 5 && y_key >= 4 * i - 1 && y_key <= 4 * i - 1 + 2 && p[i][j] != 0) {

												if (p[i - 1][j] == 0) {//A往上走
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
												cout << "[当前键盘] " << coordinate[0] << "行" << coordinate[1] << "列                                                                                                         ";
											}
										}

									if (p[(y_key + 1) / 4 - 1][(x_key + 4) / 8] == 0)
										y_key = 4 * r - 1;
									else
										y_key -= 4;
									break;
								case KB_ARROW_DOWN:
									/*变白*/
									for (i = 1; i <= r; i++)
										for (j = 1; j <= c; j++) {
											if (x_key >= 8 * j - 4 && x_key <= 8 * j - 4 + 5 && y_key >= 4 * i - 1 && y_key <= 4 * i - 1 + 2 && p[i][j] != 0) {

												for (k = 1; p[k][j] == 0; k++)
													;

												if (i == r) {//最底下往下走
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
												cout << "[当前键盘] " << coordinate[0] << "行" << coordinate[1] << "列                                                                                                         ";
											}
										}

									if (y_key >= 4 * r - 1 && y_key <= 4 * r - 1 + 3)
										y_key = 4 * k - 1;
									else
										y_key += 4;
									break;
								case KB_ARROW_LEFT:
									/*变白*/
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
												cout << "[当前键盘] " << coordinate[0] << "行" << coordinate[1] << "列                                                                                                         ";
											}
										}
									}
									x_key = 8 * k - 4;

									break;
								case KB_ARROW_RIGHT:
									/*变白*/
									for (i = 1; i <= r; i++) {
										for (j = 1; j <= c; j++) {
											if (x_key >= 8 * j - 4 && x_key <= 8 * j - 4 + 5 && y_key >= 4 * i - 1 && y_key <= 4 * i - 1 + 2 && p[i][j] != 0) {

												if (j == c) {//最右往右走
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
												cout << "[当前键盘] " << coordinate[0] << "行" << coordinate[1] << "列                                                                                                         ";
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
											cout << "选中了" << coordinate[0] << "行" << coordinate[1] << "列                                                ";
											cct_gotoxy(0, 4 + r * 4);
											cct_setcursor(CURSOR_VISIBLE_NORMAL);
											end();
											return 0;
										}
										if (menu == 'g' && keycode1 != 13) {
											cout << "                                                                ";
											cct_gotoxy(0, 4 + r * 4);
											cct_disable_mouse();	//禁用鼠标
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
								same_array((y + 1) / 4, (x + 4) / 8, result, p);//寻找相同
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
				}//end of else if(ret == CCT_KEYBOARD_EVENT）
			} //end of while(1)

			if (over(p, r, c) != 0) {
				bonus(over(p, r, c), total_score);
				cct_setcolor(COLOR_BLACK, COLOR_HYELLOW);
				cct_gotoxy(0, 3 + r * 4);
				cout << "剩余" << over(p, r, c) << "个星星，无可消除项，本关结束!";
				cct_setcolor();
				cout << "回车继续下一关";
				while (1) {
					ret = cct_read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);
					if (ret == CCT_KEYBOARD_EVENT && keycode1 == 13)
						return 1;
				}
			}

			cct_disable_mouse();	//禁用鼠标
			cct_setcursor(CURSOR_VISIBLE_NORMAL);	//打开光标

		}
	}
}

/*选中和消失*/
int selected(char result[][12], int p[][12], int x, int y, int r, int c, bool split, int* x_key, int* y_key, char* coordinate, int* total_score)
{
	//形参x,y是选择方块的首坐标
	int i, j, k, sum = 0;
	int x_array, y_array;
	int X, Y;//鼠标坐标
	int ret, maction;
	int keycode1, keycode2;
	int loop = 1;

	*x_key = x;
	*y_key = y;

	/*递归选中*/
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
			cout << "周围无相同值，";
			cct_setcolor();
			cout << "箭头键/鼠标移动，回车键/单击左键选择，Q/单击右键结束";
		}
		else {
			change_color(p, (y - 3) / 3 + 1, (x - 4) / 6 + 1, COLOR_HWHITE);
			star(x, y);
			cct_setcolor();
			cct_gotoxy(0, 4 + r * 3);
			cout << "箭头键/鼠标移动取消当前选择，回车键/单击左键合成";
		}
		while (loop) {
			/* 读鼠标/键盘，返回值为下述操作中的某一种, 当前鼠标位置在<X,Y>处 */
			ret = cct_read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);
			if (ret == CCT_MOUSE_EVENT) {
				switch (maction) {
					case MOUSE_ONLY_MOVED:
						if (!(X >= x && X <= x + 5 && Y >= y && Y <= y + 2)) {//恢复颜色
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
						cct_disable_mouse();	//禁用鼠标
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
							cout << "合成完成，回车键/单击左键下落                                                ";
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
						//恢复颜色
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
								if (i == 1) {//A往上走
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
								cout << "[当前键盘] " << coordinate[0] << "行" << coordinate[1] << "列                                                                                                                                                           ";


								if (*y_key >= 3 && *y_key <= 5)
									*y_key = 3 + (r - 1) * 3;
								else
									*y_key -= 3;
								return 0;
								break;
							case KB_ARROW_DOWN:
								if (i == r) {//最底下往下走
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
								cout << "[当前键盘] " << coordinate[0] << "行" << coordinate[1] << "列                                                                                                                                                           ";


								if (*y_key >= 3 + (r - 1) * 3 && *y_key <= 5 + (r - 1) * 3)
									*y_key = 3;
								else
									*y_key += 3;
								return 0;
								break;
							case KB_ARROW_LEFT:
								if (j == 1) {//最左往左走
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
								cout << "[当前键盘] " << coordinate[0] << "行" << coordinate[1] << "列                                                                                                                                                           ";


								if (*x_key >= 4 && *x_key <= 9)
									*x_key = 4 + (c - 1) * 6;
								else
									*x_key -= 6;
								return 0;
								break;
							case KB_ARROW_RIGHT:
								if (j == c) {//最右往右走
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
								cout << "[当前键盘] " << coordinate[0] << "行" << coordinate[1] << "列                                                                                                                                                           ";
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
							cout << "合成完成，回车键/单击左键下落                                                ";
							return 2;
							break;
						}
					case 81:
					case 113:
						cct_setcolor();
						cct_gotoxy(0, 4 + r * 3);
						cout << "                                                                                                                                                      ";
						cct_gotoxy(0, 5 + r * 3);
						cct_disable_mouse();	//禁用鼠标
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
			cout << "周围无相同值，";
			cct_setcolor();
			cout << "箭头键/鼠标移动，回车键/单击左键选择，Q/单击右键结束";
		}
		else {
			change_color(p, (y + 1) / 4, (x + 4) / 8, COLOR_HWHITE);
			star(x, y);
			cct_setcolor();
			cct_gotoxy(0, 3 + r * 4);
			cout << "箭头键/鼠标移动取消当前选择，回车键/单击左键合成";
		}
		while (loop) {
			/* 读鼠标/键盘，返回值为下述操作中的某一种, 当前鼠标位置在<X,Y>处 */
			ret = cct_read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);
			if (ret == CCT_MOUSE_EVENT) {
				switch (maction) {
					case MOUSE_ONLY_MOVED:
						if (!(X >= x && X <= x + 5 && Y >= y && Y <= y + 2)) {//恢复颜色
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
						cct_disable_mouse();	//禁用鼠标
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
						//恢复颜色
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
								if (p[i - 1][j] == 0) {//A往上走
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
								cout << "[当前键盘] " << coordinate[0] << "行" << coordinate[1] << "列                                                                                                         ";

								return 0;
								break;
							case KB_ARROW_DOWN:
								for (k = 1; p[k][j] == 0; k++)
									;

								if (i == r) {//最底下往下走
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
								cout << "[当前键盘] " << coordinate[0] << "行" << coordinate[1] << "列                                                                                                         ";
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
								cout << "[当前键盘] " << coordinate[0] << "行" << coordinate[1] << "列                                                                                                         ";
								return 0;
								break;
							case KB_ARROW_RIGHT:
								if (j == c) {//最右往右走
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
								cout << "[当前键盘] " << coordinate[0] << "行" << coordinate[1] << "列                                                                                                         ";
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
						cct_disable_mouse();	//禁用鼠标
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

/*下落和平移*/
void move(int p[][12], int r, int c, char menu, bool split)
{
	int i, j, sum1 = 0, sum2 = 0, k, t, m;
	int color = 0;
	int x_srt, y_srt, x_fin, y_fin, x_now, y_now;//x,y是方块的首坐标
	int X, Y;//鼠标坐标
	int ret, maction;
	int keycode1, keycode2;
	int loop = 1;

	if (split == 0) {

		cct_enable_mouse();
		cct_setcursor(CURSOR_INVISIBLE);
		while (loop) {
			/* 读鼠标/键盘，返回值为下述操作中的某一种, 当前鼠标位置在<X,Y>处 */
			ret = cct_read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);
			if ((ret == CCT_MOUSE_EVENT && maction == MOUSE_LEFT_BUTTON_CLICK) || (ret == CCT_KEYBOARD_EVENT && keycode1 == 13)) {

				/*纵向*/
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
										cct_showstr(x_now, y_now, "╔═╗", color, COLOR_BLACK);
										cct_showstr(x_now, y_now + 1, "║★║", color, COLOR_BLACK);
										cct_showstr(x_now, y_now + 2, "╚═╝", color, COLOR_BLACK);
										Sleep(1);
										if (y_now != y_fin) {
											cct_showstr(x_now, y_now, "╔═╗", COLOR_HWHITE, COLOR_HWHITE);
											cct_showstr(x_now, y_now + 1, "║★║", COLOR_HWHITE, COLOR_HWHITE);
											cct_showstr(x_now, y_now + 2, "╚═╝", COLOR_HWHITE, COLOR_HWHITE);
										}
									}


									t = p[i][j];
									p[i][j] = p[k][j];
									p[k][j] = t;
									break;
								}

				/*横向平移*/
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
									cct_showstr(x_now, y_now, "╔═╗", color, COLOR_BLACK);
									cct_showstr(x_now, y_now + 1, "║★║", color, COLOR_BLACK);
									cct_showstr(x_now, y_now + 2, "╚═╝", color, COLOR_BLACK);
									Sleep(1);
									if (x_now != x_fin) {
										cct_showstr(x_now, y_now, "╔═╗", COLOR_HWHITE, COLOR_HWHITE);
										cct_showstr(x_now, y_now + 1, "║★║", COLOR_HWHITE, COLOR_HWHITE);
										cct_showstr(x_now, y_now + 2, "╚═╝", COLOR_HWHITE, COLOR_HWHITE);
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
				cct_showstr(0, 4 + r * 3, "本次合成结束，按C/单击左键继续新的一次合成", COLOR_BLACK, COLOR_HYELLOW);
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
		/*纵向*/
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
									cct_showstr(x_now, y_now - 1, "═══", COLOR_HWHITE, COLOR_BLACK);
								cct_showstr(x_now, y_now, "╔═╗", color, COLOR_BLACK);
								cct_showstr(x_now, y_now + 1, "║★║", color, COLOR_BLACK);
								cct_showstr(x_now, y_now + 2, "╚═╝", color, COLOR_BLACK);
								Sleep(1);
								if (y_now != y_fin) {
									cct_showstr(x_now, y_now, "╔═╗", COLOR_HWHITE, COLOR_HWHITE);
									cct_showstr(x_now, y_now + 1, "║★║", COLOR_HWHITE, COLOR_HWHITE);
									cct_showstr(x_now, y_now + 2, "╚═╝", COLOR_HWHITE, COLOR_HWHITE);
								}
							}


							t = p[i][j];
							p[i][j] = p[k][j];
							p[k][j] = t;
							break;
						}

		/*横向平移*/
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
								cct_showstr(x_now + 6, y_now, "║", COLOR_HWHITE, COLOR_BLACK);
								cct_showstr(x_now, y_now, "╔═╗", color, COLOR_BLACK);
								cct_showstr(x_now + 6, y_now + 1, "║", COLOR_HWHITE, COLOR_BLACK);
								cct_showstr(x_now, y_now + 1, "║★║", color, COLOR_BLACK);
								cct_showstr(x_now + 6, y_now + 2, "║", COLOR_HWHITE, COLOR_BLACK);
								cct_showstr(x_now, y_now + 2, "╚═╝", color, COLOR_BLACK);
							}
							cct_showstr(x_now, y_now, "╔═╗", color, COLOR_BLACK);
							cct_showstr(x_now, y_now + 1, "║★║", color, COLOR_BLACK);
							cct_showstr(x_now, y_now + 2, "╚═╝", color, COLOR_BLACK);
							Sleep(1);
							if (x_now != x_fin) {
								cct_showstr(x_now, y_now, "╔═╗", COLOR_HWHITE, COLOR_HWHITE);
								cct_showstr(x_now, y_now + 1, "║★║", COLOR_HWHITE, COLOR_HWHITE);
								cct_showstr(x_now, y_now + 2, "╚═╝", COLOR_HWHITE, COLOR_HWHITE);
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

/*星星反显恢复等等的改颜色*/
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
