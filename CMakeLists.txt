#im not updating anything on my mac
if(UNIX)
    cmake_minimum_required(VERSION 3.26)
else()
    cmake_minimum_required(VERSION 3.31)
endif ()

project(MiniAudio C)

set(CMAKE_C_STANDARD 11)

add_executable(MiniAudio main.c
        libs/miniaudio.h
        dsp/dsp.h
        music/notes.c
        main.h
)
