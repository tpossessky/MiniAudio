cmake_minimum_required(VERSION 3.31)
project(MiniAudio C)

set(CMAKE_C_STANDARD 11)

add_executable(MiniAudio main.c
        libs/miniaudio.h
        dsp/dsp.h
        music/sound.h
        music/notes.h
)
