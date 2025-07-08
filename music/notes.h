//
// Created by Tristan on 6/29/2025.
//

#ifndef NOTES_H
#define NOTES_H

static const float C0_FREQ = 16.35160f; // Frequency of C0

enum SemitoneOffsetInOctave{
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
