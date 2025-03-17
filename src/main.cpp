#include "SimpleAudioAPI.h"
#include "portaudio.h"
#include <iostream>

int main()
{
    CreateAudio();
    PrintDevices();

    // input device 2, 1 channel, output device 3, 2 channels.
    StartAudioStream(2, 1, 3, 2);

    Pa_Sleep(6000);

    StopAudioStream();
    DestroyAudio();

    return 0;
}
