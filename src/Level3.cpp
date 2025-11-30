//
// Created by tamer on 11/28/2025.
//

#include "Level3.h"

#include "Globals.h"

Level3::Level3() : ILevel() {
    father = LoadTexture("assets/FR1.png");
    fatherEnd.addDialog(&father, vec2 {50,6.f * GetScreenHeight() / 8});
    fatherEnd.addLines(0, {
        ""
    });

    granpa = LoadTexture("assets/grapna1.png");
    granpaEnd.addDialog(&granpa, vec2 {50,6.f * GetScreenHeight() / 8});
    granpaEnd.addLines(0, {
        ""
    });

    girl = LoadTexture("assets/GF2.png");
    hh = LoadTexture("assets/BF2.png");

    girlEnd.addDialog(&girl, vec2 {50,6.f * GetScreenHeight() / 8});

    girlEnd.addDialog(&hh, vec2 {50,6.f * GetScreenHeight() / 8});

    girlEnd.addLines(1, {
        "Hi, Madina! Do you want to go to the prom with me?!!",
    });

    girlEnd.addLines(0, {
        "Actually, I’ve been hoping you would invite me to the prom since kindergarten. You prepared so well, thank you for the gift. Let’s go!"
    });
}

void Level3::draw() {
    if (buket && !car_end) {
        fatherEnd.draw();
    } else if (!buket && car_end) {
        granpaEnd.draw();
    } else {
        girlEnd.draw();
    }
}

void Level3::update() {
    if (buket && !car_end) {
        fatherEnd.update();
    } else if (!buket && car_end) {
        granpaEnd.update();
    } else {
        girlEnd.update();
    }
}

Level3::~Level3() {
    UnloadTexture(father);
    UnloadTexture(granpa);
    UnloadTexture(girl);
    UnloadTexture(hh);
}

