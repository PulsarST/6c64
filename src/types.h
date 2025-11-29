#pragma once
#include <raylib.h>
#include <cstdint>
#include <math.h>
#include <functional>

typedef                     int8_t                i8;
typedef                     uint8_t               u8;
typedef                     int16_t               i16;
typedef                     uint16_t              u16;
typedef                     int32_t               i32;
typedef                     uint32_t              u32;
__MINGW_EXTENSION typedef   int64_t               i64;
__MINGW_EXTENSION typedef   uint64_t              u64;
typedef                     float                 f32;
typedef                     double                f64;
typedef                     Vector2               vec2;
typedef                     Vector3               vec3;
typedef                     Vector4               vec4;
typedef                     Color                 clr;
typedef                     Texture2D             tex2d;
typedef                     RenderTexture2D       rtex2d;
typedef                     Rectangle             rect;

#define LINKTYPE_VECVEC(op, la, lb) \
inline static vec2 operator op \
( \
    vec2 la a, vec2 lb b \
){ \
    return {a.x op b.x, a.y op b.y}; \
}

#define LINKTYPE_VECNUM(op, la, lb) \
template <typename T> \
inline static vec2 operator op \
( \
    vec2 la a, T lb b \
){ \
    return {a.x op b, a.y op b}; \
}

#define LINKTYPE_NUMVEC(op, la, lb) \
template <typename T> \
inline static vec2 operator op \
( \
    T lb b, vec2 la a \
){ \
    return {b op a.x, b op a.y}; \
}

#define OP_VECVEC(op) \
LINKTYPE_VECVEC(op, &, &) \
LINKTYPE_VECVEC(op, &, &&) \
LINKTYPE_VECVEC(op, &&, &) \
LINKTYPE_VECVEC(op, &&, &&) \

#define OP_VECNUM(op) \
LINKTYPE_VECNUM(op, &, &) \
LINKTYPE_VECNUM(op, &, &&) \
LINKTYPE_VECNUM(op, &&, &) \
LINKTYPE_VECNUM(op, &&, &&) \

#define OP_NUMVEC(op) \
LINKTYPE_NUMVEC(op, &, &) \
LINKTYPE_NUMVEC(op, &, &&) \
LINKTYPE_NUMVEC(op, &&, &) \
LINKTYPE_NUMVEC(op, &&, &&) \

OP_VECVEC(+)
OP_VECVEC(-)
OP_VECVEC(+=)
OP_VECVEC(-=)
OP_VECVEC(*)
OP_VECVEC(*=)

OP_VECNUM(*)
OP_VECNUM(*=)
OP_VECNUM(/)
OP_VECNUM(/=)

OP_NUMVEC(*)
OP_NUMVEC(*=)

template <typename T>
inline static T lerp(T a, T b, float weight){
    return (b-a)*weight + a;
}

inline static float dist(vec2 a){
    return sqrtf(a.x*a.x + (a.y*a.y));
}
inline static vec2 norm(vec2 a){
    return a / dist(a);
}

#define METER 128.f
#define GRAV 4.8f * METER