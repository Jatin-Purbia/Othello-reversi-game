# Othello - Reversi Game 🎮

## Introduction
A beautiful, modern web-based implementation of the classic Othello (Reversi) board game with an intuitive user interface. Othello is a strategic board game played on an 8x8 grid where the objective is to have the majority of discs of your color on the board by the end of the game.

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
  - **Option 3:** Starts the game setup and play.

---

## 🚀 How to Run the Web Version

### Option 1: Open Directly
Simply double-click the `index.html` file in your file explorer. It will open in your default web browser.

### Option 2: Using a Local Server (Recommended)
For the best experience, use a local web server:

#### Using Python:
```bash
# Python 3
python -m http.server 8000
# Then open: http://localhost:8000
```

#### Using VS Code Live Server:
1. Install the "Live Server" extension in VS Code
2. Right-click on `index.html`
3. Select "Open with Live Server"

---

## 🎯 How to Play the Web Version

### Setup
1. Click "Play Game" from the main menu
2. Enter names for both players
3. Click "Start Game"

### Gameplay
- **Player 1 (Black ⚫)** always goes first
- Click on any highlighted green cell to place your disc
- Valid moves will flip opponent's discs between your pieces
- The game automatically switches turns
- If you have no valid moves, the game will pass your turn
- The game ends when the board is full or neither player can move

### Features
- ✨ Smooth animations for disc placement and flipping
- 📱 Responsive design for all devices
- 🎨 Beautiful modern UI with gradient colors
- 🔄 Real-time score tracking
- ✅ Visual indicators for valid moves
- 🏆 Automatic winner determination

---

## 📁 File Structure
```
Othello-reversi-game/
├── index.html      # Main HTML structure
├── style.css       # All styling and animations
├── script.js       # Game logic and interactivity
├── game_code.cpp   # Original C++ implementation (fixed)
└── README.md       # This file
```

---

## 🛠️ Technologies Used
- **HTML5**: Semantic structure
- **CSS3**: Modern styling with gradients, animations, and responsive design
- **JavaScript (ES6+)**: Game logic, DOM manipulation, and event handling

---

## 🐛 Bug Fixes Applied
### C++ Version:
- Fixed memory access after free in the final winner evaluation
- The C++ code now properly manages memory allocation and deallocation

---

## 👨‍💻 Creator
**Jatin Purbia**  
BTECH 1st Year Student at IIT-Jodhpur

---

## 📝 Browser Compatibility
- Chrome/Edge (recommended)
- Firefox
- Safari
- Opera

---

**Thank you for playing Othello! Enjoy the game! 🎉**

