#include "pipe.h"
#include "draw_utils.h"
#include <cstdlib>

Pipe::Pipe(float startX) : x(startX) {
    // Keep gap reachable: clear of ground and ceiling
    const float minCY = GROUND_H + PIPE_GAP / 2.0f + 40.0f;
    const float maxCY = WIN_H    - PIPE_GAP / 2.0f - 40.0f;
    gapCY = minCY + (float)(rand() % (int)(maxCY - minCY));
}


void drawPipes(const std::vector<Pipe>& pipes) {
    for (const auto& p : pipes) {
        float halfG  = PIPE_GAP / 2.0f;
        float botTop = p.gapCY - halfG;   // top of bottom pillar
        float topBot = p.gapCY + halfG;   // bottom of top pillar

        // ── Bottom pillar ───────────────────────────────────────────────────
        glColor3f(0.18f, 0.75f, 0.18f);
        quad(p.x, GROUND_H, PIPE_W, botTop - GROUND_H);

        // cap
        glColor3f(0.10f, 0.55f, 0.10f);
        quad(p.x - 5.0f, botTop - 22.0f, PIPE_W + 10.0f, 22.0f);

        // ── Top pillar ──────────────────────────────────────────────────────
        glColor3f(0.18f, 0.75f, 0.18f);
        quad(p.x, topBot, PIPE_W, WIN_H - topBot);

        // cap
        glColor3f(0.10f, 0.55f, 0.10f);
        quad(p.x - 5.0f, topBot, PIPE_W + 10.0f, 22.0f);
    }
}
