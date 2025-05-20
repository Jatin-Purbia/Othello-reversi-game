#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> // For usleep

// function to show the count the number of x's and o's
void show_cnt(char *a[][8], char x[], char o[]) {
    int count_x = 0, count_y = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (strcmp(a[i][j], "x ") == 0) {
                count_x++;
            } else if (strcmp(a[i][j], "o ") == 0) {
                count_y++;
            }
        }
    }
    printf("\nCount of %s : %d\n", x, count_x);
    printf("Count of %s : %d\n", o, count_y);
    return;
}

// function to show the othello board after each turn
void show(char *a[][8]) {
    printf("   ");
    for (int i = 1; i < 9; i++) {
        printf("%d  ", i);
    }
    printf("\n");

    for (int i = 0; i < 8; i++) {
        printf("%d ", i + 1);
        for (int j = 0; j < 8; j++) {
            printf("%s ", a[i][j]);
        }
        printf("\n");
    }
}

// Helper function to update cell content
void update_cell(char *a[][8], int row, int col, const char *new_val) {
    strcpy(a[row][col], new_val);
}

// function that is checking the right side horizontal conditions and updating the scenario for 'x'
void right_condition_x(char *a[][8], int row, int col) {
    // Check if the current position already contains 'x'
    // This check is implicitly handled by `menu_x` setting the cell to "x "
    // The core logic here is to find an 'x' to the left and flip 'o's in between
    for (int i = col - 2; i >= 0; i--) {
        if (strcmp(a[row - 1][i], "x ") == 0) {
            int c = 0;
            for (int j = i + 1; j < col - 1; j++) {
                if (strcmp(a[row - 1][j], "o ") == 0) {
                    c++;
                }
            }
            if (c == (col - i - 2)) {
                for (int j = i + 1; j < col - 1; j++) {
                    update_cell(a, row - 1, j, "x ");
                }
            }
            break;
        }
    }
}

// function that is checking the left side horizontal conditions and updating the scenario for 'x'
void left_condition_x(char *a[][8], int row, int col) {
    // Similar logic as `right_condition_x`, but checking to the right
    for (int i = col; i < 8; i++) {
        if (strcmp(a[row - 1][i], "x ") == 0) {
            int c = 0;
            for (int j = col; j < i; j++) {
                if (strcmp(a[row - 1][j], "o ") == 0) {
                    c++;
                }
            }
            if (c == (i - col)) {
                for (int j = col; j < i; j++) {
                    update_cell(a, row - 1, j, "x ");
                }
            }
            break;
        }
    }
}

// function that is checking the below first diagonal conditions and updating the scenario for 'x'
void diag1_x_down(char *a[][8], int row, int col) {
    int r = row - 1, q = col - 1;
    int flip_start_row = -1, flip_start_col = -1;
    int found_x_after_o = 0;
    int o_count = 0;

    // Search for an 'x' in the diagonal below
    for (int i = 1; r + i < 8 && q + i < 8; i++) {
        if (strcmp(a[r + i][q + i], "o ") == 0) {
            o_count++;
        } else if (strcmp(a[r + i][q + i], "x ") == 0) {
            found_x_after_o = 1;
            flip_start_row = r + 1;
            flip_start_col = q + 1;
            break;
        } else { // Empty space, no flip
            break;
        }
    }

    if (found_x_after_o && o_count > 0) {
        for (int i = 0; i < o_count; i++) {
            update_cell(a, flip_start_row + i, flip_start_col + i, "x ");
        }
    }
}

// function that is checking the upper first diagonal conditions and updating the scenario for 'x'
void diag1_x_up(char *a[][8], int row, int col) {
    int r = row - 1, q = col - 1;
    int flip_start_row = -1, flip_start_col = -1;
    int found_x_after_o = 0;
    int o_count = 0;

    // Search for an 'x' in the diagonal above
    for (int i = 1; r - i >= 0 && q - i >= 0; i++) {
        if (strcmp(a[r - i][q - i], "o ") == 0) {
            o_count++;
        } else if (strcmp(a[r - i][q - i], "x ") == 0) {
            found_x_after_o = 1;
            flip_start_row = r - 1;
            flip_start_col = q - 1;
            break;
        } else { // Empty space, no flip
            break;
        }
    }

    if (found_x_after_o && o_count > 0) {
        for (int i = 0; i < o_count; i++) {
            update_cell(a, flip_start_row - i, flip_start_col - i, "x ");
        }
    }
}

