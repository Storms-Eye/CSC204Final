#pragma once

#include "draw_utils.h"
#include <vector>

class Obstacle
{
private:
    float x;
    float gapCY; // Y-coordinate of the centre of the gap
    bool scored = false;

public:
    explicit Obstacle(float startX);
    void update() {}
    bool hits(float bx, float by) const;
};

void drawObstacles(const std::vector<Obstacle> &pipes);
