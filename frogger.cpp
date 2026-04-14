#include "draw_utils.h"

#include "textures/background.h"
#include "textures/car.h"
#include "textures/frog.h"
#include "textures/log.h"
#include "textures/tree.h"

#include "background.h"
#include "frog.h"
#include "log.h"
#include "tree.h"

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

static std::vector<int> gTreexs = {0, static_cast<int>(FROG_SIZE), static_cast<int>(FROG_SIZE * 2), static_cast<int>(FROG_SIZE * 3), static_cast<int>(FROG_SIZE * 4), static_cast<int>(FROG_SIZE * 5), static_cast<int>(FROG_SIZE * 6), static_cast<int>(FROG_SIZE * 7)};
static std::vector<int> gTreeys = {0, 0, 0, 0, 0, 0, 0, 0};
static std::vector<int> gCarxs;
static std::vector<int> gCarys;
static int gFrame = 0;
static int gLives = 3;

static LogManager logs;
static Frog frog;

static void drawObstacles(std::vector<int> obxs, std::vector<int> obys, auto drawFunc)
{
    for (int i = 0; i < obxs.size(); i++)
    {
        for (int j = 0; j < obys.size(); j++)
        {
            drawFunc(i, j);
        }
    }
}

static void drawHUD()
{
    glColor3f(1.0f, 1.0f, 1.0f);
    text18(14, WIN_H - 26, "Lives: " + std::to_string(gLives));
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
    frog.reset();
    gFrame = 0;
    gLives = 3; // this variable needs to be initialized
    gState = PLAYING;
}
static void reviveFrog()
{
    frog.reset();
    gLives--;
}

static void update()
{
    if (gState != PLAYING)
        return;

    if (frog.dead())
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
    /*if (frog.hasWon())
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
    frog.draw();
    logs.draw();

    drawHUD();

    if (gState == MENU)
        drawOverlay("Frogger", "press SPACE to start");
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
            frog.hopPosY();
        break;
    case GLUT_KEY_DOWN:
        if (gState == PLAYING)
            frog.hopNegY();
        break;
    case GLUT_KEY_RIGHT:
        if (gState == PLAYING)
            frog.hopPosX();
        break;
    case GLUT_KEY_LEFT:
        if (gState == PLAYING)
            frog.hopNegX();
        break;
    }
}

GLuint frogTextureID;
GLuint backgroundTextureID;
GLuint treeTextureID;
GLuint logTextureID;
GLuint carTextureID;

void initTextures()
{
    // Crisp pixel borders instead of blurring.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    GLenum frogFormat = (frog_texture.bytes_per_pixel == 4) ? GL_RGBA : GL_RGB;
    glGenTextures(1, &frogTextureID);
    glBindTexture(GL_TEXTURE_2D, frogTextureID);
    glTexImage2D(GL_TEXTURE_2D, 0, frogFormat, frog_texture.width, frog_texture.height, 0, frogFormat, GL_UNSIGNED_BYTE, frog_texture.pixel_data);

    GLenum backgroundFormat = (background_texture.bytes_per_pixel == 4) ? GL_RGBA : GL_RGB;
    glGenTextures(1, &backgroundTextureID);
    glBindTexture(GL_TEXTURE_2D, backgroundTextureID);
    glTexImage2D(GL_TEXTURE_2D, 0, backgroundFormat, background_texture.width, background_texture.height, 0, backgroundFormat, GL_UNSIGNED_BYTE, background_texture.pixel_data);

    GLenum treeFormat = (tree_texture.bytes_per_pixel == 4) ? GL_RGBA : GL_RGB;
    glGenTextures(1, &treeTextureID);
    glBindTexture(GL_TEXTURE_2D, treeTextureID);
    glBindTexture(GL_TEXTURE_2D, treeTextureID);
    glTexImage2D(GL_TEXTURE_2D, 0, treeFormat, tree_texture.width, tree_texture.height, 0, treeFormat, GL_UNSIGNED_BYTE, tree_texture.pixel_data);

    GLenum logFormat = (log_texture.bytes_per_pixel == 4) ? GL_RGBA : GL_RGB;
    glGenTextures(1, &logTextureID);
    glBindTexture(GL_TEXTURE_2D, logTextureID);
    glTexImage2D(GL_TEXTURE_2D, 0, logFormat, log_texture.width, log_texture.height, 0, logFormat, GL_UNSIGNED_BYTE, log_texture.pixel_data);

    GLenum carFormat = (car_texture.bytes_per_pixel == 4) ? GL_RGBA : GL_RGB;
    glGenTextures(1, &carTextureID);
    glBindTexture(GL_TEXTURE_2D, carTextureID);
    glTexImage2D(GL_TEXTURE_2D, 0, carFormat, car_texture.width, car_texture.height, 0, carFormat, GL_UNSIGNED_BYTE, car_texture.pixel_data);
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

    glutReshapeFunc([](int w, int h)
    {
        glutReshapeWindow(WIN_W, WIN_H);
    });

    glutDisplayFunc(display);
    glutKeyboardFunc(keyDown);
    glutSpecialFunc(specialKeyDown);
    glutTimerFunc(16, timerCB, 0);

    glutMainLoop();
    return 0;
}
