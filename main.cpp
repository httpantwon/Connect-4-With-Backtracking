/*********
 * Backtracking program that builds on Project 5 — Connect 4.
   Program implements the ability to undo a move through a
   linked list, which keeps track of the plays that are made.
   The current player can undo the previous player's move on
   the board by entering U or u. They can continue this action
   until the board is empty.

 * Class: CS 141, Fall 2023
 * System: ZyBook Lab *
 * @author Antwon Walls
 * @version November 29, 2023
 * *******/

#include <iostream>
#include <iomanip>
#include <string>
#include "boardList.h"

using namespace std;

/**Function to fill the initial contents of the board
 * instead of the elements containing random, spattered values**/
void fillBoard(char board[6][7]) {
    for (int row = 0; row < 6; row++) {
        for (int col = 0; col < 7; col++) {
            board[row][col] = '-';
        }
    }
}

/**code that prints out the contents of the starting board**/
void displayBoard(char board[6][7]) {
    cout << setw(2);
    /**This for loop just prints out each column index (0 1 2 3 4 5 6)**/
    for (int i = 0; i < 7; i++) {
        cout << i << " ";
    }
    cout << endl;

    /**This for loop prints out the board's empty columns
     * at each respected column in each row**/
    for (int row = 0; row < 6; row++) {
        cout << setw(2);
        for (int col = 0; col < 7; col++) {
            cout << board[row][col] << ' ';
        }
        cout << endl;
    }
}

/**Checks for valid vertical win (4 X's/O's in a row). Returns false
 * if a valid vertical win isn't found**/
bool validVerticalWin(char board[6][7], char currentUser) {
    for (int row = 5; row >= 3; row--) {
        for (int col = 0; col <= 6; col++) {
            if (board[row][col] == currentUser && board[row-1][col] == currentUser &&
                board[row-2][col] == currentUser && board[row-3][col] == currentUser) {
                return true;
            }
        }
    }
    return false;
}
/**Checks for valid horizontal win (4 X's/O's in a column). Returns false
 * if a valid horizontal win isn't found**/
bool validHorizontalWin(char board[6][7], char currentUser) {
    for (int row = 5; row >= 3; row--) {
        for (int col = 0; col <= 3; col++) {
            if (board[row][col] == currentUser && board[row][col+1] == currentUser &&
                board[row][col+2] == currentUser && board[row][col+3] == currentUser) {
                return true;
            }
        }
    }
    return false;
}

/**Checks for different patterns of valid diagonal wins
 * (4 slanted consecutive X's/O's). Function returns false
 * if a valid diagonal win isn't found**/
