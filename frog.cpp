#include "frog.h"
#include "draw_utils.h"

void drawFrog(const Frog& frog) {
    float cx = frog.x;
    float cy = frog.y;

    glPushMatrix();
    glTranslatef(cx, cy, 0.0f);

    // Body
    //glColor3f(bird.bodyR, bird.bodyG, bird.bodyB); translate into frogger image
    //circle(0, 0, r);

    glPopMatrix();
}
