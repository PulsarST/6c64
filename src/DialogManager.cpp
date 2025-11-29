//
// Created by tamer on 11/29/2025.
//

#include "DialogManager.h"

void DialogManager::addDialog(const std::string& path, vec2 pos) {
    dialogs.emplace_back(path, pos);
}

void DialogManager::draw() {
    if (!isFinished)
        dialogs[currentDialogIndex].draw();
}

void DialogManager::update() {
    if (IsKeyPressed(KEY_ENTER)) {
        if (currentDialogIndex < dialogs.size() - 1) {
            currentDialogIndex++;
        } else {
            isFinished = true;
        }
    }
}


void DialogManager::addLines(int i, std::vector<std::string> lines) {
    if (i < dialogs.size()) {
        for (auto& line : lines) {
            dialogs[i].add_line(line);
        }
    }
}
