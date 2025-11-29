//
// Created by tamer on 11/29/2025.
//

#ifndef PUNKVERSEPROJECT_DIALOGMANAGER_H
#define PUNKVERSEPROJECT_DIALOGMANAGER_H

#include "Dialog.h"

class DialogManager {
public:
    void addDialog(Texture2D *texture, vec2 pos);
    void draw();
    void update();

    void addLines(int i, std::vector<std::string> lines);

    [[nodiscard]] bool getIsFinished() const { return isFinished; }

private:
    std::vector<Dialog> dialogs;
    int currentDialogIndex = 0;
    bool isFinished = false;
};


#endif //PUNKVERSEPROJECT_DIALOGMANAGER_H