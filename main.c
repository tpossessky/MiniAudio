#define MINIAUDIO_IMPLEMENTATION
#define MA_NO_DECODING
#define MA_NO_ENCODING
#define DEVICE_FORMAT       ma_format_f32
#define DEVICE_CHANNELS     2
#define DEVICE_SAMPLE_RATE  44100
#define VOLUME_MODIFIER     0.5f

#include <stdbool.h>
#include <stdio.h>
#include "./libs/miniaudio.h"
#include "music/notes.h"
#include "dsp/dsp.h"
#include "synth/synth.h"
#include "main.h"
#include "synth/synth.h"


//this is called every time the audio buffer wants data and specifies how much with frameCount
void data_callback(const ma_device* device, void* output, const void* input, ma_uint32 frameCount) {

    float* out = output;

    SynthState* synthState = device->pUserData;
    Voice* synthVoices = synthState->voices;

    for (ma_uint32 frame_idx = 0; frame_idx < frameCount; frame_idx++) {
        Vec2 finalOutputPerFrame = {0.0f, 0.0f}; // Initialize for summing for the current sample frame

        for(ma_uint8 voice_idx = 0; voice_idx < synthState->numVoices; voice_idx++) {

            Voice* curVoice = &synthVoices[voice_idx];
            if (!curVoice->isActive) continue;

            for (ma_uint8 osc_idx = 0; osc_idx < curVoice->numOscillators; osc_idx++) {

                Oscillator* curOsc = &curVoice->oscillators[osc_idx];
                float phaseIncrement = curOsc->frequency / (float)device->sampleRate;

                Vec2 curOscOutput = generate_wave(curOsc->waveType, curOsc->phase, curOsc->detune);
                curOscOutput = vec2_mul(curOscOutput, curOsc->gain); // Apply individual oscillator gain

                // Add this oscillator's output to the combined sum
                finalOutputPerFrame = vec2_add(finalOutputPerFrame, curOscOutput);

                curOsc->phase += phaseIncrement;
                if (curOsc->phase >= 1.0f) {
                    curOsc->phase -= 1.0f;
                }
            }
        }
        finalOutputPerFrame = vec2_mul(finalOutputPerFrame, VOLUME_MODIFIER);

        // Output to sound device (stereo)
        out[frame_idx * 2]     = finalOutputPerFrame.x;
        out[frame_idx * 2 + 1] = finalOutputPerFrame.y;
    }

    (void)input;
}

void setConfig(ma_device_config* config, SynthState* synth_state){
    config->playback.format = ma_format_f32;
    config->playback.format = ma_format_f32; //one sample is a 32-bit float
    config->playback.channels = DEVICE_CHANNELS;
    config->sampleRate = DEVICE_SAMPLE_RATE;
    config->dataCallback = (ma_device_data_proc) data_callback;
    config->pUserData = synth_state;
    config->noClip = true;
}


int main() {
    SynthState* synth_state = sy_init_synth(25);
    ma_device_config config = ma_device_config_init(ma_device_type_playback);
    ma_device device;

    if (synth_state == NULL) {
        printf("Error initializing synth from main.\n");
        return -1;
    }

    //config mini audio
    setConfig(&config, synth_state);
    

    if (ma_device_init(NULL, &config, &device) != MA_SUCCESS) {
        printf("failed to init device\n");
        return -2;
    }

    if (ma_device_start(&device) != MA_SUCCESS) {
        printf("failed to start device\n");
        return -3;
    }

    printf("playing... press enter to stop\n");
    
    getchar();
    ma_device_uninit(&device);
    free(synth_state);
    return 0;
}