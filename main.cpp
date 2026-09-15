#include "checkWin.h"

int main() {
    int a[15][15] = {0};

    // Nhap ban co 
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            cin >> a[i][j];
        }
    }

    // Xuat ban co 
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }

    // Vi tri quan co vua danh 
    int x, y, player;
    cin >> x >> y >> player;

    if (checkWin(a, x, y, player))
        cout << "Thang!";
    else
        cout << "Chua thang!";

    return 0;
}
