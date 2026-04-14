#include "tree-manager.h"

extern GLuint treeTextureID;

void TreeManager::draw()
{
    for (auto &tree : trees)
    {
        float cx = tree.x;
        float cy = tree.y;

        glPushMatrix();
        glTranslatef(cx, cy, 0.0f);
        glColor3f(1.0f, 1.0f, 1.0f);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, treeTextureID); // Assuming this is accessible
        texturedQuad(0.0f, 0.0f, FROG_SIZE, FROG_SIZE);
        glDisable(GL_TEXTURE_2D);
        glPopMatrix();
    }
}