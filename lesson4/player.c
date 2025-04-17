#include <stdio.h>

#include "player.h"
#include "game.h"

void PlayerMovement(Player* player) {
    if (IsKeyDown(KEY_LEFT)) {
        player->position.x -= player->speed.x;
    }
    if (IsKeyDown(KEY_RIGHT)) {
        player->position.x += player->speed.x;
    }
    // screen edge collision
    if ((player->position.x) <= 0) {
        player->position.x = 0;
    }
    if ((player->position.x + player->size.x) >= SCREEN_WIDTH) {
        player->position.x = SCREEN_WIDTH - player->size.x;
    }

    player->bounds = (Rectangle){player->position.x, player->position.y, player->size.x, player->size.y};
}

void DrawPlayer(Player* player) {
    DrawRectangle(player->position.x, player->position.y, player->size.x, player->size.y, BLACK);
}

void InitPlayer(Player* player) {
    player->position = (Vector2){SCREEN_WIDTH / 2, SCREEN_HEIGHT * 7 / 8};
    player->speed = (Vector2){8.0f, 0.0f};
    player->size = (Vector2){100, 24};
    player->lifes = PLAYER_LIFES;
}
