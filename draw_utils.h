#pragma once

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

#include <cmath>
#include <string>

inline void quad(float x, float y, float w, float h) {
    glBegin(GL_QUADS);
      glVertex2f(x,     y    );
      glVertex2f(x + w, y    );
      glVertex2f(x + w, y + h);
      glVertex2f(x,     y + h);
    glEnd();
}

inline void circle(float cx, float cy, float r, int segs = 24) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < segs; ++i) {
        float a = 2.0f * (float)M_PI * i / segs;
        glVertex2f(cx + r * cosf(a), cy + r * sinf(a));
    }
    glEnd();
}

inline void text(float x, float y, const std::string& s,
                 void* font = GLUT_BITMAP_HELVETICA_18) {
    glRasterPos2f(x, y);
    for (char c : s) glutBitmapCharacter(font, c);
}

inline void text18(float x, float y, const std::string& s) {
    text(x, y, s, GLUT_BITMAP_HELVETICA_18);
}
