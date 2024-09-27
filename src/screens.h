#pragma once

typedef enum PR_Screen {
    SCREEN_MENU,
    SCREEN_OPTIONS,
    SCREEN_GAMESELECT,
    SCREEN_GAME,
} PR_Screen;

extern PR_Screen currentScreen;
extern PR_Screen nextScreen;

void MenuScreenLoad(void);
void MenuScreenUnload(void);
void MenuScreenUpdate(void);
void MenuScreenDraw(void);

void OptionsScreenLoad(void);
void OptionsScreenUnload(void);
void OptionsScreenUpdate(void);
void OptionsScreenDraw(void);

void GameSelectScreenLoad(void);
void GameSelectScreenUnload(void);
void GameSelectScreenUpdate(void);
void GameSelectScreenDraw(void);

// This might need to be changed to function pointers
void GameScreenLoad(void);
void GameScreenUnload(void);
void GameScreenUpdate(void);
void GameScreenDraw(void);
