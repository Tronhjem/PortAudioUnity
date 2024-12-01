#include <iostream>
#include "SimpleAudioPlayer.h"

void SimpleAudioPlayer::Run()
{
    err = Pa_Initialize();

    if (err != paNoError)
    {
        std::cout << "failed to init" << std::endl;
        return;
    }

    // Open an audio I/O stream
    err = Pa_OpenDefaultStream(&stream,
        0,              // no input channels
        2,              // Channels
        paFloat32,      // 32 bit floating point output
        SAMPLE_RATE,    // Sample Rate
        256,            // buffer size
        patestCallback, // Callback function
        &data);         // This is a pointer that will be passed to the callback
                                    
    if (err != paNoError)
    {
        std::cout << "failed to open stream" << std::endl;
        return;
    }

    err = Pa_StartStream( stream );
    if (err != paNoError)
    {
        std::cout << "failed to start stream" << std::endl;
    }
}

void SimpleAudioPlayer::Stop()
{
    PaError err;
    err = Pa_StopStream(stream);

    err = Pa_Terminate();
    if (err != paNoError)
    {
        std::cout << "failed to terminiate" << std::endl;
        return;
    }
}
