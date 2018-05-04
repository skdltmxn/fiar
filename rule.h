#pragma once
#include <iostream>
#include <stdlib.h> //needed for rand
#include <windows.h>

#define HEIGHT 6
#define WIDTH 7

int score[2][7] = { 0 };
int LastMoveX, LastMoveY;
int current[7] = { 5,5,5,5,5,5,5 };
int checknum[7] = { 0 };
using namespace std;
void draw_board();
void player_movement(int player);
bool check_for_winner(int x, int y, int player);
bool check_diagonal_combo_SW_NE(int x, int y, int player);
bool check_diagonal_combo_NW_SE(int x, int y, int player);
bool check_vertical_combo(int x, int y, int player);
bool check_horizontal_combo(int x, int y, int player);

int board_info[HEIGHT][WIDTH] = { { 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 } };

void evalutescore(int player);
