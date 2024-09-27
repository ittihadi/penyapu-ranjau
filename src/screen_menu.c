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

static int selectedMenuItem = START;

void MenuScreenLoad(void) {}
void MenuScreenUnload(void) {}

void MenuScreenUpdate(void)
{
    // Very rough wraparound code, fix later
    if (IsKeyPressed(KEY_DOWN))
    {
        selectedMenuItem = (selectedMenuItem + 1) % MENU_ITEM_COUNT;
    }
    else if (IsKeyPressed(KEY_UP))
    {
        selectedMenuItem--;
        if (selectedMenuItem < 0)
            selectedMenuItem += MENU_ITEM_COUNT;
    }
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
    // draw menu
    int selectedItemX = 110;

    DrawText("Start", selectedMenuItem == START ? selectedItemX : 100, 270, 30, BLACK);
    DrawText("Options", selectedMenuItem == OPTIONS ? selectedItemX : 100, 310, 30, BLACK);
    DrawText("Quit", selectedMenuItem == EXIT ? selectedItemX : 100, 350, 30, BLACK);
}
