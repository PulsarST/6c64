#include "Level1.h"

#include <cmath>
#include <iostream>

#include "Game.h"
#include "Globals.h"

Texture2D person_fr1;


// Constructor
Level1::Level1()
    : ILevel(), init_data({
            #define _ -1,
            #define L 0,
            #define R 1,
          _ _ _ _
          _ _ _ _
          _ _ _ _
          _ _ _ _

          _ _ _ _
          _ _ _ _
          _ _ _ _
          _ _ _ _

          _ _ _ _
          _ _ _ _
          _ _ _ _
          _ _ _ _

          _ _ _ _
          _ _ _ _
          _ _ _ _
          _ _ _ _

          R _ _ _
          _ _ _ _
          _ _ _ _
          _ _ _ _

          L _ R _
          _ _ _ _
          _ _ _ _
          _ _ _ _

          R _ R _
          L _ _ _
          _ _ _ _
          _ _ _ _

          R _ R _
          L _ L _
          _ _ _ _
          _ _ _ _

          R _ _ _
          _ _ _ _
          _ _ _ _
          _ _ _ _

          L _ R _
          _ _ _ _
          _ _ _ _
          _ _ _ _

          R _ R L
          R _ L _
          _ _ _ _
          _ _ _ _

          R _ R L
          R _ L _
          L _ R L
          R _ R _

          //1.25
          R _ _ L
          _ _ L _
          _ _ R _
          L _ L _

          //2.25
          R _ _ L
          _ _ L _
          _ _ _ _
          _ _ _ _

          //3.25
          R _ _ L
          _ _ L _
          _ _ R _
          L _ L _

          //4.25
          R _ _ R
          _ _ L _
          _ _ _ _
          L _ _ _

          //5.25
          R _ _ L
          _ _ L _
          _ _ R _
          L _ L _

          //6.25
          R _ _ L
          _ _ L _
          _ _ _ _
          _ _ _ _

          //7.25
          R _ _ _
          R _ L _
          R _ _ _
          L _ R _

          //8.25
          L _ _ L
          _ _ R _
          _ _ _ _
          L _ _ _

          //1
          L _ _ L
          _ _ R _
          L _ _ R
          _ _ R _

          //2
          L _ _ L
          _ _ R _
          L _ _ R
          _ _ L _

          //3
          L _ _ L
          _ _ R _
          L _ _ R
          _ _ R _

          //4
          L _ _ L
          _ _ R _
          R _ L _
          R _ L _

          //5
          L _ _ L
          _ _ R _
          L _ _ R
          _ _ R _

          //6
          L _ _ L
          _ _ R _
          L _ _ R
          _ _ L _

          //7
          L _ _ L
          _ _ R _
          L _ _ R
          _ _ R _

          //8
          L _ _ L
          _ _ R _
          L _ R _
          L _ R _

          //1
          R _ _ _
          _ _ _ _
          R _ L R
          _ L _ L

          //2
          _ _ _ _
          _ _ L _
          R _ _ _
          L _ L _

          //3
          R _ _ _
          L _ _ _
          R _ _ R
          _ _ L _

          //4
          _ _ _ _
          _ _ _ _
          _ _ _ _
          _ L R L

          //5
          _ _ _ _
          _ _ _ _
          R _ R L
          _ L _ L

          //6
          _ _ _ _
          _ _ L _
          R _ _ R
          _ R _ _

          //7
          L _ _ L
          _ R _ _
          L _ _ L
          _ R _ _

          //8
          L _ _ R
          _ _ R _
          _ _ _ _
          _ _ _ _

          //1
          _ _ _ _
          _ _ _ _
          R _ L R
          _ L _ L

          //2
          _ _ _ _
          _ _ L _
          R _ _ _
          L _ L _

          //3
          R _ _ _
          L _ _ _
          R _ _ R
          _ _ L _

          //4
          _ _ _ _
          _ _ _ _
          _ _ _ _
          _ L R L

          //5
          _ _ _ _
          _ _ _ _
          R _ R L
          _ L _ L

          //6
          _ _ _ _
          _ _ L _
          R _ _ R
          _ R _ _

          //7
          L _ _ L
          _ R _ _
          L _ _ L
          _ R _ _

          //8
          L _ _ R
          _ _ R _
          _ _ _ _
          _ _ _ _



            #undef L
            #undef R
            #undef _
      })
{
    // Music must be loaded here (NOT in class body)
    music = LoadMusicStream("assets/dance_dance_mania.ogg");
    music.looping = false;
    // Now it's safe to use GetScreenWidth()

    dance_bg = LoadTexture("assets/dance_bg.png");
    leftArrow = LoadTexture("assets/left_arrow.png");
    rightArrow = LoadTexture("assets/right_arrow.png");

    float screenWidth = GetScreenWidth();
    leftLaneX  = ((screenWidth - leftArrow.width) / 2.0f) - leftArrow.width;
    rightLaneX = ((screenWidth - rightArrow.width) / 2.0f) + rightArrow.width;

    leftLaneColor = GRAY;
    rightLaneColor = GRAY;

    std::cout << init_data.size() << '\n';

    // Build notes
    for (int i = 0; i < init_data.size(); i++) {
        if (init_data[i] == -1) continue;

        int lane = init_data[i];

        Vector2 pos = {
            (lane == 0 ? (leftLaneX + leftArrow.width / 2 - 25) : (rightLaneX + leftArrow.width / 2 - 25)),
            -400
        };

        Color c = {
            static_cast<unsigned char>(GetRandomValue(100, 255)),
            static_cast<unsigned char>(GetRandomValue(100, 255)),
            static_cast<unsigned char>(GetRandomValue(100, 255)),
            255
        };

        float spawnTime = note_delay * (i);
        std::cout << spawnTime << '\n';
        notes.emplace_back(spawnTime, lane, pos, c);
    }

    person_fr1 = LoadTexture("assets\\FR1.png");

    dialogManager.addDialog(&person_fr1,  vec2 {50,6.f * GetScreenHeight() / 8});
    dialogManager.addLines(0, {
        "Хэй Бро !",
        "Я слышал что тебе нужна машина, да ? Так я тебе могу помочь",
        "НООООООООООООООООООООООООООоооооооо !",
        "Ты Должен Победить Меня В Танцах !",
        "Если ты выйграешь то тачка твоя !",
        "Договорились !"
    });

    dialogManager.addDialog(&person_fr1,  vec2 {50,6.f * GetScreenHeight() / 8});
    dialogManager.addLines(1, {
        "Ок бро !",
        "Давай зажжём !"
        "Наша битва будет легендарной !"
    });

    bad_end_dialogue.addDialog(&person_fr1, vec2 {50,6.f * GetScreenHeight() / 8});
    bad_end_dialogue.addLines(0, {
        "Не плохо",
        "НОо ! Этого не достаточно !",
        "Тренируйся !",
        "Кчау !"
    });

    good_end_dialogue.addDialog(&person_fr1, vec2 {50,6.f * GetScreenHeight() / 8});
    good_end_dialogue.addLines(0, {
        "Я этого не ожидал ! Ты крут БРО !",
        "Тачка твоя",
        "Заслужил !"
    });
}

