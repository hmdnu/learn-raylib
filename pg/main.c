#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#define SCREEN_W 1600
#define SCREEN_Y 800

typedef struct Player {
    Vector2 position;
    Vector2 size;
    float radius;
    int speed;
} Player;

static void handleMovement(Player*);
static void initPlayer(Player*);

int main() {
    Player player = {0};
    initPlayer(&player);

    InitWindow(SCREEN_W, SCREEN_Y, "test");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        int size = snprintf(NULL, 0, "X: %f Y: %f", player.position.x, player.position.y);

        // movement player
        handleMovement(&player);
        char* textBuffer = malloc(size);
        if (textBuffer) {
            snprintf(textBuffer, size, "X: %f Y: %f", player.position.x, player.position.y);
        }

        // drawing section
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (textBuffer) {
            DrawText(textBuffer, 20, 20, 24, BLACK);
            free(textBuffer);
        }

        // player
        DrawCircleV(player.position, player.radius, BLUE);
        DrawRectangle(SCREEN_W / 4, SCREEN_Y / 4, 50, 30, ORANGE);
        EndDrawing();
    }
    CloseWindow();

    return 0;
}

void initPlayer(Player* player) {
    player->position = (Vector2){SCREEN_W / 2, SCREEN_Y / 2};
    player->speed = 8;
    player->size = (Vector2){50, 50};
    player->radius = 30;
}

void handleMovement(Player* player) {
    if (IsKeyDown(KEY_W)) {
        player->position.y -= player->speed;
    }
    if (IsKeyDown(KEY_S)) {
        player->position.y += player->speed;
    }
    if (IsKeyDown(KEY_A)) {
        player->position.x -= player->speed;
    }
    if (IsKeyDown(KEY_D)) {
        player->position.x += player->speed;
    }

    // collision screen x
    if ((player->position.x - player->radius) <= 0) {
        player->position.x = player->radius;
    }
    if ((player->position.x + player->radius) >= SCREEN_W) {
        player->position.x = SCREEN_W - player->radius;
    }
    // collision screen y
    if ((player->position.y - player->radius) <= 0) {
        player->position.y = player->radius;
    }
    if ((player->position.y + player->radius) >= SCREEN_Y) {
        player->position.y = SCREEN_Y - player->radius;
    }
}