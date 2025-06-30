#define MINIAUDIO_IMPLEMENTATION
#define MA_NO_DECODING
#define MA_NO_ENCODING
#define DEVICE_FORMAT       ma_format_f32
#define DEVICE_CHANNELS     2
#define DEVICE_SAMPLE_RATE  44100

#define VOLUME_MODIFIER 0.20f
#include <stdio.h>
#include "./libs/miniaudio.h"
#include "dsp/dsp.h"

typedef struct {
    float phase;
} UserData;


void data_callback(const ma_device* device, void* output, const void* input, ma_uint32 frameCount) {
    float* out = output;
    UserData* data = device->pUserData;

    float freq = 440.0f;
    float phase_increment = freq / (float)device->sampleRate; // Increment for 0.0 to 1.0 phase
    float mix_gain = 0.5f; // For two waves, 0.5 is a safe starting point

    for (ma_uint32 i = 0; i < frameCount; i++) {
        // Pass normalized phase (0.0 to 1.0) to generateWave
        Vec2 output;
        output = (Vec2){0.0f, 0.0f};

        Vec2 sine_wave = vec2_mul(generateWave(WAVE_SINE, data->phase, 0.0f), 1.8f); // 70% volume
        Vec2 triangle_wave = vec2_mul(generateWave(WAVE_PULSE, data->phase, 0.25f), 0.3f); // 30% volume
        // No need for a global mix_gain if individual gains sum up to <= 1.0
        Vec2 combined_wave = vec2_add(sine_wave, triangle_wave);


        combined_wave = vec2_mul(combined_wave, mix_gain); // Using your scalar vec2_mul

        combined_wave = vec2_softClip(combined_wave);



        output = combined_wave;





        //output to sound device
        out[i * 2]     = output.x * VOLUME_MODIFIER;
        out[i * 2 + 1] = output.y * VOLUME_MODIFIER;
        data->phase += phase_increment;
        if (data->phase >= 1.0f) {
            data->phase -= 1.0f;
        }
    }
    (void)input;
}


int main() {
    ma_device_config config = ma_device_config_init(ma_device_type_playback);
    config.playback.format = ma_format_f32;
    config.playback.channels = DEVICE_CHANNELS;
    config.sampleRate = DEVICE_SAMPLE_RATE;
    config.dataCallback = data_callback;

    UserData userData = {0};

    config.pUserData = &userData;

    ma_device device;

    if (ma_device_init(NULL, &config, &device) != MA_SUCCESS) {
        printf("failed to init device\n");
        return -1;
    }

    if (ma_device_start(&device) != MA_SUCCESS) {
        printf("failed to start device\n");
        return -2;
    }

    printf("playing... press enter to stop\n");
    getchar();
    ma_device_uninit(&device);
    return 0;
}