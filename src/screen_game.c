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
}

static void HexaGameDraw(void)
{
    DrawText("Hex Game!", 0, 0, 20, BLUE);
}

static void HexaGameGetNeighbors(size_t cellIndex)
{
}
