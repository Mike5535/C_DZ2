#include "../headers/thread_count.h"

pthread_mutex_t mutex;

void threadFunc(void* thread_data) {
    
    pthrData* data = (pthrData*)thread_data;

    size_t* temp = count_pair(data->work_file);

    if(temp) printf("ERROR%zu\n",temp[1]);    

    pthread_mutex_lock(&mutex);
    for (size_t i = 0; i < NUM_COUNTS; i++)
    {
        data->num_all[i] += temp[i];
    }
    pthread_mutex_unlock(&mutex);

    /*printf("count\n");
    for (size_t k = 0; k < 11; k++)
        {
            printf("%zu\n", data->num_all[k]);

        }
    printf("end\n");*/

    free(temp);

    return NULL;
}

void part_file(const size_t step, FILE* block, FILE* input)
{
    char* buffer=(char*)malloc(step*sizeof(char));
    size_t nread;

    nread = fread(buffer, 1, step, input);
    printf("nread:%zu step:%zu\n",nread, step);
    fwrite(buffer, 1, nread, block);
    fseek(block, 0, SEEK_SET);
    free(buffer);
}

size_t* processing_threads(FILE* const input_file)
{
    fseek(input_file,0,SEEK_END);
    size_t size_file = ftell(input_file);
    fseek(input_file,0,SEEK_SET);
    printf("File size: %zu \n", size_file);

    size_t num_CPU = sysconf(_SC_NPROCESSORS_ONLN);
    printf("num_CPU: %zu \n", num_CPU);

    size_t num_threads = 2 * num_CPU;

    const size_t step_bytes = size_file / num_threads;
    printf("step_bytes: %zu \n", step_bytes);

    const size_t last_step = size_file - (step_bytes * (num_threads - 1));
    printf("last_step: %zu \n", last_step);

    size_t* result_count = (size_t*)malloc(NUM_COUNTS * sizeof(size_t)); 

    pthread_t* threads = (pthread_t*)malloc(num_threads * sizeof(pthread_t));

    pthrData* threadData = (pthrData*)malloc(num_threads * sizeof(pthrData));

    for (size_t j = 0; j < NUM_COUNTS; j++)
    {
        result_count[j] = 0;
    }


    FILE** block = (FILE**)malloc(num_threads * sizeof(FILE*));

    pthread_mutex_init(&mutex, NULL);

    for (size_t i = 0; i < num_threads - 1; i++)
    {
        block[i] = tmpfile();
        if( i!= 0)
            part_file(step_bytes+1, block[i], input_file);
        else
            part_file(step_bytes, block[i], input_file);

        threadData[i].num_all = result_count;
        threadData[i].work_file = block[i];

        pthread_create(&(threads[i]), NULL, threadFunc, &threadData[i]);
        fseek(input_file, -1, SEEK_CUR);
    }

    //last step
    block[num_threads - 1] = tmpfile();
    part_file(last_step+1, block[num_threads - 1], input_file);

    threadData[num_threads - 1].num_all = result_count;
    threadData[num_threads - 1].work_file = block[num_threads - 1];
    pthread_create(&(threads[num_threads - 1]), NULL, threadFunc, &threadData[num_threads - 1]);


    for (size_t i = 0; i < num_threads; i++)
    {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);

    for (size_t i = 0; i < num_threads; i++)
        free(block[i]);

    free(threads);
    free(threadData);
    free(block);

    return result_count;
}
