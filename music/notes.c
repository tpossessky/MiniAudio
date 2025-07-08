//
// Created by Tristan Possessky on 7/8/25.
//
#include <math.h>
#include "notes.h"

float getNoteFrequency(enum SemitoneOffsetInOctave semitone_offset, int octave)
{
    // C0 is our reference. Each semitone is 1/12th of an octave.
    // Each octave doubles the frequency (or halves if going down).
    // The total number of semitones from C0 is:
    // (octave * 12) + semitone_offset
    int total_semitones_from_c0 = (octave * 12) + semitone_offset;

    // Formula: f = C0_FREQ * 2 ^ (total_semitones_from_c0 / 12.0f)
    return C0_FREQ * powf(2.0f, (float)total_semitones_from_c0 / 12.0f);
}