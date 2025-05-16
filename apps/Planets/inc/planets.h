#ifndef PLANETS_H
#define PLANETS_H

#include "extapp_api.h"
#include <stdio.h>

typedef struct {
    float x; // x-coordinate in space
    float y; // y-coordinate in space
} pos_t;

typedef struct {
    char name[20];
    float mass; // in kg
    float radius; // in km
    pos_t position; // position in space
    float velocity; // in km/s
    float move_angle; // angle of movement in degrees
} planet_t;

void display_planets(planet_t *planets, int planet_count);

#endif