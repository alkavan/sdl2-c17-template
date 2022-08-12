#ifndef SDL2_C17_IMAGE_H
#define SDL2_C17_IMAGE_H

#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_render.h>

struct Image {
    struct {
        void (*update)(struct Image *const, int x, int y);
        void (*render)(struct Image *const, SDL_Renderer *renderer);
    };

    SDL_Point position;
    SDL_Surface* surface;
    SDL_Texture* texture;
};

typedef struct Image Image;

Image *image_new(int x, int y, SDL_Surface *surface);
void image_free(Image *t);

#endif //SDL2_C17_IMAGE_H
