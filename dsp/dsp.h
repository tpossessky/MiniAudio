#ifndef DSP_H
#define DSP_H

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
    WAVE_PULSE,
    WAVE_WHITE_NOISE,
    WAVE_PINK_NOISE,
    WAVE_BROWN_NOISE ,
} WaveType;


// Function Prototypes (Method Definitions)
Vec2 vec2_from_float(float v);
Vec2 vec2_add(Vec2 a, Vec2 b);
Vec2 vec2_mul(Vec2 a, float scalar);
Vec2 vec2_tanh(Vec2 a);
Vec2 vec2_softClip(Vec2 x);
Vec2 vec2_hardClip(Vec2 x, float minVal, float maxVal);
Vec2 vec2_bitCrush(Vec2 x, float bitDepth);
Vec2 panSweep(float mono, float time);
Vec2 generate_white_noise();
Vec2 generate_wave(WaveType waveType, float normalized_phase, float duty);

#endif // DSP_H