cmake_minimum_required(VERSION 3.21)
project(sdl2_c17 C)

add_subdirectory(src)

# copy assets
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/res/
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/res)
