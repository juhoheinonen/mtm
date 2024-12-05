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
    // The player's body is a linked list of body parts.
    struct player_body *next;
} player_head;

typedef struct
{
    int x;
    int y;
    // The player's body is a linked list of body parts.
    struct player_body *next;    
} player_body;

// enum for game status, like running, game over and win
typedef enum
{
    RUNNING,
    GAME_OVER,
    WIN
} game_status;

#endif