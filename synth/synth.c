//
// Created by Tristan on 7/8/2025.
//
#include "synth.h"

#include <stdio.h>
#include <stdlib.h>

#define OSCILLATORS_PER_VOICE 3


Oscillator sy_init_oscillator() {
    return (Oscillator) {
        .phase = 0.0f,
        .frequency = 0.0f,
        .waveType = WAVE_SINE,
        .gain = 1.0f,
        .detune = 0.0f
    };
}


bool sy_init_voice(Voice* voice, ma_uint8 numOscillators) {
    if (voice == NULL) {
        fprintf(stderr, "Error: init_voice received a NULL voice pointer.\n");
        return false;
    }

    voice->numOscillators = numOscillators;
    voice->isActive = false;
    voice->oscillators = (Oscillator*) malloc(sizeof(Oscillator) * numOscillators);

    if (voice->oscillators == NULL) {
        fprintf(stderr, "Error: Failed to initialize voice. Cleaning up.\n");
        free(voice->oscillators);
        return false;
    }

    for (int i = 0; i < numOscillators; i++) {
        voice->oscillators[i] = sy_init_oscillator();
    }

    return true;
}


SynthState* sy_init_synth(ma_uint8 numVoices) {
    SynthState* synthState = malloc(sizeof(SynthState));

    if (synthState == NULL) {
        printf("Error allocating memory for global SynthState.");
        return NULL;
    }

    synthState->numVoices = numVoices;
    synthState->oscillatorsPerVoice = OSCILLATORS_PER_VOICE;
    synthState->masterVolume = 1.0f;
    synthState->masterFilterCutoff = 1.0f;
    synthState->voices = (Voice*) malloc(sizeof(Voice) * synthState->numVoices);

    if (synthState->voices == NULL) {
        free(synthState);
        return NULL;
    }

    for (int i = 0; i < numVoices; i++) {
        if (!sy_init_voice(synthState->voices, synthState->oscillatorsPerVoice)) {
            fprintf(stderr, "Error: Failed to initialize voice #%d. Cleaning up.\n", i);
            for (int j = 0; j < i; j++) {
                free(synthState->voices[j].oscillators);
                free(synthState->voices); // Free the array of Voice structs
                free(synthState);         // Free the SynthState struct
                return NULL;
            }
        }
    }

    return synthState;
}
