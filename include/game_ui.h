#ifndef UI_INCLUDED
#define UI_INCLUDED 

#include <game_constants.h>
#include <ncurses.h>

void print_board(WINDOW *window, int size, Square board[size][size]);
void get_play(WINDOW *window, Coordinate play, int size, Square board[size][size], int turn);
void display_splash_screen(int splash_screen);
void display_tutorial(WINDOW *window, int size);
void display_information(WINDOW *window, int turn, int size, int win_threshold);
void handle_error(WINDOW *window, int error);

#endif
