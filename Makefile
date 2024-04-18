all: tic_tac_toe

tic_tac_toe: src/main.c src/ui.c src/logic.c
	cc -o tic_tac_toe src/main.c src/logic.c src/ui.c -Iinclude -lncurses

debug: src/main.c src/ui.c src/logic.c
	cc -g -O0 -o tic_tac_toe src/main.c src/logic.c src/ui.c -Iinclude -lncurses
