#include "car-manager.h"

extern GLuint carTextureID;

void CarManager::draw()
{
    for (auto &car : cars)
    {
        float cx = car.x;
        float cy = car.y;

        glPushMatrix();
        glTranslatef(cx, cy, 0.0f);
        glColor3f(1.0f, 1.0f, 1.0f);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, carTextureID);
        texturedQuad(0.0f, 0.0f, CAR_SIZE, CAR_SIZE);
        glDisable(GL_TEXTURE_2D);
        glPopMatrix();
    }
}

void CarManager::addCar(float x, float y)
{
    cars.push_back({x, y, LOG_SIZE_W, LOG_SIZE_H, LOG_SPEED, 0.0f});
}

void CarManager::update()
{
    for (auto &car : cars)
    {
        // TODO: Add or subtract dx based on the time passed.
    }
}
