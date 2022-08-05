cmake_minimum_required(VERSION 3.21)

find_package(SDL2 REQUIRED CONFIG)

add_executable(sdl2_c17
        main.c
        config.h
        input.c
        input.h
        draw.c
        draw.h
        timer.c
        timer.h
        app.c
        app.h
        profile.c
        profile.h
        text.c
        text.h
        image.c
        image.h
        )

target_link_libraries(sdl2_c17 SDL2 SDL2_ttf SDL2_image)
