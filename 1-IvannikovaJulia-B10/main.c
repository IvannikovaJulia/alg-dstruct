#include "memallocator.h"
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <malloc.h>
#pragma warning (disable:4996)
#define MAXIMUM_SIZE 1000
#define MAXIMUM_ITERATION 100
#define ERROR_FILE 1
double malloc_time(int size) {
    LARGE_INTEGER frequency;
    LARGE_INTEGER start, end;
    double res;
    QueryPerformanceFrequency(&frequency);
    char* arr[MAXIMUM_ITERATION] = { NULL };
    QueryPerformanceCounter(&start);
    for (int i = 0; i < MAXIMUM_ITERATION; i++) {
        arr[i] = malloc(rand() % MAXIMUM_SIZE);
        free(arr[i]);
    }
    QueryPerformanceCounter(&end);
    res = (float)(end.QuadPart - start.QuadPart) / frequency.QuadPart;
    return res;
}

double memalloc_time(int size) {
    LARGE_INTEGER frequency;
    LARGE_INTEGER start, end;
    double res;
    QueryPerformanceFrequency(&frequency);
    char* arr[MAXIMUM_ITERATION] = { NULL };
    QueryPerformanceCounter(&start);
    for (int i = 0; i < MAXIMUM_ITERATION; i++) {
        arr[i] = memalloc(rand() % MAXIMUM_SIZE);
        memfree(arr[i]);
    }
    QueryPerformanceCounter(&end);
    res = (float)(end.QuadPart - start.QuadPart) / frequency.QuadPart;
    return res;
}
int main() {
    FILE* file = fopen("comparing.csv", "w");
    if (file == NULL) {
        printf("Error with file opening");
        exit(ERROR_FILE);
    }
    double arr[2];
    fprintf(file, "malloc;memalloc\n");
    for (int i = 1; i < MAXIMUM_SIZE; i++) {
        arr[0] = malloc_time(i);
        arr[1] = memalloc_time(i);
        fprintf(file, "%lf;%lf\n", arr[0], arr[1]);
    }
    fclose(file);
    return 0;
}