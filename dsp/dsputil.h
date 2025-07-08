//
// Created by Tristan on 6/30/2025.
//

#ifndef DSPUTIL_H
#define DSPUTIL_H

static float getRandomFloat() {
    // Note: rand() typically returns int up to RAND_MAX.
    // Casting to float and dividing converts it to 0.0-1.0 range.
    // Then scale to -1.0 to 1.0.
    return ((float)rand() / (float)RAND_MAX) * 2.0f - 1.0f;
}



#endif //DSPUTIL_H
