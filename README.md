# Tic-Tac-Terminal

## Usage

This is a terminal-based version of the classic tic-tac-toe game.
If no arguments are specified, a standard 3x3 tic-tac-toe game will be chosen as the default.
```
(,001)(,002)(,003)
+-----+-----+-----+
|     |     |     | (001,)
+-----+-----+-----+
|     |     |     | (002,)
+-----+-----+-----+
|     |     |     | (003,)
+-----+-----+-----+
```

Command line options allow the specification of board size, and win threshold.
For example:

```
./tic_tac_toe 5 3
```

produces the following board:

```
(,001)(,002)(,003)(,004)(,005)
+-----+-----+-----+-----+-----+
|     |     |     |     |     | (001,)
+-----+-----+-----+-----+-----+
|     |     |     |     |     | (002,)
+-----+-----+-----+-----+-----+
|     |     |     |     |     | (003,)
+-----+-----+-----+-----+-----+
|     |     |     |     |     | (004,)
+-----+-----+-----+-----+-----+
|     |     |     |     |     | (005,)
+-----+-----+-----+-----+-----+
```
There is a 5x5 board, and either player must place 3 pieces in a line (vertical, horizontal or diagonal) to win.
The arrow keys or hjkl (similar to Vim motions) can be used to move the piece. Press space or enter to place your piece.

```
(,001)(,002)(,003)(,004)(,005)
+-----+-----+-----+-----+-----+
|     |     |     |     |     | (001,)
+-----+-----+-----+-----+-----+
|     |     |  X  |     |     | (002,)
+-----+-----+-----+-----+-----+
|     |     |     |     |     | (003,)
+-----+-----+-----+-----+-----+
|     |     |     |     |     | (004,)
+-----+-----+-----+-----+-----+
|     |     |     |     |     | (005,)
+-----+-----+-----+-----+-----+
```

This continues until either a player wins, or there is no free square on the board.

## Installation

### Prerequisites

* GNU Make
* A C compiler
* A terminal with colour support
* Ncurses installation

Currently, this application has only been tested on Linux Mint 21.3.
Feedback on compatibility with other systems is welcome.

1. Clone the repo using git.
2. In the project directory, simply type `make` to compile the program.
3. Optionally place the binary `./tic_tac_toe` in a directory accessible from the system path.

## Design

This project consists of 4 header files, and 3 source files.
By far the most complicated part of this project was ensuring that wins were detected along diagonals, on an arbitrarily large board, with a variable "win threshold".

### Header Files

* include/game_constants.h
    * Various constants necessary for the UI, and game logic.
* include/game_logic.h
    * Function prototypes for logic.c source file.
* include/game_types.h
    * The types defined for this project.
* include/game_ui.h
    * Function prototypes for the ui.c source file.

### Source Files

* src/main.c
    * The entry point, which contains the main function and the main game loop, and logic to manage launching and closing the application.
* src/ui.c
    * Functions which draw various aspects of the UI using ncurses.
* src/logic.c
    * Functions for the UI-independent game logic, such as detecting when the game is won or drawn, or determining whether a square is already occupied.

### Potential Future Goals

* Implement [Ultimate Tic-Tac-Toe](https://en.wikipedia.org/wiki/Ultimate_tic-tac-toe)
* Implement an AI so that one person can play against the computer.
