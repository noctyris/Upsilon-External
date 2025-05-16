#include "inc/runningMode.h"
#include "extapp_api.h"

void handleRunningMode(Cell (*cells)[COLUMNS], Cell (*newCells)[COLUMNS], bool *paused, int *speed, int *nGen, uint64_t *previous_scancode)
{
    uint64_t scancode = extapp_scanKeyboard();
    if (scancode != 0 && scancode != *previous_scancode)
    {
        switch (scancode)
        {
        case SCANCODE_Home:
            *paused = true; // Arrêter la simulation
            return;
        case SCANCODE_Back:
            *paused = true;
            drawCellsMono(cells);
            waitForKeyReleased();
            return;
        case SCANCODE_Plus:
            *speed = (*speed < 5) ? (*speed + 1) : *speed;
            break;
        case SCANCODE_Minus:
            *speed = (*speed > 1) ? (*speed - 1) : *speed;
            break;
        case SCANCODE_Zero:
            initCells(cells);
            *paused = true;
            *speed = 1;
            drawCellsColor(cells);
            break;
        }
    }

    drawCellsColor(cells);

    // Mise à jour des cellules
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
        {
            int aliveNeighbors = countNeighbors(cells, i, j);
            if (cells[(i + ROWS) % ROWS][(j + COLUMNS) % COLUMNS].isAlive)
            {
                newCells[(i + ROWS) % ROWS][(j + COLUMNS) % COLUMNS].isAlive = (aliveNeighbors == 2 || aliveNeighbors == 3);
                newCells[(i + ROWS) % ROWS][(j + COLUMNS) % COLUMNS].nthGen = cells[(i + ROWS) % ROWS][(j + COLUMNS) % COLUMNS].nthGen + 1;
            }
            else
            {
                newCells[(i + ROWS) % ROWS][(j + COLUMNS) % COLUMNS].isAlive = (aliveNeighbors == 3);
                newCells[(i + ROWS) % ROWS][(j + COLUMNS) % COLUMNS].nthGen = 1;
            }
        }
    }

    // Copie des nouvelles cellules dans l'ancien tableau
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
        {
            cells[i][j].isAlive = newCells[i][j].isAlive;
            cells[i][j].nthGen = newCells[i][j].nthGen;
        }
    }

    extapp_msleep(-20 * (*speed) + 100);
    (*nGen)++;

    *previous_scancode = scancode;
}
