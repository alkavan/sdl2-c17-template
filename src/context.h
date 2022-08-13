#ifndef SDL2_C17_CONTEXT_H
#define SDL2_C17_CONTEXT_H

#include "animation.h"

struct GameInputContext {
    Sprite* ship_sprite;
    Animation* ship_animation;
    Vec2i mouse_position;
    bool show_debug_grid;
    bool show_debug_cross;
};
typedef struct GameInputContext GameInputContext;

struct TextRenderContext {
    char fps[255];
    char pref[255];
    char mouse[255];
    char help[255];
};
typedef struct TextRenderContext TextRenderContext;

#endif //SDL2_C17_CONTEXT_H
