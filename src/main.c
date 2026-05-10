#include <stdio.h>
#include "cli/args.h"
#include "io/video_utils.h"

int main(int argc, char** argv) {
	Config cfg;

    /* CLI; process input */


	// Initialize configurations
	init_config(&cfg);

	// Parse configurations
	parse_config(argc, argv, &cfg);

	// Print configurations
	print_config(&cfg);

    
    /* Frame Extraction */


    // Extract the frames
    extract_frames(cfg.input_file);	

	return 0;
}
