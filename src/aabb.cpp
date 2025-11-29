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
    float dt
){
    if(!isColliding(other))return;
    // if(__resolved__ || other->__resolved__)return;
    if(other->coll_type == CollisionType_PLATFORM && coll_type == other->coll_type)return;

    vec2 *this_vel = getVelocity(),
         *other_vel = other->getVelocity();
    
    if(this_vel && 
        other->coll_type == CollisionType_PLATFORM && 
        (pos.y+size.y) - (this_vel->y*dt) > other->pos.y+0.01f)return;

    vec2 old_pos = pos;
    vec2 other_old_pos = other->pos;

    vec2 center = (size * 0.5f) + pos;
    vec2 other_center = (other->size * 0.5f) + other->pos;

    float abs_x = abs(center.y - other_center.y)/other->size.y,
            abs_y = abs(center.x - other_center.x)/other->size.x;

    // DrawCircleV(center, 5.f, RED);
    // DrawCircleV(other_center, 5.f, GREEN);

    float abs_left_wall = abs(pos.x - other->pos.x - other->size.x);
    float abs_right_wall = abs(pos.x + size.x - other->pos.x);
    float abs_ceiling = abs(pos.y - other->pos.y - other->size.y);
    float abs_floor = abs(pos.y + size.y - other->pos.y);

    float this_weight = mass / (mass + other->mass),
          other_weight = other->mass / (mass + other->mass);

    // std::cout << abs_left_wall << ' ' << abs_right_wall << ' ' << abs_ceiling << ' ' << abs_floor << '\n';

    // HITS LEFT WALL
    if(abs_left_wall < abs_right_wall && abs_left_wall < abs_ceiling && abs_left_wall < abs_floor){
        // std::cout << "left wall hit\n";
        touchedWall();
        other->touchedWall();

        float final_resolution = lerp(other->pos.x + other->size.x,pos.x,this_weight);
        pos.x = final_resolution;
        other->pos.x = final_resolution - other->size.x;

        vec2 real_vel = (pos - old_pos)/dt,
              other_real_vel = (other->pos - other_old_pos)/dt;

        if(this_vel != nullptr)
            other->pos.y += this_vel->y * (this_weight) * dt;
        if(other_vel != nullptr)
            pos.y += other_vel->y * (other_weight) * dt;
        if(this_vel != nullptr && __signbitf(this_vel->x) == 1 && dt != 0)
            this_vel->x = lerp(this_vel->x, boyancy_k*real_vel.x, other_weight);
        if(other_vel != nullptr && __signbitf(other_vel->x) != 1 && dt != 0)
            other_vel->x = lerp(other_vel->x, other->boyancy_k*other_real_vel.x/dt, this_weight);
    }
    // RIGHT WALL HIT
    else if(abs_right_wall < abs_left_wall && abs_right_wall < abs_ceiling && abs_right_wall < abs_floor){
        // std::cout << "right wall hit\n";
        touchedWall();
        other->touchedWall();

        float final_resolution = lerp(other->pos.x - size.x,pos.x,this_weight);
        pos.x = final_resolution;
        other->pos.x = final_resolution + size.x;

        vec2 real_vel = (pos - old_pos)/dt,
              other_real_vel = (other->pos - other_old_pos)/dt;

        if(this_vel != nullptr)
            other->pos.y += this_vel->y * (this_weight) * dt;
        if(other_vel != nullptr)
            pos.y += other_vel->y * (other_weight) * dt;
        if(this_vel != nullptr && __signbitf(this_vel->x) == 0 && dt != 0)
            this_vel->x = lerp(this_vel->x, boyancy_k*real_vel.x, other_weight);
        if(other_vel != nullptr && __signbitf(other_vel->x) != 0 && dt != 0)
            other_vel->x = lerp(other_vel->x, other->boyancy_k*other_real_vel.x/dt, this_weight);
    }
    else if(abs_ceiling < abs_left_wall && abs_ceiling < abs_right_wall && abs_ceiling < abs_floor){
        // std::cout << "ceiling hit\n";
        touchedCeiling();
        other->touchedFloor();
        float final_resolution = lerp(other->pos.y + other->size.y,pos.y,this_weight);
        pos.y = final_resolution;
        other->pos.y = final_resolution - other->size.y;

        vec2 real_vel = (pos - old_pos)/dt,
              other_real_vel = (other->pos - other_old_pos)/dt;

        if(this_vel != nullptr)
            other->pos.x += this_vel->x * (this_weight) * dt;
        if(other_vel != nullptr)
            pos.x += other_vel->x * (other_weight) * dt;
        if(this_vel != nullptr && __signbitf(this_vel->y) == 1 && dt != 0)
            this_vel->y = lerp(this_vel->y, boyancy_k*real_vel.y, other_weight);
        if(other_vel != nullptr && __signbitf(this_vel->y) != 1 && dt != 0)
            other_vel->y = lerp(other_vel->y, other->boyancy_k*other_real_vel.y/dt, this_weight);
    }
    else if(abs_floor < abs_left_wall && abs_floor < abs_right_wall && abs_floor < abs_ceiling){
        // std::cout << "floor hit\n";
        touchedFloor();
        other->touchedCeiling();
        float final_resolution = lerp(other->pos.y - size.y,pos.y,this_weight);
        pos.y = final_resolution;
        other->pos.y = final_resolution + size.y;

        vec2 real_vel = (pos - old_pos)/dt,
              other_real_vel = (other->pos - other_old_pos)/dt;

        if(this_vel != nullptr)
            other->pos.x += this_vel->x * (this_weight) * dt;
        if(other_vel != nullptr)
            pos.x += other_vel->x * (other_weight) * dt;
        if(this_vel != nullptr && __signbitf(this_vel->y) == 0 && dt != 0){
            this_vel->y = lerp(this_vel->y, boyancy_k*real_vel.y, other_weight);
            this_vel->x *= lerp(powf(0.8f,dt*30.f),1.f, this_weight);
        }
        if(other_vel != nullptr && __signbitf(this_vel->y) != 0 && dt != 0){
            other_vel->y = lerp(other_vel->y, other->boyancy_k*other_real_vel.y/dt, this_weight);
            other_vel->x *= lerp(powf(0.8f,dt*30.f), 1.f, other_weight);
        }
            
    }

    // __resolved__ = other->__resolved__ = 1;
}

