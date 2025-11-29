#ifndef PUNKVERSEPROJECT_LEVEL1_H
#define PUNKVERSEPROJECT_LEVEL1_H

#include <vector>
#include "ILevel.h"
#include "raylib.h"
#include "Note.h"

class Level1 final : public ILevel {
public:
    Level1();
    ~Level1() override;

    void draw() override;
    void update() override;

private:
    std::vector<Note> notes;
    std::vector<int> init_data;

    // music
    Music music{};

    Texture2D leftArrow;
    Texture2D rightArrow;

    // lane positions (calculated in constructor)
    float leftLaneX;
    float rightLaneX;

    Color leftLaneColor;
    Color rightLaneColor;

    // timing
    float bpm = 90.f;
    float splits = 4.f;
    float note_delay = 60.f / bpm / splits;

    float spawnY = -400.f;
    float hitLineY = 500;
    float timeToFall = 2.0f; // seconds for note to reach hit line
    float speed = (hitLineY - spawnY) / timeToFall;

         // where arrows are
    // float speed = 300.0f;      // falling speed

    float hitWindow = 0.15f;   // seconds

    bool musicStarted = false;
    float songTime = 0.f;
};

#endif
