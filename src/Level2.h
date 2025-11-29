//
// Created by tamer on 11/28/2025.
//

#ifndef PUNKVERSEPROJECT_LEVEL2_H
#define PUNKVERSEPROJECT_LEVEL2_H
#include "ILevel.h"
#include "ParallaxBg.h"
#include "aabb.h"
#include <vector>

void static control4(vec2 &p){
    vec2 a = {0,0};
    a.x += 2.f * METER * IsKeyDown(KEY_D);
    a.x -= 2.f * METER * IsKeyDown(KEY_A);
    a.y += 2.f * METER * IsKeyDown(KEY_S);
    a.y -= 2.f * METER * IsKeyDown(KEY_W);

    p = a;
}

void static control2(vec2 &p){
    vec2 a = {0,0};
    a.x += 2.f * METER * IsKeyDown(KEY_D);
    a.x -= 2.f * METER * IsKeyDown(KEY_A);

    p.x = a.x;
}

class Level2 final : public ILevel{
public:
    Level2();

    static void house0(World *w, Chunk *c, Level2 *l);

    static void house1(World *w, Chunk *c, Level2 *l);

    static void house2(World *w, Chunk *c, Level2 *l);

    static void house3(World *w, Chunk *c, Level2 *l);

    static void add_house(World *w, Chunk *c, Level2 *l);
    static void generate_page(World *w, Chunk *c, Level2 *l);

    void draw() override;

    void update() override;

    ~Level2() override;
private:

    vec2    cam_pos;

    ParallaxBG bg;
    World   w;

    ptr<Base> player;

    tex2d   layer_1{};
    tex2d   layer_2{};

    tex2d   house_0{},
            house_1{},
            house_2{},
            house_3{},
            box{};

    Music   mus{};
};


#endif //PUNKVERSEPROJECT_LEVEL2_H