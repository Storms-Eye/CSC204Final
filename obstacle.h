#pragma once

#include "draw_utils.h"
#include <vector>

class Obstacle
{
    float x;
    float gapCY; // Y-coordinate of the centre of the gap
    bool scored = false;

    explicit Obstacle(float startX);
    void update() { x -= PIPE_SPEED; }

    bool hits(float bx, float by) const;
};

void drawObstacles(const std::vector<Obstacle> &pipes);
