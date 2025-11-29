//
// Created by tamer on 11/29/2025.
//

#ifndef PUNKVERSEPROJECT_MENU_H
#define PUNKVERSEPROJECT_MENU_H
#include "ILevel.h"
#include "ui/Button.h"


class Menu final : public ILevel {
public:
    explicit Menu();

    void draw() override;

    void update() override;

    ~Menu() override;

private:
    ui::Button play_button;
    ui::Button quit_button;
    Texture2D background{};
};


#endif //PUNKVERSEPROJECT_MENU_H