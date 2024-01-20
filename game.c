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

bool check_diagonal(int size, Square board[size][size], int win_threshold, Coordinate start, int diagonal_length, bool antidiagonal);
bool check_win(int size, Square board[size][size], int win_threshold);
void clear_board(int size, Square board[size][size]);
void display_tutorial(int size);
void handle_error(int error);
int get_play(Coordinate play);
int linear_search(int size, int array[size], int key);
int make_play(int size, Square board[size][size], Coordinate play, int value);
void print_board(int size, Square board[size][size]);
void rep(const char *str, int n);
int validate_play(Coordinate play, int size, Square board[size][size]);

int main(int argc, char *argv[])
{
	int size = 3;
	int win_threshold = size;

	// Handle input
	if (argc >= 2)
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
	if (argc >= 3)
	{
		int new_win_threshold = atoi(argv[2]);
		if (new_win_threshold > size)
		{
			printf("Invalid win threshold. Please choose an integer less than or equal to the board size.\n");
			return -2;
		}
		if (new_win_threshold < 3)
		{
			printf("Invalid win threshold. Please choose an integer greater than or equal to 3.\n");
			return -2;
		}
		win_threshold = new_win_threshold;
	}
	printf("Starting game with board size (%ix%i), with win threshold %i.\n", size, size, win_threshold);
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

		int player = (turn % 2 != 0) ? X : O;
		printf("Placed at (%d, %d).\n", play[0] + 1, play[1] + 1);
		make_play(size, board, play, player);
		print_board(size, board);
		printf("\n");

		int win_status = check_win(size, board, win_threshold);
		if (win_status == true)
		{
			char winner = (turn % 2 != 0) ? 'X' : 'O';
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
	char *instructions = "Type a coordinate to play.";
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

bool check_win(int size, Square board[size][size], int win_threshold)
{
	bool win_found = false;

	const int DIAGONAL_COUNT = 1 + ((size - win_threshold) * 2);
	const int ROW_COUNT = size;
	const int COLUMN_COUNT = size;
	const int SUMS_COUNT = ROW_COUNT + COLUMN_COUNT + DIAGONAL_COUNT;
	int sums[SUMS_COUNT];
	int row_index = 0, col_index = ROW_COUNT, diag_index = ROW_COUNT + COLUMN_COUNT;
	for (int this_sum = 0; this_sum < SUMS_COUNT; this_sum++)
	{
		sums[this_sum] = 0;
	}

	for (int i = 0; i < 2; i++)
	{
		bool is_antidiagonal = (i == 1) ? true : false;
		Coordinate offset = {0, 0};
		if (check_diagonal(size, board, win_threshold, offset, size, is_antidiagonal))
		{
			return true;
		}

		for (int j = 0; j < (DIAGONAL_COUNT - 1) / 2; j++)
		{
			Coordinate offset_A = {0, j + 1};
			Coordinate offset_B = {j + 1, 0};

			if (check_diagonal(size, board, win_threshold, offset_A, size - (j + 1), is_antidiagonal))
			{
				return true;
			}

			if (check_diagonal(size, board, win_threshold, offset_B, size - (j + 1), is_antidiagonal))
			{
				return true;
			}
	   		
		}
	}

	for (int row = 0; row < size; row++)
	{
		if (win_found == true)
		{
			return true;
		}
		
		int prev_row = row - 1;

		for (int col = 0; col < size; col++)
		{
			int prev_col = col - 1;

			if (prev_col >= 0 && board[row][col] == board[row][prev_col] && board[row][col] != BLANK)
			{
				sums[row_index + row] += board[row][col];
			}
			else
			{
				sums[row_index + row] = 0;
			}

			if (prev_row >= 0 && board[row][col] == board[prev_row][col] && board[row][col] != BLANK)
			{
				sums[col_index + col] += board[row][col];
			}
			else
			{
				sums[col_index] = 0;
			}

			win_found = (linear_search(SUMS_COUNT, sums, win_threshold - 1) >= 0 || linear_search(SUMS_COUNT, sums, -(win_threshold - 1)) >= 0);
			if (win_found == true)
			{
				return true;
			}
		}
	}

	if (win_found)
	{
		return true;
	}
	return false;
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

int linear_search(int size, int array[size], int key)
{
	for (int i = 0; i < size; i++)
	{
		if (array[i] == key)
		{
			return i;
		}
	}
	return -1;
}

bool check_diagonal(int size, Square board[size][size], int win_threshold, Coordinate offset, int diagonal_length, bool antidiagonal)
{
	const int DIAGONAL_COUNT = 1 + ((size - win_threshold) * 2);
	int sum = 0;

	for (int row = 0; row < size; row++)
	{
		int prev_row = row - 1;

		Square current_square;
		Square prev_square;
		if (antidiagonal == false)
		{
			current_square = board[offset[0] + row][offset[1] + row];
			prev_square = board[offset[0] + prev_row][offset[1] + prev_row];
		}
		else
		{
			current_square = board[offset[0] + row][(size - 1) - row - offset[1]];
			prev_square = board[offset[0] + prev_row][(size - 1) - prev_row - offset[1]];
		}

		if (prev_row >= 0 && current_square == prev_square && current_square != BLANK)
		{
			sum += current_square;
		}
		else
		{
			sum = 0;
		}

		if (sum == (win_threshold - 1) * X || sum == (win_threshold - 1) * O)
		{
			return true;
		}
	}
	return false;
}
