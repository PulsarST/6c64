#include "world.h"
#include <cmath>

#define SOLID_OBJECT_MASS __FLT_MAX__ * 0.5f

struct AABB: Base{
    vec2 size;

    AABB(){}
    AABB(vec2 pos, vec2 size);

    bool isColliding(AABB *o);
    virtual vec2 *getVelocity();

    virtual void touchedFloor(){};
    virtual void touchedWall(){};
    virtual void touchedCeiling(){};
};

enum CollType{
    CollisionType_SOLID = 0,
    CollisionType_PLATFORM,
    CollisionType_DISABLED
};

struct CollAABB: AABB{
    float mass;
    float boyancy_k;
    CollType coll_type;

    CollAABB(){}
    CollAABB(
        vec2 pos, 
        vec2 size, 
        CollType coll_type = CollisionType_SOLID, 
        float mass = SOLID_OBJECT_MASS, 
        float boyancy_k = 0.f
    );

    virtual void colideWith(
        CollAABB *other, 
        float dt
    );
};

struct KinemAABB: CollAABB{
    vec2 vel;

    bool hit_floor = 0,
         hit_wall = 0,
         hit_ceiling = 0;

    KinemAABB(){}
    KinemAABB(
        vec2 pos, 
        vec2 size, 
        CollType coll_type = CollisionType_SOLID,
        float mass = SOLID_OBJECT_MASS,
        float boyancy_k = 0.f
    );

    virtual void process(float dt) override;
    virtual vec2 *getVelocity() override;
    virtual void colideWith(CollAABB *other, float dt) override;

    virtual void touchedFloor() override;
    virtual void touchedWall() override;
    virtual void touchedCeiling() override;
};

struct StaticSprite: Base{
    tex2d   *source = nullptr;

    StaticSprite(){}
    StaticSprite(vec2 pos, tex2d *source);

    virtual void draw(vec2 &cam_pos) override;
};

struct Door: AABB{
    tex2d *icon = nullptr;

    Door(){}
    Door(vec2 pos, vec2 size, tex2d *icon = nullptr);

    virtual void draw(vec2 &cam_pos) override;
};

struct Dirizhabl: KinemAABB{
    tex2d *source = nullptr;

    Dirizhabl(){}
    Dirizhabl(float height, bool spawn_from_left, tex2d *source = nullptr);
    
    virtual void process(float dt) override;
    virtual void draw(vec2 &cam_pos) override;
};

struct Drone: KinemAABB{
    tex2d *source = nullptr;

    Drone(){}
    Drone(vec2 pos, tex2d *source = nullptr);
    
    void process(float dt) override;
    void draw(vec2 &cam_pos) override;
};