
#include <iostream>
#include "portaudio.h"
#include "pa_asio.h"

#include <cmath>

#define SAMPLE_RATE (44100)
#define FRAMES_PER_BUFFER (64)
#define PI (3.14159265359)
#define PA_USE_ASIO 1

#define INPUT_DEVICE Pa_GetDefaultInputDevice()
#define OUTPUT_DEVICE Pa_GetDefaultOutputDevice()

double d = 0.0;
double f = 300.0 / (double)SAMPLE_RATE;

int AudioCallback(const void* inputBuffer, void* outputBuffer,
	unsigned long framesPerBuffer,
	const PaStreamCallbackTimeInfo* timeInfo,
	PaStreamCallbackFlags statusFlags,
	void* userData);

const int bufferLength = 4096;
const int bufferLengthMask = bufferLength - 1;

class TempBuffer
{
public:
	TempBuffer() : writeLocation(0)
	{
		for (int i = 0; i < bufferLength; ++i)
		{
			buffer[i] = 0.f;
		}
	}

	void WriteNextSample(float s)
	{
		buffer[writeLocation] = s;
		++writeLocation;
		writeLocation &= bufferLengthMask;
	}

	float GetSample(int i)
	{
		i &= bufferLengthMask;
		return buffer[i];
	}

	int writeLocation;

private:
	float buffer[bufferLength];
};

class AudioInput
{
public:

	TempBuffer* tempBuffer;
	PaError err; 
	PaStream* stream;

	AudioInput() : err(0), stream(nullptr)
	{
		tempBuffer = new TempBuffer();
		err = Pa_Initialize();
	}

	bool OpenStream()
	{

		if (err != paNoError)
			return false;

#if PA_USE_ASIO
		PaStreamParameters inputParameters;
		PaStreamParameters outputParameters;

		PaAsioStreamInfo asioOutputInfo;
		int outputChannelSelectors[2]{ 0, 1 };
		asioOutputInfo.size = sizeof(PaAsioStreamInfo);
		asioOutputInfo.version = 1;
		asioOutputInfo.hostApiType = paASIO;
		asioOutputInfo.flags = paAsioUseChannelSelectors;
		asioOutputInfo.channelSelectors = outputChannelSelectors;

		inputParameters.device = 4;
		inputParameters.channelCount = 2;
		inputParameters.sampleFormat = paFloat32;
		inputParameters.suggestedLatency = Pa_GetDeviceInfo(inputParameters.device)->defaultLowInputLatency;
		inputParameters.hostApiSpecificStreamInfo = &asioOutputInfo;

		outputParameters.device = 4;
		outputParameters.channelCount = 2;
		outputParameters.sampleFormat = paFloat32;
		outputParameters.suggestedLatency = Pa_GetDeviceInfo(outputParameters.device)->defaultLowOutputLatency;
		outputParameters.hostApiSpecificStreamInfo = nullptr;
		//outputParameters.hostApiSpecificStreamInfo = &asioOutputInfo;

		auto count = Pa_GetDeviceCount();
		for (int i = 0; i < count; ++i)
		{
			auto info = Pa_GetDeviceInfo(i);
			int x = 0; ++x;
		}

		auto apiCount = Pa_GetHostApiCount();
		for (int i = 0; i < apiCount; ++i)
		{
			auto info = Pa_GetHostApiInfo(i);
			int x = 0; ++x;
		}

		err = Pa_OpenStream(
			&stream,
			&inputParameters,
			//NULL,
			&outputParameters,
			SAMPLE_RATE,
			FRAMES_PER_BUFFER,
			paClipOff,
			AudioCallback,
			tempBuffer
		);

		PaErrorCode code = (PaErrorCode)err;
		std::cout << code << std::endl;

#else

		err = Pa_OpenDefaultStream(&stream,
			2,          /* no input channels */
			2,          /* stereo output */
			paFloat32,  /* 32 bit floating point output */
			SAMPLE_RATE,
			64,        /* frames per buffer, i.e. the number
							   of sample frames that PortAudio will
							   request from the callback. Many apps
							   may want to use
							   paFramesPerBufferUnspecified, which
							   tells PortAudio to pick the best,
							   possibly changing, buffer size.*/
			AudioCallback, /* this is your callback function */
			tempBuffer); /*This is a pointer that will be passed to
							   your callback*/
#endif

		return err == 0;
    }

	bool StartStream()
	{
		err = Pa_StartStream(stream);
		return err == paNoError;
	}

	void StopStream()
	{
		Pa_StopStream(stream);
	}

	void CloseStream()
	{
		Pa_CloseStream(stream);
	}

    ~AudioInput()
    {
		delete tempBuffer;
		Pa_Terminate();
    }
};

int AudioCallback(const void* inputBuffer, void* outputBuffer,
	unsigned long framesPerBuffer,
	const PaStreamCallbackTimeInfo* timeInfo,
	PaStreamCallbackFlags statusFlags,
	void* userData)
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

		out[counter] = in[counter];
		//out[counter] = sample;
		++counter;

		out[counter] = in[counter];
		//out[counter] = sample;
		++counter;
	}

	return 0;
}

AudioInput* audioInAndOut = nullptr;

extern "C"
{
	__declspec(dllexport) void CreateAudio()
	{
		if (audioInAndOut == nullptr)
		{
			audioInAndOut = new AudioInput();
		}
	}

	__declspec(dllexport) void DestroyAudio()
	{
		if (audioInAndOut != nullptr)
		{
			delete audioInAndOut;
			audioInAndOut = nullptr;
		}
	}

	__declspec(dllexport) bool StartAudioStream()
	{
		if (audioInAndOut != nullptr)
		{
			audioInAndOut->OpenStream();
			return audioInAndOut->StartStream();
		}

		return false;
	}

	__declspec(dllexport) void StopAudioStream()
	{
		if (audioInAndOut != nullptr)
		{
			audioInAndOut->StopStream();
			audioInAndOut->CloseStream();
		}
	}

	__declspec(dllexport) int GetBufferLength()
	{
		return bufferLength;
	}

	__declspec(dllexport) int GetWritePosition()
	{
		if (audioInAndOut != nullptr)
			return audioInAndOut->tempBuffer->writeLocation;

		return 0;
	}

	__declspec(dllexport) int GetSampleFromBuffer(int index)
	{
		if (audioInAndOut != nullptr)
			return audioInAndOut->tempBuffer->GetSample(index);

		return 0;
	}
}

int main()
{
	CreateAudio();
	StartAudioStream();
	Pa_Sleep(20000);
	StopAudioStream();
	DestroyAudio();

	return 0;
}
