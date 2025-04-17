#ifndef BRICKS_H
#define BRICKS_H

#include <raylib.h>

#define BRICK_LINES 5
#define BRICKS_PER_LINES 20
#define BRICKS_POSITION_Y 50

typedef struct Brick {
    Vector2 position;
    Vector2 size;
    Rectangle bounds;
    int resistance;
    bool active;
} Brick;

void DrawBricks(Brick[BRICK_LINES][BRICKS_PER_LINES]);
void InitBricks(Brick[BRICK_LINES][BRICKS_PER_LINES]);

#endif
