#include <stdio.h>
#include <stdbool.h>

#define BOARD_SIZE 3
typedef int Board[BOARD_SIZE][BOARD_SIZE];

#define DIMENSIONS 2
typedef int Coordinate[DIMENSIONS];

#define BLANK 0
#define X_PLACED 1
#define O_PLACED -1

#define MAX_LINELENGTH 50

int check_win(Board board);
void display_tutorial();
void handle_error(int error);
int get_play(Coordinate play);
int make_play(Board board, Coordinate play, int value);
void print_board(Board board);
void rep(const char *str, int n);
int validate_play(Coordinate play, Board board);

int main(void)
{
	Board board = {BLANK};

	display_tutorial();
	
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
			error = validate_play(play, board);
			handle_error(error);
		} while (error != 0);

		int player = (turn % 2 == 0) ? O_PLACED : X_PLACED;
		printf("Placed at (%d, %d)\n", play[0] + 1, play[1] + 1);
		make_play(board, play, player);
		print_board(board);
		printf("\n");

		int win_status = check_win(board);
		if (win_status != 0)
		{
			char winner = (win_status > 0) ? 'X' : 'O';
			printf("%c won!\n", winner);
			game_running = false;
		}
		turn++;
		if (turn > BOARD_SIZE * BOARD_SIZE)
		{
			game_running = false;
		}
	}
}

void print_board(Board board)
{
	const char hdivider = '|';
	const char *vdivider = "---+";
	for (int row = 0; row < BOARD_SIZE; row++)
	{
		printf("+");
		rep(vdivider, BOARD_SIZE);
		printf("\n");
		printf("%c", hdivider);
		for (int column = 0; column < BOARD_SIZE; column++)
		{
			int current_square_value = board[row][column];
			char current_symbol = ' ';
			if (current_square_value != BLANK)
			{
				current_symbol = (current_square_value == X_PLACED) ? 'X' : 'O';
			}
			printf(" %c ", current_symbol);
			printf("%c", hdivider);
		}
		printf("\n");
	}
	printf("+");
	rep(vdivider, BOARD_SIZE);
	printf("\n");
}

void rep(const char *str, int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("%s", str);
	}
}

int make_play(Board board, Coordinate play, int value)
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

void display_tutorial()
{
	char *banner = "===================================";
	char *greeting = "TIC-TAC-TOE: A Terminal Based Game";
	char *instructions = "Type a coordinate to play";
	printf("%s\n%s\n%s\n", banner, greeting, instructions);
	
	Board blank = {BLANK};
	print_board(blank);

	printf("%s\n", banner);
}

int validate_play(Coordinate play, Board board)
{
	int row = play[0], column = play[1];
	for (int i = 0; i < DIMENSIONS; i++)
	{
		if (play[i] < 0)
		{
			return -1;
		}
		else if (play[i] >= BOARD_SIZE)
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

int check_win(Board board)
{
	int row_sums[BOARD_SIZE] = {0};
	int col_sums[BOARD_SIZE] = {0};
	int diagonal_sums[2] = {0};

	for (int row = 0; row < BOARD_SIZE; row++)
	{
		diagonal_sums[0] += board[row][row];
		diagonal_sums[1] += board[row][(BOARD_SIZE - 1) - row];

		for (int column = 0; column < BOARD_SIZE; column++)
		{
			row_sums[row] += board[row][column];
			col_sums[column] += board[row][column];
		}
	}

	for (int i = 0; i < 2; i++)
	{
		if (diagonal_sums[i] == BOARD_SIZE || (diagonal_sums[i] == -BOARD_SIZE))
		{
			return (diagonal_sums[i] > 0) ? X_PLACED : O_PLACED;
		}
	}

	for (int i = 0; i < BOARD_SIZE; i++)
	{
		if (row_sums[i] == BOARD_SIZE || row_sums[i] == -BOARD_SIZE)
		{
			return (row_sums[i] > 0) ? X_PLACED : O_PLACED;
		}

		if (col_sums[i] == BOARD_SIZE || col_sums[i] == -BOARD_SIZE)
		{
			return (col_sums[i] > 0) ? X_PLACED : O_PLACED;
		}
	}

	return 0;
}
