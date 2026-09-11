#ifndef BOT_H
#define BOT_H

#include <vector>

// Kích thước bàn cờ
const int BOARD_SIZE = 15;

// Cấu trúc tọa độ nước đi
struct Move {
    int row;
    int col;
};

// Khai báo các hàm từ file Bot.cpp
Move getRandomMove(const std::vector<std::vector<int>>& board);
void printBoard(const std::vector<std::vector<int>>& board);

#endif // BOT_H