// function that is checking the below second diagonal conditions and updating the scenario for 'x'
void diag2_x_down(char *a[][8], int row, int col) {
    int r = row - 1, q = col - 1;
    int flip_start_row = -1, flip_start_col = -1;
    int found_x_after_o = 0;
    int o_count = 0;

    // Search for an 'x' in the diagonal below (right to left)
    for (int i = 1; r + i < 8 && q - i >= 0; i++) {
        if (strcmp(a[r + i][q - i], "o ") == 0) {
            o_count++;
        } else if (strcmp(a[r + i][q - i], "x ") == 0) {
            found_x_after_o = 1;
            flip_start_row = r + 1;
            flip_start_col = q - 1;
            break;
        } else { // Empty space, no flip
            break;
        }
    }

    if (found_x_after_o && o_count > 0) {
        for (int i = 0; i < o_count; i++) {
            update_cell(a, flip_start_row + i, flip_start_col - i, "x ");
        }
    }
}

// function that is checking the upper second diagonal conditions and updating the scenario for 'x'
void diag2_x_up(char *a[][8], int row, int col) {
    int r = row - 1, q = col - 1;
    int flip_start_row = -1, flip_start_col = -1;
    int found_x_after_o = 0;
    int o_count = 0;

    // Search for an 'x' in the diagonal above (left to right)
    for (int i = 1; r - i >= 0 && q + i < 8; i++) {
        if (strcmp(a[r - i][q + i], "o ") == 0) {
            o_count++;
        } else if (strcmp(a[r - i][q + i], "x ") == 0) {
            found_x_after_o = 1;
            flip_start_row = r - 1;
            flip_start_col = q + 1;
            break;
        } else { // Empty space, no flip
            break;
        }
    }

    if (found_x_after_o && o_count > 0) {
        for (int i = 0; i < o_count; i++) {
            update_cell(a, flip_start_row - i, flip_start_col + i, "x ");
        }
    }
}

// function that is checking the upper vertical conditions and updating the scenario for 'x'
void top_condition_x(char *a[][8], int row, int col) {
    for (int i = row - 2; i >= 0; i--) {
        if (strcmp(a[i][col - 1], "x ") == 0) {
            int c = 0;
            for (int j = i + 1; j < row - 1; j++) {
                if (strcmp(a[j][col - 1], "o ") == 0) {
                    c++;
                }
            }
            if (c == (row - i - 2)) {
                for (int j = i + 1; j < row - 1; j++) {
                    update_cell(a, j, col - 1, "x ");
                }
            }
            break;
        }
    }
}

// function that is checking the bottom vertical conditions and updating the scenario for 'x'
void bottom_condition_x(char *a[][8], int row, int col, char y[], char z[]) {
    for (int i = row; i < 8; i++) {
        if (strcmp(a[i][col - 1], "x ") == 0) {
            int c = 0;
            for (int j = row; j < i; j++) {
                if (strcmp(a[j][col - 1], "o ") == 0) {
                    c++;
                }
            }
            if (c == (i - row)) {
                for (int j = row; j < i; j++) {
                    update_cell(a, j, col - 1, "x ");
                }
            }
            break;
        }
    }
    printf("\nUpdated Game View -\n");
    show(a);
    show_cnt(a, y, z);
}

// function that is checking the left side horizontal conditions and updating the scenario for 'o'
void left_condition_o(char *a[][8], int row, int col) {
    for (int i = col - 2; i >= 0; i--) {
        if (strcmp(a[row - 1][i], "o ") == 0) {
            int c = 0;
            for (int j = i + 1; j < col - 1; j++) {
                if (strcmp(a[row - 1][j], "x ") == 0) {
                    c++;
                }
            }
            if (c == (col - i - 2)) {
                for (int j = i + 1; j < col - 1; j++) {
                    update_cell(a, row - 1, j, "o ");
                }
            }
            break;
        }
    }
}

