all: game

game: game.c
	clang -o tic_tac_toe game.c
