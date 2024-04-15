typedef enum square {
	BLANK = 0,
	X = 1,
	O = -1,
} Square;

#define DIMENSIONS 2
typedef int Coordinate[DIMENSIONS];

#define MAX_LINELENGTH 50
#define MIN_BOARD_SIZE 3
#define MAX_BOARD_SIZE 100

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
