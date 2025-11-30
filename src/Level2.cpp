//
// Created by tamer on 11/28/2025.
//

#include "Level2.h"
#include <iostream>

void Level2::house0(vec2 pos, World *w, Chunk *c, Level2 *l){
    Base* house_sprite = new StaticSprite(pos, &l->house_0);
    w->add(house_sprite, c);
    w->add(new CollAABB(
        (vec2){73,292}+pos,
        (vec2){700,32}
        ,CollisionType_PLATFORM
    ), c);
    w->add(new CollAABB(
        (vec2){533,263}+pos,
        (vec2){199,30}
        ,CollisionType_PLATFORM
    ), c);
    w->add(new CollAABB(
        (vec2){550,244}+pos,
        (vec2){182,19}
        ,CollisionType_PLATFORM
    ), c);
    w->add(new CollAABB(
        (vec2){570,216}+pos,
        (vec2){162,28}
        ,CollisionType_PLATFORM
    ), c);
    w->add(new CollAABB(
        (vec2){589,191}+pos,
        (vec2){143,25}
        ,CollisionType_PLATFORM
    ), c);
    w->add(new CollAABB(
        (vec2){601,160}+pos,
        (vec2){131,31}
        ,CollisionType_PLATFORM
    ), c);
    w->add(new CollAABB(
        (vec2){732,160}+pos,
        (vec2){153,31}
        ,CollisionType_PLATFORM
    ), c);
    if(l->generate_zakazchik && !(rand()%3)){
        l->doors.push_back(new Door(
            (vec2){354,227}+pos,
            (vec2){7,64},
            &l->want_food
        ));
        w->add(dynamic_cast<Base*>(l->doors.back()), c);
        l->generate_zakazchik--;
    }
}

void Level2::house1(vec2 pos, World *w, Chunk *c, Level2 *l){
    Base* house_sprite = new StaticSprite(pos, &l->house_1);
    w->add(house_sprite, c);
    w->add(new CollAABB(
        (vec2){157,420}+pos,
        (vec2){609,34}
        ,CollisionType_PLATFORM
    ), c);
    w->add(new CollAABB(
        (vec2){40,611}+pos,
        (vec2){415,39}
        ,CollisionType_PLATFORM
    ), c);
    if(l->generate_zakazchik && !(rand()%3)){
        l->doors.push_back(new Door(
            (vec2){470,354}+pos,
            (vec2){22,65},
            &l->want_food
        ));
        w->add(dynamic_cast<Base*>(l->doors.back()), c);
        l->generate_zakazchik--;
    }
}

void Level2::house2(vec2 pos, World *w, Chunk *c, Level2 *l){
    Base* house_sprite = new StaticSprite(pos, &l->house_2);
    w->add(house_sprite, c);
    w->add(new CollAABB(
        (vec2){193,460}+pos,
        (vec2){508,26}
        ,CollisionType_PLATFORM
    ), c);
    w->add(new CollAABB(
        (vec2){6,316}+pos,
        (vec2){263,15}
        ,CollisionType_PLATFORM
    ), c);
    if(l->generate_zakazchik && !(rand()%3)){
        l->doors.push_back(new Door(
            (vec2){390,395}+pos,
            (vec2){17,62},
            &l->want_food
        ));
        w->add(dynamic_cast<Base*>(l->doors.back()), c);
        l->generate_zakazchik--;
    }
}

void Level2::house3(vec2 pos, World *w, Chunk *c, Level2 *l){
    Base* house_sprite = new StaticSprite(pos, &l->house_3);
    w->add(house_sprite, c);
    w->add(new CollAABB(
        (vec2){237,308}+pos,
        (vec2){517,22}
        ,CollisionType_PLATFORM
    ), c);
    w->add(new CollAABB(
        (vec2){661,200}+pos,
        (vec2){297,20}
        ,CollisionType_PLATFORM
    ), c);
    w->add(new CollAABB(
        (vec2){25,210}+pos,
        (vec2){199,13}
        ,CollisionType_PLATFORM
    ), c);
    if(l->generate_zakazchik && !(rand()%3)){
        l->doors.push_back(
            new Door(
            (vec2){481,208}+pos,
            (vec2){40,101},
            &l->want_food
            )
        );
        w->add(dynamic_cast<Base*>(l->doors.back()), c);
        l->generate_zakazchik--;
    }
}

void Level2::add_house(vec2 pos, World *w, Chunk *c, Level2 *l){
    switch(rand()%4){
        case 0:
            house0(pos,w,c,l);
            break;
        case 1:
            house1(pos,w,c,l);
            break;
        case 2:
            house2(pos,w,c,l);
            break;
        case 3:
            house3(pos,w,c,l);
    }
}

