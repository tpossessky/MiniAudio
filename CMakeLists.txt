if(UNIX)
    cmake_minimum_required(VERSION 3.26)
else()
    cmake_minimum_required(VERSION 3.31)
endif ()

project(MiniAudio C)

set(CMAKE_C_STANDARD 11)

add_executable(MiniAudio
        main.c
        libs/miniaudio.h
        music/notes.c
        dsp/dsp.c
        synth/synth.c
)
target_include_directories(MiniAudio PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/dsp
        ${CMAKE_CURRENT_SOURCE_DIR}/libs
        ${CMAKE_CURRENT_SOURCE_DIR}/music
        ${CMAKE_CURRENT_SOURCE_DIR}/synth
)