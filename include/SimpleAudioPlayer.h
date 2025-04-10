#pragma once

#include "TempBuffer.h"
#include "portaudio.h"

struct UserData
{
    TempBuffer* mBuffer;
    PaStreamParameters inputParameters;
    PaStreamParameters outputParameters;
};

class SimpleAudio
{
public:
    SimpleAudio();
    ~SimpleAudio();
    bool OpenStream(int inputDevice, int outputDevice, int bufferSize, int sampleRate);
    void CloseStream();
    bool StartStream();
    void StopStream();
    void PrintDeviceInfo();

    UserData mUserData;

private:
    PaError mErr;
    PaStream* mStream;
};

int AudioCallback(const void *inputBuffer, 
                void *outputBuffer,
                unsigned long framesPerBuffer,
                const PaStreamCallbackTimeInfo *timeInfo,
                PaStreamCallbackFlags statusFlags,
                void *userData);