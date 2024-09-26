#pragma once

typedef enum PR_Screen {
    SCREEN_MENU,
    SCREEN_OPTIONS,
    SCREEN_GAMESELECT,
    SCREEN_GAME,
} PR_Screen;

extern PR_Screen currentScreen;
extern PR_Screen nextScreen;

void MenuScreenUpdate(void);
void MenuScreenDraw(void);

void OptionsScreenUpdate(void);
void OptionsScreenDraw(void);

void GameSelectScreenUpdate(void);
void GameSelectScreenDraw(void);

// This might need to be changed to function pointers
void GameScreenUpdate(void);
void GameScreenDraw(void);
