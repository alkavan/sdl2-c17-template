#ifndef SDL2_C17_APP_H
#define SDL2_C17_APP_H

#include <stdbool.h>
#include <SDL2/SDL.h>

struct App {
    SDL_Renderer *renderer;
    SDL_Window *window;
    bool running;
    char window_title[255];
};

typedef struct App App;

App *app_new();
void app_free(App *t);

int app_init(App * app, const char* title, const char* version, int32_t width, int32_t height);
void app_quit(App *app);

#endif //SDL2_C17_APP_H
