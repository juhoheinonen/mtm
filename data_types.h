#include <stddef.h>

#ifndef DATA_TYPES_H

#define DATA_TYPES_H

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

#endif