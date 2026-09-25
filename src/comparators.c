#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "text.h"

int compareForward(const void* aptr, const void* bptr)
{
    size_t aIdx = 0, bIdx = 0;

    const char* a = ((Line *) aptr)->line;
    const char* b = ((Line *) bptr)->line;

    while (a[aIdx] != '\0' && b[bIdx] != '\0')
    {
        skipNonAlphaForward(a, &aIdx);
        skipNonAlphaForward(b, &bIdx);
        if (tolower(a[aIdx]) > tolower(b[bIdx])) {
            return 1;
        } else if (tolower(a[aIdx]) < tolower(b[bIdx])) {
            return -1;
        } else {
            aIdx++;
            bIdx++;
        }

    }

    skipNonAlphaForward(a, &aIdx);
    skipNonAlphaForward(b, &bIdx);

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

    while (aIdx > 0 && bIdx > 0)
    {
        skipNonAlphaBackward(a, &aIdx);
        skipNonAlphaBackward(b, &bIdx);
        if (tolower(a[aIdx]) > tolower(b[bIdx])) {
            return 1;
        } else if (tolower(a[aIdx]) < tolower(b[bIdx])) {
            return -1;
        } else {
            aIdx--;
            bIdx--;
        }

    }

    skipNonAlphaBackward(a, &aIdx);
    skipNonAlphaBackward(b, &bIdx);

    if (aIdx == 0 && bIdx == 0) {
        return a[aIdx] - b[bIdx];
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