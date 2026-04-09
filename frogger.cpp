// Controls: "Use arrow keys to hop directionally" | R to restart | ESC to quit

#include "constants.h"
#include "draw_utils.h"
#include "frog.h"
#include "obstacle.h"

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>

// ─── Types ────────────────────────────────────────────────────────────────────

enum State { MENU, PLAYING, DEAD };

// ─── Game state ───────────────────────────────────────────────────────────────

static State             gState = MENU;
static Frog              gFrog;
static std::vector<Obstacles> gObstacles;
static int               gScore = 0;
static int               gBest  = 0; //change this to # of lives
static int               gFrame = 0;

// ─── Scene drawing ────────────────────────────────────────────────────────────

static void drawBackground() {
    // Sky gradient (top → bottom)
    glBegin(GL_QUADS);
      glColor3f(0.27f, 0.60f, 0.95f);
      glVertex2f(0,     WIN_H);
      glVertex2f(WIN_W, WIN_H);
      glColor3f(0.55f, 0.80f, 1.00f);
      glVertex2f(WIN_W, GROUND_H);
      glVertex2f(0,     GROUND_H);
    glEnd();

    // Ground dirt
    glColor3f(0.55f, 0.37f, 0.12f);
    quad(0, 0, WIN_W, GROUND_H);

    // Grass strip
    glColor3f(0.30f, 0.72f, 0.20f);
    quad(0, GROUND_H - 8, WIN_W, 14);
}

static void drawHUD() {
    glColor3f(1.0f, 1.0f, 1.0f);
    text18(14, WIN_H - 26, "Score: " + std::to_string(gScore));
    text18(14, WIN_H - 50, "Best:  " + std::to_string(gBest));
}

static void drawOverlay(const char* title, const char* sub) {
    // Semi-transparent dark box
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.0f, 0.0f, 0.0f, 0.45f);
    quad(WIN_W / 2.0f - 160.0f, WIN_H / 2.0f - 70.0f, 320.0f, 110.0f);
    glDisable(GL_BLEND);

    glColor3f(1.0f, 0.95f, 0.2f);
    text(WIN_W / 2.0f - 90.0f, WIN_H / 2.0f + 22.0f, title,
         GLUT_BITMAP_TIMES_ROMAN_24);

    glColor3f(1.0f, 1.0f, 1.0f);
    text18(WIN_W / 2.0f - 120.0f, WIN_H / 2.0f - 14.0f, sub);

    if (gState == DEAD) {
        text18(WIN_W / 2.0f - 80.0f, WIN_H / 2.0f - 44.0f,
               "Score: " + std::to_string(gScore) +
               "   Best: " + std::to_string(gBest));
    }
}

// ─── Logic ────────────────────────────────────────────────────────────────────

static void resetGame() {
    gBird.reset();
    gPipes.clear();
    gScore = 0;
    gFrame = 0;
    gState = PLAYING;
}

static void update() {
    if (gState != PLAYING) return;

    gBird.update();

    if (gBird.dead()) {
        if (gScore > gBest) gBest = gScore;
        gState = DEAD;
        return;
    }

    // Spawn pipes
    ++gFrame;
    if (gFrame % PIPE_INTERVAL == 1)
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
                       [](const Pipe& p){ return p.offScreen(); }),
        gPipes.end());
}

// ─── GLUT callbacks ───────────────────────────────────────────────────────────

static void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawBackground();
    drawPipes(gPipes);
    drawBird(gBird);
    drawHUD();

    if (gState == MENU)
        drawOverlay("FLAPPY BIRD", "SPACE or click to start");
    else if (gState == DEAD)
        drawOverlay("GAME OVER", "Press R to restart");

    glutSwapBuffers();
}

static void timerCB(int) {
    update();
    glutPostRedisplay();
    glutTimerFunc(16, timerCB, 0);   // ~60 FPS
}

static void keyDown(unsigned char k, int, int) {
    switch (k) {
        case ' ':
            if (gState == MENU) resetGame();
            else if (gState == PLAYING) gBird.flap();
            break;
        case 'r': case 'R':
            if (gState == DEAD) resetGame();
            break;
        case 27:   // ESC
            exit(0);
    }
}

static void mouseClick(int btn, int st, int, int) {
    if (btn == GLUT_LEFT_BUTTON && st == GLUT_DOWN) {
        if (gState == MENU)         resetGame();
        else if (gState == PLAYING) gBird.flap();
    }
}

// ─── Main ─────────────────────────────────────────────────────────────────────

int main(int argc, char** argv) {
    srand((unsigned)time(nullptr));

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WIN_W, WIN_H);
    glutCreateWindow("Flappy Bird");

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WIN_W, 0, WIN_H);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyDown);
    glutMouseFunc(mouseClick);
    glutTimerFunc(16, timerCB, 0);

    glutMainLoop();
    return 0;
}
