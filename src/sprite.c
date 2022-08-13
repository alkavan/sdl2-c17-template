#include <SDL2/SDL_log.h>
#include "types.h"
#include "sprite.h"
#include "utility.h"

/**
 * Get x,y position in pixels using the sprite grid, frame, and index.
 *
 * @param frame_index
 * @param frame_size
 * @param grid
 * @return
 */
static struct vec2i get_grid_xy(int frame_index, Vec2i frame_size, Vec2i grid) {

    int row = floor((double)frame_index / grid.x);
    int col = frame_index - (grid.x * row);

    int frame_x = frame_size.x * col;
    int frame_y = frame_size.y * row;

    return (Vec2i) {frame_x, frame_y};
}

static void update(Sprite *const t) {

}

static void render(Sprite *const t, SDL_Renderer *renderer) {
    if( ! t->texture) {
        t->texture = SDL_CreateTextureFromSurface(renderer, t->surface);
        if (t->texture == NULL) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "failed to create texture (%s)", SDL_GetError());
            return;
        }
    }

    const Vec2i grid_xy = get_grid_xy(t->frame_index, t->frame_size, t->grid);

    const SDL_Rect src_rect = {
            grid_xy.x,
            grid_xy.y,
            t->frame_size.x,
            t->frame_size.y
    };

    const SDL_Rect dest_rect = {
            (int)t->object->position.x,
            (int)t->object->position.y,
            t->frame_size.x,
            t->frame_size.y
    };

    SDL_RenderCopy(renderer, t->texture, &src_rect, &dest_rect);
}

static void next(Sprite *const t) {
    int max = t->grid.x * t->grid.y;

    if(t->frame_index >= (max - 1)) {
        t->frame_index = 0;
        return;
    }

    t->frame_index++;
}

Sprite *sprite_new(Vec2 position, Vec2i frame_size, SDL_Surface *const surface) {
    Sprite *sprite = (Sprite*) malloc(sizeof(Sprite));

    sprite->update = &update;
    sprite->render = &render;
    sprite->next = &next;

    Object* object = object_new();
    object->set_position(object, position);
    sprite->object = object;

    sprite->frame_size.x = frame_size.x;
    sprite->frame_size.y = frame_size.y;

    int frame_w = frame_size.x;
    int frame_h = frame_size.y;

    if (surface == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "null surface, unable to create Sprite{}");
        return NULL;
    }

    if(is_fraction((double)surface->w / (double)frame_w)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                     "%d surface does not divide by width %d",
                     surface->w, frame_w);
        return NULL;
    } else {
        sprite->grid.x = surface->w / frame_w;
    }

    if(is_fraction((double)surface->h / (double)frame_h)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                     "%d surface does not divide by height %d",
                     surface->h, frame_h);
        return NULL;
    } else {
        sprite->grid.y = surface->h / frame_h;
    }

    sprite->surface = surface;
    sprite->texture = NULL;

    sprite->frame_index = 0;

    return sprite;
}

void sprite_free(Sprite *t) {
    SDL_FreeSurface(t->surface);
    SDL_DestroyTexture(t->texture);
    free(t);
}
