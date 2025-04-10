using UnityEngine;
using UnityEditor;

[CustomEditor(typeof(AudioInitializer))]
public class AudioInitializerEdtor : Editor
{
    private string[] InputDevices = null;
    private string[] OutputDevices = null;
    private int selectedInput = 0;
    private int selectedOutput = 0;
    private void OnEnable()
    {
        AudioPlayer.Instance.Init();
        int deviceCount = AudioPlayer.GetDeviceCount();
        if (deviceCount > 0 )
        {
            if (InputDevices == null || InputDevices.Length != deviceCount)
            {
                InputDevices = new string[deviceCount];
                for(int i = 0; i < deviceCount; ++i)
                {
                    InputDevices[i] = AudioPlayer.GetName(i);
                }
            }

            if (OutputDevices == null || OutputDevices.Length != deviceCount)
            {
                OutputDevices = new string[deviceCount];
                for (int i = 0; i < deviceCount; ++i)
                {
                    OutputDevices[i] = AudioPlayer.GetName(i);
                }
            }
            var myTarget = target as AudioInitializer;
            selectedInput = myTarget.InputDeviceId;
            selectedOutput = myTarget.OutputDeviceId;
        }
    }

    public override void OnInspectorGUI()
    {

        if (InputDevices != null)
        {
            EditorGUILayout.LabelField("Input:");
            selectedInput = EditorGUILayout.Popup(selectedInput, InputDevices);
            EditorGUILayout.LabelField("Output:");
            selectedOutput = EditorGUILayout.Popup(selectedOutput, OutputDevices);
            var myTarget = target as AudioInitializer;
            myTarget.InputDeviceId = selectedInput;
            myTarget.OutputDeviceId = selectedOutput;

            //myTarget.SetMicInput(devices[selectedDevice]);
        }

        EditorGUILayout.Space(5);
        EditorGUILayout.Separator();

        DrawDefaultInspector();
    }
}
