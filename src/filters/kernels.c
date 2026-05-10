#include <math.h>
#include <stdlib.h>
#include "kernels.h"

// Creates a 1D Gaussian using the specified sigma parameter
Kernel* createGaussian(float sigma, int radius) {
    // Allocate memory for the kernel
    Kernel* kernel = malloc(sizeof(Kernel));

    // Substitute in the specified parameters
    kernel->sigma = sigma;                                      // The spread of that parameter
    kernel->radius = radius;                                    // How many frames after/before that are considered
    kernel->size = radius * 2 + 1;                              // The total number of frames surrounding (and including) a target frame
    kernel->weights = malloc(kernel->size * sizeof(float));     // These are the weights for the kernel

    // Used to later normalize the kernel
    float sum = 0.0f;

    // Uses the simplified equation for a Gaussian to calculate the expontential term
    for(int i = -radius; i <= radius; i++) {
        float value = expf(-(i*i) / (2.0f * sigma* sigma));     
        
        kernel->weights[i + radius] = value;
        sum += value;
    }

    // Normalizes the kernel
    for(int i = 0; i < kernel->size; i++) {
        kernel->weights[i] /= size;
    }

    return kernel;
}

/* Clears a kernel from memory */
void destroyKernel(Kernel* kernel) {
    free(kernel->weights);
    free(kernel);
}








