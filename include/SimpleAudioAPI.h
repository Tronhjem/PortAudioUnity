#pragma once
#include "SimpleAudioPlayer.h"
#include "SimpleAudioTypes.h"

SimpleAudio* audioInAndOut = nullptr;

void PrintDevices()
{
	if (audioInAndOut != nullptr)
	{
		audioInAndOut->PrintDeviceInfo();
	}
}

extern "C"
{
    DLLEXPORT void CreateAudio()
    {
		if (audioInAndOut == nullptr)
		{
			audioInAndOut = new SimpleAudio();
		}
	}

    DLLEXPORT void DestroyAudio()
    {
		if (audioInAndOut != nullptr)
		{
			delete audioInAndOut;
			audioInAndOut = nullptr;
		}
	}

    DLLEXPORT bool StartAudioStream(int inputDevice, int outputDevice)
    {
		if (audioInAndOut != nullptr)
		{
			audioInAndOut->OpenStream(inputDevice, outputDevice, FRAMES_PER_BUFFER, SAMPLE_RATE);
			return audioInAndOut->StartStream();
		}

		return false;
	}

    DLLEXPORT void StopAudioStream()
    {
		if (audioInAndOut != nullptr)
		{
			audioInAndOut->StopStream();
			audioInAndOut->CloseStream();
		}
	}

    DLLEXPORT int GetBufferLength()
    {
		return bufferLength;
	}

    DLLEXPORT int GetWritePosition()
    {
		if (audioInAndOut != nullptr)
			return audioInAndOut->mUserData.mBuffer->GetWritePosition();

		return 0;
	}

    DLLEXPORT float GetSampleFromBuffer(int index)
    {
		if (audioInAndOut != nullptr)
			return audioInAndOut->mUserData.mBuffer->GetSample(index);

		return 0.f;
	}

    DLLEXPORT int GetDeviceCount()
	{
		return Pa_GetDeviceCount();
	}

    DLLEXPORT const char* GetInputDeviceName(int deviceIndex)
    {
		return Pa_GetDeviceInfo(deviceIndex)->name;
	}

    DLLEXPORT int GetDeviceInputChannels(int deviceIndex)
    {
		return Pa_GetDeviceInfo(deviceIndex)->maxInputChannels;
	}

    DLLEXPORT int GetDeviceOutputChannels(int deviceIndex)
    {
		return Pa_GetDeviceInfo(deviceIndex)->maxOutputChannels;
	}
}