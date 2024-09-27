#include "raylib.h"
#include "screens.h"

void OptionsScreenUpdate(void)
{
    if (IsKeyPressed(KEY_ESCAPE))
    {
        nextScreen = SCREEN_MENU;
    }
}

void OptionsScreenDraw(void)
{
    DrawText("Options screen!", 300, 300, 30, BLACK);
}

void OptionsScreenLoad(void) {}
void OptionsScreenUnload(void) {}
