//
// Created by tamer on 11/28/2025.
//

#include "Bullet.h"

#include <complex>

Bullet::Bullet(
    const vec2 position,
    const float angle,
    const float radius,
    const float speed)
: position(position),angle(angle), radius(radius), speed(speed) {
    velocity = vec2(0.f, 0.f);
}

void Bullet::update(float deltaTime) {
    move(deltaTime);
}

void Bullet::draw() {
    DrawCircle(position.x, position.y , radius, WHITE);
}

void Bullet::move(float deltaTime) {
    velocity.x = std::cos(RAD2DEG * angle);
    velocity.y = std::sin(RAD2DEG * angle);

    position.x = velocity.x * speed * deltaTime;
    position.y = velocity.y * speed * deltaTime;
}

Bullet::~Bullet() {

}
