//
// Created by tamer on 11/29/2025.
//

#ifndef PUNKVERSEPROJECT_DIALOGMANAGER_H
#define PUNKVERSEPROJECT_DIALOGMANAGER_H

#include "Dialog.h"

class DialogManager {
public:
    void addDialog(const std::string& path, vec2 pos);
    void draw();
    void update();

    void addLines(int i, std::vector<std::string> lines);

private:
    std::vector<Dialog> dialogs;
    int currentDialogIndex = 0;
    bool isFinished = false;
};


#endif //PUNKVERSEPROJECT_DIALOGMANAGER_H