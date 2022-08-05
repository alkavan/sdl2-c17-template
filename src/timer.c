#include <SDL2/SDL_timer.h>

#include "timer.h"

static void start(Timer *const t) {
    // start the timer
    t->started = true;

    // unpause the timer
    t->paused = false;

    // get the current clock time
    t->startTicks = SDL_GetTicks();
    t->pausedTicks = 0;
}

static void stop(Timer *const t) {
    // stop the timer
    t->started = false;

    // unpause the timer
    t->paused = false;

    // clear tick variables
    t->startTicks = 0;
    t->pausedTicks = 0;
}

static void pause(Timer *const t) {
    // if the timer is running and isn't already paused
    if( t->started && !t->paused )
    {
        // pause the timer
        t->paused = true;

        // calculate the paused ticks
        t->pausedTicks = SDL_GetTicks() - t->startTicks;
        t->startTicks = 0;
    }
}

static void unpause(Timer *const t) {
    // if the timer is running and paused
    if( t->started && t->paused )
    {
        // unpause the timer
        t->paused = false;

        // reset the starting ticks
        t->startTicks = SDL_GetTicks() - t->pausedTicks;

        // reset the paused ticks
        t->pausedTicks = 0;
    }
}

static Uint32 getTicks(Timer *const t) {
    // actual timer time
    Uint32 time = 0;

    // if the timer is running
    if( t->started )
    {
        // if the timer is paused
        if( t->paused )
        {
            // return the number of ticks when the timer was paused
            time = t->pausedTicks;
        }
        else
        {
            // return the current time minus the start time
            time = SDL_GetTicks() - t->startTicks;
        }
    }

    return time;
}

static bool isStarted(Timer *const t) {
    // timer is running and paused or unpaused
    return t->started;
}

static bool isPaused(Timer *const t) {
    // timer is running and paused
    return t->paused && t->started;
}

Timer *timer_new() {
    Timer *timer = (Timer*) malloc(sizeof(Timer));

    timer->start = &start;
    timer->stop = &stop;
    timer->pause = &pause;
    timer->unpause = &unpause;
    timer->getTicks = &getTicks;
    timer->isStarted = &isStarted;
    timer->isPaused = &isPaused;

    timer->startTicks = 0;
    timer->pausedTicks = 0;
    timer->paused = false;
    timer->started = false;

    return timer;
}

void timer_free(Timer *t) {
    free(t);
}
