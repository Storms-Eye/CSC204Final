#pragma once

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <cmath>
#include <string>

// Drawing functions
inline void quad(float x, float y, float w, float h)
{
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + w, y);
    glVertex2f(x + w, y + h);
    glVertex2f(x, y + h);
    glEnd();
}

inline void texturedQuad(float x, float y, float w, float h)
{
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); 
    glVertex2f(x, y);
    glTexCoord2f(1.0f, 1.0f); 
    glVertex2f(x + w, y);
    glTexCoord2f(1.0f, 0.0f); 
    glVertex2f(x + w, y + h);
    glTexCoord2f(0.0f, 0.0f); 
    glVertex2f(x, y + h);
    glEnd();
}

inline void circle(float cx, float cy, float r, int segs = 24)
{
    glBegin(GL_POLYGON);
    for (int i = 0; i < segs; ++i)
    {
        float a = 2.0f * (float)M_PI * i / segs;
        glVertex2f(cx + r * cosf(a), cy + r * sinf(a));
    }
    glEnd();
}

inline void text(float x, float y, const std::string &s, void *font = GLUT_BITMAP_HELVETICA_18)
{
    glRasterPos2f(x, y);
    for (char c : s)
        glutBitmapCharacter(font, c);
}

inline void text18(float x, float y, const std::string &s)
{
    text(x, y, s, GLUT_BITMAP_HELVETICA_18);
}

inline void hsvToRgb(float h, float s, float v, float &r, float &g, float &b)
{
    int i = (int)(h / 60.0f) % 6;
    float f = h / 60.0f - (int)(h / 60.0f);
    float p = v * (1.0f - s);
    float q = v * (1.0f - f * s);
    float t = v * (1.0f - (1.0f - f) * s);
    switch (i)
    {
    case 0:
        r = v;
        g = t;
        b = p;
        break;
    case 1:
        r = q;
        g = v;
        b = p;
        break;
    case 2:
        r = p;
        g = v;
        b = t;
        break;
    case 3:
        r = p;
        g = q;
        b = v;
        break;
    case 4:
        r = t;
        g = p;
        b = v;
        break;
    default:
        r = v;
        g = p;
        b = q;
        break;
    }
}

// Constants.
constexpr int WIN_W = 720;
constexpr int WIN_H = 720;
constexpr int OBSTACLE_INTERVAL = 500; // distance between obstacles.
constexpr float FROG_SIZE = 80.0f;

constexpr float CAR_SPEED = 4.0f; 
constexpr float LOG_SPEED = 3.0f; 
