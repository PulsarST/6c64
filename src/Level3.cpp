//
// Created by tamer on 11/28/2025.
//

#include "Level3.h"

Level3::Level3() : ILevel() {
    dialogManager.addDialog("assets/granpa1.png", vec2 {50,6.f * GetScreenHeight() / 8});
    std::vector<std::string> lines = {
        "einsngjkrdngnaengjnkdngjenrkngkngjkrndhb45hb3i39hf8nwak38hrwnghuinak8d498h"
        "einsngjkrdngnaengjnkdngjenrkngkngjkrndhb45hb3i39hf8nwak38hrwnghuinak8d498h",
        "einsngjkrdngnaengjnkdngjenrkngkngjkrndhb45hb3i39hf8nwak38hrwnghuinak8d498h",
    };
    dialogManager.addLines(0, lines);
}

void Level3::draw() {
    dialogManager.draw();
}

void Level3::update() {
    dialogManager.update();
}

Level3::~Level3() {

}

