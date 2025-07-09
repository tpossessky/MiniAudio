//
// Created by Tristan on 7/8/2025.
//

#ifndef SYNTH_H
#define SYNTH_H
#include <stdbool.h>
#include "../libs/miniaudio.h"
#include "../dsp/dsp.h"


typedef struct {
    float phase;
    float frequency;
    WaveType waveType;
    float gain;
    float detune;
} Oscillator;

/*
 * Voice represents the polyphonic aspects of 1 voice. The number of oscillators within the bank determines the
 * richness of the sound.
 */
typedef struct {
    Oscillator* oscillators;    // Pointer to an array of oscillators
    ma_uint8 numOscillators;    // Number of active oscillators, determined by oscillatorsPerVoice
    bool isActive;
} Voice;


typedef struct {
    Voice* voices;              // Pointer to an array of Voice structs
    ma_uint8 numVoices;         // number of "keys" able to be pressed at once
    ma_uint8 oscillatorsPerVoice; // Authoritative num of oscillators each voice uses
    float masterVolume;
    float masterFilterCutoff;
    // LFO globalLFO; //someday
} SynthState;


SynthState* sy_init_synth(ma_uint8 numVoices);
#endif //SYNTH_H
