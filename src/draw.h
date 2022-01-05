#ifndef SDL2_C17_DRAW_H
#define SDL2_C17_DRAW_H

#include <SDL2/SDL.h>

#include "types.h"

void prepare_scene(SDL_Renderer *renderer);
void present_scene(SDL_Renderer *renderer, SDL_Texture *texture);

#endif //SDL2_C17_DRAW_H
