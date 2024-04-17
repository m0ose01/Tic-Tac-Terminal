#include <game_constants.h>
#include <game_logic.h>
#include <game_ui.h>
#include <ncurses.h>

void display_tutorial(WINDOW *window, int size)
{
	char *banner = "========================================================================================";
	char *greeting = "TIC-TAC-TOE: A Terminal Based Game";
	char *instructions = "Use the arrow keys or hjkl to move your piece. Press enter or space to place your piece.";
	mvwprintw(window, 0, 0, "%s\n%s\n%s\n", banner, greeting, instructions);

	Square blank[size][size];
	clear_board(size, blank);
	wprintw(window, "%s", banner);
}

void display_information(WINDOW *window, int turn, int size, int win_threshold)
{
	int start_row = 4;
	mvwprintw(window, start_row, 0, "BOARD SIZE: %i", size);
	mvwprintw(window, start_row + 1, 0, "WIN THRESHOLD: %i", win_threshold);
	mvwprintw(window, start_row + 2, 0, "TURN: %i", turn);
	mvwprintw(window, start_row + 3, 0, "CURRENT PLAYER: %c", turn % 2 == 0 ? 'O':'X');
}

void print_board(WINDOW *window, int size, Square board[size][size])
{
	const char hdivider = '|';
	const char *vdivider = "-----+";
	const int row_height = 2;
	const int column_width = 6;
	for (int column = 0; column < size; column++)
	{
		mvwprintw(window, 0, 0 + 6 * column, "(,%03d)", column + 1);
		mvwprintw(window, 1, 1 + 6 * column, "-----+");
		mvwprintw(window, 1, 0, "+");
	}
	for (int row = 0; row < size; row++)
	{
		for (int column = 0; column < size; column++)
		{
			int current_square_value = board[row][column];
			char current_symbol = ' ';
			if (current_square_value != BLANK)
			{
				current_symbol = (current_square_value == X) ? 'X' : 'O';
			}
			mvwprintw(window, 2 + 2 * row, 0, "|");
			mvwprintw(window, 3 + 2 * row, 0, "+");
			mvwprintw(window, 2 + 2 * row, 1 + 6 * column, "  %c  |", current_symbol);
			mvwprintw(window, 3 + 2 * row, 1 + 6 * column, "-----+");

		}
		mvwprintw(window, 2 + 2 * row, 1 + 6 * size, " (%03d,)", row + 1);
	}
	wrefresh(window);
}

void rep(WINDOW *window, const char *str, int n)
{
	for (int i = 0; i < n; i++)
	{
		wprintw(window, "%s", str);
	}
}

void get_play(WINDOW *window, Coordinate play, int size, Square board[size][size], int turn)
{
	play[0] = 0;
	play[1] = 0;
	bool getting_input = true;
	while (getting_input)
	{
		print_board(window, size, board);
		int placement_y = 2 + play[0] * 2;
		int placement_x = 3 + play[1] * 6;
		char current_symbol  = (turn % 2 == 0) ? 'O': 'X';
		wattron(window, COLOR_PAIR(CURSOR_COLOUR));
		mvwaddch(window, placement_y, placement_x, current_symbol);
		wattroff(window, COLOR_PAIR(CURSOR_COLOUR));
		wrefresh(window);
		int ch = getch();
		switch (ch)
		{
			case KEY_LEFT: case 'h':
				play[1] = play[1] > 0 ? play[1] - 1: play[1];
				break;
			case KEY_RIGHT: case 'l':
				play[1] = play[1] < size - 1 ? play[1] + 1: play[1];
				break;
			case KEY_UP: case 'k':
				play[0] = play[0] > 0 ? play[0] - 1:play[0];
				break;
			case KEY_DOWN: case 'j':
				play[0] = play[0] < (size - 1) ? play[0] + 1: play[0];
				break;
			case ' ': case '\n':
				getting_input = false;
				break;
		}
	}
}

void handle_error(WINDOW *window, int error)
{
	char *messages[] = {
		"                                                ",
		"Coordinates must contain only positive integers.",
		"Coordinate exceeds board dimensions (3x3).      ",
		"A piece has already been placed on that square. ",
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
	int start_row = 4;
	mvwprintw(window, start_row + 4, 0, "MESSAGE: %s", messages[message_id]);
}
