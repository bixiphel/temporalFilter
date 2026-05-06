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
	if (argc >= 3 && argv[2][0] != '-') {
        strcpy(cfg->output_file, argv[2]);
    }

	// Processes the remaining arguments 
    for (int i = 3; i < argc; i++) {
		// Saves the filter name
        if (strcmp(argv[i], "--filter") == 0) {
            strcpy(cfg->filter, argv[++i]);
        }

		// Saves the value for sigma_s
        else if (strcmp(argv[i], "--sigma_s") == 0) {
            cfg->sigma_s = atof(argv[++i]);
        }

		// Saves the value for sigma_t
        else if (strcmp(argv[i], "--sigma_t") == 0) {
            cfg->sigma_t = atof(argv[++i]);
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
		"\n"		
	,cfg->input_file, cfg->output_file, cfg->filter, cfg->sigma_s, cfg->sigma_t
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

		 " --help\n"
		 "   Shows this message\n"
		"\n"	
			
	);

}

