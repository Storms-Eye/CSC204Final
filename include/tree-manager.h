#pragma once

#include "draw_utils.h"
#include "obstacle.h"
#include <vector>

class TreeManager
{
private:
    std::vector<Obstacle> trees;

public:
    void draw();
    void update();
		std::vector<Obstacle> getTrees();
    void addTree(float x, float y);
};
