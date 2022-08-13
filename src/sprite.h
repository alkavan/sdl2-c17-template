#ifndef SDL2_C17_SPRITE_H
#define SDL2_C17_SPRITE_H

#include <SDL2/SDL_render.h>
#include "object.h"
#include "types.h"

struct Sprite {
    struct {
        void (*update)(struct Sprite *const);
        void (*render)(struct Sprite *const, SDL_Renderer *renderer);
        void (*next)(struct Sprite *const);
    };

    Object* object;
    SDL_Surface* surface;
    SDL_Texture* texture;
    int frame_index;
    Vec2i frame_size;
    Vec2i grid;
};

typedef struct Sprite Sprite;

Sprite *sprite_new(Vec2 position, Vec2i frame_size, SDL_Surface *surface);
void sprite_free(Sprite *t);

#endif //SDL2_C17_SPRITE_H
