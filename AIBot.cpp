#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int SIZE = 10; 
int countConsecutive(int board[SIZE][SIZE], int r, int c, int dx, int dy, int player) {
    int count = 0;
    int i = r + dx;
    int j = c + dy;
    
    while (i >= 0 && i < SIZE && j >= 0 && j < SIZE && board[i][j] == player) {
        count++;
        i += dx;
        j += dy;
    }
    return count;
}

bool isDangerousCell(int board[SIZE][SIZE], int r, int c) {
    int directions[4][2] = {{0, 1}, {1, 0}, {1, 1}, {1, -1}}; 
    for (int i = 0; i < 4; i++) {
        int dx = directions[i][0];
        int dy = directions[i][1];

        int count1 = countConsecutive(board, r, c, dx, dy, 1);
        int count2 = countConsecutive(board, r, c, -dx, -dy, 1);

        if (count1 + count2 >= 3) {
            return true;
        }
    }
    return false;
}

void makeBotMove(int board[SIZE][SIZE], int &outR, int &outC) {
    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE; c++) {
            if (board[r][c] == 0) { 
                if (isDangerousCell(board, r, c)) {
                    outR = r;
                    outC = c;
                    return; 
                }
            }
        }
    }

    int r, c;
    do {
        r = rand() % SIZE;
        c = rand() % SIZE;
    } while (board[r][c] != 0); 

    outR = r;
    outC = c;
}

int main() {
    srand(time(0));
    int board[SIZE][SIZE] = {0}; 
    int botR, botC;
    
    board[0][0] = 1;
    board[0][1] = 1;
    board[0][2] = 1;

    makeBotMove(board, botR, botC);

    cout << "=== THU NGHIEM BOT CARO ===" << endl;
    cout << "Nguoi choi dang co 3 quan X o hang 0!" << endl;
    cout << "Bot da thong minh danh chan tai hang: " << botR << ", cot: " << botC << endl;

    return 0;
}
