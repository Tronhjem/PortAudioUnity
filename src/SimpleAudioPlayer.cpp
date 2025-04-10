
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
    mUserData.mBuffer = new TempBuffer();
    mErr = Pa_Initialize();
}

SimpleAudio::~SimpleAudio()
{
    delete mUserData.mBuffer;
    Pa_Terminate();
}

bool SimpleAudio::OpenStream(int inputDevice, int outputDevice, int bufferSize, int sampleRate)
{
    if (mErr != paNoError)
        return false;

    mUserData.inputParameters.device = inputDevice;
    mUserData.inputParameters.channelCount = Pa_GetDeviceInfo(inputDevice)->maxInputChannels;
    mUserData.inputParameters.sampleFormat = paFloat32;
    mUserData.inputParameters.suggestedLatency = Pa_GetDeviceInfo(mUserData.inputParameters.device)->defaultLowInputLatency;
    mUserData.inputParameters.hostApiSpecificStreamInfo = nullptr;

    mUserData.outputParameters.device = outputDevice;
    mUserData.outputParameters.channelCount = Pa_GetDeviceInfo(outputDevice)->maxOutputChannels;
    mUserData.outputParameters.sampleFormat = paFloat32;
    mUserData.outputParameters.suggestedLatency = Pa_GetDeviceInfo(mUserData.outputParameters.device)->defaultLowOutputLatency;
    mUserData.outputParameters.hostApiSpecificStreamInfo = nullptr;

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
        &mUserData.inputParameters,
        &mUserData.outputParameters,
        sampleRate,
        bufferSize,
        paClipOff,
        AudioCallback,
        &mUserData);

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
}

int AudioCallback(const void *inputBuffer, 
                  void *outputBuffer,
                  unsigned long framesPerBuffer,
                  const PaStreamCallbackTimeInfo *timeInfo,
                  PaStreamCallbackFlags statusFlags,
                  void *userData)
{
    UserData* data = (UserData*) userData;

    float* in = (float*)inputBuffer;
    float* out = (float*)outputBuffer;

    int inCounter = 0;
    int outCounter = 0;
    for (int i = 0; i < framesPerBuffer; i++)
    {
        // Sine test
        // double sample = 0.2 * sin(2.0 * PI * d);
        // d += f;

        float inputSum = 0.f;
        if (in != nullptr)
        {
            for (int j = 0; j < data->inputParameters.channelCount; ++j)
            {
                inputSum += in[inCounter] * 0.707f;
                ++inCounter;
            }

            if (data->mBuffer != nullptr)
                data->mBuffer->WriteNextSample(inputSum);
        }

        if (out != nullptr)
        {
            for (int j = 0; j < data->outputParameters.channelCount; ++j)
            {
                out[outCounter] = inputSum;
                ++outCounter;
            }
        }
    }

    return 0;
}
