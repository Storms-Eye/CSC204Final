#pragma once

#include "constants.h"
#include <cstdlib>

struct Frog {
    float x  = 180.0f;
    float y  = WIN_H / 2.0f;
    float vy = 0.0f;
		float vx = 0.0f;

    void reset() {
        x = 180.0f; y = WIN_H / 2.0f; vy = 0.0f; //swap to 72 and 8 (respective to screen size)
    }

    void hopNegX() { if(vx == 0) vx = -HOP_VEL; }
    void hopNegY() { if(vy == 0) vy = -HOP_VEL; }
    void hopPosX() { if(vx == 0) vx = HOP_VEL; }
    void hopPosY() { if(vy == 0) vy = HOP_VEL; }

    void update() {
        if(vy > 0) vy -= FROG_SLOW_SPEED;
				if(vx > 0) vx -= FROG_SLOW_SPEED;
				if(vy < 0) vy += FROG_SLOW_SPEED;
				if(vx < 0) vx += FROG_SLOW_SPEED;
				if(vx > 0.1f || vx < -0.1f) x += vx;
				if(vy > 0.1f || vy < -0.1f) y += vy;
    }

    //Make Death Conditions
		bool dead() const {
				return false;
    }
private:
    static void hsvToRgb(float h, float s, float v,
                         float& r, float& g, float& b) {
        int   i = (int)(h / 60.0f) % 6;
        float f = h / 60.0f - (int)(h / 60.0f);
        float p = v * (1.0f - s);
        float q = v * (1.0f - f * s);
        float t = v * (1.0f - (1.0f - f) * s);
        switch (i) {
            case 0: r=v; g=t; b=p; break;
            case 1: r=q; g=v; b=p; break;
            case 2: r=p; g=v; b=t; break;
            case 3: r=p; g=q; b=v; break;
            case 4: r=t; g=p; b=v; break;
            default: r=v; g=p; b=q; break;
        }
    }

};

void drawFrog(const Frog& frog);
