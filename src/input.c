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
                context->ship_sprite->object->translate(context->ship_sprite->object, (Vec2){-1, 0});
                break;
            }
            case SDLK_w: {
                context->ship_sprite->object->translate(context->ship_sprite->object, (Vec2){0, -1});
                break;
            }
            case SDLK_s: {
                context->ship_sprite->object->translate(context->ship_sprite->object, (Vec2){0, 1});
                break;
            }
            case SDLK_d: {
                context->ship_sprite->object->translate(context->ship_sprite->object, (Vec2){1, 0});
                break;
            }
            default:
                break;
        }
    }
}