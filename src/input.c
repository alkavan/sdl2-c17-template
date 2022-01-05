#include "input.h"

void handle_input(App *app)
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                app->is_running = false;
                break;
            default:
                break;
        }

        switch(event.key.keysym.sym)
        {
            case SDLK_ESCAPE:
                app->is_running = false;
                break;
            default:
                break;
        }
    }
}