KinemAABB::KinemAABB(vec2 pos, vec2 size,
    CollType coll_type, float mass, float boyancy_k):
CollAABB(pos, size, coll_type, mass, boyancy_k),
vel((vec2){0.f, 0.f})
{}

void KinemAABB::process(float dt){
    if(abs(vel.x) < 0.001f)vel.x = 0.f;
    if(abs(vel.y) < 0.001f)vel.y = 0.f;
    if(abs(vel.x) > 1000.f)vel.x = 1000.f;
    if(abs(vel.y) > 1000.f)vel.y = 1000.f;
    pos += vel * dt;
}

void KinemAABB::colideWith(CollAABB *other, float dt){
    
    hit_floor = 0;
    hit_wall = 0;
    hit_ceiling = 0;
    CollAABB::colideWith(other, dt);
}

vec2 *KinemAABB::getVelocity(){
    return &vel;
}

void KinemAABB::touchedFloor(){hit_floor = 1;}
void KinemAABB::touchedWall(){hit_wall = 1;}
void KinemAABB::touchedCeiling(){hit_ceiling = 1;}

StaticSprite::StaticSprite(vec2 pos, tex2d *source): Base(pos), source(source){}

void StaticSprite::draw(vec2 &cam_pos){
    DrawTextureV(*source, pos-cam_pos, WHITE);
}

Door::Door(vec2 pos, vec2 size, tex2d *icon): AABB(pos, size),
icon(icon)
{
    z = 20;
}

void Door::draw(vec2 &cam_pos){
    if(icon){
        DrawTextureV(*icon, pos - cam_pos - (vec2){32.f,32.f*(1.f+sinf(GetTime()))}, WHITE);
    }
}

Dirizhabl::Dirizhabl(float height, bool spawn_from_left, tex2d *source):
KinemAABB(
    (vec2){spawn_from_left ? -250.f : CHUNK_SIZE.x + 250.f,height},
    (vec2){400.f, 127.f},
    CollisionType_PLATFORM
    ),
    source(source){
        z = 5;
        vel.x = spawn_from_left ? 2.f * METER : -2.f * METER;
}
    
void Dirizhabl::process(float dt){
    KinemAABB::process(dt);
    // std::cout << pos.x << '\n';
}
void Dirizhabl::draw(vec2 &cam_pos){
    if(source){
        DrawTextureV(*source, pos - cam_pos, WHITE);
    }
}