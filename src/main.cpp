#include "SimpleAudioAPI.h"
#include "portaudio.h"
#include <iostream>

int main()
{
    CreateAudio();
    PrintDevices();

    StartAudioStream();

    Pa_Sleep(6000);

    StopAudioStream();
    DestroyAudio();

    return 0;
}
