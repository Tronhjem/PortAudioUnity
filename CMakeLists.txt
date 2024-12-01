cmake_minimum_required(VERSION 3.19)
project(SimpleAudioPlayer)

set(CMAKE_CXX_STANDARD 17)
include_directories(include/)
link_directories(lib/)

add_library(SimpleAudioPlayer STATIC src/SimpleAudioPlayer.cpp)

target_link_libraries(SimpleAudioPlayer portaudio)
target_link_libraries(SimpleAudioPlayer "-framework CoreAudio")
target_link_libraries(SimpleAudioPlayer "-framework AudioToolbox")
target_link_libraries(SimpleAudioPlayer "-framework AudioUnit")
target_link_libraries(SimpleAudioPlayer "-framework CoreServices")
target_link_libraries(SimpleAudioPlayer "-framework Carbon")


# Main audio player.
# project(MainAudioPlayer)

# add_executable(
#     MainAudioPlayer 
#     src/main.cpp
# )

# target_link_libraries(MainAudioPlayer SimpleAudioPlayer)

project(AudioPlayer)
add_library(AudioPlayer MODULE src/main.cpp)            

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

target_link_libraries(AudioPlayer SimpleAudioPlayer)
