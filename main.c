#define MINIAUDIO_IMPLEMENTATION
#define MA_NO_DECODING
#define MA_NO_ENCODING
#define DEVICE_FORMAT       ma_format_f32
#define DEVICE_CHANNELS     2
#define DEVICE_SAMPLE_RATE  44100
#define VOLUME_MODIFIER 0.5f

#include <stdio.h>
#include "./libs/miniaudio.h"
#include "music/notes.c"
#include "dsp/dsp.h"
#include "main.h"


//this is called every time the audio buffer wants data and specifies how much with frameCount
void data_callback(const ma_device* device, void* output, const void* input, ma_uint32 frameCount) {
    float* out = (float*)output; // Explicit cast for clarity
    OscillatorBank* oscillatorBank = (OscillatorBank*)device->pUserData; // Explicit cast for clarity

    // Basic error checking
    if (oscillatorBank == NULL || oscillatorBank->oscillators == NULL || oscillatorBank->numOscillators == 0) {
        // Output silence if no valid data
        for (ma_uint32 i = 0; i < frameCount * DEVICE_CHANNELS; ++i) {
            out[i] = 0.0f;
        }
        (void)input;
        return;
    }

    // You no longer need the unused `freq` and `phase_incrementONE` variables here.
    for (ma_uint32 i = 0; i < frameCount; i++) {
        Vec2 combined_wave_for_this_frame = {0.0f, 0.0f}; // Initialize for summing for the current sample frame

        // Loop through all oscillators to sum their outputs
        for (int osc_idx = 0; osc_idx < oscillatorBank->numOscillators; osc_idx++) {
            Oscillator* current_osc = &oscillatorBank->oscillators[osc_idx];

            // Calculate phase increment for THIS oscillator
            float phase_increment = current_osc->frequency / (float)device->sampleRate;

            // Generate wave for this oscillator at its current phase
            Vec2 osc_output = generateWave(current_osc->waveType, current_osc->phase, current_osc->detune);
            osc_output = vec2_mul(osc_output, current_osc->gain); // Apply individual oscillator gain

            // Add this oscillator's output to the combined sum
            combined_wave_for_this_frame = vec2_add(combined_wave_for_this_frame, osc_output);

            // *** IMPORTANT: Update and wrap the phase for THIS oscillator ***
            current_osc->phase += phase_increment;
            if (current_osc->phase >= 1.0f) {
                current_osc->phase -= 1.0f;
            }
        }

        // Apply master gain based on the number of oscillators to prevent clipping
        // and then apply the overall VOLUME_MODIFIER.
        if (oscillatorBank->numOscillators > 0) {
            // This normalizes the sum if all individual gains were 1.0f.
            // Since you set individual gains to `1.0f / numOscillators`, this effectively doubles it back.
            // You might want to remove the `1.0f / (float)oscillatorBank->numOscillators` here
            // if your individual gains already manage clipping, or adjust it carefully.
            // Let's remove it for now, as your `main` already sets appropriate individual gains.
            // combined_wave_for_this_frame = vec2_mul(combined_wave_for_this_frame, 1.0f / (float)oscillatorBank->numOscillators);
        }
        // Apply your master volume modifier last
        combined_wave_for_this_frame = vec2_mul(combined_wave_for_this_frame, VOLUME_MODIFIER);

        // Output to sound device (stereo)
        out[i * 2]     = combined_wave_for_this_frame.x;
        out[i * 2 + 1] = combined_wave_for_this_frame.y;
    }

    (void)input; // Cast to void to suppress unused parameter warning
}

int main() {
    ma_device_config config = ma_device_config_init(ma_device_type_playback);
    config.playback.format = ma_format_f32;
    config.playback.channels = DEVICE_CHANNELS;
    config.sampleRate = DEVICE_SAMPLE_RATE;
    config.dataCallback = (ma_device_data_proc) data_callback;


    OscillatorBank oscillatorBanks = { NULL, 0 }; // Initialize its members.

    oscillatorBanks.numOscillators = 6;
    oscillatorBanks.oscillators = (Oscillator*) malloc(sizeof(Oscillator) * oscillatorBanks.numOscillators);


    //assumes all waves should be equal
    float gain = 1.0f/(float) oscillatorBanks.numOscillators;

    oscillatorBanks.oscillators[0] = (Oscillator){
            .phase = 0.0f,
            .frequency = getNoteFrequency(SEMITONE_A,4),
            .waveType = WAVE_SINE,
            .gain = gain,
            .detune = 0.0f
    };
    oscillatorBanks.oscillators[1] = (Oscillator){
            .phase = 0.0f,
            .frequency = getNoteFrequency(SEMITONE_CS,4),
            .waveType = WAVE_SINE,
            .gain = gain,
            .detune = 0.0f
    };
    oscillatorBanks.oscillators[2] = (Oscillator){
            .phase = 0.0f,
            .frequency = getNoteFrequency(SEMITONE_E,4),
            .waveType = WAVE_SINE,
            .gain = gain,
            .detune = 0.0f
    };
    oscillatorBanks.oscillators[3] = (Oscillator){
            .phase = 0.0f,
            .frequency = getNoteFrequency(SEMITONE_E,3),
            .waveType = WAVE_SINE,
            .gain = gain,
            .detune = 0.0f
    };
    oscillatorBanks.oscillators[4] = (Oscillator){
            .phase = 0.0f,
            .frequency = getNoteFrequency(SEMITONE_CS,3),
            .waveType = WAVE_SINE,
            .gain = gain,
            .detune = 0.0f
    };
    oscillatorBanks.oscillators[5] = (Oscillator){
            .phase = 0.0f,
            .frequency = getNoteFrequency(SEMITONE_A,2),
            .waveType = WAVE_SINE,
            .gain = gain,
            .detune = 0.0f
    };




    config.pUserData = &oscillatorBanks;

    ma_device device;

    if (ma_device_init(NULL, &config, &device) != MA_SUCCESS) {
        printf("failed to init device\n");
        free(oscillatorBanks.oscillators); // IMPORTANT: Free the dynamically allocated memory
        return -1;
    }

    if (ma_device_start(&device) != MA_SUCCESS) {
        printf("failed to start device\n");
        free(oscillatorBanks.oscillators); // IMPORTANT: Free the dynamically allocated memory
        return -2;
    }

    printf("playing... press enter to stop\n");
    getchar();
    ma_device_uninit(&device);
    free(oscillatorBanks.oscillators); // IMPORTANT: Free the dynamically allocated memory
    return 0;
}