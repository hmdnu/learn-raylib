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

void InitBall(Ball* ball, Player* player) {
    ball->radius = 10.0f;
    ball->active = false;
    ball->position = (Vector2){player->position.x + player->size.x / 2, player->position.y - ball->radius * 2};
    ball->speed = (Vector2){4.0f, 4.0f};
}
