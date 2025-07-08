//
// Created by Tristan on 7/8/2025.
//
#include "dsp.h"

#include <math.h>
#include <stdlib.h>

Vec2 vec2_from_float(float v) {
    return (Vec2){ v, v };
}

Vec2 vec2_add(Vec2 a, Vec2 b) {
    return (Vec2){ a.x + b.x, a.y + b.y };
}

Vec2 vec2_mul(Vec2 a, float scalar) {
    return (Vec2){ a.x * scalar, a.y * scalar };
}

Vec2 vec2_tanh(Vec2 a) {
    return (Vec2){ tanhf(a.x), tanhf(a.y) };
}

Vec2 vec2_softClip(Vec2 x) {
    return (Vec2){ x.x / (1.0f + fabsf(x.x)),
                   x.y / (1.0f + fabsf(x.y)) };
}

Vec2 vec2_hardClip(Vec2 x, float minVal, float maxVal) {
    return (Vec2){ fminf(fmaxf(x.x, minVal), maxVal),
                   fminf(fmaxf(x.y, minVal), maxVal) };
}

Vec2 vec2_bitCrush(Vec2 x, float bitDepth) {
    return (Vec2){ floorf(x.x * bitDepth) / bitDepth,
                   floorf(x.y * bitDepth) / bitDepth };
}

Vec2 panSweep(float mono, float time) {
    float pan = sinf(TWO_PI * 0.1f * time); // -1 to 1
    float angle = (pan * 0.5f + 0.5f) * 0.5f * (float)M_PI;
    float leftGain = cosf(angle);
    float rightGain = sinf(angle);
    return (Vec2){ mono * leftGain, mono * rightGain };
}

Vec2 generate_white_noise() {
    float val = ((float)rand() / (float)RAND_MAX) * 2.0f - 1.0f;
    return vec2_from_float(val);
}

Vec2 generate_wave(WaveType waveType, float normalized_phase, float duty) {
    float val = 0.0f;
    float phase_rad = normalized_phase * TWO_PI; // Convert normalized phase to radians if needed by sinf, etc.

    switch (waveType) {
        case WAVE_SINE:
            val = sinf(phase_rad); // Use phase_rad directly
            break;
        case WAVE_SQUARE:
            val = (normalized_phase < 0.5f) ? 1.0f : -1.0f;
            break;
        case WAVE_PULSE:
            val = (normalized_phase < duty) ? 1.0f : -1.0f;
            break;
        case WAVE_SAW:
            val = 2.0f * normalized_phase - 1.0f;
            break;
        case WAVE_TRIANGLE:
            val = 4.0f * fabsf(normalized_phase - 0.5f) - 1.0f;
            break;
        case WAVE_WHITE_NOISE:
            return generate_white_noise();
        default:
            val = sinf(phase_rad);
            break;
    }
    return vec2_from_float(val);
}