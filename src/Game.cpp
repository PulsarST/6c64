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

    levels[MENU] = new Menu();
    levels[LEVEL1] = new Level1();
    levels[LEVEL2] = nullptr;
    levels[LEVEL3] = new Level3();

}

void Game::run() {
    while (!WindowShouldClose()) {
        if (IsKeyDown(KEY_P)) {
            currentLevel = (Level)((int)currentLevel + 1);
        }
        if(!levels[LEVEL2] && currentLevel == LEVEL2){
            levels[LEVEL2] = new Level2();
        }

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
    for(auto i : levels)
        delete i;
}


