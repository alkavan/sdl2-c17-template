#include "draw.h"

void prepare_scene(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 96, 128, 255, 255);
    SDL_RenderClear(renderer);
}

void present_scene(SDL_Renderer *renderer, SDL_Texture *texture)
{
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}
