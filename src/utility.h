#ifndef SDL2_C17_UTILITY_H
#define SDL2_C17_UTILITY_H

#include <SDL2/SDL_surface.h>
#include <stdbool.h>
#include "types.h"

void load_image(SDL_Surface **surface, const char* filename);
void load_bitmap(SDL_Surface **surface, const char* filename);
bool is_fraction(double f);

double vec2_to_rad(Vec2 v);
double vec2_to_deg(Vec2 v);
double mat2_to_rad(Mat2 m);
double mat2_to_deg(Mat2 m);

Vec2 relative_mouse_position(Vec2 mouse_position, Vec2 object_position);

#endif //SDL2_C17_UTILITY_H
