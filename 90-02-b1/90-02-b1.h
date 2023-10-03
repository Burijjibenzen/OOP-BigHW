// 2251206 ·ëÓğĞ¾ ¼Æ¿Æ
#pragma once

void input(int* h, int* w);
void generate_array(char(*p)[22], int& h, int& w);
void current_array(char(*p)[22], int& h, int& w);

int get_next_num(const bool new_seed, const unsigned int seed);
void generate_num(char(*p)[22], int& h, int& w, int& cntr_x, int& cntr_y, int& current_num, int mode);
void rotate(char(*p)[22], int& h, int& w, int& cntr_x, int& cntr_y, int next_num);
void end(void);

void frame(int& h, int& w);
void tips(int& next_num, int score, int line, int& w);