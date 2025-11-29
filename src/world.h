#pragma once
#include "types.h"
#define CHUNK_SIZE (vec2){3000.f,800.f}
#define RES (vec2){(float)GetScreenWidth(), (float)GetScreenHeight()}
#include <unordered_set>

struct Chunk;

struct Base{
     Chunk *chunk;
     vec2 pos;

    Base(){}
    Base(vec2 pos): pos(pos){}

     virtual void process(float dt){};
     virtual void draw(vec2 &cam_pos){};
};

struct Chunk{
        const i32 pos;
        Chunk *top = nullptr;
        Chunk *bottom = nullptr;
        std::unordered_set<Base*> in_chunk;

        Chunk(i32 pos): pos(pos){}
        ~Chunk(){
            for(auto &i : in_chunk)
                delete i;
            delete top;
            delete bottom;
        }
};

struct World{
    Chunk* root = nullptr;
    Chunk* current = root;

    vec2 *cam_target = nullptr;
    vec2 cam_pos;

    std::unordered_set<Base*> active;

    World(){
        cam_pos = {0.f,0.f};
        root = new Chunk(0);
    }

    void add(Base *item, Chunk *c){
        c->in_chunk.insert(item);
        item->pos.y += c->pos * CHUNK_SIZE.y;
    }

    void process(float dt){
        if(cam_target)
            cam_pos = lerp(
                cam_pos, 
                *cam_target - (RES * 0.5f),
                dt*3.f < 1.f ? dt*3.f : 1.f
            );
        if(cam_pos.x < 0)
            cam_pos.x = 0;
        else if(cam_pos.x > CHUNK_SIZE.x - RES.x)
            cam_pos.x = CHUNK_SIZE.x - RES.x;
        if(cam_pos.y < current->pos * CHUNK_SIZE.y){
            for(auto &i : active){
                if(i->chunk == current->bottom)
                    active.erase(i);
            }
            if(current->top){
                current = current->top;
                for(auto &i : current->in_chunk)
                        active.insert(i);
            }
        }
        else if(cam_pos.y >= current->pos+1 * CHUNK_SIZE.y){
            for(auto &i : active){
                if(i->chunk == current)
                    active.erase(i);
            }
            if(current->bottom){
                current = current->bottom;
                for(auto &i : current->bottom->in_chunk)
                    active.insert(i);
            }
        }
        for(auto &i : active){
            i->process(dt);
        }
    }
    void draw(){
        for(auto &i : active){
            i->draw(cam_pos);
        }
    }

   ~World(){
        delete root;
    }
   
};