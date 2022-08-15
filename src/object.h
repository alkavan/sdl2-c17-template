#ifndef SDL2_C17_OBJECT_H
#define SDL2_C17_OBJECT_H

#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

#include "types.h"

struct Object {
    struct {
        void (*set_position)(struct Object *const, Vec2 position);
        void (*set_rotation)(struct Object *const, Mat2 rotation);
        void (*translate)(struct Object *const, Vec2 translation);
        void (*rotate)(struct Object *const, float degrees);
        float (*px)(struct Object *const);
        float (*py)(struct Object *const);
    };

    Vec2 position;
    Mat2 rotation;
};

typedef struct Object Object;

Object *object_new();
void object_free(Object *t);

#endif //SDL2_C17_OBJECT_H
