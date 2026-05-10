#ifndef GAUSSIAN_H
#define GAUSSIAN_H

#include "../core/frame.h"
#include "kernels.h"
#include "../video/temporal_buffer.h"

// Below defines the 1D Gaussians for each dimension

void gauss_x(Frame* input, Frame* output, Kernel* kernel);
void gauss_y(Frame* input, Frame* output, Kernel* kernel);
void gauss_t(TemporalBuffer* buffer, Frame* output, Kernel* kernel);

#endif
