#include <SDL2/SDL_log.h>
#include <SDL2/SDL_image.h>
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

Image *image_new(int x, int y, const char* filename, ImageLoader loader) {
    Image *image = (Image*) malloc(sizeof(Image));

    image->update = &update;
    image->render = &render;

    SDL_Point position = {x, y};
    image->position = position;

    switch (loader) {
        case PNG_LOADER: {
            image->surface = IMG_Load(filename);
            break;
        }
        case JPG_LOADER: {
            image->surface = IMG_Load(filename);
            break;
        }
        case BMP_LOADER: {
            image->surface = SDL_LoadBMP(filename);
            break;
        }
    }



    if (image->surface == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "failed to load bitmap (%s)", SDL_GetError());
        return NULL;
    }

    return image;
}

void image_free(Image *t) {
    SDL_FreeSurface(t->surface);
    SDL_DestroyTexture(t->texture);
    free(t);
}