void Level2::generate_page(World *w, Chunk *c, Level2 *l){
    float height = 0.f;
    float x = rand()%((int)CHUNK_SIZE.x- 500);
    for(u8 i = 0; i < rand()%2+3; i++){
        add_house({x, height},w, c, l);
        height -= rand()%500 + 250;
        float x = rand()%((int)CHUNK_SIZE.x- 500);
    }
}

void Level2::onDelivering(Bullet *b){
    score += calcScore(b);
    delivered++;
}
u32 Level2::calcScore(Bullet *b){
    float d = dist(player_cast->pos - b->pos);
    if(d < METER)
        return 100;
    if(d < 2*METER)
        return 500;
    if(d < 5*METER)
        return 1000;
    return 5000;
}

Level2::Level2(): ILevel() {
    cam_pos = {0.f, -360.f};

    dirizhabl_left_img = LoadImage("assets/dirizhabl.png");
    dirizhabl_right_img = LoadImage("assets/dirizhabl.png");
    player_img_left = LoadImage("assets/guy_running2.png");

    layer_1 = LoadTexture("assets/level_2_bg_base.png");
    layer_2 = LoadTexture("assets/level_2_bg_front.png");

    house_0 = LoadTexture("assets/level_2_house_0.png");
    house_1 = LoadTexture("assets/level_2_house_1.png");
    house_2 = LoadTexture("assets/level_2_house_2.png");
    house_3 = LoadTexture("assets/level_2_house_3.png");

    tovar_icon_0 = LoadTexture("assets/test_bullet.png");
    tovar_icon_1 = LoadTexture("assets/test_bullet.png");
    tovar_icon_2 = LoadTexture("assets/test_bullet.png");

    want_food = LoadTexture("assets/want_food.png");

    box = LoadTexture("assets/ball.png");

    ImageFlipHorizontal(&dirizhabl_right_img);
    ImageFlipHorizontal(&player_img_left);

    dirizhabl_left = LoadTextureFromImage(dirizhabl_left_img);
    dirizhabl_right = LoadTextureFromImage(dirizhabl_right_img);

    player_tex_left = LoadTextureFromImage(player_img_left);
    player_tex_right = LoadTexture("assets/guy_running2.png");

    player_spr_left = AnimationSprite(&player_tex_left, 4, 1, 77, 103, 10.f);
    player_spr_right = AnimationSprite(&player_tex_right, 4, 1, 77, 103, 10.f);

    mus = LoadMusicStream("assets/delivery.wav");

    score = 0;
    zakasi = 10;
    generate_zakazchik = zakasi;
    delivered = 0;

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
    add_house((vec2){1000.f, -300.f}, &w, w.current, this);

    player = new KinemAABB(
        (vec2){1500.f, -300.f},
        (vec2){32.f, 103.f},
        CollisionType_SOLID,
        1.f);


    player_cast = dynamic_cast<KinemAABB*>(player);
    
    w.add(
        player,
        w.current
    );
    w.cam_target = &player->pos;
}

void Level2::gameEndDraw(){
    bg.draw(w.cam_pos);
    if(game_timer < 0.f){
        DrawText("TIME'S UP!", RES.x/2-100.f, RES.y/2, 64, RED);
    }
    else if(zakasi == 0 && bullets.empty()){
        DrawText(delivered >= 7.5 ? "ORDERS DELIVERED!" : "YOU LOST TOO MUCH", RES.x/2-300.f, RES.y/2, 64, delivered >= 7.5 ? WHITE : RED);
    }
}

void Level2::draw(){
    bool game_end = game_timer <= 0.f || (zakasi == 0 && bullets.empty());
    if(game_end){
        gameEndDraw();
        return;
    }
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

    if(player_anim)
        player_spr_left.draw(w.cam_pos);
    else
        player_spr_right.draw(w.cam_pos);
    for(auto &i : doors){
        DrawCircleV(player_cast->size*0.5f + player_cast->pos - w.cam_pos + (64.f * norm(player_cast->size*-0.5f+i->pos-player_cast->pos)), 5, WHITE);
    }
    DrawText(("SCORE "+std::to_string(score)).c_str(), 20, 40, 40, WHITE);
    DrawText(("ORDERS "+std::to_string(zakasi)+" ("+std::to_string(delivered)+" DELIVERED)").c_str(), 20, 80, 40, WHITE);
    DrawText("TIME", 317, 590, 40, WHITE);
    DrawRectangle(317,635,634,35,BLACK);
    DrawRectangle(318,636,632*game_timer/max_game_time,33,WHITE);
}

void Level2::gameEndCycle(float dt){
    // if(delivered >= 7.5){
    //     //win
    // }
    // else{
    //     //lose
    // }
}

