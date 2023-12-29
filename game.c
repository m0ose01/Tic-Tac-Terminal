#include <linux/limits.h>
#include <stdio.h>
#include <stdbool.h>


#define BOARD_SIZE 3
typedef int Board[BOARD_SIZE][BOARD_SIZE];

#define DIMENSIONS 2
typedef int Coordinate[DIMENSIONS];

#define BLANK 0
#define X_PLACED 1
#define O_PLACED 2

#define MAX_LINELENGTH 50

void display_tutorial();
int get_play(Coordinate play);
int make_play(Board board, Coordinate play, int value);
void print_board(Board board);

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
		printf("Turn %i: ", turn);
		while (get_play(play) != 0)
		{
			printf("Invalid coordinate. Enter two integers between 1 and 3 inclusive.\n");
			printf("Turn %i: ", turn);
		}
		int player = BLANK;
		if (turn % 2 == 0)
		{
			player = O_PLACED;
		}
		else
		{
			player = X_PLACED;
		}
		printf("Placed at (%d, %d)\n", play[0] + 1, play[1] + 1);
		make_play(board, play, player);
		print_board(board);
		turn++;
	}
}

void print_board(Board board)
{
	const char symbols[] = {' ', 'X', 'O'};
	const char hdivider = '|';
	for (int row = 0; row < BOARD_SIZE; row++)
	{
		printf("%c", hdivider);
		for (int column = 0; column < BOARD_SIZE; column++)
		{
			int current_square_value = board[row][column];
			char current_symbol = symbols[current_square_value];
			printf("%c", current_symbol);
			printf("%c", hdivider);
		}
		printf("\n");
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
		if (play[i] < 1)
		{
			return -1;
		}
		else if (play[i] > BOARD_SIZE)
		{
			return -2;
		}
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