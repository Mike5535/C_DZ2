#include "thread_count.h"

void threadFunc(void* thread_data){
	pthrData* data = (pthrData*) thread_data;
    size_t i = data->value_bytes;
    FILE* input_file = data->work_file; 
    
 
	size_t z_o = 0;
    char c[2];
    c[z_o] = fgetc(input_file);
    z_o++;

    size_t number_byts = 0;
    while ((c[z_o] = fgetc(input_file)) != EOF)
    {
        if (z_o)
            z_o--;
        else 
            z_o++; 
        if (c[0] - c[1] == i || c[1] - c[0] == i)
            data->num_all[i]++;
    }
    fseek(input_file, 0, SEEK_SET);

	return NULL;
}

size_t* processing_threads(FILE* source_file)
{
    size_t* result_count = (size_t*) malloc(NUM_THREADS * sizeof(size_t));

    pthread_t* threads = (pthread_t*) malloc(NUM_THREADS * sizeof(pthread_t));

    pthrData* threadData = (pthrData*) malloc(NUM_THREADS * sizeof(pthrData));

   
    

    for (size_t j = 0; j < NUM_THREADS; j++)
    {
        result_count[j] = 0;
    }

    for(size_t i = 0; i < NUM_THREADS; i++)
    {
        threadData[i].work_file = source_file;
        threadData[i].value_bytes = i;
        threadData[i].num_all = result_count;
        pthread_create(&(threads[i]), NULL, threadFunc, &threadData[i]);
    }

    for(size_t i = 0; i < NUM_THREADS; i++)
        pthread_join(threads[i], NULL);

    free(threads);
	free(threadData);

    return result_count;
}
