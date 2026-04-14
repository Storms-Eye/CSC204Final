#pragma once

class Obstacle
{
private:
    float x, y;

public:
    Obstacle(float x, float y);

    bool hits(float fx, float fy);

    virtual void draw() = 0;
    virtual void update() = 0;
};
