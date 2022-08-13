#ifndef SDL2_C17_DRAW_H
#define SDL2_C17_DRAW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "types.h"

void prepare_scene(SDL_Renderer *renderer);
void present_scene(SDL_Renderer *renderer);

void draw_debug_cross(SDL_Renderer *renderer, SDL_Color color);
void draw_debug_grid(SDL_Renderer *renderer, Vec2i size, SDL_Color color);

#endif //SDL2_C17_DRAW_H
