//
// Created by tamer on 11/28/2025.
//

#ifndef PUNKVERSEPROJECT_LEVEL2_H
#define PUNKVERSEPROJECT_LEVEL2_H
#include "ILevel.h"


class Level2 final : public ILevel{
public:
    Level2();

    void draw() override;

    void update() override;

    ~Level2() override;
};


#endif //PUNKVERSEPROJECT_LEVEL2_H