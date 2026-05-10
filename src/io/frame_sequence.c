#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#include "frame_sequence.h"

/* Helper function to compare */
static int compare(const void* a, const void* b)
{
    return strcmp(*(char**)a, *(char**)b);
}

/* Loads a sequence into memory */
FrameSequence* loadSequence(const char* directory)
{
    DIR* dir = opendir(directory);

    if (!dir)
    {
        printf("Failed to open directory\n");
        return NULL;
    }

    FrameSequence* seq = malloc(sizeof(FrameSequence));

    seq->filenames = NULL;
    seq->count = 0;

    struct dirent* entry;

    while ((entry = readdir(dir)) != NULL)
    {
        if (strstr(entry->d_name, ".pgm"))
        {
            seq->filenames = realloc(
                seq->filenames,
                sizeof(char*) * (seq->count + 1)
            );

            seq->filenames[seq->count] =
                strdup(entry->d_name);

            seq->count++;
        }
    }

    closedir(dir);

    qsort(seq->filenames, seq->count, sizeof(char*), compare);

    return seq;
}

/* Clears a sequence from memory */
void destroySequence(FrameSequence* seq)
{
    for (int i = 0; i < seq->count; i++)
    {
        free(seq->filenames[i]);
    }

    free(seq->filenames);
    free(seq);
}
