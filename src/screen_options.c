#include "raylib.h"
#include "screens.h"

void OptionsScreenUpdate()
{
    if (IsKeyPressed(KEY_BACKSPACE))
    {
        nextScreen = SCREEN_MENU;
    }
}

void OptionsScreenDraw()
{
    DrawText("Options screen!", 300, 300, 30, BLACK);
}

// Placeholder here until I implement the screens
void GameSelectScreenUpdate() {}
void GameSelectScreenDraw() {}
void GameScreenUpdate() {}
void GameScreenDraw() {}
