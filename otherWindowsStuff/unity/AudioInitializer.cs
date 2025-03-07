using UnityEngine;
using System.Runtime.InteropServices;

public class AudioInitializer : MonoBehaviour
{
    [DllImport("SimpleAudioPlayerDLL", CallingConvention = CallingConvention.Cdecl)]
    public static extern void CreateAudio();

    [DllImport("SimpleAudioPlayerDLL", CallingConvention = CallingConvention.Cdecl)]
    public static extern void DestroyAudio();

    [DllImport("SimpleAudioPlayerDLL", CallingConvention = CallingConvention.Cdecl)]
    public static extern bool StartAudioStream();

    [DllImport("SimpleAudioPlayerDLL", CallingConvention = CallingConvention.Cdecl)]
    public static extern void StopAudioStream();

    [DllImport("SimpleAudioPlayerDLL", CallingConvention = CallingConvention.Cdecl)]
    public static extern int GetBufferLength();

    [DllImport("SimpleAudioPlayerDLL", CallingConvention = CallingConvention.Cdecl)]
    public static extern int GetWritePosition();

    [DllImport("SimpleAudioPlayerDLL", CallingConvention = CallingConvention.Cdecl)]
    public static extern int GetSampleFromBuffer(int index);

    private void Awake()
    {
        CreateAudio();
    }

    void OnEnable()
    {
        int bufferLeng = GetBufferLength();
        bool wasInit = StartAudioStream();
    }

    void OnDisable()
    {
        StopAudioStream();
    }
    private void OnDestroy()
    {
        DestroyAudio();
    }
}

