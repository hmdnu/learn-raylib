#include <raylib.h>
#include <stdio.h>

#include "player.h"
#include "ball.h"
#include "bricks.h"
#include "game.h"

static void InitPlayer(Player*);
static void InitBall(Ball*, Player*);
static void InitBrick(Brick[BRICK_LINES][BRICKS_PER_LINES]);

int main(void) {
    // initialize window
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, GAME_TITLE);

    // load resource after window init
    // game required variables
    GameScreen screen = LOGO; // current game state
    int framesCounter = 0;    // general purpose frames counter
    int gameResult = 1;       // game result : 0 = lose, 1 = win, -1 not defined
    bool gamePaused = false;  // game paused state toggle

    // check defined struct on top
    Player player = {0};
    Ball ball = {0};
    Brick bricks[BRICK_LINES][BRICKS_PER_LINES] = {0};

    // init structs
    InitPlayer(&player);
    InitBall(&ball, &player);
    InitBrick(bricks);

    SetTargetFPS(60);              // set fps to 60
    while (!WindowShouldClose()) { // detect esc click button
        MainGameLoop(&screen, &framesCounter, &gamePaused, &player, &ball);
        DrawGame(&screen, &player, &ball, bricks, &gamePaused, &framesCounter);
    }
    // DE-initialization
    CloseWindow(); // close window and OpenGL context
    return 0;
}

void InitPlayer(Player* player) {
    player->position = (Vector2){SCREEN_WIDTH / 2, SCREEN_HEIGHT * 7 / 8};
    player->speed = (Vector2){8.0f, 0.0f};
    player->size = (Vector2){100, 24};
    player->lifes = PLAYER_LIFES;
}

void InitBall(Ball* ball, Player* player) {
    ball->radius = 10.0f;
    ball->active = false;
    ball->position = (Vector2){player->position.x + player->size.x / 2, player->position.y - ball->radius * 2};
    ball->speed = (Vector2){4.0f, 4.0f};
}

void InitBrick(Brick bricks[BRICK_LINES][BRICKS_PER_LINES]) {
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
