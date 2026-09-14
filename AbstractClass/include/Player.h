#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <utility>
#include <vector>

class Player {
protected:
    std::string name;
    char symbol; // 'X' hoặc 'O'

public:
    Player(const std::string& name, char symbol);
    virtual ~Player() = default;

    // Pure virtual function
    virtual std::pair<int, int> makeMove(const std::vector<std::vector<char>>& board) = 0;

    std::string getName() const;
    char getSymbol() const;
    void displayInfo() const;
};

#endif // PLAYER_H