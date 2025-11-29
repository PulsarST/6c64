//
// Created by tamer on 11/29/2025.
//

#include "Button.h"

#include <raylib.h>

#define DIFF 50

namespace ui {
    Button::Button(const std::string& path, std::string  text, const vec2 pos, Color idle, std::function<void()> on_click)
        : texture(LoadTexture(path.c_str())), pos(pos), text(std::move(text)), idle_color(idle), on_click(std::move(on_click)) {

        hover_color = Color(idle_color.r + DIFF, idle_color.g + DIFF, idle_color.b + DIFF, 255);
        click_color = Color(idle_color.r - DIFF, idle_color.g - DIFF, idle_color.b - DIFF, 255);
        current_color = idle_color;
    }

    void Button::draw() const {
        DrawTexture(texture, pos.x, pos.y, current_color);

        int text_screen_width = MeasureText(text.c_str(), 20);
        int texture_width = texture.width;
        int texture_height = texture.height;

        int gap_x = (texture_width - text_screen_width) / 2;
        int gap_y = (texture_height - 20) / 2;

        DrawText(text.c_str(), pos.x + gap_x, pos.y + gap_y, 20, BLACK);

    }

    void Button::update() {
        const vec2 mouse_pos = GetMousePosition();
        const Rectangle button_rect = {
            .x = pos.x,
            .y = pos.y,
            .width = static_cast<float>(texture.width),
            .height = static_cast<float>(texture.height)
        };

        if (CheckCollisionPointRec(mouse_pos, button_rect)) {
            current_color = hover_color;

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                current_color = click_color;
                on_click();
            }
        } else {
            current_color = idle_color;
        }

    }

    Button::~Button() {
        UnloadTexture(texture);
    }
} // ui