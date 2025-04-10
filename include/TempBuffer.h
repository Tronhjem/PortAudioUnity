#pragma once
#include "SimpleAudioTypes.h"

class TempBuffer
{
public:
    TempBuffer() : mWriteLocation(0), mLastCompletedBufferPosition(0)
    {
        for (int i = 0; i < bufferLength; ++i)
        {
            buffer[i] = 0.f;
        }
    }

    void WriteNextSample(float s)
    {
        buffer[mWriteLocation] = s;
        ++mWriteLocation;
        mWriteLocation &= bufferLengthMask;
    }

    float GetSample(int i)
    {
        i &= bufferLengthMask;
        return buffer[i];
    }

    int GetLastCompletedBufferPosition() { return mLastCompletedBufferPosition; }
    int GetWritePosition() { return mWriteLocation; }
    void IncrementCompletedBufferPosition(int sample)
    {
        mLastCompletedBufferPosition += sample;
        mLastCompletedBufferPosition &= bufferLengthMask;
    }

private:
    int mWriteLocation;
    int mLastCompletedBufferPosition;
    float buffer[bufferLength];
};