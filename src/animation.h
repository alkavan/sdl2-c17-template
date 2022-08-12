#ifndef SDL2_C17_ANIMATION_H
#define SDL2_C17_ANIMATION_H

#include "timer.h"
#include "sprite.h"

struct Animation {
    struct {
        void (*sprite)(struct Animation *const, Sprite *const sprite);
        void (*start)(struct Animation *const);
        void (*stop)(struct Animation *const);
    };

    Timer* timer;
    int frame_rate_ms;
    bool loop;
    Uint32 last_frame_tick;
};

typedef struct Animation Animation;

Animation *animation_new(int frame_rate_ms, bool loop);
void animation_free(Animation *t);

#endif //SDL2_C17_ANIMATION_H
