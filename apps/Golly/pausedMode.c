#include "inc/pausedMode.h"
#include "extapp_api.h"

// Gestion du mode édition (paused)
void handlePausedMode(Cell (*cells)[COLUMNS], coord_t *coord, bool *running, bool *paused, int *speed, bool *isEditingWorld, uint64_t *previous_scancode)
{
    uint64_t scancode = extapp_scanKeyboard();
    if (*previous_scancode != scancode && scancode != 0)
    {
        switch (scancode)
        {
        case SCANCODE_Home:
            *running = false; // Quitter le programme
            return;
        case SCANCODE_Back:
            *paused = false; // Démarrer la simulation
            break;
        case SCANCODE_Left:
            coord->x = (coord->x - 1 + ROWS) % ROWS;
            drawCellsMono(cells);
            drawCursor(cells, *coord);
            break;
        case SCANCODE_Right:
            coord->x = (coord->x + 1) % ROWS;
            drawCellsMono(cells);
            drawCursor(cells, *coord);
            break;
        case SCANCODE_Up:
            coord->y = (coord->y - 1 + COLUMNS) % COLUMNS;
            drawCellsMono(cells);
            drawCursor(cells, *coord);
            break;
        case SCANCODE_Down:
            coord->y = (coord->y + 1) % COLUMNS;
            drawCellsMono(cells);
            drawCursor(cells, *coord);
            break;
        case SCANCODE_OK:
            cells[coord->x][coord->y].isAlive = !cells[coord->x][coord->y].isAlive;
            cells[coord->x][coord->y].nthGen = cells[coord->x][coord->y].isAlive ? 1 : 0;
            drawCellsMono(cells);
            drawCursor(cells, *coord);
            break;
        case SCANCODE_Zero:
            initCells(cells);
            drawCellsMono(cells);
            drawCursor(cells, *coord);
            *coord = (coord_t){0, 0};
            *speed = 1;
            break;
        case SCANCODE_Toolbox:
            *isEditingWorld = true;
            break;
        }
    }
    *previous_scancode = scancode;

    extapp_msleep(20);
}

void handleEditingWorld(Cell (*cells)[COLUMNS], coord_t *coord, bool *running, bool *paused, int *speed, bool *isEditingWorld, uint64_t *previous_scancode)
{
    /**
     * @brief Fonction de gestion du mode édition (Toolbox)
     * Paramètres modifiables :
     * - type de monde (fermé, torique, etc.)
     * - règles de vie (règles de Conway, etc.)
     * - nombre maximal pour le calcul de couleurs
    */
    uint64_t scancode = extapp_scanKeyboard();
    if (*previous_scancode != scancode && scancode != 0)
    {
        switch (scancode)
        {
        case SCANCODE_Home:
            *running = false; // Quitter le programme
            return;
        case SCANCODE_Back:
            *paused = true; // Démarrer la simulation
            *isEditingWorld = false;
            break;
        case SCANCODE_Toolbox:
            *isEditingWorld = false;
            break;
        }
        *previous_scancode = scancode;

        extapp_msleep(20);
    }
}