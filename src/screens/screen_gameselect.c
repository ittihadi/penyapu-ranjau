#include <stddef.h>
#include <stdlib.h>

#include "games.h"
#include "raylib.h"
#include "screens.h"

typedef struct GameOption
{
    char *title;
    char *description;
} GameOption;

const static size_t gameCount = 2;
static GameOption  *games;

static size_t selectedGame;

void GameSelectScreenLoad(void)
{
    selectedGame = 0;

    // Dynamically allocate because it's a bunch of strings
    games    = (GameOption *)malloc(gameCount * sizeof(GameOption));
    games[0] = (GameOption){
        .title       = "Classic Minesweeper",
        .description = "Minesweeper like it's most commonly done"};
    games[1] = (GameOption){
        .title       = "Hexa Minesweeper",
        .description = "Minesweeper but it's in the shape of hexagons"};
}

void GameSelectScreenUnload(void)
{
    free(games);
}

void GameSelectScreenUpdate(void)
{
    if (IsKeyPressed(KEY_ESCAPE))
        nextScreen = SCREEN_MENU;
    else if (IsKeyPressed(KEY_ENTER))
    {
        nextScreen = SCREEN_GAME;
        gameType   = (PR_GameType)selectedGame;
        switch (gameType)
        {
            case GAME_CLASSIC:
                gameParams.classicGame.width  = 10;
                gameParams.classicGame.height = 8;
                break;
            case GAME_HEXA:
                gameParams.hexaGame.sideLength = 6;
                break;
        }
    }

    else if (IsKeyPressed(KEY_DOWN))
        selectedGame = (selectedGame + 1) % gameCount;
    else if (IsKeyPressed(KEY_UP))
        selectedGame = (selectedGame + gameCount - 1) % gameCount;
}

void GameSelectScreenDraw(void)
{
    for (size_t i = 0; i < gameCount; ++i)
    {
        DrawText(games[i].title, selectedGame == i ? 110 : 100, 100 + 100 * i, 30, BLACK);
        DrawText(games[i].description, selectedGame == i ? 110 : 100, 130 + 100 * i, 20, BLACK);
    }
}
