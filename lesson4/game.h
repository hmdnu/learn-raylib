#include "player.h"
#include "ball.h"
#include "bricks.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 450
#define GAME_TITLE "Block Game"

// Lesson 1 : window initialization and screen management
typedef enum GameScreen { LOGO, TITLE, GAMEPLAY, ENDING } GameScreen;

void MainGameLoop(GameScreen*, int*, bool*, Player*, Ball*, Brick[BRICK_LINES][BRICKS_PER_LINES]);
void DrawGame(GameScreen*, Player*, Ball*, Brick[BRICK_LINES][BRICKS_PER_LINES], bool*, int*);
