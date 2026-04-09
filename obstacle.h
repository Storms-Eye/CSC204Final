#pragma once

#include "constants.h"
#include <vector>

struct Pipe {
    float x;
    float gapCY;   // Y-coordinate of the centre of the gap
    bool  scored = false;

    explicit Pipe(float startX);

    void update()          { x -= PIPE_SPEED; }
    bool offScreen() const { return x + PIPE_W < 0.0f; }

    // ── TODO (Part 5): Return true if the bird collides with this pipe ────
    //
    //  The bird is a circle with centre (bx, by) and radius BIRD_R.
    //  Each pipe has two rectangular pillars separated by a gap:
    //
    //    botTop = gapCY - PIPE_GAP / 2   ← top edge of the bottom pillar
    //    topBot = gapCY + PIPE_GAP / 2   ← bottom edge of the top pillar
    //
    //  Step 1 — Is the bird even in the X range of this pipe?
    //    If the bird's right edge (bx + BIRD_R) is left of the pipe's left
    //    edge (x), OR the bird's left edge (bx - BIRD_R) is right of the
    //    pipe's right edge (x + PIPE_W), there is no collision → return false.
    //
    //  Step 2 — Does the bird overlap either pillar?
    //    Bottom pillar: bird's bottom edge (by - BIRD_R) < botTop
    //    Top pillar:    bird's top edge    (by + BIRD_R) > topBot
    //    Return true if either condition holds.
    //
    bool hits(float bx, float by) const {
       	if(bx + BIRD_R < x || bx - BIRD_R > x + PIPE_W) return false;
				if(by - BIRD_R < gapCY - PIPE_GAP / 2 || by + BIRD_R > gapCY + PIPE_GAP / 2) return true;
				return false; 
    }
};

void drawPipes(const std::vector<Pipe>& pipes);
