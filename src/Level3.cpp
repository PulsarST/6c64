//
// Created by tamer on 11/28/2025.
//

#include "Level3.h"

#include "Globals.h"

Level3::Level3() : ILevel() {
    hh = LoadTexture("assets/BF2.png");

    father = LoadTexture("assets/FATH1.png");
    girl = LoadTexture("assets/GF2.png");


    fatherEnd.addDialog(&hh, vec2 {50,6.f * GetScreenHeight() / 8});        // 0

    fatherEnd.addLines(0, {
        "Hi, Madina! Do you want to go to the prom with me???!"
    });

    fatherEnd.addDialog(&girl, vec2 {50,6.f * GetScreenHeight() / 8});      // 1

    fatherEnd.addLines(1, {
        "Actually, I have been hoping you would invite me to the prom since kindergarten.",
        "I really would love to go with you. However, you didnt prepare well enough.",
        "Thats disappointing. Unfortunately, I cant accept your invitation, and I will go to the prom alone."

    });
    fatherEnd.addDialog(&hh, vec2 {50,6.f * GetScreenHeight() / 8});        //2

    fatherEnd.addLines(2, {
        "..."
    });


    fatherEnd.addLines(0, {
        "Madinas father comes out."
    });

    fatherEnd.addDialog(&father, vec2 {50,6.f * GetScreenHeight() / 8});        // 3

    fatherEnd.addLines(3, {
        " Dont be upset. I see how hard you tried. Your car is really cool."
    });

    fatherEnd.addDialog(&father, vec2 {50,6.f * GetScreenHeight() / 8});        // 4

    fatherEnd.addLines(4, {
        "You know…"
    });
    fatherEnd.addDialog(&father, vec2 {50,6.f * GetScreenHeight() / 8});        // 5

    fatherEnd.addLines(5, {
        "I will go with you. Im very curious what it feels like to ride this car.",
        "And I will keep you company so you don’t die of loneliness."

    });
    fatherEnd.addDialog(&father, vec2 {50,6.f * GetScreenHeight() / 8});        //6

    fatherEnd.addLines(6, {
        "Dad will tell you many stories from his life, get ready."
    });

    fatherEnd.addDialog(&hh, vec2 {50,6.f * GetScreenHeight() / 8});        //7

    fatherEnd.addLines(7, {
            "..."
    });

    fatherEnd.addDialog(&hh, vec2 {50,6.f * GetScreenHeight() / 8});        //8


    fatherEnd.addLines(8, {
        "Alright then…"
    });

    // --------------------------------
    granpa = LoadTexture("assets/grapna1.png");
    granpaEnd.addDialog(&granpa, vec2 {50,6.f * GetScreenHeight() / 8});
    granpaEnd.addLines(0, {
        ""
    });



    // --------------------------------

    girlEnd.addDialog(&hh, vec2 {50,6.f * GetScreenHeight() / 8});

    girlEnd.addDialog(&girl, vec2 {50,6.f * GetScreenHeight() / 8});

    girlEnd.addLines(0, {
        "Hi, Madina! Do you want to go to the prom with me?!!",
    });

    girlEnd.addLines(1, {
        "Actually, I’ve been hoping you would invite me to the prom since kindergarten.",
        "You prepared so well, thank you for the gift. Let’s go!"
    });

    // -----------------------------------------------------------


}

void Level3::draw() {
    if (!buket && car_end) {
        fatherEnd.draw();
    } else if (buket && !car_end) {
        granpaEnd.draw();
    } else {
        girlEnd.draw();
    }
}

void Level3::update() {
    if (!buket && car_end) {
        fatherEnd.update();
    } else if (buket && !car_end) {
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

