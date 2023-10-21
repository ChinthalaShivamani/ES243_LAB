#include <stdio.h>
#include <assert.h>

#include "test.h"

enum {
    LINE_EMPTY = 0,
    LINE_RED = 1,
    LINE_BLUE = 2
};

typedef char Board[15];
typedef char Player;

Player switchPlayer(Player player) {
    return (player == LINE_RED) ? LINE_BLUE : LINE_RED;
}

int isBoardFull(Board board) {
    int full = 1;
    int i = 0;
    while (i < 15) {
        if (board[i] == LINE_EMPTY) {
            full = 0;
            break;
        }
        i++;
    }
    return full;
}

typedef struct {
    int line;
    int score;
} Move;

int hasPlayerWon(Board board, Player player) {
    Player opponent = switchPlayer(player);

    int j = 0;
    int k;
    while (j < 4) {
        k = 0;
        k += (4 - j);
        if (board[j] == opponent) {
            int i = j + 1;
            while (i < 5) {
                if ((board[i] == opponent) && (board[i + k] == opponent)) {
                    return 1;
                }
                i++;
            }
        }
        j++;
    }

    int l;
    j = 5;
    while (j < 8) {
        l = 0;
        l += (8 - j);
        if (board[j] == opponent) {
            int i = j + 1;
            while (i < 9) {
                if ((board[i] == opponent) && (board[i + l] == opponent)) {
                    return 1;
                }
                i++;
            }
        }
        j++;
    }

    int m;
    j = 9;
    while (j < 11) {
        m = 0;
        m += (11 - j);
        if (board[j] == opponent) {
            int i = j + 1;
            while (i < 12) {
                if ((board[i] == opponent) && (board[i + m] == opponent)) {
                    return 1;
                }
                i++;
            }
        }
        j++;
    }

    return ((board[12] == opponent) && (board[13] == opponent) && (board[14] == opponent)) ? 1 : 0;
}

Move findBestMove(Board board, Player player) {
    Move chosenMove;
    Move bestResponse;

    int comparison = 100;
    chosenMove.line = -1;
    chosenMove.score = -1;

    int i = 0;
    while (i < 15) {
        if (board[i] != LINE_EMPTY) {
            i++;
            continue;
        }

        board[i] = player;

        if (hasPlayerWon(board, switchPlayer(player))) {
            board[i] = LINE_EMPTY;
            if (chosenMove.line == -1) {
                chosenMove.line = i;
            }
            i++;
            continue;
        }

        bestResponse = findBestMove(board, switchPlayer(player));

        if (bestResponse.score < 0) {
            chosenMove.line = i;
            chosenMove.score = 1 - bestResponse.score;
            board[i] = LINE_EMPTY;
            return chosenMove;
        } else {
            int score = -1 - bestResponse.score;
            if (score < comparison) {
                chosenMove.score = score;
                comparison = score;
                chosenMove.line = i;
            }
        }

        board[i] = LINE_EMPTY;
        i++;
    }

    return chosenMove;
}

void printBoard(Board board) {
    int i = 0;
    while (i < 15) {
        (board[i] == LINE_RED) ? printf("R  ") : (board[i] == LINE_BLUE) ? printf("B  ") : printf("N  ");
        i++;
    }
    printf("\n");
}

void initializeBoard(Board board) {
    int i = 0;
    while (i < 15) {
        board[i] = LINE_EMPTY;
        i++;
    }
}

int main() {
    Board game;
    initializeBoard(game);
    printf("Select your player (1 for Red, 2 for Blue): ");
    int playerChoice;
    int isGameOver = 0;
    Player currentPlayer;
    Player humanPlayer;
    Player computerPlayer;

    scanf("%d", &playerChoice);

    humanPlayer = (playerChoice == 1) ? LINE_RED : LINE_BLUE;
    computerPlayer = (playerChoice == 1) ? LINE_BLUE : LINE_RED;
    currentPlayer = humanPlayer;

    printf("Who should make the first move?\n");
    printf("Enter 1 for human\n");
    printf("Enter 2 for Computer\n");
    scanf("%d", &playerChoice);

    currentPlayer = (playerChoice == 1) ? humanPlayer : computerPlayer;

    while (!isGameOver) {
        if (currentPlayer == humanPlayer) {
            int userMove;
            printf("Your move (Enter a number between 0 and 14): ");
            scanf("%d", &userMove);

            game[userMove] = humanPlayer;
        } else {
            Move computerMove = findBestMove(game, computerPlayer);
            game[computerMove.line] = computerPlayer;
            printf("Computer's move: %d\n", computerMove.line);
        }

        printBoard(game);

        if (hasPlayerWon(game, humanPlayer)) {
            printf("Human has won!\n");
            isGameOver = 1;
            break;
        } else if (hasPlayerWon(game, computerPlayer)) {
            printf("Computer has won!\n");
            isGameOver = 1;
            break;
        } else if (isBoardFull(game)) {
            printf("It's a draw!\n");
            isGameOver = 1;
            break;
        }

        currentPlayer = switchPlayer(currentPlayer);
    }

    printf("Game over.\n");

    return 0;
}
