#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "sort.h"

const size_t MAX_STR_LEN = 1000;

int readText(FILE* fp, char* text[], size_t len);
int compareForward(const void* aptr, const void* bptr);
//int compareBackward(const char** a, const char** b);

int main()
{
    const size_t maxLines = 1000;
    char* textPtrs[maxLines] = {};

    FILE* input = NULL;
    if ((input= fopen("input.txt", "r")) == NULL) {
        return -1;
    }

    int readText(input, textPtrs, nStr);

    msort(textPtrs, maxLines, sizeof(textPtrs[0]), &compareForward);

    for (size_t i = 0; i < maxLines; i++)
    {
        printf("%ld. %p <%s>", i + 1, textPtrs[i], textPtrs[i]);
    }

    for (size_t i = 0; i < maxLines; i++)
    {
        free(textPtrs[i]);
    }


    return 0;
}

int readText(FILE* fp, char* text[], size_t len)
{
    char buffer[1000] = "";
    int nLines = 0;
    while (fgets(buffer, MAX_STR_LEN, fp) != -1 && nLines < len)
    {
        text[nLines] = strdup(buffer);
    }

    return nLines;
}

int compareForward(const void* aptr, const void* bptr)
{
    size_t aIdx = 0, bIdx = 0;

    char* a = *(char **) aptr;
    char* b = *(char **) bptr;

    while (a[aIdx] != '\0' && b[bIdx] != '\0')
    {
        if (!isalpha(a[aIdx])) {
            aIdx++;
        } else if (!isalpha(b[bIdx])) {
            bIdx++;
        } else if (a[aIdx] > b[bIdx]) {
            return 1;
        } else if (a[aIdx] < b[bIdx]) {
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