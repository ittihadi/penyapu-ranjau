#pragma once

#include "stddef.h"
#include "raylib.h"
#include "stdint.h"

typedef enum PR_GameType
{
    GAME_CLASSIC,
    GAME_HEXA,
} PR_GameType;

typedef union PR_GameConstraints
{
    struct ClassicGame
    {
        int width;
        int height;
    } classicGame;

    struct HexaGame
    {
        int sideLength;
    } hexaGame;
} PR_GameConstraints;

typedef struct PR_GameCell
{
    int8_t type;
    int8_t state;
    Rectangle bounds;
} PR_GameCell;

typedef struct PR_GameTypeData
{
    int    currentGameRunning;
    int    gameScore;
    double gameTimeElapsed;

    size_t       cellCount;
    PR_GameCell *cells;

    size_t        neighborCount;
    PR_GameCell **neighborBuffer;

    void (*PopulateNeighborBuffer)(struct PR_GameTypeData *data, PR_GameConstraints *constraints, size_t cellIndex);
    void (*DrawCells)(struct PR_GameTypeData *data, PR_GameConstraints *constraints);
} PR_GameTypeData;

extern PR_GameType        gameType;
extern PR_GameConstraints gameParams;

extern Texture2D cellTex;

void StandardGameDraw(PR_GameTypeData *data, PR_GameConstraints *constraints);
void StandardGameGetNeighbors(struct PR_GameTypeData *data, PR_GameConstraints *constraints, size_t cellIndex);

void HexaGameDraw(PR_GameTypeData *data, PR_GameConstraints *constraints);
void HexaGameGetNeighbors(struct PR_GameTypeData *data, PR_GameConstraints *constraints, size_t cellIndex);
