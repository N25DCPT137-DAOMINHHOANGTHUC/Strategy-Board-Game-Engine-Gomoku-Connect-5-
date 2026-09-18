#ifndef BOARD_H
#define BOARD_H

const int BOARD_SIZE = 15;

struct Board {
    int a[BOARD_SIZE][BOARD_SIZE];
};

void initBoard(Board& b) {
    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++)
            b.a[i][j] = 0;
}

#endif
