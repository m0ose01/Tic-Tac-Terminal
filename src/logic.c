#include <game_constants.h>
#include <game_logic.h>
#include <stdbool.h>

int make_play(int size, Square board[size][size], Coordinate play, int value)
{
	int row, column;
	row = play[0];
	column = play[1];
	board[row][column] = value;

	return 0;
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
				sums[col_index + col] = 0;
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

	for (int row = 0; row < diagonal_length; row++)
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
