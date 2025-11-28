//
// Created by tamer on 11/28/2025.
//

#include "Player.h"

#include <cmath>

#include "Bullet.h"
#include "raylib.h"
#include "types.h"

void Player::draw() {
    DrawRectangle(GetScreenWidth() / 2, GetScreenHeight() / 2 - 50, 50, 50, WHITE);
}

void Player::update(float deltaTime) {
    vec2 mouse_pos = GetMousePosition();
    vec2 player_pos = {.x = GetScreenWidth() / 2.0f, .y = GetScreenHeight() / 2.0f - 50.0f};
    angle = atan2(mouse_pos.y - player_pos.y, mouse_pos.x - player_pos.x);

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        bullets.emplace_back(player_pos, angle, 5,100);
}

