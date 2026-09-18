#ifndef MANG2CHIEU_H
#define MANG2CHIEU_H

#include <iostream>
using namespace std;

const int KICH_THUOC = 10;

void nhapMang(int a[KICH_THUOC][KICH_THUOC]) {
    for (int i = 0; i < KICH_THUOC; i++)
        for (int j = 0; j < KICH_THUOC; j++)
            cin >> a[i][j];
}

void xuatMang(const int a[KICH_THUOC][KICH_THUOC]) {
    for (int i = 0; i < KICH_THUOC; i++) {
        for (int j = 0; j < KICH_THUOC; j++)
            cout << a[i][j] << " ";
        cout << endl;
    }
}

#endif
