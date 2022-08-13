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
            context->mouse_position.x = event.motion.x;
            context->mouse_position.y = event.motion.y;
        }

        if(event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
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
                case SDLK_a: {
                    if(event.key.state == SDL_PRESSED) {
                        context->ship_sprite->object->translate(context->ship_sprite->object, (Vec2){-1, 0});
                    }
                    break;
                }
                case SDLK_w: {
                    if(event.key.state == SDL_PRESSED) {
                        context->ship_sprite->object->translate(context->ship_sprite->object, (Vec2){0, -1});
                    }
                    break;
                }
                case SDLK_s: {
                    if(event.key.state == SDL_PRESSED) {
                        context->ship_sprite->object->translate(context->ship_sprite->object, (Vec2){0, 1});
                    }
                    break;
                }
                case SDLK_d: {
                    if(event.key.state == SDL_PRESSED) {
                        context->ship_sprite->object->translate(context->ship_sprite->object, (Vec2){1, 0});
                    }
                    break;
                }
                default:
                    break;
            }
        }
    }
}
