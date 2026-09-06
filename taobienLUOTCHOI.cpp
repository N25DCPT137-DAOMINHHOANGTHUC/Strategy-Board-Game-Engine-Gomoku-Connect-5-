#include <iostream>
#include <conio.h>   
using namespace std;

int main() {
    int Luotchoi = 1;

    cout << "Luot choi hien tai: " << Luotchoi << endl;
    cout << "Nhan phim bat ky de doi luot (ESC de thoat)..." << endl;

    char key;
    while (true) {
        key = _getch();

        if (key == 27) 
            break;

  
        Luotchoi = (Luotchoi == 1) ? 2 : 1;

        cout << "Luot choi hien tai: " << Luotchoi << endl;
    }

    cout << "Ket thuc chuong trinh." << endl;
    return 0;
}