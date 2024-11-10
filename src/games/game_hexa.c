#include "../games.h"
#include "raylib.h"
#include "stddef.h"

void HexaGameDraw(PR_GameTypeData *data, PR_GameConstraints *constraints)
{
    int sideLength = constraints->hexaGame.sideLength;
    for (size_t j = 0; j < sideLength; j++)
    {
        for (size_t i = 0; i < sideLength + j; i++)
        {
            DrawTexturePro(
                cellTex,
                (Rectangle){0, 24, 24, 24},
                (Rectangle){(i * 16) - (8.0 * j), j * 14, 24, 24},
                (Vector2){12, 12}, 0, WHITE);
        }
    }
    for (size_t j = 0; j < sideLength - 1; j++)
    {
        for (size_t i = 0; i < sideLength * 2 - j - 2; i++)
        {
            DrawTexturePro(
                cellTex,
                (Rectangle){0, 24, 24, 24},
                (Rectangle){(i * 16) - (8.0 * (sideLength - j - 2)), j * 14 + sideLength * 14, 24, 24},
                (Vector2){12, 12}, 0, WHITE);
        }
    }
}

void HexaGameGetNeighbors(PR_GameTypeData *data, PR_GameConstraints *constraints, size_t cellIndex)
{
    int    gridLength      = gameParams.hexaGame.sideLength;
    size_t cellIndexInLine = cellIndex;

    int    found   = 0;
    size_t lineIdx = 0;
    size_t prevLen = 0;
    size_t currLen = 0;
    size_t nextLen = 0;

    size_t maxCurrNext;
    size_t maxCurrPrev;

    // Top half
    for (size_t i = 0; i < gridLength; ++i)
    {
        lineIdx++;
        currLen = gridLength + i;
        prevLen = currLen - 1;
        nextLen = currLen + 1;
        if (cellIndexInLine < currLen)
        {
            found = 1;
            break;
        }
        cellIndexInLine -= currLen;
    }

    // Bottom half
    for (size_t i = gridLength - 2; i >= 0 && !found; i--)
    {
        lineIdx++;
        currLen = gridLength + i;
        prevLen = currLen + 1;
        nextLen = currLen - 1;
        if (cellIndexInLine < currLen)
            break;
        cellIndexInLine -= currLen;
    }

    // Exactly in the middle
    if (currLen == (gridLength * 2) - 1)
        prevLen = nextLen = currLen - 1;

    // Clear neighbor buffer
    for (size_t i = 0; i < data->neighborCount; i++)
        data->neighborBuffer[i] = NULL;

    maxCurrNext = (1 + nextLen + currLen) >> 1;
    maxCurrPrev = (1 + prevLen + currLen) >> 1;

    if (cellIndexInLine > 0)
    {
        // W neighbor
        data->neighborBuffer[2] = &data->cells[cellIndex - 1];
        // NW neighbor
        if (lineIdx > 0)
            data->neighborBuffer[0] = &data->cells[cellIndex - maxCurrPrev];
        // NE neighbor
        if (lineIdx < 2 * gridLength - 2)
            data->neighborBuffer[1] = &data->cells[cellIndex - maxCurrPrev + 1];
    }
    else
    {
        // "Top" half
        if (currLen < nextLen)
            data->neighborBuffer[4] = &data->cells[cellIndex + maxCurrNext - 1];
        // "bottom" half
        if (currLen < prevLen)
            data->neighborBuffer[0] = &data->cells[cellIndex - maxCurrPrev];
    }

    if (cellIndexInLine < currLen - 1)
    {
        // E neighbor
        data->neighborBuffer[3] = &data->cells[cellIndex + 1];
        // SW neighbor
        if (lineIdx > 0)
            data->neighborBuffer[4] = &data->cells[cellIndex + maxCurrNext - 1];
        // SE neighbor
        if (lineIdx < 2 * gridLength - 2)
            data->neighborBuffer[5] = &data->cells[cellIndex + maxCurrNext];
    }
    else
    {
        // "Top" half
        if (currLen < nextLen)
            data->neighborBuffer[5] = &data->cells[cellIndex + maxCurrNext];
        // "bottom" half
        if (currLen < prevLen)
            data->neighborBuffer[1] = &data->cells[cellIndex - maxCurrPrev + 1];
    }
}
