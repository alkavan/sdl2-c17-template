cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 17)

# project, languages, and version
project(sdl2_c17 LANGUAGES C VERSION 0.2.2)

# generated code
configure_file(version_config.h.in ${CMAKE_BINARY_DIR}/generated/version_config.h)
include_directories(${CMAKE_BINARY_DIR}/generated/)

# mathc library
add_library(mathc
        third_party/mathc/mathc.h
        third_party/mathc/mathc.c
        )
include_directories(sdl2_c17 third_party/mathc)

# project files
add_subdirectory(src)

# copy mandatory assets
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/res/
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/res)

# png assets
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets/crosshair1.png DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/res/)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets/enemy1.png DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/res/)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets/explosion1.png DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/res/)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets/ship1.png DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/res/)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets/shot1.png DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/res/)

# jpg assets
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets/galaxy-purple_1280x720.jpg DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/res/)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets/galaxy-red_1280x720.jpg DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/res/)

# bmp assets
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets/solid-tileset.bmp DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/res/)
