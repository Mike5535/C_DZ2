#ifndef THREAD_H
#define THREAD_H
#include <pthread.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
//#include <unistd.h>

#define NUM_THREADS 11

typedef struct{
    size_t value_bytes;
    size_t* num_all;
	FILE* work_file;
} pthrData;


void threadFunc(void* thread_data);
size_t* processing_threads(FILE* source_file);
#endif // THREAD_H
