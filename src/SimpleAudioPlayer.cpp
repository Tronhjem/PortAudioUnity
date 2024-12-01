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

    /* Open an audio I/O stream. */
    err = Pa_OpenDefaultStream(&stream,
                               0,         /* no input channels */
                               2,         /* stereo output */
                               paFloat32, /* 32 bit floating point output */
                               SAMPLE_RATE,
                               256,            /* frames per buffer, i.e. the number
                                                      of sample frames that PortAudio will
                                                      request from the callback. Many apps
                                                      may want to use
                                                      paFramesPerBufferUnspecified, which
                                                      tells PortAudio to pick the best,
                                                      possibly changing, buffer size.*/
                               patestCallback, /* this is your callback function */
                               &data);         /*This is a pointer that will be passed to
                                                         your callback*/
    if (err != paNoError)
    {
        std::cout << "failed to open stream" << std::endl;
        return;
    }

    // Start wait stop.
    err = Pa_StartStream( stream );

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
