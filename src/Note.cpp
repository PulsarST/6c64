#include "Note.h"
#include <cmath>
#include <iostream>

Note::Note(const float t, const int l, const Vector2 startPos, const Color c) {
    time = t;
    lane = l;
    position = startPos;
    color = c;
    hit = false;
}

void Note::Update(const float songTime, const float speed, const float pad_pos_y) {
    if (hit) return;

    // FNF style: note should reach hitLine exactly at "time"
    float dt = songTime - time;   // how much the music passed the note time

    // speed = (hitLineY - spawnY) / note_delay;

    // Move downward based on note speed
    position.y = dt * speed + pad_pos_y;

    // position.y += speed * GetFrameTime() + pad_pos_y;



}

void Note::Draw() const {
    if (hit) return;

    DrawRectangle(static_cast<int>(position.x), static_cast<int>(position.y), 50, 50, color);

    // std::cout << "pos y: " << position.y << "\n";
}

bool Note::IsColliding(const float hitLineY) const {
    return (position.y + 50 >= hitLineY - 20 &&
            position.y <= hitLineY + 20);
}

bool Note::TryHit(const float songTime, const float hitWindow, const float hitLineY) {
    if (hit) return false;

    // Must collide with arrow
    if (!IsColliding(hitLineY)) return false;

    // Must be within timing window
    if (std::fabs(songTime - time) <= hitWindow) {
        hit = true;
        return true;
    }

    return false;
}
