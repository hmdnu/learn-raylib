#include "ball.h"
#include "game.h"

void DrawBall(Ball* ball) {
    DrawCircleV(ball->position, ball->radius, MAROON);
}

void BallMovement(Ball* ball) {
    ball->position.x += ball->speed.x;
    ball->position.y += ball->speed.y;

    // collision logic: ball vs screen limits
    if (((ball->position.x + ball->radius) >= SCREEN_WIDTH) || ((ball->position.x - ball->radius) <= 0)) {
        ball->speed.x *= -1;
    }

    if ((ball->position.y - ball->radius) <= 0) {
        ball->speed.y *= -1;
    }
}