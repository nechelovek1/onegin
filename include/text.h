#ifndef TEXT_H
#define TEXT_H

#include <stdio.h>

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
void skipNonAlphaForward(const char* str, size_t* idx);
void skipNonAlphaBackward(const char* str, size_t* idx);

#endif