#include "input.h"
#include "draw.h"
#include "utility.h"
#include "app.h"
#include "timer.h"
#include "config.h"

int main()
{
    App* app = app_new();

    // init game application
    int init_code = app_init(app, "SDL2 C17 Example", SCREEN_WIDTH, SCREEN_HEIGHT);

    if(init_code != 0) {
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        return init_code;
    }

    // load font
    TTF_Font* font = TTF_OpenFont("../res/Ac437_ATI_8x8.ttf", 12);
    if (!font) {
        fprintf(stderr, "TTF_OpenFont Error: %s\n", TTF_GetError());
        return EXIT_FAILURE;
    }

    // load image
    SDL_Surface* bmp = SDL_LoadBMP("../res/grumpy-cat.bmp");
    if (bmp == NULL) {
        fprintf(stderr, "SDL_LoadBMP Error: %s\n", SDL_GetError());
        app_quit(app);
        return EXIT_FAILURE;
    }

    // create texture
    SDL_Texture* tex = SDL_CreateTextureFromSurface(app->renderer, bmp);
    if (tex == NULL) {
        fprintf(stderr, "SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());

        SDL_FreeSurface(bmp);
        app_quit(app);

        return EXIT_FAILURE;
    }
    SDL_FreeSurface(bmp);

    SDL_Surface* text;
    SDL_Color font_color = {255, 0, 0 };

    char fps_string[32];

    // frames per second timer
    Timer* fps_timer = timer_new();

    // frames per second cap timer
    Timer* cap_timer = timer_new();

    //Start counting frames per second
    int counted_frames = 0;
    fps_timer->start(fps_timer);

    // render loop
    while (app->running)
    {
        // start cap timer
        cap_timer->start(cap_timer);

        // profile start
//        Uint64 start = SDL_GetPerformanceCounter();

        // handle input
        handle_input(app);

        // calculate and correct fps
        float avg_fps = counted_frames / (fps_timer->getTicks(fps_timer) / 1000.f );
        if(avg_fps > 2000000.0f)
        {
            avg_fps = 0;
        }

        // update scene
        sprintf(fps_string, "FPS: %.2f", avg_fps);
        update_text(fps_string, &text, font, font_color);

        // prepare and clear scene
        prepare_scene(app->renderer);

        // draw to back-buffer
        SDL_RenderCopy(app->renderer, tex, NULL, NULL);
        render_text(app->renderer, text);

        // present scene
        present_scene(app->renderer);

        // profile end
//        Uint64 end = SDL_GetPerformanceCounter();

        ++counted_frames;

        // if frame finished early
        Uint32 frameTicks = cap_timer->getTicks(cap_timer);
        if( frameTicks < SCREEN_TICKS_PER_FRAME )
        {
            // wait remaining time
            SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
        }
    }

    // clean up
    SDL_DestroyTexture(tex);
    app_quit(app);

    return EXIT_SUCCESS;
}
