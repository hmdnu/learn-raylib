#include "game.h"
#include "player.h"
#include <stdio.h>

void MainGameLoop(GameScreen* screen,
                  int* framesCounter,
                  bool* gamePaused,
                  Player* player,
                  Ball* ball,
                  Brick bricks[BRICK_LINES][BRICKS_PER_LINES]) {
    // update
    switch (*screen) {
        case LOGO: {
            // update LOGO screen data here
            (*framesCounter)++;
            if (*framesCounter > 60) {
                *screen = TITLE; // change to TITLE screen after 3 seconds
                *framesCounter = 0;
            }
            break;
        }

        case TITLE: {
            // update TITLE screen data here
            (*framesCounter)++;

            // LESSON 3: inputs management (keyboard, mouse)
            if (IsKeyPressed(KEY_ENTER)) {
                *screen = GAMEPLAY;
            }
            break;
        }

        case GAMEPLAY: {
            // update GAMEPLAY screen data here!
            if (IsKeyPressed(KEY_P)) {
                *gamePaused = !*gamePaused;
            }

            if (!(*gamePaused)) {
                // TODO: gameplay logic
                PlayerMovement(player); // player movement logic

                // ball movement logic
                if (ball->active) {
                    BallMovement(ball);

                    // TODO: collision detection and resolution
                    // collision logic: ball vs player

                    if (CheckCollisionCircleRec(ball->position, ball->radius, player->bounds)) {
                        ball->speed.y *= -1;
                        ball->speed.x =
                            (ball->position.x - (player->position.x + player->size.x / 2)) / player->size.x * 5.0f;
                    }

                    // collision ball vs bricks
                    for (int j = 0; j < BRICK_LINES; j++) {
                        for (int i = 0; i < BRICKS_PER_LINES; i++) {
                            if (bricks[j][i].active &&
                                (CheckCollisionCircleRec(ball->position, ball->radius, bricks[j][i].bounds))) {
                                bricks[j][i].active = false;
                                ball->speed.y *= -1;
                                break;
                            }
                        }
                    }

                    // game ending logic
                    if ((ball->position.y + ball->radius) >= SCREEN_HEIGHT) {
                        ball->position.x = player->position.x + player->size.x / 2;
                        ball->position.y = player->position.y - ball->radius - 1.0f;
                        ball->speed = (Vector2){0, 0};
                        ball->active = false;
                        player->lifes--;
                    }

                    // player lifes logic
                    if (player->lifes < 0) {
                        *screen = ENDING;
                        player->lifes = 5;
                        *framesCounter = 0;
                    }
                } else {
                    // reset ball position
                    ball->position.x = player->position.x + player->size.x / 2;

                    // LESSON 3: inputs management (keyboard, mouse)
                    if (IsKeyPressed(KEY_SPACE)) {
                        ball->active = true;
                        ball->speed = (Vector2){0, -5.0f};
                    }
                }
            }
            break;
        }

        case ENDING: {
            // update END screen data here!
            (*framesCounter)++;

            // LESSON 3: inputs management (keyboard, mouse)
            if (IsKeyPressed(KEY_ENTER)) {
                *screen = TITLE;
            }
            break;
        }
        default: {
            break;
        }
    }
}

void DrawGame(GameScreen* screen,
              Player* player,
              Ball* ball,
              Brick bricks[BRICK_LINES][BRICKS_PER_LINES],
              bool* gamePaused,
              int* framesCounter) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    switch (*screen) {
        case LOGO: {
            // draw logo screen here
            DrawText("LOGO SCREEN", 20, 20, 40, LIGHTGRAY);
            break;
        }

        case TITLE: {
            // draw logo title screen here
            // DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, GREEN);
            DrawText("TITLE SCREEN", 20, 20, 40, DARKGREEN);
            char* titleText = "PRESS [ENTER] to START";

            if ((*framesCounter / 30) % 2 == 0) {
                DrawText(titleText,
                         GetScreenWidth() / 2 - MeasureText(titleText, 20) / 2,
                         GetScreenHeight() / 2 + 60,
                         20,
                         DARKGREEN);
            }
            break;
        }
        case GAMEPLAY: {
            // drawing gameplay screen
            // LESSON 2: draw basic shapes (circle, rectangle)
            DrawPlayer(player); // player
            DrawBall(ball);     // ball
            DrawBricks(bricks); // bricks

            // draw gui: player lifes
            for (int i = 0; i < player->lifes; i++) {
                DrawRectangle(20 + 40 * i, SCREEN_HEIGHT - 30, 35, 10, LIGHTGRAY);
            }

            // draw pause message when required
            if (*gamePaused) {
                DrawText("GAME PAUSED",
                         SCREEN_WIDTH / 2 - MeasureText("GAME PAUSED", 40) / 2,
                         SCREEN_HEIGHT / 2 + 60,
                         40,
                         GRAY);
            }
            break;
        }

        case ENDING: {
            // draw ending screen here
            DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, BLUE);
            DrawText("ENDING SCREEN", 20, 20, 40, DARKBLUE);
            DrawText("PRESS ENTER or TAP to RETURN to TITLE SCREEN", 120, 220, 20, DARKBLUE);
            break;
        }
        default: {
            break;
        }
    }
    EndDrawing();
}
