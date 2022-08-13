#ifndef SDL2_C17_CONTROL_H
#define SDL2_C17_CONTROL_H

#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

struct Control {
    struct {
        void (*update)(struct Control *const, int x, int y);
        void (*render)(struct Control *const, SDL_Renderer *renderer);
    };

    SDL_Point position;
};

typedef struct Control Control;

Control *control_new();
void control_free(Control *t);

#endif //SDL2_C17_CONTROL_H
