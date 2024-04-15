#include <game_constants.h>
#include <game_logic.h>
#include <game_ui.h>

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>



int main(int argc, char *argv[])
{
	int size = 3;
	int win_threshold = size;

	// Handle input
	if (argc >= 2)
	{
		int new_size = atoi(argv[1]);
		if (new_size < MIN_BOARD_SIZE)
		{
			printf("Invalid board size. Please choose an integer greater than or equal to 3.\n");
			return -1;
		}
		if (new_size > MAX_BOARD_SIZE)
		{
			printf("Invalid board size. This exceeds the max board size of %i.\n", MAX_BOARD_SIZE);
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
