#include "bricks.h"

static void DrawBrickPerLines(Brick bricks[BRICK_LINES][BRICKS_PER_LINES], int j) {
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
