#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>
#include <errno.h>

#include "sort.h"

typedef struct {
    char* line;
    size_t len;
} Line;

typedef struct {
    char* buffer;
    size_t bufferLen;
    Line* lines;
    size_t nLines;
} TextFile;

int readText(const char* filename, TextFile* textFile);
void splitText(TextFile* textFile);
size_t getFileSize(const char* filename);
size_t getCharCount(const char* str, char c);
int replaceChars(char* str, char oldC, char newC);
int fprintLines(FILE* fp, const TextFile* textFile);
int freeTextFile(TextFile* textFile);
int compareForward(const void* aptr, const void* bptr);
int compareBackward(const void* aptr, const void* bptr);
int compareOriginal(const void* a, const void* b);

int main(int argc, char* argv[])
{
    if (argc != 3) {
        printf("Usage: %s <input filename> <output filename>\n", argv[0]);
        return -1;
    }

    char* inputFilename = argv[1];
    char* outputFilename = argv[2];

    TextFile textFile = {};

    readText(inputFilename, &textFile);

    FILE* output = NULL;
    if ((output = fopen(outputFilename, "w")) == NULL) {
        printf("Failed to open output %s\n", outputFilename);
        return -1;
    }

    //fprintf(output, "JUST READ\n");
    //fprintLines(output, &textFile);

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

int readText(const char* filename, TextFile* textFile)
{
    if (filename == NULL || textFile == NULL) {
        return -1;
    }

    size_t fileSize = getFileSize(filename) + 1;

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        return -1;
    }

    textFile->buffer = (char* ) calloc(fileSize, sizeof(char));

    if(textFile->buffer == NULL) {
        return -1;
    }

    size_t bufferLen = fread(textFile->buffer, sizeof(char), fileSize, file);
    textFile->bufferLen = bufferLen;
    textFile->buffer[textFile->bufferLen + 1] = '\0';
    

    size_t nLines = replaceChars(textFile->buffer, '\n', '\0') + 1;
    textFile->nLines = nLines;
    textFile->lines = (Line* ) calloc(textFile->nLines, sizeof(Line));

    if (textFile->lines == NULL) {
        return -1;
    }

    splitText(textFile);
    fclose(file);

    return 0;
}

void splitText(TextFile* textFile)
{
    textFile->lines[0].line = textFile->buffer;
    textFile->lines[0].len = strlen(textFile->buffer);

    size_t lineIdx = 1;
    for (size_t i = 1; i < textFile->bufferLen; i++)
    {
        if (textFile->buffer[i] == '\0' && lineIdx < textFile->nLines) {
            textFile->lines[lineIdx].line = textFile->buffer + (i + 1);
            textFile->lines[lineIdx].len = strlen(textFile->buffer + (i + 1));
            lineIdx++;
        }
    }

    if (textFile->lines[textFile->nLines - 1].line[0] == '\0') {
        textFile->nLines--;
    }
}

int compareForward(const void* aptr, const void* bptr)
{
    size_t aIdx = 0, bIdx = 0;

    const char* a = ((Line *) aptr)->line;
    const char* b = ((Line *) bptr)->line;

    while (a[aIdx] != '\0' && b[bIdx] != '\0')
    {
        if (!isalpha(a[aIdx])) {
            aIdx++;
        } else if (!isalpha(b[bIdx])) {
            bIdx++;
        } else if (tolower(a[aIdx]) > tolower(b[bIdx])) {
            return 1;
        } else if (tolower(a[aIdx]) < tolower(b[bIdx])) {
            return -1;
        } else {
            aIdx++;
            bIdx++;
        }

    }

    while (a[aIdx] != '\0' && !isalpha(a[aIdx]))
    {
        aIdx ++;
    }
    while (b[bIdx] != '\0' && !isalpha(b[bIdx]))
    {
        bIdx ++;
    }

    if (a[aIdx] == '\0' && b[bIdx] == '\0') {
        return 0;
    } else if (a[aIdx] != '\0') {
        return 1;
    } else {
        return -1;
    }
}

int compareBackward(const void* aptr, const void* bptr)
{
    size_t aIdx = ((Line *) aptr)->len - 1; 
    size_t bIdx = ((Line *) bptr)->len - 1;

    const char* a = ((Line *) aptr)->line;
    const char* b = ((Line *) bptr)->line;

    while (aIdx >= 0 && bIdx >= 0)
    {
        if (!isalpha(a[aIdx])) {
            aIdx--;
        } else if (!isalpha(b[bIdx])) {
            bIdx--;
        } else if (tolower(a[aIdx]) > tolower(b[bIdx])) {
            return 1;
        } else if (tolower(a[aIdx]) < tolower(b[bIdx])) {
            return -1;
        } else {
            aIdx--;
            bIdx--;
        }

    }

    while (aIdx >= 0 && !isalpha(a[aIdx]))
    {
        aIdx --;
    }
    while (bIdx >= 0 && !isalpha(b[bIdx]))
    {
        bIdx --;
    }

    if (aIdx == 0 && bIdx == 0) {
        return 0;
    } else if (aIdx >= 0) {
        return 1;
    } else {
        return -1;
    } 
}

int compareOriginal(const void* aptr, const void* bptr)
{
    size_t a = *((size_t *) aptr);
    size_t b = *((size_t *) bptr);
    return a - b;
}

size_t getFileSize(const char* filename)
{
    struct stat st = {};
    stat(filename, &st);
    return st.st_size;
}

size_t getCharCount(const char* str, char c)
{
    size_t idx = 0;
    size_t cnt = 0;
    while (str[idx] != '\0')
    {
        if (str[idx] == c) {
            cnt++;
        }
        idx++;
    }
    return cnt;
}

int replaceChars(char* str, char oldC, char newC)
{
    size_t idx = 0;
    size_t cnt = 0;
    while (str[idx] != '\0')
    {
        if (str[idx] == oldC) {
            str[idx] = newC;
            cnt++;
        }
        idx++;
    }
    return cnt;
}

int fprintLines(FILE* fp, const TextFile* textFile)
{
    if (fp == NULL || textFile == NULL) {
        return -1;
    }

    for (size_t i = 0; i < textFile->nLines; i++)
    {
        fprintf(fp, "%lu. %s\n", i, textFile->lines[i].line);
    }

    return 0;
}

int freeTextFile(TextFile* textFile)
{
    if (textFile == NULL) {
        return -1;
    }

    free(textFile->buffer);
    free(textFile->lines);

    return 0;
}