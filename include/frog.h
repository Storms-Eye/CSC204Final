#pragma once

#include "../include/car-manager.h"
#include "../include/log-manager.h"
#include "../include/tree-manager.h"
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
		std::array<bool, 5> getWins();
		void setPos(int a, int b);
		int hasWon();
		bool dead(CarManager carM, LogManager logM, TreeManager treeM);
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
