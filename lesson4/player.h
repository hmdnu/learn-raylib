#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>
#define PLAYER_LIFES 5

typedef struct Player {
    Vector2 position;
    Vector2 speed;
    Vector2 size;
    Rectangle bounds;
    int lifes;
} Player;

void PlayerMovement(Player*);
void DrawPlayer(Player*);
void InitPlayer(Player*);

#endif