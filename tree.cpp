#include "tree.h"
#include "draw_utils.h"
#include "tree-texture.h"
#include "frog.h"

extern GLuint treeID;

void Tree::draw(float tree_x, float tree_y)
{
    float cx = tree_x;
    float cy = tree_y;

    glPushMatrix();
    glTranslatef(cx, cy, 0.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, treeID); // Assuming this is accessible
    texturedQuad(0.0f, 0.0f, FROG_SIZE, FROG_SIZE);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}
