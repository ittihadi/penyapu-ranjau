#include <stddef.h>
#include <stdlib.h>

#include "games.h"
#include "raylib.h"
#include "screens.h"

//----------------------------------------------------------------------------------
// Shared Variables Definition
//----------------------------------------------------------------------------------
PR_GameType        currentGameType;
PR_GameConstraints currentGameParams;

//----------------------------------------------------------------------------------
// Local Variables Definition
//----------------------------------------------------------------------------------
static int    currentGameRunning;
static int    gameScore;
static double gameTimeElapsed;

static Camera2D camera = {0};

static size_t       cellCount;
static PR_GameCell* cells;

static size_t        neighborCount;
static PR_GameCell** neighborBuffer;

// Gets neighbor cell addresses of the current given cell,
// gives NULL if none found.
static void (*GetNeighborsToBuffer)(size_t cellIndex);
static void (*Draw)(void);

static void StandardGameDraw(void);
static void StandardGameGetNeighbors(size_t cellIndex);
static void HexaGameDraw(void);
static void HexaGameGetNeighbors(size_t cellIndex);

void GameScreenUpdate(void)
{
    int moveDirectionX = 0;
    int moveDirectionY = 0;
    if (IsKeyPressed(KEY_LEFT)) moveDirectionX--;
    if (IsKeyPressed(KEY_RIGHT)) moveDirectionX++;
    if (IsKeyPressed(KEY_UP)) moveDirectionY--;
    if (IsKeyPressed(KEY_DOWN)) moveDirectionY++;
    if (moveDirectionX != 0 || moveDirectionY != 0)
    {
        // move the cell / cursor here
    }

    if (IsKeyPressed(KEY_ESCAPE))
    {
        nextScreen = SCREEN_MENU;
    }
}

void GameScreenDraw(void)
{
    BeginMode2D(camera);
    Draw();
    EndMode2D();
}

void GameScreenLoad(void)
{
    switch (currentGameType)
    {
        case GAME_CLASSIC:
            neighborCount = 8;
            cellCount     = currentGameParams.classicGame.width * currentGameParams.classicGame.height;

            GetNeighborsToBuffer = StandardGameGetNeighbors;
            Draw                 = StandardGameDraw;
            break;

        case GAME_HEXA:
            neighborCount = 6;
            cellCount     = 0;
            // Some mathematical deduction and simplification would really help and turn
            // this to one simple algebraic expression
            for (size_t i = 0; i < currentGameParams.hexaGame.sideLength; ++i)
                cellCount += 2 * (i + currentGameParams.hexaGame.sideLength);
            cellCount -= (2 * currentGameParams.hexaGame.sideLength) - 1;

            GetNeighborsToBuffer = HexaGameGetNeighbors;
            Draw                 = HexaGameDraw;
            break;
    }
    cells          = malloc(cellCount * sizeof(PR_GameCell));
    neighborBuffer = malloc(neighborCount * sizeof(PR_GameCell*));

    camera.zoom     = 1.0f;
    camera.offset   = (Vector2){GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
    camera.target   = (Vector2){0.0f, 0.0f};
    camera.rotation = 0;
}

void GameScreenUnload(void)
{
    free(cells);
    free(neighborBuffer);
}

//----------------------------------------------------------------------------------
// Game function definitions
//----------------------------------------------------------------------------------
static void StandardGameDraw(void)
{
    DrawText("Standard Game!", 0, 0, 20, BLACK);
}

static void StandardGameGetNeighbors(size_t cellIndex)
{
    int gridWidth  = currentGameParams.classicGame.width;
    int gridHeight = currentGameParams.classicGame.height;
    int cellX      = cellIndex % gridWidth;
    int cellY      = cellIndex / gridWidth;

    size_t offsets[] = {-gridWidth - 1, -gridWidth,
                        -gridWidth + 1, -1, 1,
                        gridWidth - 1, gridWidth,
                        gridWidth + 1};

    // This only bound checks y axis
    for (size_t i = 0; i < neighborCount; i++)
    {
        size_t idx = offsets[i] + cellIndex;
        if (idx < 0 || idx >= cellCount)
            neighborBuffer[i] = NULL;
        else
            neighborBuffer[i] = &cells[idx];
    }

    // Handle neighbors wrapped around on the x axis
    if (cellX == 0)
    {
        neighborBuffer[0] = NULL;
        neighborBuffer[3] = NULL;
        neighborBuffer[5] = NULL;
    }

    if (cellX == gridWidth - 1)
    {
        neighborBuffer[2] = NULL;
        neighborBuffer[4] = NULL;
        neighborBuffer[7] = NULL;
    }
}

static void HexaGameDraw(void)
{
    DrawText("Hex Game!", 0, 0, 20, BLUE);
}

static void HexaGameGetNeighbors(size_t cellIndex)
{
    int    gridLength      = currentGameParams.hexaGame.sideLength;
    size_t cellIndexInLine = cellIndex;

    int    found   = 0;
    size_t lineIdx = 0;
    size_t prevLen = 0;
    size_t currLen = 0;
    size_t nextLen = 0;

    // Top half
    for (size_t i = 0; i < gridLength; ++i)
    {
        lineIdx++;
        currLen = gridLength + i;
        prevLen = currLen - 1;
        nextLen = currLen + 1;
        if (cellIndexInLine < currLen)
        {
            found = 1;
            break;
        }
        cellIndexInLine -= currLen;
    }

    // Bottom half
    for (size_t i = gridLength - 2; i >= 0 && !found; i--)
    {
        lineIdx++;
        currLen = gridLength + i;
        prevLen = currLen + 1;
        nextLen = currLen - 1;
        if (cellIndexInLine < currLen)
            break;
        cellIndexInLine -= currLen;
    }

    // Exactly in the middle
    if (currLen == (gridLength * 2) - 1)
        prevLen = nextLen = currLen - 1;

    // Clear neighbor buffer
    for (size_t i = 0; i < neighborCount; i++)
        neighborBuffer[i] = NULL;

    size_t maxCurrNext = (1 + nextLen + currLen) >> 1;
    size_t maxCurrPrev = (1 + prevLen + currLen) >> 1;

    if (cellIndexInLine > 0)
    {
        // W neighbor
        neighborBuffer[2] = &cells[cellIndex - 1];
        // NW neighbor
        if (lineIdx > 0)
            neighborBuffer[0] = &cells[cellIndex - maxCurrPrev];
        // NE neighbor
        if (lineIdx < 2 * gridLength - 2)
            neighborBuffer[1] = &cells[cellIndex - maxCurrPrev + 1];
    }
    else
    {
        // "Top" half
        if (currLen < nextLen)
            neighborBuffer[4] = &cells[cellIndex + maxCurrNext - 1];
        // "bottom" half
        if (currLen < prevLen)
            neighborBuffer[0] = &cells[cellIndex - maxCurrPrev];
    }

    if (cellIndexInLine < currLen - 1)
    {
        // E neighbor
        neighborBuffer[3] = &cells[cellIndex + 1];
        // SW neighbor
        if (lineIdx > 0)
            neighborBuffer[4] = &cells[cellIndex + maxCurrNext - 1];
        // SE neighbor
        if (lineIdx < 2 * gridLength - 2)
            neighborBuffer[5] = &cells[cellIndex + maxCurrNext];
    }
    else
    {
        // "Top" half
        if (currLen < nextLen)
            neighborBuffer[5] = &cells[cellIndex + maxCurrNext];
        // "bottom" half
        if (currLen < prevLen)
            neighborBuffer[1] = &cells[cellIndex - maxCurrPrev + 1];
    }
}
