#include "input.h"
#include "types.h"

void handle_input(App *app, GameInputContext *context)
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                app->running = false;
                break;
            default:
                break;
        }

        if(event.type == SDL_MOUSEMOTION) {
            context->mouse_position.x = (float)event.motion.x;
            context->mouse_position.y = (float)event.motion.y;
        }

        if(event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {

            context->ship_control->handle(context->ship_control, &event.key);

            switch(event.key.keysym.sym)
            {
                case SDLK_ESCAPE: {
                    app->running = false;
                    break;
                }
                case SDLK_F5: {
                    if(event.key.state == SDL_PRESSED) {
                        context->ship_animation->start(context->ship_animation);
                    }
                    break;
                }
                case SDLK_F6: {
                    if(event.key.state == SDL_PRESSED) {
                        context->ship_animation->stop(context->ship_animation);
                    }
                    break;
                }
                case SDLK_F7: {
                    if(event.key.state == SDL_PRESSED) {
                        context->show_debug_cross = !context->show_debug_cross;
                    }
                    break;
                }
                case SDLK_F8: {
                    if(event.key.state == SDL_PRESSED) {
                        context->show_debug_grid = !context->show_debug_grid;
                    }
                    break;
                }
                default:
                    break;
            }
        }
    }
}
