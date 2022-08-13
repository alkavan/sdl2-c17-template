#include <SDL2/SDL_log.h>
#include "image.h"

static void update(Image *const t) {

}

static void render(Image *const t, SDL_Renderer *renderer) {
    if( ! t->texture) {
        t->texture = SDL_CreateTextureFromSurface(renderer, t->surface);
        if (t->texture == NULL) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "failed to create texture (%s)", SDL_GetError());
            return;
        }
    }

    const SDL_Rect dest_rect = {
            (int)t->object->position.x,
            (int)t->object->position.y,
            t->surface->w,
            t->surface->h
    };

    SDL_RenderCopy(renderer, t->texture, NULL, &dest_rect);
}

Image *image_new(Vec2 position, SDL_Surface *const surface) {
    Image *image = (Image*) malloc(sizeof(Image));

    image->update = &update;
    image->render = &render;

    Object* object = object_new();
    object->set_position(object, position);
    image->object = object;

    if (surface == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "null surface, unable to create Image{}");
        return NULL;
    }
    image->surface = surface;
    image->texture = NULL;

    return image;
}

void image_free(Image *t) {
    object_free(t->object);
    SDL_FreeSurface(t->surface);
    SDL_DestroyTexture(t->texture);
    free(t);
}