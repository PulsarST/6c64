//
// Created by tamer on 11/28/2025.
//

#ifndef PUNKVERSEPROJECT_LEVEL3_H
#define PUNKVERSEPROJECT_LEVEL3_H
#include "ILevel.h"


class Level3: public ILevel {
public:
    Level3();

    void draw() override;

    void update() override;

    ~Level3() override;
};


#endif //PUNKVERSEPROJECT_LEVEL3_H