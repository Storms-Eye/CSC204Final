#pragma once

#include "draw_utils.h"
#include "obstacle.h"
#include <vector>

class LogManager
{
private:
    std::vector<Obstacle> obstacles;
public:
    void draw();
    void update();
    
    void addLog(float x, float y);
};
