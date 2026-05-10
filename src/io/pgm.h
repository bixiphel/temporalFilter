#ifndef PGM_H
#define PGM_H

#include "../core/frame.h"

// Reads in a PGM file
Frame* readPGM(const char* filename);

// Writes to a PGM file
int writePGM(const char* filename, Frame* frame);

#endif
