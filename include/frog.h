#pragma once

#include "draw_utils.h"
#include <cstdlib>

class Frog
{
private:
    float x = WIN_W / 2.0f - FROG_SIZE / 2.0f;
    float y = 0.0f;
    int lives;

public:
    Frog();

    bool dead();
    void draw();
    void update();
    void revive();
    void reset();

    int getLives();
    
    void hopNegX();
    void hopNegY();
    void hopPosX();
    void hopPosY();
};
