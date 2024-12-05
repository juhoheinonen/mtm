#include "raylib.h"

typedef struct
{
    int x;
    int y;
    enum
    {
        EMPTY,
        WALL,
        PLAYER,
        GOAL
    } type;
} game_tile;
