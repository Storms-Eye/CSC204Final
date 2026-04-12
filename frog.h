#pragma once

#include "draw_utils.h"
#include <cstdlib>

struct Frog
{
    float x = 180.0f;
    float y = WIN_H / 2.0f;

    void reset();
    bool dead();
    void draw();
    void update();

    void hopNegX();
    void hopNegY();
    void hopPosX();
    void hopPosY();
};
