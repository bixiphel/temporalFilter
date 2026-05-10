#include <stdlib.h>
#include "frame.h"

Frame* createFrame(int width, int height) {
    // Allocates space in memory for a frame
    Frame* frame = malloc(sizeof(Frame));

    // Sets the frame's dimensions to the specified dimensions
    frame->width = width;
    frame->height = height;

    // Allocates memory for the data field 
    frame->data = malloc(width*height);

    return frame;
}

// Clears the frame from memory
void destroyFrame(Frame* frame) {
    // Checks if the frame exists first, frees it if it does
    if(frame == NULL) {
        return;
    } else {
        free(frame->data);
        free(frame);
    }
}
