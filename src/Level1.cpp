#include "Level1.h"

#include <cmath>
#include <iostream>



// Constructor
Level1::Level1()
    : ILevel(), init_data({
            #define _ -1,
            #define L 0,
            #define R 1,
          _ _ _ _
          _ _ _ _
          _ _ _ _
          _ _ _ _

          _ _ _ _
          _ _ _ _
          _ _ _ _
          _ _ _ _

          _ _ _ _
          _ _ _ _
          _ _ _ _
          _ _ _ _

          _ _ _ _
          _ _ _ _
          _ _ _ _
          _ _ _ _

          L _ _ _
          _ _ _ _
          _ _ _ _
          _ _ _ _

          R _ L _
          _ _ _ _
          _ _ _ _
          _ _ _ _

          R _ L _
          L _ _ _
          _ _ _ _
          _ _ _ _

          R _ R _
          L _ L _
          _ _ _ _
          _ _ _ _

          L _ _ _
          _ _ _ _
          _ _ _ _
          _ _ _ _

          L _ R _
          _ _ _ _
          _ _ _ _
          _ _ _ _

          R _ L R
          L _ R _
          _ _ _ _
          _ _ _ _

          L _ L R
          R _ L _
          L _ R L
          R _ R _

          //1.25
          R _ _ R
          _ _ L _
          _ _ R _
          L _ L _

          //2.25
          L _ _ R
          _ _ R _
          _ _ _ _
          _ _ _ _

          //3.25
          R _ _ L
          _ _ R _
          _ _ L _
          L _ R _

          //4.25
          R _ _ R
          _ _ L _
          _ _ _ _
          R _ _ _

          //5.25
          R _ _ R
          _ _ L _
          _ _ R _
          L _ L _

          //6.25
          L _ _ R
          _ _ R _
          _ _ _ _
          _ _ _ _

          //7.25
          L _ _ _
          R _ L _
          R _ _ _
          L _ R _

          //8.25
          L _ _ L
          _ _ R _
          _ _ _ _
          L _ _ _

          //1
          R _ _ R
          _ _ R _
          L _ _ R
          _ _ L _

          //2
          L _ _ L
          _ _ L _
          R _ _ L
          _ _ L _

          //3
          R _ _ R
          _ _ R _
          L _ _ R
          _ _ L _

          //4
          L _ _ L
          _ _ R _
          R _ L _
          R _ L _

          //5
          R _ _ R
          _ _ R _
          L _ _ R
          _ _ L _

          //6
          L _ _ L
          _ _ L _
          R _ _ L
          _ _ L _

          //7
          R _ _ R
          _ _ R _
          L _ _ R
          _ _ L _

          //8
          L _ _ L
          L _ L _
          R _ L _
          R _ L _

          //1
          _ _ _ _
          _ _ _ _
          R _ R L
          _ L _ L

          //2
          _ _ _ _
          _ _ L _
          R _ R _
          L _ L _

          //3
          R _ _ _
          L _ _ _
          R _ _ R
          _ _ L _

          //4
          _ _ _ _
          _ _ _ _
          _ _ _ _
          _ L R L

          //5
          _ _ _ _
          _ _ _ _
          R _ R L
          _ L _ L

          //6
          _ _ _ _
          _ _ L _
          R _ L _
          L _ R _

          //7
          L _ R _
          L _ L _
          R _ L _
          R _ R _

          //8
          L _ _ R
          _ _ R _
          _ _ _ _
          _ _ _ _

          //1
          _ _ _ _
          _ _ _ _
          R _ R L
          _ L _ L

          //2
          _ _ _ _
          _ _ L _
          R _ R _
          L _ L _

          //3
          R _ _ _
          L _ _ _
          R _ _ R
          _ _ L _

          //4
          _ _ _ _
          _ _ _ _
          _ _ _ _
          _ L R L

          //5
          _ _ _ _
          _ _ _ _
          R _ R L
          _ L _ L

          //6
          _ _ _ _
          _ _ L _
          R _ L _
          L _ R _

          //7
          L _ R _
          L _ L _
          R _ L _
          R _ R _

          //8
          L _ _ R
          _ _ R _
          _ _ _ _
          _ _ _ _



            #undef L
            #undef R
            #undef _
      })
{
    // Music must be loaded here (NOT in class body)
    music = LoadMusicStream("assets/dance_dance_mania.ogg");
    // Now it's safe to use GetScreenWidth()

    leftArrow = LoadTexture("assets/left_arrow.png");
    rightArrow = LoadTexture("assets/right_arrow.png");

    float screenWidth = GetScreenWidth();
    leftLaneX  = ((screenWidth - leftArrow.width) / 2.0f) - leftArrow.width;
    rightLaneX = ((screenWidth - rightArrow.width) / 2.0f) + rightArrow.width;

    leftLaneColor = GRAY;
    rightLaneColor = GRAY;

    std::cout << init_data.size() << '\n';

    // Build notes
    for (int i = 0; i < init_data.size(); i++) {
        if (init_data[i] == -1) continue;

        int lane = init_data[i];

        Vector2 pos = {
            (lane == 0 ? (leftLaneX + leftArrow.width / 2 - 25) : (rightLaneX + leftArrow.width / 2 - 25)),
            -400
        };

        Color c = {
            static_cast<unsigned char>(GetRandomValue(100, 255)),
            static_cast<unsigned char>(GetRandomValue(100, 255)),
            static_cast<unsigned char>(GetRandomValue(100, 255)),
            255
        };

        float spawnTime = note_delay * (i);
        std::cout << spawnTime << '\n';
        notes.emplace_back(spawnTime, lane, pos, c);
    }
}

// Update
void Level1::update() {
    // MUSIC
    if (!musicStarted) {
        PlayMusicStream(music);
        musicStarted = true;
    }

    UpdateMusicStream(music);
    songTime = GetMusicTimePlayed(music);

    // DRAW ARROWS

    // INPUT HIT
    if (IsKeyPressed(KEY_LEFT)) {
        for (auto &n : notes)
            if (n.lane == 0) n.TryHit(songTime, hitWindow, hitLineY);
    }

    if (IsKeyPressed(KEY_RIGHT)) {
        for (auto &n : notes)
            if (n.lane == 1) n.TryHit(songTime, hitWindow, hitLineY);
    }

    if (IsKeyDown(KEY_LEFT)) {
        leftLaneColor = WHITE;
    } else {
        leftLaneColor = GRAY;
    }

    if (IsKeyDown(KEY_RIGHT)) {
        rightLaneColor = WHITE;
    } else {
        rightLaneColor = GRAY;
    }

    // REMOVE hit or missed
    std::erase_if(notes,
                  [&](const Note& n){
                      return n.hit || n.position.y > GetScreenHeight() + 50;
                  });
}

// Draw
void Level1::draw() {
    // DrawRectangle(leftLaneX,  hitLineY, 50, 50, WHITE);
    // DrawRectangle(rightLaneX, hitLineY, 50, 50, WHITE);

    DrawTexture(leftArrow, leftLaneX, hitLineY, leftLaneColor);
    DrawTexture(rightArrow, rightLaneX, hitLineY, rightLaneColor);

    // UPDATE + DRAW NOTES
    for (auto &n : notes) {
        n.Update(songTime, speed, hitLineY);
        n.Draw();
    }
}

// Destructor
Level1::~Level1() {
    UnloadTexture(leftArrow);
    UnloadTexture(rightArrow);
    UnloadMusicStream(music);
}

