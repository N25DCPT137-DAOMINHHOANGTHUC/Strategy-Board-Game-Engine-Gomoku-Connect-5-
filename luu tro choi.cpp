#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// 1. Cau truc luu toa do 1 nuoc di
struct Move {
    int row;        // Toa do dong
    int col;        // Toa do cot
    char symbol;    // Ky hieu quan co ('X' hoac 'O')
};

// 2. Lop quan ly thong tin nguoi choi
class Player {
private:
    string name;
    char symbol;

public:
    Player(string n, char s) : name(n), symbol(s) {}
    string getName() const { return name; }
    char getSymbol() const { return symbol; }
};

// 3. HAM LUU GAME THEO DUNG NHIEM VU
bool saveGame(const string& filename,
              const vector<vector<char>>& board,
              const vector<Move>& moveHistory,
              const Player& p1,
              const Player& p2,
              char currentTurn) 
{
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        cerr << "[-] Khong the mo file de luu!" << endl;
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
    cout << "[+] Da luu toan bo trang thai game vao file '" << filename << "' thanh cong!" << endl;
    return true;
}

// 4. Ham main dung de chay kiem tra 
int main() {
    const int SIZE = 10; // Kich thuoc ban co 10x10
    vector<vector<char>> board(SIZE, vector<char>(SIZE, '.')); // Ban co khoi tao
    vector<Move> history; // Danh sach toa do cac nuoc di

    Player p1("Nguoi Choi 1", 'X');
    Player p2("Nguoi Choi 2", 'O');
    char currentTurn = 'X'; // Khai bao luot di hien tai

    // Goi ham thuc hien luu file
    saveGame("save.txt", board, history, p1, p2, currentTurn);

    return 0;
}

