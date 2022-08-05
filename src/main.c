#include <version_config.h>

#include "config.h"
#include "input.h"
#include "draw.h"
#include "app.h"
#include "timer.h"
#include "profile.h"
#include "text.h"
#include "image.h"

typedef struct {
    char fps[255];
    char pref[255];
} TextRender;

int main()
{
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "loading ... %s %s", PROJECT_NAME, PROJECT_VERSION);

    // create application object
    App* app = app_new();

    // init game application
    int init_code = app_init(app, "SDL2 C17 Example", PROJECT_VERSION,
                             SCREEN_WIDTH, SCREEN_HEIGHT);

    // if application failed to load exit
    if(init_code != 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "failed to create application (code: %d)", init_code);
        return init_code;
    }

    // load font
    TTF_Font* font = TTF_OpenFont("../res/Ac437_ATI_8x8.ttf", FONT_DEFAULT_SIZE);
    if ( ! font) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "failed to create font (%s)", TTF_GetError());
        return EXIT_FAILURE;
    }

    // load background image
    Image* bg_image = image_new(0, 0, "../res/grumpy-cat.bmp");
    if (bg_image == NULL) {
        app_quit(app);
        return EXIT_FAILURE;
    }

    Text* fps_text = text_new(10, 10, font);
    Text* pref_text = text_new(10, 10+get_line_height(), font);

    TextRender text_render = {"", ""};
    SDL_Color font_color = {255, 0, 0 };

    // create profile object
    Profile* profile = profile_new(true);

    // initialize profiler and start fps timer
    profile->init(profile);

    // render loop
    while (app->running)
    {
        // start profile session
        profile->start(profile);

        // handle input
        handle_input(app);

        // calculate current fps after handling input
        profile->update(profile);

        // update scene
        sprintf(text_render.fps, "FPS: %.2f", profile->currentFps);
        fps_text->update(fps_text, text_render.fps, font_color);

        sprintf(text_render.pref, "Pref: %lu", profile->performanceCount);
        pref_text->update(pref_text, text_render.pref, font_color);

        // prepare and clear scene
        prepare_scene(app->renderer);

        // render background image
        bg_image->render(bg_image, app->renderer);

        // render texts
        fps_text->render(fps_text, app->renderer);
        pref_text->render(pref_text, app->renderer);

        // present scene
        present_scene(app->renderer);

        // finish profile session
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
    profile_free(profile);
    text_free(fps_text);
    text_free(pref_text);
    image_free(bg_image);
    app_quit(app);

    return EXIT_SUCCESS;
}
