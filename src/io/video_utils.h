#ifndef VIDEO_UTILS_H
#define VIDEO_UTILS_H

#include "../cli/args.h"

// Extracts frames from the input file
void extract_frames(Config* cfg);

// Puts frames back into a video file
void assemble_video(Config* cfg);

// Gets the fps value from the input file
void extract_fps(Config* cfg);

#endif
