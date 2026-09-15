#ifndef THONGKE_H
#define THONGKE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "khaibaohainguoichoi.h"

// ============================================================================
// 1. HAM CAP NHAT KET QUA TRAN DAU GIUA 2 NGUOI CHOI TRONG GOMOKU
//    winner: 1 = Nguoi 1 thang, 2 = Nguoi 2 thang, 0 = Hoa
// ============================================================================
inline void capNhatKetQuaTranDau(Player& p1, Player& p2, int winner) {
    if (winner == 1) {
        p1.recordWin();
        p2.recordLoss();
        std::cout << "\n[Ket qua] >>> '" << p1.getName() << "' gianh CHIEN THANG truoc '" << p2.getName() << "'! <<<\n";
    } else if (winner == 2) {
        p2.recordWin();
        p1.recordLoss();
        std::cout << "\n[Ket qua] >>> '" << p2.getName() << "' gianh CHIEN THANG truoc '" << p1.getName() << "'! <<<\n";
    } else {
        p1.recordDraw();
        p2.recordDraw();
        std::cout << "\n[Ket qua] >>> Tran dau ket thuc voi ti so HOA! <<<\n";
    }

    // Tu dong luu thong ke cua ca 2 nguoi choi ra file rieng
    p1.saveStats();
    p2.saveStats();
}

// ============================================================================
// 2. LOP QUAN LY BANG XEP HANG / THONG KE TOAN BO NGUOI CHOI TRONG FILE CHUNG
//    File luu dinh dang: <Ten> <Thang> <Thua> <Hoa>
// ============================================================================
class ThongKeManager {
private:
    std::string filename;
    std::vector<Player> danhSach;

public:
    ThongKeManager(std::string fname = "thongke_nguoichoi.txt") : filename(fname) {
        taiDuLieu();
    }

    // Doc toan bo danh sach thong ke tu file chung
    bool taiDuLieu() {
        danhSach.clear();
        std::ifstream file(filename);
        if (!file.is_open()) {
            return false;
        }

        std::string ten;
        int thang = 0, thua = 0, hoa = 0;
        while (file >> ten >> thang >> thua >> hoa) {
            Player p(ten, ' ', thang, thua, hoa);
            danhSach.push_back(p);
        }
        file.close();
        return true;
    }

    // Ghi toan bo danh sach thong ke vao file chung
    bool luuDuLieu() const {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "[Loi] Khong the mo file '" << filename << "' de luu bang xep hang!\n";
            return false;
        }

        for (const auto& p : danhSach) {
            file << p.getName() << " " 
                 << p.getWins() << " " 
                 << p.getLosses() << " " 
                 << p.getDraws() << "\n";
        }
        file.close();
        std::cout << "[He thong] Da cap nhat va luu danh sach thong ke vao '" << filename << "'.\n";
        return true;
    }

    // Tim hoac tao moi nguoi choi trong danh sach
    Player* timHoacTaoNguoiChoi(const std::string& ten) {
        for (auto& p : danhSach) {
            if (p.getName() == ten) return &p;
        }
        danhSach.push_back(Player(ten));
        return &danhSach.back();
    }

    // Ghi nhan ket qua tran dau vao he thong chung
    void ghiNhanTranDau(const std::string& ten1, const std::string& ten2, int winner) {
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

    // Hien thi bang xep hang (sap xep theo so tran thang giam dan)
    void hienThiBangXepHang() {
        if (danhSach.empty()) {
            std::cout << "[Thong bao] Chua co du lieu nguoi choi nao trong bang xep hang.\n";
            return;
        }

        // Sap xep: Uu tien so tran thang, neu bang nhau uu tien ti le thang
        std::sort(danhSach.begin(), danhSach.end(), [](const Player& a, const Player& b) {
            if (a.getWins() != b.getWins()) {
                return a.getWins() > b.getWins();
            }
            return a.getWinRate() > b.getWinRate();
        });

        std::cout << "\n=======================================================================\n";
        std::cout << "                    BANG XEP HANG NGUOI CHOI GOMOKU                   \n";
        std::cout << "=======================================================================\n";
        std::cout << std::left << std::setw(6)  << "Top" 
                  << std::setw(18) << "Nguoi Choi" 
                  << std::right << std::setw(10) << "Tong Tran" 
                  << std::setw(10) << "Thang" 
                  << std::setw(10) << "Thua" 
                  << std::setw(8)  << "Hoa" 
                  << std::setw(15) << "Ti Le Thang" << "\n";
        std::cout << std::string(71, '-') << "\n";

        int rank = 1;
        for (const auto& p : danhSach) {
            std::cout << std::left << std::setw(6)  << ("#" + std::to_string(rank++))
                      << std::setw(18) << p.getName()
                      << std::right << std::setw(10) << p.getTotalGames()
                      << std::setw(10) << p.getWins()
                      << std::setw(10) << p.getLosses()
                      << std::setw(8)  << p.getDraws()
                      << std::setw(14) << std::fixed << std::setprecision(1) << p.getWinRate() << "%\n";
        }
        std::cout << "=======================================================================\n\n";
    }

    const std::vector<Player>& getDanhSach() const { return danhSach; }
};

#endif // THONGKE_H
