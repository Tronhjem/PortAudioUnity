#pragma once

#if WIN32
    #define DLLEXPORT __declspec(dllexport)
#else
    #define DLLEXPORT
#endif

// #define PA_USE_ASIO _WIN32
#define SAMPLE_RATE (44100)
#define FRAMES_PER_BUFFER (64)
#define PI (3.14159265359)

const int BUFFER_LENGTH = 4096;
const int BUFFER_LENGTH_MASK = BUFFER_LENGTH - 1;