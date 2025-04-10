using UnityEngine;

public class SimpleAudioPlayerInterface : MonoBehaviour
{
    private float f = 0f;
    private float delta = 500f / 44100f;

    private bool firstTimeSetup = true;
    private int readPosition = 0;
    private const int bufferLength = 4096;
    private const int bufferLengthMask = bufferLength - 1;

    void OnEnable()
    {
        AudioSource source = GetComponent<AudioSource>();
        if (source != null)
        {
            source.loop = true;
            source.Play();
        }
    }

    private void OnAudioFilterRead(float[] data, int channels)
    {
        int length = data.Length;
        if (channels > 1)
        {
            length = length / channels;
        }

        if (!AudioInitializer.AudioIsInitialized)
            return;

        if(firstTimeSetup)
        {
            int pos = AudioPlayer.GetWritePosition();
            readPosition = (pos - length) & bufferLengthMask;
            firstTimeSetup = false;
        }

        for (int i = 0; i < data.Length; i += 2)
        {
            //float sample = 0.2f * Mathf.Sin(2 * Mathf.PI * f);
            ////float sample = GetSampleFromBuffer(readPosition);

            float sample = AudioPlayer.GetSampleFromBuffer(readPosition);
            data[i] = sample;
            data[i + 1] = sample;

            //f += delta;

            ++readPosition;
            readPosition &= bufferLengthMask;
        }
    }
}
