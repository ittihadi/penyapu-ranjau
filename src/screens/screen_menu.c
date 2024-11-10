#include "globals.h"
#include "raylib.h"
#include "screens.h"

enum MenuItem
{
    START,
    OPTIONS,
    EXIT,
    MENU_ITEM_COUNT,
};

static int       selectedMenuItem = START;
static Texture2D backgroundTex;

void MenuScreenLoad(void)
{
    // backgroundTex = LoadTexture("menuBG.png");
}

void MenuScreenUnload(void)
{
    // UnloadTexture(backgroundTex);
}

void MenuScreenUpdate(void)
{
    // Very rough wraparound code, fix later
    // // Still very rought but hey, both are one liners now
    if (IsKeyPressed(KEY_DOWN))
        selectedMenuItem = (selectedMenuItem + 1) % MENU_ITEM_COUNT;
    else if (IsKeyPressed(KEY_UP))
        selectedMenuItem = (selectedMenuItem + MENU_ITEM_COUNT - 1) % MENU_ITEM_COUNT;

    else if (IsKeyPressed(KEY_ENTER))
    {
        switch (selectedMenuItem)
        {
            case START:
                nextScreen = SCREEN_GAMESELECT;
                break;
            case OPTIONS:
                nextScreen = SCREEN_OPTIONS;
                break;
            case EXIT:
                gameShouldRun = false;
                break;
        }
    }
    else if (IsKeyPressed(KEY_ESCAPE))
    {
        gameShouldRun = false;
    }
}

void MenuScreenDraw(void)
{
    DrawText("Start", selectedMenuItem == START ? 110 : 100, 270, 30, BLACK);
    DrawText("Options", selectedMenuItem == OPTIONS ? 110 : 100, 310, 30, BLACK);
    DrawText("Quit", selectedMenuItem == EXIT ? 110 : 100, 350, 30, BLACK);
}
