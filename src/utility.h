#ifndef SDL2_C17_UTILITY_H
#define SDL2_C17_UTILITY_H

#include <SDL2/SDL_surface.h>
#include <stdbool.h>

void load_image(SDL_Surface **surface, const char* filename);
void load_bitmap(SDL_Surface **surface, const char* filename);
bool is_fraction(double f);

#endif //SDL2_C17_UTILITY_H
