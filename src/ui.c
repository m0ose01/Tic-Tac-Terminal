#include <game_constants.h>
#include <game_logic.h>
#include <game_ui.h>
#include <stdio.h>

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

void print_board(int size, Square board[size][size])
{
	const char hdivider = '|';
	const char *vdivider = "-----+";
	for (int column = 0; column < size; column++)
	{
		printf("(,%03i)", column + 1);
	}
	printf("\n");

	for (int row = 0; row < size; row++)
	{
		printf("+");
		rep(vdivider, size);
		printf("\n%c", hdivider);
		for (int column = 0; column < size; column++)
		{
			int current_square_value = board[row][column];
			char current_symbol = ' ';
			if (current_square_value != BLANK)
			{
				current_symbol = (current_square_value == X) ? 'X' : 'O';
			}
			printf("  %c  ", current_symbol);
			printf("%c", hdivider);
		}
		printf(" (%03i,)", row + 1);
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
