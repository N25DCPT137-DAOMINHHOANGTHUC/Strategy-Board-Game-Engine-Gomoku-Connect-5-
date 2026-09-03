#include "raylib.h"
#include <vector>

const int BOARD_SIZE = 15;
const int CELL_SIZE = 40;
const int OFFSET_X = 50;
const int OFFSET_Y = 100;

struct Move {
    int row;
    int col;
};

char board[BOARD_SIZE][BOARD_SIZE];
std::vector<Move> moveHistory;
char currentPlayer = 'X';

void ResetGame() {
    for (int r = 0; r < BOARD_SIZE; r++) {
        for (int c = 0; c < BOARD_SIZE; c++) {
            board[r][c] = ' ';
        }
    }
    moveHistory.clear();
    currentPlayer = 'X';
}

void UndoMove() {
    if (!moveHistory.empty()) {
        Move lastMove = moveHistory.back();
        moveHistory.pop_back();
        board[lastMove.row][lastMove.col] = ' ';
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }
}

int main() {
    const int screenWidth = 800;
    const int screenHeight = 750;
    InitWindow(screenWidth, screenHeight, "Game Caro - Raylib");
    SetTargetFPS(60);

    Texture2D btnStart = LoadTexture("nut_bam/start.png");
    Texture2D btnUndo  = LoadTexture("nut_bam/di lai.png");
    Texture2D btnExit  = LoadTexture("nut_bam/exit.png");
    Texture2D iconX    = LoadTexture("nut_bam/nut X.png");
    Texture2D iconO    = LoadTexture("nut_bam/nut O.png");

    ResetGame();

    while (!WindowShouldClose()) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Vector2 mousePos = GetMousePosition();

            Rectangle rectStart = { 50, 20, (float)btnStart.width, (float)btnStart.height };
            Rectangle rectUndo  = { 200, 20, (float)btnUndo.width, (float)btnUndo.height };
            Rectangle rectExit  = { 350, 20, (float)btnExit.width, (float)btnExit.height };

            if (CheckCollisionPointRec(mousePos, rectStart)) {
                ResetGame();
            }
            else if (CheckCollisionPointRec(mousePos, rectUndo)) {
                UndoMove();
            }
            else if (CheckCollisionPointRec(mousePos, rectExit)) {
                break;
            }
            else {
                for (int r = 0; r < BOARD_SIZE; r++) {
                    for (int c = 0; c < BOARD_SIZE; c++) {
                        Rectangle cellRect = { 
                            (float)(OFFSET_X + c * CELL_SIZE), 
                            (float)(OFFSET_Y + r * CELL_SIZE), 
                            (float)CELL_SIZE, 
                            (float)CELL_SIZE 
                        };

                        if (CheckCollisionPointRec(mousePos, cellRect) && board[r][c] == ' ') {
                            board[r][c] = currentPlayer;
                            moveHistory.push_back({r, c});
                            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
                        }
                    }
                }
            }
        }

        BeginDrawing();
            ClearBackground(RAYWHITE);

            DrawTexture(btnStart, 50, 20, WHITE);
            DrawTexture(btnUndo, 200, 20, WHITE);
            DrawTexture(btnExit, 350, 20, WHITE);

            for (int i = 0; i <= BOARD_SIZE; i++) {
                DrawLine(OFFSET_X + i * CELL_SIZE, OFFSET_Y, 
                         OFFSET_X + i * CELL_SIZE, OFFSET_Y + BOARD_SIZE * CELL_SIZE, LIGHTGRAY);
                DrawLine(OFFSET_X, OFFSET_Y + i * CELL_SIZE, 
                         OFFSET_X + BOARD_SIZE * CELL_SIZE, OFFSET_Y + i * CELL_SIZE, LIGHTGRAY);
            }

            for (int r = 0; r < BOARD_SIZE; r++) {
                for (int c = 0; c < BOARD_SIZE; c++) {
                    int posX = OFFSET_X + c * CELL_SIZE;
                    int posY = OFFSET_Y + r * CELL_SIZE;

                    if (board[r][c] == 'X') {
                        DrawTexture(iconX, posX, posY, WHITE);
                    } else if (board[r][c] == 'O') {
                        DrawTexture(iconO, posX, posY, WHITE);
                    }
                }
            }

        EndDrawing();
    }

    UnloadTexture(btnStart);
    UnloadTexture(btnUndo);
    UnloadTexture(btnExit);
    UnloadTexture(iconX);
    UnloadTexture(iconO);

    CloseWindow();
    return 0;
}