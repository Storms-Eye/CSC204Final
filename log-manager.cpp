#include "log-manager.h"

extern GLuint logTextureID;

void LogManager::draw()
{
    for (auto &obstacle : obstacles)
    {
        float cx = obstacle.x;
        float cy = obstacle.y;

        glPushMatrix();
        glTranslatef(cx, cy, 0.0f);
        glColor3f(1.0f, 1.0f, 1.0f);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, logTextureID);
        texturedQuad(0.0f, 0.0f, LOG_SIZE_W, LOG_SIZE_H);
        glDisable(GL_TEXTURE_2D);
        glPopMatrix();
    }
}

void LogManager::addLog(float x, float y)
{
    obstacles.push_back({x, y, LOG_SIZE_W, LOG_SIZE_H, LOG_SPEED, 0.0f});
}

void LogManager::update()
{
    for (auto &obstacle : obstacles)
    {
        // TODO: Add or subtract dx based on the time passed.
    }
}
