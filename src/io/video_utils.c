#include <stdio.h>
#include <stdlib.h>

// Extracts frames from the input file
void extract_frames(char* input_file) {
    // Creates a buffer for calling the FFmpeg command
    char command[1024];

    // Creates the command to call
    sprintf(
        command,                                        // Stores the command in the buffer 'command'
        "mkdir -p temp/frames &&"                       // Creates a folder 'temp' to hold the individual frames
        "ffmpeg -i %s  temp/frames/output-%%06d.ppm",     // Converts each frame into PPM and names each frame as 'output<frame number>.ppm'
        input_file
    );

    // Info message
    printf("Extracting frames...\n");

    // Checks to see if FFmpeg is able to perform the frame extraction
    int ret = system(command);
    if(ret != 0) {
        printf("FFmpeg frame extraction failed.\n");
        exit(1);
    }   
    
}

