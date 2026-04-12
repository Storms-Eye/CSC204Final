#include "draw_utils.h"
#include "frog-texture.h"
#include "frog.h"
#include "obstacle.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>

// Types
enum State
{
    MENU,
    PLAYING,
    DEAD
};

// Game state
static State gState = MENU;
static Frog gFrog;
static std::vector<Obstacle> gObstacles;
static int gScore = 0; // unecessary
static int gBest = 0;  // unecessary
static int gFrame = 0;
static int gLives = 3;

// Scene drawing
static void drawBackground()
{
    // Brady's background goes here
}

static void drawHUD()
{
    glColor3f(1.0f, 1.0f, 1.0f);
    text18(14, WIN_H - 26, "Lives: " + std::to_string(gScore /*change this*/));
}

static void drawOverlay(const char *title, const char *sub)
{
    // Semi-transparent dark box
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.0f, 0.0f, 0.0f, 0.45f);
    quad(WIN_W / 2.0f - 160.0f, WIN_H / 2.0f - 70.0f, 320.0f, 110.0f);
    glDisable(GL_BLEND);

    glColor3f(1.0f, 0.95f, 0.2f);
    text(WIN_W / 2.0f - 90.0f, WIN_H / 2.0f + 22.0f, title, GLUT_BITMAP_TIMES_ROMAN_24);

    glColor3f(1.0f, 1.0f, 1.0f);
    text18(WIN_W / 2.0f - 120.0f, WIN_H / 2.0f - 14.0f, sub);

    if (gState == DEAD)
    {
        text18(WIN_W / 2.0f - 80.0f, WIN_H / 2.0f - 44.0f, "Game Over");
    }
}

// Logic
static void resetGame()
{
    gFrog.reset();
    gObstacles.clear();
    gScore = 0;
    gFrame = 0;
    gLives = 3; // this variable needs to be initialized
    gState = PLAYING;
}
static void reviveFrog()
{
    gFrog.reset();
    gLives--;
}

static void update()
{
    if (gState != PLAYING)
        return;

    gFrog.update();

    if (gFrog.dead())
    {
        if (gLives > 0)
        {
            reviveFrog();
        }
        else
        {
            gState = DEAD;
            return;
        }
    }
    /*if (gFrog.hasWon())
    {

    }*/

    // this code is for a win check

    /*// Spawn pipes
    ++gFrame;
    if (gFrame % OBSTACLE_INTERVAL == 1)
        gPipes.emplace_back((float)WIN_W + 10.0f);

    // Update & check pipes
    for (auto& p : gPipes) {
        p.update();

        if (!p.scored && p.x + PIPE_W < gBird.x) {
            p.scored = true;
            ++gScore;
        }

        if (p.hits(gBird.x, gBird.y)) {
            if (gScore > gBest) gBest = gScore;
            gState = DEAD;
            return;
        }
    }

    gPipes.erase(
        std::remove_if(gPipes.begin(), gPipes.end(),
                       [](const Obstacle& p){ return p.offScreen(); }),
        gPipes.end());

*/
}
// above comment is for refernence when we make log and car obstacles.

//  GLUT callbacks
static void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    drawBackground();
    drawObstacles(gObstacles);
    gFrog.draw();
    drawHUD();

    if (gState == MENU)
        drawOverlay("Frogger", "SPACE or click to start");
    else if (gState == DEAD)
        drawOverlay("GAME OVER", "Press R to restart");

    glutSwapBuffers();
}

static void timerCB(int)
{
    update();
    glutPostRedisplay();
    glutTimerFunc(16, timerCB, 0); // ~60 FPS
}

static void keyDown(unsigned char k, int, int)
{
    switch (k)
    {
    case ' ':
        if (gState == MENU)
            resetGame();
        break;
    case 'r':
    case 'R':
        if (gState == DEAD)
            resetGame();
        break;
    case 27: // ESC
        exit(0);
    }
}
static void specialKeyDown(int k, int, int)
{
    switch (k)
    {
    case GLUT_KEY_UP:
        if (gState == PLAYING)
            gFrog.hopPosY();
        break;
    case GLUT_KEY_DOWN:
        if (gState == PLAYING)
            gFrog.hopNegY();
        break;
    case GLUT_KEY_RIGHT:
        if (gState == PLAYING)
            gFrog.hopPosX();
        break;
    case GLUT_KEY_LEFT:
        if (gState == PLAYING)
            gFrog.hopNegX();
        break;
    }
}

GLuint frogTextureID;
void initTextures()
{
    glGenTextures(1, &frogTextureID);
    glBindTexture(GL_TEXTURE_2D, frogTextureID);

    // Crisp pixel borders instead of blurring.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    GLenum format = (gimp_image.bytes_per_pixel == 4) ? GL_RGBA : GL_RGB;

    glTexImage2D(GL_TEXTURE_2D, 0, format, gimp_image.width, gimp_image.height, 0, format, GL_UNSIGNED_BYTE, gimp_image.pixel_data);
}

int main(int argc, char **argv)
{
    srand((unsigned)time(nullptr));

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WIN_W, WIN_H);
    glutCreateWindow("Frogger");

    initTextures();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WIN_W, 0, WIN_H);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyDown);
    glutSpecialFunc(specialKeyDown);
    glutTimerFunc(16, timerCB, 0);

    glutMainLoop();
    return 0;
}
