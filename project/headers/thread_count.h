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

#define NUM_THREADS 11

typedef struct{
    size_t* num_all;
	FILE* work_file;
} pthrData;

size_t getFileSize(const char* file_name);
void threadFunc(void* thread_data);
size_t* processing_threads(FILE* source_file,const char* path_file);
#endif // THREAD_H
