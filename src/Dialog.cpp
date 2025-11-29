//
// Created by tamer on 11/29/2025.
//

#include "Dialog.h"

#include "Globals.h"

Dialog::Dialog(const std::string& filename, const vec2 pos) {
    this->person = LoadTexture(filename.c_str());
    this->pos = pos;
}

void Dialog::draw() {
    std::string longest_string =
    lines.empty() ? "" :
    *std::max_element(lines.begin(), lines.end(),
        [](const string &a, const string &b) { return a.size() < b.size(); });

    float rect_width = MeasureText(longest_string.c_str(), 20) + 20;
    float rect_height = lines.size() * 22.0f + 20.0f;

    Rectangle rect = {
        .x = pos.x,
        .y = pos.y,
        .width = rect_width,
        .height = rect_height
    };

    DrawTexture(person, GetScreenWidth() / 2 - 780, 0, WHITE);
    //DrawTexture(personTexture[personID], 0, 720, WHITE);
    DrawRectangle(rect.x, rect.y, rect.width, rect.height, BROWN);
    DrawRectangleLines(rect.x, rect.y, rect.width, rect.height, BLACK);

    for (int i = 0; i < lines.size(); i++) {
        DrawText(lines[i].c_str(), rect.x + 5, rect.y + i * 20 + 10, 20, WHITE);
    }
}

void Dialog::add_line(const string &line) {
    lines.push_back(line);
}

Dialog::~Dialog() {
    UnloadTexture(person);
}
