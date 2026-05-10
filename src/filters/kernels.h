#ifndef KERNELS_H
#define KERNELS_H

typedef struct {
    int radius;
    int size;
    
    float** weights;
} Kernel;

// Creates a 1D gaussian kernel using a specified sigma paramter
Kernel* createGaussian(float sigma, int radius);

// Clears a kernel from memory
void destroyGaussian(Kernel* kernel);

#endif
