
#include <iostream>
using namespace std;

const int SIZE = 10;
char board[SIZE][SIZE];

void initBoard() {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            board[i][j] = '.';
}

void printBoard() {
    cout << "   ";
    for (int j = 0; j < SIZE; j++) cout << j << " ";
    cout << endl;

    for (int i = 0; i < SIZE; i++) {
        cout << i << (i < 10 ? "  " : " ");
        for (int j = 0; j < SIZE; j++)
            cout << board[i][j] << " ";
        cout << endl;
    }
}


bool isValidMove(int row, int col) {
   
    if (row < 0 || row >= SIZE || col < 0 || col >= SIZE) {
        cout << "Nuoc di khong hop le: vi tri (" << row << ", " << col 
             << ") nam ngoai ban co (0-" << SIZE - 1 << ")." << endl;
        return false;
    }

    
    if (board[row][col] != '.') {
        cout << "Nuoc di khong hop le: o (" << row << ", " << col 
             << ") da co quan '" << board[row][col] << "'." << endl;
        return false;
    }

    return true;
}

int main() {
    initBoard();

    int row, col;
    char symbol = 'X';

    while (true) {
        printBoard();
        cout << "Nhap hang va cot (vd: 3 4), hoac -1 -1 de thoat: ";
        cin >> row >> col;

        if (row == -1 && col == -1) break;

        if (!isValidMove(row, col)) {
            continue; 
        }

        board[row][col] = symbol;
        symbol = (symbol == 'X') ? 'O' : 'X'; 
    }

    return 0;
}
