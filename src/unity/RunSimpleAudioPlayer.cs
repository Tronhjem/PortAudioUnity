using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using UnityEngine;

public class RunSimpleAudioPlayer : MonoBehaviour
{
    //Just for testing
    [DllImport("AudioPlayer", CallingConvention = CallingConvention.Cdecl)]
    public static extern int AddSomeNumbers(int a, int b);

    [DllImport("AudioPlayer", CallingConvention = CallingConvention.Cdecl)]
    public static extern void RunAudioStuff();

    [DllImport("AudioPlayer", CallingConvention = CallingConvention.Cdecl)]
    public static extern void StopAudioStuff();

    void Start()
    {
        // to see that it's working properly calling functions from the library.
        Debug.Log(AddSomeNumbers(2,3));
        RunAudioStuff();
    }

    void OnDisable()
    {
        StopAudioStuff();
    }
}
