/*
 * This screen handles the options/settings of the game in general
 * options included here include:
 * - Window Size
 * - Window Fullscreen State
 * - Master Volume
 * - Sound Effects Volume
 * - Music Volume
 *
 * all defined from options.h
 */

#include <stddef.h>

#include "options.h"
#include "raylib.h"
#include "screens.h"

static size_t selectedOption;
static size_t optionCount = 5;

void OptionsScreenUpdate(void)
{
    if (IsKeyPressed(KEY_DOWN))
        selectedOption = (selectedOption + 1) % optionCount;
    else if (IsKeyPressed(KEY_UP))
        selectedOption = (selectedOption + optionCount - 1) % optionCount;

    else if (IsKeyPressed(KEY_ESCAPE))
    {
        nextScreen = SCREEN_MENU;
    }
}

void OptionsScreenDraw(void)
{
    DrawText("Options", 40, 40, 30, BLACK);
    DrawText("Fullscreen", 50, 90, 20, BLACK);
}

void OptionsScreenLoad(void) {}
void OptionsScreenUnload(void)
{
    SaveOptions();
}
