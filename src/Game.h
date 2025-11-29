//
// Created by tamer on 11/28/2025.
//

#ifndef PUNKVERSEPROJECT_GAME_H
#define PUNKVERSEPROJECT_GAME_H
#include <memory>
#include <vector>

#include "ILevel.h"
#include "raylib.h"

enum Level {
    MENU = 0,
    LEVEL1,
    LEVEL2,
    LEVEL3,
    CREDITS
};

class Game final {
public:
    explicit Game();

    void run();

    ~Game();

private:
    std::vector<std::unique_ptr<ILevel>> levels;
    Camera2D camera{};
    Level currentLevel = LEVEL2;
    double deltaTime;
};


#endif //PUNKVERSEPROJECT_GAME_H