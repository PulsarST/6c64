#pragma once
#include "types.h"
#define CHUNK_SIZE (vec2){3000.f,800.f}
#define RES (vec2){(float)GetScreenWidth(), (float)GetScreenHeight()}
#include <unordered_set>
#include <iostream>

#include <queue>

struct Chunk;

struct Base{

    i32 z;

    Chunk *chunk = nullptr;
    vec2 pos;

    Base(): z(0){}
    Base(vec2 pos): pos(pos), z(0){}

    virtual void process(float dt){};
    virtual void draw(vec2 &cam_pos){};
};

struct ZComp{
  bool operator()(const Base* a, const Base* b) const  {
    if(a->z == b->z)return a > b;
    return a->z > b->z;
  }
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

    std::function<void(World*)> on_reaching_top;
    std::function<void(World*)> on_reaching_bottom;

    std::priority_queue<Base*, std::vector<Base*>, ZComp> draw_queue;

    World(){
        on_reaching_top = [](World* w){};
        on_reaching_bottom = [](World* w){};
        cam_pos = {0.f,0.f};
        root = new Chunk(0);
        current = root;
    }

    void add(Base* item, Chunk *c, bool to_active = 0){
        // std::cout << "World::add began\n";
        if(!item)return;
        if(!c)return;
        // std::cout << "passed not nullptr\n";
        // std::cout << item->pos.x << ' ' << item->pos.y << '\n';
        // std::cout << item << '\n';
        c->in_chunk.insert(item);
        // std::cout << "in chunk inserted successfully\n";
        if(to_active)
            active.insert(item);
        // std::cout << "active inserted successfully\n";
        item->pos.y += c->pos * CHUNK_SIZE.y;
        item->chunk = c;
    }

    void remove(Base *item){
        if(!item)return;
        active.erase(item);
        item->chunk->in_chunk.erase(item);
        delete item;
    }

    void process(float dt){
        if(current == nullptr)return;
        // std::cout << "nullptr passed\n";
        // std::cout << "if active empty\n";
        if(active.empty())
            for(auto &i : current->in_chunk){
                active.insert(i);
            }
        // std::cout << "cam target\n";
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
            // std::cout << "unload bottom\n";
            // if(current->bottom)
            //     for(auto &i : active){
            //         if(i->chunk == current->bottom)
            //             active.erase(i);
            //     }
            if(!current->top){
                on_reaching_top(this);
            }
            if(current->top){
                current = current->top;
                for(auto &i : current->in_chunk)
                    active.insert(i);
            }
            
        }
        else if(cam_pos.y >= current->pos+1 * CHUNK_SIZE.y){
            // std::cout << "unload top\n";
            // for(auto &i : active){
            //     if(i->chunk == current)
            //         active.erase(i);
            // }
            if(!current->bottom){
                on_reaching_bottom(this);
            }
            if(current->bottom){
                current = current->bottom;
                for(auto &i : current->bottom->in_chunk)
                    active.insert(i);
            }
        }
        // std::cout << "process dt\n";
        for(auto &i : active){
            i->process(dt);
        }
    }
    void draw(){
        for(auto &i : active){
            draw_queue.push(i);
        }
        while(!draw_queue.empty()){
            Base* curr = draw_queue.top();
            curr->draw(cam_pos);
            draw_queue.pop();
        }
    }

   ~World(){
        delete root;
    }
   
};