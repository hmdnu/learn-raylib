#ifndef BALL_H
#define BALL_H

#include <raylib.h>

typedef struct Ball {
    Vector2 position;
    Vector2 speed;
    float radius;
    bool active;
} Ball;

void DrawBall(Ball*);
void BallMovement(Ball*);

#endif