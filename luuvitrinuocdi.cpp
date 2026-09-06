#include <iostream>
#include <string>
#include <stack>
#include <conio.h>   
using namespace std;

const int SIZE = 15;

struct Player {
    string name;
    char symbol;
    Player(string n, char s) : name(n), symbol(s) {}
};

struct Move {
    int row, col;
    char symbol;
};

char board[SIZE][SIZE];
stack<Move> moveHistory; 

void initBoard() {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            board[i][j] = '.';
}

void printBoard() {
    cout << "   ";
    for (int j = 0; j < SIZE; j++) cout << j % 10 << " ";
    cout << endl;

    for (int i = 0; i < SIZE; i++) {
        cout << i << (i < 10 ? "  " : " ");
        for (int j = 0; j < SIZE; j++)
            cout << board[i][j] << " ";
        cout << endl;
    }
}

bool checkWin(int row, int col, char symbol) {
    int dx[] = {1, 0, 1, 1};
    int dy[] = {0, 1, 1, -1};

    for (int d = 0; d < 4; d++) {
        int count = 1;
        for (int step = 1; step < 5; step++) {
            int r = row + dx[d] * step;
            int c = col + dy[d] * step;
            if (r < 0 || r >= SIZE || c < 0 || c >= SIZE || board[r][c] != symbol) break;
            count++;
        }
        for (int step = 1; step < 5; step++) {
            int r = row - dx[d] * step;
            int c = col - dy[d] * step;
            if (r < 0 || r >= SIZE || c < 0 || c >= SIZE || board[r][c] != symbol) break;
            count++;
        }
        if (count >= 5) return true;
    }
    return false;
}

// Đánh một nước đi và lưu vào stack
void makeMove(int row, int col, char symbol) {
    board[row][col] = symbol;
    moveHistory.push({row, col, symbol});
}

// Xóa nước đi gần nhất
void Undo(int &Luotchoi) {
    if (moveHistory.empty()) {
        cout << "Khong co nuoc di nao de undo!" << endl;
        return;
    }

    Move lastMove = moveHistory.top();
    moveHistory.pop();

    board[lastMove.row][lastMove.col] = '.'; 
    Luotchoi = (Luotchoi == 1) ? 2 : 1;       

    cout << "Da undo nuoc di tai (" << lastMove.row << ", " << lastMove.col << ")" << endl;
}

int main() {
    Player player1("Nguoi choi 1", 'X');
    Player player2("Nguoi choi 2", 'O');

    initBoard();

    int Luotchoi = 1;
    bool gameOver = false;

    while (!gameOver) {
        printBoard();

        Player& current = (Luotchoi == 1) ? player1 : player2;
        cout << "Luot cua: " << current.name << " (" << current.symbol << ")" << endl;
        cout << "Nhap hang cot (vd: 7 7) hoac go 'u' de Undo, 'q' de thoat: ";

        string input;
        cin >> input;

        if (input == "u" || input == "U") {
            Undo(Luotchoi);
            continue;
        }

        if (input == "q" || input == "Q") {
            gameOver = true;
            break;
        }

        int row = stoi(input);
        int col;
        cin >> col;

        if (row < 0 || row >= SIZE || col < 0 || col >= SIZE || board[row][col] != '.') {
            cout << "Vi tri khong hop le, thu lai!" << endl;
            continue;
        }

        makeMove(row, col, current.symbol);

        if (checkWin(row, col, current.symbol)) {
            printBoard();
            cout << current.name << " thang!" << endl;
            gameOver = true;
        } else {
            Luotchoi = (Luotchoi == 1) ? 2 : 1;
        }
    }

    return 0;
}