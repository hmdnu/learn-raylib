#include <raylib.h>

// Lesson 1 : window initialization and screen management
typedef enum GameScreen { LOGO, TITLE, GAMEPLAY, ENDING } GameScreen;

static void mainGameLoop(GameScreen*, int*, bool*);
static void drawGame(GameScreen*, int, int);

int main(void) {
    const int screenWidth = 800;
    const int screenHeight = 450;
    const char* title = "Block Game";

    // initialize window
    InitWindow(screenWidth, screenHeight, title);

    // load resource after window init
    // game required variables
    GameScreen screen = LOGO; // current game state
    int framesCounter = 0;    // general purpose frames counter
    int gameResult = 1;       // game result : 0 = lose, 1 = win, -1 not defined
    bool gamePaused = false;  // game paused state toggle

    SetTargetFPS(60); // set fps to 60

    while (!WindowShouldClose()) { // detect esc click button
        mainGameLoop(&screen, &framesCounter, &gamePaused);
        drawGame(&screen, screenWidth, screenHeight);
    }
    // DE-initialization
    CloseWindow(); // close window and OpenGL context
    return 0;
}

void drawGame(GameScreen* screen, int screenWidth, int screenHeight) {
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
            DrawRectangle(0, 0, screenWidth, screenHeight, GREEN);
            DrawText("TITLE SCREEN", 20, 20, 40, DARKGREEN);
            DrawText("PRESS ENTER or TAP to JUMP to GAMEPLAY SCREEN",
                     120,
                     220,
                     20,
                     DARKGREEN);
            break;
        }

        case ENDING: {
            // draw ending screen here
            DrawRectangle(0, 0, screenWidth, screenHeight, BLUE);
            DrawText("ENDING SCREEN", 20, 20, 40, DARKBLUE);
            DrawText("PRESS ENTER or TAP to RETURN to TITLE SCREEN",
                     120,
                     220,
                     20,
                     DARKBLUE);
            break;
        }
        default: {
            break;
        }
    }
    EndDrawing();
}

void mainGameLoop(GameScreen* screen, int* framesCounter, bool* gamePaused) {
    // update
    switch (*screen) {
        case LOGO: {
            // update LOGO screen data here
            (*framesCounter)++;
            if (*framesCounter > 100) {
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
