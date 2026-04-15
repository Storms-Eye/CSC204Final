#include "../include/frog.h"
#include "../include/draw_utils.h"
#include "../textures/frog.h"
#include <array>
extern GLuint frogTextureID;

Frog::Frog()
{
  lives = 3;
}

void Frog::setPos(int newX, int newY)
{
	x = newX;
	y = newY;
}
void Frog::draw()
{
    float cx = x;
    float cy = y;
    glPushMatrix();
    glTranslatef(cx, cy, 0.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, frogTextureID);
    texturedQuad(0.0f, 0.0f, FROG_SIZE, FROG_SIZE);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
    glPopMatrix();
}
std::array<bool, 5> Frog::getWins()
{
	return winPlatforms;
}
int Frog::hasWon()
{
	if(y == WIN_H-FROG_SIZE)
	{
		int location = static_cast<int>(x/FROG_SIZE);
		if((location%2 == 0) && winPlatforms.at(location/2) == false)
		{
			winPlatforms[location/2] = true;
			int returnvalue = 3;
			for(bool value : winPlatforms)
			{
				if(!value) returnvalue = 0;
			}
			return returnvalue;
		}
		else
		{
			return 1;
		}
	}
	return 2;
}


void Frog::revive(bool hasWon)
{
  x = WIN_W / 2.0f - FROG_SIZE / 2.0f;
	y = 0.0f;
  if(!hasWon) lives--;
}

void Frog::reset()
{
	x = WIN_W / 2.0f - FROG_SIZE / 2.0f;
	y = 0.0f;
  lives = 3;
	winPlatforms = {false, false, false, false, false};
}

bool Frog::dead(CarManager carM, LogManager logM, TreeManager treeM) //is frog dead?
{
	bool dead = false;
	for(auto car : carM.getCars())
	{
		if(x == car.x && y == car.y)
		{
			dead = true;
			return dead;
		}
	}
	if(y < 720 - FROG_SIZE && y > 720 - FROG_SIZE*3)
	{
		for(auto log : logM.getLogs())
		{
			if(!(x == log.x && y == log.y))
			{
				dead = true;
				return dead;
			}
		}
	}
	for(auto tree : treeM.getTrees())
	{
		if(x == tree.x && y == tree.y)
		{
			dead = true;
			return dead;
		}
	}
	return dead;
}

int Frog::getLives()
{
    return lives;
}

void Frog::hopPosX()
{
    if ((x + FROG_SIZE) < WIN_W)
    {
        x += FROG_SIZE;
    }
}

void Frog::hopNegX()
{
    if ((x - FROG_SIZE) >= 0)
    {
        x -= FROG_SIZE;
    }
}

void Frog::hopPosY()
{
    if ((y + FROG_SIZE) < WIN_H)
    {
        y += FROG_SIZE;
    }
}

void Frog::hopNegY()
{
    if ((y - FROG_SIZE) >= 0)
    {
        y -= FROG_SIZE;
    }
}
