cmake_minimum_required(VERSION 3.19)
set(CMAKE_CXX_STANDARD 17)

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/SimpleAudioPlayer.cpp
)

if(WIN32)
    set(CMAKE_VS_SDK_INCLUDE_DIRECTORIES $(VC_IncludePath);$(WindowsSDK_IncludePath); ${CMAKE_SOURCE_DIR}/includes)

    #Windows DLL
    project(SimpleAudioPlayerDLL)
    add_library(SimpleAudioPlayerDLL SHARED ${SOURCES})
    target_include_directories(SimpleAudioPlayerDLL PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/includes)
    target_link_libraries(SimpleAudioPlayerDLL portaudio)
    target_link_directories(SimpleAudioPlayerDLL PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/lib)

elseif(APPLE)
    # Audio Player Bundle.
    project(AudioPlayer)
    add_library(AudioPlayer MODULE ${SOURCES})            

    set_target_properties(
        AudioPlayer 
        PROPERTIES
        BUNDLE True
        MACOSX_BUNDLE_GUI_IDENTIFIER com.myshit.something.AudioPlayer
        MACOSX_BUNDLE_BUNDLE_NAME AudioPlayer
        MACOSX_BUNDLE_BUNDLE_VERSION "0.1"
        MACOSX_BUNDLE_SHORT_VERSION_STRING "0.1"
        MACOSX_BUNDLE_SUPPORTED_PLATFORMS MacOSX
    )

    target_include_directories(AudioPlayer PUBLIC include)
    target_link_directories(AudioPlayer PRIVATE lib)

    target_link_libraries(AudioPlayer portaudio)
    target_link_libraries(AudioPlayer "-framework CoreAudio")
    target_link_libraries(AudioPlayer "-framework AudioToolbox")
    target_link_libraries(AudioPlayer "-framework AudioUnit")
    target_link_libraries(AudioPlayer "-framework CoreServices")
    target_link_libraries(AudioPlayer "-framework Carbon")
endif()

# executable for testing 
project(AudioPlayerExe)
add_executable(AudioPlayerExe ${SOURCES})
target_include_directories(AudioPlayerExe PRIVATE include)
target_link_directories(AudioPlayerExe PRIVATE lib)

target_link_libraries(AudioPlayerExe portaudio)
target_link_libraries(AudioPlayerExe "-framework CoreAudio")
target_link_libraries(AudioPlayerExe "-framework AudioToolbox")
target_link_libraries(AudioPlayerExe "-framework AudioUnit")
target_link_libraries(AudioPlayerExe "-framework CoreServices")
target_link_libraries(AudioPlayerExe "-framework Carbon")
