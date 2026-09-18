#ifndef CHECKWIN_H
#define CHECKWIN_H

const int BOARD_SIZE = 15;

bool checkWin(const int a[BOARD_SIZE][BOARD_SIZE], int x, int y, int player) {
    const int dx[] = {0, 1, 1, 1};
    const int dy[] = {1, 0, 1, -1};

    for (int k = 0; k < 4; k++) {
        int dem = 1;

        for (int i = x + dx[k], j = y + dy[k];
             i >= 0 && i < BOARD_SIZE &&
             j >= 0 && j < BOARD_SIZE &&
             a[i][j] == player;
             i += dx[k], j += dy[k])
            dem++;

        for (int i = x - dx[k], j = y - dy[k];
             i >= 0 && i < BOARD_SIZE &&
             j >= 0 && j < BOARD_SIZE &&
             a[i][j] == player;
             i -= dx[k], j -= dy[k])
            dem++;

        if (dem >= 5)
            return true;
    }
    return false;
}

#endif
