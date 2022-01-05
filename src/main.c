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

    // render loop
    while (1)
    {
        Uint64 start = SDL_GetPerformanceCounter();

        //////////
        prepare_scene(app.renderer);

        handle_input(&app);

        if(app.is_running == false) {
            break;
        }

        present_scene(app.renderer, tex);
        //////////

        Uint64 end = SDL_GetPerformanceCounter();
        // cap to 60fps
        SDL_Delay(get_frame_delay(start, end));
    }

    // clean up
    SDL_DestroyTexture(tex);
    quit(&app);

    return EXIT_SUCCESS;
}
