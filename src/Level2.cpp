//
// Created by tamer on 11/28/2025.
//

#include "Level2.h"
#include <iostream>

void Level2::house0(World *w, Chunk *c, Level2 *l){
    vec2 rand_pos = {rand()%((int)CHUNK_SIZE.x- 500), (rand()%((int)CHUNK_SIZE.y+500))-500};
    Base* house_sprite = new StaticSprite(rand_pos, &l->house_0);
    w->add(house_sprite, c);
    w->add(new CollAABB(
        (vec2){73,292}+rand_pos,
        (vec2){700,32}
        ,CollisionType_PLATFORM
    ), c);
    w->add(new CollAABB(
        (vec2){533,263}+rand_pos,
        (vec2){199,30}
    ), c);
    w->add(new CollAABB(
        (vec2){550,244}+rand_pos,
        (vec2){182,19}
    ), c);
    w->add(new CollAABB(
        (vec2){570,216}+rand_pos,
        (vec2){162,28}
    ), c);
    w->add(new CollAABB(
        (vec2){589,191}+rand_pos,
        (vec2){143,25}
    ), c);
    w->add(new CollAABB(
        (vec2){601,160}+rand_pos,
        (vec2){131,31}
    ), c);
    w->add(new CollAABB(
        (vec2){732,160}+rand_pos,
        (vec2){153,31}
        ,CollisionType_PLATFORM
    ), c);
}

void Level2::house1(World *w, Chunk *c, Level2 *l){
    vec2 rand_pos = {rand()%((int)CHUNK_SIZE.x- 500), rand()%(int)CHUNK_SIZE.y-500};
    Base* house_sprite = new StaticSprite(rand_pos, &l->house_1);
    w->add(house_sprite, c);
    w->add(new CollAABB(
        (vec2){157,420}+rand_pos,
        (vec2){609,34}
        ,CollisionType_PLATFORM
    ), c);
    w->add(new CollAABB(
        (vec2){40,611}+rand_pos,
        (vec2){415,39}
        ,CollisionType_PLATFORM
    ), c);
}

void Level2::house2(World *w, Chunk *c, Level2 *l){
    vec2 rand_pos = {rand()%((int)CHUNK_SIZE.x- 500), rand()%(int)CHUNK_SIZE.y-500};
    Base* house_sprite = new StaticSprite(rand_pos, &l->house_2);
    w->add(house_sprite, c);
    w->add(new CollAABB(
        (vec2){193,460}+rand_pos,
        (vec2){508,26}
        ,CollisionType_PLATFORM
    ), c);
    w->add(new CollAABB(
        (vec2){6,316}+rand_pos,
        (vec2){263,15}
        ,CollisionType_PLATFORM
    ), c);
}

void Level2::house3(World *w, Chunk *c, Level2 *l){
    vec2 rand_pos = {rand()%((int)CHUNK_SIZE.x- 500), rand()%(int)CHUNK_SIZE.y-500};
    Base* house_sprite = new StaticSprite(rand_pos, &l->house_3);
    w->add(house_sprite, c);
    w->add(new CollAABB(
        (vec2){237,308}+rand_pos,
        (vec2){517,22}
        ,CollisionType_PLATFORM
    ), c);
    w->add(new CollAABB(
        (vec2){661,200}+rand_pos,
        (vec2){297,20}
        ,CollisionType_PLATFORM
    ), c);
    w->add(new CollAABB(
        (vec2){25,210}+rand_pos,
        (vec2){199,13}
        ,CollisionType_PLATFORM
    ), c);
}

void Level2::add_house(World *w, Chunk *c, Level2 *l){
    switch(rand()%4){
        case 0:
            house0(w,c,l);
            break;
        case 1:
            house1(w,c,l);
            break;
        case 2:
            house2(w,c,l);
            break;
        case 3:
            house3(w,c,l);
    }
}

void Level2::generate_page(World *w, Chunk *c, Level2 *l){
    for(u8 i = 0; i < rand()%3+3; i++){
        add_house(w, c, l);
    }
}

