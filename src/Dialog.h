//
// Created by tamer on 11/29/2025.
//

#ifndef PUNKVERSEPROJECT_DIALOG_H
#define PUNKVERSEPROJECT_DIALOG_H
#include <string>
#include <vector>

#include "types.h"

using std::vector;
using std::string;

class Dialog {
public:
    explicit Dialog(vec2 pos);

    void draw();

    [[nodiscard]] vec2 get_pos() const {
        return pos;
    }

    void set_pos(const vec2 &pos) {
        this->pos = pos;
    }

    [[nodiscard]] vec2 get_size() const {
        return size;
    }

    void set_size(const vec2 &size) {
        this->size = size;
    }

private:
    vector<string> lines;
    vec2 pos;
    vec2 size;
};

#endif //PUNKVERSEPROJECT_DIALOG_H
