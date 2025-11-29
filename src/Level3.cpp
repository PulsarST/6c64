//
// Created by tamer on 11/28/2025.
//

#include "Level3.h"

Level3::Level3() : ILevel() {
}

void Level3::draw() {
    dialogManager.draw();
}

void Level3::update() {
    dialogManager.update();
}

Level3::~Level3() {

}

