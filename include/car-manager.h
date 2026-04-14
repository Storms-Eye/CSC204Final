#pragma once

#include "draw_utils.h"
#include "obstacle.h"
#include <vector>

class CarManager
{
private:
    std::vector<Obstacle> cars;
    static constexpr int MOVE_INTERVAL = 20; 
    
public:
    void draw();
    void update();
    
    void addCar(float x, float y, float speed = CAR_SPEED);
};
