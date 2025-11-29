#include "world.h"
#include <cmath>

#define SOLID_OBJECT_MASS __FLT_MAX__ * 0.5f

struct AABB: Base{
    vec2 size;

    AABB(vec2 pos, vec2 size);

    bool isColliding(AABB *o);
    virtual vec2 *getVelocity();

    virtual void touchedFloor(){};
    virtual void touchedWall(){};
    virtual void touchedCeiling(){};
};

enum CollType{
    CollisionType_SOLID = 0,
    CollisionType_PLATFORM
};

struct CollAABB: AABB{
    float mass;
    float boyancy_k;
    CollType coll_type;

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
    tex2d   *source;

    StaticSprite(vec2 pos, tex2d *source);

    virtual void draw(vec2 &cam_pos) override;
};