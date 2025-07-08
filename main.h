#ifndef MINIAUDIO_MAIN_H
#define MINIAUDIO_MAIN_H

#include "music/notes.h"

typedef struct {
    float phase;
    float frequency;
    WaveType waveType;
    float gain;
    float detune;
} Oscillator;

typedef struct {
    Oscillator* oscillators; // Pointer to an array of oscillators
    int numOscillators;      // Number of active oscillators
} OscillatorBank;
#endif //MINIAUDIO_MAIN_H
