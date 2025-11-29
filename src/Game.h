//
// Created by tamer on 11/28/2025.
//

#ifndef PUNKVERSEPROJECT_GAME_H
#define PUNKVERSEPROJECT_GAME_H
#include <memory>
#include <vector>

#include "ILevel.h"
#include <raylib.h>

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

    void clean_up();

    ~Game();

private:
    std::vector<std::unique_ptr<ILevel>> levels;
    Camera2D camera{};
    double deltaTime;
    bool running = true;
};


#endif //PUNKVERSEPROJECT_GAME_H