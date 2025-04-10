using UnityEngine;
using System.Runtime.InteropServices;
using System;

public class AudioPlayer
{
    [DllImport("AudioPlayer", CallingConvention = CallingConvention.Cdecl)]
    public static extern void CreateAudio();

    [DllImport("AudioPlayer", CallingConvention = CallingConvention.Cdecl)]
    public static extern void DestroyAudio();

    [DllImport("AudioPlayer", CallingConvention = CallingConvention.Cdecl)]
    public static extern bool StartAudioStream(int inputDevice, int outputDevic3);

    [DllImport("AudioPlayer", CallingConvention = CallingConvention.Cdecl)]
    public static extern void StopAudioStream();

    [DllImport("AudioPlayer", CallingConvention = CallingConvention.Cdecl)]
    public static extern int GetBufferLength();

    [DllImport("AudioPlayer", CallingConvention = CallingConvention.Cdecl)]
    public static extern int GetWritePosition();

    [DllImport("AudioPlayer", CallingConvention = CallingConvention.Cdecl)]
    public static extern float GetSampleFromBuffer(int index);

    [DllImport("AudioPlayer", CallingConvention = CallingConvention.Cdecl)]
    public static extern int GetDeviceCount();

    [DllImport("AudioPlayer", CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr GetInputDeviceName(int deviceIndex);

    [DllImport("AudioPlayer", CallingConvention = CallingConvention.Cdecl)]
    private static extern int GetDeviceInputChannels(int deviceIndex);

    [DllImport("AudioPlayer", CallingConvention = CallingConvention.Cdecl)]
    private static extern int GetDeviceOutputChannels(int deviceIndex);

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

    public static AudioPlayer Instance
    {
        get
        {
            if (init == null)
                init = new AudioPlayer();
            return init;
        }
    }
    private static AudioPlayer init = null;

    public void Init()
    {
        Debug.Log("Init");
    }

    public AudioPlayer()
    {
        CreateAudio();
    }
    ~AudioPlayer()
    {
        DestroyAudio();
    }
}

public class AudioInitializer : MonoBehaviour
{
    [HideInInspector] public int InputDeviceId = 1;
    [HideInInspector] public int OutputDeviceId = 3;
    [HideInInspector] public static bool AudioIsInitialized = false;

    private void Awake()
    {
        AudioPlayer.Instance.Init();
    }

    void OnEnable()
    {
        AudioIsInitialized = AudioPlayer.StartAudioStream(InputDeviceId, OutputDeviceId);
    }

    void OnDisable()
    {
        AudioIsInitialized = false;
        AudioPlayer.StopAudioStream();
    }

    private void OnDestroy()
    {
    }
}
