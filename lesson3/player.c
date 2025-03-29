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