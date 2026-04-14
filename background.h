#pragma once

#include "textures/background.h"
#include "draw_utils.h"

extern GLuint backgroundTextureID;

static void drawBackground()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, backgroundTextureID);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 1);
    glVertex2f(0, 0);
    glTexCoord2f(1, 1);
    glVertex2f(WIN_W, 0);
    glTexCoord2f(1, 0);
    glVertex2f(WIN_W, WIN_H);
    glTexCoord2f(0, 0);
    glVertex2f(0, WIN_H);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}