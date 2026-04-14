#pragma once

#include "draw_utils.h"
#include <cstdlib>

struct Frog
{
    float x = WIN_W / 2.0f - FROG_SIZE / 2.0f;
    float y = 0.0f;
    void reset();
    bool dead();
    void draw();
    void update();

    void hopNegX();
    void hopNegY();
    void hopPosX();
    void hopPosY();
};
