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
        GRASS,
        WALL,
        PLAYER_HEAD,
        PLAYER_BODY,
        GOAL
    } type;
} game_tile;

typedef struct player_body
{
    int x;
    int y;
    struct player_body *next;    
} player_body;

typedef struct
{
    int x;
    int y;
    enum 
    {
        UP,
        DOWN,
        LEFT,
        RIGHT
    } direction;
    player_body *next;
} player_head;

// enum for game status, like running, game over and win
typedef enum
{
    RUNNING,
    GAME_OVER,
    WIN
} game_status;

#endif