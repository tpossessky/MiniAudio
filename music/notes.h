//
// Created by Tristan on 6/29/2025.
//

#ifndef NOTES_H
#define NOTES_H

static const float NOTE_C1_FREQ  = 32.70320f;
static const float NOTE_Cs1_FREQ = 34.64783f;
static const float NOTE_Db1_FREQ = 34.64783f;
static const float NOTE_D1_FREQ  = 36.70810f;
static const float NOTE_Ds1_FREQ = 38.89087f;
static const float NOTE_Eb1_FREQ = 38.89087f;
static const float NOTE_E1_FREQ  = 41.20344f;
static const float NOTE_F1_FREQ  = 43.65353f;
static const float NOTE_Fs1_FREQ = 46.24930f;
static const float NOTE_Gb1_FREQ = 46.24930f;
static const float NOTE_G1_FREQ  = 48.99943f;
static const float NOTE_Gs1_FREQ = 51.91309f;
static const float NOTE_Ab1_FREQ = 51.91309f;
static const float NOTE_A1_FREQ  = 55.00000f;
static const float NOTE_As1_FREQ = 58.27047f;
static const float NOTE_Bb1_FREQ = 58.27047f;
static const float NOTE_B1_FREQ  = 61.73541f;

typedef enum {
    _32_NOTE,
    _16_NOTE,
    _8_NOTE,
    _4_NOTE,
    _2_NOTE,
    _1_NOTE,
} NoteLength;

#endif //NOTES_H
