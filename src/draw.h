#ifndef SDL2_C17_DRAW_H
#define SDL2_C17_DRAW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

void prepare_scene(SDL_Renderer *renderer);
void present_scene(SDL_Renderer *renderer);

void render_text(SDL_Renderer *renderer, SDL_Surface *text);

#endif //SDL2_C17_DRAW_H
