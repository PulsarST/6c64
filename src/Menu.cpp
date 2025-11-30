//
// Created by tamer on 11/29/2025.
//

#include "Menu.h"

#include <iostream>

#include "Globals.h"

Menu::Menu() : play_button("assets/button.png", "Play", (vec2){.x = WIN_WIDTH / 2, .y = WIN_HEIGHT / 2},
                           (Color){230, 103, 103, 255},
                           []() { std::cout << "ITS WORKING !" << "\n"; }), quit_button(
                   "assets/button.png", "Quit", (vec2){.x = WIN_WIDTH / 2, .y = WIN_HEIGHT / 2},
                   (Color){230, 103, 103, 255}, []() {
                   }) {
    background = LoadTexture("assets/background_menu.png");
    chrs = LoadTexture("assets/chrs_menu.png");

    vec2 play_button_size = play_button.get_size();
    play_button.set_pos((GetScreenWidth() - play_button_size.x) / 2,
                        (GetScreenHeight() - play_button_size.y) / 2);

    vec2 quit_button_size = quit_button.get_size();

    quit_button.set_pos((GetScreenWidth() - quit_button_size.x) / 2,
                        (GetScreenHeight() - quit_button_size.y) / 2 + 120);

    blank = LoadTexture("assets/BF2.png");

    intro.addDialog(&blank, vec2 {50,6.f * GetScreenHeight() / 8});
    intro.addLines(0, {
        "The prom. is coming very soon! I can’t wait to get there"
    });

    intro.addDialog(&blank, vec2 {50,6.f * GetScreenHeight() / 8});
    intro.addLines(1, {
        "I really want to invite Madina to dance, because I’ve been in love with her since childhood."
    });

    intro.addDialog(&blank, vec2 {50,6.f * GetScreenHeight() / 8});
    intro.addLines(2, {
        "But I can’t just go to her like this!",
        "I need a cool car to pick her up from home, and a gift to make her happy."
    });

    intro.addDialog(&blank, vec2 {50,6.f * GetScreenHeight() / 8});
    intro.addLines(3, {
        "There’s no other way! These are the rules of our school.",
        "The law of the jungle, so to speak."
    });

    intro.addDialog(&blank, vec2 {50,6.f * GetScreenHeight() / 8});
    intro.addLines(4, {
        "I need to save up money for the gift;",
        "I can work as a food delivery guy for a while.",
        "But there is no way I’ll be able to save up for a car in time.",
        "Come to think of it… My best friend has a car, but I really doubt he’ll lend it to me.",
        "Well, in any case, it’s better to try asking than doing nothing at all."
    });

    intro.addDialog(&blank, vec2 {50,6.f * GetScreenHeight() / 8});
    intro.addLines(5, {
        "I’m very afraid of failing, because she’s the love of my whole life…"
    });


    play_button.set_on_click([&]() {
        play_di = true;
    });

    quit_button.set_on_click([]() {
        CloseWindow();
    });
}

void Menu::draw() {

    if (play_di) {
        intro.draw();
    } else {
        DrawTexture(background, 0, 0, WHITE);
        DrawTexture(chrs, 0, 0, WHITE);
        play_button.draw();
        quit_button.draw();

        if (play_di) {
            intro.draw();
        }
    }
}

void Menu::update() {
    if (play_di) {
        intro.update();
    }
    else {
        play_button.update();
        quit_button.update();
    }

    if (intro.getIsFinished()) {
        currentLevel = LEVEL1;
    }
}

Menu::~Menu() {
    UnloadTexture(background);
}
