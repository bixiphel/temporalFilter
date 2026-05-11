#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "args.h"

// Function to initialize default values 
void init_config(Config* cfg) {
    // File names
    strcpy(cfg->input_file, "");
    strcpy(cfg->output_file, "output.mkv");

    // Filter name
    strcpy(cfg->filter, "gaussian");

    // Radius size
    cfg->radius = 1;
    
    // FPS
    cfg->fps = 30.0f;

    // Filter parameters
    cfg->sigma_s = 1.0f;
    cfg->sigma_t = 1.0f;
}

// Parses arguments
void parse_config(int argc, char** argv, Config* cfg) {

    // Catches if there aren't enough arguments to run a valid process
    if(argc < 2) {
        print_help();
        exit(1);
    }

    // Prints out the help instructions if specified
    if(strcmp(argv[1], "--help") == 0) {
        print_help();
        exit(0);
    }	

    // Saves the name of the input file
    strcpy(cfg->input_file, argv[1]);

    // Saves the name of the output file if given
    int arg_start = 2;      // This is used to determine where the flags start depending on if an output file is specified

    if (argc > 2 && argv[2][0] != '-') {
        strcpy(cfg->output_file, argv[2]);
        arg_start = 3;
    }

    // Processes the remaining arguments 
    for (int i = arg_start; i < argc; i++) {
        // Saves the filter name
        if (strcmp(argv[i], "--filter") == 0) {
            strcpy(cfg->filter, argv[++i]);
        }

        // Saves the value for sigma_s
        else if (strcmp(argv[i], "--sigma_s") == 0) {
            // Checks if a value for sigma_s is given
            if (i + 1 >= argc) {
                printf("Missing sigma_s value\n");
                exit(1);
            }

            float value = atof(argv[++i]);

            if(value < 0 || value == 0) {
                printf("Invalid sigma_s value\n");
                exit(1);	
            } else {
                cfg->sigma_s = value;
            }
        }

        // Saves the value for sigma_t
        else if (strcmp(argv[i], "--sigma_t") == 0) {
            // Checks if a value for sigma_t is given
            if (i + 1 >= argc) {
                printf("Missing sigma_t value\n");
                exit(1);
            }
                
            float value = atof(argv[++i]);

            if(value < 0 || value == 0) {
                printf("Invalid sigma_t value\n");
                exit(1);	
            } else {
                cfg->sigma_t = value;
            }
        }

        // Saves the radius
        else if (strcmp(argv[i], "--radius") == 0) {
            // Checks if a value for the radius is given
            if (i + 1 >= argc) {
                printf("Radius value\n");
                exit(1);
            }

            int value = atoi(argv[++i]);

            if(value < 0 || value == 0) {
                printf("Invalid radius value\n");
                exit(1);
            } else {
                cfg->radius = value;
            }
        }

        // Exits if an unknown argument is found
        else {
            printf("Unknown argument: %s\n", argv[i]);
            exit(1);
        }
    }
}

// Prints the current configuration (debug)
void print_config(Config* cfg) {
    printf(
            "Input file name:	%s\n"
            "Output file name:	%s\n"
            "Filter chosen:		%s\n"
            "Spatial Sigma:		%f\n"
            "Temporal Sigma:		%f\n"
            "Radius:			%d\n"
            "\n"		
            ,cfg->input_file, cfg->output_file, cfg->filter, cfg->sigma_s, cfg->sigma_t, cfg->radius
          );	
}

// Print help message
void print_help() {
    printf(
            "\nUsage:\n"
            "temporalFilter <input.mkv> <output.mkv> [options]\n\n"

            "Options:\n"
            " --filter <name>\n"
            "   Filter type\n\n"

            " --sigma_s <float>\n"
            "Spatial sigma; controls the spatial spread in the Gaussian filter\n\n"

            " --sigma_t <float>\n"
            "Temporal sigma; controls the time spread in the Gaussian filter\n\n"

            " --radius\n"
            "Sets the radius of the filter kernel\n\n"

            " --help\n"
            "   Shows this message\n"
            "\n"	

            );

}

