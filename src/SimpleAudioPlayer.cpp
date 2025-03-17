
#include "portaudio.h"
#include "pa_asio.h"
#include "TempBuffer.h"
#include "SimpleAudioTypes.h"
#include "SimpleAudioPlayer.h"

#include <cmath>
#include <iostream>

#define INPUT_DEVICE Pa_GetDefaultInputDevice()
#define OUTPUT_DEVICE Pa_GetDefaultOutputDevice()

double d = 0.0;
double f = 300.0 / (double)SAMPLE_RATE;

SimpleAudio::SimpleAudio() : mErr(0), mStream(nullptr)
{
    mTempBuffer = new TempBuffer();
    mErr = Pa_Initialize();
}

SimpleAudio::~SimpleAudio()
{
    delete mTempBuffer;
    Pa_Terminate();
}

bool SimpleAudio::OpenStream(int inputDevice, int inputChannels, int outputDevice, int outputChannels, int bufferSize, int sampleRate)
{
    if (mErr != paNoError)
        return false;

    PaStreamParameters inputParameters;
    PaStreamParameters outputParameters;

    inputParameters.device = inputDevice;
    inputParameters.channelCount = 1;
    inputParameters.sampleFormat = paFloat32;
    inputParameters.suggestedLatency = Pa_GetDeviceInfo(inputParameters.device)->defaultLowInputLatency;
    inputParameters.hostApiSpecificStreamInfo = nullptr;

    outputParameters.device = outputDevice;
    outputParameters.channelCount = 2;
    outputParameters.sampleFormat = paFloat32;
    outputParameters.suggestedLatency = Pa_GetDeviceInfo(outputParameters.device)->defaultLowOutputLatency;
    outputParameters.hostApiSpecificStreamInfo = nullptr;

#if PA_USE_ASIO
    PaAsioStreamInfo asioOutputInfo;
    int outputChannelSelectors[2]{0, 1};
    asioOutputInfo.size = sizeof(PaAsioStreamInfo);
    asioOutputInfo.version = 1;
    asioOutputInfo.hostApiType = paASIO;
    asioOutputInfo.flags = paAsioUseChannelSelectors;
    asioOutputInfo.channelSelectors = outputChannelSelectors;

    inputParameters.hostApiSpecificStreamInfo = &asioOutputInfo;
    outputParameters.hostApiSpecificStreamInfo = nullptr;
#endif

    mErr = Pa_OpenStream(
        &mStream,
        &inputParameters,
        &outputParameters,
        sampleRate,
        bufferSize,
        paClipOff,
        AudioCallback,
        mTempBuffer);

    PaErrorCode code = (PaErrorCode)mErr;
    std::cout << "Open stream: " << Pa_GetErrorText((PaErrorCode)mErr) << std::endl;
    return mErr == 0;
}

bool SimpleAudio::StartStream()
{
    mErr = Pa_StartStream(mStream);
    PaErrorCode code = (PaErrorCode)mErr;
    std::cout << "Start Stream: " << Pa_GetErrorText((PaErrorCode)mErr) << std::endl;
    return mErr == paNoError;
}

void SimpleAudio::StopStream()
{
    mErr = Pa_StopStream(mStream);
    PaErrorCode code = (PaErrorCode)mErr;
    std::cout << "Stop Stream: " << Pa_GetErrorText((PaErrorCode)mErr) << std::endl;
}

void SimpleAudio::CloseStream()
{
    mErr = Pa_CloseStream(mStream);
    std::cout << "Close Stream: " << Pa_GetErrorText((PaErrorCode)mErr) << std::endl;
}

void SimpleAudio::PrintDeviceInfo()
{
    const int count = Pa_GetDeviceCount();
    for (int i = 0; i < count; ++i)
    {
        const PaDeviceInfo* info = Pa_GetDeviceInfo(i);
        std::cout << i << ": " << info->name << std::endl;
    }

    // auto apiCount = Pa_GetHostApiCount();
    // for (int i = 0; i < apiCount; ++i)
    // {
    //     auto info = Pa_GetHostApiInfo(i);
    //     int x = 0;
    //     ++x;
    // }
}

int AudioCallback(const void *inputBuffer, 
                  void *outputBuffer,
                  unsigned long framesPerBuffer,
                  const PaStreamCallbackTimeInfo *timeInfo,
                  PaStreamCallbackFlags statusFlags,
                  void *userData)
{
    TempBuffer* data = (TempBuffer*) userData;

    float* in = (float*)inputBuffer;
    float* out = (float*)outputBuffer;

    int counter = 0;
    for (int i = 0; i < framesPerBuffer; i++)
    {
        // Sine test
        double sample = 0.2 * sin(2.0 * PI * d);
        d += f;

        data->WriteNextSample((float)sample);

        // out[counter] = in[counter];
        out[counter] = sample;
        ++counter;

        // out[counter] = in[counter];
        out[counter] = sample;
        ++counter;
    }

    return 0;
}
