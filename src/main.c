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
#include "control.h"

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
    Image* bg_image = image_new(
            (Vec2){(float)SCREEN_HALF_WIDTH, (float)SCREEN_HALF_HEIGHT},
            surface_bg
            );

    if (bg_image == NULL) {
        app_quit(app);
        return EXIT_FAILURE;
    }

    // create ship sprite
    Sprite* ship_sprite = sprite_new(
            (Vec2){(float)SCREEN_HALF_WIDTH, (float)SCREEN_HALF_HEIGHT},
            (Vec2i){32, 32},
            surface_ship
            );

    // create solid tileset sprite
    Sprite* solid_tiles_sprite = sprite_new(
            (Vec2){(float)SCREEN_HALF_WIDTH-100, (float)SCREEN_HALF_HEIGHT-100},
            (Vec2i){16, 16},
            surface_solid_tiles
            );

    // animations
    Animation* ship_animation = animation_new(25, true);
    Animation* tiles_animation = animation_new(100, true);

    // create text objects
    Text* fps_text = text_new(16, 16, font);
    Text* pref_text = text_new(16, 16+get_line_height(), font);
    Text* mouse_text = text_new(16, 16+(get_line_height()*2), font);
    Text* ship_text = text_new(16, 16+(get_line_height()*3), font);
    Text* help_text = text_new(16, SCREEN_HEIGHT-get_line_height()-10, font);

    TextRenderContext text_render_context = {
            .fps="",
            .pref="",
            .mouse="mouse (0, 0)",
            .ship="ship (0, 0)",
            .help="use AWSD keys to move ship, F5/F6 to start/stop animation, F7/F8 toggle grid/cross, ESC to quit!"
    };

    // player control
    Control* ship_control = control_new(1000.0f, 500.0f);

    // initialize context objects
    GameInputContext input_context = (GameInputContext){
        ship_sprite,
        ship_animation,
        ship_control,
        {0, 0},
        true,
        true
    };

    // create profile object
    Profile* profile = profile_new(true);

    // initialize profiler and start fps timer
    profile->init(profile);

    ship_animation->start(ship_animation);
    tiles_animation->start(tiles_animation);

    float dt;

    // render loop
    while (app->running)
    {
        // start profile session
        profile->start(profile);

        // update delta time (if fps is not zero)
        if(profile->current_fps > 0) {
            dt = 1.0f / profile->current_fps;
        }

        // handle input
        handle_input(app, &input_context, dt);

        // calculate current fps after handling input
        profile->update(profile);

        ship_control->update(ship_control, dt, ship_sprite->object);

        // fps text
        sprintf(text_render_context.fps, "fps: %.2f", profile->current_fps);
        fps_text->update(fps_text, text_render_context.fps, COLOR_RED);

        // delta time text
        sprintf(text_render_context.pref, "dt: %f", dt);
        pref_text->update(pref_text, text_render_context.pref, COLOR_RED);

        // mouse text
        sprintf(text_render_context.mouse, "mouse (%d, %d)",
                input_context.mouse_position.x, input_context.mouse_position.y);
        mouse_text->update(mouse_text, text_render_context.mouse, COLOR_RED);

        // ship text
        sprintf(text_render_context.ship, "ship (%f, %f)",
                ship_sprite->object->position.x, ship_sprite->object->position.y);
        ship_text->update(ship_text, text_render_context.ship, COLOR_RED);

        // help text
        help_text->update(help_text, text_render_context.help, COLOR_WHITE);

        // prepare and clear scene
        prepare_scene(app->renderer);

        // render background image
        bg_image->render(bg_image, app->renderer);

        // render global debug elements
        if(input_context.show_debug_grid) {
            draw_debug_grid(app->renderer, COLOR_BLUE, (Vec2i){16, 16});
        }

        if(input_context.show_debug_cross) {
            draw_debug_cross(app->renderer, COLOR_RED);
        }

        Vec2 mv = (Vec2){(float)input_context.mouse_position.x, (float)input_context.mouse_position.y};
        draw_debug_line(app->renderer, COLOR_GREEN, mv, ship_sprite->object->position);

        // render sprites and handle animations
        ship_sprite->render(ship_sprite, app->renderer);
        ship_animation->sprite(ship_animation, ship_sprite);

        solid_tiles_sprite->render(solid_tiles_sprite, app->renderer);
        tiles_animation->sprite(tiles_animation, solid_tiles_sprite);

        // render texts
        fps_text->render(fps_text, app->renderer);
        pref_text->render(pref_text, app->renderer);
        mouse_text->render(mouse_text, app->renderer);
        ship_text->render(ship_text, app->renderer);
        help_text->render(help_text, app->renderer);

        // present scene
        present_scene(app->renderer);

        // finish profile session
        profile->end(profile);

        // if frame finished early
        Uint32 frame_ticks = profile->get_frame_ticks(profile);
        if(frame_ticks < SCREEN_TICKS_PER_FRAME)
        {
            // wait remaining time
            SDL_Delay(SCREEN_TICKS_PER_FRAME - frame_ticks);
        }
    }

    // clean up
    profile_free(profile);
    control_free(ship_control);
    text_free(fps_text);
    text_free(pref_text);
    animation_free(ship_animation);
    animation_free(tiles_animation);
    sprite_free(ship_sprite);
    sprite_free(solid_tiles_sprite);
    image_free(bg_image);
    app_quit(app);

    return EXIT_SUCCESS;
}
