#ifndef ARGS_H
#define ARGS_H

typedef struct
{
    // File names
    char input_file[256];	// String represention of the input file's name
    char output_file[256];	// String rep. of the output file's name

    float fps;          // The frames per second of the input video

    // Filter name
    char filter[256];	// Name of the filter used

    // Radius of filter
    int radius;

    // Filter parameters
    float sigma_s;		// Spatial spread for Spatiotemporal Gaussian Filter
    float sigma_t;		// Temporal spread for Spatiotemporal Gaussian Filter

} Config;

// Function to initialize default values 
void init_config(Config* cfg);

// Parses arguments
void parse_config(int argc, char** argv, Config* cfg);

// Prints the current configuration (debug)
void print_config(Config* cfg);

// Print help message
void print_help();


#endif
