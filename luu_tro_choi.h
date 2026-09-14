#ifndef LUU_TRO_CHOI_H
#define LUU_TRO_CHOI_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "khaibaohainguoichoi.h"

// 1. Cau truc luu toa do 1 nuoc di
struct Move {
    int row;        // Toa do dong
    int col;        // Toa do cot
    char symbol;    // Ky hieu quan co ('X' hoac 'O')
};

// 2. Ham luu game vao file theo trang thai ban co, lich su nuoc di va nguoi choi
inline bool saveGame(const std::string& filename,
                     const std::vector<std::vector<char>>& board,
                     const std::vector<Move>& moveHistory,
                     const Player& p1,
                     const Player& p2,
                     char currentTurn) 
{
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "[-] Khong the mo file de luu!" << std::endl;
        return false;
    }

    int rows = board.size();
    int cols = (rows > 0) ? board[0].size() : 0;

    // Ghi thong tin kich thuoc ban co va nguoi choi
    outFile << rows << " " << cols << "\n";
    outFile << p1.getName() << " " << p1.getSymbol() << "\n";
    outFile << p2.getName() << " " << p2.getSymbol() << "\n";
    outFile << currentTurn << "\n";

    // Ghi danh sach toa do nuoc di
    outFile << moveHistory.size() << "\n";
    for (size_t i = 0; i < moveHistory.size(); ++i) {
        outFile << moveHistory[i].row << " " 
                << moveHistory[i].col << " " 
                << moveHistory[i].symbol << "\n";
    }

    // Ghi ma tran ban co
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            outFile << board[i][j];
            if (j + 1 < cols) outFile << " ";
        }
        outFile << "\n";
    }

    outFile.close();
    std::cout << "[+] Da luu toan bo trang thai game vao file '" << filename << "' thanh cong!" << std::endl;
    return true;
}

#endif // LUU_TRO_CHOI_H
