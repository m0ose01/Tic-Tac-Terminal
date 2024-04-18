# Tic-Tac-Terminal

## Usage

This is a terminal-based version of the classic tic-tac-toe game.
If no arguments are specified, a standard 3x3 tic-tac-toe game will be chosen as the default.
```bash
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

```bash
./tic_tac_toe 5 3
```

produces the following board:

```bash
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

```bash
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
