#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

void bubbleSort(int arr[], size_t len, int(*compareFunc)(int a, int b))
{
    bool sorted = true;
    for (size_t i = len; i > 1; i--) 
    {
        for (size_t j = 0; j < i - 1; j++)
        {
            if ((*compareFunc)(arr[j], arr[j + 1]) > 1) {
                swap(&arr[j], &arr[j + 1]);
                sorted = false;
            }
        }

        if (sorted) {
            return;
        }
    }
}

void mergeSort(int* arr, size_t len, int(*compareFunc)(int a, int b))
{

    if (len == 1) {
        return;
    }

    if (len == 2) {
        if ((*compareFunc)(arr[0], arr[1]) > 0) {
            swap(&arr[0], &arr[1]);
        }
        return;
    }

    size_t leftSize = len / 2;
    size_t rightSize = len - leftSize;

    mergeSort(arr, leftSize, compareFunc);
    mergeSort(arr + leftSize, rightSize, compareFunc);

    int* left = (int *) calloc(leftSize, sizeof(int));
    int* right = (int *) calloc(rightSize, sizeof(int));

    memmove(left, arr, leftSize * sizeof(int));
    memmove(right, arr + leftSize, rightSize * sizeof(int));   

    size_t iLeft = 0;
    size_t iRight = 0;

    for (size_t i = 0; i < len; i++) 
    {
        if (iLeft >= leftSize) {
            arr[i] = right[iRight];
            iRight++;
        } else if (iRight >= rightSize) {
            arr[i] = left[iLeft];
            iLeft++;
        } else if (left[iLeft] > right[iRight]) {
            arr[i] = right[iRight];
            iRight++;
        } else {
            arr[i] = left[iLeft];
            iLeft++;
        }
    }

    free(left);
    free(right);
}

int compareUp(int a, int b)
{
    return a - b;
}

int compareRand(int a, int b)
{
    return rand() % 3 - 1;
}

int compUp(const int* a, const int* b)
{
    return *a - *b;
}

void msort(void* arr, size_t len, size_t elemSize, int(*compareFunc)(const void* a, const void* b))
{

    if (len == 1) {
        return;
    }

    if (len == 2) {
        if ((*compareFunc)(arr, arr + elemSize) > 0) {
            swapElems(arr, arr + elemSize, elemSize);
        }
        //printf("%d %d\n", *(int *) arr, *(int *) (arr + elemSize));
        return;
    }

    size_t leftSize = len / 2;
    size_t rightSize = len - leftSize;

    msort(arr, leftSize, elemSize, compareFunc);
    msort(arr + leftSize * elemSize, rightSize, elemSize, compareFunc);

    void* left = calloc(leftSize, elemSize);
    void* right = calloc(rightSize, elemSize);

    memmove(left, arr, leftSize * elemSize);
    memmove(right, arr + leftSize * elemSize, rightSize * elemSize);   

    size_t iLeft = 0;
    size_t iRight = 0;

    for (size_t i = 0; i < len; i++) 
    {
        if (iLeft >= leftSize) {
            //arr[i] = right[iRight];
            memmove(arr + i * elemSize, right + iRight * elemSize, elemSize);
            //moveElem(arr + i * elemSize, right + iRight * elemSize, elemSize);
            iRight++;
        } else if (iRight >= rightSize) {
            //arr[i] = left[iLeft];
            memmove(arr + i * elemSize, left + iLeft * elemSize, elemSize);
            //moveElem(arr + i * elemSize, left + iLeft * elemSize, elemSize);
            iLeft++;
        } else if ((*compareFunc)(left + iLeft * elemSize, right + iRight * elemSize) > 0) {
            //arr[i] = right[iRight];
            memmove(arr + i * elemSize, right + iRight * elemSize, elemSize);
            //moveElem(arr + i * elemSize, right + iRight * elemSize, elemSize);
            iRight++;
        } else {
            //arr[i] = left[iLeft];
            memmove(arr + i * elemSize, left + iLeft * elemSize, elemSize);
            //moveElem(arr + i * elemSize, left + iLeft * elemSize, elemSize);
            iLeft++;
        }
    }

    free(left);
    free(right);
}

void swapElems(void* a, void* b, size_t elemSize)
{
    char* tmp = calloc(1, elemSize);
    
    memmove(tmp, a, elemSize);
    memmove(a, b, elemSize);
    memmove(b, tmp, elemSize);

    free(tmp);
    
    //for (size_t i = 0; i < elemSize; i++)
    //{
    //    char tmp = *(char* ) (b + i);
    //    *(char* ) (b + i) = *(char* ) (a + i);
    //    *(char* ) (a + i) = tmp;
    //}
}

void moveElem(void* dest, const void* src, size_t elemSize)
{
    for (size_t i = 0; i < elemSize; i++)
    {
        *(char *) (dest + i) = *(char *) (src + i);
    }
}