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
        PLAYER_HEAD,
        PLAYER_BODY,
        GOAL
    } type;
} game_tile;

#endif