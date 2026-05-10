#include <math.h>
#include "gaussian.h"

/* Helper function to clamp values between a specified min and max */
static int clamp(int value, int min, int max) {
    if(value < min) {
        return min;
    }

    if(value > max) {
        return max;
    }
        
    return value;
}

void gauss_x(Frame* input, Frame* output, Kernel* kernel) {
    // Sets the specified width and height
    int width = input->width;
    int height = input->height;

    int radius = kernel->radius;

    // Iterates through the spatial domain 
    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            float sum = 0.0f;
            
            // Calculates the sum of pixels within the kernel
            for(int k = -radius; k <= radius; k++) {
                // Checks to see if the frame is within bounds
                int sample_x = clamp(x + k, 0, width - 1);

                sum += kernel->weights[k + radius] * input->data[y*width + sample_x];            
            }
            
            // Writes to the output Frame
            output->data[y*width + x] = (unsigned char) sum;        
        }
    }
}

void gauss_y(Frame* input, Frame* output, Kernel* kernel) {
    // Sets the corresponding data from the specified inputs
    int width = input->width;
    int height = input->height;
    int radius = kernel->radius;

    // Iterates through the spatial domain
    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            float sum = 0.0f;
            
            // Calculates the sum of pixels within the kernel
            for(int k = -radius; k <= radius; k++) {
                int sample_y = clamp(y+k, 0, height - 1);
                
                sum += kernel->weights[k+radius] * input->data[sample_y * width + x];    
            }
            
            // Writes to the output Frame
            output->data[y*width + x] = (unsigned char) sum;
        }
    }
}

void gauss_t(TemporalBuffer* buffer, Frame* output, Kernel* kernel) {
    // Finds the center frame within the temporal buffer
    Frame* center = buffer->frames[buffer->radius];

    // Sets the width and height
    int width = center->width;
    int height = center->height;
        
    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            float sum = 0.0f;
            
            // Iterates through the temporal buffer
            for(int k = 0; k < buffer->size; k++) {
                Frame* frame = buffer->frames[k];
                
                sum += kernel->weights[k] * frame->data[y*width + x];
            }
            
            // Writes to the output
            output->data[y*width + x] = (unsigned char) sum;
        }
    }
}



