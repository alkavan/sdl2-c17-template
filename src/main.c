#include "config.h"
#include "input.h"
#include "draw.h"
#include "utility.h"
#include "app.h"
#include "timer.h"
#include "profile.h"

int main()
{
    App* app = app_new();

    // init game application
    int init_code = app_init(app, "SDL2 C17 Example", SCREEN_WIDTH, SCREEN_HEIGHT);

    if(init_code != 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "failed to create application (code: %d)", init_code);
        return init_code;
    }

    // load font
    TTF_Font* font = TTF_OpenFont("../res/Ac437_ATI_8x8.ttf", FONT_DEFAULT_SIZE);
    if (!font) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "failed to create font (%s)", TTF_GetError());
        return EXIT_FAILURE;
    }

    // load image
    SDL_Surface* bmp = SDL_LoadBMP("../res/grumpy-cat.bmp");
    if (bmp == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "failed to load bitmap (%s)", SDL_GetError());
        app_quit(app);
        return EXIT_FAILURE;
    }

    // create texture
    SDL_Texture* texture = SDL_CreateTextureFromSurface(app->renderer, bmp);
    if (texture == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "failed to create texture (%s)", SDL_GetError());
        SDL_FreeSurface(bmp);
        app_quit(app);

        return EXIT_FAILURE;
    }
    SDL_FreeSurface(bmp);

    SDL_Surface* fps_text;
    SDL_Surface* pref_text;
    SDL_Color font_color = {255, 0, 0 };

    char fps_string[32];
    char pref_string[32];

    // create profile object
    Profile* profile = profile_new(true);

    // initialize profiler and start fps timer
    profile->init(profile);

    // render loop
    while (app->running)
    {
        profile->start(profile);

        // handle input
        handle_input(app);

        profile->update(profile);

        // update scene
        sprintf(fps_string, "FPS: %.2f", profile->currentFps);
        update_text(fps_string, &fps_text, font, font_color);

        sprintf(pref_string, "Pref: %lu", profile->performanceCount);
        update_text(pref_string, &pref_text, font, font_color);

        // prepare and clear scene
        prepare_scene(app->renderer);

        // draw to back-buffer
        SDL_RenderCopy(app->renderer, texture, NULL, NULL);

        render_text(app->renderer, fps_text, 10, 10);
        render_text(app->renderer, pref_text, 10, 10+get_line_height());

        // present scene
        present_scene(app->renderer);

        profile->end(profile);

        // if frame finished early
        Uint32 frameTicks = profile->getFrameTicks(profile);
        if(frameTicks < SCREEN_TICKS_PER_FRAME)
        {
            // wait remaining time
            SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
        }
    }

    // clean up
    SDL_DestroyTexture(texture);
    profile_free(profile);
    app_quit(app);

    return EXIT_SUCCESS;
}
