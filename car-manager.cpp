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
        texturedQuad(0.0f, 0.0f, car.width, car.height);
        glDisable(GL_TEXTURE_2D);
        glPopMatrix();
    }
}

void CarManager::addCar(float x, float y)
{
    cars.push_back({x, y, CAR_SIZE, CAR_SIZE, CAR_SPEED});
}

void CarManager::update()
{
    for (auto &car : cars)
    {
        // TODO: Add or subtract dx based on the time passed.
    }
}
