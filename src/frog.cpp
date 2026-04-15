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

bool Frog::dead(CarManager carM, LogManager logM, TreeManager treeM)
{
    bool dead = false;

    // Out of horizontal bounds (e.g. rode off edge of screen on a log)
    if (x < 0 || x + FROG_SIZE > WIN_W)
    {
        return true;
    }

    for (auto car : carM.getCars())
    {
        if (x == car.x && y == car.y)
            return true;
    }

    if (y == FROG_SIZE * 6 || y == FROG_SIZE * 7)
    {
        bool onLog = false;
        for (auto log : logM.getLogs())
        {
            if (y == log.y && x + FROG_SIZE > log.x && x < log.x + log.width)
            {
                onLog = true;
                break;
            }
        }
        if (!onLog)
            return true;
    }

    for (auto tree : treeM.getTrees())
    {
        if (x == tree.x && y == tree.y)
            return true;
    }

    return false;
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

void Frog::rideLog(LogManager &logM)
{
    if (y != FROG_SIZE * 6 && y != FROG_SIZE * 7)
        return;

    for (auto &log : logM.getLogs())
    {
        if (y == log.y && x + FROG_SIZE > log.x && x < log.x + log.width)
        {
            // Move frog by same amount the log moves each interval
            float step = (log.speed > 0) ? FROG_SIZE : -FROG_SIZE;
            x += step;
            // Don't clamp — let dead() catch out-of-bounds naturally,
            // but also catch it here so frog doesn't wrap or glitch
            if (x < 0 || x + FROG_SIZE > WIN_W)
            {
                // Frog rode off screen — treat as dead by placing out of bounds
                x = -FROG_SIZE;
            }
            return;
        }
    }
}