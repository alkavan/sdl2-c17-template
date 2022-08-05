#ifndef SDL2_C17_TIMER_H
#define SDL2_C17_TIMER_H

#include <stdbool.h>
#include <SDL2/SDL_types.h>

/**
 * Implementing example: https://lazyfoo.net/tutorials/SDL/23_advanced_timers/index.php
 */

struct Timer {
    struct {
        void (*start)(struct Timer *const);
        void (*stop)(struct Timer *const);
        void (*pause)(struct Timer *const);
        void (*unpause)(struct Timer *const);
        Uint32 (*getTicks)(struct Timer *const);
        bool (*isStarted)(struct Timer *const);
        bool (*isPaused)(struct Timer *const);
    };

    // clock time when the timer started
    Uint32 startTicks;

    // ticks stored when the timer was paused
    Uint32 pausedTicks;

    // timer status
    bool paused;
    bool started;
};

typedef struct Timer Timer;

Timer *timer_new();
void timer_free(Timer *t);

#endif //SDL2_C17_TIMER_H
