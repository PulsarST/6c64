//
// Created by tamer on 11/28/2025.
//

#ifndef PUNKVERSEPROJECT_LEVEL2_H
#define PUNKVERSEPROJECT_LEVEL2_H
#include "ILevel.h"
#include "ParallaxBg.h"
#include "Bullet.h"
#include "AnimationSprite.h"
#include <vector>

void static control4(vec2 &p){
    vec2 a = {0,0};
    a.x += 3.f * METER * IsKeyDown(KEY_D);
    a.x -= 3.f * METER * IsKeyDown(KEY_A);
    a.y += 3.f * METER * IsKeyDown(KEY_S);
    a.y -= 3.f * METER * IsKeyDown(KEY_W);

    p = a;
}

void static control2(vec2 &p){
    vec2 a = {0,0};
    a.x += 3.f * METER * IsKeyDown(KEY_D);
    a.x -= 3.f * METER * IsKeyDown(KEY_A);

    p.x = a.x;
}

class Level2 final : public ILevel{
public:
    Level2();

    static void house0(vec2 pos, World *w, Chunk *c, Level2 *l);

    static void house1(vec2 pos, World *w, Chunk *c, Level2 *l);

    static void house2(vec2 pos, World *w, Chunk *c, Level2 *l);

    static void house3(vec2 pos, World *w, Chunk *c, Level2 *l);

    static void add_house(vec2 pos, World *w, Chunk *c, Level2 *l);
    static void generate_page(World *w, Chunk *c, Level2 *l);

    void onDelivering(Bullet *b);
    u32 calcScore(Bullet *b);

    void draw() override;

    void update() override;

    ~Level2() override;
private:

    vec2    cam_pos;

    ParallaxBG bg;
    World   w;

    u32 generate_zakazchik;
    u32 score;
    u32 zakasi;
    u32 delivered;

    Base *player;
    KinemAABB *player_cast;
    bool player_anim = 0.f;

    float dirizhabl_timer = 0.f;

    std::vector<Bullet*> bullets;
    std::vector<Door*> doors;
    std::vector<Dirizhabl*> dirizhabls;

    tex2d   layer_1{};
    tex2d   layer_2{};

    Image dirizhabl_left_img{},
          dirizhabl_right_img{},
          player_img_left{};

    tex2d   house_0{},
            house_1{},
            house_2{},
            house_3{},
            box{},
            tovar_icon_0{},
            tovar_icon_1{},
            tovar_icon_2{},
            want_food{},
            dirizhabl_left{},
            dirizhabl_right{},
            player_tex_left{},
            player_tex_right{};

    AnimationSprite player_spr_left,
                    player_spr_right;

    Music   mus{};
};


#endif //PUNKVERSEPROJECT_LEVEL2_H