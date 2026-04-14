#pragma once

#include "draw_utils.h"
#include "obstacle.h"
#include <vector>

class CarManager
{
private:
    std::vector<Obstacle> cars;
public:
    void draw();
    void update();
    
    void addCar(float x, float y);
};
