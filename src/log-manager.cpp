#include "../include/log-manager.h"

extern GLuint logTextureID;
extern int gFrame;

void LogManager::draw()
{
    for (auto &log : obstacles)
    {
        float cx = log.x;
        float cy = log.y;

        glPushMatrix();
        glTranslatef(cx, cy, 0.0f);
        glColor3f(1.0f, 1.0f, 1.0f);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, logTextureID);
        texturedQuad(0.0f, 0.0f, log.width, log.height);
        glDisable(GL_TEXTURE_2D);
        glPopMatrix();
    }
}

std::vector<Obstacle> LogManager::getLogs()
{
	return obstacles;
}
void LogManager::addLog(float x, float y, float speed)
{
    obstacles.push_back({x, y, LOG_SIZE_W, LOG_SIZE_H, speed});
}

void LogManager::update()
{
    // Move logs every 30 frames
    if (gFrame % MOVE_INTERVAL == 0)
    {
        for (size_t i = 0; i < obstacles.size(); ++i)
        {
            if (obstacles[i].speed > 0)
            {
                obstacles[i].x += FROG_SIZE;
            }
            else if (obstacles[i].speed < 0)
            {
                obstacles[i].x -= FROG_SIZE;
            }
            
            if (obstacles[i].x > WIN_W)
            {
                obstacles[i].x = -LOG_SIZE_W;
            }
            else if (obstacles[i].x < -LOG_SIZE_W)
            {
                obstacles[i].x = WIN_W;
            }
        }
    }
}
