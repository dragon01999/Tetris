#include <SDL2/SDL.h>
#include <math.h>
#include "beep.h"

float phase = 0.0;  // global so callback can use it

// callback must be outside main
void callback(void *userdata, Uint8 *stream, int len) {
    float *f = (float*)stream;
    int samples = len / sizeof(float);
    for(int i=0; i<samples; i++) {
        f[i] = sinf(phase * 2*M_PI) * 0.5f;
        phase += 440.0 / 44100;  // 440 Hz
        if(phase >= 1.0) phase -= 1.0;
    }
}

int bep() {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        SDL_Log("SDL_Init Error: %s", SDL_GetError());
        return 1;
    }

    SDL_AudioSpec want, have;
    SDL_zero(want);

    want.freq = 44100;
    want.format = AUDIO_F32SYS;
    want.channels = 1;
    want.samples = 4096;
    want.callback = callback;  // now works

    SDL_AudioDeviceID dev = SDL_OpenAudioDevice(NULL, 0, &want, &have, 0);
    if (!dev) {
        SDL_Log("SDL_OpenAudioDevice Error: %s", SDL_GetError());
        return 1;
    }

    SDL_PauseAudioDevice(dev, 0);  // start playing
    SDL_Delay(300);                // play for 300ms
    SDL_CloseAudioDevice(dev);
    SDL_Quit();
    return 0;
}
