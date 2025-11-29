//
// Created by tamer on 11/29/2025.
//

#ifndef PUNKVERSEPROJECT_SPRITE_H
#define PUNKVERSEPROJECT_SPRITE_H
#include <string>

#include "raylib.h"
#include "types.h"
#include "world.h"


class AnimationSprite final: public Base {
public:
    AnimationSprite() = delete;
    explicit AnimationSprite(const std::string &fileName, int cellCountX, int cellCountY, int cellSizeX, int cellSizeY,
                    float speed);

    void draw(vec2 &cam_pos) override;

    void process(float deltaTime) override;

    ~AnimationSprite();

private:
    Texture2D texture;
    Rectangle rect{};
    vec2 cellCount;
    vec2 cellSize;

    float frameCounter = 0;
    int currentCellX = 0;
    int currentCellY = 0;
    float animationSpeed;
};


#endif //PUNKVERSEPROJECT_SPRITE_H