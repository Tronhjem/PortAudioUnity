#pragma once
#include "SimpleAudioTypes.h"

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