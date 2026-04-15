#pragma once

#include "draw_utils.h"
#include "obstacle.h"
#include <vector>

class LogManager
{
private:
    std::vector<Obstacle> obstacles;
    static constexpr int MOVE_INTERVAL = 30;  // Move every 30 frames
public:
    void draw();
    void update();
    std::vector<Obstacle>& getLogs();  
    void addLog(float x, float y, float speed = LOG_SPEED);
};
