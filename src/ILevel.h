//
// Created by tamer on 11/28/2025.
//

#ifndef PUNKVERSEPROJECT_ILEVEL_H
#define PUNKVERSEPROJECT_ILEVEL_H


class ILevel {
public:
    virtual void draw() = 0;
    virtual void update() = 0;

    virtual ~ILevel() = default;
};


#endif //PUNKVERSEPROJECT_ILEVEL_H