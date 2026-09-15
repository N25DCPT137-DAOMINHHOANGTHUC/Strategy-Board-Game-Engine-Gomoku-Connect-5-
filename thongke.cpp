#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

// ============================================================================
// 1. LOP QUAN LY THONG TIN VA THONG KE NGUOI CHOI
// ============================================================================
class Player {
private:
    string name;        // Ten nguoi choi
    char symbol;        // Ky hieu quan co ('X' hoac 'O')
    int wins;           // So tran thang
    int losses;         // So tran thua
    int draws;          // So tran hoa

public:
    Player(string n = "", char s = ' ', int w = 0, int l = 0, int d = 0)
        : name(n), symbol(s), wins(w), losses(l), draws(d) {}

    // Getters
    string getName() const { return name; }
    char getSymbol() const { return symbol; }
    int getWins() const { return wins; }
    int getLosses() const { return losses; }
    int getDraws() const { return draws; }
    int getTotalGames() const { return wins + losses + draws; }

    // Setters
    void setName(const string& n) { name = n; }
    void setSymbol(char s) { symbol = s; }
    void setWins(int w) { wins = w; }
    void setLosses(int l) { losses = l; }
    void setDraws(int d) { draws = d; }

    // Cap nhat ket qua tran dau
    void recordWin() { wins++; }
    void recordLoss() { losses++; }
    void recordDraw() { draws++; }

    // Tinh ti le thang (%) - tranh loi chia cho 0
    float getWinRate() const {
        int total = getTotalGames();
        if (total == 0) return 0.0f;
        return (static_cast<float>(wins) / total) * 100.0f;
    }

    // Tao ten file mac dinh tu ten nguoi choi (loai bo ky tu gay loi duong dan)
    string getDefaultFilename() const {
        string cleanName = name.empty() ? "player" : name;
        for (char &c : cleanName) {
            if (c == ' ' || c == '/' || c == '\\' || c == ':') c = '_';
        }
        return cleanName + "_stats.txt";
    }

    // Luu thong ke ra file (.txt)
    bool saveStats(const string& filename = "") const {
        string fname = filename.empty() ? getDefaultFilename() : filename;
        ofstream file(fname);
        if (!file.is_open()) {
            cerr << "[Loi] Khong the mo file '" << fname << "' de ghi du lieu!\n";
            return false;
        }

        file << name << "\n";
        file << wins << " " << losses << " " << draws << "\n";
        file.close();
        cout << "[He thong] Da luu thong ke cua '" << name << "' vao file '" << fname << "'.\n";
        return true;
    }

    // Doc thong ke tu file (.txt)
    bool loadStats(const string& filename = "") {
        string fname = filename.empty() ? getDefaultFilename() : filename;
        ifstream file(fname);
        if (!file.is_open()) {
            cout << "[He thong] Khong tim thay du lieu cu cho '" << name << "'. Khoi tao moi (0-0-0).\n";
            wins = 0;
            losses = 0;
            draws = 0;
            return false;
        }

        string savedName;
        if (getline(file, savedName)) {
            if (!savedName.empty()) {
                name = savedName;
            }
        }

        int w = 0, l = 0, d = 0;
        if (file >> w >> l >> d) {
            wins = w;
            losses = l;
            draws = d;
        } else if (file >> w >> l) {
            // Tuong thich neu doc file cu chi co wins va losses
            wins = w;
            losses = l;
            draws = 0;
        }
        file.close();
        cout << "[He thong] Da tai thanh cong thong ke cua '" << name << "'.\n";
        return true;
    }

    // Hien thi thong tin thong ke ca nhan
    void displayStats() const {
        cout << "\n========================================\n";
        cout << "         THONG KE NGUOI CHOI            \n";
        cout << "========================================\n";
        cout << " Ten nguoi choi : " << name << "\n";
        if (symbol != ' ') {
            cout << " Quan co        : " << symbol << "\n";
        }
        cout << " Tong so tran   : " << getTotalGames() << "\n";
        cout << " So tran thang  : " << wins << "\n";
        cout << " So tran thua   : " << losses << "\n";
        cout << " So tran hoa    : " << draws << "\n";
        cout << fixed << setprecision(1);
        cout << " Ti le thang    : " << getWinRate() << "%\n";
        cout << "========================================\n";
    }
};

// ============================================================================
// 2. HAM CAP NHAT KET QUA TRAN DAU TRONG GOMOKU
//    winner: 1 = Nguoi 1 thang, 2 = Nguoi 2 thang, 0 = Hoa
// ============================================================================
void capNhatKetQuaTranDau(Player& p1, Player& p2, int winner) {
    if (winner == 1) {
        p1.recordWin();
        p2.recordLoss();
        cout << "\n[Ket qua] >>> '" << p1.getName() << "' gianh CHIEN THANG truoc '" << p2.getName() << "'! <<<\n";
    } else if (winner == 2) {
        p2.recordWin();
        p1.recordLoss();
        cout << "\n[Ket qua] >>> '" << p2.getName() << "' gianh CHIEN THANG truoc '" << p1.getName() << "'! <<<\n";
    } else {
        p1.recordDraw();
        p2.recordDraw();
        cout << "\n[Ket qua] >>> Tran dau ket thuc voi ti so HOA! <<<\n";
    }

    // Tu dong luu thong ke ca nhan vao file
    p1.saveStats();
    p2.saveStats();
}

// ============================================================================
// 3. LOP QUAN LY BANG XEP HANG / THONG KE CHUNG (FILE: thongke_nguoichoi.txt)
// ============================================================================
class ThongKeManager {
private:
    string filename;
    vector<Player> danhSach;

public:
    ThongKeManager(string fname = "thongke_nguoichoi.txt") : filename(fname) {
        taiDuLieu();
    }

