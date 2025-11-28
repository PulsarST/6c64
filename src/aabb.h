#include "types.h"
#include <cmath>

struct AABB{
    vec2 pos;
    vec2 size;

    AABB(vec2 pos, vec2 size);

    bool isColliding(AABB *o);
    virtual vec2 *getVelocity();

    virtual void touchedFloor(){};
    virtual void touchedWall(){};
    virtual void touchedCeiling(){};
};

struct CollAABB: AABB{
    float mass;
    float boyancy_k;
    bool __resolved__ = 0;

    CollAABB(vec2 pos, vec2 size, float mass = __FLT_MAX__ * 0.5f, float boyancy_k = 0.f);

    void colideWith(
        CollAABB *other, 
        float &&dt
    );
};

struct KinemAABB: CollAABB{
    vec2 vel;

    bool hit_floor = 0,
         hit_wall = 0,
         hit_ceiling = 0;

    KinemAABB(vec2 pos, vec2 size, float mass = __FLT_MAX__ * 0.5f, float boyancy_k = 0.f);

    virtual vec2 *getVelocity() override;

    virtual void touchedFloor() override;
    virtual void touchedWall() override;
    virtual void touchedCeiling() override;
};