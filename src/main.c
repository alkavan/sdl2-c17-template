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

    // load shot1 sprite image
    SDL_Surface *surface_shot1 = NULL;
    load_image(&surface_shot1, "../res/shot1.png");

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

    // create shot sprite
    Sprite* shot1_sprite = sprite_new(
            (Vec2){(float)SCREEN_HALF_WIDTH+100, (float)SCREEN_HALF_HEIGHT+100},
            (Vec2i){16, 16},
            surface_shot1
    );

    // create solid tileset sprite
    Sprite* solid_tiles_sprite = sprite_new(
            (Vec2){(float)SCREEN_HALF_WIDTH-100, (float)SCREEN_HALF_HEIGHT-100},
            (Vec2i){16, 16},
            surface_solid_tiles
            );

    // animations
    Animation* ship_animation = animation_new(25, true);
    Animation* shot_animation = animation_new(250, true);
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
    Control* ship_control = control_new(1.0f);

    // initialize context objects
    GameInputContext input_context = (GameInputContext) {
        ship_animation,
        ship_control,
        {0.0f, 0.0f},
        {0.0f, 0.0f},
        false, // enable/disable debug grid by default, should move to settings.
        true // enable/disable debug cross by default, should move to settings.
    };

    // create profile object
    Profile* profile = profile_new(true);

    // initialize profiler and start fps timer
    profile->init(profile);

    // start animations
    ship_animation->start(ship_animation);
    shot_animation->start(shot_animation);
    tiles_animation->start(tiles_animation);

    // delta time
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
        handle_input(app, &input_context);

        // calculate current fps after handling input
        profile->update(profile);


        ship_control->update(ship_control, dt, ship_sprite->object);

        // fps text
        sprintf(text_render_context.fps, "fps: %.2f", profile->current_fps);
        fps_text->update(fps_text, text_render_context.fps, COLOR_RED);

        // delta time text
        sprintf(text_render_context.pref, "dt: %f", dt);
        pref_text->update(pref_text, text_render_context.pref, COLOR_RED);

        // ship direction relative to mouse position
        Vec2 ship_direction = relative_mouse_position(
                input_context.mouse_position,
                ship_sprite->object->position
                );

        ship_direction = svec2_normalize(ship_direction);
        input_context.ship_direction.x = ship_direction.x;
        input_context.ship_direction.y = ship_direction.y;

        // TODO: get this out of here
        float direction_deg = (float)vec2_to_deg(svec2_rotate(ship_direction, to_radians(90)));
        Mat2 ship_rotation = smat2_rotation_z(to_radians(direction_deg));
        ship_sprite->object->set_rotation(ship_sprite->object, ship_rotation);
        float ship_deg = (float)mat2_to_deg(ship_rotation);

        sprintf(text_render_context.mouse, "mouse (%.0f, %.0f) dir (%.2f, %.2f) deg: %.2f",
                input_context.mouse_position.x, input_context.mouse_position.y, ship_direction.x, ship_direction.y, ship_deg);
        mouse_text->update(mouse_text, text_render_context.mouse, COLOR_RED);

        // ship text
        sprintf(text_render_context.ship, "ship p(%.2f, %.2f) v(%.2f, %.2f)",
                ship_sprite->object->position.x, ship_sprite->object->position.y,
                ship_control->velocity.x, ship_control->velocity.y);
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

        draw_debug_line(app->renderer, COLOR_GREEN,
                        input_context.mouse_position,
                        ship_sprite->object->position
                        );

        // render sprites and handle animations
        solid_tiles_sprite->render(solid_tiles_sprite, app->renderer);
        tiles_animation->sprite(tiles_animation, solid_tiles_sprite);

        ship_sprite->render(ship_sprite, app->renderer);
        ship_animation->sprite(ship_animation, ship_sprite);

        shot1_sprite->render(shot1_sprite, app->renderer);
        shot_animation->sprite(shot_animation, shot1_sprite);

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
