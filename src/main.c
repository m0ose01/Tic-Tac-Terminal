#include <game_constants.h>
#include <game_logic.h>
#include <game_types.h>
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
	Square board [size][size];
	clear_board(size, board);

	// Initialise UI
	initscr();
	cbreak();
	noecho();
	curs_set(0);
	keypad(stdscr, TRUE);

	const int messages_wheight = 9;
	const int messages_wwidth = 89;
	const int messages_starty = 0;
	const int messages_startx = (COLS) / 2 - messages_wwidth / 2;
	WINDOW *messages_window = newwin(messages_wheight, messages_wwidth, messages_starty, messages_startx);

	const int board_wheight = 2 + 2 * size;
	const int board_wwidth = 1 + 6 * size + 7;
	const int board_starty = messages_starty + messages_wheight + 1;
	const int board_startx = (COLS) / 2 - board_wwidth / 2;
	WINDOW *board_window = newwin(board_wheight, board_wwidth, board_starty, board_startx);

	// Check screen is of sufficient size to hold UI.
	if (messages_wwidth > COLS)
	{
		delwin(board_window);
		delwin(messages_window);
		endwin();
		printf("Terminal window too small to display UI.\n");
		return -3;
	}
	if (board_wwidth > COLS || (board_wheight + board_starty) > LINES)
	{
		delwin(board_window);
		delwin(messages_window);
		endwin();
		printf("Terminal window too small to display a board of this size. Please try with a smaller size.\n");
		return -3;
	}

	// Turn colours on
	start_color();
	if (!has_colors())
	{
		delwin(board_window);
		delwin(messages_window);
		endwin();
		printf("Error: Colour not supported.");
		return -4;
	}
	init_pair(CURSOR_COLOUR, COLOR_BLACK, COLOR_WHITE);

	display_splash_screen(SPLASH_GAME_START);

	display_tutorial(messages_window, size);
	refresh();
	
	bool game_running = true;
	int turn = 1;

	// MAIN GAME LOOP
	while (game_running)
	{
		Coordinate play = {-1, -1};
		int error = 0;
		// Handle player input
		do
		{
			display_information(messages_window, turn, size, win_threshold);
			wrefresh(messages_window);
			get_play(board_window, play, size, board, turn);
			error = validate_play(play, size, board);
			handle_error(messages_window, error);
		} while (error != 0);

		int player = (turn % 2 != 0) ? X : O;
		make_play(size, board, play, player);
		print_board(board_window, size, board);

		int win_status = check_win(size, board, win_threshold);
		if (win_status == true)
		{
			char winner = (turn % 2 != 0) ? 'X' : 'O';
			werase(messages_window);
			wrefresh(messages_window);
			werase(stdscr);
			wrefresh(stdscr);
			int winner_splash_screen = (turn % 2 != 0) ? SPLASH_X_WON : SPLASH_O_WON;
			display_splash_screen(winner_splash_screen);
			game_running = false;
		}

		turn++;
		if (turn > size * size && game_running == true)
		{
			werase(messages_window);
			wrefresh(messages_window);
			werase(stdscr);
			wrefresh(stdscr);
			display_splash_screen(SPLASH_GAME_DRAWN);
			getch();
			game_running = false;
		}
	}
	delwin(board_window);
	delwin(messages_window);
	endwin();
	return 0;
}
