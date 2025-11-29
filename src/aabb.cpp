#include "aabb.h"
#include <iostream>

AABB::AABB(vec2 pos, vec2 size):
    Base(pos), size(size)
{}

bool AABB::isColliding(AABB *other){
    if(other == nullptr)return 0;
    if(this == other)return 0;

    return 
    
    pos.x          < other->pos.x + other->size.x &&
    pos.x + size.x > other->pos.x                 &&
    pos.y          < other->pos.y + other->size.y &&
    pos.y + size.y > other->pos.y;

}

vec2 *AABB::getVelocity(){
    return nullptr;
}

CollAABB::CollAABB(
    vec2 pos, 
    vec2 size, 
    CollType coll_type,
    float mass, 
    float boyancy_k
):
    AABB(pos, size),
    coll_type(coll_type),
    mass(mass),
    boyancy_k(boyancy_k)
{}

void CollAABB::colideWith(
    CollAABB *other, 
    float &&dt
){
    if(!isColliding(other))return;
    // if(__resolved__ || other->__resolved__)return;
    if(other->coll_type == CollisionType_PLATFORM && coll_type == other->coll_type)return;

    vec2 *this_vel = getVelocity(),
         *other_vel = other->getVelocity();

    vec2 old_pos = pos;
    vec2 other_old_pos = other->pos;

    vec2 center = (size * 0.5f) + pos;
    vec2 other_center = (other->size * 0.5f) + other->pos;

    float abs_x = abs(center.y - other_center.y),
            abs_y = abs(center.x - other_center.x);

    // DrawCircleV(center, 5.f, RED);
    // DrawCircleV(other_center, 5.f, GREEN);
    
    if(abs_x > abs_y){
        bool top_wall;
        if(center.y > other_center.y){
            top_wall = 1;
            float final_resolution = lerp(other->pos.y + other->size.y,pos.y,mass / (mass + other->mass));
            pos.y = final_resolution;
            other->pos.y = final_resolution - other->size.y;
            touchedCeiling();
            other->touchedFloor();
        }
        else{
            top_wall = 0;
            float final_resolution = lerp(other->pos.y - size.y,pos.y,mass / (mass + other->mass));
            pos.y = final_resolution;
            other->pos.y = final_resolution + size.y;
            touchedFloor();
            other->touchedCeiling();
        }
        vec2 real_vel = (pos - old_pos)/dt,
              other_real_vel = (other->pos - other_old_pos)/dt;

        if(this_vel != nullptr)
            other->pos.x += this_vel->x * (mass / (mass + other->mass)) * dt;
        if(other_vel != nullptr)
            pos.x += other_vel->x * (other->mass / (mass + other->mass)) * dt;
        if(this_vel != nullptr && __signbitf(this_vel->y) == top_wall && dt != 0)
            this_vel->y = lerp(this_vel->y, boyancy_k*real_vel.y, other->mass / (mass + other->mass));
        if(other_vel != nullptr && __signbitf(this_vel->y) != top_wall && dt != 0)
            other_vel->y = lerp(other_vel->y, other->boyancy_k*other_real_vel.y/dt, mass / (mass + other->mass));
    }
    else if(abs_x < abs_y){
        touchedWall();
        other->touchedWall();
        bool left_wall;
        if(center.x > other_center.x){
            left_wall = 1;
            float final_resolution = lerp(other->pos.x + other->size.x,pos.x,mass / (mass + other->mass));
            pos.x = final_resolution;
            other->pos.x = final_resolution - other->size.x;
        }
        else{
            left_wall = 0;
            float final_resolution = lerp(other->pos.x - size.x,pos.x,mass / (mass + other->mass));
            pos.x = final_resolution;
            other->pos.x = final_resolution + size.x;
        }
        vec2 real_vel = (pos - old_pos)/dt,
              other_real_vel = (other->pos - other_old_pos)/dt;

        if(this_vel != nullptr)
            other->pos.y += this_vel->y * (mass / (mass + other->mass)) * dt;
        if(other_vel != nullptr)
            pos.y += other_vel->y * (other->mass / (mass + other->mass)) * dt;
        if(this_vel != nullptr && __signbitf(this_vel->x) == left_wall && dt != 0)
            this_vel->x = lerp(this_vel->x, boyancy_k*real_vel.x, other->mass / (mass + other->mass));
        if(other_vel != nullptr && __signbitf(other_vel->x) != left_wall && dt != 0)
            other_vel->x = lerp(other_vel->x, other->boyancy_k*other_real_vel.x/dt, mass / (mass + other->mass));
    }

    // __resolved__ = other->__resolved__ = 1;
}

KinemAABB::KinemAABB(vec2 pos, vec2 size,
    CollType coll_type, float mass, float boyancy_k):
CollAABB(pos, size, coll_type, mass, boyancy_k),
vel((vec2){0.f, 0.f})
{}

vec2 *KinemAABB::getVelocity(){
    return &vel;
}

void KinemAABB::touchedFloor(){hit_floor = 1;}
void KinemAABB::touchedWall(){hit_wall = 1;}
void KinemAABB::touchedCeiling(){hit_ceiling = 1;}