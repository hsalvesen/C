/* 
   naughts_and_crosses: implementation of a two-player game of
   noughts and crosses (or tic-tic-toe).

    Board is implemented as a 1D array that contains the 3x3 board
    state like:
    
    0 1 2
    3 4 5
    6 7 8

*/

#include <stdio.h>

#define NONE 0
#define PLAYER1 1
#define PLAYER2 2

#define GRIDSIZE 3

// draw_token: render single player piece to screen
void draw_token(int token) {
    switch (token) {
        case NONE:
            printf(" ");
            break;
        case PLAYER1:
            printf("O");
            break;
        case PLAYER2:
            printf("X");
            break;
    }
}

// get_token: 
int get_token(int *board, int row, int col) {
    return board[GRIDSIZE*row + col];
}

void draw_line(void) {
    printf("-------\n");
}

// draw_board: draws boards to the screen
void draw_board(int *board) {
    draw_line();
    for (int row = 0; row < GRIDSIZE; row++) {
        printf("|");
        for (int col = 0; col < GRIDSIZE; col++) {
            int token = get_token(board,row,col);
            draw_token(token);
            printf("|");
        }
        printf("\n");
        draw_line();
    }
}

// check_move: check proposed move is valid
int check_move(int move, int *board) {
    if (move >= 0 && move <= 8 && board[move] == NONE) {
        return 1;
    }
    else {
        return 0;
    }
}

// get_move: gets a move from the user
int get_move(int *board) {
    int move = -1;
    while ( check_move(move, board) == 0 ) {
        printf("Enter move (0-8): ");
        scanf("%d", &move);
    }
    return move;
}

// check_row_win: checks if a row is in a winnning state
int check_row_win(int *board, int row) {
    int i1 = GRIDSIZE*row, i2 = 1+GRIDSIZE*row, i3 = 2+GRIDSIZE*row;
    if (board[i1] != NONE && board[i1] == board[i2] && board[i1] == board[i3]) {
        return 1;
    }
    else {
        return 0;
    }
}

// check_row_win: checks if a column is in a winnning state
int check_col_win(int *board, int col) {
    int i1 = col, i2 = col+GRIDSIZE, i3 = col+2*GRIDSIZE;
    if (board[i1] != NONE && board[i1] == board[i2] && board[i1] == board[i3]) {
        return 1;
    }
    else {
        return 0;
    }
}

// check_for_win: returns 1 if the current board state contains a win
int check_for_win(int *board) {

    // check rows and columns for a win
    if ( check_row_win(board,0) || check_row_win(board,1) || check_row_win(board,2) ) {
        return 1;
    }
    if ( check_col_win(board,0) || check_col_win(board,1) || check_col_win(board,2) ) {
        return 1;
    }

    // check diagonals for a win
    if (board[0] != NONE && board[0] == board[4] && board[0] == board[8]) {
        return 1;
    }
    if (board[2] != NONE && board[2] == board[4] && board[2] == board[6]) {
        return 1;
    }

    return 0;
}

int main(void) {

    // initialise variables to track which player, look for winner
    int current_player = PLAYER1;
    int winner = NONE;
    int move_count = 0;
    
    int board[9] = {NONE, NONE, NONE,
        NONE, NONE, NONE,
        NONE, NONE, NONE};
    
    // main game loop
    while (winner == NONE) {

        //draw board
        draw_board(board);

        // get player move, put on board
        int move = get_move(board);
        board[move] = current_player;

        // check if board is in a winning state
        if ( check_for_win(board) == 1 ) {
            winner = current_player;
        }

        // switch player
        if (current_player == PLAYER1) {
            current_player = PLAYER2;
        }
        else {
            current_player = PLAYER1;
        }

        // check for draw
        move_count++;
        if (move_count == 9) {
            break;
        }

    }

    // congratulate winner
    draw_board(board);
    if (winner == NONE) {
        printf("A draw!\n");
    }
    else {
        printf("Congratulations! Player %d wins!\n", winner);
    }
    
}

