#include "types.h"

#define PARALLAX_LAYERS_COUNT 3
struct ParallaxBG{
    vec2    coeffs[PARALLAX_LAYERS_COUNT];
    tex2d  *textures[PARALLAX_LAYERS_COUNT];

    ParallaxBG(){}

    ParallaxBG(
        vec2          coeffs[PARALLAX_LAYERS_COUNT],
        tex2d        *textures[PARALLAX_LAYERS_COUNT]
    )
    {
        for(u32 i = 0; i < PARALLAX_LAYERS_COUNT; i++){
            this->coeffs[i] = coeffs[i];
            this->textures[i] = textures[i];
        }
    }

    void draw(vec2 cam_pos){
        for(u8 i = 0; i < PARALLAX_LAYERS_COUNT; i++){
            vec2 resulting_pos = cam_pos * coeffs[i];
            DrawTexturePro(
                *textures[i],
                {resulting_pos.x,resulting_pos.y,(float)GetScreenWidth(),(float)GetScreenHeight()},
                {0,0,(float)GetScreenWidth(),(float)GetScreenHeight()},
                {0,0},
                0,
                WHITE
            );
        }
    }
};