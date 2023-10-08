//2251206 ·ëÓðÐ¾ ¼Æ¿Æ
#pragma once

void menu_A(void);
void menu_B(void);
void menu_C(void);
void menu_D(void);
void menu_E(void);
void menu_F(void);
void menu_G(void);

void generate_array(int p[][12], int& r, int& c);
void current_array(int p[][12], int& r, int& c);
void coordinate_input(char* coordinate, int p[][12], int& r, int& c);
void same_array(int x, int y, char result[][12], int p[][12]);
void result_array(char result[][12], int& r, int& c);
void color_array(char result[][12], int p[][12], int& r, int& c);

void end(void);
char confirm(char* coordinate);
void color_vanish_array(char result[][12], int p[][12], int& r, int& c);
void vanish_array(char result[][12], int p[][12], int& r, int& c);
void wait_for_enter(const char* prompt);
void fall_array(int p[][12], int& r, int& c);
void print_fall_array(char result[][12], int p[][12], int& r, int& c);
void SCORE(char result[][12], int& r, int& c, int* total);
int over(int p[][12], int& r, int& c);

void screen_set(int cmd_col, int cmd_row);
void frame(int r, int c, bool split);
void color_block(int p[][12], int r, int c, bool split);
int MouseKey(int p[][12], int r, int c, bool split, char menu, int* total_score);
int selected(char result[][12], int p[][12], int x, int y, int r, int c, bool split, int* x_key, int* y_key, char* coordinate, int* total_score);
void move(int p[][12], int r, int c, char menu, bool split);
void change_color(int p[][12], int x_p, int y_p, int fg_color);
void bonus(int left, int* total);