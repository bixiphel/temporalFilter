#ifndef TEMPORAL_BUFFER_H
#define TEMPORAL_BUFFER_H

#include "../core/frame.h"

typedef struct {
    int radius;     // How many frames outwards from the center are considered in the buffer (i.e. r=1 means frame -1, frame 0 (the target frame), and frame +1 are considered)
    int size;       // How many frames are in the buffer
    
    Frame** frames;  
} TemporalBuffer;

/* Functions relating to the temporal buffer */

// Creates a buffer
TemporalBuffer* createBuffer(int radius);

// Clears a buffer from memory
void destroyBuffer(TemporalBuffer* buffer);

// Moves the buffer to the next frame
void shiftBuffer(TemporalBuffer* buffer);

#endif
