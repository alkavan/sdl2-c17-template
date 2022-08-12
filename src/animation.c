#include "animation.h"

static void sprite(Animation *const t, Sprite *const sprite) {
    Uint32 now_tick = t->timer->get_ticks(t->timer);
    if((now_tick - t->last_frame_tick) < t->frame_rate_ms) {
        return;
    }

    sprite->next(sprite);
    t->last_frame_tick = t->timer->get_ticks(t->timer);
}

void start(struct Animation *const t) {
    if( ! t->timer->started) {
        t->timer->start(t->timer);
    }
}

void stop(struct Animation *const t) {
    if(t->timer->started) {
        t->timer->stop(t->timer);
    }
}

Animation *animation_new(int frame_rate_ms, bool loop) {
    Animation *animation = (Animation*) malloc(sizeof(Animation));

    animation->sprite = &sprite;
    animation->start = &start;
    animation->stop = &stop;

    animation->timer = timer_new();
    animation->frame_rate_ms = frame_rate_ms;
    animation->loop = loop;
    animation->last_frame_tick = 0;

    return animation;
}

void animation_free(Animation *t) {
    timer_free(t->timer);
    free(t);
}
