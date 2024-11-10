#include "../games.h"
#include "raylib.h"
#include "stddef.h"

void StandardGameDraw(PR_GameTypeData *data, PR_GameConstraints *constraints)
{
    for (size_t j = 0; j < constraints->classicGame.height; j++)
    {
        for (size_t i = 0; i < constraints->classicGame.width; i++)
        {
            DrawTexturePro(
                cellTex,
                (Rectangle){0, 0, 24, 24},
                (Rectangle){i * 15, j * 15, 24, 24},
                (Vector2){12, 12}, 0, WHITE);
        }
    }
}

void StandardGameGetNeighbors(PR_GameTypeData *data, PR_GameConstraints *constraints, size_t cellIndex)
{
    int gridWidth = constraints->classicGame.width;
    int cellX     = cellIndex % gridWidth;

    size_t offsets[] = {-gridWidth - 1, -gridWidth,
                        -gridWidth + 1, -1, 1,
                        gridWidth - 1, gridWidth,
                        gridWidth + 1};

    // This only bound checks y axis
    for (size_t i = 0; i < data->neighborCount; i++)
    {
        size_t idx = offsets[i] + cellIndex;
        if (idx < 0 || idx >= data->cellCount)
            data->neighborBuffer[i] = NULL;
        else
            data->neighborBuffer[i] = &data->cells[idx];
    }

    // Handle neighbors wrapped around on the x axis
    if (cellX == 0)
    {
        data->neighborBuffer[0] = NULL;
        data->neighborBuffer[3] = NULL;
        data->neighborBuffer[5] = NULL;
    }

    if (cellX == gridWidth - 1)
    {
        data->neighborBuffer[2] = NULL;
        data->neighborBuffer[4] = NULL;
        data->neighborBuffer[7] = NULL;
    }
}
