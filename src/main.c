#include <stdio.h>
#include <sys/stat.h>

#include "cli/args.h"
#include "io/frame_sequence.h"
#include "io/pgm.h"
#include "io/video_utils.h"
#include "core/frame.h"
#include "filters/kernels.h"
#include "filters/gaussian.h"

int main(int argc, char** argv) {

    /* Setup */
    
    // Create the necessary directories for images
    mkdir("temp", 0755);            // Directory containing extracted frames, processed frames, and output
    mkdir("temp/frames", 0755);     // Directory containing extracted frames
    mkdir("temp/output", 0755);     // Directory containing processed frames


	Config cfg;

    /* CLI; process input */


	// Initialize configurations
	init_config(&cfg);

	// Parse configurations
	parse_config(argc, argv, &cfg);

	// Print configurations
	print_config(&cfg);

    // Determine fps value
    extract_fps(&cfg);
 
    /* Frame Extraction */

    // Extract the frames
    extract_frames(&cfg);	

    // Load the frames into a FrameSequence object
    FrameSequence* sequence = loadSequence("temp/frames");


    /* Spatiotemporal Filtering */

    // Create the kernels based on hte sigma values specified by the user
    Kernel* spatial = createKernel(cfg.sigma_s, cfg.radius);
    Kernel* temporal = createKernel(cfg.sigma_t, cfg.radius);


    // Create the buffer used for the temporal gaussian 
    TemporalBuffer* buffer = createBuffer(cfg.radius);
     
    // Preload the buffer with the first (radius)-th frames that are within the radius
    for(int i = 0; i < buffer->size; i++) {
        // Read in the i-th frame in the sequence
        Frame* raw = readPGM(sequence->filenames[i]);

        // Create temporary blank frames
        Frame* temp = createFrame(raw->width, raw->height);
        Frame* filtered = createFrame(raw->width, raw->height);

        // Apply spatial filtering on the i-th frame
        gauss_x(raw, temp, spatial);
        gauss_y(temp, filtered, spatial);

        // Add the filtered frame to the buffer
        buffer->frames[i] = filtered;
        
        // Deallocate the temporary frames
        destroyFrame(raw);
        destroyFrame(temp);
    }
   

    /* Main processing loop */
    for(int t = cfg.radius; t < sequence->count - cfg.radius; t++) {
        // Debug statement
        printf("Processing frame %d\n", t);

        // Apply the temporal gaussian on frames within the buffer
        Frame* output = createFrame(buffer->frames[0]->width, buffer->frames[0]->height);
        gauss_t(buffer, output, temporal);

        // Write to the resulting PGM file
        char filename[256];
        sprintf(filename, "temp/output/out_%06d.pgm",t);
        
        writePGM(filename, output);

        destroyFrame(output);

        // Slide the buffer to the next frame
        shiftBuffer(buffer);

        // Load the next frame into the buffer
        int next = t + cfg.radius + 1;
        if(next < sequence->count) {
            Frame* raw = readPGM(sequence->filenames[next]);
    
            Frame* temp = createFrame(raw->width, raw->height);
            Frame* filtered = createFrame(raw->width, raw->height);

            // Spatial filtering 
            gauss_x(raw, temp, spatial);
            gauss_y(temp, filtered, spatial);

            // Put the filtered frame into the buffer
            buffer->frames[buffer->size - 1] = filtered;

            // Cleanup
            destroyFrame(raw);
            destroyFrame(temp);
        }

    }

    /* Cleanup */

    destroyBuffer(buffer);
    destroyKernel(spatial);
    destroyKernel(temporal);
    destroySequence(sequence);
    printf("Processing complete\n");


    /* Create video from processed frames */
    assemble_video(&cfg);

    return 0;    

}
