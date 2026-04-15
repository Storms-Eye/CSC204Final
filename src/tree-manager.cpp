#include "../include/tree-manager.h"

extern GLuint treeTextureID;

void TreeManager::draw()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    for (auto &tree : trees)
    {
        float cx = tree.x;
        float cy = tree.y;
				
        glPushMatrix();
        glTranslatef(cx, cy, 0.0f);
        glColor3f(1.0f, 1.0f, 1.0f);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, treeTextureID); // Assuming this is accessible
        texturedQuad(0.0f, 0.0f, tree.width, tree.height);
        glDisable(GL_TEXTURE_2D);
        glPopMatrix();
    }
    glDisable(GL_BLEND);
}

void TreeManager::addTree(float x, float y)
{
    trees.push_back({x, y, TREE_SIZE, TREE_SIZE, 0});
}
std::vector<Obstacle> TreeManager::getTrees()
{
	return trees;
}

void TreeManager::update(){}//unnecessary
