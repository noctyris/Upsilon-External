#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "extapp_api.h"

#include "inc/peripherals.h"
#include "inc/planets.h"

void extapp_main(void) {
    waitForKeyReleased();
    
    init_display();

    planet_t *planets = (planet_t *)malloc(sizeof(planet_t) * 10);
    int planet_count = 0;
    if (planets == NULL) {
        return;
    }

    bool running = true;

    planets[0] = (planet_t){.name = "Earth", .mass = 5.972e24, .radius = 6371, .position = {0, 0}, .velocity = 29.78, .move_angle = 0};
    planet_count++;

    while (running) {
        uint64_t scancode = extapp_scanKeyboard();
        switch (scancode)
        {
        case SCANCODE_Home:
            running = false;
            break;
        case SCANCODE_Plus:
            planet_t new_planet;
            snprintf(new_planet.name, sizeof(new_planet.name), "Planet %d", rand() % 100);
            new_planet.mass = (float)(rand() % 1000 + 1);
            new_planet.radius = (float)(rand() % 100 + 1);
            new_planet.position.x = (float)(rand() % 320);
            new_planet.position.y = (float)(rand() % 240);
            new_planet.velocity = (float)(rand() % 100 + 1);
            new_planet.move_angle = (float)(rand() % 360);
            planets[planet_count] = new_planet;
            waitForKeyReleased();
            break;
        
        default:
            break;
        }
        display_planets(planets, planet_count);
    }

    
    waitForKeyPressed();
    waitForKeyReleased();

    return;
}
