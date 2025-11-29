//
// Created by tamer on 11/28/2025.
//

#ifndef PUNKVERSEPROJECT_LEVEL2_H
#define PUNKVERSEPROJECT_LEVEL2_H
#include "ILevel.h"
#include "ParallaxBg.h"
#include "aabb.h"
#include <vector>

void static control(vec2 &p){
    vec2 a = {0,0};
    a.x += 2.f * METER * IsKeyDown(KEY_D);
    a.x -= 2.f * METER * IsKeyDown(KEY_A);

    p.x = a.x;
}

class Level2 final : public ILevel{
public:
    Level2();

    void draw() override;

    void update() override;

    ~Level2() override;
private:

    vec2 cam_pos;

    tex2d layer_1{};
    tex2d layer_2{};

    Music mus{};

    tex2d box{};

    std::vector<KinemAABB> balls;

    size_t dirizhables_index;

    ParallaxBG bg;

    bool infinite_mass;
};


#endif //PUNKVERSEPROJECT_LEVEL2_H