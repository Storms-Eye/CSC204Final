#pragma once

#include "draw_utils.h"
#include "obstacle.h"
#include <vector>

class CarManager
{
private:
    std::vector<Obstacle> cars;
    static constexpr int MOVE_INTERVAL = 30; 
    
public:
    void draw();
    void update();
    std::vector<Obstacle> getCars();

    void addCar(float x, float y, float speed = CAR_SPEED);
};
