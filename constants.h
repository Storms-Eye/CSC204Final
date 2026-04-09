#pragma once

// ── Window & world ────────────────────────────────────────────────────────────
constexpr int   WIN_W         = 800;
constexpr int   WIN_H         = 600;
constexpr int   GROUND_H      =  55;   // pixels from bottom
constexpr int   PIPE_INTERVAL =  95;   // frames between pipe spawns
constexpr float BIRD_R        =  14.0f;
constexpr float PIPE_W        =  60.0f; //unnecessary

constexpr float FROG_SLOW_SPEED    =  -0.4f; //TODO

// Upward velocity applied when the player flaps.
// Must be POSITIVE (e.g. try values between 6.0 and 12.0).
constexpr float HOP_VEL   =  7.0f; //TODO

// How many pixels the pipes move left each frame.
// Try values between 2.0 and 5.0.
constexpr float PIPE_SPEED =  4.0f;   // remove this

