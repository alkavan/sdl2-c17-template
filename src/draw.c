#include "draw.h"

void prepare_scene(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 96, 128, 255, 255);
    SDL_RenderClear(renderer);
}

void present_scene(SDL_Renderer *renderer)
{
    SDL_RenderPresent(renderer);
}

void render_text(SDL_Renderer *renderer, SDL_Surface *text, int x, int y)
{
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, text);
    SDL_Rect dest = {x, y, text->w, text->h};
    SDL_RenderCopy(renderer, texture, NULL, &dest);
    SDL_DestroyTexture(texture);
}
