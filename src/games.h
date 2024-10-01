#pragma once

#include "stddef.h"

typedef signed char PR_int8_t;
typedef char PR_bool_t;

typedef enum PR_GameType
{
    GAME_CLASSIC,
    GAME_HEXA,
} PR_GameType;

typedef union PR_GameConstraints {
    struct ClassicGame {
        int width;
        int height;
    } classicGame;

    struct HexaGame {
        int sideLength;
    } hexaGame;
} PR_GameConstraints;

typedef struct PR_GameCell {
    PR_int8_t type;
    PR_bool_t isOpened;
} PR_GameCell;

extern PR_GameType currentGameType;
extern PR_GameConstraints currentGameParams;
