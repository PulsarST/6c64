#pragma once
#include "raylib.h"

class Note {
public:
    float time;          // When the note should reach the arrow
    int lane;            // 0 = left, 1 = right
    bool hit;

    Vector2 position{};    // Current note position
    Color color{};

    // Constructor
    Note(float t, int l, Vector2 startPos, Color c);

    // Move note downward based on music time
    void Update(float songTime, float speed, float pad_pos_y);

    // Draw note rectangle
    void Draw() const;

    // Check if note is touching arrow at hitLine
    [[nodiscard]] bool IsColliding(float hitLineY) const;

    // Check if player hit at correct time
    bool TryHit(float songTime, float hitWindow, float hitLineY);
};
