#ifndef SDL2_C17_IMAGE_H
#define SDL2_C17_IMAGE_H

#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_render.h>

typedef enum ImageLoader {
    PNG_LOADER = 1,
    JPG_LOADER = 2,
    BMP_LOADER = 3,
} ImageLoader;

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

Image *image_new(int x, int y, const char* filename, ImageLoader loader);
void image_free(Image *t);

#endif //SDL2_C17_IMAGE_H
