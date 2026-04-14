#include "log.h"

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
        texturedQuad(0.0f, 0.0f, LOG_SIZE, LOG_SIZE);
        glDisable(GL_TEXTURE_2D);
        glPopMatrix();
    }
}
