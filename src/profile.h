#ifndef SDL2_C17_PROFILE_H
#define SDL2_C17_PROFILE_H

#include "timer.h"

struct Profile {
    struct {
        void (*init)(struct Profile *const);
        void (*update)(struct Profile *const);
        void (*start)(struct Profile *const);
        void (*end)(struct Profile *const);
        Uint32 (*getFrameTicks)(struct Profile *const);
    };

    Timer* fpsTimer;
    Timer* capTimer;

    float currentFps;
    Uint32 countedFrames;
    bool isPerformance;

    Uint64 performanceStart;
    Uint64 performanceCount;
};

typedef struct Profile Profile;

Profile *profile_new(bool is_performance);
void profile_free(Profile *t);

#endif //SDL2_C17_PROFILE_H
