#pragma once

// Not all variables are used by certain managers, such as the tree, which is stationary. 
struct Obstacle
{
    float x;
    float y;
    float width;
    float height;
    float speed; // Horizontal speed. 
};
