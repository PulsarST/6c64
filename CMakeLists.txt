cmake_minimum_required(VERSION 4.0)
project(PunkVerseProject)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME} src/main.cpp)

include(FetchContent)

fetchcontent_declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_VERSION 5.5
)

fetchcontent_makeavailable(raylib)
target_link_libraries(${PROJECT_NAME} PUBLIC raylib)


set(ASSETS_SOURCE_DIR ${CMAKE_SOURCE_DIR}/assets)
set(ASSETS_DEST_DIR ${CMAKE_BINARY_DIR}/assets)

add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${ASSETS_SOURCE_DIR}"
        "${ASSETS_DEST_DIR}"
)

