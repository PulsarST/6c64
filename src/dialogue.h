#include "types.h"
#include <string>

#define LEFT_SIDE 0
#define LEFT_SIDE 1

struct Dialogue{
    std::string line;
    tex2d       sprite;
    u8          side;

    void process(float dt);
    void draw(vec2);
};