# Tic-Tac-Terminal

This is a terminal-based version of the classic tic-tac-toe game.
If no arguments are specified, a standard 3x3 tic-tac-toe game will be chosen as the default.
```bash
===================================
TIC-TAC-TOE: A Terminal Based Game
Type a coordinate to play.
(,001)(,002)(,003)
+-----+-----+-----+
|     |     |     | (001,)
+-----+-----+-----+
|     |     |     | (002,)
+-----+-----+-----+
|     |     |     | (003,)
+-----+-----+-----+
===================================
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
Input is received by typing two numbers into the console, separated by spaces, e.g.,

```bash
Turn 1: 2 3
Placed at (2, 3).
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
