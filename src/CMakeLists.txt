cmake_minimum_required(VERSION 3.21)

set(CMAKE_C_STANDARD 17)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(sdl2_c17 main.c init.c init.h config.h input.c input.h draw.c draw.h utility.c utility.h)
target_link_libraries(sdl2_c17 ${SDL2_LIBRARIES})
