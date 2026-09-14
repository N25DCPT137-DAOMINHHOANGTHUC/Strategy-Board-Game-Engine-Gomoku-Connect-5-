#ifndef LUU_H
#define LUU_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

class GomokuGame {
private:
    int size;                           
    std::vector<std::vector<char>> board;         
    std::string player1Name;
    char player1Symbol;
    std::string player2Name;
    char player2Symbol;
    int currentTurn;                    
    bool gameOver;

public:
    GomokuGame(int s = 15) : size(s), currentTurn(0), gameOver(false) {
        board.assign(size, std::vector<char>(size, '.'));
        player1Name = "Player 1";
        player1Symbol = 'X';
        player2Name = "Player 2";
        player2Symbol = 'O';
    }

    void displayBoard() const {
        std::cout << "\n      ";
        for (int c = 0; c < size; ++c) std::cout << std::setw(3) << c + 1;
        std::cout << "\n     " << std::string(size * 3 + 2, '-') << "\n";

        for (int r = 0; r < size; ++r) {
            std::cout << std::setw(3) << r + 1 << " |";
            for (int c = 0; c < size; ++c) {
                std::cout << std::setw(3) << board[r][c];
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }

    // --- HAM LUU GAME ---
    bool saveGame(const std::string& filename = "save.txt") const {
        std::ofstream outFile(filename);
        if (!outFile.is_open()) {
            std::cout << "[Loi] Khong the tao hoac mo file de luu: " << filename << "\n";
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
        std::cout << "[Thong bao] Da luu trang thai ban co vao file: " << filename << "\n";
        return true;
    }

    // --- HAM TAI GAME ---
    bool loadGame(const std::string& filename = "save.txt") {
        std::ifstream inFile(filename);
        if (!inFile.is_open()) {
            std::cout << "[Loi] Khong tim thay hoac khong the mo file: " << filename << "\n";
            return false;
        }

        int newSize;
        if (!(inFile >> newSize) || newSize <= 0) return false;
        inFile.ignore(); 

        std::string p1Name; char p1Symbol;
        if (!getline(inFile, p1Name) || !(inFile >> p1Symbol)) return false;
        inFile.ignore();

        std::string p2Name; char p2Symbol;
        if (!getline(inFile, p2Name) || !(inFile >> p2Symbol)) return false;
        inFile.ignore();

        int turn;
        if (!(inFile >> turn)) return false;
        inFile.ignore();

        std::vector<std::vector<char>> newBoard(newSize, std::vector<char>(newSize, '.'));
        for (int r = 0; r < newSize; ++r) {
            std::string line;
            if (!getline(inFile, line) || (int)line.length() < newSize) return false;
            for (int c = 0; c < newSize; ++c) newBoard[r][c] = line[c];
        }
        inFile.close();

        // Cap nhat du lieu
        size = newSize;
        player1Name = p1Name; player1Symbol = p1Symbol;
        player2Name = p2Name; player2Symbol = p2Symbol;
        currentTurn = turn;
        board = newBoard;
        gameOver = false;

        std::cout << "[Thong bao] Tai van co thanh cong!\n";
        displayBoard();
        return true;
    }

    // Getters / Setters ho tro them
    int getSize() const { return size; }
    int getCurrentTurn() const { return currentTurn; }
    bool isGameOver() const { return gameOver; }
    const std::vector<std::vector<char>>& getBoard() const { return board; }
};

#endif // LUU_H
