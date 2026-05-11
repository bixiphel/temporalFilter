#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "video_utils.h"


/* Extracts frames from the input file */
void extract_frames(Config* cfg) {
    char command[1024];

    snprintf(
        command,
        sizeof(command),
        "mkdir -p temp/frames && "
        "ffmpeg -i %s temp/frames/output-%%06d.pgm",
        cfg->input_file
    );

    printf("Extracting frames...\n");

    int ret = system(command);

    if (ret != 0) {
        printf("FFmpeg frame extraction failed.\n");
        exit(1);
    }
}


/* Determines the FPS for the input file */
void extract_fps(Config* cfg) {
    char command[512];

    snprintf(
        command,
        sizeof(command),
        "ffprobe -v 0 -select_streams v:0 "
        "-show_entries stream=avg_frame_rate "
        "-of default=noprint_wrappers=1:nokey=1 %s",
        cfg->input_file
    );

    FILE* pipe = popen(command, "r");

    if (!pipe) {
        printf("Failed to run ffprobe\n");
        cfg->fps = 30.0f;
        return;
    }

    int num = 0, den = 1;

    fscanf(pipe, "%d/%d", &num, &den);

    pclose(pipe);

    if (den == 0) {
        cfg->fps = 30.0f;
    }
    else {
        cfg->fps = (float)num / (float)den;
    }

    printf("Detected FPS: %.3f\n", cfg->fps);
}


/* Assembles frames back into a video file */
void assemble_video(Config* cfg) {
    char command[1024];

    snprintf(
        command,
        sizeof(command),
        "ffmpeg -start_number %d" 
        " -framerate %.3f "
        "-i temp/output/out_%%06d.pgm "
        "-c:v libx264 -pix_fmt yuv420p %s",
        cfg->radius,
        cfg->fps,
        cfg->output_file
    );

    printf("Encoding video...\n");

    int ret = system(command);

    if (ret != 0) {
        printf("FFmpeg encoding failed.\n");
        exit(1);
    }
}
