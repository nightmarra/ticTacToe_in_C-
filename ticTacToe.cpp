#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <cctype>

#define NEW_LINES for(int i = 0; i < 5; ++i) std::cout << '\n';
#define BORDERS_1 "- - - - - | - - - - - | - - - - -"
#define BORDERS_2 "          |           |          "

using std::cout, std::cin;

char playLines[3][35] = {{"          |           |          "},
                         {"          |           |          "},
                         {"          |           |          "}};
int gameState[3][3] = {{0,0,0},{0,0,0},{0,0,0}};
const int validInput[3] = {1,2,3};

/****************************************************************/

void printBoard() {
    cout << '\n';
    cout << BORDERS_2 << "\n\n";
    cout << playLines[0] << "\n\n" << BORDERS_1 << "\n\n";
    cout << playLines[1] << "\n\n" << BORDERS_1 << "\n\n";
    cout << playLines[2] << "\n\n";
    cout << BORDERS_2 << "\n\n";
}

bool rowValidator(int x) {
    if(gameState[x][0] != 0 && gameState[x][1] != 0 && gameState[x][2] != 0) {
        return true;
    } return false;
}

bool validityCheck(float x, float y) {
    int r = static_cast<int>(x);
    int c = static_cast<int>(y);
    if(gameState[r-1][c-1] == 0) {
        return true;
    } else {
        return false;
    }
}

void myMove() {
    float row, col; 

    cout << "\nPick a row (1-3): ";
    cin >> row; // the next line is why I'm the greatest programmer of all time
    while(!cin || rowValidator(row-1) || std::find(validInput, validInput + 3, row) == validInput + 3) {
        cout << "\nInvalid input.\n";
        cin.clear();
        cin.ignore(2000, '\n');
        cout << "Pick a row (1-3): ";
        cin >> row;
    }

    cout << "Pick a column (1-3): ";
    cin >> col;
    while(!cin || !validityCheck(row, col) || std::find(validInput, validInput + 3, col) == validInput + 3) {
        cout << "\nInvalid input.\n";
        cin.clear();
        cin.ignore(2000, '\n');
        cout << "Pick a column (1-3): ";
        cin >> col;
    }

    int r = static_cast<int>(row);
    int c = static_cast<int>(col);
    gameState[r-1][c-1] += 1;
    playLines[r-1][12*(c-1)+4] = 'X';
    
}

void computerMove() {
    while(1) {
        std::srand(std::time(nullptr));
        int x = std::rand() % 3;
        int y = std::rand() % 3;
        if(gameState[x][y] == 0) {
            gameState[x][y] += 2;
            playLines[x][12*y+4] = 'O';
            break;
        }
    }
}

int gameEnd() {
    // rows
    for(int i = 0; i <= 2; ++i) {
        if(gameState[i][0] == gameState[i][1] && gameState[i][0] == gameState[i][2]) {
            if(gameState[i][0] == 1) {
                return 1;
            } else if(gameState[i][0] == 2) {
                return 2;
            }
        }
    }
    // columns
    for(int i = 0; i <= 2; ++i) {
        if(gameState[0][i] == gameState[1][i] && gameState[0][i] == gameState[2][i]) {
            if(gameState[0][i] == 1) {
                return 1;
            } else if(gameState[0][i] == 2) {
                return 2;
            }
        }
    }
    // diag 1
    if(gameState[0][0] == gameState[1][1] && gameState[0][0] == gameState[2][2]) {
        if(gameState[0][0] == 1) {
            return 1;
        } else if(gameState[0][0] == 2) {
            return 2;
        }
    }
    // diag 2
    if(gameState[0][2] == gameState[1][1] && gameState[0][2] == gameState[2][0]) {
        if(gameState[0][2] == 1) {
            return 1;
        } else if(gameState[0][2] == 2) {
            return 2;
        }
    }
    return 0;
}

bool winner() {
    if(gameEnd() == 1) {
        printBoard();
        cout << "YOU WIN!!!";
        return true;
    } else if(gameEnd() == 2) {
        printBoard();
        cout << "Computer wins. :/";
        return true;
    }
    return false;
}

void game() {
    int turnCount = 0;
    char answer;

    NEW_LINES
    cout << "HELLO AND WELCOME TO TIC-TAC-TOE!!";

    do {
        NEW_LINES
        printBoard();
        myMove();
        turnCount++;
        if(winner() == true || turnCount == 9) {
            break;
        }
        computerMove();
        turnCount++;
        if(winner() == true || turnCount == 9) {
            break;
        }
    } while(turnCount < 9);

    if(gameEnd() != 1 && gameEnd() != 2) {
        cout << "\nTie.";
    }

    cout << "\nType 'y' if you want to play again, or anything else if you want to quit: ";
    cin >> answer;
    answer = toupper(answer);
    if(answer == 'Y') {
        for(int i = 0; i < 3; ++i) {
            for(int j = 0; j < 3; ++j) {
                gameState[i][j] = 0;
            }
        }
        for(int k = 0; k < 3; ++k) {
            playLines[k][4] = ' ';
            playLines[k][16] = ' ';
            playLines[k][28] = ' ';
        }
        game();
    } else {
        cout << "\n\nThank you for playing :)\n\n\n";
    }
}

int main() {
    game();
    return 0;
}