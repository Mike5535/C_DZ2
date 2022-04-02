#ifndef THREAD_H
#define THREAD_H
#include <pthread.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define NUM_COUNTS 11

typedef struct {
    size_t* num_all;
    FILE* work_file;
} pthrData;

void threadFunc(void* thread_data);
void part_file(const size_t step, FILE* block, FILE* input);
size_t* processing_threads(FILE* const input_file);
#endif // THREAD_H
