#include <crow.h>
#include <iostream>

using namespace std;

// Function to make a move on the Tic Tac Toe board
void makeMove(char board[], char& currentPlayer, int position) {
    if (position >= 1 && position <= 9 && board[position - 1] == ' ') {
        board[position - 1] = currentPlayer;
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }
}

// Function to check if a player has won based on a line of positions
bool checkLine(char board[], int pos1, int pos2, int pos3) {
    return (board[pos1] != ' ') && (board[pos1] == board[pos2]) && (board[pos2] == board[pos3]);
}

// Function to check for a win on the Tic Tac Toe board
char checkWin(const char board[]) {
    const int WINNING_COMBINATIONS[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8},  // Rows
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8},  // Columns
        {0, 4, 8}, {2, 4, 6}              // Diagonals
    };

    for (auto& combo : WINNING_COMBINATIONS) {
        if (checkLine(board, combo[0], combo[1], combo[2])) {
            return board[combo[0]];
        }
    }

    for (int i = 0; i < 9; ++i) {
        if (board[i] == ' ') {
            return ' '; // Game is still ongoing
        }
    }

    return 'T'; // Tie
}

// Function to display the current Tic Tac Toe board
string displayBoard(const char board[]) {
    string result = " " + string(1, board[0]) + " | " + string(1, board[1]) + " | " + string(1, board[2]) + "\n";
    result += "---------\n";
    result += " " + string(1, board[3]) + " | " + string(1, board[4]) + " | " + string(1, board[5]) + "\n";
    result += "---------\n";
    result += " " + string(1, board[6]) + " | " + string(1, board[7]) + " | " + string(1, board[8]) + "\n";

    return result;
}

void testMakeMoveAndWin() {
    char board[BOARD_SIZE] = { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' };
    char currentPlayer = 'X';

    // Horizontal win for X
    makeMove(board, currentPlayer, 1);
    makeMove(board, currentPlayer, 4);
    makeMove(board, currentPlayer, 2);
    makeMove(board, currentPlayer, 5);
    makeMove(board, currentPlayer, 3);
    assert(checkWin(board, 'X') == 'X');

    // Vertical win for O
    currentPlayer = 'X'; // Reset currentPlayer
    makeMove(board, currentPlayer, 1);
    makeMove(board, currentPlayer, 2);
    makeMove(board, currentPlayer, 4);
    currentPlayer = 'O'; // Switch to O
    makeMove(board, currentPlayer, 3);
    makeMove(board, currentPlayer, 7);
    makeMove(board, currentPlayer, 5);
    assert(checkWin(board, 'O') == 'O');

    // Diagonal win for X
    currentPlayer = 'X'; // Reset currentPlayer
    makeMove(board, currentPlayer, 1);
    makeMove(board, currentPlayer, 2);
    makeMove(board, currentPlayer, 5);
    currentPlayer = 'O'; // Switch to O
    makeMove(board, currentPlayer, 4);
    makeMove(board, currentPlayer, 9);
    makeMove(board, currentPlayer, 7);
    assert(checkWin(board, 'X') == 'X');

    // Tie game
    currentPlayer = 'X'; // Reset currentPlayer
    makeMove(board, currentPlayer, 1);
    makeMove(board, currentPlayer, 3);
    makeMove(board, currentPlayer, 2);
    currentPlayer = 'O'; // Switch to O
    makeMove(board, currentPlayer, 4);
    makeMove(board, currentPlayer, 6);
    makeMove(board, currentPlayer, 5);
    currentPlayer = 'X'; // Switch back to X
    makeMove(board, currentPlayer, 7);
    makeMove(board, currentPlayer, 9);
    currentPlayer = 'O'; // Switch to O
    makeMove(board, currentPlayer, 8);
    assert(checkWin(board, 'X') == 'T');
    assert(checkWin(board, 'O') == 'T');

    logMessage("testMakeMoveAndWin passed!");
}

int main() {
    //testMakeMoveAndWin(); // -> Enable for testing.
    
    crow::SimpleApp app;

    char board[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
    char currentPlayer = 'X';

    // Route to make a move
    CROW_ROUTE(app, "/makeMove/<int>")
    .methods("POST"_method)
    ([&board, &currentPlayer](const crow::request& req, int position) {
        makeMove(board, currentPlayer, position);
        return crow::response{displayBoard(board)};
    });

    // Route to check for a win
    CROW_ROUTE(app, "/checkWin")
    .methods("GET"_method)
    ([&board]() {
        char result = checkWin(board);
        string message;
        if (result == 'X' || result == 'O') {
            message = "Player " + string(1, result) + " wins!";
        } else if (result == 'T') {
            message = "It's a tie!";
        } else {
            message = "Game is still ongoing.";
        }
        return crow::response{message};
    });

    // Route to display the current board state
    CROW_ROUTE(app, "/displayBoard")
    .methods("GET"_method)
    ([&board]() {
        return crow::response{displayBoard(board)};
    });

    app.port(8080).multithreaded().run();
}