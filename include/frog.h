#pragma once

#include "draw_utils.h"
#include <cstdlib>
#include <array>
class Frog
{
private:
    float x = WIN_W / 2.0f - FROG_SIZE / 2.0f;
    float y = 0.0f;
    int lives;
		std::array<bool, 5> winPlatforms = {false, false, false, false, false};
public:
    Frog();
		int hasWon();
    bool dead();
    void draw();
    void update();
    void revive(bool hasWon);
    void reset();

    int getLives();
    
    void hopNegX();
    void hopNegY();
    void hopPosX();
    void hopPosY();
};