void Level1::update() {

    // FIRST DIALOG (before gameplay)
    if (!dialogManager.getIsFinished() && !isEndingDialog) {
        dialogManager.update();
        return;
    }

    // GAMEPLAY PART
    if (!isEndingDialog) {

        // start music
        if (!musicStarted) {
            PlayMusicStream(music);
            musicStarted = true;
        }

        UpdateMusicStream(music);
        songTime = GetMusicTimePlayed(music);

        // hit detection
        if (IsKeyPressed(KEY_LEFT)) {
            for (auto &n : notes)
                if (n.lane == 0 && n.TryHit(songTime, hitWindow, hitLineY))
                    rhythm_score++;
        }

        if (IsKeyPressed(KEY_RIGHT)) {
            for (auto &n : notes)
                if (n.lane == 1 && n.TryHit(songTime, hitWindow, hitLineY))
                    rhythm_score++;
        }

        leftLaneColor  = IsKeyDown(KEY_LEFT)  ? WHITE : GRAY;
        rightLaneColor = IsKeyDown(KEY_RIGHT) ? WHITE : GRAY;

        // remove hit/missed
        std::erase_if(notes, [&](const Note& n){
            return n.hit || n.position.y > GetScreenHeight() + 50;
        });

        // MUSIC ENDED → start ending dialog
        if (!IsMusicStreamPlaying(music)) {
            isEndingDialog = true;
            useGoodEnding = rhythm_score >= 100;
        }

        return;
    }

    // ENDING DIALOG PHASE
    if (isEndingDialog) {
        if (useGoodEnding)
            good_end_dialogue.update();
        else
            bad_end_dialogue.update();

        // ⬇️ ADD THIS CHECK HERE
        if ( (useGoodEnding && good_end_dialogue.getIsFinished()) ||
             (!useGoodEnding && bad_end_dialogue.getIsFinished()) ) {
            buket = true;

            currentLevel = LEVEL2;   // <--- SWITCH LEVEL
            }
    }
}

// Draw
void Level1::draw() {

    // 1. Intro dialogs
    if (!dialogManager.getIsFinished() && !isEndingDialog) {
        DrawTexture(dance_bg, 0, 0, WHITE);
        dialogManager.draw();
        return;
    }

    // 2. Ending dialogs
    if (isEndingDialog) {
        DrawTexture(dance_bg, 0, 0, WHITE);
        if (useGoodEnding)
            good_end_dialogue.draw();
        else
            bad_end_dialogue.draw();
        return;
    }

    // 3. Gameplay drawing
    DrawTexture(dance_bg, 0, 0, WHITE);
    DrawTexture(leftArrow, leftLaneX, hitLineY, leftLaneColor);
    DrawTexture(rightArrow, rightLaneX, hitLineY, rightLaneColor);

    for (auto &n : notes) {
        n.Update(songTime, speed, hitLineY);
        n.Draw();
    }

    DrawText(("Score: " + std::to_string(rhythm_score)).c_str(), 20, 40, 20, BLACK);
}


// Destructor
Level1::~Level1() {
    UnloadTexture(person_fr1);
    UnloadTexture(dance_bg);
    UnloadTexture(leftArrow);
    UnloadTexture(rightArrow);
    UnloadMusicStream(music);
}

