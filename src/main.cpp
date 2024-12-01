#include "SimpleAudioPlayer.h"

SimpleAudioPlayer audioPlayer;
extern "C"
{
    int AddSomeNumbers(int a, int b)
    {
        return a + b;
    }

    void RunAudioStuff()
    {
        audioPlayer.Run();
    }

    void StopAudioStuff(void* streamToStop)
    {
        audioPlayer.Stop();
    }
}