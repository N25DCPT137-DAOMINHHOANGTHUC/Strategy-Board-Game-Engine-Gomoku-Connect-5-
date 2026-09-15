#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

const int BOARD_SIZE = 15;

struct Move {
    int row;
    int col;
};

/**
 * AI ch?n ng?u nhiên m?t ô tr?ng trên bàn c?.
 */
Move getRandomMove(const vector<vector<int> >& board) {
    vector<Move> emptyCells;

    // 1. Duy?t toàn b? bàn c? ð? thu th?p t?t c? các ô tr?ng
    for (int r = 0; r < BOARD_SIZE; ++r) {
        for (int c = 0; c < BOARD_SIZE; ++c) {
            if (board[r][c] == 0) {
                Move m;
                m.row = r;
                m.col = c;
                emptyCells.push_back(m);
            }
        }
    }

    // 2. N?u không c?n ô tr?ng nào
    if (emptyCells.empty()) {
        Move noMove;
        noMove.row = -1;
        noMove.col = -1;
        return noMove;
    }

    // 3. Ch?n ng?u nhiên 1 ô trong danh sách các ô tr?ng
    int randomIndex = rand() % emptyCells.size();
    return emptyCells[randomIndex];
}

void printBoard(const vector<vector<int> >& board) {
    cout << "   ";
    for (int c = 0; c < BOARD_SIZE; ++c) {
        if (c < 10) cout << c << "  ";
        else cout << c << " ";
    }
    cout << "\n";

    for (int r = 0; r < BOARD_SIZE; ++r) {
        if (r < 10) cout << r << "  ";
        else cout << r << " ";
        for (int c = 0; c < BOARD_SIZE; ++c) {
            if (board[r][c] == 0) cout << ".  ";
            else if (board[r][c] == 1) cout << "X  ";
            else if (board[r][c] == 2) cout << "O  ";
        }
        cout << "\n";
    }
}

int main() {
    srand(time(NULL));

    // Kh?i t?o bàn c? 15x15
    vector<vector<int> > board(BOARD_SIZE, vector<int>(BOARD_SIZE, 0));

    board[7][7] = 1;
    board[7][8] = 2;

    cout << "--- BAN CO BAN DAU ---" << endl;
    printBoard(board);

    cout << "\n--- TEST BOT CHON NUOC DI NGAU NHIEN ---" << endl;
    for (int i = 1; i <= 3; ++i) {
        Move botMove = getRandomMove(board);
        if (botMove.row != -1) {
            cout << "Lan " << i << " -> Bot chon o: Row " << botMove.row << ", Col " << botMove.col << endl;
            board[botMove.row][botMove.col] = 2;
        } else {
            cout << "Ban co da day!" << endl;
        }
    }

    cout << "\n--- BAN CO SAU KHI BOT DANH ---" << endl;
    printBoard(board);

    return 0;
}
