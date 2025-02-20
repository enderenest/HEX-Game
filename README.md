# 🔷🔴 Hex Game Implementation


## 📝 Project Overview

This project is a console-based implementation of the Hex Board Game using C++. It includes:

HexBoard Class for board representation and player moves.

UnionFind Class for tracking connected components to check winning conditions.

Main Game Loop allowing two players to play alternately until one player wins.

Players compete as Red (R) and Blue (B). The goal is to form a continuous path connecting opposite sides of the board.

## 🏛️ Key Components

### 1️⃣ HexBoard Class

Represents the board as a 2D grid with cells marked R for Red, B for Blue, and E for Empty.

Handles player moves and board visualization using ASCII symbols.

Key functions:

printBoard() – Prints the current state of the board.

turnRed(int i, int j) – Marks position (i, j) with R if empty.

turnBlue(int i, int j) – Marks position (i, j) with B if empty.

### 2️⃣ UnionFind Class

Implements Union-Find data structure to check for connected paths.

Helps determine winning conditions efficiently.

Key functions:

unionSets(int x, int y) – Connects two positions on the board.

winning_condition(HexBoard &hex) – Checks if Red or Blue has connected their respective sides.

unionNeighbors(HexBoard &hex, int i, int j, char color) – Connects a cell to its same-colored neighbors.

---

##▶️ How to Run

Compile and run the program:

g++ main.cpp -o hex_game
./hex_game

Follow the instructions in the console:

Players take turns by entering row and column indices (1-based).

Invalid moves prompt re-entry.

The game ends when Red connects top to bottom or Blue connects left to right.

---

## 📤 Sample Output

Welcome to my HEX game's early gameplay
Red can play the first move
Red's turn
1 1
...
Game over!
RED WINS!

---

## 🧑‍💻 Dependencies

C++11 or later

---

## ✨ Key Learnings

Board game representation using ASCII Art.

Validating player moves.

Pathfinding and connectivity using Union-Find.

---

## 📫 Contact

Feel free to reach out for questions or contributions!
