#include <SDL2/SDL_timer.h>
#include "profile.h"

#define MAX_FPS_VALUE 2000000.0f

static void init(struct Profile *const t) {
    t->fpsTimer->start(t->fpsTimer);
    t->countedFrames = 0;
}

static void start(struct Profile *const t) {
    t->capTimer->start(t->capTimer);
    if(t->isPerformance) {
        t->performanceStart = SDL_GetPerformanceCounter();
    }
}

static void end(struct Profile *const t) {
    ++t->countedFrames;

    if(t->isPerformance) {
        t->performanceCount = SDL_GetPerformanceCounter() - t->performanceStart;
    }
}

static void update(struct Profile *const t) {
    // calculate and correct fps
    t->currentFps = t->countedFrames / (t->fpsTimer->getTicks(t->fpsTimer) / 1000.f );

    if(t->currentFps > MAX_FPS_VALUE)
    {
        t->currentFps = 0;
    }
}

Uint32 getFrameTicks(struct Profile *const t) {
    return t->capTimer->getTicks(t->capTimer);
}

Profile *profile_new(bool is_performance) {
    Profile *profile = (Profile*) malloc(sizeof(Profile));

    profile->init = &init;
    profile->start = &start;
    profile->end = &end;
    profile->update = &update;
    profile->getFrameTicks = &getFrameTicks;

    // frames per second timer
    profile->fpsTimer = timer_new();

    // frames per second cap timer
    profile->capTimer = timer_new();

    // some initial values
    profile->currentFps = 0.0f;
    profile->countedFrames = 0;

    profile->isPerformance = is_performance;
    profile->performanceStart = 0;
    profile->performanceCount = 0;

    return profile;
}

void profile_free(Profile *t) {
    free(t);
}
