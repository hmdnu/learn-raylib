#include "bricks.h"
#include "game.h"

void DrawBrickPerLines(Brick bricks[BRICK_LINES][BRICKS_PER_LINES], int j) {
    for (int i = 0; i < BRICKS_PER_LINES; i++) {
        if (!bricks[j][i].active) {
            return;
        }
        if ((i + j) % 2 == 0) {
            DrawRectangle(
                bricks[j][i].position.x, bricks[j][i].position.y, bricks[j][i].size.x, bricks[j][i].size.y, GRAY);
        } else {
            DrawRectangle(
                bricks[j][i].position.x, bricks[j][i].position.y, bricks[j][i].size.x, bricks[j][i].size.y, DARKGRAY);
        }
        }
}

void DrawBricks(Brick bricks[BRICK_LINES][BRICKS_PER_LINES]) {
    for (int j = 0; j < BRICK_LINES; j++) {
        DrawBrickPerLines(bricks, j);
    }
}

void InitBricks(Brick bricks[BRICK_LINES][BRICKS_PER_LINES]) {
    for (int j = 0; j < BRICK_LINES; j++) {
        for (int i = 0; i < BRICKS_PER_LINES; i++) {
            bricks[j][i].size = (Vector2){SCREEN_WIDTH / BRICKS_PER_LINES, 20};
            bricks[j][i].position = (Vector2){i * bricks[j][i].size.x, j * bricks[j][i].size.y + BRICKS_POSITION_Y};
            bricks[j][i].bounds =
                (Rectangle){bricks[j][i].position.x, bricks[j][i].position.y, bricks[j][i].size.x, bricks[j][i].size.y};
            bricks[j][i].active = true;
        }
    }
}
