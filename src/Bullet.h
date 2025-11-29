//
// Created by tamer on 11/28/2025.
//

#ifndef PUNKVERSEPROJECT_BULLET_H
#define PUNKVERSEPROJECT_BULLET_H
#include "types.h"
#include "aabb.h"


struct Bullet: KinemAABB{
    tex2d *source = nullptr;

    Bullet(): KinemAABB({0.f, 0.f}, {1.f, 1.f}){}
    Bullet(vec2 pos, tex2d *source = nullptr, vec2 target = {0.f, 0.f});

    virtual void process(float dt) override;
    virtual void draw(vec2 &cam_pos) override;
};


#endif //PUNKVERSEPROJECT_BULLET_H