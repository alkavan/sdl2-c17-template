#ifndef SDL2_C17_SPRITE_H
#define SDL2_C17_SPRITE_H

#include <SDL2/SDL_render.h>
#include <mathc.h>

struct Sprite {
    struct {
        void (*update)(struct Sprite *const, int x, int y);
        void (*render)(struct Sprite *const, SDL_Renderer *renderer);
        void (*next)(struct Sprite *const);
    };

    SDL_Point position;
    SDL_Surface* surface;
    SDL_Texture* texture;
    int frame_index;
    struct vec2i frame_size;
    struct vec2i grid;
};

typedef struct Sprite Sprite;

Sprite *sprite_new(int x, int y, int w, int h, SDL_Surface *surface);
void sprite_free(Sprite *t);

#endif //SDL2_C17_SPRITE_H
