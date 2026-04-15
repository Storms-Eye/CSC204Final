#include "../include/car-manager.h"

extern GLuint carTextureID;
extern int gFrame;

void CarManager::draw()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    for (auto &car : cars)
    {
        float cx = car.x;
        float cy = car.y;

        glPushMatrix();
        glTranslatef(cx, cy, 0.0f);
        
        if (car.speed < 0)
        {
            glTranslatef(car.width, 0.0f, 0.0f); 
            glScalef(-1.0f, 1.0f, 1.0f);  
        }
        
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, carTextureID);
        texturedQuad(0.0f, 0.0f, car.width, car.height);
        glDisable(GL_TEXTURE_2D);
        glPopMatrix();
    }
    
    glDisable(GL_BLEND);
}

void CarManager::addCar(float x, float y, float speed)
{
    cars.push_back({x, y, CAR_SIZE, CAR_SIZE, speed});
}

void CarManager::update()
{
    // moves car by interval from .h file
    if (gFrame % MOVE_INTERVAL == 0)
    {
        for (size_t i = 0; i < cars.size(); ++i)
        {
            if (cars[i].speed > 0)
            {
                cars[i].x += FROG_SIZE;
            }
            else if (cars[i].speed < 0)
            {
                cars[i].x -= FROG_SIZE;
            }
            
            if (cars[i].x > WIN_W)
            {
                cars[i].x = -CAR_SIZE;
            }
            else if (cars[i].x < -CAR_SIZE)
            {
                cars[i].x = WIN_W;
            }
        }
    }
}
