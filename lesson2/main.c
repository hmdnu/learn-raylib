#include <raylib.h>
#include <stdio.h>

// values def
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 450
#define PLAYER_LIFES 5
#define BRICK_LINES 5
#define BRICKS_PER_LINES 20
#define BRICKS_POSITION_Y 50
#define GAME_TITLE "Block Game"

// player struct
typedef struct Player {
    Vector2 position;
    Vector2 speed;
    Vector2 size;
    Rectangle bounds;
    int lifes;
} Player;

// ball struct
typedef struct Ball {
    Vector2 position;
    Vector2 speed;
    float radius;
    bool active;
} Ball;

// brick struct
typedef struct Brick {
    Vector2 position;
    Vector2 size;
    Rectangle bounds;
    int resistance;
    bool active;
} Brick;

// Lesson 1 : window initialization and screen management
typedef enum GameScreen { LOGO, TITLE, GAMEPLAY, ENDING } GameScreen;

static void MainGameLoop(GameScreen*, int*, bool*);
static void DrawGame(GameScreen*, Player*, Ball*, Brick[BRICK_LINES][BRICKS_PER_LINES], bool);
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
        MainGameLoop(&screen, &framesCounter, &gamePaused);
        DrawGame(&screen, &player, &ball, bricks, gamePaused);
    }
    // DE-initialization
    CloseWindow(); // close window and OpenGL context
    return 0;
}

void MainGameLoop(GameScreen* screen, int* framesCounter, bool* gamePaused) {
    // update
    switch (*screen) {
        case LOGO: {
            // update LOGO screen data here
            (*framesCounter)++;
            if (*framesCounter > 180) {
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

            if (!gamePaused) {
                // TODO: gameplay logic
            }

            // LESSON 3: inputs management (keyboard, mouse)
            if (IsKeyPressed(KEY_ENTER)) {
                *screen = ENDING;
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

void DrawGame(
    GameScreen* screen, Player* player, Ball* ball, Brick bricks[BRICK_LINES][BRICKS_PER_LINES], bool gamePaused) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    switch (*screen) {
        case LOGO: {
            // draw logo screen here
            DrawText("LOGO SCREEN", 20, 20, 40, LIGHTGRAY);
            DrawText("WAIT for 3 SECONDS...", 200, 220, 20, GRAY);
            break;
        }

        case TITLE: {
            // draw logo title screen here
            DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, GREEN);
            DrawText("TITLE SCREEN", 20, 20, 40, DARKGREEN);
            DrawText("PRESS ENTER or TAP to JUMP to GAMEPLAY SCREEN", 120, 220, 20, DARKGREEN);
            break;
        }

        case GAMEPLAY: {
            // drawing gameplay screen
            // LESSON 2: draw basic shapes (circle, rectangle)
            DrawRectangle(player->position.x, player->position.y, player->size.x, player->size.y, BLACK); // player
            DrawCircleV(ball->position, ball->radius, MAROON);                                            // ball

            // draw bricks
            for (int j = 0; j < BRICK_LINES; j++) {
                for (int i = 0; i < BRICKS_PER_LINES; i++) {
                    if (!bricks[j][i].active) {
                        return;
                    }
                    if ((i + j) % 2 == 0) {
                        DrawRectangle(bricks[j][i].position.x,
                                      bricks[j][i].position.y,
                                      bricks[j][i].size.x,
                                      bricks[j][i].size.y,
                                      GRAY);
                    } else {
                        DrawRectangle(bricks[j][i].position.x,
                                      bricks[j][i].position.y,
                                      bricks[j][i].size.x,
                                      bricks[j][i].size.y,
                                      DARKGRAY);
                    }
                }
            }
            // draw gui: player lifes
            for (int i = 0; i < player->lifes; i++) {
                DrawRectangle(20 + 40 * i, SCREEN_HEIGHT - 30, 35, 10, LIGHTGRAY);
            }

            // draw pause message when required
            if (gamePaused) {
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
