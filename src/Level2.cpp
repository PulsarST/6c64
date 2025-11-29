//
// Created by tamer on 11/28/2025.
//

#include "Level2.h"
#include <iostream>

Level2::Level2(): ILevel() {
    cam_pos = {0.f, 0.f};

    std::cout << "cam_pos inited\n";

    layer_1 = LoadTexture("assets/layer_1.png");
    layer_2 = LoadTexture("assets/layer_2.png");
    layer_3 = LoadTexture("assets/layer_3.png");

    box = LoadTexture("assets/ball.png");

    std::cout << "textures inited\n";

    for(u32 i = 0; i < 20; i++){
        balls.emplace_back(
            (vec2){(float)(rand()%GetScreenWidth()), (float)(rand()%GetScreenHeight())},
            (vec2){64.f, 64.f}
        );
    }
    std::cout << "balls inited\n";

    balls[0].pos = {0,0};

    dirizhables_index = balls.size();
    for(u32 i = dirizhables_index; i < dirizhables_index+5; i++){
        balls.emplace_back(
            (vec2){(float)(rand()%GetScreenWidth()), (float)(rand()%GetScreenHeight())},
            (vec2){64.f, 64.f}
        );
        balls[i].vel.x = rand()&1 ? -100.f : 100.f;
    }
    // std::cout << GetScreenHeight() << ' ' << GetScreenWidth() << '\n';
    balls.emplace_back(
        (vec2){0.f, (float)GetScreenHeight()},
        (vec2){(float)GetScreenWidth(), (float)GetScreenHeight()}
    );
    std::cout << balls.back().pos.x << ' ' << balls.back().pos.y << '\n';
    std::cout << balls.back().vel.x << ' ' << balls.back().vel.y << '\n';
    std::cout << "dirizhables inited\n";

    vec2 parallax_coeffs[PARALLAX_LAYERS_COUNT] = {
        {0.f, 0.f},
        {0.1f, 0.f},
        {0.4f, 0.4f}
    };

    tex2d* parallax_textures[PARALLAX_LAYERS_COUNT] = {
        &layer_1,
        &layer_2,
        &layer_3
    };

    bg = ParallaxBG(parallax_coeffs, parallax_textures);
    std::cout << "parallaxbg inited\n";

    infinite_mass = 0;
}

void Level2::draw() {
    cam_pos = lerp(
        cam_pos, 
        balls[0].pos 
        - (vec2){GetScreenWidth()*0.5f,GetScreenHeight()*0.5f}
        , 
        GetFrameTime()*3.f < 1.f ? GetFrameTime()*3.f : 1.f
    );
    // bg.draw(cam_pos);
    for(auto& i : balls){
        // DrawCircleV(i.pos-cam_pos, 10, BLUE);
        DrawTextureV(box,i.pos-cam_pos,WHITE);
    }   
}

void Level2::update() {
    // std::cout << "start\n";
    
    if(IsKeyPressed(KEY_SPACE))
        infinite_mass = !infinite_mass;
    // std::cout << "key pressed SPACE\n";

    if(IsKeyPressed(KEY_W) && balls[0].hit_floor)
        balls[0].vel.y = -4.f * METER;
    // std::cout << "jump\n";

    balls[0].vel.y += GRAV * GetFrameTime();
    // std::cout << "getframetime\n";
    balls[0].mass = infinite_mass ? __FLT_MAX__ * 0.5f : 1.f;
    // std::cout << "inf mass\n";

    // std::cout << "trying to control vector\n";
    control(balls[0].vel);
    // std::cout << "vector controled\n";

    std::cout << balls.back().pos.x << ' ' << balls.back().pos.y << '\n';
    std::cout << balls.back().vel.x << ' ' << balls.back().vel.y << '\n';

    for(auto& i : balls){
        i.pos += i.vel * GetFrameTime();
        i.hit_ceiling = 0;
        i.hit_floor = 0;
        i.hit_wall = 0;
    }
    // std::cout << "velocity applied\n";

    for(auto& i : balls){
        for(auto& j : balls){
            i.colideWith(&j, GetFrameTime());
        }
    }
    // std::cout << "collisions resolved\n";
}

Level2::~Level2() {
    UnloadTexture(box);
    UnloadTexture(layer_1);
    UnloadTexture(layer_2);
    UnloadTexture(layer_3);
}

