using UnityEngine;
using System.Runtime.InteropServices;
using System;

public class AudioInitializer : MonoBehaviour
{
    [DllImport("AudioPlayer", CallingConvention = CallingConvention.Cdecl)]
    public static extern void CreateAudio();

    [DllImport("AudioPlayer", CallingConvention = CallingConvention.Cdecl)]
    public static extern void DestroyAudio();

    [DllImport("AudioPlayer", CallingConvention = CallingConvention.Cdecl)]
    public static extern bool StartAudioStream(int inputDevice, int inputChannel, int outputDevice, int outputChannel);

    [DllImport("AudioPlayer", CallingConvention = CallingConvention.Cdecl)]
    public static extern void StopAudioStream();

    [DllImport("AudioPlayer", CallingConvention = CallingConvention.Cdecl)]
    public static extern int GetBufferLength();

    [DllImport("AudioPlayer", CallingConvention = CallingConvention.Cdecl)]
    public static extern int GetWritePosition();

    [DllImport("AudioPlayer", CallingConvention = CallingConvention.Cdecl)]
    public static extern int GetSampleFromBuffer(int index);

    [DllImport("AudioPlayer", CallingConvention = CallingConvention.Cdecl)]
    public static extern int GetDeviceCount();

    [DllImport("AudioPlayer", CallingConvention = CallingConvention.Cdecl)]
    public static extern IntPtr GetInputDeviceName(int deviceIndex);

    [DllImport("AudioPlayer", CallingConvention = CallingConvention.Cdecl)]
    public static extern int GetDeviceInputChannels(int deviceIndex);

    [DllImport("AudioPlayer", CallingConvention = CallingConvention.Cdecl)]
    public static extern int GetDeviceOutputChannels(int deviceIndex);

    public static string GetName(int deviceIndex)
    {
        IntPtr intptr = GetInputDeviceName(deviceIndex);
        return Marshal.PtrToStringAnsi(intptr);
    }

    public static int GetInputChannels(int deviceIndex)
    {
        return GetDeviceInputChannels(deviceIndex);
    }

    public static int GetOutputChannels(int deviceIndex)
    {
        return GetDeviceOutputChannels(deviceIndex);
    }

    // UNITY Stuff
    private void Awake()
    {
        CreateAudio();
    }

    void OnEnable()
    {
        int bufferLeng = GetBufferLength();

        int devices = GetDeviceCount();
        for (int i = 0; i < devices; ++i)
        {
            GetName(i);
            GetInputChannels(i);
            GetOutputChannels(i);
        }

        bool wasInit = StartAudioStream(2, 1, 3, 2);
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
