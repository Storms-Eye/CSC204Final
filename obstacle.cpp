#include "obstacle.h"
#include "draw_utils.h"
#include <cstdlib>

Obstacle::Obstacle(float startX) : x(startX)
{
}

bool Obstacle::hits(float bx, float by) const
{
    return false;
}

void drawObstacles(const std::vector<Obstacle> &obstacles)
{
    for (const auto &p : obstacles)
    {
    }
}
