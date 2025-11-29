//
// Created by tamer on 11/28/2025.
//

#include "Bullet.h"

#include <complex>

Bullet::Bullet(vec2 pos, tex2d *source, vec2 target): 
    KinemAABB(
        pos - (vec2){24.f,24.f}, 
        (vec2){48.f, 48.f}, 
        CollisionType_SOLID,
        0.5f, 
        0.1f
    ),
    source(source)
{
    z = 10;
    vel = 5.f * METER * norm(target - pos);
}

void Bullet::process(float dt) {
    vel.y += GRAV * dt;
    KinemAABB::process(dt);
}

void Bullet::draw(vec2 &cam_pos) {
    DrawTextureV(*source, pos-cam_pos, WHITE);
}