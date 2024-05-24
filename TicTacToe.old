#include <iostream>
using namespace std;

char wincheck(char board[], char P) {
    if ((board[0] == P && board[1] == P && board[2] == P) ||
        (board[3] == P && board[4] == P && board[5] == P) ||
        (board[6] == P && board[7] == P && board[8] == P) ||
        (board[0] == P && board[3] == P && board[6] == P) ||
        (board[1] == P && board[4] == P && board[7] == P) ||
        (board[2] == P && board[5] == P && board[8] == P) ||
        (board[0] == P && board[4] == P && board[8] == P) ||
        (board[2] == P && board[4] == P && board[6] == P)) {
        return P;
    }
    else if (board[0] != ' ' && board[1] != ' ' && board[2] != ' ' &&
        board[3] != ' ' && board[4] != ' ' && board[5] != ' ' &&
        board[6] != ' ' && board[7] != ' ' && board[8] != ' ') {
        return 'T';
    }
    else {
        return ' ';
    }
}

void log(const char* message) {
    cout << message << endl;
}

bool move(int P, char board[]) {
    return P >= 1 && P <= 9 && board[P - 1] == ' ';
}

void displayBoard(char board[]) {
    cout << " " << board[0] << " | " << board[1] << " | " << board[2] << endl;
    cout << "-------------" << endl;
    cout << " " << board[3] << " | " << board[4] << " | " << board[5] << endl;
    cout << "-------------" << endl;
    cout << " " << board[6] << " | " << board[7] << " | " << board[8] << endl;
    cout << endl;
}

int main() {
    char board[9] = { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' };
    char XO;
    while (wincheck(board, 'X') == ' ' && wincheck(board, 'O') == ' ') {
        log("Select a position");
        int P;
        cin >> P;
        if (move(P, board)) {
            log("Enter X or O");
            cin >> XO;
            board[P - 1] = XO;
            cout << endl;
            displayBoard(board);
        }
        else {
            log("You must select another position");
            continue;
        }
    }
    if (wincheck(board, 'X') == 'X') {
        log("Player X has won");
    }
    else if (wincheck(board, 'O') == 'O') {
        log("Player O has won");
    }
    else if (wincheck(board, 'X') == 'T' || wincheck(board, 'O') == 'T') {
        log("The game is a tie");
    }
}





