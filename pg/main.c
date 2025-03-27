#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

static void handleMovement(float*, float*, int*);

int main() {
    const int screenW = 1600;
    const int screenH = 800;
    Vector2 position = {(float)screenW / 2, (float)screenH / 2};
    const int speed = 20;

    InitWindow(screenW, screenH, "test");

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        //
        int size = snprintf(NULL, 0, "X: %d Y: %d", (int)position.x, (int)position.y);

        handleMovement(&position.x, &position.y, &speed);

        char* textBuffer = malloc(size);
        if (textBuffer) {
            snprintf(textBuffer, size, "X: %d Y: %d", (int)position.x, (int)position.y);
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (textBuffer) {
            DrawText(textBuffer, 20, 20, 24, BLACK);
            free(textBuffer);
        }
        DrawCircleV(position, 30, BLUE);
        DrawRectangle(screenW / 4, screenH / 4, 50, 30, ORANGE);

        EndDrawing();
    }
    CloseWindow();

    return 0;
}

void handleMovement(float* positionX, float* positionY, int* speed) {
    if (IsKeyDown(KEY_A)) {
        *positionX -= *speed;
    }
    if (IsKeyDown(KEY_D)) {
        *positionX += *speed;
    }
    if (IsKeyDown(KEY_W)) {
        *positionY -= *speed;
    }
    if (IsKeyDown(KEY_S)) {
        *positionY += *speed;
    }
}