// function that is checking the right side horizontal conditions and updating the scenario for 'o'
void right_condition_o(char *a[][8], int row, int col) {
    for (int i = col; i < 8; i++) {
        if (strcmp(a[row - 1][i], "o ") == 0) {
            int c = 0;
            for (int j = col; j < i; j++) {
                if (strcmp(a[row - 1][j], "x ") == 0) {
                    c++;
                }
            }
            if (c == (i - col)) {
                for (int j = col; j < i; j++) {
                    update_cell(a, row - 1, j, "o ");
                }
            }
            break;
        }
    }
}

// function that is checking the below first diagonal conditions and updating the scenario for 'o'
void diag1_o_down(char *a[][8], int row, int col) {
    int r = row - 1, q = col - 1;
    int flip_start_row = -1, flip_start_col = -1;
    int found_o_after_x = 0;
    int x_count = 0;

    for (int i = 1; r + i < 8 && q + i < 8; i++) {
        if (strcmp(a[r + i][q + i], "x ") == 0) {
            x_count++;
        } else if (strcmp(a[r + i][q + i], "o ") == 0) {
            found_o_after_x = 1;
            flip_start_row = r + 1;
            flip_start_col = q + 1;
            break;
        } else {
            break;
        }
    }

    if (found_o_after_x && x_count > 0) {
        for (int i = 0; i < x_count; i++) {
            update_cell(a, flip_start_row + i, flip_start_col + i, "o ");
        }
    }
}

// function that is checking the upper first diagonal conditions and updating the scenario for 'o'
void diag1_o_up(char *a[][8], int row, int col) {
    int r = row - 1, q = col - 1;
    int flip_start_row = -1, flip_start_col = -1;
    int found_o_after_x = 0;
    int x_count = 0;

    for (int i = 1; r - i >= 0 && q - i >= 0; i++) {
        if (strcmp(a[r - i][q - i], "x ") == 0) {
            x_count++;
        } else if (strcmp(a[r - i][q - i], "o ") == 0) {
            found_o_after_x = 1;
            flip_start_row = r - 1;
            flip_start_col = q - 1;
            break;
        } else {
            break;
        }
    }

    if (found_o_after_x && x_count > 0) {
        for (int i = 0; i < x_count; i++) {
            update_cell(a, flip_start_row - i, flip_start_col - i, "o ");
        }
    }
}

// function that is checking the below second diagonal conditions and updating the scenario for 'o'
void diag2_o_down(char *a[][8], int row, int col) {
    int r = row - 1, q = col - 1;
    int flip_start_row = -1, flip_start_col = -1;
    int found_o_after_x = 0;
    int x_count = 0;

    for (int i = 1; r + i < 8 && q - i >= 0; i++) {
        if (strcmp(a[r + i][q - i], "x ") == 0) {
            x_count++;
        } else if (strcmp(a[r + i][q - i], "o ") == 0) {
            found_o_after_x = 1;
            flip_start_row = r + 1;
            flip_start_col = q - 1;
            break;
        } else {
            break;
        }
    }

    if (found_o_after_x && x_count > 0) {
        for (int i = 0; i < x_count; i++) {
            update_cell(a, flip_start_row + i, flip_start_col - i, "o ");
        }
    }
}

// function that is checking the upper second diagonal conditions and updating the scenario for 'o'
void diag2_o_up(char *a[][8], int row, int col) {
    int r = row - 1, q = col - 1;
    int flip_start_row = -1, flip_start_col = -1;
    int found_o_after_x = 0;
    int x_count = 0;

    for (int i = 1; r - i >= 0 && q + i < 8; i++) {
        if (strcmp(a[r - i][q + i], "x ") == 0) {
            x_count++;
        } else if (strcmp(a[r - i][q + i], "o ") == 0) {
            found_o_after_x = 1;
            flip_start_row = r - 1;
            flip_start_col = q + 1;
            break;
        } else {
            break;
        }
    }

    if (found_o_after_x && x_count > 0) {
        for (int i = 0; i < x_count; i++) {
            update_cell(a, flip_start_row - i, flip_start_col + i, "o ");
        }
    }
}

