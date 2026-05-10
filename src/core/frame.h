#ifndef FRAME_H
#define FRAME_H

// Definition of a "Frame" object
typedef struct {
    int width;
    int height;

    unsigned char data*;
} Frame;

/* Functions related to frame objects */

// Creates a blank frame of 'x' width and 'y' height
Frame* createFrame(int width, int height);

// Destroys a specified frame
void destroyFrame(Frame* frame);

#endif
