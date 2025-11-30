//
// Created by tamer on 11/29/2025.
//

#ifndef PUNKVERSEPROJECT_MENU_H
#define PUNKVERSEPROJECT_MENU_H
#include "ILevel.h"
#include "AnimationSprite.h"
#include "DialogManager.h"
#include "ui/Button.h"


class Menu final : public ILevel {
public:
    explicit Menu();

    void draw() override;

    void update() override;

    ~Menu() override;

private:
    DialogManager intro;
    bool play_di = false;

    ui::Button play_button;
    ui::Button quit_button;
    Texture2D background{};
    Texture2D chrs{};

    Texture2D blank;
};


#endif //PUNKVERSEPROJECT_MENU_H