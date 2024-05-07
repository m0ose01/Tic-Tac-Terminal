#include <game_constants.h>
#include <game_logic.h>
#include <game_types.h>
#include <game_ui.h>
#include <ncurses.h>
#include <string.h>

void display_splash_screen(int splash_screen)
{
	char *x_won_string = 
		"__   __  _    _             _ \n"
		"\\ \\ / / | |  | |           | |\n"
		" \\ V /  | |  | | ___  _ __ | |\n"
		" /   \\  | |/\\| |/ _ \\| '_ \\| |\n"
		"/ /^\\ \\ \\  /\\  / (_) | | | |_|\n"
		"\\/   \\/  \\/  \\/ \\___/|_| |_(_)\n";

	char *o_won_string = 
		" _____   _    _             _ \n"
		"|  _  | | |  | |           | |\n"
		"| | | | | |  | | ___  _ __ | |\n"
		"| | | | | |/\\| |/ _ \\| '_ \\| |\n"
		"\\ \\_/ / \\  /\\  / (_) | | | |_|\n"
		" \\___/   \\/  \\/ \\___/|_| |_(_)\n";

	char *game_drawn_string = 
"______                    _ \n"
"|  _  \\                  | |\n"
"| | | |_ __ __ ___      _| |\n"
"| | | | '__/ _` \\ \\ /\\ / / |\n"
"| |/ /| | | (_| |\\ V  V /|_|\n"
"|___/ |_|  \\__,_| \\_/\\_/ (_)\n";

	char *start_string =
		" _____ _           _____               _____                   _             _ \n"
		"|_   _(_)         |_   _|             |_   _|                 (_)           | |\n"
		"  | |  _  ___ ______| | __ _  ___ ______| | ___ _ __ _ __ ___  _ _ __   __ _| |\n"
		"  | | | |/ __|______| |/ _` |/ __|______| |/ _ \\ '__| '_ ` _ \\| | '_ \\ / _` | |\n"
		"  | | | | (__       | | (_| | (__       | |  __/ |  | | | | | | | | | | (_| | |\n"
		"  \\_/ |_|\\___|      \\_/\\__,_|\\___|      \\_/\\___|_|  |_| |_| |_|_|_| |_|\\__,_|_|\n";

	const int splash_screen_wheight = 8;
	int splash_screen_wwidth = 89;
	char *splash_string;

	switch (splash_screen) {
		case SPLASH_X_WON:
			splash_screen_wwidth = 32;
			splash_string = x_won_string;
			break;
		case SPLASH_O_WON:
			splash_screen_wwidth = 32;
			splash_string = o_won_string;
			break;
		case SPLASH_GAME_DRAWN:
			splash_screen_wwidth = 30;
			splash_string = game_drawn_string;
			break;	
		default:
			splash_screen_wwidth = 89;
			splash_string = start_string;
			break;
	}

	const int splash_screen_starty = (LINES / 2) - (splash_screen_wheight / 2);
	const int splash_screen_startx = (COLS / 2) - (splash_screen_wwidth / 2);
	WINDOW *splash_window = newwin(splash_screen_wheight, splash_screen_wwidth, splash_screen_starty, splash_screen_startx);


	const int splash_colour = 3;
	init_pair(splash_colour, COLOR_RED, COLOR_BLACK);
	wattron(splash_window, COLOR_PAIR(splash_colour));
	wattron(splash_window, A_BOLD);
	wprintw(splash_window, "%s", splash_string);
	wattroff(splash_window, COLOR_PAIR(splash_colour));
	wattroff(splash_window, A_BOLD);
	char *instruction = "Press any key to continue.";
	mvwprintw(splash_window, 7, getmaxx(splash_window) / 2 - strlen(instruction) / 2, "%s", instruction);
	wrefresh(splash_window);
	wgetch(splash_window);
	wclear(splash_window);
	refresh();
	delwin(splash_window);
}

void display_tutorial(WINDOW *window, int size)
{
	char *banner = "========================================================================================";
	char *greeting = "TIC-TAC-TOE: A Terminal Based Game";
	char *instructions = "Use the arrow keys or hjkl to move your piece. Press enter or space to place your piece.";
	char *exit_instructions = "Press Ctrl-C to exit.";
	mvwprintw(window, 0, 0, "%s\n%s\n%s\n%s\n%s\n", banner, greeting, instructions, exit_instructions, banner);

	Square blank[size][size];
	clear_board(size, blank);
}

void display_information(WINDOW *window, int turn, int size, int win_threshold)
{
	int start_row = 0;
	mvwprintw(window, start_row, 0, "BOARD SIZE: %03d      WIN_THRESHOLD: %03d", size, win_threshold);
	mvwprintw(window, start_row + 1, 0, "TURN:       %03d      CURRENT PLAYER: %c", turn, turn % 2 == 0 ? 'O':'X');
}

void print_board(WINDOW *window, int size, Square board[size][size])
{
	const char hdivider = '|';
	const char *vdivider = "+-----+";
	for (int column = 0; column < size; column++)
	{
		mvwprintw(window, 0, 0 + COLUMN_WIDTH * column, "(,%03d)", column + 1);
		mvwprintw(window, 1, 0 + COLUMN_WIDTH * column, "%s", vdivider);
	}
	for (int row = 0; row < size; row++)
	{
		for (int column = 0; column < size; column++)
		{
			// Determine which symbol should be displayed in each square
			int current_square_value = board[row][column];
			char current_symbol = ' ';
			if (current_square_value != BLANK)
			{
				current_symbol = (current_square_value == X) ? 'X' : 'O';
			}
			mvwprintw(window, 2 + ROW_HEIGHT * row, 0 + COLUMN_WIDTH * column, "%c  %c  %c", hdivider, current_symbol, hdivider);
			mvwprintw(window, 3 + ROW_HEIGHT * row, 0 + COLUMN_WIDTH * column, "%s", vdivider);

		}
		mvwprintw(window, 2 + ROW_HEIGHT * row, 1 + COLUMN_WIDTH * size, " (%03d,)", row + 1);
	}
	wrefresh(window);
}

void get_play(WINDOW *window, Coordinate play, int size, Square board[size][size], int turn)
{
	play[0] = 0;
	play[1] = 0;
	bool getting_input = true;
	while (getting_input)
	{
		print_board(window, size, board);
		int placement_y = 2 + play[0] * ROW_HEIGHT;
		int placement_x = 3 + play[1] * COLUMN_WIDTH;
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
	int start_row = 0;
	mvwprintw(window, start_row + 2, 0, "MESSAGE: %s", messages[message_id]);
}
