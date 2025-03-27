#include <raylib.h>
#include <stdio.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 450

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "shape example");
    float rotation = 0.0f;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        rotation += 0.2f;
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("some basic shapes available on raylib", 20, 20, 20, DARKGRAY);

        // circle shapes and lines
        DrawCircle(SCREEN_WIDTH / 5, 120, 35, DARKBLUE);
        DrawCircleGradient(SCREEN_WIDTH / 5, 220, 60, GREEN, SKYBLUE);
        DrawCircleLines(SCREEN_WIDTH / 5, 340, 80, DARKBLUE);

        // rectangle shapes and lines
        DrawRectangle(SCREEN_WIDTH / 4 * 2 - 60, 100, 120, 60, RED);
        DrawRectangleGradientH(SCREEN_WIDTH / 4 * 2 - 90, 170, 180, 130, MAROON, GOLD);
        DrawRectangleLines(SCREEN_WIDTH / 4 * 2 - 40, 320, 80, 60, ORANGE); // NOTE: Uses QUADS internally, not lines

        // triangle shapes and lines
        DrawTriangle((Vector2){SCREEN_WIDTH / 4.0f * 3.0f, 80.0f},
                     (Vector2){SCREEN_WIDTH / 4.0f * 3.0f - 60.0f, 150.0f},
                     (Vector2){SCREEN_WIDTH / 4.0f * 3.0f + 60.0f, 150.0f},
                     VIOLET);

        DrawTriangleLines((Vector2){SCREEN_WIDTH / 4.0f * 3.0f, 160.0f},
                          (Vector2){SCREEN_WIDTH / 4.0f * 3.0f - 20.0f, 230.0f},
                          (Vector2){SCREEN_WIDTH / 4.0f * 3.0f + 20.0f, 230.0f},
                          DARKBLUE);

        // Polygon shapes and lines
        DrawPoly((Vector2){SCREEN_WIDTH / 4.0f * 3, 330}, 6, 80, rotation, BROWN);
        DrawPolyLines((Vector2){SCREEN_WIDTH / 4.0f * 3, 330}, 6, 90, rotation, BROWN);
        DrawPolyLinesEx((Vector2){SCREEN_WIDTH / 4.0f * 3, 330}, 6, 85, rotation, 6, BEIGE);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
