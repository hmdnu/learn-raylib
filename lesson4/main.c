#include <raylib.h>
#include <stdio.h>

#include "player.h"
#include "ball.h"
#include "bricks.h"
#include "game.h"

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
    InitBricks(bricks);

    SetTargetFPS(60);              // set fps to 60
    while (!WindowShouldClose()) { // detect esc click button
        MainGameLoop(&screen, &framesCounter, &gamePaused, &player, &ball, bricks);
        DrawGame(&screen, &player, &ball, bricks, &gamePaused, &framesCounter);
    }
    // DE-initialization
    CloseWindow(); // close window and OpenGL context
    return 0;
}
