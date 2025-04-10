#pragma once
#include "SimpleAudioTypes.h"

class TempBuffer
{
public:
    TempBuffer() : mWriteLocation(0), mLastCompletedBufferPosition(0)
    {
        for (int i = 0; i < BUFFER_LENGTH; ++i)
        {
            buffer[i] = 0.f;
        }
    }

    void WriteNextSample(float s)
    {
        buffer[mWriteLocation] = s;
        ++mWriteLocation;
        mWriteLocation &= BUFFER_LENGTH_MASK;
    }

    float GetSample(int i)
    {
        i &= BUFFER_LENGTH_MASK;
        return buffer[i];
    }

    int GetLastCompletedBufferPosition() { return mLastCompletedBufferPosition; }
    int GetWritePosition() { return mWriteLocation; }
    void IncrementCompletedBufferPosition(int sample)
    {
        mLastCompletedBufferPosition += sample;
        mLastCompletedBufferPosition &= BUFFER_LENGTH_MASK;
    }

private:
    int mWriteLocation;
    int mLastCompletedBufferPosition;
    float buffer[BUFFER_LENGTH];
};