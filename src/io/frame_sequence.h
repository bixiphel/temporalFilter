#ifndef FRAME_SEQUENCE_H
#define FRAME_SEQUENCE_H

typedef struct {
    char** filenames;       // Points to the filenames in memory

    int count;              // Stores the number of frames in the sequence
} FrameSequence;

// Loads a sequence of frames
FrameSequence* loadSequence(const char* directory);

// Clears a sequence from memory
void destroySequence(FrameSequence* sequence);

#endif
