#include <stdio.h>
#include <stdlib.h>
#include "pgm.h"

/* Reads in a PGM file */
Frame* readPGM(const char* filename) {
    FILE* fp = fopen(filename, "rb");

    // Checks if the file exists
    if (!fp) {
        printf("Failed to open %s\n", filename);
        return NULL;
    }

    // Array that holds the magic number specified by th PGM format
    char num[3];

    int width;      // Width of image
    int height;     // Height of image
    int maxval;     // Maximum intensity within the image

    // Searches the first two characters in the file for the magic number (this is guaranteed by the PGM specifications)
    fscanf(fp, "%2s", num);

    // FFmpeg always uses the same magic number (P5) when generating PGM files, so the magic number should always be P5
    if(num[0] != 'P' || num[1] != '5') {
        printf("Invalid PGM format\n");
        return NULL;
    }

    // Determines the other information about the file
    fscanf(fp, "%d %d", &width, &height);
    fscanf(fp, "%d", &maxval);

    // Finds the next character in the file
    fgetc(fp);

    // Creates a frame with the same dimensions as the input
    Frame* frame = createFrame(width, height);

    // Copies the PGM data into the Frame object
    fread(frame->data, 1, width*height, fp);
    fclose(fp)

    return frame;
}


/* Writes to a PGM file */
int writePGM(const char* filename, Frame* frame) {
    FILE* fp = fopen(filename, "wb");

    // Checks if the file exists
    if(!fp) {
        return 0;
    }

    // Prints the information from the Frame into the specified PGM
    fprintf(fp, "P5\n");                    // Magic number
    fprintf(fp, "%d %d\n", width, height);  // Width and height information
    fprintf(fp, "%d\n", maxval);            // Maximun intensity value

    fwrite(frame->data, 1, frame->width * frame->height, fp);
    
    fclose(fp);

    return 1;
}






