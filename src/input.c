#include "input.h"

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

        switch(event.key.keysym.sym)
        {
            case SDLK_ESCAPE:
                app->running = false;
                break;
            case SDLK_F5:
                context->ship_animation->start(context->ship_animation);
                break;
            case SDLK_F6:
                context->ship_animation->stop(context->ship_animation);
                break;
            case SDLK_a: {
                int x = context->ship_sprite->position.x;
                int y = context->ship_sprite->position.y;
                context->ship_sprite->update(context->ship_sprite, x-1, y);
                break;
            }

            case SDLK_w: {
                int x = context->ship_sprite->position.x;
                int y = context->ship_sprite->position.y;
                context->ship_sprite->update(context->ship_sprite, x, y-1);
                break;
            }
            case SDLK_s: {
                int x = context->ship_sprite->position.x;
                int y = context->ship_sprite->position.y;
                context->ship_sprite->update(context->ship_sprite, x, y+1);
                break;
            }
            case SDLK_d: {
                int x = context->ship_sprite->position.x;
                int y = context->ship_sprite->position.y;
                context->ship_sprite->update(context->ship_sprite, x+1, y);
                break;
            }
            default:
                break;
        }
    }
}