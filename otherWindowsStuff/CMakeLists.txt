cmake_minimum_required(VERSION 3.19)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_VS_SDK_INCLUDE_DIRECTORIES $(VC_IncludePath);$(WindowsSDK_IncludePath); ${CMAKE_SOURCE_DIR}/includes)


set(SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/PortAudioDemo.cpp
)

# DLL files
project(SimpleAudioPlayerDLL)
add_library(SimpleAudioPlayerDLL SHARED ${SOURCE_FILES})
target_include_directories(SimpleAudioPlayerDLL PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/includes)
target_link_libraries(SimpleAudioPlayerDLL portaudio)
target_link_directories(SimpleAudioPlayerDLL PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/lib)

# Exe for testing.
project(SimpleAudioPlayer)
add_executable(SimpleAudioPlayer ${SOURCE_FILES})
target_include_directories(SimpleAudioPlayer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/includes)
target_link_libraries(SimpleAudioPlayer portaudio)
target_link_directories(SimpleAudioPlayer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/lib)
