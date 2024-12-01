### Port Audio in Unity

A small example of how to set up a Port Audio to be loaded as a library in Unity and play. 
This is just for OSX at the moment and a very small example. 

Use CMake to build. 

For now it's just a class you instantiate called SimpleAudioPlayer. 
Put the lib in the your Unity project and make sure it's setup to load correctly. 

Reference `RunSimpleAudioPlayer.cs` for how to load it. It currently just starts and stops the engine and plays a sine wave.
