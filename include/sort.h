#ifndef SORT_H
#define SORT_H
#include <stdlib.h>

void bubbleSort(int arr[], size_t len, int(*compareFunc)(int a, int b));
void swap(int* a, int* b);
void mergeSort(int* arr, size_t len, int(*compareFunc)(int a, int b));
void msort(void* arr, size_t len, size_t elemSize, int(*compareFunc)(const void* a, const void* b));
int compareUp(int a, int b);
int compareRand(int a, int b);
int compUp(const int* a, const int* b);
void swapElems(void* a, void* b, size_t elemSize);
void moveElem(void* dest, const void* src, size_t elemSize);

#endif