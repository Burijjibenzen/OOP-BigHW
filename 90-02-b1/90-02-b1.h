// 2251206 ·ëÓğĞ¾ ¼Æ¿Æ
#pragma once

void generate_array(char(*p)[23], int& h, int& w);
void current_array(char(*p)[23], int& h, int& w);

int get_next_num(const bool new_seed, const unsigned int seed);
void generate_num(char(*p)[23], int& h, int& w, int& cntr_x, int& cntr_y, int& current_num, int mode);
void rotate1(char(*p)[23], int& h, int& w, int& cntr_x, int& cntr_y, int next_num, int& sum, int mode);

void cmd_rotate_clear(char(*p)[23], int& cntr_x, int& cntr_y, int current_num, int mode);
void cmd_rotate_draw(char(*p)[23], int& cntr_x, int& cntr_y, int current_num, int mode);
void end(void);

void frame(int& h, int& w);
void tips(int& next_num, int score, int line, int& w);

void clear(int x_star, int y_star);

int clearup(char(*p)[23], char(*q)[23], int& h, int& w);
int fall(char(*p)[23], char(*q)[23], int current_num, int cntr_x, int cntr_y, int& h, int& w, int& judge, int& line, int mode);
void left(char(*p)[23], int current_num, int& cntr_x, int cntr_y);
void right(char(*p)[23], int current_num, int& cntr_x, int cntr_y, int w);
void rotate(char(*p)[23], int& h, int& w, int& cntr_x, int& cntr_y, int current_num, int& sum, int mode);
int opr(char(*p)[23], char(*q)[23], int current_num, int& h, int& w, int cntr_x, int cntr_y, int& score, int& line, int mode);
int death(char(*p)[23], int w);
