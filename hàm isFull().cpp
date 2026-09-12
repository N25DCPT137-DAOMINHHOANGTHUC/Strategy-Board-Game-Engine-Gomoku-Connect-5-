#include <iostream>
using namespace std;
bool isFull(int a[15][15]) {
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            if (a[i][j] == 0) {
                return false; 
            }
        }
    }

    return true; 
}
if (isFull()) {
    cout << "Tran dau hoa!" << endl;
    break;
}

