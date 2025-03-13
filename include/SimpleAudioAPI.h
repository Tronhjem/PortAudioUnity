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

    DLLEXPORT bool StartAudioStream()
    {
		if (audioInAndOut != nullptr)
		{
			audioInAndOut->OpenStream(2, 3, FRAMES_PER_BUFFER, SAMPLE_RATE);
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
			return audioInAndOut->mTempBuffer->writeLocation;

		return 0;
	}

    DLLEXPORT int GetSampleFromBuffer(int index)
    {
		if (audioInAndOut != nullptr)
			return audioInAndOut->mTempBuffer->GetSample(index);

		return 0;
	}
}