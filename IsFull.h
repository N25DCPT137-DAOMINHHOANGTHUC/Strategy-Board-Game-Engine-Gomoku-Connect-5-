#ifndef ISFULL_H
#define ISFULL_H

const int BOARD_SIZE = 15;

bool isFull(const int a[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++)
            if (a[i][j] == 0)
                return false;
    return true;
}

#endif
