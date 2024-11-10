/*******************************************************************************************
 *
 *   raylib game template
 *
 *   Penyapu Ranjau
 *   A collection of minesweeper-type games
 *
 *   This game has been created using raylib (www.raylib.com)
 *   raylib is licensed under an unmodified zlib/libpng license (View raylib.h *for details)
 *
 *   Copyright (c) 2021 Ramon Santamaria (@raysan5)
 *
 ********************************************************************************************/

#include <stdio.h>

#include "globals.h"
#include "options.h"
#include "raylib.h"
#include "screens/screens.h"

//----------------------------------------------------------------------------------
// Shared Variables Definition (global)
//----------------------------------------------------------------------------------
PR_Screen currentScreen = SCREEN_MENU;
PR_Screen nextScreen    = SCREEN_MENU;

int gameShouldRun = true;

//----------------------------------------------------------------------------------
// Local Variables Definition (local to this module)
//----------------------------------------------------------------------------------
static const int screenWidth  = 800;
static const int screenHeight = 450;

//----------------------------------------------------------------------------------
// Local Functions Declaration
//----------------------------------------------------------------------------------
static void UpdateDrawFrame(void);        // Update and draw one frame
static void SwitchToNextScreen(void);     // Switch to next screen in queue
// TODO: maybe transition (fade/sweep) function here? for now instant transition
// works fine

//----------------------------------------------------------------------------------
// Main entry point
//----------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //---------------------------------------------------------
    ChangeDirectory(GetApplicationDirectory());

    LoadOptions();

    InitWindow(screenWidth, screenHeight, "Penyapu Ranjau");
    SetExitKey(KEY_NULL);

    // Set to fullscreen based on option
    if (isFullscreen) ToggleFullscreen();

    InitAudioDevice();     // Initialize audio device
    SetMasterVolume(masterVolume);

    MenuScreenLoad();

    SetTargetFPS(60);     // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose() && gameShouldRun)     // Detect window close button or ESC key
    {
        UpdateDrawFrame();
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    // Unload current screen data before closing
    switch (currentScreen)
    {
        case SCREEN_MENU:
            MenuScreenUnload();
            break;
        case SCREEN_OPTIONS:
            OptionsScreenUnload();
            break;
        case SCREEN_GAMESELECT:
            GameSelectScreenUnload();
            break;
        case SCREEN_GAME:
            GameScreenUnload();
            break;
    }

    CloseAudioDevice();     // Close audio context

    CloseWindow();     // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

//----------------------------------------------------------------------------------
// Module specific Functions Definition
//----------------------------------------------------------------------------------
// Switch to next screen in queue
static void SwitchToNextScreen(void)
{
    // Add some deinitialization of heavy screen specific data here
    switch (currentScreen)
    {
        case SCREEN_MENU:
            MenuScreenUnload();
            break;
        case SCREEN_OPTIONS:
            OptionsScreenUnload();
            break;
        case SCREEN_GAMESELECT:
            GameSelectScreenUnload();
            break;
        case SCREEN_GAME:
            GameScreenUnload();
            break;
    }

    currentScreen = nextScreen;

    switch (currentScreen)
    {
        case SCREEN_MENU:
            MenuScreenLoad();
            break;
        case SCREEN_OPTIONS:
            OptionsScreenLoad();
            break;
        case SCREEN_GAMESELECT:
            GameSelectScreenLoad();
            break;
        case SCREEN_GAME:
            GameScreenLoad();
            break;
    }
}

// Update and draw game frame
static void UpdateDrawFrame(void)
{
    // Update
    //----------------------------------------------------------------------------------
    if (nextScreen != currentScreen)
    {
        SwitchToNextScreen();
    }

    switch (currentScreen)
    {
        case SCREEN_MENU:
            MenuScreenUpdate();
            break;
        case SCREEN_GAMESELECT:
            GameSelectScreenUpdate();
            break;
        case SCREEN_GAME:
            GameScreenUpdate();
            break;
        case SCREEN_OPTIONS:
            OptionsScreenUpdate();
            break;
    }
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

    ClearBackground(RAYWHITE);
    // Draw menu scene
    switch (currentScreen)
    {
        case SCREEN_MENU:
            MenuScreenDraw();
            break;
        case SCREEN_GAMESELECT:
            GameSelectScreenDraw();
            break;
        case SCREEN_GAME:
            GameScreenDraw();
            break;
        case SCREEN_OPTIONS:
            OptionsScreenDraw();
            break;
    }

    EndDrawing();
    //----------------------------------------------------------------------------------
}
