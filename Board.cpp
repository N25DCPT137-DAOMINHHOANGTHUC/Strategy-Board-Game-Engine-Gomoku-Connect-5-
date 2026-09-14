#include <iostream>
using namespace std;

bool checkWin(int a[15][15], int x, int y, int player) {

    // 4 huong: 
    // (0, 1)  : ngang
    // (1, 0)  : doc 
    // (1, 1)  :  \
    // (1, -1) :  /
    int dx[] = {0, 1, 1, 1};
    int dy[] = {1, 0, 1, -1};

    for (int k = 0; k < 4; k++) {

        int dem = 1;

        // Kiem tra phia truoc 
        int i = x + dx[k];
        int j = y + dy[k];

        while (i >= 0 && i < 15 &&
               j >= 0 && j < 15 &&
               a[i][j] == player) {

            dem++;

            i += dx[k];
            j += dy[k];
        }

        // Kiem tra phia sau 
        i = x - dx[k];
        j = y - dy[k];

        while (i >= 0 && i < 15 &&
               j >= 0 && j < 15 &&
               a[i][j] == player) {

            dem++;

            i -= dx[k];
            j -= dy[k];
        }

        // Neu 5 quan lien tiep 
        if (dem >= 5)
            return true;
    }

    return false;
}

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
