#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

class GomokuGame {
private:
    int size;                           
    vector<vector<char>> board;         
    string player1Name;
    char player1Symbol;
    string player2Name;
    char player2Symbol;
    int currentTurn;                    
    bool gameOver;

public:
    GomokuGame(int s = 15) : size(s), currentTurn(0), gameOver(false) {
        board.assign(size, vector<char>(size, '.'));
        player1Name = "Player 1";
        player1Symbol = 'X';
        player2Name = "Player 2";
        player2Symbol = 'O';
    }

    void displayBoard() const {
        cout << "\n      ";
        for (int c = 0; c < size; ++c) cout << setw(3) << c + 1;
        cout << "\n     " << string(size * 3 + 2, '-') << "\n";

        for (int r = 0; r < size; ++r) {
            cout << setw(3) << r + 1 << " |";
            for (int c = 0; c < size; ++c) {
                cout << setw(3) << board[r][c];
            }
            cout << "\n";
        }
        cout << "\n";
    }

    // --- HÀM LÝU GAME ---
    bool saveGame(const string& filename = "save.txt") const {
        ofstream outFile(filename);
        if (!outFile.is_open()) {
            cout << "[Loi] Khong the tao hoac mo file de luu: " << filename << "\n";
            return false;
        }

        outFile << size << "\n";
        outFile << player1Name << "\n";
        outFile << player1Symbol << "\n";
        outFile << player2Name << "\n";
        outFile << player2Symbol << "\n";
        outFile << currentTurn << "\n";

        for (int r = 0; r < size; ++r) {
            for (int c = 0; c < size; ++c) {
                outFile << board[r][c];
            }
            outFile << "\n";
        }

        outFile.close();
        cout << "[Thong bao] Da luu trang thai ban co vao file: " << filename << "\n";
        return true;
    }

    // --- HÀM T?I GAME ---
    bool loadGame(const string& filename = "save.txt") {
        ifstream inFile(filename);
        if (!inFile.is_open()) {
            cout << "[Loi] Khong tim thay hoac khong the mo file: " << filename << "\n";
            return false;
        }

        int newSize;
        if (!(inFile >> newSize) || newSize <= 0) return false;
        inFile.ignore(); 

        string p1Name; char p1Symbol;
        if (!getline(inFile, p1Name) || !(inFile >> p1Symbol)) return false;
        inFile.ignore();

        string p2Name; char p2Symbol;
        if (!getline(inFile, p2Name) || !(inFile >> p2Symbol)) return false;
        inFile.ignore();

        int turn;
        if (!(inFile >> turn)) return false;
        inFile.ignore();

        vector<vector<char>> newBoard(newSize, vector<char>(newSize, '.'));
        for (int r = 0; r < newSize; ++r) {
            string line;
            if (!getline(inFile, line) || (int)line.length() < newSize) return false;
            for (int c = 0; c < newSize; ++c) newBoard[r][c] = line[c];
        }
        inFile.close();

        // C?p nh?t d? li?u
        size = newSize;
        player1Name = p1Name; player1Symbol = p1Symbol;
        player2Name = p2Name; player2Symbol = p2Symbol;
        currentTurn = turn;
        board = newBoard;
        gameOver = false;

        cout << "[Thong bao] Tai van co thanh cong!\n";
        displayBoard();
        return true;
    }
};

int main() {
    GomokuGame game;
    
    // Lýu ván c? hi?n t?i ra file
    game.saveGame("save.txt");

    // Ð?c l?i ván c? t? file
    game.loadGame("save.txt");

    return 0;
}
