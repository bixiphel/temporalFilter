#include <stdlib.h>
#include "temporal_buffer.h"

/* Creates a buffer */
TemporalBuffer* createBuffer(int radius) {
    // Allocates memory for a temporal buffer
    TemporalBuffer* buffer = malloc(sizeof(TemporalBuffer));

    // Sets the data fields of the buffer
    buffer->radius = radius;
    buffer->size = radius * 2 + 1;
    buffer->frames = malloc(buffer->size * sizeof(Frame*));

    // Creates an empty buffer of the specfied size    
    for(int i = 0; i < buffer->size; i++) {
        buffer->frames[i] = NULL;
    }

    return buffer;
}

/* Clears the buffer from memory */
void destroyBuffer(TemporalBuffer* buffer) {
    // Clears each frame from memory 
    for(int i = 0; i < buffer->size; i++) {
        // If the frame exists, clear it
        if(buffer->frames[i] != NULL) {
            destroyFrame(buffer->frames[i]);
        }
    }

    // Remove the buffer from memory entirely
    free(buffer->frames);
    free(buffer);
}

/* Moves the buffer to the next frame */
void shiftBuffer(TemporalBuffer* buffer) {
    // Removes the first frame from the buffer
    destroyFrame(buffer->frames[0]);

    // Shifts the remaining frames in the buffer over to the left by 1 frame
    for(int i = 0; i < buffer->size - 1; i++) {
        buffer->frames[i] = buffer->frames[i+1];
    }

    buffer->frames[buffer->size - 1] = NULL;
}