// function that is checking the upper vertical conditions and updating the scenario for 'o'
void top_condition_o(char *a[][8], int row, int col) {
    for (int i = row - 2; i >= 0; i--) {
        if (strcmp(a[i][col - 1], "o ") == 0) {
            int c = 0;
            for (int j = i + 1; j < row - 1; j++) {
                if (strcmp(a[j][col - 1], "x ") == 0) {
                    c++;
                }
            }
            if (c == (row - i - 2)) {
                for (int j = i + 1; j < row - 1; j++) {
                    update_cell(a, j, col - 1, "o ");
                }
            }
            break;
        }
    }
}

// function that is checking the bottom vertical conditions and updating the scenario for 'o'
void bottom_condition_o(char *a[][8], int row, int col, char y[], char z[]) {
    for (int i = row; i < 8; i++) {
        if (strcmp(a[i][col - 1], "o ") == 0) {
            int c = 0;
            for (int j = row; j < i; j++) {
                if (strcmp(a[j][col - 1], "x ") == 0) {
                    c++;
                }
            }
            if (c == (i - row)) {
                for (int j = row; j < i; j++) {
                    update_cell(a, j, col - 1, "o ");
                }
            }
            break;
        }
    }
    printf("\nUpdated Game View -\n");
    show(a);
    show_cnt(a, y, z);
}

// this is the menu function that contains all sorts of calling statements of X for checking and updating the scenario of the game
void menu_x(char *a[][8], int n, int m, char y[], char z[]) {
    if (n > 8 || n < 1 || m > 8 || m < 1) {
        printf("Wrong input, try again!\n");
        printf("Again %s's turn\n", z);
        printf("Write the row and column:");
        scanf("%d %d", &n, &m);
        menu_x(a, n, m, y, z);
    } else if ((strcmp(a[n - 1][m - 1], "x ") == 0) || (strcmp(a[n - 1][m - 1], "o ") == 0)) {
        printf("Wrong input, try again!\n");
        printf("Again %s's turn\n", z);
        printf("Write the row and column:");
        scanf("%d %d", &n, &m);
        menu_x(a, n, m, y, z);
    } else {
        update_cell(a, n - 1, m - 1, "x ");
        printf("\n");
        // No need to show the board here, it's shown after all conditions are checked
        left_condition_x(a, n, m);
        right_condition_x(a, n, m);
        diag1_x_up(a, n, m);
        diag1_x_down(a, n, m);
        diag2_x_up(a, n, m);
        diag2_x_down(a, n, m);
        top_condition_x(a, n, m);
        bottom_condition_x(a, n, m, y, z); // This function also calls show and show_cnt
    }
    return;
}

// this is the menu function that contains all sorts of calling statements of Y for checking and updating the scenario of the game
void menu_o(char *a[][8], int n, int m, char y[], char z[]) {
    if (n > 8 || n < 1 || m > 8 || m < 1) {
        printf("Wrong input, try again!\n");
        printf("Again %s's turn\n", z);
        printf("Write the row and column:");
        scanf("%d %d", &n, &m);
        menu_o(a, n, m, y, z);
    } else if ((strcmp(a[n - 1][m - 1], "x ") == 0) || (strcmp(a[n - 1][m - 1], "o ") == 0)) {
        printf("Wrong input, try again!\n");
        printf("Again %s's turn\n", z);
        printf("Write the row and column:");
        scanf("%d %d", &n, &m);
        menu_o(a, n, m, y, z);
    } else {
        update_cell(a, n - 1, m - 1, "o ");
        printf("\n");
        // No need to show the board here, it's shown after all conditions are checked
        left_condition_o(a, n, m);
        right_condition_o(a, n, m);
        diag1_o_up(a, n, m);
        diag1_o_down(a, n, m);
        diag2_o_up(a, n, m);
        diag2_o_down(a, n, m);
        top_condition_o(a, n, m);
        bottom_condition_o(a, n, m, y, z); // This function also calls show and show_cnt
    }
    return;
}

