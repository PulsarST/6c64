#pragma once
#include "types.h"
#define CHUNK_SIZE (vec2){3000.f,800.f}
#define RES (vec2){(float)GetScreenWidth(), (float)GetScreenHeight()}
#include <vector>
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

        std::vector<Base*> in_chunk;

        Chunk(): pos(0){}
        Chunk(i32 pos): pos(pos){}
        ~Chunk(){
            for(auto i : in_chunk)
                if(i)
                    delete i;
            if(top)
                delete top;
            if(bottom)
                delete bottom;
        }
};

struct World{
    Chunk root;
    Chunk *current;

    vec2 *cam_target = nullptr;
    vec2 cam_pos;

    std::vector<Base*> active;

    std::function<void(World*)> on_reaching_top;
    std::function<void(World*)> on_reaching_bottom;

    std::priority_queue<Base*, std::vector<Base*>, ZComp> draw_queue;

    World(){
        on_reaching_top = [](World* w){};
        on_reaching_bottom = [](World* w){};
        cam_pos = {0.f,0.f};
        current = &root;
    }

    void add(Base* item, Chunk *c, bool to_active = 0){
        // std::cout << "World::add began\n";
        if(!item)return;
        if(!c)return;
        // std::cout << "passed not nullptr\n";
        // std::cout << item->pos.x << ' ' << item->pos.y << '\n';
        // std::cout << item << '\n';
        c->in_chunk.push_back(item);
        // std::cout << "in chunk inserted successfully\n";
        if(to_active)
            active.push_back(item);
        // std::cout << "active inserted successfully\n";
        item->pos.y += c->pos * CHUNK_SIZE.y;
        item->chunk = c;
    }

    void remove(Base *item){
        if(!item)return;
        std::erase(active, item);
        std::erase(item->chunk->in_chunk, item);
        delete item;
        std::cout << "REMOVED PERMANENTLY\n";
    }

    void process(float dt){
        if(current == nullptr)return;
        // std::cout << "nullptr passed\n";
        // std::cout << "if active empty\n";
        if(active.empty()) {
            // std::cout << current << '\n';
            // std::cout << current->in_chunk.size() << '\n';
            for(auto i : current->in_chunk){
                // std::cout << "proceel pre insert" << i << "\n";
                active.push_back(i);
            }
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
            if(current->bottom != nullptr){
                // std::cout << "cycle start\n";
                for(auto it = active.begin(); it != active.end();){
                    if (*it && (*it)->chunk == current->bottom) {
                        it = active.erase(it);
                    } else {
                        ++it;
                    }
                }
            }
            if(current->top == nullptr){
                on_reaching_top(this);
            }
            if(current->top != nullptr){
                current = current->top;
                for(auto i : current->in_chunk)
                    active.push_back(i);
            }
            
        }
        else if(cam_pos.y >= current->pos+1 * CHUNK_SIZE.y){
            // std::cout << "unload top\n";
            for(auto it = active.begin(); it != active.end();){
                if (*it && (*it)->chunk == current) {
                    it = active.erase(it);
                } else {
                    ++it;
                }
            }
            if(current->bottom == nullptr){
                on_reaching_bottom(this);
            }
            if(current->bottom != nullptr){
                current = current->bottom;
                for(auto i : current->bottom->in_chunk)
                    active.push_back(i);
            }
        }
        // std::cout << "process dt\n";
        for(auto i : active){
            // std::cout << i << '\n';
            // std::cout << i->pos.x << ' ' << i->pos.y << '\n';
            // std::cout << i->z << '\n';
            // std::cout << i->chunk << '\n';
            // std::cout << '\n';
            i->process(dt);
        }
    }
    void draw(){
        for(auto i : active){
            draw_queue.push(i);
        }
        while(!draw_queue.empty()){
            Base* curr = draw_queue.top();
            curr->draw(cam_pos);
            draw_queue.pop();
        }
    }
   
};