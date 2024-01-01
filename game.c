#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef enum square {
	BLANK = 0,
	X = 1,
	O = -1,
} Square;

#define DIMENSIONS 2
typedef int Coordinate[DIMENSIONS];

#define MAX_LINELENGTH 50

int check_win(int size, Square board[size][size]);
void clear_board(int size, Square board[size][size]);
void display_tutorial(int size);
void handle_error(int error);
int get_play(Coordinate play);
int make_play(int size, Square board[size][size], Coordinate play, int value);
void print_board(int size, Square board[size][size]);
void rep(const char *str, int n);
int validate_play(Coordinate play, int size, Square board[size][size]);

int main(int argc, char *argv[])
{
	int size = 3;

	// Handle input
	if (argc == 2)
	{
		int new_size = atoi(argv[1]);
		if (new_size < 3)
		{
			printf("Invalid board size. Please choose an integer greater than or equal to 3.\n");
			return -1;
		}
		else
		{
			size = new_size;
		}
	}
	Square board [size][size];
	clear_board(size, board);

	display_tutorial(size);
	
	bool game_running = true;
	int turn = 1;

	// MAIN GAME LOOP
	while (game_running)
	{
		Coordinate play = {-1, -1};
		int error = 0;
		do
		{
			printf("Turn %i: ", turn);
			get_play(play);
			error = validate_play(play, size, board);
			handle_error(error);
		} while (error != 0);

		int player = (turn % 2 == 0) ? O : X;
		printf("Placed at (%d, %d)\n", play[0] + 1, play[1] + 1);
		make_play(size, board, play, player);
		print_board(size, board);
		printf("\n");

		int win_status = check_win(size, board);
		if (win_status != 0)
		{
			char winner = (win_status > 0) ? 'X' : 'O';
			printf("%c won!\n", winner);
			game_running = false;
		}
		turn++;
		if (turn > size * size)
		{
			game_running = false;
		}
	}
}

void print_board(int size, Square board[size][size])
{
	const char hdivider = '|';
	const char *vdivider = "---+";
	for (int column = 0; column < size; column++)
	{
		printf("(,%i)", column + 1);
	}
	printf("\n");

	for (int row = 0; row < size; row++)
	{
		printf("+");
		rep(vdivider, size);
		printf("\n");
		printf("%c", hdivider);
		for (int column = 0; column < size; column++)
		{
			int current_square_value = board[row][column];
			char current_symbol = ' ';
			if (current_square_value != BLANK)
			{
				current_symbol = (current_square_value == X) ? 'X' : 'O';
			}
			printf(" %c ", current_symbol);
			printf("%c", hdivider);
		}
		printf(" (%i,)", row + 1);
		printf("\n");
	}
	printf("+");
	rep(vdivider, size);
	printf("\n");
}

void rep(const char *str, int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("%s", str);
	}
}

int make_play(int size, Square board[size][size], Coordinate play, int value)
{
	int row, column;
	row = play[0];
	column = play[1];
	board[row][column] = value;

	return 0;
}

int get_play(Coordinate play)
{
	char input[MAX_LINELENGTH];

	fgets(input, MAX_LINELENGTH, stdin);
	sscanf(input, " %d %d ", &play[0], &play[1]);
	for (int i = 0; i < DIMENSIONS; i++)
	{
		play[i] += -1;
	}
	return 0;
}

void display_tutorial(int size)
{
	char *banner = "===================================";
	char *greeting = "TIC-TAC-TOE: A Terminal Based Game";
	char *instructions = "Type a coordinate to play";
	printf("%s\n%s\n%s\n", banner, greeting, instructions);
	
	Square blank[size][size];
	clear_board(size, blank);
	print_board(size, blank);

	printf("%s\n", banner);
}

int validate_play(Coordinate play, int size, Square board[size][size])
{
	int row = play[0], column = play[1];
	for (int i = 0; i < DIMENSIONS; i++)
	{
		if (play[i] < 0)
		{
			return -1;
		}
		else if (play[i] >= size)
		{
			return -2;
		}
	}

	if (board[row][column] != BLANK)
	{
		return -3;
	}
	return 0;
}

void handle_error(int error)
{
	char *messages[] = {
		"",
		"Coordinates must contain only positive integers.\n",
		"Coordinate exceeds board dimensions (3x3).\n",
		"A piece has already been placed on that square.\n",
	};
	int message_id = 0;
	switch (error)
	{
		case 0:
			message_id = 0;
			break;
		case -1:
			message_id = 1;
			break;
		case -2:
			message_id = 2;
			break;
		case -3:
			message_id = 3;
			break;
	}
	printf("%s", messages[message_id]);
}

int check_win(int size, Square board[size][size])
{
	int row_sums[size];
	int col_sums[size];

	for (int i = 0; i < size; i++)
	{
		row_sums[i] = 0;
		col_sums[i] = 0;
	}
	int diagonal_sums[2] = {0, 0};

	for (int row = 0; row < size; row++)
	{
		diagonal_sums[0] += board[row][row];
		diagonal_sums[1] += board[row][(size - 1) - row];

		for (int column = 0; column < size; column++)
		{
			row_sums[row] += board[row][column];
			col_sums[column] += board[row][column];
		}
	}

	for (int i = 0; i < 2; i++)
	{
		if (diagonal_sums[i] == size || (diagonal_sums[i] == -size))
		{
			return (diagonal_sums[i] > 0) ? X : O;
		}
	}

	for (int i = 0; i < size; i++)
	{
		if (row_sums[i] == size || row_sums[i] == -size)
		{
			return (row_sums[i] > 0) ? X : O;
		}

		if (col_sums[i] == size || col_sums[i] == -size)
		{
			return (col_sums[i] > 0) ? X : O;
		}
	}

	return 0;
}

void clear_board(int size, Square board[size][size])
{
	for (int row = 0; row < size; row++)
	{
		for (int column = 0; column < size; column++)
		{
			board[row][column] = BLANK;
		}
	}
}
