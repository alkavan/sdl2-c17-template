#ifndef SDL2_C17_TYPES_H
#define SDL2_C17_TYPES_H

#include <SDL2/SDL.h>
#include <stdbool.h>

typedef struct {
    SDL_Renderer *renderer;
    SDL_Window *window;
    bool is_running;
} App;

#endif //SDL2_C17_TYPES_H