void Level2::update() {
    float dt = GetFrameTime();
    // std::cout << "start\n";
    if(!IsMusicStreamPlaying(mus))
        PlayMusicStream(mus);
    UpdateMusicStream(mus);

    bool game_end = game_timer <= 0.f || (zakasi == 0 && bullets.empty());

    if(game_end){
        gameEndCycle(dt);
        return;
    }

    dirizhabl_timer += dt;
    game_timer -= dt;

    if(dirizhabl_timer >= 4.f){
        bool from_left = rand()%2;
        dirizhabls.push_back(
            new Dirizhabl(
                player->pos.y - (rand()%200 - 50),
                from_left,
                from_left ? &dirizhabl_right : &dirizhabl_left
            )
        );
        dirizhabls.back()->pos.y -= w.current->pos * CHUNK_SIZE.y;
        w.add(
            dirizhabls.back(),
            w.current,
            1
        );
        dirizhabl_timer = 0.f;
    }

    // std::cout << "jumps\n";
    player_cast->vel.y += GRAV * dt;
    control2(player_cast->vel);
    if(IsKeyPressed(KEY_A))
        player_anim = 1;
    if(IsKeyPressed(KEY_D))
        player_anim = 0;

    player_spr_left.process(dt*(player_cast->vel.x != 0));
    player_spr_right.process(dt*(player_cast->vel.x != 0));
    player_spr_left.pos = player_cast->pos - (vec2){22.f,0.f};
    player_spr_right.pos = player_cast->pos - (vec2){22.f,0.f};

    if(zakasi && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        zakasi--;
        // std::cout << player_cast->pos.x << ' ' << player_cast->pos.y << '\n';
        bullets.push_back(new Bullet(player_cast->pos + (vec2){16.f,16.f}, &tovar_icon_0,
            w.cam_pos + GetMousePosition()));

        bullets.back()->vel += player_cast->vel*0.4f;
            
        w.add(bullets.back(), w.current, 1);
        bullets.back()->pos.y -= (CHUNK_SIZE.y*w.current->pos);

        // std::cout << bullets.back()->pos.x << ' ' << bullets.back()->pos.y << '\n';
    }

    // std::cout << "process world\n";
    w.process(dt);

    // std::cout << "player collides with active\n";
    for(auto i : w.active){
        if(auto p = dynamic_cast<Bullet*>(i)){
            if(IsKeyPressed(KEY_LEFT_SHIFT) && player_cast->isColliding(p)){
                std::erase_if(bullets, [p]( Bullet* &el){return el == p;});
                w.remove(dynamic_cast<Base*>(i));
                zakasi++;
            }
            continue;
        }
        player_cast->colideWith(dynamic_cast<CollAABB*>(i), dt);
    }
    
    // std::cout << "bullets collide with active\n";
    for(auto i : dirizhabls){
        if(i->pos.x > CHUNK_SIZE.x+600 || i->pos.x < -600){
            w.remove(dynamic_cast<Base*>(i));
            std::erase_if(dirizhabls, [i]( Dirizhabl* &el){return el == i;});
        }
    }
    for(auto i : bullets){
        if(dist(i->pos - player_cast->pos) > 15.f * METER){
            w.remove(dynamic_cast<Base*>(i));
            std::erase_if(bullets, [i]( Bullet* &el){return el == i;});
        }
        for(auto j : w.active){
            if(j == player)continue;
            i->colideWith(dynamic_cast<CollAABB*>(j), dt);
        }
        for(auto j : doors)
            if(i->isColliding(dynamic_cast<AABB*>(j))){
                onDelivering(i);
                w.remove(dynamic_cast<Base*>(i));
                std::erase_if(bullets, [i]( Bullet* &el){return el == i;});
                w.remove(dynamic_cast<Base*>(j));
                std::erase_if(doors, [j]( Door* &el){return el == j;});
            }
    }
    if(player_cast->vel.y == 0.f && IsKeyPressed(KEY_SPACE)){
        if(IsKeyDown(KEY_S)){
            player_cast->pos.y += 1.f;
            player_cast->vel.y = METER;
        }
        else
            player_cast->vel.y = -5.f * METER;
    }
    if(IsKeyReleased(KEY_SPACE) && player_cast->vel.y < 0.f)
        player_cast->vel.y *= 0.5f;
    // std::cout << "done\n";
}

Level2::~Level2() {
    UnloadImage(dirizhabl_left_img);
    UnloadImage(dirizhabl_right_img);
    UnloadImage(player_img_left);

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

    UnloadTexture(want_food);

    UnloadTexture(dirizhabl_left);
    UnloadTexture(dirizhabl_right);

    UnloadTexture(player_tex_left);
    UnloadTexture(player_tex_right);

    UnloadMusicStream(mus);

    w.~World();
}

