#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>
#include <errno.h>

#include "sort.h"
#include "comparators.h"
#include "text.h"

int main(int argc, char* argv[])
{
    if (argc != 3) {
        printf("Usage: %s <input filename> <output filename>\n", argv[0]);
        return -1;
    }

    char* inputFilename = argv[1];
    char* outputFilename = argv[2];

    TextFile textFile = {};

    if (readText(inputFilename, &textFile) == -1) {
        printf("Failed to get text from %s", inputFilename);
        return -1;
    }

    FILE* output = NULL;
    if ((output = fopen(outputFilename, "w")) == NULL) {
        printf("Failed to open output %s\n", outputFilename);
        return -1;
    }
    
    msort(textFile.lines, textFile.nLines, sizeof(textFile.lines[0]), &compareForward);
    fprintf(output, "\nSORTED FORWARD\n\n");
    fprintLines(output, &textFile);

    msort(textFile.lines, textFile.nLines, sizeof(textFile.lines[0]), &compareBackward);
    fprintf(output, "\nSORTED BACKWARD\n\n");
    fprintLines(output, &textFile);

    msort(textFile.lines, textFile.nLines, sizeof(textFile.lines[0]), &compareOriginal);
    fprintf(output, "\nRETURNED TO ORIGINAL\n\n");
    fprintLines(output, &textFile);

    freeTextFile(&textFile);

    return 0;
}