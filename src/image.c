#include <SDL2/SDL_log.h>
#include "image.h"

static void update(Image *const t, int x, int y) {
    t->position.x = x;
    t->position.y = y;
}

static void render(Image *const t, SDL_Renderer *renderer) {
    if( ! t->texture) {
        t->texture = SDL_CreateTextureFromSurface(renderer, t->surface);
        if (t->texture == NULL) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "failed to create texture (%s)", SDL_GetError());
            return;
        }
    }

    SDL_RenderCopy(renderer, t->texture, NULL, NULL);
}

Image *image_new(int x, int y, SDL_Surface *const surface) {
    Image *image = (Image*) malloc(sizeof(Image));

    image->update = &update;
    image->render = &render;

    SDL_Point position = {x, y};
    image->position = position;

    if (surface == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "null surface, unable to create Image{}");
        return NULL;
    }
    image->surface = surface;
    image->texture = NULL;

    return image;
}

void image_free(Image *t) {
    SDL_FreeSurface(t->surface);
    SDL_DestroyTexture(t->texture);
    free(t);
}
