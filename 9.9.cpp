#include <iostream>
#include <fstream>
#include <string>
class Player {
private:
    std::string username;
    int wins;
    int losses;
public:
    // Khởi tạo người chơi mới
    Player(std::string name) : username(name), wins(0), losses(0) {}
    // Cập nhật kết quả
    void recordWin() { wins++; }
    void recordLoss() { losses++; }  
    // Tính tỉ lệ thắng (tránh lỗi chia cho 0)
    float getWinRate() const {
        int totalGames = wins + losses;
        if (totalGames == 0) return 0.0f;
        return (static_cast<float>(wins) / totalGames) * 100.0f;
    }
    // Ghi dữ liệu ra file (.txt)
    void saveStats() const {
        std::string filename = username + "_stats.txt";
        std::ofstream file(filename);
        if (file.is_open()) {
            file << wins << "\n" << losses << "\n";
  file.close();
            std::cout << "[Hệ thống] Đã lưu dữ liệu cho " << username << ".\n";
        } else {
            std::cerr << "[Lỗi] Không thể mở file để ghi dữ liệu!\n";
        }
    }
    // Đọc dữ liệu từ file khi đăng nhập
    void loadStats() {
        std::string filename = username + "_stats.txt";
        std::ifstream file(filename);
      
        if (file.is_open()) {
            file >> wins >> losses;
            file.close();
            std::cout << "[Hệ thống] Đã tải dữ liệu của " << username << ".\n";
        } else {
            std::cout << "[Hệ thống] Không tìm thấy dữ liệu cũ. Tạo hồ sơ mới.\n";
        }
    }
    // Hiển thị thông tin
    void displayStats() const {
        std::cout << "=== Thống kê: " << username << " ===\n";
        std::cout << "Số trận thắng : " << wins << "\n";
        std::cout << "Số trận thua  : " << losses << "\n";
        std::cout << "Tỉ lệ thắng   : " << getWinRate() << "%\n";
        std::cout << "===========================\n";
    }
};
int main() {
    // 1. Tạo đối tượng người chơi
    Player p1("FakerVN");    
    // 2. Tải dữ liệu từ lần chơi trước (nếu có)
    p1.loadStats();
    // 3. Giả lập kết quả các trận đấu mới
    p1.recordWin();
    p1.recordWin();
    p1.recordLoss();
    // 4. In thông kê hiện tại
    p1.displayStats();
    // 5. Lưu lại trước khi thoát game
    p1.saveStats();
    return 0;
}
