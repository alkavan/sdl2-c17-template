cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 17)

project(sdl2_c17 LANGUAGES C VERSION 0.1.0)

configure_file(version_config.h.in ${CMAKE_BINARY_DIR}/generated/version_config.h)
include_directories(${CMAKE_BINARY_DIR}/generated/)

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

# bmp assets
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets/star-bg.bmp DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/res/)
