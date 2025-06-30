//
// Created by Tristan on 6/29/2025.
//

#ifndef NOTES_H
#define NOTES_H

static const float C0_FREQ = 16.35160f; // Frequency of C0

typedef enum {
    SEMITONE_C = 0,
    SEMITONE_CS = 1, // C#
    SEMITONE_DB = 1, // Db (enharmonic with C#)
    SEMITONE_D = 2,
    SEMITONE_DS = 3, // D#
    SEMITONE_EB = 3, // Eb
    SEMITONE_E = 4,
    SEMITONE_F = 5,
    SEMITONE_FS = 6, // F#
    SEMITONE_GB = 6, // Gb
    SEMITONE_G = 7,
    SEMITONE_GS = 8, // G#
    SEMITONE_AB = 8, // Ab
    SEMITONE_A = 9,
    SEMITONE_AS = 10, // A#
    SEMITONE_BB = 10, // Bb
    SEMITONE_B = 11
} SemitoneOffsetInOctave;

static float getNoteFrequency(SemitoneOffsetInOctave semitone_offset, int8_t octave)
{
    // C0 is our reference. Each semitone is 1/12th of an octave.
    // Each octave doubles the frequency (or halves if going down).
    // The total number of semitones from C0 is:
    // (octave * 12) + semitone_offset
    int total_semitones_from_c0 = (octave * 12) + semitone_offset;

    // Formula: f = C0_FREQ * 2 ^ (total_semitones_from_c0 / 12.0f)
    return C0_FREQ * powf(2.0f, (float)total_semitones_from_c0 / 12.0f);
}
typedef enum {
    _32_NOTE,
    _16_NOTE,
    _8_NOTE,
    _4_NOTE,
    _2_NOTE,
    _1_NOTE,
} NoteLength;

#endif //NOTES_H
