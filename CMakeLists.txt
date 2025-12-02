cmake_minimum_required(VERSION 4.0)
project(PunkVerseProject)

set(CMAKE_CXX_STANDARD 20)

# --- STATIC BUILD ON MINGW ---
if (MINGW)
    message(STATUS "Building static executable on MinGW-w64")

    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} \
        -static -static-libgcc -static-libstdc++ \
        -Wl,--whole-archive -lpthread -Wl,--no-whole-archive \
        -Wl,-subsystem,windows"
    )

    set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
endif()
# --------------------------------

# 🔥 IMPORTANT: WIN32 removes the console window
add_executable(${PROJECT_NAME} WIN32
        src/main.cpp
        src/types.h
        src/Globals.h
        src/Note.cpp
        src/Note.h
        src/Game.cpp
        src/Game.h
        src/ILevel.h
        src/Level1.cpp
        src/Level1.h
        src/ParallaxBg.h
        src/Level2.cpp
        src/Level2.h
        src/Level3.cpp
        src/Level3.h
        src/Bullet.cpp
        src/Bullet.h
        src/aabb.cpp
        src/aabb.h
        src/world.h
        src/ui/Button.cpp
        src/ui/Button.h
        src/Menu.cpp
        src/Menu.h
        src/AnimationSprite.cpp
        src/AnimationSprite.h
        src/Dialog.cpp
        src/Dialog.h
        src/DialogManager.cpp
        src/DialogManager.h
)

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
