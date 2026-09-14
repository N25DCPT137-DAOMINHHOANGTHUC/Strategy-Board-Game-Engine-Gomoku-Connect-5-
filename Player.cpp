#include <iostream>
#include <string>
using namespace std;

class Player {
private:
    string name;
    char symbol;

public:
    Player(string n, char s) : name(n), symbol(s) {}

    string getName() const { return name; }
    char getSymbol() const { return symbol; }
};

int main() {
    Player player1("Nguoi choi 1", 'X');
    Player player2("Nguoi choi 2", 'O');

    cout << player1.getName() << " (" << player1.getSymbol() << ")" << endl;
    cout << player2.getName() << " (" << player2.getSymbol() << ")" << endl;

    return 0;
}