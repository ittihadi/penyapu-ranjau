#include <stddef.h>
#include <stdlib.h>

#include "games.h"
#include "raylib.h"
#include "screens.h"

//----------------------------------------------------------------------------------
// Shared Variables Definition
//----------------------------------------------------------------------------------
PR_GameType        gameType;
PR_GameConstraints gameParams;
Texture2D          cellTex;

//----------------------------------------------------------------------------------
// Local Variables Definition
//----------------------------------------------------------------------------------
static Camera2D        camera        = {0};
static RenderTexture2D gridRenderTex = {0};

static PR_GameTypeData gameData;

void GameScreenUpdate(void)
{
    int moveDirectionX = 0;
    int moveDirectionY = 0;
    if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_H)) moveDirectionX--;
    if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_L)) moveDirectionX++;
    if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_K)) moveDirectionY--;
    if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_J)) moveDirectionY++;
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
    // TODO: draw grid onto render texture
    gameData.DrawCells(&gameData, &gameParams);
    EndMode2D();
}

void GameScreenLoad(void)
{
    switch (gameType)
    {
        case GAME_CLASSIC:
            gameData.neighborCount = 8;
            gameData.cellCount     = gameParams.classicGame.width * gameParams.classicGame.height;

            gameData.PopulateNeighborBuffer = StandardGameGetNeighbors;
            gameData.DrawCells              = StandardGameDraw;

            // get grid size
            // gridRenderTex = LoadRenderTexture(gridWidth, gridheight);
            break;

        case GAME_HEXA:
            gameData.neighborCount = 6;
            gameData.cellCount     = 0;
            // Some mathematical deduction and simplification would really help and turn
            // this to one simple algebraic expression
            for (size_t i = 0; i < gameParams.hexaGame.sideLength; ++i)
                gameData.cellCount += 2 * (i + gameParams.hexaGame.sideLength);
            gameData.cellCount -= (2 * gameParams.hexaGame.sideLength) - 1;

            gameData.PopulateNeighborBuffer = HexaGameGetNeighbors;
            gameData.DrawCells              = HexaGameDraw;

            // get grid size
            // gridRenderTex = LoadRenderTexture(gridWidth, gridheight);
            break;
    }
    gameData.cells          = malloc(gameData.cellCount * sizeof(PR_GameCell));
    gameData.neighborBuffer = malloc(gameData.neighborCount * sizeof(PR_GameCell *));

    camera.zoom     = 2.0f;
    camera.offset   = (Vector2){GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
    camera.target   = (Vector2){0.0f, 0.0f};
    camera.rotation = 0;

    cellTex = LoadTexture("resources/cells.png");
}

void GameScreenUnload(void)
{
    free(gameData.cells);
    free(gameData.neighborBuffer);
}
