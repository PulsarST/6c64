//
// Created by tamer on 11/29/2025.
//

#include "Menu.h"

#include <iostream>

#include "Globals.h"

Menu::Menu() : play_button("assets/button.png", "Play", (vec2){.x = WIN_WIDTH / 2, .y = WIN_HEIGHT / 2},
                           (Color){230, 103, 103, 255},
                           []() { std::cout << "ITS WORKING !" << "\n"; }), quit_button(
                   "assets/button.png", "Quit", (vec2){.x = WIN_WIDTH / 2, .y = WIN_HEIGHT / 2},
                   (Color){230, 103, 103, 255}, []() {
                   }) {
    background = LoadTexture("assets/background_menu.png");

    vec2 play_button_size = play_button.get_size();
    play_button.set_pos((GetScreenWidth() - play_button_size.x) / 2,
                        (GetScreenHeight() - play_button_size.y) / 2);

    vec2 quit_button_size = quit_button.get_size();

    quit_button.set_pos((GetScreenWidth() - quit_button_size.x) / 2,
                        (GetScreenHeight() - quit_button_size.y) / 2 + 120);

    play_button.set_on_click([]() {
        currentLevel = LEVEL1;
    });

    quit_button.set_on_click([]() {
        CloseWindow();
    });
}

void Menu::draw() {
    DrawTexture(background, 0, 0, WHITE);
    play_button.draw();
    quit_button.draw();
}

void Menu::update() {
    play_button.update();
    quit_button.update();
}

Menu::~Menu() {
    UnloadTexture(background);
}
