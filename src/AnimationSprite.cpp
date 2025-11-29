//
// Created by tamer on 11/29/2025.
//

#include "Sprite.h"

#include <iostream>

AnimationSprite::AnimationSprite(const std::string &fileName, int cellCountX, int cellCountY, int cellSizeX, int cellSizeY,
               float speed) : texture(LoadTexture(fileName.c_str())), cellCount(cellCountX, cellCountY),
                              cellSize(cellSizeX, cellSizeY), animationSpeed(speed) {

    rect.width = cellSizeX;
    rect.height = cellSizeY;
}

void AnimationSprite::draw(vec2 &cam_pos) {
    DrawRectangle(pos.x - cam_pos.x, pos.y - cam_pos.y, rect.width, rect.height, WHITE);
}

void AnimationSprite::process(float deltaTime) {
    frameCounter += deltaTime;

    if (float frameTime = 1.f / animationSpeed; frameCounter > frameTime) {
        currentCellX++;
        frameCounter -= frameTime;

        if (currentCellX > cellCount.x) {
            currentCellX = 0;
        }

        rect.x = currentCellX * cellSize.x;
        rect.y = currentCellY * cellSize.y;
    }
}

AnimationSprite::~AnimationSprite() {
    UnloadTexture(texture);
}

