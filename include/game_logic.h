#ifndef LOGIC_INCLUDED
#define LOGIC_INCLUDED

#include <game_constants.h>
#include <stdbool.h>

bool check_diagonal(int size, Square board[size][size], int win_threshold, Coordinate start, int diagonal_length, bool antidiagonal);
bool check_win(int size, Square board[size][size], int win_threshold);
void clear_board(int size, Square board[size][size]);
void handle_error(int error);
int get_play(Coordinate play);
int linear_search(int size, int array[size], int key);
int make_play(int size, Square board[size][size], Coordinate play, int value);
int validate_play(Coordinate play, int size, Square board[size][size]);

#endif