//
// Created by tamer on 11/28/2025.
//

#ifndef PUNKVERSEPROJECT_PLAYER_H
#define PUNKVERSEPROJECT_PLAYER_H
#include <vector>

class Bullet;

class Player {
public:
    Player();

    void draw();
    void update(float deltaTime);

    ~Player();

private:
    float angle;
    std::vector<Bullet> bullets;
};

#endif //PUNKVERSEPROJECT_PLAYER_H