#include "inc/planets.h"

/**
 * display_planets : drawplanets from a given array of planets and its count
 * @param planets Dynamically allocated array of planets
 * @param planet_count Number of planets in the array
*/
void display_planets(planet_t *planets, int planet_count) {
    for (int i = 0; i < planet_count; i++) {
        char *text;
        sprintf(text, "%s  %.3ekg  %dkm  (%d, %d)", planets[i].name, planets[i].mass, planets[i].radius, planets[i].position.x, planets[i].position.y);
        extapp_drawTextSmall(text, 0, i * 12, 0xFFFF, 0, 0);
    }
}