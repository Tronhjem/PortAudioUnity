#pragma once

#if WIN32
    #define DLLEXPORT __declspec(dllexport)
#else
    #define DLLEXPORT
#endif

#define PA_USE_ASIO 0
#define SAMPLE_RATE (44100)
#define FRAMES_PER_BUFFER (64)
#define PI (3.14159265359)

const int bufferLength = 4096;
const int bufferLengthMask = bufferLength - 1;