bool validDiagonalWin(char board[6][7], char currentUser) {
    /**from bottom left to top right**/
    for (int row = 5; row >= 3; row--) {
        for (int col = 0; col <= 3; col++) {
            if (board[row][col] == currentUser && board[row-1][col+1] == currentUser &&
                board[row-2][col+2] == currentUser && board[row-3][col+3] == currentUser) {
                return true;
            }
        }
    }

    /**from top left to bottom right**/
    for (int row = 0; row <= 3; row++) {
        for (int col = 0; col <= 3; col++) {
            if (board[row][col] == currentUser && board[row+1][col+1] == currentUser &&
                board[row+2][col+2] == currentUser && board[row+3][col+3] == currentUser) {
                return true;
            }
        }
    }

    /**from bottom right to top left**/
    for (int row = 5; row >= 0; row--) {
        for (int col = 6; col >= 3; col--) {
            if ((board[row][col] == currentUser) && (board[row--][col--] == currentUser)
                && board[row-2][col-2] == currentUser && board[row-3][col-3] == currentUser) {
                return true;
            }
        }
    }

    /**from top right to bottom left**/
    for (int row = 0; row <= 3; row++) {
        for (int col = 6; col >= 3; col--) {
            if (board[row][col] == currentUser && board[row-1][col-1] == currentUser &&
                board[row-2][col-2] == currentUser && board[row-3][col-3] == currentUser) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    ///prints intro message
    cout << "This is the Game Connect 4." << endl
    << "Each player should place an X or an O in the space" << endl
    << "by entering the column you want to place the piece." << endl
    << "The piece will fall until it reaches the bottom or" << endl
    << "the current places in the board. When X or O gets 4 in " << endl
    << "a row (either horizontally, vertically, or diagonally)," << endl
    << "then that person wins. The user can enter Q (or q) to" << endl
    << "end the game early." << endl << "Let's get started!!!" << endl;

    char board[6][7];
    char currentUser = 'X';

    ///user's input is either q or a column
    string userInput;

    fillBoard(board);

    ///colIndex keeps track of the index number of the user's chosen column
    int colIndex;

    displayBoard(board);
    boardList linkedList;

    while (true) {
        cout << "It is " << currentUser << "'s turn." << endl
        << "Enter a column to place your piece. ";

        /**User's input: the user either quits the game or
         * chooses a column**/
        cin >> userInput;
        if (userInput == "Q" || userInput == "q") {
            cout << "Ending Game";
            break;
        }

        /**else, if user enters u, removes the last element at the linked list
         * (remove last node and update tail). call remove() function here.**/
        else if (userInput == "U" || userInput == "u") {
            if (linkedList.getHead() != nullptr) {
                linkedList.undo(board);

                /**determine whichever player is playing, then switches to the
                 * other user, after undoing move**/
                if (currentUser == 'X') {
                    currentUser = 'O';
                }
                else {
                    currentUser = 'X';
                }
            }

            displayBoard(board);
            continue;
        }

        else if (userInput == "P" || userInput == "p") {
            linkedList.print(linkedList.getHead());
            displayBoard(board);
            continue;
        }

        /**the user has chosen not to quit and they must enter in a column,
         * which is a number, hence the stoi conversion of their input**/
        colIndex = stoi(userInput);

        /**if value is out of bound on the board, then continue,
         * which will restart this while loop**/
        if ((colIndex > 6) || (colIndex < 0)) {
            cout << "Please enter a valid column" << endl;
            continue;
        }

        /**When the board fills all the way up to the top,
         * prevents the user from filling it up anymore so the
         * array doesn't overwrite**/
        if (board[0][colIndex] != '-') {
            cout << "column chosen is already full" << endl;
            continue;
        }

        /**If player picks a column that's full, doesn't update the board
         * and restarts the loop until they pick an one with a spot open one**/
        for (int row = 5; row >= 0; row--) {
            if (board[row][colIndex] != '-') {
                continue;
            }
            else {
                /**Slot on the array is a player (X or O). Calls the add()
                 * function here to add the next new version
                 * of the board to a new node**/
                linkedList.add(board);

                /**Based on who is playing, sets that spot in
                 * board[row][col] as that player**/
                board[row][colIndex] = currentUser;

                ///shows the updated board
                displayBoard(board);
                break;
            }
        }

        /**checks if a player wins the game check**/
        if (validVerticalWin(board, currentUser) || validHorizontalWin(board, currentUser) || validDiagonalWin(board, currentUser)) {
            cout << "Game is Over, Player " << currentUser << " got 4 in a row!!!!";
            break;
        }

        /**This stage means a player has not won (if the above if statement wasn't true).
         * Program then checks if the board is full**/
        int counter = 0;
        for (int col = 0; col < 7; col++) {
            if (board[0][col] != '-') {
                counter++;
            }
        }
        if (counter == 7) {
            cout << "Board is Full, It's a Draw!!!";
            break;
        }

        /**user doesn't undo a move, decides to continue playing.
         * After the next column is entered, alternates between players,
         * rinse and repeat**/

        if (currentUser == 'X') {
            currentUser = 'O';
        }
        else {
            currentUser = 'X';
        }
    }

    return 0;
}