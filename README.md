# OTHELLO ORCHESTRATION: Unveiling the Reversal Symphony

## Introduction
Othello is a strategic board game played on an 8x8 grid. The objective is to have the majority of discs of your color on the board by the end of the game. This document provides an overview of the rules, execution, and environment required to run the game.

---

## Basic Rules

### **Board Setup:**
- The game is played on an 8x8 grid.
- Each player starts with two discs of their color placed diagonally at the center.

### **Turns:**
- Players take turns placing one disc of their color on an empty square.
- A valid move must "sandwich" at least one opponent's disc between two of the player's own discs, in a horizontal, vertical, or diagonal direction.

### **Flipping Discs:**
- When a player surrounds the opponent's discs on opposite sides, all enclosed discs flip to the player's color.

### **Passing:**
- If a player has no legal moves, they must pass, and the opponent continues to play.

### **End of the Game:**
- The game ends when the board is full or when neither player can make a legal move.

### **Winning:**
- The player with the most discs of their color on the board at the end of the game wins.
- In case of a tie (both players have an equal number of discs), the game ends in a draw.

---

## Execution

### **Board Initialization:**
- The game board is represented as a 2D array (`a[8][8]`), initialized with empty slots (`"_ "`).
- The starting four discs (two "x " and two "o ") are placed at the center.

### **Menu Display:**
- The user is presented with a menu with the following options:

  1. View Team Members
  2. View Game Rules
  3. Play the Game
  4. Exit

### **Menu Option Handling:**
- If the user selects:
  - **Option 1:** Displays team members.
  - **Option 2:** Displays the rules of Othello.
  - **Option 3:** Starts the game setup.
  - **Option 4:** Exits the program with a farewell message.

### **Game Setup:**
- Players enter their names (`p1` and `p2`).
- The initial board is displayed using the `show()` function.
- A loop begins for turn-based gameplay.

### **Game Turns:**
- Each turn consists of:
  - The current player inputting a row and column for their move.
  - Move validation using `menu_x()` or `menu_o()`.
  - Updating and displaying the board.
  - The game continues until a player chooses to exit.

### **Game Completion:**
- If a player exits, they can:
  - Evaluate the winner based on the number of discs.
  - Exit without evaluation.

### **Program Termination:**
- If the player chooses **Option 4** from the main menu, the program displays a farewell message and exits.

---

## Environment
- This game is implemented in C.
- It can be compiled and executed using any standard C compiler, such as **GCC**, **Visual Studio Code**, or **Code::Blocks**.

---

## Acknowledgment
Thank you for playing Othello! We hope you enjoy the game and refine your strategy over time.

---

## Contact
For any questions or suggestions, feel free to reach out!

**Happy Gaming!** 🎮

