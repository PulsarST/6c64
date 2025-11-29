//
// Created by tamer on 11/29/2025.
//

#include "Menu.h"

#include <iostream>

Menu::Menu() : play_button("assets/button.png", "Play", (vec2){.x = 100, .y = 100}, (Color){200, 200, 200, 255},
                           []() { std::cout << "ITS WORKING !" << "\n"; }) {
}

void Menu::draw() {
    play_button.draw();
}

void Menu::update() {
    play_button.update();
}

Menu::~Menu() {
}
