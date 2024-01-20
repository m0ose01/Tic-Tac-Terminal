all: game

game: game.c
	clang -o tic_tac_toe game.c

debug: game.c
	clang -g -O0 -o tic_tac_toe game.c
