#include "types.h"
#include "init.h"
#include "input.h"
#include "draw.h"
#include "utility.h"

int main()
{
    App app = {NULL, NULL, true};

    // init game application
    int init_code = init(&app, "Da Game");

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
        quit(&app);
        return EXIT_FAILURE;
    }

    // create texture
    SDL_Texture* tex = SDL_CreateTextureFromSurface(app.renderer, bmp);
    if (tex == NULL) {
        fprintf(stderr, "SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());

        SDL_FreeSurface(bmp);
        quit(&app);

        return EXIT_FAILURE;
    }
    SDL_FreeSurface(bmp);

    SDL_Surface* text;
    SDL_Color font_color = {255, 0, 0 };

    float last_fps = 0.0f;
    char fps_string[32];
    Uint64 frame_count = 0;
    Uint32 tick_count = 0;

    // render loop
    while (1)
    {
        // profile start
        Uint64 start = SDL_GetPerformanceCounter();

        // handle input
        handle_input(&app);

        if(app.is_running == false) {
            break;
        }

        // update scene
        sprintf(fps_string, "FPS: %.2f (%lu frames, %u ticks)", last_fps, frame_count, tick_count);
        update_text(fps_string, &text, font, font_color);

        // prepare and clear scene
        prepare_scene(app.renderer);

        // draw to back-buffer
        SDL_RenderCopy(app.renderer, tex, NULL, NULL);
        render_text(app.renderer, text);

        // present scene
        present_scene(app.renderer);
        msleep(10);

        // profile end
        Uint64 end = SDL_GetPerformanceCounter();

        // cap to 60fps
        SDL_Delay(get_frame_delay(start, end));
        last_fps = get_fps(start, end);
        frame_count++;
        tick_count = SDL_GetTicks();
    }

    // clean up
    SDL_DestroyTexture(tex);
    quit(&app);

    return EXIT_SUCCESS;
}