    // Tai du lieu toan bo nguoi choi tu file chung
    bool taiDuLieu() {
        danhSach.clear();
        ifstream file(filename);
        if (!file.is_open()) return false;

        string ten;
        int thang = 0, thua = 0, hoa = 0;
        while (file >> ten >> thang >> thua >> hoa) {
            Player p(ten, ' ', thang, thua, hoa);
            danhSach.push_back(p);
        }
        file.close();
        return true;
    }

    // Ghi toan bo danh sach nguoi choi vao file chung
    bool luuDuLieu() const {
        ofstream file(filename);
        if (!file.is_open()) {
            cerr << "[Loi] Khong the mo file '" << filename << "' de luu du lieu!\n";
            return false;
        }

        for (const auto& p : danhSach) {
            file << p.getName() << " " 
                 << p.getWins() << " " 
                 << p.getLosses() << " " 
                 << p.getDraws() << "\n";
        }
        file.close();
        cout << "[He thong] Da dong bo vao file danh sach '" << filename << "'.\n";
        return true;
    }

    // Tim hoac tao moi nguoi choi trong danh sach
    Player* timHoacTaoNguoiChoi(const string& ten) {
        for (auto& p : danhSach) {
            if (p.getName() == ten) return &p;
        }
        danhSach.push_back(Player(ten));
        return &danhSach.back();
    }

    // Ghi nhan ket qua tran dau vao co so du lieu chung
    void ghiNhanTranDau(const string& ten1, const string& ten2, int winner) {
        Player* p1 = timHoacTaoNguoiChoi(ten1);
        Player* p2 = timHoacTaoNguoiChoi(ten2);

        if (winner == 1) {
            p1->recordWin();
            p2->recordLoss();
        } else if (winner == 2) {
            p2->recordWin();
            p1->recordLoss();
        } else {
            p1->recordDraw();
            p2->recordDraw();
        }

        luuDuLieu();
    }

    // Hien thi bang xep hang (sap xep giam dan theo so tran thang va ti le thang)
    void hienThiBangXepHang() {
        if (danhSach.empty()) {
            cout << "\n[Thong bao] Chua co du lieu nguoi choi trong bang xep hang.\n";
            return;
        }

        sort(danhSach.begin(), danhSach.end(), [](const Player& a, const Player& b) {
            if (a.getWins() != b.getWins()) {
                return a.getWins() > b.getWins();
            }
            return a.getWinRate() > b.getWinRate();
        });

        cout << "\n=======================================================================\n";
        cout << "                    BANG XEP HANG NGUOI CHOI GOMOKU                   \n";
        cout << "=======================================================================\n";
        cout << left << setw(6)  << "Top" 
             << setw(18) << "Nguoi Choi" 
             << right << setw(10) << "Tong Tran" 
             << setw(10) << "Thang" 
             << setw(10) << "Thua" 
             << setw(8)  << "Hoa" 
             << setw(15) << "Ti Le Thang" << "\n";
        cout << string(71, '-') << "\n";

        int rank = 1;
        for (const auto& p : danhSach) {
            cout << left << setw(6)  << ("#" + to_string(rank++))
                 << setw(18) << p.getName()
                 << right << setw(10) << p.getTotalGames()
                 << setw(10) << p.getWins()
                 << setw(10) << p.getLosses()
                 << setw(8)  << p.getDraws()
                 << setw(14) << fixed << setprecision(1) << p.getWinRate() << "%\n";
        }
        cout << "=======================================================================\n\n";
    }
};

// ============================================================================
// 4. HAM MAIN CHAY THU FILE thongke.cpp
// ============================================================================
int main() {
    cout << "=======================================================\n";
    cout << "        CHUONG TRINH QUAN LY & LUU THONG KE (C++)      \n";
    cout << "=======================================================\n\n";

    // ---------------------------------------------------------
    // BUOC 1: TEST THONG KE VA LUU FILE CA NHAN (<Ten>_stats.txt)
    // ---------------------------------------------------------
    cout << "[TEST 1] KHOI TAO VA TAI THONG KE NGUOI CHOI CA NHAN:\n";
    Player p1("FakerVN", 'X');
    Player p2("Rookie", 'O');

    p1.loadStats();
    p2.loadStats();

    // Mo phong 3 tran dau
    cout << "\n[TEST 2] MO PHONG CAC TRAN DAU GOMOKU:\n";
    capNhatKetQuaTranDau(p1, p2, 1); // FakerVN thang
    capNhatKetQuaTranDau(p1, p2, 2); // Rookie thang
    capNhatKetQuaTranDau(p1, p2, 0); // Hoa

    // Hien thi thong ke chi tiet cua 2 nguoi
    p1.displayStats();
    p2.displayStats();

    // ---------------------------------------------------------
    // BUOC 2: TEST BANG XEP HANG CHUNG (thongke_nguoichoi.txt)
    // ---------------------------------------------------------
    cout << "\n[TEST 3] CAP NHAT VA XUAT BANG XEP HANG TONG HOP:\n";
    ThongKeManager manager("thongke_nguoichoi.txt");

    manager.ghiNhanTranDau("FakerVN", "Rookie", 1);
    manager.ghiNhanTranDau("FakerVN", "Rookie", 2);
    manager.ghiNhanTranDau("FakerVN", "Rookie", 0);
    manager.ghiNhanTranDau("TheShy", "FakerVN", 1);
    manager.ghiNhanTranDau("TheShy", "Rookie", 1);
    manager.ghiNhanTranDau("Chovy", "TheShy", 1);

    manager.hienThiBangXepHang();

    cout << "[*] Hoan tat chay thu nghiem! Du lieu da duoc ghi ra cac file .txt thanh cong.\n";
    return 0;
}
