#include <stdio.h>

#include "cli/args.h"
#include "io/frame_sequence.h"
#include "io/pgm.h"
#include "io/video_utils.h"
#include "core/frame.h"
#include "filters/kernels.h"
#include "filters/gaussian.h"

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


    /* Spatiotemporal Filtering */
    Frame* input = readPGM(
        "../temp/frames/output_000001.pgm"
    );

    Frame* temp = createFrame(
        input->width,
        input->height
    );

    Frame* output = createFrame(
        input->width,
        input->height
    );

    Kernel* kernel =
        createKernel(2.0f, 3);

    gauss_x(input, temp, kernel);

    gauss_y(temp, output, kernel);

    writePGM("output.pgm", output);

    destroyFrame(input);
    destroyFrame(temp);
    destroyFrame(output);

    destroyKernel(kernel);

    return 0;    

}
