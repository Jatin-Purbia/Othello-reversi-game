# ICS_CP_CODECRAFTERS

**OTHELLO ORCHESTRATION:  Unveiling the Reversal Symphony**

***Following are the Basic rules which are to be considered while playing the game:***

**Board Setup:**

The game is played on an 8x8 grid board.

Each player starts with two discs of their color placed diagonally in the center.

**Turns:**

Players take turns placing one disc of their color on an empty square.A player must place a disc so that it 'sandwiches' at least one opponent's disc between two of their own discs horizontally, vertically, or diagonally.

**Flipping Discs:**

When a player surrounds the opponent's discs with their own on opposite sides, all the enclosed discs of the opponent's color are flipped to the current player's color.

**Passing:**

If a player has no legal moves, they must pass, and their opponent continues to play.

**End of the Game:**

The game ends when the board is full or when neither player can make a legal move.

The player with the most discs of their color on the board wins.

**Winning:**

The player with the most discs of their color on the board at the end of the game is the winner.

**Tiebreaker:**

If both players have the same number of discs of their color, the game is a tie.

**1) EXECUTION:**

***Board Initialization:***

A 2D array (a[8][8]) is created to represent the Othello game board. Each element is initially set to "_ " (underscore followed by a space).
The starting positions for the four discs (two "x " and two "o ") are set in the center of the board.

***Menu Display:***

A welcome message and a menu are displayed, prompting the user to choose an option.
Options include viewing team members, rules, playing the game, or exiting.

Enter ***1*** for viewing the Team Members.

Enter ***2*** for viewing the Rules of the Othello GamE.

Enter ***3*** for playing the Game.

Enter ***4*** for Exit.

***Menu Option Handling:***

If the user chooses to view team members (b == 1) or rules (b == 2), the corresponding information is displayed.
If the user chooses to play the game (b == 3), the game setup begins.

***Game Setup:***

Player names (p1 and p2) are obtained from the user.
The initial game board is displayed using the show function.
A loop is initiated for the game turns.

***Game Turns:***

Players take turns to make a move. For each turn:
The current player is prompted to input the row and column for their move.
The move is validated using the menu_x or menu_o function, updating the game board accordingly.
The game board is displayed after each move using the show function.
The loop continues until the user decides to exit the game.

***Game Completion:***

If the user chooses to exit the game, they may also choose to evaluate the winner or exit without evaluation.
If the user chooses to evaluate the winner, the program calculates and displays the winner based on the number of "x " and "o " discs.
If the user chooses not to evaluate, the program breaks out of the loop and ends.

***Program Termination:***

If the user chooses to exit the program from the main menu (b == 4), a goodbye message is displayed, and the program terminates.

**2) ENVIRONMENT**

THIS CODE CAN BE USED IN ANY C COMPILER LIKE VISUAL CODE.

  ***THANK YOU FOR READING !***
