#include "raylib.h"

int main(void) {
    const int screenWidth = 800;
    const int screenHeight = 450;
    const char *title = "Basic Window";

    // init windows
    InitWindow(screenWidth, screenHeight, title);

    SetTargetFPS(60); // set game to run at 60 fps

    // main game loop
    while (!WindowShouldClose()) { // detect window close button or ESC key
        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawText("Congrats you created your first window!", 190, 200, 20, LIGHTGRAY);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
