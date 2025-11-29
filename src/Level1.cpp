#include "Level1.h"
#include <iostream>

// Constructor
Level1::Level1()
    : ILevel(), init_data({
          -1, -1, -1, -1,
          -1, -1, -1, -1,
          -1, -1, -1, -1,
          -1, -1, -1, -1,

          -1, -1, -1, -1,
          -1, -1, -1, -1,
          -1, -1, -1, -1,
          -1, -1, -1, -1,

          0, 1, 0, 1,
          -1, 0, 1, 1,
          0, 1, 1, 1
      })
{
    // Music must be loaded here (NOT in class body)
    music = LoadMusicStream("assets/mus.mp3");
    // Now it's safe to use GetScreenWidth()
    leftLaneX  = GetScreenWidth()  / 2.0f - 150;
    rightLaneX = GetScreenWidth()  / 2.0f + 100;   // FIXED (you used GetScreenHeight!)

    std::cout << init_data.size() << '\n';

    // Build notes
    for (int i = 0; i < init_data.size(); i++) {
        if (init_data[i] == -1) continue;

        int lane = init_data[i];

        Vector2 pos = {
            (lane == 0 ? leftLaneX : rightLaneX),
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

    // REMOVE hit or missed
    std::erase_if(notes,
                  [&](const Note& n){
                      return n.hit || n.position.y > GetScreenHeight() + 50;
                  });
}

// --------------------
// Draw
// --------------------
void Level1::draw() {
    DrawRectangle(leftLaneX,  hitLineY, 50, 50, WHITE);
    DrawRectangle(rightLaneX, hitLineY, 50, 50, WHITE);
    // UPDATE + DRAW NOTES
    for (auto &n : notes) {
        n.Update(songTime, speed, hitLineY);
        n.Draw();
    }
}

// Destructor
Level1::~Level1() {
    UnloadMusicStream(music);
}

