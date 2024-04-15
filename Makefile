all: tic_tac_toe

tic_tac_toe: src/main.c
	clang -o tic_tac_toe src/main.c src/logic.c src/ui.c -Iinclude

debug: src/main.c
	clang -g -O0 -o tic_tac_toe src/main.c src/logic.c src/ui.c -Iinclude