int main() {
    char message[] = "* WELCOME TO THE WORLD OF GAMES *\n\tOTHELLO ORCHESTRATION: \n    Unveiling the Reversal Symphony\n\n";
    int i;
    for (i = 0; message[i] != '\0'; i++) {
        putchar(message[i]);
        fflush(stdout);
        usleep(100000); // usleep takes input in microseconds
    }

    while (1) {
        char table[] = "TABLE OF CONTENT-\nEnter 1 for viewing the details of game creator\nEnter 2 for viewing the Rules of the Othello Game\nEnter 3 for playing the Game\nEnter 4 for Exit\n";
        int j;
        for (j = 0; table[j] != '\0'; j++) {
            putchar(table[j]);
            fflush(stdout);
            usleep(10000);
        }
        int b;
        printf("Enter your choice: ");
        scanf("%d", &b);

        if (b == 1) {
            printf("\nHi Guys\n My Name is Jatin Purbia\n I'm a BTECH 1st year Student at IIT-Jodhpur\n\n");
        } else if (b == 2) {
            printf("%s", "\n\nFollowing are the Basic rules which are to be considered while playing the game:\n\
                        \nBoard Setup:\n\
                        The game is played on an 8x8 grid board.\n\
                        Each player starts with two discs of their color placed diagonally in the center.\n\
                        \nTurns:\n\
                        Players take turns placing one disc of their color on an empty square.\n\
                        A player must place a disc so that it 'sandwiches' at least one opponent's disc between two of their own discs horizontally, vertically, or diagonally.\n\
                        \nFlipping Discs:\n\
                        When a player surrounds the opponent's discs with their own on opposite sides, all the enclosed discs of the opponent's color are flipped to the current player's color.\n\
                        \nPassing:\n\
                        If a player has no legal moves, they must pass, and their opponent continues to play.\n\
                        \nEnd of the Game:\n\
                        The game ends when the board is full or when neither player can make a legal move.\n\
                        The player with the most discs of their color on the board wins.\n\
                        \nWinning:\n\
                        The player with the most discs of their color on the board at the end of the game is the winner.\n\
                        \nTiebreaker:\n\
                        If both players have the same number of discs of their color, the game is a tie.\n\n");
        } else if (b == 3) {
            char p1[20], p2[20];
            printf("Enter name of player 1:");
            scanf("%s", p1);
            printf("Enter name of player 2:");
            scanf("%s", p2);

            char *a[8][8];
            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                    a[i][j] = (char *)malloc(3 * sizeof(char)); // Allocate space for "_ " and null terminator
                    if (a[i][j] == NULL) {
                        perror("Failed to allocate memory");
                        exit(EXIT_FAILURE);
                    }
                    strcpy(a[i][j], "_ ");
                }
            }

            strcpy(a[3][3], "x ");
            strcpy(a[3][4], "o ");
            strcpy(a[4][3], "o ");
            strcpy(a[4][4], "x ");
            show(a);

            int end1, end2;
            int count_x, count_y;

            // The game typically has a maximum of 60 moves (64 cells - 4 initial)
            // You had a loop for 30 moves, which means 15 turns for each player.
            // A full game is 60 moves. Let's make it 60 for now.
            for (int turn_count = 0; turn_count < 60; turn_count++) {
                int n, m;
                printf("%s's turn\n", p1);
                printf("Write the row and column:");
                scanf("%d %d", &n, &m);
                menu_x(a, n, m, p1, p2);

                printf("\nDo you want to exit the game? \nif yes-->press 1\nif no--> press 2\n");
                printf("Enter your choice: ");
                scanf("%d", &end1);
                if (end1 == 1) {
                    printf("\nDo you want to evaluate the winner? \nif yes-->press 1\nif no-->press 2\n");
                    printf("Enter your choice: ");
                    scanf("%d", &end2);
                    if (end2 == 1) {
                        count_x = 0;
                        count_y = 0;
                        for (int r_idx = 0; r_idx < 8; r_idx++) {
                            for (int c_idx = 0; c_idx < 8; c_idx++) {
                                if (strcmp(a[r_idx][c_idx], "x ") == 0) {
                                    count_x++;
                                } else if (strcmp(a[r_idx][c_idx], "o ") == 0) {
                                    count_y++;
                                }
                            }
                        }
                        if (count_x > count_y) {
                            printf("\nCONGRATULATIONS...Winner is %s !!!\n\n", p1);
                        } else if (count_y > count_x) {
                            printf("\nCONGRATULATIONS...Winner is %s !!!\n\n", p2);
                        } else {
                            printf("\nOH IT'S A TIE\n\n");
                        }
                        break; // Exit game loop
                    } else if (end2 == 2) {
                        break; // Exit game loop without evaluating winner
                    }
                }

                // If the game board is full after P1's turn, end the game
                int empty_cells = 0;
                for (int r_idx = 0; r_idx < 8; r_idx++) {
                    for (int c_idx = 0; c_idx < 8; c_idx++) {
                        if (strcmp(a[r_idx][c_idx], "_ ") == 0) {
                            empty_cells++;
                        }
                    }
                }
                if (empty_cells == 0) {
                    printf("\nBoard is full! Game Over.\n");
                    break;
                }
                
                int p, q;
                printf("%s's turn\n", p2);
                printf("Write the row and column:");
                scanf("%d %d", &p, &q);
                menu_o(a, p, q, p1, p2);

                printf("\nDo you want to exit the game? \nif yes-->press 1\nif no--> press 2\n");
                printf("Enter your choice: ");
                scanf("%d", &end1);
                if (end1 == 1) {
                    printf("\nDo you want to evaluate the winner? \nif yes-->press 1\nif no-->press 2\n");
                    printf("Enter your choice: ");
                    scanf("%d", &end2);
                    if (end2 == 1) {
                        count_x = 0;
                        count_y = 0;
                        for (int r_idx = 0; r_idx < 8; r_idx++) {
                            for (int c_idx = 0; c_idx < 8; c_idx++) {
                                if (strcmp(a[r_idx][c_idx], "x ") == 0) {
                                    count_x++;
                                } else if (strcmp(a[r_idx][c_idx], "o ") == 0) {
                                    count_y++;
                                }
                            }
                        }
                        if (count_x > count_y) {
                            printf("CONGRATULATIONS...Winner is %s !!!\n\n", p1);
                        } else if (count_y > count_x) {
                            printf("CONGRATULATIONS...Winner is %s !!!\n\n", p2);
                        } else {
                            printf("OH IT'S A TIE\n\n");
                        }
                        break; // Exit game loop
                    } else if (end2 == 2) {
                        break; // Exit game loop without evaluating winner
                    }
                }
                
                // If the game board is full after P2's turn, end the game
                empty_cells = 0;
                for (int r_idx = 0; r_idx < 8; r_idx++) {
                    for (int c_idx = 0; c_idx < 8; c_idx++) {
                        if (strcmp(a[r_idx][c_idx], "_ ") == 0) {
                            empty_cells++;
                        }
                    }
                }
                if (empty_cells == 0) {
                    printf("\nBoard is full! Game Over.\n");
                    break;
                }
            }

            // Free the dynamically allocated memory
            for (int r_idx = 0; r_idx < 8; r_idx++) {
                for (int c_idx = 0; c_idx < 8; c_idx++) {
                    free(a[r_idx][c_idx]);
                }
            }

            // Final winner evaluation if the loop finishes without early exit
            count_x = 0;
            count_y = 0;
            for (int r_idx = 0; r_idx < 8; r_idx++) {
                for (int c_idx = 0; c_idx < 8; c_idx++) {
                    if (strcmp(a[r_idx][c_idx], "x ") == 0) {
                        count_x++;
                    } else if (strcmp(a[r_idx][c_idx], "o ") == 0) {
                        count_y++;
                    }
                }
            }

            if (count_x > count_y) {
                printf("CONGRATULATIONS...Winner is %s !!!\n\n", p1);
            } else if (count_y > count_x) {
                printf("CONGRATULATIONS...Winner is %s !!!\n\n", p2);
            } else {
                printf("OH IT'S A TIE\n\n");
            }
        } else if (b == 4) {
            printf("\nTHANK YOU For Playing\nHave A Nice Day!!\n");
            break;
        } else {
            printf("\nInvalid choice. Please enter a number between 1 and 4.\n\n");
        }
    }
    return 0;
}