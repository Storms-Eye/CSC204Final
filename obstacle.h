#pragma once

// Not all variables are used by certain managers, such as the tree, which is stationary. 
struct Obstacle
{
    float x;
    float y;
    float w;
    float h;
    float dx; // Distance per second.
    float dy;
};
