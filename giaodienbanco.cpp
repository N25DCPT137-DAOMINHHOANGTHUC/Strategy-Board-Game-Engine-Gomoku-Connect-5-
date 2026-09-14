#include "raylib.h"

const int BOARD_SIZE = 10;   // Bàn cờ 10x10
const int CELL_SIZE = 50;    // Kích thước mỗi ô (50px)
const int OFFSET_X = 50;     // Căn lề trái
const int OFFSET_Y = 50;     // Căn lề trên

int main() {
    // TÍNH KÍCH THƯỚC CỬA SỔ VỪA KHÍT BÀN CỜ (Xóa phần khoảng trống thừa phía dưới)
    int windowWidth = OFFSET_X * 2 + BOARD_SIZE * CELL_SIZE;   // 600px
    int windowHeight = OFFSET_Y * 2 + BOARD_SIZE * CELL_SIZE;  // 600px

    InitWindow(windowWidth, windowHeight, "Ban co Caro 10x10 - Raylib");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // VẼ BÀN CỜ 10x10
        for (int i = 0; i <= BOARD_SIZE; i++) {
            // Đường dọc
            DrawLine(OFFSET_X + i * CELL_SIZE, OFFSET_Y, 
                     OFFSET_X + i * CELL_SIZE, OFFSET_Y + BOARD_SIZE * CELL_SIZE, BLACK);
            // Đường ngang
            DrawLine(OFFSET_X, OFFSET_Y + i * CELL_SIZE, 
                     OFFSET_X + BOARD_SIZE * CELL_SIZE, OFFSET_Y + i * CELL_SIZE, BLACK);
        }

        // XÓA LỆNH DrawText(...) HIỂN THỊ "Luot đi hien tai" Ở ĐÂY

        EndDrawing();
    }

    CloseWindow();
    return 0;
}