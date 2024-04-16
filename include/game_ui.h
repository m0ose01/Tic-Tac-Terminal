#ifndef UI_INCLUDED
#define UI_INCLUDED 

#include <game_constants.h>
#include <ncurses.h>

void print_board(WINDOW *window, int size, Square board[size][size]);
void rep(WINDOW *window, const char *str, int n);
void get_play(WINDOW *window, Coordinate play, int size, Square board[size][size], int turn);
void display_tutorial(WINDOW *window, int size);
void handle_error(int error);

#endif
