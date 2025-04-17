#include <math.h>
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#define SCREEN_W (float)1280
#define SCREEN_Y (float)720

typedef struct Player {
    Vector2 position;
    Vector2 size;
    float radius;
    int speed;
} Player;

typedef struct Block {
    Vector2 position;
    Vector2 size;
    Rectangle bounds;
} Block;

typedef struct PlayerRect {
    Vector2 position;
    Vector2 size;
    Rectangle bounds;
    float speed;

} PlayerRect;
// Forward declarations of functions
void initPlayer(Player* player, PlayerRect* playerRect);
void initBlock(Block* block);
void handleMovement(Player* player);
void handleMovementPlayerRect(PlayerRect* player);
void playerCollisionScreen(Player* player);
void playerCollisionBlock(Player* player, PlayerRect* playerRect, Block* block);

int main() {
    Player player = {0};
    Block block = {0};
    PlayerRect playerRect = {0};

    initPlayer(&player, &playerRect);
    initBlock(&block);
    InitWindow(SCREEN_W, SCREEN_Y, "test");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        int size = snprintf(NULL, 0, "X: %f Y: %f", player.position.x, player.position.y);

        // movement player
        handleMovement(&player);
        handleMovementPlayerRect(&playerRect);
        playerCollisionScreen(&player);
        playerCollisionBlock(&player, &playerRect, &block);

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

        DrawFPS(10, SCREEN_Y / 10);

        // player
        // DrawCircleV(player.position, player.radius, BLUE);
        DrawRectangle(playerRect.position.x, playerRect.position.y, playerRect.size.x, playerRect.size.y, MAROON);
        DrawRectangle(block.position.x, block.position.y, block.size.x, block.size.y, ORANGE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

float findCollisionDepth(PlayerRect* player, Block* block) {
    // float left = player->position.x - 9;
    return 0;
}

void playerCollisionBlock(Player* player, PlayerRect* playerRect, Block* block) {
    block->bounds = (Rectangle){block->position.x, block->position.y, block->size.x, block->size.y};
    playerRect->bounds =
        (Rectangle){playerRect->position.x, playerRect->position.y, playerRect->size.x, playerRect->size.y};

    // collision playerRect vs block
    if (CheckCollisionRecs(playerRect->bounds, block->bounds)) {
        DrawText("Collide x", 50, 50, 20, BLACK);

    } else {
        DrawText("Not colliding", 50, 50, 20, BLACK);
    }

    // if (CheckCollisionCircleRec(player->position, player->radius, block->bounds)) {
    //     // Calculate collision depth from each side
    //     float left = player->position.x + player->radius - block->bounds.x;
    //     float right = (block->bounds.x + block->bounds.width) - (player->position.x - player->radius);
    //     float top = player->position.y + player->radius - block->bounds.y;
    //     float bottom = (block->bounds.y + block->bounds.height) - (player->position.y - player->radius);
    //     // printf("%d\n", left);
    //     printf("%d\n", right);
    //     // printf("%d\n", top);
    //     // printf("%d\n", bottom);

    //     // Find the minimum penetration depth
    //     float minDepth = fmin(fmin(left, right), fmin(top, bottom));
    //     printf("%d\n", minDepth);

    //     if (minDepth == left) {
    //         player->position.x = block->bounds.x - player->radius; // Push left
    //     } else if (minDepth == right) {
    //         player->position.x = block->bounds.x + block->bounds.width + player->radius; // Push right
    //     } else if (minDepth == top) {
    //         player->position.y = block->bounds.y - player->radius; // Push up
    //     } else {
    //         player->position.y = block->bounds.y + block->bounds.height + player->radius; // Push down
    //     }
    // }
}

void initPlayer(Player* player, PlayerRect* playerRect) {
    player->position = (Vector2){SCREEN_W / 2, SCREEN_Y / 2};
    player->speed = 8;
    player->size = (Vector2){50, 50};
    player->radius = 30;

    // init player rect
    playerRect->position = (Vector2){SCREEN_W / 2, SCREEN_Y / 2};
    playerRect->speed = 8.0f;
    playerRect->size = (Vector2){120, 100};
}

void initBlock(Block* block) {
    block->position = (Vector2){SCREEN_W / 4, SCREEN_Y / 4};
    block->size = (Vector2){120, 100};
    block->bounds = (Rectangle){0};
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
}

void handleMovementPlayerRect(PlayerRect* player) {
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
}

void playerCollisionScreen(Player* player) {
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
