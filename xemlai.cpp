#ifndef REPLAY_H
#define REPLAY_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <thread>
#include <chrono>

// 1. Cấu trúc một nước đi trong lịch sử
#ifndef MOVE_STRUCT_DEFINED
#define MOVE_STRUCT_DEFINED
struct Move {
    int row;        // Tọa độ hàng (0-indexed)
    int col;        // Tọa độ cột (0-indexed)
    char symbol;    // Ký hiệu quân cờ ('X' hoặc 'O')
};
#endif

// 2. Cấu trúc lưu toàn bộ dữ liệu trận đấu đọc từ file save
struct ReplayMatchData {
    int rows = 0;
    int cols = 0;
    std::string player1Name;
    char player1Symbol = 'X';
    std::string player2Name;
    char player2Symbol = 'O';
    char lastTurn = 'X';
    std::vector<Move> moveHistory;
};

// 3. Hàm đọc danh sách nước đi từ file save
inline bool loadMatchForReplay(const std::string& filename, ReplayMatchData& data) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        std::cerr << "[!] Khong the mo file save: " << filename << std::endl;
        return false;
    }

    if (!(inFile >> data.rows >> data.cols)) return false;
    if (!(inFile >> data.player1Name >> data.player1Symbol)) return false;
    if (!(inFile >> data.player2Name >> data.player2Symbol)) return false;
    if (!(inFile >> data.lastTurn)) return false;

    int numMoves = 0;
    if (!(inFile >> numMoves) || numMoves < 0) return false;

    data.moveHistory.clear();
    for (int i = 0; i < numMoves; ++i) {
        Move m;
        if (!(inFile >> m.row >> m.col >> m.symbol)) return false;
        data.moveHistory.push_back(m);
    }

    inFile.close();
    return true;
}

// 4. Hàm hiển thị bàn cờ (nổi bật nước vừa đánh dạng [X] hoặc [O])
inline void displayReplayBoard(const std::vector<std::vector<char>>& board, int lastRow = -1, int lastCol = -1) {
    int rows = board.size();
    int cols = (rows > 0) ? board[0].size() : 0;

    std::cout << "\n      ";
    for (int c = 0; c < cols; ++c) std::cout << std::setw(3) << c + 1;
    std::cout << "\n     " << std::string(cols * 3 + 2, '-') << "\n";

    for (int r = 0; r < rows; ++r) {
        std::cout << std::setw(3) << r + 1 << " |";
        for (int c = 0; c < cols; ++c) {
            if (r == lastRow && c == lastCol) {
                std::cout << "[" << board[r][c] << "]";
            } else {
                std::cout << std::setw(3) << board[r][c];
            }
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

// 5. Hàm thực thi luồng Replay
inline void startReplay(const std::string& filename) {
    ReplayMatchData matchData;
    if (!loadMatchForReplay(filename, matchData)) {
        std::cout << "[-] Khong the bat dau Replay do loi doc file.\n";
        return;
    }

    int totalMoves = matchData.moveHistory.size();
    std::cout << "\n=========================================\n";
    std::cout << "        CHE DO XEM LAI (REPLAY)          \n";
    std::cout << "=========================================\n";
    std::cout << "Nguoi choi 1    : " << matchData.player1Name << " ('" << matchData.player1Symbol << "')\n";
    std::cout << "Nguoi choi 2    : " << matchData.player2Name << " ('" << matchData.player2Symbol << "')\n";
    std::cout << "Tong so nuoc di : " << totalMoves << "\n";
    std::cout << "=========================================\n";
    std::cout << "PHIM DIEU KHIEN:\n";
    std::cout << "  [Enter] hoac [N] : Nuoc tiep theo\n";
    std::cout << "  [P]              : Lui lai 1 nuoc\n";
    std::cout << "  [A]              : Tu dong phat (Auto Play)\n";
    std::cout << "  [Q]              : Thoat Replay\n";
    std::cout << "=========================================\n\n";

    std::vector<std::vector<char>> board(matchData.rows, std::vector<char>(matchData.cols, '.'));
    int currentStep = 0;
    displayReplayBoard(board);

    std::string cmd;
    bool autoMode = false;

    while (true) {
        if (!autoMode) {
            std::cout << "[Replay: " << currentStep << "/" << totalMoves << "] Nhap lenh (Enter=Tiep, P=Lui, A=Auto, Q=Thoat): ";
            std::getline(std::cin, cmd);
            if (cmd.empty()) cmd = "n";
        } else {
            cmd = "n";
            std::this_thread::sleep_for(std::chrono::milliseconds(700));
        }

        char choice = std::tolower(cmd[0]);

        if (choice == 'q') {
            std::cout << "[-] Da thoat che do Replay.\n";
            break;
        } 
        else if (choice == 'a') {
            autoMode = true;
            std::cout << "[>] Bat che do tu dong phat...\n";
        }
        else if (choice == 'p') {
            if (currentStep > 0) {
                currentStep--;
                Move prevMove = matchData.moveHistory[currentStep];
                board[prevMove.row][prevMove.col] = '.'; // Xóa quân cờ
                
                int lastRow = -1, lastCol = -1;
                if (currentStep > 0) {
                    lastRow = matchData.moveHistory[currentStep - 1].row;
                    lastCol = matchData.moveHistory[currentStep - 1].col;
                }
                displayReplayBoard(board, lastRow, lastCol);
            } else {
                std::cout << "[!] Da o trang thai ban dau, khong the lui!\n";
            }
        } 
        else if (choice == 'n') {
            if (currentStep < totalMoves) {
                Move curMove = matchData.moveHistory[currentStep];
                board[curMove.row][curMove.col] = curMove.symbol;
                currentStep++;

                std::string pName = (curMove.symbol == matchData.player1Symbol) 
                                    ? matchData.player1Name : matchData.player2Name;

                std::cout << "\n>> Nuoc " << currentStep << "/" << totalMoves << ": " 
                          << pName << " ('" << curMove.symbol << "') danh tai (" 
                          << curMove.row + 1 << ", " << curMove.col + 1 << ")\n";

                displayReplayBoard(board, curMove.row, curMove.col);

                if (currentStep == totalMoves) {
                    std::cout << "[*] DA XEM LAI HET TAT CA CAC NUOC DI!\n";
                    autoMode = false;
                }
            } else {
                std::cout << "[*] Da o nuoc di cuoi cung!\n";
                autoMode = false;
            }
        }
    }
}


