#include "raylib.h"
#include "screens.h"

void GameScreenUpdate(void)
{
    if (IsKeyPressed(KEY_ESCAPE))
    {
        nextScreen = SCREEN_MENU;
    }
}

void GameScreenDraw(void)
{
    DrawText("Game screen!", 300, 300, 30, BLACK);
}

void GameScreenLoad(void) {}
void GameScreenUnload(void) {}
