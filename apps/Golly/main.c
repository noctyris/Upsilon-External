#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "extapp_api.h"

#include "inc/peripherals.h"
#include "inc/pausedMode.h"
#include "inc/runningMode.h"

void extapp_main(void)
{
    waitForKeyReleased();
    clearscreen();

    bool running = true;
    bool paused = true;
    bool isEditingWorld = false;
    int nGen = 0;
    int speed = 1;
    coord_t coord = {ROWS/2, COLUMNS/2};
    uint64_t previous_scancode = 0;

    Cell(*cells)[COLUMNS] = malloc(ROWS * sizeof(*cells));
    Cell(*newCells)[COLUMNS] = malloc(ROWS * sizeof(*newCells));

    if (!cells || !newCells) return;

    initCells(cells);

    // for (int i = 0; i < 500; i++)
    // {
    //     int x = rand() % ROWS;
    //     int y = rand() % COLUMNS;
    //     cells[x][y].isAlive = true;
    // }

    drawCellsColor(cells);
    drawCursor(cells, coord);

    while (running)
    {
        if (!paused && !isEditingWorld) handleRunningMode(cells, newCells, &paused, &speed, &nGen, &previous_scancode);
        else if (paused && !isEditingWorld) handlePausedMode(cells, &coord, &running, &paused, &speed, &isEditingWorld, &previous_scancode);
        else if (paused && isEditingWorld) handleEditingWorld(cells, &coord, &running, &paused, &speed, &isEditingWorld, &previous_scancode);
    }

    free(cells);
    free(newCells);

    return;
}
