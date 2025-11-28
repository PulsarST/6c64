//
// Created by tamer on 11/28/2025.
//

#ifndef PUNKVERSEPROJECT_BULLET_H
#define PUNKVERSEPROJECT_BULLET_H
#include "types.h"


class Bullet final {
public:
    explicit Bullet() = delete;
    Bullet(const Bullet& b) = delete;
    explicit Bullet(Bullet&& bullet) = default;
    Bullet& operator=(const Bullet& b) = delete;
    Bullet& operator=(Bullet&& bullet) = default;

    explicit Bullet(vec2 position, float angle, float radius, float speed);

    void update(float deltaTime);
    void draw();

    ~Bullet();

private:
    void move(float deltaTime);

    vec2 position;
    vec2 velocity { .x = 0, .y = 0 };
    float angle;
    float radius;
    float speed;
};


#endif //PUNKVERSEPROJECT_BULLET_H