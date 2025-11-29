//
// Created by tamer on 11/29/2025.
//

#ifndef PUNKVERSEPROJECT_BUTTON_H
#define PUNKVERSEPROJECT_BUTTON_H
#include <functional>
#include <string>

#include "raylib.h"
#include "../types.h"

namespace ui {
    class Button {
    public:
        Button() = delete;
        /*
         * path is used for Texture2D and represents a path to the texture
         * idle is idle color when the button doesn't pushed or hovered, BUT it shouldn't' contain 255 values,
         * because it's calculate automatically colours for hover and push states
         * pos it's the position of the Button on screen it represents a Vector2
         * on_click is a function which calling when Button is pushed
         */
        explicit Button(const std::string& path, std::string  text, vec2 pos, Color idle, std::function<void()> on_click);
        Button(const Button&) = delete;
        Button(Button&&) = default;

        Button& operator=(const Button&) = delete;
        Button& operator=(Button&&) = default;

        void draw() const;
        void update();

        ~Button();

    private:
        Texture2D texture;
        vec2 pos;
        std::string text;
        Color current_color{};
        Color idle_color{};
        Color hover_color{};
        Color click_color{};
        std::function<void()> on_click;
    };
} // ui

#endif //PUNKVERSEPROJECT_BUTTON_H