//
// Created by tamer on 11/28/2025.
//

#include "Game.h"

#include <iostream>

#include "Globals.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"
#include "Menu.h"

Game::Game(): levels(5) {
    InitWindow(1280, 720, "Hello World");
    InitAudioDevice();

    SetTargetFPS(60);

    camera = Camera2D();
    camera.zoom = 1.0f;
    camera.rotation = 0.0f;
    camera.offset = {
        .x = static_cast<float>(GetScreenWidth()) / 2.f,
        .y = static_cast<float>(GetScreenHeight()) / 2.f
    };
    camera.target = camera.offset;

    deltaTime = 0;

    levels[MENU] = std::make_unique<Menu>();
    levels[LEVEL1] = std::make_unique<Level1>();
    levels[LEVEL2] = std::make_unique<Level2>();
    levels[LEVEL3] = std::make_unique<Level3>();

}

void Game::run() {
    while (!WindowShouldClose()) {
        deltaTime = GetFrameTime();
        levels[currentLevel]->update();

        BeginDrawing();
            ClearBackground(SKYBLUE);

            levels[currentLevel]->draw();
            DrawFPS(20, 20);
        EndDrawing();
    }

    running = false;
}

void Game::clean_up() {
    if (!running) {
        CloseAudioDevice();
        CloseWindow();
    }
}

Game::~Game() {
}