Level2::Level2(): ILevel() {
    cam_pos = {0.f, -360.f};

    layer_1 = LoadTexture("assets/level_2_bg_base.png");
    layer_2 = LoadTexture("assets/level_2_bg_front.png");

    house_0 = LoadTexture("assets/level_2_house_0.png");
    house_1 = LoadTexture("assets/level_2_house_1.png");
    house_2 = LoadTexture("assets/level_2_house_2.png");
    house_3 = LoadTexture("assets/level_2_house_3.png");

    tovar_icon_0 = LoadTexture("assets/test_bullet.png");
    tovar_icon_1 = LoadTexture("assets/test_bullet.png");
    tovar_icon_2 = LoadTexture("assets/test_bullet.png");

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

    w = World();
    w.on_reaching_top = [this](World *w){
        Chunk *new_chunk = new Chunk(w->current->pos-1);
        w->current->top = new_chunk;
        generate_page(w, new_chunk, this);
    };
    generate_page(&w,w.current,this);

    player = new KinemAABB(
        (vec2){1500.f, -300.f},
        (vec2){64.f, 86.f},
        CollisionType_SOLID,
        1.f);
    player_cast = dynamic_cast<KinemAABB*>(player);
    w.add(
        player,
        w.current
    );
    w.cam_target = &player->pos;
}

void Level2::draw(){
    // cam_pos = lerp(
    //     cam_pos, 
    //     balls[0].pos 
    //     - (vec2){GetScreenWidth()*0.5f,GetScreenHeight()*0.5f}
    //     , 
    //     GetFrameTime()*3.f < 1.f ? GetFrameTime()*3.f : 1.f
    // );
    bg.draw(w.cam_pos);
    // for(auto& i : balls){
    //     // DrawCircleV(i.pos-cam_pos, 10, BLUE);
    //     DrawTextureV(box,i.pos-cam_pos,WHITE);
    // }   
    w.draw();
    DrawTextureV(box, player_cast->pos-w.cam_pos, WHITE);
}

void Level2::update() {
    // std::cout << "start\n";
    if(!IsMusicStreamPlaying(mus))
        PlayMusicStream(mus);
    UpdateMusicStream(mus);

    // std::cout << "jumps\n";
    player_cast->vel.y += GRAV * GetFrameTime();
    control2(player_cast->vel);

    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        std::cout << player_cast->pos.x << ' ' << player_cast->pos.y << '\n';
        bullets.push_back(new Bullet(player_cast->pos + (vec2){32.f,32.f}, &tovar_icon_0,
            w.cam_pos + GetMousePosition()));
        bullets.back()->pos -= (CHUNK_SIZE*w.current->pos);
        w.add(bullets.back(), w.current, 1);
        std::cout << bullets.back()->pos.x << ' ' << bullets.back()->pos.y << '\n';
    }

    // std::cout << "process world\n";
    w.process(GetFrameTime());

    // std::cout << "player collides with active\n";
    for(auto &i : w.active){
        bool cont = 0;
        for(auto &j : bullets)
            if(i == dynamic_cast<Base*>(j)){
                cont = 1;
                break;
            }

        if(cont)continue;
        
        player_cast->colideWith(dynamic_cast<CollAABB*>(i), GetFrameTime());
    }
    
    // std::cout << "bullets collide with active\n";
    for(auto &i : bullets){
        for(auto &j : w.active){
            if(j == player)continue;
            i->colideWith(dynamic_cast<CollAABB*>(j), GetFrameTime());
        }
    }
    if(player_cast->vel.y == 0.f && IsKeyPressed(KEY_SPACE))
        player_cast->vel.y = -5.f * METER;
    // std::cout << "done\n";
}

Level2::~Level2() {
    UnloadTexture(box);
    UnloadTexture(layer_1);
    UnloadTexture(layer_2);

    UnloadTexture(house_0);
    UnloadTexture(house_1);
    UnloadTexture(house_2);
    UnloadTexture(house_3);

    UnloadTexture(tovar_icon_0);
    UnloadTexture(tovar_icon_1);
    UnloadTexture(tovar_icon_2);

    UnloadMusicStream(mus);

    w.~World();
}

