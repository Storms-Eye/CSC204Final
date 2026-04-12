#include "frog.h"
#include "draw_utils.h"
#include "frog-texture.h"

extern GLuint frogTextureID;

void Frog::draw()
{
    float cx = x;
    float cy = y;

    glPushMatrix();
    glTranslatef(cx, cy, 0.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, frogTextureID); // Assuming this is accessible
    texturedQuad(0.0f, 0.0f, FROG_SIZE, FROG_SIZE);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

void Frog::update()
{
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

void Frog::reset()
{
    x = WIN_W / 2.0f;
    y = WIN_H / 2.0f;
}

// TODO: add the conditions for death from obstacle.
bool Frog::dead()
{
    return false;
}