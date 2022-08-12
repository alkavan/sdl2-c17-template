#include <version_config.h>

#include "config.h"
#include "context.h"
#include "input.h"
#include "draw.h"
#include "app.h"
#include "timer.h"
#include "profile.h"
#include "text.h"
#include "image.h"
#include "sprite.h"
#include "animation.h"
#include "utility.h"

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
    SDL_Surface *surface_bg = NULL;
    load_image(&surface_bg, "../res/galaxy-purple_1280x720.jpg");

    // load ship sprite image
    SDL_Surface *surface_ship = NULL;
    load_image(&surface_ship, "../res/ship1.png");

    // load solid tiles image
    SDL_Surface *surface_solid_tiles = NULL;
    load_bitmap(&surface_solid_tiles, "../res/solid-tileset.bmp");

    // create background image
    Image* img_background = image_new(0, 0, surface_bg);
    if (img_background == NULL) {
        app_quit(app);
        return EXIT_FAILURE;
    }

    // create ship sprite
    Sprite* ship_sprite = sprite_new(SCREEN_HALF_WIDTH, SCREEN_HALF_HEIGHT, 32, 32, surface_ship);

    // create solid tileset sprite
    Sprite* solid_tiles_sprite = sprite_new(
            SCREEN_HALF_WIDTH-100, SCREEN_HALF_HEIGHT-100, 16, 16, surface_solid_tiles);

    // animations
    Animation* ship_animation = animation_new(25, true);
    Animation* tiles_animation = animation_new(100, true);

    // create text objects
    Text* fps_text = text_new(10, 10, font);
    Text* pref_text = text_new(10, 10+get_line_height(), font);
    Text* help_text = text_new(10, SCREEN_HEIGHT-get_line_height()-10, font);

    TextRenderContext text_render_context = {
            .fps="",
            .pref="",
            .help="use AWSD keys to move ship, F5/F6 to start/stop animation, ESC to quit!"
    };

    SDL_Color color_red = {255, 0, 0 };
    SDL_Color color_white = {255, 255, 255 };

    // initialize context objects
    GameInputContext input_context = (GameInputContext){ship_sprite, ship_animation};

    // create profile object
    Profile* profile = profile_new(true);

    // initialize profiler and start fps timer
    profile->init(profile);

    ship_animation->start(ship_animation);
    tiles_animation->start(tiles_animation);

    // render loop
    while (app->running)
    {
        // start profile session
        profile->start(profile);

        // handle input
        handle_input(app, &input_context);

        // calculate current fps after handling input
        profile->update(profile);

        // update scene
        sprintf(text_render_context.fps, "FPS: %.2f", profile->current_fps);
        fps_text->update(fps_text, text_render_context.fps, color_red);

        sprintf(text_render_context.pref, "Pref: %lu", profile->performance_count);
        pref_text->update(pref_text, text_render_context.pref, color_red);

        help_text->update(help_text, text_render_context.help, color_white);

        // prepare and clear scene
        prepare_scene(app->renderer);

        // render background image
        img_background->render(img_background, app->renderer);

        // render sprites and handle animations
        ship_sprite->render(ship_sprite, app->renderer);
        ship_animation->sprite(ship_animation, ship_sprite);

        solid_tiles_sprite->render(solid_tiles_sprite, app->renderer);
        tiles_animation->sprite(tiles_animation, solid_tiles_sprite);

        // render texts
        fps_text->render(fps_text, app->renderer);
        pref_text->render(pref_text, app->renderer);
        help_text->render(help_text, app->renderer);

        // present scene
        present_scene(app->renderer);

        // finish profile session
        profile->end(profile);

        // if frame finished early
        Uint32 frameTicks = profile->get_frame_ticks(profile);
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
    animation_free(ship_animation);
    animation_free(tiles_animation);
    sprite_free(ship_sprite);
    sprite_free(solid_tiles_sprite);
    image_free(img_background);
    app_quit(app);

    return EXIT_SUCCESS;
}
