#include <game_constants.h>
#include <game_logic.h>
#include <game_ui.h>

#include <ncurses.h>
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

	initscr();
	cbreak();
	noecho();
	curs_set(0);
	keypad(stdscr, TRUE);
	refresh();

	int board_wheight = 2 + 2 * size;
	int board_wwidth = 1 + 6 * size + 7;
	int board_starty = (LINES) / 2 - board_wheight / 2;
	int board_startx = (COLS) / 2 - board_wwidth / 2;
	WINDOW *board_window = newwin(board_wheight, board_wwidth, board_starty, board_startx);

	int messages_wheight = 10;
	int messages_wwidth = COLS;
	int messages_starty = 0;
	int messages_startx = (COLS) / 2 - messages_wwidth / 2;

	WINDOW *messages_window = newwin(messages_wheight, messages_wwidth, messages_starty, messages_startx);
	box(messages_window, 0, 0);
	wrefresh(board_window);
	wrefresh(messages_window);
	refresh();

	display_tutorial(messages_window, size);
	wrefresh(messages_window);
	
	bool game_running = true;
	int turn = 1;

	// MAIN GAME LOOP
	while (game_running)
	{
		refresh();
		Coordinate play = {-1, -1};
		int error = 0;
		do
		{
			printw("Turn %i: ", turn);
			get_play(board_window, play, size, board, turn);
			error = validate_play(play, size, board);
			handle_error(error);
			wrefresh(board_window);
			refresh();
		} while (error != 0);

		int player = (turn % 2 != 0) ? X : O;
		// printw("Placed at (%d, %d).\n", play[0] + 1, play[1] + 1);
		make_play(size, board, play, player);
		print_board(board_window, size, board);
		printw("\n");

		int win_status = check_win(size, board, win_threshold);
		if (win_status == true)
		{
			char winner = (turn % 2 != 0) ? 'X' : 'O';
			printw("%c won!\n", winner);
			game_running = false;
		}

		turn++;
		if (turn > size * size)
		{
			game_running = false;
		}
	}
	delwin(board_window);
	delwin(messages_window);
	endwin();
	return 0;
}
