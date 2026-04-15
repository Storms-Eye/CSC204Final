#pragma once

#include "draw_utils.h"
#include "obstacle.h"
#include <vector>

class TreeManager
{
private:
    std::vector<Obstacle> trees = 
		{
			{0, 0, FROG_SIZE, FROG_SIZE, 0},
			{FROG_SIZE, 0, FROG_SIZE, FROG_SIZE, 0},
			{FROG_SIZE*2, 0, FROG_SIZE,FROG_SIZE, 0},
			{FROG_SIZE*3, 0, FROG_SIZE,FROG_SIZE, 0},
			{FROG_SIZE*5, 0, FROG_SIZE,FROG_SIZE, 0},
			{FROG_SIZE*6, 0, FROG_SIZE,FROG_SIZE, 0},
			{FROG_SIZE*7, 0, FROG_SIZE,FROG_SIZE, 0},
			{FROG_SIZE*8, 0, FROG_SIZE,FROG_SIZE, 0},
			{FROG_SIZE*8, FROG_SIZE, FROG_SIZE, FROG_SIZE, 0},
			{FROG_SIZE, FROG_SIZE, FROG_SIZE, FROG_SIZE, 0},
			{FROG_SIZE*3, FROG_SIZE*4, FROG_SIZE, FROG_SIZE, 0},
			{FROG_SIZE*6, FROG_SIZE*4, FROG_SIZE, FROG_SIZE, 0},
			{0, FROG_SIZE*4, FROG_SIZE, FROG_SIZE, 0},
			{0, FROG_SIZE*5, FROG_SIZE, FROG_SIZE, 0},
			{FROG_SIZE*8, FROG_SIZE*5, FROG_SIZE, FROG_SIZE, 0},
			{FROG_SIZE*2, FROG_SIZE*5, FROG_SIZE, FROG_SIZE, 0},
			{FROG_SIZE*4, FROG_SIZE*5, FROG_SIZE, FROG_SIZE, 0},
		};

public:
    void draw();
    void update();
		std::vector<Obstacle> getTrees();
    void addTree(float x, float y);
};
