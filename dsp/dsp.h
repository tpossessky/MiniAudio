#ifndef DSP_H
#define DSP_H
#include <math.h>

#define PI 3.14159265359f
#define TWO_PI 6.28318530718f

// Stereo vector
typedef struct {
    float x;
    float y;
} Vec2;

typedef enum {
    WAVE_SINE,
    WAVE_SQUARE,
    WAVE_SAW,
    WAVE_TRIANGLE,
    WAVE_NOISE,
    WAVE_PULSE
} WaveType;



static Vec2 vec2_from_float(float v) {
    return (Vec2){ v, v };
}

static Vec2 vec2_add(Vec2 a, Vec2 b) {
    return (Vec2){ a.x + b.x, a.y + b.y };
}

static Vec2 vec2_mul(Vec2 a, float scalar) {
    return (Vec2){ a.x * scalar, a.y * scalar };
}

static Vec2 vec2_tanh(Vec2 a) {
    return (Vec2){ tanhf(a.x), tanhf(a.y) };
}

static Vec2 vec2_softClip(Vec2 x) {
    return (Vec2){ x.x / (1.0f + fabsf(x.x)),
                   x.y / (1.0f + fabsf(x.y)) };
}

static Vec2 vec2_hardClip(Vec2 x, float minVal, float maxVal) {
    return (Vec2){ fminf(fmaxf(x.x, minVal), maxVal),
                   fminf(fmaxf(x.y, minVal), maxVal) };
}

static Vec2 vec2_bitCrush(Vec2 x, float bitDepth) {
    return (Vec2){ floorf(x.x * bitDepth) / bitDepth,
                   floorf(x.y * bitDepth) / bitDepth };
}

static Vec2 panSweep(float mono, float time) {
    float pan = sinf(TWO_PI * 0.1f * time); // -1 to 1
    float angle = (pan * 0.5f + 0.5f) * 0.5f * (float)M_PI;
    float leftGain = cosf(angle);
    float rightGain = sinf(angle);
    return (Vec2){ mono * leftGain, mono * rightGain };
}

inline Vec2 generateWhiteNoise() {
    float val = ((float)rand() / (float)RAND_MAX) * 2.0f - 1.0f;
    return vec2_from_float(val);
}

/**
 *
 * @param waveType enum defining wavetype
 * @param freq frequency of the wave
 * @param t current time
 * @param duty (or duty cycle) is the fraction of one period of a waveform during which the signal is high (on) versus low (off).
 * @return stereo wave
 */
// In dsp.h
Vec2 generateWave(WaveType waveType, float normalized_phase, float duty) { // Removed freq, t
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
        case WAVE_NOISE:
            val = (float)rand() / (float)RAND_MAX * 2.0f - 1.0f;
            break;
        default:
            val = sinf(phase_rad);
            break;
    }
    return vec2_from_float(val);
}


#endif //DSP_H
