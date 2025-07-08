//
// Created by Tristan on 6/29/2025.
//

#ifndef NOTES_H
#define NOTES_H

static const float C0_FREQ = 16.35160f; // Frequency of C0

enum SemitoneOffsetInOctave{
    SEMITONE_C = 0,
    SEMITONE_Cs = 1, // C#
    SEMITONE_Db = 1, // Db (enharmonic with C#)
    SEMITONE_D = 2,
    SEMITONE_Ds = 3, // D#
    SEMITONE_Eb = 3, // Eb
    SEMITONE_E = 4,
    SEMITONE_F = 5,
    SEMITONE_Fs = 6, // F#
    SEMITONE_Gb = 6, // Gb
    SEMITONE_G = 7,
    SEMITONE_Gs = 8, // G#
    SEMITONE_Ab = 8, // Ab
    SEMITONE_A = 9,
    SEMITONE_As = 10, // A#
    SEMITONE_Bb = 10, // Bb
    SEMITONE_B = 11
};

enum NoteLength {
    _32_NOTE,
    _16_NOTE,
    _8_NOTE,
    _4_NOTE,
    _2_NOTE,
    _1_NOTE,
};

struct Note {
    float freq;
    enum NoteLength duration;
};

float getNoteFrequency(enum SemitoneOffsetInOctave semitone_offset, int octave);

#endif //NOTES_H
