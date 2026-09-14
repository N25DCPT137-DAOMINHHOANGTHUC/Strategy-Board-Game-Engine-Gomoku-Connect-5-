#ifndef KHAIBAOHAINGUOICHOI_H
#define KHAIBAOHAINGUOICHOI_H

#include <string>

// Lop quan ly thong tin nguoi choi
class Player {
private:
    std::string name;
    char symbol;

public:
    Player(std::string n = "", char s = ' ') : name(n), symbol(s) {}

    std::string getName() const { return name; }
    char getSymbol() const { return symbol; }

    void setName(const std::string& n) { name = n; }
    void setSymbol(char s) { symbol = s; }
};

#endif // KHAIBAOHAINGUOICHOI_H
