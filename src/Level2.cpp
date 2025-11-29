//
// Created by tamer on 11/28/2025.
//

#include "Level2.h"
#include <iostream>

Level2::Level2(): ILevel() {
    cam_pos = {0.f, 0.f};

    layer_1 = LoadTexture("assets/level_2_bg_base.png");
    layer_2 = LoadTexture("assets/level_2_bg_front.png");

    house_0 = LoadTexture("assets/level_2_house_0.png");
    house_1 = LoadTexture("assets/level_2_house_1.png");
    house_2 = LoadTexture("assets/level_2_house_2.png");
    house_3 = LoadTexture("assets/level_2_house_3.png");

    box = LoadTexture("assets/ball.png");

    mus = LoadMusicStream("assets/delivery.wav");

    vec2 parallax_coeffs[PARALLAX_LAYERS_COUNT] = {
        {0.1f, 0.1f},
        {0.4f, 0.4f}
    };

    tex2d* parallax_textures[PARALLAX_LAYERS_COUNT] = {
        &layer_1,
        &layer_2
    };

    bg = ParallaxBG(parallax_coeffs, parallax_textures);
}

void Level2::draw(){
    // cam_pos = lerp(
    //     cam_pos, 
    //     balls[0].pos 
    //     - (vec2){GetScreenWidth()*0.5f,GetScreenHeight()*0.5f}
    //     , 
    //     GetFrameTime()*3.f < 1.f ? GetFrameTime()*3.f : 1.f
    // );
    bg.draw(cam_pos);
    // for(auto& i : balls){
    //     // DrawCircleV(i.pos-cam_pos, 10, BLUE);
    //     DrawTextureV(box,i.pos-cam_pos,WHITE);
    // }   
}

void Level2::update() {
    // std::cout << "start\n";
    if(!IsMusicStreamPlaying(mus))
        PlayMusicStream(mus);
    UpdateMusicStream(mus);

    w.process(GetFrameTime());
    // std::cout << "collisions resolved\n";
}

Level2::~Level2() {
    UnloadTexture(box);
    UnloadTexture(layer_1);
    UnloadTexture(layer_2);

    UnloadTexture(house_0);
    UnloadTexture(house_1);
    UnloadTexture(house_2);
    UnloadTexture(house_3);

    UnloadMusicStream(mus);
}

